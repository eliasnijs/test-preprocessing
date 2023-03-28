#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "baselayer.h"
#include "baselayer.c"

#include "config.h"

#define IsWhiteSpace(a) (((a) == ' ' || (a) == '\n' || (a) == EOF) ? 1 : 0)
#define IsLineBreak(a) (((a) == '\n' || (a) == EOF) ? 1 : 0)
#define StrPrintRange(a,b,c) \
  do {\
    for (int i = (b); i < (c); ++i) printf("%c", a[i]);\
    printf("\n");\
  } while(0);

typedef struct StrBuffer {
  char *buffer;
  S32 n;
} StrBuffer;

typedef struct StrNode {
  struct StrNode *prev;
  char str[32]; 
} StrNode;

internal S32 
readfile(char *path, StrBuffer *strbuffer) 
{
  S32 err_code = 0, l_file = 0;
  FILE *file = fopen(path, "rb");

  if (!file) 
  {
    LogErrStr("failed to open file stream!"); 
    err_code = 1;
    goto err1; 
  }
  fseek(file, 0, SEEK_END);
  l_file = ftell(file);
  fseek(file, 0, SEEK_SET);

  strbuffer->buffer = (char *)malloc(l_file * sizeof(char));
  if (!strbuffer) 
  {
    LogErrStr("failed to allocate memory for buffer!"); 
    err_code = 2;
    goto err2; 
  }
  strbuffer->n = l_file;
  fread(strbuffer->buffer, sizeof(char), strbuffer->n, file);

err2:
  fclose(file);
err1:
  return(err_code);
}

internal void
strnodes_die(StrNode *l)
{
  while (l) 
  {
    StrNode *t = l->prev;
    free(l);
    l = t;
  }
}

internal S32 
parse(StrBuffer *strbuffer, StrNode **strnode)
{
  S32 err_code = 0;

  S32 n = strbuffer->n, i_line = 0, i = 0;
  char *buffer = strbuffer->buffer, *line = buffer;
  B32 is_function = false;
  *strnode = 0x0;
  while (line < buffer + n) 
  {
    is_function = false;
    i_line = 0;
    while (!IsWhiteSpace(line[i_line]) &&
            !is_function) 
    {
      if (line[i_line] == '(') 
      {
        StrNode *new_node = (StrNode *)calloc(1, sizeof(StrNode));
        if (!new_node) 
        {
          strnodes_die(*strnode);
          LogErrStr("failed to allocate memory for new node!");
          err_code = 1; 
          goto err1;  
        }
        for (i = 0; i < i_line && i < ArrayCount(new_node->str); ++i) 
        {
          new_node->str[i] = line[i];
        }
        if (*strnode) 
        {
          new_node->prev = *strnode;
        }
        *strnode = new_node;
        is_function = true;
      }
      ++i_line;
    }
    while (!IsLineBreak(line[i_line])) 
    {
      ++i_line;
    }
    line += i_line + 1;
  }

err1:

  return(err_code);
}

internal S32
makefile(char *path, char *name, char *ts_path, StrNode *strnode, StrBuffer *strbuffer)
{
  S32 err_code = 0;

  FILE *file;
  S32 i = 0;

  file = fopen(path, "wb");
  if (!file)
  {
    LogErrStr("failed to open file for writing!");
    goto err1;
  }

  fprintf(file, "#include <%s/mtf.h>\n#include <%s/mtf.c>\n", ts_path, ts_path);
  while (i < strbuffer->n)
  {
    putc(strbuffer->buffer[i], file);
    ++i;
  }

  fprintf(file,
      "int main() {\n"
      "Mtf_Test %s[]={\n", name);
  while (strnode)
  {
    fprintf(file, "    Mtf_T(%s),\n", strnode->str);
    err_code = 1;
    strnode = strnode->prev;
  }
  fprintf(file, "  };\n"
                "Mtf_RunMultipleTests(%s);\n}\n", name);

  fclose(file);

err1:

  return(err_code);
}

S32
main(S32 argc, char *argv[])
{
  S32 err_code;
  char *tests_path, *temp_path;
  StrBuffer strbuffer;
  StrNode *strnode;

  tests_path = argv[1];
  temp_path = argv[2];

  if (readfile(tests_path, &strbuffer) != 0)
  {
    LogErrStr("failed to read file!");
    err_code = 1;
    goto err1;
  }

  if (parse(&strbuffer, &strnode) != 0)
  {
    LogErrStr("failed to parse file!");
    err_code = 2;
    goto err2;
  }

  if (makefile(temp_path, "tests", ts_path, strnode, &strbuffer) != 0)
  { LogErrStr("failed create new temporary file!");
    err_code = 3;
    goto err3;
  }

err3:
  strnodes_die(strnode);
err2:
  free(strbuffer.buffer);
err1:

  return(err_code);
}












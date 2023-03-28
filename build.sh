SOURCE="src/main.c"
OUTPUT="build/c-preproc"

# includes and libs
INCS=""
LIBS="-lm"

# flags
CPPFLAGS="-D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_C_SOURCE=2 -DVERSION=\"${VERSION}\""
CFLAGS="-g -std=c99 -Wall -Wno-deprecated-declarations -Wno-unused-variable -Wno-unused-function -O0 -fsanitize=address ${INCS} ${CPPFLAGS}"
LDFLAGS=${LIBS}

# compiler and linker
CC="cc"

# building
${CC} $CFLAGS -o $OUTPUT $SOURCE $LDFLAGS 

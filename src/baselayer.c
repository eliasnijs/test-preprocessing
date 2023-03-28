///////////////////////////////////////////////////////////
//// NOTE(Elias): Symbolic Constant Functions

internal char * 
string_from_month(Month month)
{
  char *result = "(null)";
  switch (month) 
  {
    case (Month_Jan):
    {
      result = "janunary";
    } break;
    case (Month_Feb):
    {
      result = "february";
    } break;
    case (Month_Mar):
    {
      result = "march";
    } break;
    case (Month_Apr):
    {
      result = "april";
    } break;
    case (Month_May):
    {
      result = "may";
    } break;
    case (Month_Jun):
    {
      result = "juny";
    } break;
    case (Month_Jul):
    {
      result = "july";
    } break;
    case (Month_Aug):
    {
      result = "augustus";
    } break;
    case (Month_Sep):
    {
      result = "september";
    } break;
    case (Month_Oct):
    {
      result = "october";
    } break;
    case (Month_Nov):
    {
      result = "november";
    } break;
    case (Month_Dec):
    {
      result = "december";
    } break;
  }
  return(result);
}

internal char * 
string_from_day_of_week(DayOfWeek day_of_week)
{
  char * result = "(null)";
  switch (day_of_week)
  {
    case(DayOfWeek_Monday):
    {
      result = "monday";
    } break;
    case(DayOfWeek_Tuesday):
    {
      result = "tuesday";
    } break;
    case(DayOfWeek_Wednesday):
    {
      result = "wednesday";
    } break;
    case(DayOfWeek_Thursday):
    {
      result = "thursday";
    } break;
    case(DayOfWeek_Friday):
    {
      result = "friday";
    } break;
    case(DayOfWeek_Saturday):
    {
      result = "saturday";
    } break;
    case(DayOfWeek_Sunday):
    {
      result = "sunday";
    } break;
  }
  return(result);
}

///////////////////////////////////////////////////////////
//// NOTE(Elias): Float Constant Functions

internal F32 
inf_F32(void)
{
  union{ F32 f; U32 u; } r;
  r.u = 0x7f800000;
  return(r.f);
}
internal F32 
neg_inf_F32(void)
{
  union{ F32 f; U32 u; } r;
  r.u = 0xff800000;
  return(r.f);
}

internal F64 
inf_F64(void)
{
  union{ F64 f; U64 u; } r;
  r.u = 0x7ff00000ff800000;
  return(r.f);
}

internal F64 
neg_inf_F64(void)
{
  union{ F64 f; U64 u; } r;
  r.u = 0xfff00000ff800000;
  return(r.f);
}

///////////////////////////////////////////////////////////
//// NOTE(Elias): Math functions 

internal F32 
abs_F32(F32 x)
{
  union{ F32 f; U32 u; } r;
  r.f = x;
  r.u = r.u & 0x7fffffff;
  return(r.f);
}

internal F64 
abs_F64(F64 x)
{
  union{ F32 f; U32 u; } r;
  r.f = x;
  r.u = r.u & 0x7fffffffffffffff;
  return(r.f);
} 

internal F32 
srqt_F32(F32 x)
{
  return(sqrtf(x));
}

internal F32 
sin_F32(F32 x)
{
  return(sinf(x));
}

internal F32 
cos_F32(F32 x)
{
  return(cosf(x));
}

internal F32 
tan_F32(F32 x)
{
  return(tanf(x));
}

internal F32 
ln_F32(F32 x)
{
  return(logf(x));
}

internal F64 
srqt_F64(F64 x)
{
  return(sqrt(x));
}

internal F64 
sin_F64(F64 x)
{
  return(sin(x));
}

internal F64 
cos_F64(F64 x)
{
  return(cos(x));
}

internal F64 
tan_F64(F64 x)
{
  return(tan(x));
} 

internal F64 
ln_F64(F64 x)
{
  return(log(x));
} 

internal F32 
lerp(F32 a, F32 t, F32 b)
{
  F32 x = a + t*(b - a);
  return(x);
}

internal F32 
unlerp(F32 a, F32 x, F32 b)
{
  F32 t = 0.f;
  if (a != b)
  {
    t = (x - a) / (b - a);
  }
  return(t);
}

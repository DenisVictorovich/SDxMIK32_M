#ifndef  DIG_TYPES_H
#define  DIG_TYPES_H

typedef  signed __int8   i8;
typedef  signed __int16  i16;
typedef  signed __int32  i32;
typedef  signed __int64  i64;

typedef  unsigned __int8   ui8;
typedef  unsigned __int16  ui16;
typedef  unsigned __int32  ui32;
typedef  unsigned __int64  ui64;

struct DTime { ui8 sec,min,hour,date,mon,year; };

#endif /* DIG_TYPES_H */

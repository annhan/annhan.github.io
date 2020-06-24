---
layout: default
title: 
---

Example:
```
void cond_printf(const char *format, ...)
{    
    char loc_buf[64];
    char * temp = loc_buf;
    va_list arg;
    va_list copy;
    va_start(arg, format);
    va_copy(copy, arg);
    size_t len = vsnprintf(NULL, 0, format, arg);
    va_end(copy);
    if(len >= sizeof(loc_buf)){
        temp = new char[len+1];
        if(temp == NULL) {
            return;
        }
    }
    len = vsnprintf(temp, len+1, format, arg);
    pc->printf( temp);
    va_end(arg);
    if(len > 64){
        delete[] temp;
    }    
}

```

Ta có thể gọi như sau
```
cond_printf(" Mechanical Angle:  %f    Electrical Angle:  %f    Raw:  %d\n\r", spi.GetMechPosition(), spi.GetElecPosition(), spi.GetRawPosition());
```

-> Ta dùng macro này để gọp các biến vào một cách nhanh chóng.
```
int vsnprintf(
   char *buffer,
   size_t count,
   const char *format,
   va_list argptr
);
The vsnprintf function returns the number of characters written, not counting the terminating null character.
```
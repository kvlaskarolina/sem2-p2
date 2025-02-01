//Karolina Kulas
//ok
#include "bitwise_operations.h"
void Insert(char*l,int*z)
{
    
    if(*l!='\0') 
    {
        if(*l==' ') Insert((l+1),z);
        else
        {
        int liczba=0;
        if(*l=='1') liczba+=16;
        if(*(l+1)=='1') liczba+=8;
        if(*(l+2)=='1') liczba+=4;
        if(*(l+3)=='1') liczba+=2;
        if(*(l+4)=='1') liczba+=1;
        *z|=(1<<liczba);
        Insert((l+5),z);
        }
    }
}

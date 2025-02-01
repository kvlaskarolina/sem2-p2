//Karolina Kulas
#include "bitwise_operations.h"
int Cardinality(int z)
{
    if(z==-2147483648) return 1;
    if(z<0) return 32-Cardinality(~z);
    if(z==0) return 0;
    if(z==1) return 1;
    return (z%2)+Cardinality(z/2);
}
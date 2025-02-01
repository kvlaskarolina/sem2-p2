//Karolina Kulas
//dziala
#include "bitwise_operations.h"
bool Inclusion(int z1,int z2)
{
    return ((z1|z2)==z2);
}
bool Equality(int z1,int z2)
{
    return (Inclusion(z1,z2)&&Inclusion(z2,z1));
}
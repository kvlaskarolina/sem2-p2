//Karolina Kulas
#include "bitwise_operations.h"
bool GreatThen(int a,int b)
{
    int ac=Cardinality(a);
    int bc=Cardinality(b);
    if(a<0&&b>=0)
    {
        return ((ac>bc)||((ac==bc)));
    }
    if(a<0&&b<0)
    {
        return ((ac>bc)||((ac==bc)&&(a<b)));
    }
    if(a>=0&&b>=0)
    {
        return ((ac>bc)||((ac==bc)&&(a>b)));
    }
    if(a>=0&&b<0)
    {
        return ((ac>bc));
    }
}
bool GreatEqual(int a,int b)
{
    int ac=Cardinality(a);
    int bc=Cardinality(b);
    return (GreatThen(a,b)||Equality(a,b));
}
bool LessThen(int a,int b)
{
    int ac=Cardinality(a);
    int bc=Cardinality(b);
    return (!GreatEqual(a,b));
}
bool LessEqual(int a,int b)
{
    int ac=Cardinality(a);
    int bc=Cardinality(b);
    return (!GreatThen(a,b));
}

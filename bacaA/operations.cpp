//Karolina Kulas
//dziala
void Union(int z1,int z2,int*z)
{
    *z=(z1|z2);
}
void Intersection(int z1,int z2,int*z)
{
    *z=(z1&z2);
}
void Symmetric(int z1,int z2,int*z)
{
    *z=(z1^z2);
}
void Difference(int z1,int z2,int*z)
{
    *z=z1&(~z2);
}
void Complement(int z1,int*z)
{
    *z=~z1;
}
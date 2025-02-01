//Karolina Kulas
//dziala
bool Disjoint(int z1,int z2)
{
    return !(z1&z2);
}
bool Conjunctive(int z1,int z2)
{
    return (z1&z2);
}
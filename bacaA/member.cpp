//Karolina Kulas
//ok
bool Member(char* element, int z)
{
    if(*element==' ') return Member((element+1),z);
    if(*element=='\0') return 0;
        int liczba=0;
        if(*element=='1') liczba+=16;
        if(*(element+1)=='1') liczba+=8;
        if(*(element+2)=='1') liczba+=4;
        if(*(element+3)=='1') liczba+=2;
        if(*(element+4)=='1') liczba+=1;
        return (z&(1<<liczba));
    
}

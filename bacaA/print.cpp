// Karolina Kulas
//dziala an logike
void Print(int z, char *print)
{
    int licznik = 31, k = 0;
    if (z == 0)
    {
        *print = 'e';
        *(print + 1) = 'm';
        *(print + 2) = 'p';
        *(print + 3) = 't';
        *(print + 4) = 'y';
        *(print + 5) = '\0';
        return;
    }
    else
    {
        if (z & (1 << licznik))
        {
            *(print + k) = '1';
            *((print + k) + 1) = '1';
            *((print + k) + 2) = '1';
            *((print + k) + 3) = '1';
            *((print + k) + 4) = '1';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '1';
            *((print + k) + 1) = '1';
            *((print + k) + 2) = '1';
            *((print + k) + 3) = '1';
            *((print + k) + 4) = '0';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '1';
            *((print + k) + 1) = '1';
            *((print + k) + 2) = '1';
            *((print + k) + 3) = '0';
            *((print + k) + 4) = '1';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '1';
            *((print + k) + 1) = '1';
            *((print + k) + 2) = '1';
            *((print + k) + 3) = '0';
            *((print + k) + 4) = '0';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '1';
            *((print + k) + 1) = '1';
            *((print + k) + 2) = '0';
            *((print + k) + 3) = '1';
            *((print + k) + 4) = '1';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '1';
            *((print + k) + 1) = '1';
            *((print + k) + 2) = '0';
            *((print + k) + 3) = '1';
            *((print + k) + 4) = '0';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '1';
            *((print + k) + 1) = '1';
            *((print + k) + 2) = '0';
            *((print + k) + 3) = '0';
            *((print + k) + 4) = '1';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '1';
            *((print + k) + 1) = '1';
            *((print + k) + 2) = '0';
            *((print + k) + 3) = '0';
            *((print + k) + 4) = '0';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '1';
            *((print + k) + 1) = '0';
            *((print + k) + 2) = '1';
            *((print + k) + 3) = '1';
            *((print + k) + 4) = '1';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '1';
            *((print + k) + 1) = '0';
            *((print + k) + 2) = '1';
            *((print + k) + 3) = '1';
            *((print + k) + 4) = '0';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '1';
            *((print + k) + 1) = '0';
            *((print + k) + 2) = '1';
            *((print + k) + 3) = '0';
            *((print + k) + 4) = '1';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '1';
            *((print + k) + 1) = '0';
            *((print + k) + 2) = '1';
            *((print + k) + 3) = '0';
            *((print + k) + 4) = '0';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '1';
            *((print + k) + 1) = '0';
            *((print + k) + 2) = '0';
            *((print + k) + 3) = '1';
            *((print + k) + 4) = '1';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '1';
            *((print + k) + 1) = '0';
            *((print + k) + 2) = '0';
            *((print + k) + 3) = '1';
            *((print + k) + 4) = '0';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '1';
            *((print + k) + 1) = '0';
            *((print + k) + 2) = '0';
            *((print + k) + 3) = '0';
            *((print + k) + 4) = '1';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '1';
            *((print + k) + 1) = '0';
            *((print + k) + 2) = '0';
            *((print + k) + 3) = '0';
            *((print + k) + 4) = '0';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '0';
            *((print + k) + 1) = '1';
            *((print + k) + 2) = '1';
            *((print + k) + 3) = '1';
            *((print + k) + 4) = '1';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '0';
            *((print + k) + 1) = '1';
            *((print + k) + 2) = '1';
            *((print + k) + 3) = '1';
            *((print + k) + 4) = '0';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '0';
            *((print + k) + 1) = '1';
            *((print + k) + 2) = '1';
            *((print + k) + 3) = '0';
            *((print + k) + 4) = '1';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '0';
            *((print + k) + 1) = '1';
            *((print + k) + 2) = '1';
            *((print + k) + 3) = '0';
            *((print + k) + 4) = '0';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '0';
            *((print + k) + 1) = '1';
            *((print + k) + 2) = '0';
            *((print + k) + 3) = '1';
            *((print + k) + 4) = '1';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '0';
            *((print + k) + 1) = '1';
            *((print + k) + 2) = '0';
            *((print + k) + 3) = '1';
            *((print + k) + 4) = '0';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '0';
            *((print + k) + 1) = '1';
            *((print + k) + 2) = '0';
            *((print + k) + 3) = '0';
            *((print + k) + 4) = '1';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '0';
            *((print + k) + 1) = '1';
            *((print + k) + 2) = '0';
            *((print + k) + 3) = '0';
            *((print + k) + 4) = '0';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '0';
            *((print + k) + 1) = '0';
            *((print + k) + 2) = '1';
            *((print + k) + 3) = '1';
            *((print + k) + 4) = '1';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '0';
            *((print + k) + 1) = '0';
            *((print + k) + 2) = '1';
            *((print + k) + 3) = '1';
            *((print + k) + 4) = '0';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '0';
            *((print + k) + 1) = '0';
            *((print + k) + 2) = '1';
            *((print + k) + 3) = '0';
            *((print + k) + 4) = '1';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '0';
            *((print + k) + 1) = '0';
            *((print + k) + 2) = '1';
            *((print + k) + 3) = '0';
            *((print + k) + 4) = '0';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '0';
            *((print + k) + 1) = '0';
            *((print + k) + 2) = '0';
            *((print + k) + 3) = '1';
            *((print + k) + 4) = '1';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '0';
            *((print + k) + 1) = '0';
            *((print + k) + 2) = '0';
            *((print + k) + 3) = '1';
            *((print + k) + 4) = '0';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '0';
            *((print + k) + 1) = '0';
            *((print + k) + 2) = '0';
            *((print + k) + 3) = '0';
            *((print + k) + 4) = '1';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        licznik--;
        if (z & (1 << licznik))
        {
            *(print + k) = '0';
            *((print + k) + 1) = '0';
            *((print + k) + 2) = '0';
            *((print + k) + 3) = '0';
            *((print + k) + 4) = '0';
            *((print + k) + 5) = ' ';
            k += 6;
        }
        *(print + k - 1) = '\0';
    }
}
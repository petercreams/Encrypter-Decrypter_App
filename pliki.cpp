#include "menu.h"
#include "klucz.h"
#include "pliki.h"

#include <iostream>
#include <fstream>



using namespace std;

void wczytaj_zamien()
{
    char litera;

    ifstream plik ("tekst.txt");

    if(!plik.good()){
        cout<<"Blad otwarcia!\n";
        return;
    }
    while (!plik.eof())
    {
        plik>>litera;
        for(int i=0; i<46; i++)
        {
            if (litera == liczba) cout<<"a";
        }
    }

}



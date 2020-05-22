#include "menu.h"
#include "klucz.h"
#include "pliki.h"

#include <iostream>
#include <conio.h> //biblioteka obslugujaca getch()

using namespace std;

int wybor;

void wyswietl_menu();
void wyczysc(){
    system( "cls" );
}

void wybierz()
{
    cin>>wybor;

        while(wybor<1 || wybor>5)
    {
        cout<<"Wybierz opcje 1-5! Nacisnij dowolny przycisk, aby odswiezyc";
        getch();
        wyczysc();
        wyswietl_menu();
        cin>>wybor;
    }
        switch (wybor)
          {
          case 1:
            klucz_wybor("szyfrowanie");
            czyscplik("zaszyfrowane.txt");
            wczytaj_szyfruj();
            cout<<"Pomyslnie wykonano\n";
            cout<<"Wcisnij dowolny klawisz, aby powrocic do menu\n";
            getch();
            wyczysc();
            wyswietl_menu();
          break;
          case 2:
            cout<<"Wybierz, na podstawie jakiego klucza chcesz deszyfrowac plik 'wynik.txt'\n";
            klucz_wybor("deszyfracja");
            czyscplik("deszyfrowane.txt");
            wczytaj_deszyfruj();
            cout<<"Pomyslnie wykonano\n";
            getch();
            wyczysc();
            wyswietl_menu();
            break;
          case 3:
            wyczysc();
            zapisz_klucz();
            cout<<endl;
            cout<<"Zapisano nowy szyfr do pliku. Wcisinij dowolny przycisk, aby powrocic do menu";
            getch();
            wyczysc();
            wyswietl_menu();
          break;
          case 4:
            wyczysc();
            generuj();
            break;
          case 5:
            exit(0);
            break;

          }
}

void wyswietl_menu()
{
cout << "     ***** PROJEKT 15 *****    \n";
cout <<"     Copyright 2019 marzec        \n    Piotr Smietanka PW MCHTR     \n";
cout<<"________________________________\n";
cout<<endl;
cout<<"             MENU: \n";
cout<<"-----------------------------\n";
cout<<"1. Szyfruj plik\n";
cout<<"2. Deszyfruj plik\n";
cout<<"3. Definiuj klucz\n";
cout<<"4. Automatycznie generuj klucz\n";
cout<<"5. Wyjdz\n";
cout<<"-----------------------------\n";
cout<<"Wybor: ";
wybierz();
}







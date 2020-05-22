#include "menu.h"
#include "klucz.h"
#include "pliki.h"

#include <iostream>
#include <fstream>
#include <conio.h> //biblioteka obslugujaca getch()
#include <cstdlib> //losowanie
#include <time.h>

using namespace std;

struct Lkey{
    char we;
    char wy;

    Lkey *next;
};
struct key{
    char we;
    char wy;
};
struct dane
{
    char litera;
    double ile;

};

char litera;
const int N=52; //tyle jest LITER w alfabecie (duze + male) bylo 46 wczesniej
key tlitera[N];

void czylitera (char zn, bool &czylitera)
{
    if ( (zn<'a' || zn>'z') and (zn<'A' || zn>'Z') )
        czylitera=false;
}
void naMala (char &litera)
{
if(litera>='A' and litera <='Z')
    litera= char(litera+32); //zamiana duzej litery na mala
}
void naDuza (char litera)
{
    if(litera>='A' and litera <='Z')
        litera= char(litera-32); //zamiana malej litery na duza
}

void czyistnieje(Lkey *glowa, char litera, bool &istnieje)
{
while(glowa!=NULL)
{
    if(litera==glowa->wy)
    {

        istnieje =true;
        break;

    }
    glowa=glowa->next;
}
}

void wczytaj_klucz(string nazwa)
{
    int i=0;

    ifstream plik (nazwa.c_str());


    if(!plik.good()){
        cout<<"Blad otwarcia. Wcisnij dowolny przycisk\n";
        getch();
        wyczysc();
        wyswietl_menu();
    }
    while (!plik.eof())
    {
        plik>>tlitera[i].we;
        plik>>tlitera[i].wy;
        i++;
    }
    plik.close();
}

void klucz_wybor(string opcja)
{
    int wybor;
    system("cls");
    cout<<"Jakiego klucza chcesz uzyc?\n";
    cout<<"1. Domyslny (male litery)\n";
    cout<<"2. Losowany\n";
    cout<<"3. Zdefiniowany przez uzytkownika\n";
if(opcja=="deszyfracja") cout<<"4. Generowany na podstawie analizy fragmentu tekstu\n";

    cout<<"-----------------------------\n";
    cout<<"Wybor: ";
    cin>>wybor;
if(opcja=="szyfrowanie")    while(wybor<1 or wybor>3)
    {
        cout<<"Wybierz opcje 1-3\n";
        cin>>wybor;


    }
if(opcja=="deszyfracja")   while(wybor<1 or wybor>4)
    {
        cout<<"Wybierz opcje 1-4\n";
        cin>>wybor;

    }

    switch(wybor)
    {
    case 1:
        system("cls");
        wczytaj_klucz("klucz_male.txt");
//if(opcja=="szyfrowanie")        cout<<"Pomyslnie zaszyfrowano plik 'tekst.txt' do pliku 'zaszyfrowane.txt'\n";
//if(opcja=="deszyfrowacja")      cout<<"Pomyslnie zdeszyfrowano plik 'szyfrowane.txt' do pliku 'deszyfrowane.txt'\n";
        cout<<"Prosze poczekac. Trwa procesowanie polecenia.\n";

        break;
    case 2:
        system("cls");
        wczytaj_klucz("klucz_losowany.txt");
//if(opcja=="szyfrowanie")        cout<<"Pomyslnie zaszyfrowano plik 'tekst.txt' do pliku 'wynik.txt'\n";
//        cout<<"Wcisnij dowolny klawisz, aby powrocic do menu\n";
        cout<<"Prosze poczekac. Trwa procesowanie polecenia.\n";
        break;
    case 3:
        system("cls");
        wczytaj_klucz("klucz_wlasny.txt");
if(opcja=="szyfrowanie")        cout<<"Pomyslnie zaszyfrowano plik 'tekst.txt' do pliku 'wynik.txt'\n";
        cout<<"Prosze poczekac. Trwa procesowanie polecenia.\n";

        break;
    case 4:
        system("cls");
        char znak;
        ifstream wzor ("statystyki.txt");
        ifstream wzor_kolejnosc ("statystyki_kolejnosc.txt");
        cout<<"WYJASNIENIE DZIALANIA:\nGenerowanie klucza oparte jest o dane podawane przez PWN dot. procentowego wystepowania danej litery w j. polskim. Deszyfracja, w szczegolnosci przy krotkich tekstach, moze byc niedokladna, a nawet niemozliwa. Dodatkowo, ten algorytm nie uwzglednia wielkosci liter (dla duzej i malej litery jest ten sam odpowiednik).\nWcisnij dowolny klawisz, by przejsc dalej\n";
        if(!wzor.good())
        {
            cout<<"Problem z otworzeniem pliku 'statystyki.txt'\nWcisnij dowolny klawisz, aby powrocic do menu\n";
            getch();
            wyswietl_menu();
        }
        if(!wzor_kolejnosc.good())
        {
            cout<<"Problem z otworzeniem pliku 'statystyki_kolejnosc.txt'\nWcisnij dowolny klawisz, aby powrocic do menu\n";
            getch();
            wyswietl_menu();
        }
        cout<<endl;
        while(!wzor.eof())
        {
            char a;
            string b;
            wzor>>a;
            wzor>>b;
            cout<<a<<'\t';
            cout<<b<<"%";
            cout<<endl;

        }
        getch();
        const int N=26; //liczba malych liter
        dane wystepowanie[N]; //tablica wystepowania danych liter w zaszyfrowanym tekscie
        dane statystyka [N]; //tablica wystepowania danych liter w jezyku malejaco

        while(!wzor_kolejnosc.eof())
        {
            for(int i=0; i<N; i++)
            wzor_kolejnosc>>statystyka[i].litera;

        }

        for(int i=0; i<N; i++)
        {
            wystepowanie[i].litera= (char)'a'+i;
            wystepowanie[i].ile=0;
        }

//        system("cls");
        ifstream tekst ("zaszyfrowane.txt");
        if(!tekst.good())
        {
            cout<<"Problem z otwarciem!\n";
            getch();
            system("cls");
            wyswietl_menu();
        }
        while(!tekst.eof())
        {
            tekst>>znak; //wczytuj litera po literze
            //naMala(znak);
            for(int i=0; i<N; i++)
            {
                if (znak == wystepowanie[i].litera)  //sprawdzaj czy mamy taki znak w spisie
                {
                    wystepowanie[i].ile++; //jesli tak to zwieksz jego ilosc
                    break; //wczytaj kolejny znak

                }
            }
        }

cout<<endl;
        dane temp;
       for(int i=N-1; i>0; i--) //sortowanie babelkowe
            for(int j=0; j<i; j++)
            {
                if(wystepowanie[j].ile<wystepowanie[j+1].ile)
                {
                    temp.litera=wystepowanie[j].litera;
                    temp.ile=wystepowanie[j].ile;
                    wystepowanie[j].litera=wystepowanie[j+1].litera;
                    wystepowanie[j].ile=wystepowanie[j+1].ile;
                    wystepowanie[j+1].litera=temp.litera;
                    wystepowanie[j+1].ile=temp.ile;



            } }
        for(int i=0; i<N; i++)
        {
            cout<<wystepowanie[i].litera<<'\t';
            cout<<wystepowanie[i].ile;
            cout<<endl;
        }
        ofstream klucz ("klucz_statystyczny.txt");
        for(int i=0; i<N; i++)
        {
           klucz<<statystyka[i].litera<<'\t';
           klucz<< wystepowanie[i].litera;
           klucz<<endl;
        }

        wczytaj_klucz("klucz_statystyczny.txt");
        czyscplik("deszyfrowane.txt");
        wczytaj_deszyfruj_male();
        cout<<"Zakonczono generowanie klucza i odszyfrowanie. Nacisnij dowolny klawisz, aby powrocic do menu.\n";
        getch();




        wzor.close();
        wzor_kolejnosc.close();
        klucz.close();
              break;
    }
}


void zapisz_klucz()
{
    Lkey *temp, *glowa, *szyfr, *ogon;
    bool istnieje, Blitera;
    glowa=NULL;
    szyfr=NULL;
    glowa=new Lkey;



    for (int i='a'; i<='z'; i++)
    {   Blitera=true;
        istnieje=false;
        ogon=szyfr;
        szyfr = new Lkey;
        cout<<(char)i<<": ";
        cin>>litera; //ma byc litera!
        czylitera(litera, Blitera);
        while(Blitera==false)
        {
            Blitera=true;
            cout<<"Podana wartosc musi byc litera!\n";
            cout<<"Podaj litere\n";
            cout<<(char)i<<": ";
            cin>>litera;
            czylitera(litera, Blitera);


        }
        if(i>'a')
        {
            czyistnieje(glowa, litera, istnieje);
        while(istnieje==true)
        {
            istnieje=false;
            cout<<"Podana litera juz zostala uzyta. Sprobuj uzyc innej.\n";
            cout<<(char)i<<": ";
            cin>>litera;
            czyistnieje(glowa, litera, istnieje);



        }
        }
        cout<<"Wczytano\n";
        cout<<endl;

        szyfr->we=(char)i;
        szyfr->wy=litera;
        szyfr->next=NULL;
        if(ogon==NULL){
            glowa=szyfr;
        }
        else{
            ogon->next=szyfr;
        }

    }

    for (int i='A'; i<='Z'; i++)
    {
        Blitera=true;
        istnieje=false;
        ogon=szyfr;
        szyfr = new Lkey;
        cout<<(char)i<<": ";
        cin>>litera;
        czylitera(litera, Blitera);
        while(Blitera==false)
        {
            Blitera=true;
            cout<<"Podana wartosc musi byc litera!\n";
            cout<<"Podaj litere\n";
            cout<<(char)i<<": ";
            cin>>litera;
            czylitera(litera, Blitera);


        }
        if(i>'A')
        {
            czyistnieje(glowa, litera, istnieje);
        while(istnieje==true)
        {
            istnieje=false;
            cout<<"Podana litera juz zostala uzyta. Sprobuj uzyc innej.\n";
            cout<<(char)i<<": ";
            cin>>litera;
            czyistnieje(glowa, litera, istnieje);



        }
        }
        cout<<"Wczytano\n";
        cout<<endl;

        szyfr->we=(char)i;
        szyfr->wy=litera;
        szyfr->next=NULL;
        if(ogon==NULL){
            glowa=szyfr;
        }
        else{
            ogon->next=szyfr;
        }

    }

    ofstream plik ("klucz_wlasny.txt");
    cout<<"Utworzono plik\n";

    szyfr=glowa; //ustawiam sie na poczatku listy, zeby wypisac elementy listy

            while(szyfr!=NULL)
    {
                plik<<szyfr->we<<'\t'<<szyfr->wy<<endl;
                szyfr=szyfr->next;

    }
            cout<<"Zapisano do pliku 'klucz_wlasny.txt' \n";
            cout<<"Wcisnij dowolny przycisk, aby powrocic do menu";
            getch();
            plik.close();


            wyczysc();
            wyswietl_menu();
}

void czyscplik(string nazwa)
{
    ofstream plik (nazwa.c_str());
    plik.clear();
    plik.close();
}

void zapisz(char znak, string gdzie)
{
    ofstream plik (gdzie.c_str(), ios::app);

    plik<<znak;
    plik.close();
}

void wczytaj_szyfruj()
{


    ifstream plik ("tekst.txt");

    if(!plik.good()){
        cout<<"Blad otwarcia!\n";
        return;
    }
    while (!plik.eof())
    {
        plik>>litera;
        for(int i=0; i<52; i++) //bylo 46
        {

            if(litera == '+') {
                zapisz('+', "zaszyfrowane.txt");
                break;
            }

            if (litera == tlitera[i].we)
            {   litera = tlitera[i].wy;
                zapisz(litera, "zaszyfrowane.txt");
                break;
            }
            if(i == 51) {
                zapisz(litera, "zaszyfrowane.txt"); //jezeli nie znajdziesz odpowiednika w kluczu - przepisz znak
                break;
        }
        }
    }
plik.close();
}

void wczytaj_deszyfruj()
{


    ifstream plik ("zaszyfrowane.txt");

    if(!plik.good()){
        cout<<"Blad otwarcia!\n";
        return;
    }
    while (!plik.eof())
    {
        plik>>litera;
        for(int i=0; i<52; i++) //bylo 46
        {

            if(litera == '+') {
                zapisz(' ', "deszyfrowane.txt");
                break;
            }
            if (litera == tlitera[i].wy)
            {
                litera = tlitera[i].we;
                zapisz(litera, "deszyfrowane.txt");
                break;
            }
            if(i == 51) {
                zapisz(litera, "deszyfrowane.txt"); //jezeli nie znajdziesz odpowiednika w kluczu - przepisz znak
                break;
        }
        }
    }
plik.close();
}

void wczytaj_deszyfruj_male()
{


    ifstream plik ("zaszyfrowane.txt");

    if(!plik.good()){
        cout<<"Blad otwarcia!\n";
        return;
    }
    while (!plik.eof())
    {
        plik>>litera;
        naMala(litera);
        for(int i=0; i<26; i++)
        {

            if(litera == '+') {
                zapisz(' ', "deszyfrowane.txt");
                break;
            }
            if (litera == tlitera[i].wy)
            {
                litera = tlitera[i].we;
                zapisz(litera, "deszyfrowane.txt");
                break;
            }
            if(i == 25) {
                zapisz(litera, "deszyfrowane.txt"); //jezeli nie znajdziesz odpowiednika w kluczu - przepisz znak
                break;
        }
        }
    }
plik.close();
}

void generuj()
{
    Lkey *temp, *glowa, *szyfr, *ogon;
    srand(time(0));
    bool istnieje;
    glowa=NULL;
    szyfr=NULL;
    glowa=new Lkey;



    for (int i='a'; i<='z'; i++)
    {
        istnieje=false;
        ogon=szyfr;
        szyfr = new Lkey;

        litera = rand()%('z'-'a' + 1) + 'a';
        if(i>'a')
        {
            czyistnieje(glowa, litera, istnieje);
        while(istnieje==true)
        {
            istnieje=false;
            litera = rand()%('z'-'a' + 1) + 'a';
            czyistnieje(glowa, litera, istnieje);



        }
        }

        szyfr->we=(char)i;
        szyfr->wy=litera;
        szyfr->next=NULL;
        if(ogon==NULL){
            glowa=szyfr;
        }
        else{
            ogon->next=szyfr;
        }

    }
    for (int i='A'; i<='Z'; i++)
    {
        istnieje=false;
        ogon=szyfr;
        szyfr = new Lkey;

        litera = rand()%('Z'-'A' + 1) + 'A';
        if(i>'A')
        {
            czyistnieje(glowa, litera, istnieje);
        while(istnieje==true)
        {
            istnieje=false;
            litera = rand()%('Z'-'A' + 1) + 'A';
            czyistnieje(glowa, litera, istnieje);



        }
        }

        szyfr->we=(char)i;
        szyfr->wy=litera;
        szyfr->next=NULL;
        if(ogon==NULL){
            glowa=szyfr;
        }
        else{
            ogon->next=szyfr;
        }

    }
    ofstream plik ("klucz_losowany.txt");
    cout<<"Utworzono plik\n";

    szyfr=glowa; //ustawiam sie na poczatku listy, zeby wypisac elementy listy

            while(szyfr!=NULL)
    {
                plik<<szyfr->we<<'\t'<<szyfr->wy<<endl;
                szyfr=szyfr->next;

    }
            cout<<"Zapisano do pliku 'klucz_losowany.txt' \n";
            cout<<"Wcisnij dowolny przycisk, aby powrocic do menu";
            getch();
            plik.close();


            wyczysc();
            wyswietl_menu();
}



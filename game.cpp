//2017-12-19; Code::Blocks 16.01; GNU GCC Compiler
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <ctime>
using namespace std;

void rysuj(string plansza[8][8]);
void pionki(string plansza[8][8]);
void ruchGracz (string plansza[8][8], bool gracz);
void ruchAI (string plansza[8][8], bool gracz);
void theEnd(string plansza[8][8], bool koniec);

int main()
{
    srand(time(NULL));
    string plansza[8][8];
    bool koniec=false, gracz=true;
    pionki(plansza);
    while (koniec==false)
    {
        system("cls");
        rysuj(plansza);
        gracz=true;
        ruchGracz(plansza,gracz);
        theEnd(plansza,koniec);
        gracz=false;
        ruchAI(plansza,gracz);
        theEnd(plansza,koniec);
        cout << endl;
    }

    return 0;
}

void theEnd (string plansza[8][8], bool koniec)
{
    bool koniecO=true, koniecX=true;
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            if (plansza[i][j][0]=='o')
            {
                koniecO=false;
                break;
            }
        }
    }
    for (int i=0; i<8; i++)
    {
        for (int j=0; j<8; j++)
        {
            if (plansza[i][j][0]=='x')
            {
                koniecX=false;
                break;
            }
        }
    }
    if (koniecO==true)
    {
        system("cls");
        rysuj(plansza);
        cout << endl << "Brawo, wygrales gre.";
        koniec=true;
    }
    if (koniecX==true)
    {
        system("cls");
        rysuj(plansza);
        cout << endl << "Niestety, przegrales gre.";
        koniec=true;
    }
}

void ruchGracz (string plansza[8][8], bool gracz)
{
    while (gracz)
    {
        int y, x, skok=1;
        char xchar, ychar, z; //ychar zeby przez program sie nie zapetlal przy wpisaniu znaku do inta

        cout << endl <<"Aby wybrac pionek, wpisz wspolrzedne (cyfra): ";

        cin >> ychar;
        y = abs(ychar-48-8);
        if (y<0||y>7)
        {
            cout << endl << "Zly klawisz. Sprobuj ponownie";
            continue;
        }

        cout << endl << "Aby wybrac pionek, wpisz wspolrzedne (litera): ";

        cin >> xchar;
        xchar = tolower(xchar); // zamiana wszystkich liter na male zeby nie nakladac ograniczen na uzytkownika
        if (xchar<'a'||xchar>'h')
        {
            cout << endl << "Zly klawisz. Sprobuj ponownie";
            continue;
        }
        x=xchar-97; // zamiana char na int

        if (plansza[y][x]=="---"||plansza[y][x]=="  ")
        {
            cout << endl << "W tym miejscu nie ma pionka. Sprobuj ponownie";
            continue;
        }

        if(plansza[y][x][0]=='o')
        {
            cout << endl << "To nie jest twoj pionek. Sprobuj ponownie";
            continue;
        }

        cout << endl << "Wybierz kierunek (WSAD): ";
        cin >> z;
        tolower(z);

        if (plansza[y][x][1]-48>1)
        {
            cout << "O ile chcesz przeskoczyc? (1-" << plansza[y][x][1]-48 <<"):";
            cin >> skok;

            if (skok>plansza[y][x][1]-48||skok<1)
            {
                cout << "Niepoprawna dlugosc skoku. Sprobuj ponownie";
                continue;
            }
        }

        if (z=='w')
        {
            bool bylo=false, bylodwa=false;
            int pomoc=0;
            for (int i=1;i<=skok;i++) //sprawdzanie czy gracz nie chce przeskoczyc wiecej niz pionek
            {
                if (bylo) if (plansza[y-i][x]!="  ") bylodwa=true;
                if (bylodwa) break;
                if (plansza[y-i][x]!="  ")
                {
                    bylo=true;
                    pomoc=i;
                }
            }
            if (bylodwa)
            {
                cout << endl << "Nie mozesz przeskakiwac wiecej niz jednego pionka naraz. Sprobuj ponownie";
                continue;
            }
            if (y==0||plansza[y-skok][x]=="---")
            {
                cout << endl << "Niedozwolony ruch. Sprobuj ponownie";
                continue;
            }
            else if (plansza[y-skok][x][0]=='x'||plansza[y-skok][x][0]=='o') // sprawdza miejsce docelowe
            {
                if (plansza[y-skok-1][x][0]=='x'||plansza[y-skok-1][x][0]=='o'||plansza[y-skok-1][x]=="---"||y==skok) // sprawdza powyzej docelowego
                {
                    cout << endl << "Niedozwolony ruch. Sprobuj ponownie";
                    continue;
                }
                else if (plansza[y-pomoc][x][0]=='x')
                {
                    cout << endl << "Nie mozesz przeskakiwac przez swoje piony. Sprobuj ponownie";
                    continue;
                }
                else // na docelowym jest pionek
                {
                    swap(plansza[y][x],plansza[y-skok-1][x]);
                    if (bylo)
                    {
                        plansza[y-pomoc][x]="  ";
                        plansza[y-skok-1][x][1]=plansza[y-skok-1][x][1]+1;
                    }
                    if (bylo&&skok!=(plansza[y-skok-1][x][1]-48-1) || !bylo&&skok!=(plansza[y-skok-1][x][1]-48)) // UWAGA, DODATKOWE -1 BO POZIOM NOWEJ WIEZY JEST O JEDEN WIEKSZY
                    {
                         cout << endl << endl << skok << "   " << plansza[y-skok-1][x][1]-48-1;
                         plansza[y][x]="o1";
                         plansza[y-skok-1][x][1]=plansza[y-skok-1][x][1]-1;
                    }
                    gracz=false;
                }
            }
            else // na docelowym nic nie ma
            {
                swap(plansza[y][x],plansza[y-skok][x]);
                if (bylo)
                {
                    plansza[y-pomoc][x]="  ";
                    plansza[y-skok][x][1]=plansza[y-skok][x][1]+1;
                }
                if ((bylo&&(skok!=(plansza[y-skok][x][1]-48-1))) || (!bylo&&(skok!=(plansza[y-skok][x][1]-48)))) // UWAGA, DODATKOWE -1 BO POZIOM NOWEJ WIEZY JEST O JEDEN WIEKSZY
                {
                     plansza[y][x]="o1";
                     plansza[y-skok][x][1]=plansza[y-skok][x][1]-1;
                }
                gracz=false;
            }

        }

        else if (z=='s')
        {
            bool bylo=false, bylodwa=false;
            int pomoc=0;
            for (int i=1;i<=skok;i++) //sprawdzanie czy gracz nie chce przeskoczyc wiecej niz pionek
            {
                if (bylo) if (plansza[y+i][x]!="  ") bylodwa=true;
                if (bylodwa) break;
                if (plansza[y+i][x]!="  ")
                {
                    bylo=true;
                    pomoc=i;
                }
            }
            if (bylodwa)
            {
                cout << endl << "Nie mozesz przeskakiwac wiecej niz jednego pionka naraz. Sprobuj ponownie";
                continue;
            }
            if (y==7||plansza[y+skok][x]=="---")
            {
                cout << endl << "Niedozwolony ruch. Sprobuj ponownie";
                continue;
            }
            else if (plansza[y+skok][x][0]=='x'||plansza[y+skok][x][0]=='o')
            {
                if (plansza[y+skok+1][x][0]=='x'||plansza[y+skok+1][x][0]=='o'||plansza[y+skok+1][x]=="---"||y==7-skok)
                {
                    cout << endl << "Niedozwolony ruch. Sprobuj ponownie";
                    continue;
                }
                else if (plansza[y+pomoc][x][0]=='x')
                {
                    cout << endl << "Nie mozesz przeskakiwac przez swoje piony. Sprobuj ponownie";
                    continue;
                }
                else // na docelowym jest pionek
                {
                    swap(plansza[y][x],plansza[y+skok+1][x]);
                    if (bylo)
                    {
                        plansza[y+pomoc][x]="  ";
                        plansza[y+skok+1][x][1]=plansza[y+skok+1][x][1]+1;
                    }
                    if ((bylo&&skok!=(plansza[y+skok+1][x][1]-48-1)) || (!bylo&&skok!=(plansza[y+skok+1][x][1]-48))) // UWAGA, DODATKOWE -1 BO POZIOM NOWEJ WIEZY JEST O JEDEN WIEKSZY
                    {
                         plansza[y][x]="o1";
                         plansza[y+skok+1][x][1]=plansza[y+skok+1][x][1]-1;
                    }
                    gracz=false;
                }
            }
            else // na docelowym nic nie ma
            {
                swap(plansza[y][x],plansza[y+skok][x]);
                if (bylo)
                {
                    plansza[y+pomoc][x]="  ";
                    plansza[y+skok][x][1]=plansza[y+skok][x][1]+1;
                }
                if ((bylo&&skok!=(plansza[y+skok][x][1]-48-1)) || (!bylo&&skok!=(plansza[y+skok][x][1]-48))) // UWAGA, DODATKOWE -1 BO POZIOM NOWEJ WIEZY JEST O JEDEN WIEKSZY
                {
                     plansza[y][x]="o1";
                     plansza[y+skok][x][1]=plansza[y+skok][x][1]-1;
                }
                gracz=false;
            }

        }

        else if (z=='a')
        {
            bool bylo=false, bylodwa=false;
            int pomoc=0;
            for (int i=1;i<=skok;i++) //sprawdzanie czy gracz nie chce przeskoczyc wiecej niz pionek
            {
                if (bylo) if (plansza[y][x-i]!="  ") bylodwa=true;
                if (bylodwa) break;
                if (plansza[y][x-i]!="  ")
                {
                    bylo=true;
                    pomoc=i;
                }
            }
            if (x==0||plansza[y][x-skok]=="---")
            {
                cout << endl << "Niedozwolony ruch. Sprobuj ponownie";
                continue;
            }
            else if (plansza[y][x-skok][0]=='x'||plansza[y][x-skok][0]=='o')
            {
                if (plansza[y][x-skok-1][0]=='x'||plansza[y][x-skok-1][0]=='o'||plansza[y][x-skok-1]=="---"||x==skok)
                {
                    cout << endl << "Niedozwolony ruch. Sprobuj ponownie";
                    continue;
                }
                else if (plansza[y][x-skok][0]=='x')
                {
                    cout << endl << "Nie mozesz przeskakiwac przez swoje piony. Sprobuj ponownie";
                    continue;
                }
                else // na docelowym jest pionek
                {
                    swap(plansza[y][x],plansza[y][x-skok-1]);
                    if (bylo)
                    {
                        plansza[y][x-pomoc]="  ";
                        plansza[y][x-skok-1][1]=plansza[y][x-skok-1][1]+1;
                    }
                    if ((bylo&&skok!=(plansza[y][x-skok-1][1]-48-1)) || (!bylo&&skok!=(plansza[y][x-skok-1][1]-48))) // UWAGA, DODATKOWE -1 BO POZIOM NOWEJ WIEZY JEST O JEDEN WIEKSZY
                    {
                         plansza[y][x]="o1";
                         plansza[y][x-skok-1][1]=plansza[y][x-skok-1][1]-1;
                    }
                    gracz=false;
                }
            }
            else // na docelowym pusto
            {
                swap(plansza[y][x],plansza[y][x-skok]);
                if (bylo)
                {
                    plansza[y][x-pomoc]="  ";
                    plansza[y][x-skok][1]=plansza[y][x-skok][1]+1;
                }
                if ((bylo&&skok!=(plansza[y][x-skok][1]-48-1)) || (!bylo&&skok!=(plansza[y][x-skok][1]-48))) // UWAGA, DODATKOWE -1 BO POZIOM NOWEJ WIEZY JEST O JEDEN WIEKSZY
                {
                     plansza[y][x]="o1";
                     plansza[y][x-skok][1]=plansza[y][x-skok][1]-1;
                }
                gracz=false;
            }

        }

        else if (z=='d')
        {
            bool bylo=false, bylodwa=false;
            int pomoc=0;
            for (int i=1;i<=skok;i++) //sprawdzanie czy gracz nie chce przeskoczyc wiecej niz pionek
            {
                if (bylo) if (plansza[y][x+i]!="  ") bylodwa=true;
                if (bylodwa) break;
                if (plansza[y][x+i]!="  ")
                {
                    bylo=true;
                    pomoc=i;
                }
            }
            if (bylodwa)
            {
                cout << endl << "Nie mozesz przeskakiwac wiecej niz jednego pionka naraz. Sprobuj ponownie";
                continue;
            }
            if (x==7||plansza[y][x+skok]=="---")
            {
                cout << endl << "Niedozwolony ruch. Sprobuj ponownie";
                continue;
            }
            else if (plansza[y][x+skok][0]=='x'||plansza[y][x+skok][0]=='o')
            {
                if (plansza[y][x+skok+1][0]=='x'||plansza[y][x+skok+1][0]=='o'||plansza[y][x+skok+1]=="---"||x==7-skok)
                {
                    cout << endl << "Niedozwolony ruch. Sprobuj ponownie";
                    continue;
                }
                else if (plansza[y][x+skok][0]=='x')
                {
                    cout << endl << "Nie mozesz przeskakiwac przez swoje piony. Sprobuj ponownie";
                    continue;
                }
                else // na docelowym jest pionek
                {
                    swap(plansza[y][x],plansza[y][x+skok+1]);
                    if (bylo)
                    {
                        plansza[y][x+pomoc]="  ";
                        plansza[y][x+skok+1][1]=plansza[y][x+skok+1][1]+1;
                    }
                    if ((bylo&&skok!=(plansza[y][x+skok+1][1]-48-1)) || (!bylo&&skok!=(plansza[y][x+skok+1][1]-48))) // UWAGA, DODATKOWE -1 BO POZIOM NOWEJ WIEZY JEST O JEDEN WIEKSZY
                    {
                         plansza[y][x]="o1";
                         plansza[y][x+skok+1][1]=plansza[y][x+skok+1][1]-1;
                    }
                    gracz=false;
                }
            }
            else // na docelowym nic nie ma
            {
                swap(plansza[y][x],plansza[y][x+skok]);
                if (bylo)
                {
                    plansza[y][x+pomoc]="  ";
                    plansza[y][x+skok][1]=plansza[y][x+skok][1]+1;
                }
                if ((bylo&&skok!=(plansza[y][x+skok][1]-48-1) || !bylo&&skok!=(plansza[y][x+skok][1]-48))) // UWAGA, DODATKOWE -1 BO POZIOM NOWEJ WIEZY JEST O JEDEN WIEKSZY
                {
                     plansza[y][x]="o1";
                     plansza[y][x+skok][1]=plansza[y][x+skok][1]-1;
                }
                gracz=false;
            }

        }
        else
        {
            cout << endl << "Zly klawisz. Sprobuj ponownie";
            continue;
        }
    }
}

void ruchAI(string plansza[8][8], bool gracz)
{
    int y, x;
    char z, wsad[4];
    bool dobrze=true;
    wsad[0]='w';
    wsad[1]='s';
    wsad[2]='a';
    wsad[3]='d';
    while (!gracz)
    {
        y=rand()%8;
        x=rand()%8;
        if (plansza[y][x][0]!='o') continue;
        z=wsad[rand()%4];
        int skok;
        skok=rand()%(plansza[y][x][1]-48)+1;
        if (z=='w')
        {
            bool bylo=false, bylodwa=false;
            int pomoc=0;
            for (int i=1;i<=skok;i++)
            {
                if (bylo) if (plansza[y-i][x]!="  ") bylodwa=true;
                if (bylodwa) break;
                if (plansza[y-i][x]!="  ")
                {
                    bylo=true;
                    pomoc=i;
                }
            }
            if (bylodwa)
            {
                continue;
            }
            if (y==0||plansza[y-skok][x]=="---")
            {
                continue;
            }
            else if (plansza[y-skok][x][0]=='x'||plansza[y-skok][x][0]=='o') // sprawdza miejsce docelowe
            {
                if (plansza[y-skok-1][x][0]=='x'||plansza[y-skok-1][x][0]=='o'||plansza[y-skok-1][x]=="---"||y==skok) // sprawdza powyzej docelowego
                {
                    continue;
                }
                else if (plansza[y-pomoc][x][0]=='o')
                {
                    continue;
                }
                else // na docelowym jest pionek
                {
                    swap(plansza[y][x],plansza[y-skok-1][x]);
                    if (bylo)
                    {
                        plansza[y-pomoc][x]="  ";
                        plansza[y-skok-1][x][1]=plansza[y-skok-1][x][1]+1;
                    }
                    if ((bylo&&skok!=(plansza[y-skok-1][x][1]-48-1)) || (!bylo&&skok!=(plansza[y-skok-1][x][1]-48))) // UWAGA, DODATKOWE -1 BO POZIOM NOWEJ WIEZY JEST O JEDEN WIEKSZY
                    {
                         plansza[y][x]="x1";
                         plansza[y-skok-1][x][1]=plansza[y-skok-1][x][1]-1;
                    }
                    gracz=true;
                }
            }
            else // na docelowym nic nie ma
            {
                swap(plansza[y][x],plansza[y-skok][x]);
                if (bylo)
                {
                    plansza[y-pomoc][x]="  ";
                    plansza[y-skok][x][1]=plansza[y-skok][x][1]+1;
                }
                if ((bylo&&skok!=(plansza[y-skok][x][1]-48-1)) || (!bylo&&skok!=(plansza[y-skok][x][1]-48))) // UWAGA, DODATKOWE -1 BO POZIOM NOWEJ WIEZY JEST O JEDEN WIEKSZY
                {
                     plansza[y][x]="x1";
                     plansza[y-skok][x][1]=plansza[y-skok][x][1]-1;
                }
                gracz=true;
            }

        }
        else if (z=='s')
        {
            bool bylo=false, bylodwa=false;
            int pomoc=0;
            for (int i=1;i<=skok;i++)
            {
                if (bylo) if (plansza[y+i][x]!="  ") bylodwa=true;
                if (bylodwa) break;
                if (plansza[y+i][x]!="  ")
                {
                    bylo=true;
                    pomoc=i;
                }
            }
            if (bylodwa)
            {
                continue;
            }
            if (y==7||plansza[y+skok][x]=="---")
            {
                continue;
            }
            else if (plansza[y+skok][x][0]=='x'||plansza[y+skok][x][0]=='o')
            {
                if (plansza[y+skok+1][x][0]=='x'||plansza[y+skok+1][x][0]=='o'||plansza[y+skok+1][x]=="---"||y==7-skok)
                {
                    continue;
                }
                else if (plansza[y+pomoc][x][0]=='o')
                {
                    continue;
                }
                else // na docelowym jest pionek
                {
                    swap(plansza[y][x],plansza[y+skok+1][x]);
                    if (bylo)
                    {
                        plansza[y+pomoc][x]="  ";
                        plansza[y+skok+1][x][1]=plansza[y+skok+1][x][1]+1;
                    }
                    if ((bylo&&skok!=(plansza[y+skok+1][x][1]-48-1)) || (!bylo&&skok!=(plansza[y+skok+1][x][1]-48))) // UWAGA, DODATKOWE -1 BO POZIOM NOWEJ WIEZY JEST O JEDEN WIEKSZY
                    {
                         plansza[y][x]="x1";
                         plansza[y+skok+1][x][1]=plansza[y+skok+1][x][1]-1;
                    }
                    gracz=true;
                }
            }
            else // na docelowym nic nie ma
            {
                swap(plansza[y][x],plansza[y+skok][x]);
                if (bylo)
                {
                    plansza[y+pomoc][x]="  ";
                    plansza[y+skok][x][1]=plansza[y+skok][x][1]+1;
                }
                if ((bylo&&skok!=(plansza[y+skok][x][1]-48-1)) || (!bylo&&skok!=(plansza[y+skok][x][1]-48))) // UWAGA, DODATKOWE -1 BO POZIOM NOWEJ WIEZY JEST O JEDEN WIEKSZY
                {
                     plansza[y][x]="x1";
                     plansza[y+skok][x][1]=plansza[y+skok][x][1]-1;
                }
                gracz=true;
            }

        }
        else if (z=='a')
        {
            bool bylo=false, bylodwa=false;
            int pomoc=0;
            for (int i=1;i<=skok;i++) //sprawdzanie czy gracz nie chce przeskoczyc wiecej niz pionek
            {
                if (bylo) if (plansza[y][x-i]!="  ") bylodwa=true;
                if (bylodwa) break;
                if (plansza[y][x-i]!="  ")
                {
                    bylo=true;
                    pomoc=i;
                }
            }
            if (x==0||plansza[y][x-skok]=="---")
            {
                continue;
            }
            else if (plansza[y][x-skok][0]=='x'||plansza[y][x-skok][0]=='o')
            {
                if (plansza[y][x-skok-1][0]=='x'||plansza[y][x-skok-1][0]=='o'||plansza[y][x-skok-1]=="---"||x==skok)
                {
                    continue;
                }
                else if (plansza[y][x-skok][0]=='o')
                {
                    continue;
                }
                else // na docelowym jest pionek
                {
                    swap(plansza[y][x],plansza[y][x-skok-1]);
                    if (bylo)
                    {
                        plansza[y][x-pomoc]="  ";
                        plansza[y][x-skok-1][1]=plansza[y][x-skok-1][1]+1;
                    }
                    if ((bylo&&skok!=(plansza[y][x-skok-1][1]-48-1)) || (!bylo&&skok!=(plansza[y][x-skok-1][1]-48))) // UWAGA, DODATKOWE -1 BO POZIOM NOWEJ WIEZY JEST O JEDEN WIEKSZY
                    {
                         plansza[y][x]="x1";
                         plansza[y][x-skok-1][1]=plansza[y][x-skok-1][1]-1;
                    }
                    gracz=true;
                }
            }
            else // na docelowym pusto
            {
                swap(plansza[y][x],plansza[y][x-skok]);
                if (bylo)
                {
                    plansza[y][x-pomoc]="  ";
                    plansza[y][x-skok][1]=plansza[y][x-skok][1]+1;
                }
                if ((bylo&&skok!=(plansza[y][x-skok][1]-48-1)) || (!bylo&&skok!=(plansza[y][x-skok][1]-48))) // UWAGA, DODATKOWE -1 BO POZIOM NOWEJ WIEZY JEST O JEDEN WIEKSZY
                {
                     plansza[y][x]="x1";
                     plansza[y][x-skok][1]=plansza[y][x-skok][1]-1;
                }
                gracz=true;
            }

        }
        else if (z=='d')
        {
            bool bylo=false, bylodwa=false;
            int pomoc=0;
            for (int i=1;i<=skok;i++) //sprawdzanie czy gracz nie chce przeskoczyc wiecej niz pionek
            {
                if (bylo) if (plansza[y][x+i]!="  ") bylodwa=true;
                if (bylodwa) break;
                if (plansza[y][x+i]!="  ")
                {
                    bylo=true;
                    pomoc=i;
                }
            }
            if (bylodwa)
            {
                continue;
            }
            if (x==7||plansza[y][x+skok]=="---")
            {
                continue;
            }
            else if (plansza[y][x+skok][0]=='x'||plansza[y][x+skok][0]=='o')
            {
                if (plansza[y][x+skok+1][0]=='x'||plansza[y][x+skok+1][0]=='o'||plansza[y][x+skok+1]=="---"||x==7-skok)
                {
                    continue;
                }
                else if (plansza[y][x+skok][0]=='o')
                {
                    continue;
                }
                else // na docelowym jest pionek
                {
                    swap(plansza[y][x],plansza[y][x+skok+1]);
                    if (bylo)
                    {
                        plansza[y][x+pomoc]="  ";
                        plansza[y][x+skok+1][1]=plansza[y][x+skok+1][1]+1;
                    }
                    if ((bylo&&skok!=(plansza[y][x+skok+1][1]-48-1)) || (!bylo&&skok!=(plansza[y][x+skok+1][1]-48))) // UWAGA, DODATKOWE -1 BO POZIOM NOWEJ WIEZY JEST O JEDEN WIEKSZY
                    {
                         plansza[y][x]="x1";
                         plansza[y][x+skok+1][1]=plansza[y][x+skok+1][1]-1;
                    }
                    gracz=true;
                }
            }
            else // na docelowym nic nie ma
            {
                swap(plansza[y][x],plansza[y][x+skok]);
                if (bylo)
                {
                    plansza[y][x+pomoc]="  ";
                    plansza[y][x+skok][1]=plansza[y][x+skok][1]+1;
                }
                if ((bylo&&skok!=(plansza[y][x+skok][1]-48-1)) || (!bylo&&skok!=(plansza[y][x+skok][1]-48))) // UWAGA, DODATKOWE -1 BO POZIOM NOWEJ WIEZY JEST O JEDEN WIEKSZY
                {
                     plansza[y][x]="x1";
                     plansza[y][x+skok][1]=plansza[y][x+skok][1]-1;
                }
                gracz=true;
            }

        }
        else
        {
            continue;
        }
    }
}


void rysuj (string plansza[8][8])
{
    cout << endl;
    cout << " " << 8 << "  " << " ---  --- | " << plansza[0][2] << " | " << plansza[0][3] << " | " << plansza[0][4] << " | " << plansza[0][5] << " | ---  --- " << endl;
    cout << " " << 7 << "  " << " --- | " << plansza[1][1] << " | " << plansza[1][2] << " | " << plansza[1][3] << " | " << plansza[1][4] << " | " << plansza[1][5] << " | " << plansza[1][6] << " | --- " << endl;
    cout << " " << 6 << "  " << "| " << plansza[2][0] << " | " << plansza[2][1] << " | " << plansza[2][2] << " | " << plansza[2][3] << " | " << plansza[2][4] << " | " << plansza[2][5] << " | " << plansza[2][6] << " | " << plansza[2][7] << " |" <<endl;
    cout << " " << 5 << "  " << "| " << plansza[3][0] << " | " << plansza[3][1] << " | " << plansza[3][2] << " | " << plansza[3][3] << " | " << plansza[3][4] << " | " << plansza[3][5] << " | " << plansza[3][6] << " | " << plansza[3][7] << " |" <<endl;
    cout << " " << 4 << "  " << "| " << plansza[4][0] << " | " << plansza[4][1] << " | " << plansza[4][2] << " | " << plansza[4][3] << " | " << plansza[4][4] << " | " << plansza[4][5] << " | " << plansza[4][6] << " | " << plansza[4][7] << " |" <<endl;
    cout << " " << 3 << "  " << "| " << plansza[5][0] << " | " << plansza[5][1] << " | " << plansza[5][2] << " | " << plansza[5][3] << " | " << plansza[5][4] << " | " << plansza[5][5] << " | " << plansza[5][6] << " | " << plansza[5][7] << " |" <<endl;
    cout << " " << 2 << "  " << " --- | " << plansza[6][1] << " | " << plansza[6][2] << " | " << plansza[6][3] << " | " << plansza[6][4] << " | " << plansza[6][5] << " | " << plansza[6][6] << " | --- " << endl;
    cout << " " << 1 << "  " <<  " ---  --- | " << plansza[7][2] << " | " << plansza[7][3] << " | " << plansza[7][4] << " | " << plansza[7][5] << " | ---  --- " << endl;
    cout << "      A    B    C    D    E    F     G    H";
}

void pionki (string plansza[8][8])
{
    for (int i=1; i<7; i++)
    {
        for(int j=1; j<7; j++)
        {
            if (i%2==1)
            {
                plansza[i][1]="x1";
                plansza[i][2]="x1";
                plansza[i][3]="o1";
                plansza[i][4]="o1";
                plansza[i][5]="x1";
                plansza[i][6]="x1";
            }
            if (i%2==0)
            {
                plansza[i][1]="o1";
                plansza[i][2]="o1";
                plansza[i][3]="x1";
                plansza[i][4]="x1";
                plansza[i][5]="o1";
                plansza[i][6]="o1";
            }
        }
    }

    plansza[0][2]="  ";
    plansza[0][3]="  ";
    plansza[0][4]="  ";
    plansza[0][5]="  ";

    plansza[2][0]="  ";
    plansza[2][7]="  ";

    plansza[3][0]="  ";
    plansza[3][7]="  ";

    plansza[4][0]="  ";
    plansza[4][7]="  ";

    plansza[5][0]="  ";
    plansza[5][7]="  ";

    plansza[7][2]="  ";
    plansza[7][3]="  ";
    plansza[7][4]="  ";
    plansza[7][5]="  ";


    plansza[0][0]="---"; //jest niedozwolone
    plansza[0][1]="---";
    plansza[0][6]="---";
    plansza[0][7]="---";

    plansza[1][0]="---";
    plansza[1][7]="---";

    plansza[6][0]="---";
    plansza[6][7]="---";

    plansza[7][0]="---";
    plansza[7][1]="---";
    plansza[7][6]="---";
    plansza[7][7]="---";
}

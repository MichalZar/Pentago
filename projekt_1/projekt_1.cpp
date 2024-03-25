#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

//definicja stalych konfigurowalnych
const int MAX_LEN_IMIE = 15;
const int MAX_LEN_WYBOR = 8;
const int MAX_LEN_PLANSZA_KIK = 6;
const int MAX_LEN_PLANSZA_P = 9;
const int MAX_LICZBA_RUND = 36;
const int MAX_ODST_LEWO = 6;
const int MAX_ODST_GORA = 1;
const int MAX_ODST_DOL = 1;

//funkcja wita graczy i prosi ich o podanie imion
void powitanie_kik(char Gracz1[], char Gracz2[]) {
    cout << endl;
    cout << "Gra w kolko i krzyzyk" << endl;
    cout << "=====================" << endl;
    cout << endl;
    cout << "Niech gracz pierwszy poda swoje imie: ";
    cin >> Gracz1;
    cout << endl;
    cout << "Niech gracz drugi poda swoje imie: ";
    cin >> Gracz2;
    system("cls");
}

//funkcja odpowiada za przesuniecie planszy
void przesuniecie_lewo() {
    for (int p = 0;p < MAX_ODST_LEWO;p++) {
        cout << " ";
    }
}

//funkcja rysuje plansze do gry
void rysowanie_planszy_kik(char plansza[MAX_LEN_PLANSZA_KIK][MAX_LEN_PLANSZA_KIK]) {
    for (int k = 0; k < MAX_ODST_GORA;k++) {
        cout << endl;
    }
    for (int i = 1; i <= MAX_LEN_PLANSZA_KIK; i++) {
        przesuniecie_lewo();
        for (int j = 1; j <= MAX_LEN_PLANSZA_KIK; j++) {
            cout << " " << plansza[i - 1][j - 1] << " ";
            if (j % MAX_LEN_PLANSZA_KIK) {
                cout << "|";
            }
        }
        cout << endl;
        przesuniecie_lewo();
        if (i < MAX_LEN_PLANSZA_KIK) {
            cout << "---+---+---+---+---+---" << endl;
        }
    }
    for (int k = 0; k < MAX_ODST_DOL;k++) {
        cout << endl;
    }
}

//funkcja odpowiada za powiadomienie ktorego gracza jest runda, pyta danego gracza o wspolrzedne, sprawdza czy mozna w danym miejscu dostawic zeton i zamienia wolne pole na dany zeton
void ruch_kik(char plansza[MAX_LEN_PLANSZA_KIK][MAX_LEN_PLANSZA_KIK], char Gracz1[], char Gracz2[], int& k) {
    int pierwsza, druga;
    przesuniecie_lewo();
    if (k == 1) {
        cout << "Gracz: " << Gracz1 << " zeton: O" << endl;
    }
    else {
        cout << "Gracz: " << Gracz2 << " zeton: X" << endl;
    }

    cout << endl;
    przesuniecie_lewo();
    cout << "Podaj numer wiersz (1-6): ";
    cin >> pierwsza;
    przesuniecie_lewo();
    cout << "Podaj numer kolumny (1-6): ";
    cin >> druga;
    cout << endl;

    if ((pierwsza >= 1) && (pierwsza <= MAX_LEN_PLANSZA_KIK) && ((druga >= 1) && (druga <= MAX_LEN_PLANSZA_KIK)) && (plansza[pierwsza - 1][druga - 1] == ' ')) {
        if (k == 1) {
            for (int i = 0; i < MAX_LEN_PLANSZA_KIK; i++) {
                for (int j = 0; j < MAX_LEN_PLANSZA_KIK; j++) {
                    plansza[pierwsza - 1][druga - 1] = 'O';
                }
            }
        }
        else {
            for (int i = 0; i < MAX_LEN_PLANSZA_KIK; i++) {
                for (int j = 0; j < MAX_LEN_PLANSZA_KIK; j++) {
                    plansza[pierwsza - 1][druga - 1] = 'X';
                }
            }
        }
    }
    else if (((pierwsza < 1) || (pierwsza > MAX_LEN_PLANSZA_KIK)) || ((druga < 1) || (druga > MAX_LEN_PLANSZA_KIK))) {
        system("cls");
        rysowanie_planszy_kik(plansza);
        cout << "Liczby sa spoza zakresu!" << endl;
        cout << endl;
        cout << "HELP" << endl;
        cout << "Mozesz wybierac liczby TYLKO z zakresu od 1 do 6" << endl;
        cout << endl;
        ruch_kik(plansza, Gracz1, Gracz2, k);
    }
    else{
        system("cls");
        rysowanie_planszy_kik(plansza);
        przesuniecie_lewo();
        cout << "To miejsce jest juz zajete" << endl;
        cout << endl;
        ruch_kik(plansza, Gracz1, Gracz2, k);
    }

    system("cls");
}

//funkcja sprawdza warunek wygranej dla obydwu graczy i zwraca odpowiednio true jesli ktorys z graczy wygral i false, jezeli zaden gracz jeszcze nie wygral
bool wygrana_kik(int k, char plansza[MAX_LEN_PLANSZA_KIK][MAX_LEN_PLANSZA_KIK]) {
    bool test = false;
    if (k == 1) {
        for (int i = 0; i < 6;i++) {
            test = (((plansza[0][i] == 'O') && (plansza[1][i] == 'O') && (plansza[2][i] == 'O') && (plansza[3][i] == 'O') && (plansza[4][i] == 'O')) || ((plansza[1][i] == 'O') && (plansza[2][i] == 'O') && (plansza[3][i] == 'O') && (plansza[4][i] == 'O') && (plansza[5][i] == 'O')) || ((plansza[i][0] == 'O') && (plansza[i][1] == 'O') && (plansza[i][2] == 'O') && (plansza[i][3] == 'O') && (plansza[i][4] == 'O')) || ((plansza[i][1] == 'O') && (plansza[i][2] == 'O') && (plansza[i][3] == 'O') && (plansza[i][4] == 'O') && (plansza[i][5] == 'O')));
            if (test) {
                return true;
            }
        }
        test = (((plansza[0][0] == 'O') && (plansza[1][1] == 'O') && (plansza[2][2] == 'O') && (plansza[3][3] == 'O') && (plansza[4][4] == 'O')) || ((plansza[1][1] == 'O') && (plansza[2][2] == 'O') && (plansza[3][3] == 'O') && (plansza[4][4] == 'O') && (plansza[5][5] == 'O')) || ((plansza[1][0] == 'O') && (plansza[2][1] == 'O') && (plansza[3][2] == 'O') && (plansza[4][3] == 'O') && (plansza[5][4] == 'O')) || ((plansza[0][1] == 'O') && (plansza[1][2] == 'O') && (plansza[2][3] == 'O') && (plansza[3][4] == 'O') && (plansza[4][5] == 'O')) || ((plansza[0][5] == 'O') && (plansza[1][4] == 'O') && (plansza[2][3] == 'O') && (plansza[3][2] == 'O') && (plansza[4][1] == 'O')) || ((plansza[1][4] == 'O') && (plansza[2][3] == 'O') && (plansza[3][2] == 'O') && (plansza[4][1] == 'O') && (plansza[5][0] == 'O')) || ((plansza[1][5] == 'O') && (plansza[2][4] == 'O') && (plansza[3][3] == 'O') && (plansza[4][2] == 'O') && (plansza[5][1] == 'O')) || ((plansza[0][4] == 'O') && (plansza[1][3] == 'O') && (plansza[2][2] == 'O') && (plansza[3][1] == 'O') && (plansza[4][0] == 'O')));

        if (test) {
            return true;
        }
        return false;

    }
    else {
        for (int i = 0; i < 6;i++) {
            test = (((plansza[0][i] == 'X') && (plansza[1][i] == 'X') && (plansza[2][i] == 'X') && (plansza[3][i] == 'X') && (plansza[4][i] == 'X')) || ((plansza[1][i] == 'X') && (plansza[2][i] == 'X') && (plansza[3][i] == 'X') && (plansza[4][i] == 'X') && (plansza[5][i] == 'X')) || ((plansza[i][0] == 'X') && (plansza[i][1] == 'X') && (plansza[i][2] == 'X') && (plansza[i][3] == 'X') && (plansza[i][4] == 'X')) || ((plansza[i][1] == 'X') && (plansza[i][2] == 'X') && (plansza[i][3] == 'X') && (plansza[i][4] == 'X') && (plansza[i][5] == 'X')));
            if (test) {
                return true;
            }
        }
        test = (((plansza[0][0] == 'X') && (plansza[1][1] == 'X') && (plansza[2][2] == 'X') && (plansza[3][3] == 'X') && (plansza[4][4] == 'X')) || ((plansza[1][1] == 'X') && (plansza[2][2] == 'X') && (plansza[3][3] == 'X') && (plansza[4][4] == 'X') && (plansza[5][5] == 'X')) || ((plansza[1][0] == 'X') && (plansza[2][1] == 'X') && (plansza[3][2] == 'X') && (plansza[4][3] == 'X') && (plansza[5][4] == 'X')) || ((plansza[0][1] == 'X') && (plansza[1][2] == 'X') && (plansza[2][3] == 'X') && (plansza[3][4] == 'X') && (plansza[4][5] == 'X')) || ((plansza[0][5] == 'X') && (plansza[1][4] == 'X') && (plansza[2][3] == 'X') && (plansza[3][2] == 'X') && (plansza[4][1] == 'X')) || ((plansza[1][4] == 'X') && (plansza[2][3] == 'X') && (plansza[3][2] == 'X') && (plansza[4][1] == 'X') && (plansza[5][0] == 'X')) || ((plansza[1][5] == 'X') && (plansza[2][4] == 'X') && (plansza[3][3] == 'X') && (plansza[4][2] == 'X') && (plansza[5][1] == 'X')) || ((plansza[0][4] == 'X') && (plansza[1][3] == 'X') && (plansza[2][2] == 'X') && (plansza[3][1] == 'X') && (plansza[4][0] == 'X')));

        if (test) {
            return true;
        }
        return false;
    }
}

//funkcaja wita graczy i prosi ich o podanie imion
void powitanie_pentago(char Gracz1[], char Gracz2[]) {
    cout << endl;
    cout << "Gra w Pentago" << endl;
    cout << "==============" << endl;
    cout << endl;
    cout << "Niech gracz pierwszy poda swoje imie: ";
    cin >> Gracz1;
    cout << endl;
    cout << "Niech gracz drugi poda swoje imie: ";
    cin >> Gracz2;
    system("cls");
}

//dzieki tej funkcji gracze moga wybrac zetony na poczatku gry
void wybor_zetonow(char &g1, char &g2) {
    bool czy = true;
    while (czy) {
        cout << "Jakimi zetonami chce grac Gracz1? (C - czerwone/N - niebieskie): ";
        cin >> g1;
        cout << "Jakimi zetonami chce grac Gracz2? (C - czerwone/N - niebieskie): ";
        cin >> g2;
        if (g1 == g2) {
            system("cls");
            cout << "Znaki musza byc rozne!" << endl;
            cout << endl;
            continue;
        }
        else if (!(((g1=='C')&&(g2=='N'))||((g1=='N')&&(g2=='C')))) {
            system("cls");
            cout << "Mozesz podac tylko znaki 'C' lub ' N'" << endl;
            cout << endl;
            continue;
        }
        czy = false;
        system("cls");
    }
}

//funkcja wypisuje informacje o graczach i zetonach jakimi graja
void gracze(int k, char Gracz1[], char Gracz2[],char g1, char g2) {
    if (k == 1) {
        cout << "Gracz: " << Gracz1 << " zeton: " << g1 << endl;
    }
    else {
        cout << "Gracz: " << Gracz2 << " zeton: " << g2 << endl;
    }
}

//funckaj rysuje poziome linie na planszy
void rysowanie_poziome() {
    cout << endl;
    przesuniecie_lewo();
    cout << "\xC3";
    for (int i = 0; i < 3; i++) {
        cout << "\xC4";
    }
    cout << "\xC5";
    for (int i = 0; i < 3; i++) {
        cout << "\xC4";
    }
    cout << "\xC5";
    for (int i = 0; i < 3; i++) {
        cout << "\xC4";
    }
    cout << "\xBA";
    for (int i = 0; i < 3; i++) {
        cout << "\xC4";
    }
    cout << "\xC5";
    for (int i = 0; i < 3; i++) {
        cout << "\xC4";
    }
    cout << "\xC5";
    for (int i = 0; i < 3; i++) {
        cout << "\xC4";
    }
    cout << "\xB4";
}
//funkcja rysuje srodek planszy
void rysowanie_srodka1(int k, char plansza[]) {
    for (int i = k; i < k + 3; i++) {
        cout << "\xB3 " << plansza[i] << " ";
    }
}
//funkcja rysuje srodek planszy
void rysowanie_srodka2(int k, char plansza[]) {
    cout << "\xBA";
    for (int i = k; i < k + 3; i++) {
        cout << " " << plansza[i] << " \xB3";
    }
}

//funkcja rysuje plansze
void rysowanie_planszy_pentago(char plansza1[], char plansza2[], char plansza3[], char plansza4[]) {
    for (int k = 0; k < MAX_ODST_GORA;k++) {
        cout << endl;
    }
    przesuniecie_lewo();
    cout << "\xDA";
    for (int i = 0; i < 23; i++) {
        cout << "\xC4";
    }
    cout << "\xBF" << endl;
    int k = 0;
    przesuniecie_lewo();
    rysowanie_srodka1(k, plansza1);
    rysowanie_srodka2(k, plansza2);;
    rysowanie_poziome();
    cout << endl;
    k += 3;
    przesuniecie_lewo();
    rysowanie_srodka1(k, plansza1);
    rysowanie_srodka2(k, plansza2);
    rysowanie_poziome();
    cout << endl;
    k += 3;
    przesuniecie_lewo();
    rysowanie_srodka1(k, plansza1);
    rysowanie_srodka2(k, plansza2);
    cout << endl;
    przesuniecie_lewo();
    cout << "\xC3";
    for (int i = 0; i < 11; i++) {
        cout << "\xCD";
    }
    cout << "\xCE";
    for (int i = 0; i < 11; i++) {
        cout << "\xCD";
    }
    cout << "\xB4";
    cout << endl;
    k = 0;
    przesuniecie_lewo();
    rysowanie_srodka1(k, plansza3);
    rysowanie_srodka2(k, plansza4);
    rysowanie_poziome();
    cout << endl;
    k += 3;
    przesuniecie_lewo();
    rysowanie_srodka1(k, plansza3);
    rysowanie_srodka2(k, plansza4);
    rysowanie_poziome();
    cout << endl;
    k += 3;
    przesuniecie_lewo();
    rysowanie_srodka1(k, plansza3);
    rysowanie_srodka2(k, plansza4);
    cout << endl;
    przesuniecie_lewo();
    cout << "\xC0";
    for (int i = 0; i < 23; i++) {
        cout << "\xC4";
    }
    cout << "\xD9" << endl;
    for (int k = 0; k < MAX_ODST_DOL;k++) {
        cout << endl;
    }
}

//funkcja zamienia zatony graczy na planszy, jesli ci wybrali obcje zmiany zetonow
void zamaiana_na_planszy(char g1,char g2, char plansza[]) {
    int plansza_p[MAX_LEN_PLANSZA_P];
    int b = 0;
    for (int i = 0; i < MAX_LEN_PLANSZA_P; i++) {
        if (plansza[i] == g1) {
            plansza_p[b] = i;
            b += 1;
        }
        if (plansza[i] == g2) {
            plansza[i] = g1;
        }
    }
    for (int i = 0; i < b; i++) {
        plansza[plansza_p[i]] = g2;
    }
}

//funkcja zamienia zetony graczy 
void czy_zmienic_zetony(char &g1,char &g2, char plansza1[],char plansza2[], char plansza3[], char plansza4[], int k, char Gracz1[], char Gracz2[]) {
    char czy;
    char temp;
    cout << "Czy zamienic zetony graczy? (T - TAK/ N - NIE): ";
    cin >> czy;
    if ((czy == 'T')|| (czy == 't')) {
        zamaiana_na_planszy(g1, g2, plansza1);
        zamaiana_na_planszy(g1, g2, plansza2);
        zamaiana_na_planszy(g1, g2, plansza3);
        zamaiana_na_planszy(g1, g2, plansza4);
        
        temp = g1;
        g1 = g2;
        g2 = temp;
        system("cls");
        cout << endl;
        przesuniecie_lewo();
        gracze(k, Gracz1, Gracz2, g1, g2);
        rysowanie_planszy_pentago(plansza1, plansza2, plansza3, plansza4);
    }
}

//funckja odpowiada za czyszczenie planszy przed rozgrywka
void czyszczenie_planszy(char plansza[]) {
    for (int i = 0; i < MAX_LEN_PLANSZA_P; i++) {
        plansza[i] = ' ';
    }
}

//funkcja sprawdza poziomo czy ktorys z graczy nie wygral
bool wygrana_poziomo1(bool& test, int m, char plansza1[], char plansza2[], char g) {
    test = ((plansza1[m] == g) && (plansza1[m + 1] == g) && (plansza1[m + 2] == g) && (plansza2[m] == g) && (plansza2[m + 1] == g));
    if (test) {
        return true;
    }
    return false;
}
//funkcja sprawdza poziomo czy ktorys z graczy nie wygral
bool wygrana_poziomo2(bool& test, int m, char plansza1[], char plansza2[], char g) {
    test = ((plansza1[m + 1] == g) && (plansza1[m + 2] == g) && (plansza1[m] == g) && (plansza2[m + 1] == g) && (plansza2[m + 2] == g));
    if (test) {
        return true;
    }
    return false;
}
//funkcja sprawdza pionow czy ktorys z graczy nie wygral
bool wygrana_pionowo1(bool& test, int m, char plansza1[], char plansza2[], char g) {
    test = ((plansza1[m] == g) && (plansza1[m + 3] == g) && (plansza1[m + 6] == g) && (plansza2[m] == g) && (plansza2[m + 3] == g));
    if (test) {
        return true;
    }
    return false;
}
//funkcja sprawdza pionow czy ktorys z graczy nie wygral
bool wygrana_pionowo2(bool& test, int m, char plansza1[], char plansza2[], char g) {
    test = ((plansza1[m + 3] == g) && (plansza1[m + 6] == g) && (plansza1[m] == g) && (plansza2[m + 3] == g) && (plansza2[m + 6] == g));
    if (test) {
        return true;
    }
    return false;
}
//funkcja sprawdza czy ktorys z graczy nie wygral
bool wygrana_pentago(int k, char plansza1[], char plansza2[], char plansza3[], char plansza4[], char g1, char g2) {
    bool test = false;
    if (k == 1) {
        for (int i = 0; i <= 6; i += 3) {
            if (wygrana_poziomo1(test, i, plansza1, plansza2, g1)) {
                return true;
            }
            else if (wygrana_poziomo2(test, i, plansza2, plansza1, g1)) {
                return true;
            }
            else if (wygrana_poziomo1(test, i, plansza3, plansza4, g1)) {
                return true;
            }
            else if (wygrana_poziomo2(test, i, plansza4, plansza3, g1)) {
                return true;
            }
        }

        for (int i = 0; i <= 2; i++) {
            if (wygrana_pionowo1(test, i, plansza1, plansza3, g1)) {
                return true;
            }
            else if (wygrana_pionowo2(test, i, plansza3, plansza1, g1)) {
                return true;
            }
            else if (wygrana_pionowo1(test, i, plansza2, plansza4, g1)) {
                return true;
            }
            else if (wygrana_pionowo2(test, i, plansza4, plansza2, g1)) {
                return true;
            }
        }

        test = (((plansza1[0] == g1) && (plansza1[4] == g1) && (plansza1[8] == g1) && (plansza4[0] == g1) && (plansza4[4] == g1)) || ((plansza1[4] == g1) && (plansza1[8] == g1) && (plansza4[0] == g1) && (plansza4[4] == g1) && (plansza4[8] == g1)) || ((plansza1[1] == g1) && (plansza1[5] == g1) && (plansza2[6] == g1) && (plansza4[1] == g1) && (plansza4[5] == g1)) || ((plansza1[3] == g1) && (plansza1[7] == g1) && (plansza3[2] == g1) && (plansza4[3] == g1) && (plansza4[7] == g1)) || ((plansza2[2] == g1) && (plansza2[4] == g1) && (plansza2[6] == g1) && (plansza3[2] == g1) && (plansza3[4] == g1)) || ((plansza2[4] == g1) && (plansza2[6] == g1) && (plansza3[2] == g1) && (plansza3[4] == g1) && (plansza3[6] == g1)) || ((plansza2[1] == g1) && (plansza2[3] == g1) && (plansza1[8] == g1) && (plansza3[1] == g1) && (plansza3[3] == g1)) || ((plansza2[5] == g1) && (plansza2[7] == g1) && (plansza4[0] == g1) && (plansza3[5] == g1) && (plansza3[7] == g1)));

        if (test) {
            return true;
        }
        return false;
    }
    else {
        for (int i = 0; i <= 6; i += 3) {
            if (wygrana_poziomo1(test, i, plansza1, plansza2, g2)) {
                return true;
            }
            else if (wygrana_poziomo2(test, i, plansza2, plansza1, g2)) {
                return true;
            }
            else if (wygrana_poziomo1(test, i, plansza3, plansza4, g2)) {
                return true;
            }
            else if (wygrana_poziomo2(test, i, plansza4, plansza3, g2)) {
                return true;
            }
        }

        for (int i = 0; i <= 2; i++) {
            if (wygrana_pionowo1(test, i, plansza1, plansza3, g2)) {
                return true;
            }
            else if (wygrana_pionowo2(test, i, plansza3, plansza1, g2)) {
                return true;
            }
            else if (wygrana_pionowo1(test, i, plansza2, plansza4, g2)) {
                return true;
            }
            else if (wygrana_pionowo2(test, i, plansza4, plansza2, g2)) {
                return true;
            }
        }

        test = (((plansza1[0] == g2) && (plansza1[4] == g2) && (plansza1[8] == g2) && (plansza4[0] == g2) && (plansza4[4] == g2)) || ((plansza1[4] == g2) && (plansza1[8] == g2) && (plansza4[0] == g2) && (plansza4[4] == g2) && (plansza4[8] == g2)) || ((plansza1[1] == g2) && (plansza1[5] == g2) && (plansza2[6] == g2) && (plansza4[1] == g2) && (plansza4[5] == g2)) || ((plansza1[3] == g2) && (plansza1[7] == g2) && (plansza3[2] == g2) && (plansza4[3] == g2) && (plansza4[7] == g2)) || ((plansza2[2] == g2) && (plansza2[4] == g2) && (plansza2[6] == g2) && (plansza3[2] == g2) && (plansza3[4] == g2)) || ((plansza2[4] == g2) && (plansza2[6] == g2) && (plansza3[2] == g2) && (plansza3[4] == g2) && (plansza3[6] == g2)) || ((plansza2[1] == g2) && (plansza2[3] == g2) && (plansza1[8] == g2) && (plansza3[1] == g2) && (plansza3[3] == g2)) || ((plansza2[5] == g2) && (plansza2[7] == g2) && (plansza4[0] == g2) && (plansza3[5] == g2) && (plansza3[7] == g2)));

        if (test) {
            return true;
        }
        return false;
    }
}

//funkcja jest odpowiedzialna za odliczanie czasu dla graczy
void odliczanie_czasu(clock_t& start, int& ile_czasu) {
    start = clock();
    przesuniecie_lewo();
    cout << "Twoj czas: " << ile_czasu / 60 << " minut i ";
    if (ile_czasu > 60) {
        cout << ile_czasu - ((ile_czasu / 60) * 60) << " sekund" << endl;
    }
    else {
        cout << ile_czasu << " sekund" << endl;
    }
}

//funkcja wyswietla menu
void menu(int k, clock_t& start1, clock_t& stop1, int& ile_czasu1, clock_t& start2, clock_t& stop2, int& ile_czasu2) {
    char opcja;
    do {
        system("cls");
        cout << "MENU" << endl;
        cout << "1. Pauza (p)" << endl;
        cout << "2. Opis programu (h)" << endl;
        cout << "Podaj opcje:";
        cin >> opcja;

        switch (opcja) {
        case 'p':
            system("cls");
            cout << endl;
            przesuniecie_lewo();
            cout << "PAUZA" << endl;
            if (k==1) {
                ile_czasu1 = ile_czasu1 + (double)(clock() - start1) / CLOCKS_PER_SEC;
                stop1 = clock();
            }
            else {
                ile_czasu2 = ile_czasu2 + (double)(clock() - start2) / CLOCKS_PER_SEC;
                stop2 = clock();
            }
            cout << endl;
            cout << "Jezeli chcesz wyjsc z pauzy wcinsij przycisk 'p' ";
            cin >> opcja;
            if (opcja=='p') {
                if (k == 1) {
                    odliczanie_czasu(start1,ile_czasu1);
                }
                else {
                    odliczanie_czasu(start2,ile_czasu1);
                }
                break;
            }
        case 'h':
            cout << endl;
            cout << "Pentago jest gra dwuosobowa na planszy. \nPlansza sklada się z 4 ruchomych czesci, ktore mozna obracac. \nKazda czesc zawiera 9 miejsc na zetony. \nGracze po kolei oddaja ruch skladajacy sie z 2 czesci: \ndolozenia swojego zetonu na niezajete pole planszy\n obrot jednej z czesci planszy o 90 stopni w dowolnym kierunku.\n Nie mozna zrezygnowac z zadnej czesci ruchu.\n Wygrywa osoba, ktorej 5 zetonow, po pelnym ruchu,\n sa ulozone w rzedzie / kolumnie / po skosach" << endl;
            cout << endl;
            break;
        default:
            cout << "Nie ma takiej opcji!" << endl;
            break;
        }
        cout << "Jezeli chcesz wyjsc z opcji wcisnij dowolny przycisk, jezeli nie wcinsij 'm' ";
        cin >> opcja;
        system("cls");
    } while (opcja=='m');
}

//funkcja sprawdza czy podane przez gracza miejsce jest wolne
bool sprawdzenie_planszy(char znak,int pole, char plansza1[], char plansza2[], char plansza3[], char plansza4[]) {
    if (znak=='q') {
        if (plansza1[pole] == ' ') {
            return true;
        }
        return false;
    }
    else if (znak == 'w') {
        if (plansza2[pole] == ' ') {
            return true;
        }
        return false;
    }
    else if (znak == 'a') {
        if (plansza3[pole] == ' ') {
            return true;
        }
        return false;
    }
    else if (znak == 's') {
        if (plansza4[pole] == ' ') {
            return true;
        }
        return false;
    }
}

//funkcja odpowiada za obrot jednej z mniejszych plansz
void obrot_planszy(char znak, char plansza[]) {
    char a,b;
    if (znak == 'z') {
        a = plansza[2];
        plansza[2] = plansza[0];

        b = plansza[8];
        plansza[8] = a;

        plansza[0] = plansza[6];
        plansza[6] = b;

        a = plansza[5];
        plansza[5] = plansza[1];

        b = plansza[7];
        plansza[7] = a;

        plansza[1] = plansza[3];
        plansza[3] = b;

    }
    else if (znak == 'x') {
        a = plansza[6];
        plansza[6] = plansza[0];

        b = plansza[8];
        plansza[8] = a;

        plansza[0] = plansza[2];
        plansza[2] = b;

        a = plansza[3];
        plansza[3] = plansza[1];

        b = plansza[7];
        plansza[7] = a;

        plansza[1] = plansza[5];
        plansza[5] = b;
    }
}

//funkcja pyta sie gracza ktora plansze chce obrocic, sprawdza wprowadzone dane i obraca plansze
void obrot_pola(char k_plansza, char plansza1[], char plansza2[], char plansza3[], char plansza4[]) {
    char obrot;
    przesuniecie_lewo();
    cout << "Podaj plansze ktora chcesz obrocic (q/w/a/s): ";
    cin >> k_plansza;
    cout << endl;
    przesuniecie_lewo();
    cout << "Podaj w ktora strone chcesz obrocic (z - w prawo/x - w lewo): ";
    cin >> obrot;

    if (((k_plansza == 'q') || (k_plansza == 'a') || (k_plansza == 's') || (k_plansza == 'w')) && ((obrot == 'z') || (obrot=='x'))) {
        switch (k_plansza) {
        case 'q':
            obrot_planszy(obrot, plansza1);
            break;
        case 'w':
            obrot_planszy(obrot, plansza2);
            break;
        case 'a':
            obrot_planszy(obrot, plansza3);
            break;
        case 's':
            obrot_planszy(obrot, plansza4);
            break;
        }
    }
    else if (!(obrot == 'z') || (obrot == 'x')) {
        system("cls");
        rysowanie_planszy_pentago(plansza1, plansza2, plansza3, plansza4);
        cout << "Zly wybor obrotu!" << endl;
        cout << "HELP" << endl;
        cout << "Mozesz wybierac TYLKO znaki 'x','z'" << endl;
        cout << endl;
        obrot_pola(k_plansza, plansza1, plansza2, plansza3, plansza4);
    }
    else {
        system("cls");
        rysowanie_planszy_pentago(plansza1, plansza2, plansza3, plansza4);
        cout << "Zly wybor pola!" << endl;
        cout << "HELP" << endl;
        cout << "Mozesz wybierac TYLKO znaki 'q','w','a',''s'" << endl;
        cout << endl;
        obrot_pola(k_plansza, plansza1, plansza2, plansza3, plansza4);
    }
}

//funkcja odpowiada za dostawienie zetonu na plansze, sprawdzenie czy wszystkie dane sa poprawne i wyswietlenie odpowiedniego komunikatu
void ruch_pentago(int &k, char Gracz1[], char Gracz2[], char plansza1[], char plansza2[], char plansza3[], char plansza4[], char &g1, char &g2, int a, clock_t &start1, clock_t &stop1,int &ile_czasu1, clock_t &start2, clock_t &stop2,int &ile_czasu2,bool &czy) {
    int pole;
    char k_plansza;
    char opcja;
    przesuniecie_lewo();
    cout << "Wejsc do opcji? (wcisnij 'm' jezeli tak, inny klawisz jezeli nie) ";
    cin >> opcja;
    if (opcja == 'm') {
        menu(k,start1,stop1, ile_czasu1,start2, stop2, ile_czasu2);
    }
    przesuniecie_lewo();
    gracze(k, Gracz1, Gracz2, g1, g2);
    rysowanie_planszy_pentago(plansza1, plansza2, plansza3, plansza4);
    przesuniecie_lewo();
    czy_zmienic_zetony(g1, g2, plansza1, plansza2, plansza3, plansza4, k, Gracz1, Gracz2);
    przesuniecie_lewo();
    cout << "Podaj plansze (q - lewa gorna/w - prawa gorna/a - lewa dolna/s - prawa dolna): ";
    cin >> k_plansza;
    przesuniecie_lewo();
    cout << "Podaj numer pola (1-9): ";
    cin >> pole;
    cout << endl;

    if ((pole==7)||(pole==8)||(pole==9)) {
        pole = pole - 7;
    }else if ((pole == 4) || (pole == 5) || (pole == 6)) {
        pole = pole - 1;
    }else if ((pole == 1) || (pole == 2) || (pole == 3)) {
        pole = pole + 5;
    }

    if (((pole >= 0) && (pole <= MAX_LEN_PLANSZA_P)) && ((k_plansza == 'q') || (k_plansza == 'a') || (k_plansza == 's') || (k_plansza == 'w')) && (sprawdzenie_planszy(k_plansza, pole, plansza1, plansza2, plansza3, plansza4))) {
        if (k == 1) {
            switch (k_plansza) {
            case 'q':
                plansza1[pole] = g1;
                break;
            case 'w':
                plansza2[pole] = g1;
                break;
            case 'a':
                plansza3[pole] = g1;
                break;
            case 's':
                plansza4[pole] = g1;
                break;
            }
            system("cls");
            rysowanie_planszy_pentago(plansza1, plansza2, plansza3, plansza4);
            obrot_pola(k_plansza,plansza1, plansza2, plansza3, plansza4);
        }
        else {
            switch (k_plansza) {
            case 'q':
                plansza1[pole] = g2;
                break;
            case 'w':
                plansza2[pole] = g2;
                break;
            case 'a':
                plansza3[pole] = g2;
                break;
            case 's':
                plansza4[pole] = g2;
                break;
            }
            system("cls");
            rysowanie_planszy_pentago(plansza1, plansza2, plansza3, plansza4);
            obrot_pola(k_plansza, plansza1, plansza2, plansza3, plansza4);

        }
        if (wygrana_pentago(k, plansza1, plansza2, plansza3, plansza4, g1, g2)) {
            czy = true;
        }
    }
    else if ((pole<1)||(pole>MAX_LEN_PLANSZA_P)){
        system("cls");
        przesuniecie_lewo();
        cout << "Liczby sa spoza zakresu!" << endl;
        przesuniecie_lewo();
        cout << "HELP" << endl;
        przesuniecie_lewo();
        cout << "Mozesz wybierac liczby TYLKO z zakresu od 1 do 9" << endl;
        cout << endl;
        ruch_pentago(k, Gracz1, Gracz2, plansza1, plansza2, plansza3, plansza4,g1,g2,a, start1,stop1,ile_czasu1,start2,stop2,ile_czasu2,czy);
    }
    else if ((sprawdzenie_planszy(k_plansza, pole, plansza1, plansza2, plansza3, plansza4))==false) {
        system("cls");
        przesuniecie_lewo();
        cout << endl;
        cout << "To pole jest juz zajete!" << endl;
        cout << endl;
        ruch_pentago(k, Gracz1, Gracz2, plansza1, plansza2, plansza3, plansza4,g1,g2,a, start1, stop1, ile_czasu1, start2, stop2, ile_czasu2,czy);
    }
    else {
        system("cls");
        przesuniecie_lewo();
        cout << "Zly wybor pola!" << endl;
        przesuniecie_lewo();
        cout << "HELP" << endl;
        przesuniecie_lewo();
        cout << "Mozesz wybierac TYLKO znaki 'q','w','a',''s'" << endl;
        ruch_pentago(k, Gracz1, Gracz2, plansza1, plansza2, plansza3, plansza4,g1,g2,a, start1, stop1, ile_czasu1, start2, stop2, ile_czasu2,czy);
    }
    
    system("cls");
}

int main()
{
    char Gracz1[MAX_LEN_IMIE];
    char Gracz2[MAX_LEN_IMIE];

    char wybor[MAX_LEN_WYBOR];
    cout << "Wybierz gre w jaka chcesz zagrac: pentago lub kolko i krzyzyk (wpisz: pentago/kik): ";
    cin >> wybor;

    //kolko i krzyzyk
    if (!(strcmp(wybor, "kik"))) {

        char plansza[MAX_LEN_PLANSZA_KIK][MAX_LEN_PLANSZA_KIK];

        powitanie_kik(Gracz1, Gracz2);
        cout << endl;

        //utworzenie pustej planszy
        for (int i = 0; i < MAX_LEN_PLANSZA_KIK; i++) {
            for (int j = 0; j < MAX_LEN_PLANSZA_KIK; j++) {
                plansza[i][j] = ' ';
            }
        }
        int k=1;
 
        for (int a = 1; a <= MAX_LICZBA_RUND; a++) {
            przesuniecie_lewo();
            cout << "Runda: " << a << endl;
            rysowanie_planszy_kik(plansza);
            ruch_kik(plansza, Gracz1, Gracz2, k);
            cout << endl;
            if (wygrana_kik(k, plansza)) {
                if (k == 1) {
                    rysowanie_planszy_kik(plansza);
                    cout << endl;
                    cout << "Wygrywa " << Gracz1 << " w rundzie numer " << a << endl;
                }
                else {
                    rysowanie_planszy_kik(plansza);
                    cout << endl;
                    cout << "Wygrywa " << Gracz2 << " w rundzie numer " << a << endl;
                }
                return 0;
            }
            //zmiana gracza
            k++;
            if (k > 2) {
                k -= 2;
            }
        }

        //informacja o remisie
        rysowanie_planszy_kik(plansza);
        cout << endl;
        cout << "REMIS!" << endl;

        return 0;

    }
    else if (!(strcmp(wybor, "pentago"))) {

        powitanie_pentago(Gracz1, Gracz2);
        cout << endl;

        char czy_plansza;
        cout << "Wczytac predefinowana plansze? \n(jezeli tak wcisnij 'o', jezeli nie wcisnij inny dowolny przycisk) ";
        cin >> czy_plansza;

        system("cls");

        //wczytanie predefiniowanej planszy
        if (czy_plansza == 'o') {
            char plansza1[MAX_LEN_PLANSZA_P] = {' ','N',' ','C','C','N',' ','C',' '};
            char plansza2[MAX_LEN_PLANSZA_P] = {' ','C',' ','C','N',' ',' ',' ',' '};
            char plansza3[MAX_LEN_PLANSZA_P] = {'C','C',' ','N',' ','C',' ','N',' '};
            char plansza4[MAX_LEN_PLANSZA_P] = {' ',' ',' ',' ','N',' ',' ','N','N'};

            char g1='C', g2='N';

            int k = 1;
            int czas = 900;

            clock_t start1, stop1, start2, stop2;
            int ile_czasu1 = 420, ile_czasu2 = 420;

            bool czy = false;

            for (int a = 17; a <= MAX_LICZBA_RUND; a++) {
                //sprawdzenie czy ktorys z graczy nie przekroczyl limitu czasu
                if (ile_czasu1 > czas) {
                    rysowanie_planszy_pentago(plansza1, plansza2, plansza3, plansza4);
                    cout << endl;
                    cout << "Wygrywa " << Gracz2 << " w rundzie numer " << a << endl;
                    return 0;
                }

                else if (ile_czasu2 > czas) {
                    rysowanie_planszy_pentago(plansza1, plansza2, plansza3, plansza4);
                    cout << endl;
                    cout << "Wygrywa " << Gracz1 << " w rundzie numer " << a << endl;
                    return 0;
                }
                przesuniecie_lewo();
                cout << "Runda: " << a << endl;
                przesuniecie_lewo();
                if (k == 1) {
                    odliczanie_czasu(start1, ile_czasu1);
                }
                else {
                    odliczanie_czasu(start2, ile_czasu2);
                }
                ruch_pentago(k, Gracz1, Gracz2, plansza1, plansza2, plansza3, plansza4, g1, g2,a, start1, stop1, ile_czasu1, start2, stop2, ile_czasu2,czy);
                if (k == 1) {
                    ile_czasu1 = ile_czasu1 + (double)(clock() - start1) / CLOCKS_PER_SEC;
                    stop1 = clock();
                }
                else {
                    ile_czasu2 = ile_czasu2 + (double)(clock() - start2) / CLOCKS_PER_SEC;
                    stop2 = clock();
                }
                cout << endl;
                if (czy) {
                    if (k == 1) {
                        rysowanie_planszy_pentago(plansza1, plansza2, plansza3, plansza4);
                        cout << endl;
                        cout << "Wygrywa " << Gracz1 << " w rundzie numer " << a << endl;
                    }
                    else {
                        rysowanie_planszy_pentago(plansza1, plansza2, plansza3, plansza4);
                        cout << endl;
                        cout << "Wygrywa " << Gracz2 << " w rundzie numer " << a << endl;
                    }
                    return 0;
                }
                k++;
                if (k > 2) {
                    k -= 2;
                }
            }

            rysowanie_planszy_pentago(plansza1, plansza2, plansza3, plansza4);
            cout << endl;
            cout << "REMIS!" << endl;

            return 0;
        }
        else {
            //wczytanie prawidlowej gry
            char plansza1[MAX_LEN_PLANSZA_P];
            char plansza2[MAX_LEN_PLANSZA_P];
            char plansza3[MAX_LEN_PLANSZA_P];
            char plansza4[MAX_LEN_PLANSZA_P];

            czyszczenie_planszy(plansza1);
            czyszczenie_planszy(plansza2);
            czyszczenie_planszy(plansza3);
            czyszczenie_planszy(plansza4);

            int k=1;

            char g1, g2;
            wybor_zetonow(g1, g2);
            cout << endl;

            int czas;
            cout << "Podaj ile czasu ma kazdy gracz: (w minutach): ";
            cin >> czas;
            system("cls");

            bool czy = false;

            clock_t start1, stop1, start2,stop2;
            int ile_czasu1=0, ile_czasu2=0;
            
            for (int a = 1; a <= MAX_LICZBA_RUND; a++) {
                //sprawdzenie czy ktorys z graczy nie przekroczyl limitu czasu
                if (ile_czasu1 > (czas*60)) {
                    rysowanie_planszy_pentago(plansza1, plansza2, plansza3, plansza4);
                    cout << endl;
                    cout << "Wygrywa " << Gracz2 << " w rundzie numer " << a << endl;
                    return 0;
                }
                else if (ile_czasu2 > (czas*60)) {
                    rysowanie_planszy_pentago(plansza1, plansza2, plansza3, plansza4);
                    cout << endl;
                    cout << "Wygrywa " << Gracz1 << " w rundzie numer " << a << endl;
                    return 0;
                }
                przesuniecie_lewo();
                cout << "Runda: " << a << endl;
                przesuniecie_lewo();
                //wystartowanie czasu gracza ktory ma ruch
                if (k == 1) {
                    odliczanie_czasu(start1, ile_czasu1);
                }
                else {
                    odliczanie_czasu(start2, ile_czasu2);
                }
                ruch_pentago(k, Gracz1, Gracz2, plansza1, plansza2, plansza3, plansza4, g1, g2,a, start1, stop1, ile_czasu1, start2, stop2, ile_czasu2,czy);
                if (czy) {
                    if (k == 1) {
                        rysowanie_planszy_pentago(plansza1, plansza2, plansza3, plansza4);
                        cout << endl;
                        cout << "Wygrywa " << Gracz1 << " w rundzie numer " << a << endl;
                    }
                    else {
                        rysowanie_planszy_pentago(plansza1, plansza2, plansza3, plansza4);
                        cout << endl;
                        cout << "Wygrywa " << Gracz2 << " w rundzie numer " << a << endl;
                    }
                    return 0;
                }
                //zatrzymanie czasu gracza ktory mial przed chwila ruch
                if (k == 1) {
                    ile_czasu1 = ile_czasu1 + (double)(clock() - start1) / CLOCKS_PER_SEC;
                    stop1 = clock();
                }
                else {
                    ile_czasu2 = ile_czasu2 + (double)(clock() - start2) / CLOCKS_PER_SEC;
                    stop2 = clock();
                }
                k++;
                if (k > 2) {
                    k -= 2;
                }
            }

            rysowanie_planszy_pentago(plansza1, plansza2, plansza3, plansza4);
            cout << endl;
            cout << "REMIS!" << endl;

            return 0;
        }
    }
    else {
    //inforamcja jezeli wybrana opcja jest niepoprawna
        cout << "Nie ma takiej opcij!" << endl;
        return 0;
    }
}
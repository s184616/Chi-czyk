// POP 2020-12-08 projekt 1 Rykowska Aleksandra EIT 6 184616, Dev-C++ 5.11, TDM-GCC 4.9.2 64-bit

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

const int MAX_KOSTKA = 6; // 6, ale dla testow mozna ustawic np 1

void wczytaj_imiona (int & ilosc_graczy, string & gracz2, string & gracz3, string & gracz4);
void rysuj_plansze(int g[4][4]);
void narysuj_pionek(int pole, int g[4][4]); // funkcja rysuje pionka na bialym polu (1-40) o numerze 'pole'
void narysuj_pionek_r(int pole, int g[4][4]); // sprawdza red tylko na mecie. pola = 41, 42, 43, 44 
void narysuj_pionek_b(int pole, int g[4][4]); // sprawdza blue tylko na mecie. pola = 41, 42, 43, 44 
void narysuj_pionek_g(int pole, int g[4][4]); // sprawdza green tylko na mecie. pola = 41, 42, 43, 44 
void narysuj_pionek_y(int pole, int g[4][4]); // sprawdza yellow tylko na mecie. pola = 41, 42, 43, 44 
void rysuj_status(int g[4][4], int ile_rzutow [4], int biezacy_gracz, char miejsca [4], string imie_gracza [4], int ilosc_graczy, int wykorzystane_rzuty[4]);
int rzuc_kostka(int biezacy_gracz); // wylosowanie 1-6 i zwracanie wartosci kostka
void narysuj_kostke(int los); // narysuj kostke graficznie
int sprawdz_ile_rzutow(int biezacy_gracz, int nr_gracza_i_nr_pionka[4][4], int wylosowana_liczba); // 1, 2 (gdy bedzie 6), 3 (w bazie i w mecie)
int spytaj_jakim_pionkiem_ruszyc(int biezacy_gracz, int nr_gracza_i_nr_pionka[4][4], string imie_gracza[4]); // 1, 2, 3, 4, -1 (q)-quit
int czy_pionek_moze_ruszyc(int biezacy_gracz, int nr_gracza_i_nr_pionka[4][4], int wylosowana_liczba, int nr_pionka_rusza); // sprawdz czy da rade ruszyc z wylosowana wartoscia: 0 - nie wolno, 1 - moze ruszyc
int spr_bicie_y(int nr_gracza_i_nr_pionka[4][4], int biezacy_gracz, int nr_pionka_rusza); // sprawdz ktorego pionka zbic YELLOW    (1-4) jesli 0 to nie ma bicia
int spr_bicie_g(int nr_gracza_i_nr_pionka[4][4], int biezacy_gracz, int nr_pionka_rusza); // sprawdz ktorego pionka zbic GREEN    (1-4) jesli 0 to nie ma bicia
int spr_bicie_b(int nr_gracza_i_nr_pionka[4][4], int biezacy_gracz, int nr_pionka_rusza); // sprawdz ktorego pionka zbic BLUE    (1-4) jesli 0 to nie ma bicia
int spr_bicie_r(int nr_gracza_i_nr_pionka[4][4], int biezacy_gracz, int nr_pionka_rusza); // sprawdz ktorego pionka zbic RED    (1-4) jesli 0 to nie ma bicia
int nastepny_gracz(int biezacy_gracz, int ilosc_graczy, int nr_gracza_i_nr_pionka[4][4]); // sprawdza kto nastepny (omija osoby ktore dojechaly do mety) 0 - Koniec gry

int main ()
{
	int nr_gracza_i_nr_pionka [4][4];  // [gracz], [pionek]
	int ilosc_graczy = 1; // od 1 do 4
	string imie_gracza [4] = {"Komp", "---", "---", "---" }; // jesli nie podamy imiona to beda kreski
	int biezacy_gracz = 1;  // Red, Blue, Green, Yellow o wartoœciach 1, 2, 3, 4
	char miejsca [4] = { '-', '-', '-', '-' }; // dla graczy: 1 - komp, 2 - gracz2, 3 - gracz3, 4 - gracz4
	int wylosowana_liczba = 1; // wylosowana wartoœæ przez kostke
	int i,j;
	int nr_pionka_rusza = 0; // od -1 (q) do 3  (jesli gracz wcisnie q to zamieni na wartosc "-1" i zakonczy gre. )
	int ile_rzutow [4] = { 1, 1, 1, 1 }; // rzuty 4 graczy - kazdy ma 1 rzut, jesli jest w starcie to zwiekszymy mu do 3 rzutow
	int wykorzystane_rzuty[4] = { 0, 0, 0, 0 }; // zapamietamy ile juz wykorzystal rzutow. Zero - jeszcze nie rzucil kostka
	int zbij_pionka = 0;
	int bitwa_o_miejsce = 1;
	
	wczytaj_imiona (ilosc_graczy, imie_gracza [1], imie_gracza [2], imie_gracza [3]);
	
	/*
	ilosc_graczy = 4;
	imie_gracza[0] ="KOMP";
	imie_gracza[1] ="gracz1";
	imie_gracza[2] ="gracz2";
	imie_gracza[3] ="gracz3";
	*/
	
	for (i=0; i<4; i++) 
		for (j=0; j<4; j++)
			nr_gracza_i_nr_pionka[i][j]= 0; //zerujemy pozycje 16-tu pionkow;
	
	/*
	// red - komputer
	nr_gracza_i_nr_pionka [0][0] = 1; //max44
	nr_gracza_i_nr_pionka [0][1] = 2; //max43
	nr_gracza_i_nr_pionka [0][2] = 3; //max42
	nr_gracza_i_nr_pionka [0][3] = 4; //max41
	// blue - gracz1                
	nr_gracza_i_nr_pionka [1][0] = 5; //max44
	nr_gracza_i_nr_pionka [1][1] = 6; //max43
	nr_gracza_i_nr_pionka [1][2] = 7; //max42
	nr_gracza_i_nr_pionka [1][3] = 8; //max41
	// green - gracz2               
	nr_gracza_i_nr_pionka [2][0] = 9; //max44
	nr_gracza_i_nr_pionka [2][1] = 10; //max43
	nr_gracza_i_nr_pionka [2][2] = 11; //max42
	nr_gracza_i_nr_pionka [2][3] = 12; //max41 
	// yellow - gracz1              
	nr_gracza_i_nr_pionka [3][0] = 13; //max44
	nr_gracza_i_nr_pionka [3][1] = 14; //max43
	nr_gracza_i_nr_pionka [3][2] = 15; //max42
	nr_gracza_i_nr_pionka [3][3] = 16; //max41
	*/
	
	//jesli sa ustawione pionki to sprawdz kazdemu ile ma rzutow:
	for (i=1; i<5; i++)
		ile_rzutow[i-1] = sprawdz_ile_rzutow(i,nr_gracza_i_nr_pionka, wylosowana_liczba);  // ( wartosci rzutow od 1 do 3)
	
	
	// Glowny program w petli az sie zakonczy GRA (nacisniecie znaku: "q") :
	do
	{
		// czysci ekran w funkcji rysuj_plansze i rysuje plansze z ustawieniami pionkow
		rysuj_plansze(nr_gracza_i_nr_pionka);
		rysuj_status(nr_gracza_i_nr_pionka, ile_rzutow, biezacy_gracz, miejsca, imie_gracza, ilosc_graczy, wykorzystane_rzuty);
		wylosowana_liczba = rzuc_kostka(biezacy_gracz);
		if (wylosowana_liczba == 6)
			wykorzystane_rzuty[biezacy_gracz-1] = 1;
		else
			wykorzystane_rzuty[biezacy_gracz-1] ++;
		narysuj_kostke(wylosowana_liczba); // pokaz co wylosowal
		
		// sprawdz czy gracz powinien drugi raz rzucac kostka i wpisz mu ta wartosc w tabele
		ile_rzutow [biezacy_gracz-1] = sprawdz_ile_rzutow(biezacy_gracz, nr_gracza_i_nr_pionka, wylosowana_liczba);
		
		rysuj_plansze(nr_gracza_i_nr_pionka); //dodatkowo czysci plansze
		rysuj_status(nr_gracza_i_nr_pionka, ile_rzutow, biezacy_gracz, miejsca, imie_gracza, ilosc_graczy, wykorzystane_rzuty);
		narysuj_kostke(wylosowana_liczba);
		nr_pionka_rusza = spytaj_jakim_pionkiem_ruszyc(biezacy_gracz, nr_gracza_i_nr_pionka, imie_gracza);
		
		// sprawdz czy ruszyc o 1 czy o 6 (jesli stoimy na starcie to po wylosowaniu 6 ruszamy tylko o 1 )
		if (czy_pionek_moze_ruszyc(biezacy_gracz,nr_gracza_i_nr_pionka,wylosowana_liczba,nr_pionka_rusza) == 1 )
		{
			if (nr_gracza_i_nr_pionka[biezacy_gracz-1][nr_pionka_rusza] == 0 ) // jest w bazie
			{
				nr_gracza_i_nr_pionka[biezacy_gracz-1][nr_pionka_rusza] = nr_gracza_i_nr_pionka[biezacy_gracz-1][nr_pionka_rusza] + 1; // wychodzi z bazy
				// jesli mielismy 3 rzuty i za pierwszym razem wyrzucimy 6 to pozostale rzuty nam sie anuluja i mamy jeden wiecej za wyrzucona 6-tke
				wykorzystane_rzuty[biezacy_gracz-1] = 1;
				ile_rzutow[biezacy_gracz-1] = 2;
			}
			else
				nr_gracza_i_nr_pionka[biezacy_gracz-1][nr_pionka_rusza] = nr_gracza_i_nr_pionka[biezacy_gracz-1][nr_pionka_rusza] + wylosowana_liczba;	
		}
		
		
		// teraz sprawdz czy biezacy gracz ustawil sie na polu gdzie ktos stal. jesli tak to zbij i tamten wraca do bazy
		zbij_pionka = spr_bicie_r(nr_gracza_i_nr_pionka, biezacy_gracz, nr_pionka_rusza);
		if (zbij_pionka != 0 ) // zbijamy pionka Red
		{
			nr_gracza_i_nr_pionka[0][zbij_pionka-1] = 0;
		}
		zbij_pionka = spr_bicie_b(nr_gracza_i_nr_pionka, biezacy_gracz, nr_pionka_rusza);
		if (zbij_pionka != 0 ) // zbijamy pionka Blue
		{
			nr_gracza_i_nr_pionka[1][zbij_pionka-1] = 0;
		}
		zbij_pionka = spr_bicie_g(nr_gracza_i_nr_pionka, biezacy_gracz, nr_pionka_rusza);
		if (zbij_pionka != 0 ) // zbijamy pionka Green
		{
			nr_gracza_i_nr_pionka[2][zbij_pionka-1] = 0;
		}				
		zbij_pionka = spr_bicie_y(nr_gracza_i_nr_pionka, biezacy_gracz, nr_pionka_rusza);
		if (zbij_pionka != 0 ) // zbijamy pionka Yellow
		{
			nr_gracza_i_nr_pionka[3][zbij_pionka-1] = 0;
		}		
		
		// teraz sprawdz czy ktos wygral
		// najpierw sprawdzam wszystkie cztery pionki gracza biezacego
		if ( (nr_gracza_i_nr_pionka[biezacy_gracz-1][0]==44) and (nr_gracza_i_nr_pionka[biezacy_gracz-1][1]==43) and (nr_gracza_i_nr_pionka[biezacy_gracz-1][2]==42) and (nr_gracza_i_nr_pionka[biezacy_gracz-1][3]==41) )
		{
			// wszytkie pionki tego gracza sa na mecie, zgarnij wartosc: "bitwa_o_miejsce" 1, 2, 3 lub 4
			switch (bitwa_o_miejsce)
			{
				case 1:
					miejsca [biezacy_gracz-1] = '1';
					break;
				case 2:
					miejsca [biezacy_gracz-1] = '2';
					break;
				case 3:
					miejsca [biezacy_gracz-1] = '3';
					break;
				case 4:
					miejsca [biezacy_gracz-1] = '4';
					break;
			}
			bitwa_o_miejsce ++; // po zdobyciu pierwszego miejsca przez biezacego gracza zmienia sie na kolejne wolne
		}
		
		/* biezacy gracz
		   ma_rzutow:   wykorzystane_rzuty:
		   1			0			
		   1			1			nastepny gracz, wyzeruj wykorzystane
		   2			0
		   2			1
		   2			2			nastepny gracz, wyzeruj wykorzystane
		   3			0
		   3			1
		   3			2
		   3			3			nastepny gracz, wyzeruj wykorzystane
		*/
		
		if ( wykorzystane_rzuty[biezacy_gracz-1] >= ile_rzutow[biezacy_gracz-1]) // jesli wykorzystalismy juz wszystkie przyznane rzuty ( 1, 2 lub 3)
		{
			wykorzystane_rzuty[biezacy_gracz-1] = 0;
			biezacy_gracz = nastepny_gracz(biezacy_gracz,ilosc_graczy,nr_gracza_i_nr_pionka); // zwraca nam nastepnego gracza - gracze ktorzy skonczyli sa omijani	
		}
		
	} while (nr_pionka_rusza != -1);
	
	return 0;
}

void wczytaj_imiona (int & ilosc_graczy, string & gracz2, string & gracz3, string & gracz4)
{
	cout << "Gracz 1: Komp\n";
	
	while ( (ilosc_graczy < 2) or (ilosc_graczy > 4) )
	{
		cout << "\nPodaj ilosc wszystkich graczy (od 2 do 4): ";
		cin >> ilosc_graczy;
		if ( (ilosc_graczy < 2) or (ilosc_graczy > 4) )
			cout << "Niepoprawna ilosc.\n";
	}
	
	if ( ilosc_graczy == 2 )
	{
		cout << "Podaj nazwe gracza Blue: ";
		cin >> gracz2;
		cout << endl;
	}
	
	if ( ilosc_graczy == 3 )
	{
		cout << "Podaj nazwe gracza Blue: ";
		cin >> gracz2;
		cout << "Podaj nazwe gracza Green: ";
		cin >> gracz3;
		cout << endl;
	}
	
	if ( ilosc_graczy == 4 )
	{
		cout << "Podaj nazwe gracza Blue: ";
		cin >> gracz2;
		cout << "Podaj nazwe gracza Green: ";
		cin >> gracz3;
		cout << "Podaj nazwe gracza Yellow: ";
		cin >> gracz4;
		cout << endl;
	}
}

void rysuj_plansze(int g[4][4])
{
	/* tak bedzie wygladac: 
	cout << "[R1] [R2]              [  ]  [  ]  [  ] |             [B1] [B2]  \n";	
	cout << "[R3] [R4]              [  ]  [b ]  [  ] |             [B3] [B4]  \n";
	cout << "                       [  ]  [b ]  [  ] V                        \n";
	cout << " --->                  [  ]  [b ]  [  ]                          \n";
	cout << "[  ]  [  ]  [  ]  [  ] [  ]  [b ]  [  ]  [  ]  [  ]  [  ]  [  ]  \n";
	cout << "[  ]  [r ]  [r ]  [r ] [r ]        [g ]  [g ]  [g ]  [g ]  [  ]  \n";
	cout << "[  ]  [  ]  [  ]  [  ] [  ]  [y ]  [  ]  [  ]  [  ]  [  ]  [  ]  \n";
	cout << "                       [  ]  [y ]  [  ]                   <---   \n";
	cout << "                     ^ [  ]  [y ]  [  ]                          \n";
	cout << "[Y1] [Y2]            | [  ]  [y ]  [  ]               [G1] [G2]  \n";
	cout << "[Y3] [Y4]            | [  ]  [  ]  [  ]               [G3] [G4]  \n";
	*/
	
	/* numeracja pol:
	cout << "[ 0] [ 0]              [ 9]  [10]  [11] |             [ 0] [ 0]  \n";	
	cout << "[ 0] [ 0]              [ 8]  [b ]  [12] |             [ 0] [ 0]  \n";
	cout << "                       [ 7]  [b ]  [13] V                        \n";
	cout << " --->                  [ 6]  [b ]  [14]                          \n";
	cout << "[ 1]  [ 2]  [ 3]  [ 4] [ 5]  [b ]  [15]  [16]  [17]  [18]  [19]  \n";
	cout << "[40]  [r ]  [r ]  [r ] [r ]        [g ]  [g ]  [g ]  [g ]  [20]  \n";
	cout << "[39]  [38]  [37]  [36] [35]  [y ]  [25]  [24]  [23]  [22]  [21]  \n";
	cout << "                       [34]  [y ]  [26]                   <---   \n";
	cout << "                     ^ [33]  [y ]  [27]                          \n";
	cout << "[ 0] [ 0]            | [32]  [y ]  [28]               [ 0] [ 0]  \n";
	cout << "[ 0] [ 0]            | [31]  [30]  [29]               [ 0] [ 0]  \n";
	*/
	
	// g - oznacza nr_gracza_i_nr_pionka[4][4]
	
	system( "cls" );
	cout << "Chinczyk - Aleksandra Rykowska 2020\n\n";
	
	//cout << "[R1] [R2]              [ 9]  [10]  [11] |             [B1] [B2]  \n";
	cout << "[";
	if (g[0][0] == 0 ) 
		cout << "R1";
	else 
		cout << "r ";
	cout << "] [";
	if (g[0][1] == 0 ) 
	    cout << "R2";
	else 
	    cout << "r ";
	cout << "]              [";
	narysuj_pionek(9, g);  // sprawdz jaki kolor (gracza) jest na polu 9 i narysuj pionka
	cout << "]  [";
	narysuj_pionek(10, g);
	cout << "]  [";
	narysuj_pionek(11, g);
	cout << "] |             [";
	if (g[1][0] == 0 )
		cout << "B1";
	else 
		cout << "b ";
	cout << "] [";
	if (g[1][1] == 0 )
	   	cout << "B2";
	else 
		cout << "b ";
	cout << "]  \n";		
	
	//cout << "[R3] [R4]              [ 8]  [b ]  [12] |             [B3] [B4]  \n";
	cout << "[";
	if (g[0][2] == 0 )
		cout << "R3";
	else 
		cout << "r ";
	cout << "] [";
	if (g[0][3] == 0 )
	    cout << "R4";
	else
	    cout << "r ";     
	cout << "]              [";
    narysuj_pionek(8, g);
    cout << "]  [";
	narysuj_pionek_b(41, g); //
	cout << "]  [";
	narysuj_pionek(12, g); //
	cout << "] |             [";
	if (g[1][2] == 0 )
		cout << "B3";
	else 
		cout << "b ";
	cout << "] [";
	if (g[1][3] == 0 ) 
		cout << "B4";
	else 
		cout << "b ";
	cout << "]  \n";		  

    //cout << "                       [ 7]  [b ]  [13] V                        \n";
	cout << "                       [";
    narysuj_pionek(7, g);
    cout << "]  [";
	narysuj_pionek_b(42, g);
	cout << "]  [";
	narysuj_pionek(13, g);
	cout << "] V                        \n";
 
  
    //cout << " --->                  [ 6]  [b ]  [14]                          \n";	
	cout << " --->                  [";
    narysuj_pionek(6, g);
    cout << "]  [";
	narysuj_pionek_b(43, g);
	cout << "]  [";
	narysuj_pionek(14, g);
	cout << "]                          \n";
  
    //cout << "[ 1]  [ 2]  [ 3]  [ 4] [ 5]  [b ]  [15]  [16]  [17]  [18]  [19]  \n";						                  
    cout << "[";
    narysuj_pionek(1, g);
	cout << "]  [";
    narysuj_pionek(2, g);
    cout << "]  [";
    narysuj_pionek(3, g);
    cout << "]  [";
   	narysuj_pionek(4, g);
   	cout << "] [";
   	narysuj_pionek(5, g);
   	cout << "]  [";
   	narysuj_pionek_b(44, g);
	cout << "]  [";
	narysuj_pionek(15, g);
	cout << "]  [";
	narysuj_pionek(16, g);
	cout << "]  [";
	narysuj_pionek(17, g);
	cout << "]  [";   
	narysuj_pionek(18, g);
	cout << "]  [";
	narysuj_pionek(19, g);
	cout << "]  \n"; 																	     
   			
    //cout << "[40]  [r ]  [r ]  [r ] [r ]        [g ]  [g ]  [g ]  [g ]  [20]  \n";
    cout << "[";
    narysuj_pionek(40, g);  
    cout << "]  [";
	narysuj_pionek_r(41, g);
    cout << "]  [";
    narysuj_pionek_r(42, g);
    cout << "]  [";
    narysuj_pionek_r(43, g);
    cout << "] [";
    narysuj_pionek_r(44, g);
    cout << "]        [";
    narysuj_pionek_g(44, g);
	cout << "]  [";
	narysuj_pionek_g(43, g);
	cout << "]  [";
	narysuj_pionek_g(42, g);
	cout << "]  [";
	narysuj_pionek_g(41, g);
	cout << "]  [";
	narysuj_pionek(20, g);
	cout << "]  \n";
              			  
    //cout << "[39]  [38]  [37]  [36] [35]  [y ]  [25]  [24]  [23]  [22]  [21]  \n";
    cout << "[";
    narysuj_pionek(39, g);
    cout << "]  [";
    narysuj_pionek(38, g);
    cout << "]  [";
    narysuj_pionek(37, g);
    cout << "]  [";
   	narysuj_pionek(36, g);
   	cout << "] [";
   	narysuj_pionek(35, g);
   	cout << "]  [";
   	narysuj_pionek_y(44, g);
	cout << "]  [";
	narysuj_pionek(25, g);
	cout << "]  [";
	narysuj_pionek(24, g);
	cout << "]  [";
	narysuj_pionek(23, g);
	cout << "]  [";
	narysuj_pionek(22, g);
	cout << "]  [";
	narysuj_pionek(21, g);
	cout << "]  \n";

     //cout << "                       [34]  [y ]  [26]                   <---   \n";	
	cout << "                       [";
    narysuj_pionek(34, g);
    cout << "]  [";
	narysuj_pionek_y(43, g);
	cout << "]  [";
	narysuj_pionek(26, g);
	cout << "]                   <---\n";

    //cout << "                     ^ [33]  [y ]  [27]                          \n";
  	cout << "                     ^ [";
    narysuj_pionek(33, g);
    cout << "]  [";
	narysuj_pionek_y(42, g);
	cout << "]  [";
	narysuj_pionek(27, g);
	cout << "]  \n";
  
    //cout << "[Y1] [Y2]            | [32]  [y ]  [28]               [G1] [G2]  \n";  
	cout << "[";
	if (g[3][0] == 0 )
		cout << "Y1";
	else
		cout << "y ";
	cout << "] [";
	if (g[3][1] == 0 )
	    cout << "Y2";
	else
	    cout << "y ";
	cout << "]            | [";
    narysuj_pionek(32, g);
    cout << "]  [";
	narysuj_pionek_y(41, g);
	cout << "]  [";
	narysuj_pionek(28, g);
	cout << "]               [";
	if (g[2][0] == 0 )
		cout << "G1";
	else
		cout << "g ";
	cout << "] [";
	if (g[2][1] == 0 )
		cout << "G2";
	else
		cout << "g ";
	cout << "]  \n";

    //cout << "[Y3] [Y4]            | [31]  [30]  [29]               [G3] [G4]  \n";
	cout << "[";
	if (g[3][2] == 0 )
		cout << "Y3";
	else
		cout << "y ";
	cout << "] [";
	if (g[3][3] == 0 )
	    cout << "Y4";
	else
	    cout << "y ";
	cout << "]            | [";
    narysuj_pionek(31, g);
    cout << "]  [";
	narysuj_pionek(30, g);
	cout << "]  [";
	narysuj_pionek(29, g);
	cout << "]               [";
	if (g[2][2] == 0 )
		cout << "G3";
	else
		cout << "g ";
	cout << "] [";
	if (g[2][3] == 0 )
		cout << "G4";
	else
		cout << "g ";
	cout << "]  \n";
 	cout << "\n";
}

void narysuj_pionek(int pole, int g[4][4])
{
	/*	
	pozycje pol bialych:
	plansza nr :     1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40
	
	Red    gracz1:   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40
	Blue   gracz2:  31  32  33  34  35  36  37  38  39  40   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30
	Green  gracz3:  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20
	Yellow gracz4:  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40   1   2   3   4   5   6   7   8   9  10
	*/
	// g - tablica nr_gracza_i_nr_pionka
	int x = 0;
	x = pole;
	if ( (g[0][0]==x) or (g[0][1]==x) or (g[0][2]==x )or (g[0][3]==x) )
	{
		cout << "R";
		if (g[0][0]==x) cout << "1";
		if (g[0][1]==x) cout << "2";
		if (g[0][2]==x) cout << "3";
		if (g[0][3]==x) cout << "4";
	}
	else
	{
		x = pole; // dla Blue jest liczba o 30 wieksza 
		x = x + 30;
		if (x > 40 )
			x = x - 40;   
		if ( (g[1][0]==x) or (g[1][1]==x) or (g[1][2]==x )or (g[1][3]==x) )
		{
			cout << "B";
			if (g[1][0]==x) cout << "1";
			if (g[1][1]==x) cout << "2";
			if (g[1][2]==x) cout << "3";
			if (g[1][3]==x) cout << "4";			
		}
		else
		{
			x = pole; // dla Green jest liczba o 20 wieksza
			x = x + 20;
			if (x > 40 )
				x = x - 40;
			if ( (g[2][0]==x) or (g[2][1]==x) or (g[2][2]==x )or (g[2][3]==x) )
			{
				cout << "G";
				if (g[2][0]==x) cout << "1";
				if (g[2][1]==x) cout << "2";
				if (g[2][2]==x) cout << "3";
				if (g[2][3]==x) cout << "4";					
			}
			else
			{
				x = pole; // dla Yellow jest liczba o 10 wieksza
				x = x + 10;
				if (x > 40 )
					x = x - 40;
				if ( (g[3][0]==x) or (g[3][1]==x) or (g[3][2]==x )or (g[3][3]==x) )
				{
					cout << "Y";		
					if (g[3][0]==x) cout << "1";
					if (g[3][1]==x) cout << "2";
					if (g[3][2]==x) cout << "3";
					if (g[3][3]==x) cout << "4";				
				}
				else
					cout << "  "; // jezeli zaden z 16 pionkow nie stoi na polu to pole jest puste "  "
			}
		}
	}
}

void narysuj_pionek_r(int pole, int g[4][4])
{
	// stosowane dla pola = 41, 42, 43, 44 tylko
	int x = pole;
	if (g[0][0]==x)
		cout << "R1"; 
	else 
		if (g[0][1]==x)
			cout << "R2";
		else 
			if (g[0][2]==x)
				cout << "R3";
			else 
				if (g[0][3]==x)
					cout << "R4";
				else
					cout <<"r ";
}

void narysuj_pionek_b(int pole, int g[4][4])
{
	// stosowane dla pola = 41, 42, 43, 44 tylko
	int x = pole;
	if (g[1][0]==x)
		cout << "B1"; 
	else 
		if (g[1][1]==x)
		 	cout << "B2";
		else 
			if (g[1][2]==x)
				cout << "B3";
			else 
				if (g[1][3]==x)
					cout << "B4";
				else
					cout <<"b ";
}

void narysuj_pionek_g(int pole, int g[4][4])
{
	// stosowane dla pola = 41, 42, 43, 44 tylko
	int x = pole;
	if (g[2][0]==x)
		cout << "G1"; 
	else 
		if (g[2][1]==x)
			cout << "G2";
		else 
			if (g[2][2]==x)
				cout << "G3";
			else 
				if (g[2][3]==x)
					cout << "G4";
				else
					cout <<"g ";
}

void narysuj_pionek_y(int pole, int g[4][4])
{
	// stosowane dla pola = 41, 42, 43, 44 tylko
	int x = pole;
	if (g[3][0]==x)
		cout << "Y1"; 
	else 
		if (g[3][1]==x)
			cout << "Y2";
		else 
			if (g[3][2]==x)
				cout << "Y3";
			else 
				if (g[3][3]==x)
					cout << "Y4";
				else
					cout <<"y ";
}

void rysuj_status(int g[4][4], int ile_rzutow [4], int biezacy_gracz, char miejsca[4], string imie_gracza [4], int ilosc_graczy, int wykorzystane_rzuty[4])
{
	cout << "Status:\n";
	cout << "Max  44        43        42        41   Rzuty/Wykorzystane:  Kolejka:  Miejsce:  Nazwa:\n";
	
	//cout << "R1 = 00;  R2 = 00;  R3 = 00;  R4 = 00;        3/1             <---      -         COMP\n";
	cout << "R1 = ";
	cout << setw(2);
	cout << g[0][0];
	cout << ";  R2 = ";
	cout << setw(2);
	cout << g[0][1];
	cout << ";  R3 = ";
	cout << setw(2);
	cout << g[0][2];
	cout << ";  R4 = ";
	cout << setw(2);
	cout << g[0][3];
	cout << setw(8);
	cout << ile_rzutow [0];
	cout << "/";
	cout << wykorzystane_rzuty[0];
	cout << setw(20);
	if ( biezacy_gracz == 1)
		cout << "<---";
	else 
		cout << " ";
	cout << setw(11);
	cout << miejsca [0];
	cout << setw(3);
	cout << " ";
	cout << imie_gracza [0];
	cout << endl;
	
	//cout << "B1 = 00;  B2 = 00;  B3 = 00;  B4 = 00;            -         gracz1\n";
	cout << "B1 = ";
	cout << setw(2);
	cout << g[1][0];
	cout << ";  B2 = ";
	cout << setw(2);
	cout << g[1][1];
	cout << ";  B3 = ";
	cout << setw(2);
	cout << g[1][2];
	cout << ";  B4 = ";
	cout << setw(2);
	cout << g[1][3];
	cout << setw(8);
	cout << ile_rzutow [1];
	cout << "/";
	cout << wykorzystane_rzuty[1];
	cout << setw(20);
	if ( biezacy_gracz == 2)
		cout << "<---";
	else 
		cout << " ";
	cout << setw(11);
	cout << miejsca [1];
	cout << setw(3);
	cout << " ";
	cout << imie_gracza [1];
	cout << endl;
	
	if ( ilosc_graczy > 2 )
	{
		//cout << "G1 = 00;  G2 = 00;  G3 = 00;  G4 = 00;            -         gracz2\n";
		cout << "G1 = ";
		cout << setw(2);
		cout << g[2][0];
		cout << ";  G2 = ";
		cout << setw(2);
		cout << g[2][1];
		cout << ";  G3 = ";
		cout << setw(2);
		cout << g[2][2];
		cout << ";  G4 = ";
		cout << setw(2);
		cout << g[2][3];
		cout << setw(8);
		cout << ile_rzutow [2];
		cout << "/";
		cout << wykorzystane_rzuty[2];
		cout << setw(20);
		if ( biezacy_gracz == 3)
			cout << "<---";
		else 
			cout << " ";
		cout << setw(11);
		cout << miejsca [2];
		cout << setw(3);
		cout << " ";
		cout << imie_gracza [2];
		cout << endl;
	}
	
	
	if ( ilosc_graczy == 4 )
	{
		//cout << "Y1 = 00;  Y2 = 00;  Y3 = 00;  Y4 = 00;            -         gracz3\n";
		cout << "Y1 = ";
		cout << setw(2);
		cout << g[3][0];
		cout << ";  Y2 = ";
		cout << setw(2);
		cout << g[3][1];
		cout << ";  Y3 = ";
		cout << setw(2);
		cout << g[3][2];
		cout << ";  Y4 = ";
		cout << setw(2);
		cout << g[3][3];
		cout << setw(8);
		cout << ile_rzutow [3];
		cout << "/";
		cout << wykorzystane_rzuty[3];
		cout << setw(20);
		if ( biezacy_gracz == 4)
			cout << "<---";
		else 
			cout << " ";
		cout << setw(11);
		cout << miejsca [3];
		cout << setw(3);
		cout << " ";
		cout << imie_gracza [3];
		cout << endl;
	}
	cout << endl;
}

int rzuc_kostka(int biezacy_gracz)
{
	int los = 1;
	if (biezacy_gracz == 1 )
		cout << "Komputer bedzie teraz rzucac kostka. Nacisnij Enter";
	else
		cout << "Nacisnij Enter by rzucic kostka";
	cin.get();
	srand( time( NULL ) );
	los =  rand() % MAX_KOSTKA + 1;
	
	return los; // funkcja bedzie nam zwaracala jaka liczbe wylosowala
}

void narysuj_kostke(int los)
{
	cout << "Rzut kostka:  " << los << "\n";
	switch (los)
	{
		case 1:
			cout << " _______ \n";
			cout << "|       |\n";
			cout << "|   X   |\n";
			cout << "|       |\n";			
			cout << " ------- \n";
			break;
		case 2:
			cout << " _______ \n";
			cout << "|       |\n";
			cout << "| X   X |\n";
			cout << "|       |\n";			
			cout << " ------- \n";
			break;
		case 3:
			cout << " _______ \n";
			cout << "| X     |\n";
			cout << "|   X   |\n";
			cout << "|     X |\n";			
			cout << " ------- \n";
			break;
		case 4:
			cout << " _______ \n";
			cout << "| X   X |\n";
			cout << "|       |\n";
			cout << "| X   X |\n";			
			cout << " ------- \n";
			break;
		case 5:
			cout << " _______ \n";
			cout << "| X   X |\n";
			cout << "|   X   |\n";
			cout << "| X   X |\n";			
			cout << " ------- \n";
			break;
		case 6:
			cout << " _______ \n";
			cout << "| X   X |\n";
			cout << "| X   X |\n";
			cout << "| X   X |\n";			
			cout << " ------- \n";
			break;
	}
}

int sprawdz_ile_rzutow(int biezacy_gracz, int nr_gracza_i_nr_pionka[4][4], int wylosowana_liczba)
{
	int p1, p2, p3, p4, rzutow;
	//pionki biezacego gracza
	p1 = nr_gracza_i_nr_pionka[biezacy_gracz-1][0];
	p2 = nr_gracza_i_nr_pionka[biezacy_gracz-1][1];
	p3 = nr_gracza_i_nr_pionka[biezacy_gracz-1][2];
	p4 = nr_gracza_i_nr_pionka[biezacy_gracz-1][3];
	rzutow = 1; // domyslnie jeden rzut ma gracz w kolejce
	// jesli wyrzucil 6 to ustaw 2 i juz nie sprawdzaj ponizej warunkow:
	if (wylosowana_liczba == 6)
		rzutow = 2;
	else // jesli wylosowal mniej niz 6 ale nie ma pionka na polu od 1 do 41, 42, 43 lub 44 to ustaw na 3
	{
		if( ( (p1==0)or(p1==44) ) and  ( (p2==0)or(p2==43) ) and ( (p3==0)or(p3==42) ) and ( (p4==0)or(p4==41) ) )
		// nie ma zadnego pionka na polu miedzy startem a meta, wiec daj mu 3 rzuty
			rzutow = 3;
	}

	return rzutow;
}

int spytaj_jakim_pionkiem_ruszyc(int biezacy_gracz, int nr_gracza_i_nr_pionka[4][4], string imie_gracza[4])
{
	int tmp; // tymczasowa
	char znak;

	if (biezacy_gracz == 1)
	{
		// komputer ruszy nastepnym jak biezacym pionkiem dojedzie do mety
		if (nr_gracza_i_nr_pionka[0][0] < 44) 
		{
			znak = '1'; 
			cout << "Komputer zdecydowal ze ruszy pionkiem 1. Nacisnij enter, aby kontynuowac. ";
		}
		else
		{	
			if (nr_gracza_i_nr_pionka[0][1] < 43)
			{
				znak = '2';
				cout << "Komputer zdecydowal ze ruszy pionkiem 2. Nacisnij enter, aby kontynuowac. ";
			}
			else
			{
				if (nr_gracza_i_nr_pionka[0][2] < 42)
				{
					znak = '3';
					cout << "Komputer zdecydowal ze ruszy pionkiem 3. Nacisnij enter, aby kontynuowac. ";
				}
				else
				{
					if (nr_gracza_i_nr_pionka[0][3] < 41)
					{
						znak = '4';
						cout << "Komputer zdecydowal ze ruszy pionkiem 4. Nacisnij enter, aby kontynuowac. ";
					}
				}
			}
		}
		cin.get();
	}
	else
	{
		cout << imie_gracza[biezacy_gracz-1];
		if (biezacy_gracz == 2)
			cout << " (B - Blue)";
		else
			if (biezacy_gracz == 3)
				cout << " (G - Green)";
			else
				if (biezacy_gracz == 4)
					cout << " (Y - Yellow)";
		
		cout << " ktorym pionkiem ruszyc? <1>, <2>, <3>, <4>, <q>: ";
		cin >> znak;
	}
	
	switch (znak)
	{
		case '1':
			tmp = 0;
			break;
		case '2':
			tmp = 1;
			break;
		case '3':
			tmp = 2;
			break;
		case '4':
			tmp = 3;
			break;
		case 'q':	// jesli podamy q to zakonczy program
			tmp = -1;
			break;			
		default:	// jesli bzdure podamy to ruszy pionkiem 1
			tmp = 0;
			break;
	}
	return tmp;
}

int czy_pionek_moze_ruszyc(int biezacy_gracz, int nr_gracza_i_nr_pionka[4][4], int wylosowana_liczba, int nr_pionka_rusza)
{
	// pionek 0-3 
	int poz; // pozycja pionka gracza do sprawdzenia
	int pionek_moze = 0;  // jesli 0 - to nie moze ruszyc  // jesli 1 - to moze ruszyc	  
	poz = nr_gracza_i_nr_pionka[biezacy_gracz-1][nr_pionka_rusza];
	
	// sprawdzmy czy moze ruszyc pionek
	if (( wylosowana_liczba == 6 ) and ( poz < (45 - wylosowana_liczba - nr_pionka_rusza) ) ) // dla wszystkich pionkow lacznie z baza
		pionek_moze = 1; // mozna ruszyc kostka 1
	if (( wylosowana_liczba < 6 ) and (poz > 0) and (poz < (45 - wylosowana_liczba - nr_pionka_rusza) )) // dla pionkow poza baza
		pionek_moze = 1; // mozna ruszyc kostka
	
	return pionek_moze;
}

int spr_bicie_y(int nr_gracza_i_nr_pionka[4][4], int biezacy_gracz, int nr_pionka_rusza) // sprawdzamy, którego pionka zbiæ zoltemu
{
	/*	
	pozycje pol bialych:
	plansza nr :     1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40
	
	Red    gracz1:   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40
	Blue   gracz2:  31  32  33  34  35  36  37  38  39  40   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30
	Green  gracz3:  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20
	Yellow gracz4:  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40   1   2   3   4   5   6   7   8   9  10
	*/
	
	int zbij = 0; // domyslnie ustawiamy ze nikogo nie zbijamy
	int i;
	int poz_pio_bije; // pozycja pionka ktory ruszyl i sprawdzimy czy kogos zbija
	poz_pio_bije = nr_gracza_i_nr_pionka[biezacy_gracz-1][nr_pionka_rusza];
	
	if ( (biezacy_gracz == 1) and (poz_pio_bije > 0) and (poz_pio_bije < 41) ) //sprawdz czy Red zbija jakiegos pionka Yellow
	{ 
		poz_pio_bije = poz_pio_bije + 10; // pozycja Red jest przesunieta o 10 wzgledem Yellow
		if (poz_pio_bije > 40 )
			poz_pio_bije = poz_pio_bije - 40; // jesli poza dopuszczalnym polem to skoryguj o 40
		for (i=0; i<4; i++) // sprawdzamy dla wszystich 4 pionkow Yellow
		{
			if (poz_pio_bije == nr_gracza_i_nr_pionka[3][i] ) 
				zbij = i + 1; // 1 - zbij Y1, 2 - zbij Y2 itd...
		}
	}
	
	if ( (biezacy_gracz == 2) and (poz_pio_bije > 0) and (poz_pio_bije < 41) ) //sprawdz czy Blue zbija jakiegos pionka Yellow
	{ 
		poz_pio_bije = poz_pio_bije + 20; // pozycja Blue jest przesunieta o 20 wzgledem Yellow
		if (poz_pio_bije > 40 )
			poz_pio_bije = poz_pio_bije - 40; // jesli poza dopuszczalnym polem to skoryguj o 40
		for (i=0; i<4; i++) // sprawdzamy dla wszystich 4 pionkow Yellow
		{
			if (poz_pio_bije == nr_gracza_i_nr_pionka[3][i] ) 
				zbij = i + 1;
		}
	}	
	
	if ( (biezacy_gracz == 3) and (poz_pio_bije > 0) and (poz_pio_bije < 41) ) //sprawdz czy Green zbija jakiegos pionka Yellow
	{ 
		poz_pio_bije = poz_pio_bije + 30; // pozycja Green jest przesunieta o 30 wzgledem Yellow
		if (poz_pio_bije > 40 )
			poz_pio_bije = poz_pio_bije - 40; // jesli poza dopuszczalnym polem to skoryguj o 40
		for (i=0; i<4; i++) // sprawdzamy dla wszystich 4 pionkow Yellow
		{
			if (poz_pio_bije == nr_gracza_i_nr_pionka[3][i] ) 
				zbij = i + 1;
		}
	}	
	return zbij;
}

int spr_bicie_g(int nr_gracza_i_nr_pionka[4][4], int biezacy_gracz, int nr_pionka_rusza) // sprawdzamy, którego pionka zbiæ zielonemu
{
	/*	
	pozycje pol bialych:
	plansza nr :     1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40
	
	Red    gracz1:   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40
	Blue   gracz2:  31  32  33  34  35  36  37  38  39  40   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30
	Green  gracz3:  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20
	Yellow gracz4:  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40   1   2   3   4   5   6   7   8   9  10
	*/
	
	int zbij = 0; // domyslnie ustawieamy ze nikogo nie zbijamy
	int i;
	int poz_pio_bije; // pozycja pionka ktory ruszyl i sprawdzimy czy kogos zbija
	poz_pio_bije = nr_gracza_i_nr_pionka[biezacy_gracz-1][nr_pionka_rusza];

	if ( (biezacy_gracz == 4) and (poz_pio_bije > 0) and (poz_pio_bije < 41) ) //sprawdz czy Yellow zbija jakiegos pionka Green
	{ 
		poz_pio_bije = poz_pio_bije + 10; // pozycja Yellow jest przesunieta o 10 wzgledem Green
		if (poz_pio_bije > 40 )
			poz_pio_bije = poz_pio_bije - 40; // jesli poza dopuszczalnym polem to skoryguj o 40
		for (i=0; i<4; i++) // sprawdzamy dla wszystich 4 pionkow Green
		{
			if (poz_pio_bije == nr_gracza_i_nr_pionka[2][i] ) 
				zbij = i + 1;
		}
	}
	
	if ( (biezacy_gracz == 1) and (poz_pio_bije > 0) and (poz_pio_bije < 41) ) //sprawdz czy Red zbija jakiegos pionka Green
	{ 
		poz_pio_bije = poz_pio_bije + 20; // pozycja Red jest przesunieta o 20 wzgledem Green
		if (poz_pio_bije > 40 )
			poz_pio_bije = poz_pio_bije - 40; // jesli poza dopuszczalnym polem to skoryguj o 40
		for (i=0; i<4; i++) // sprawdzamy dla wszystich 4 pionkow Green
		{
			if (poz_pio_bije == nr_gracza_i_nr_pionka[2][i] ) 
				zbij = i + 1;
		}
	}	
	
	if ( (biezacy_gracz == 2) and (poz_pio_bije > 0) and (poz_pio_bije < 41) ) //sprawdz czy Blue zbija jakiegos pionka Green
	{ 
		poz_pio_bije = poz_pio_bije + 30; // pozycja Blue jest przesunieta o 30 wzgledem Green
		if (poz_pio_bije > 40 )
			poz_pio_bije = poz_pio_bije - 40; // jesli poza dopuszczalnym polem to skoryguj o 40
		for (i=0; i<4; i++) // sprawdzamy dla wszystich 4 pionkow Green
		{
			if (poz_pio_bije == nr_gracza_i_nr_pionka[2][i] ) 
				zbij = i + 1;
		}
	}	
	return zbij;
}

int spr_bicie_b(int nr_gracza_i_nr_pionka[4][4], int biezacy_gracz, int nr_pionka_rusza) // sprawdzamy, którego pionka zbiæ niebieskiemu
{
	/*	
	pozycje pol bialych:
	plansza nr :     1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40
	
	Red    gracz1:   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40
	Blue   gracz2:  31  32  33  34  35  36  37  38  39  40   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30
	Green  gracz3:  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20
	Yellow gracz4:  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40   1   2   3   4   5   6   7   8   9  10
	*/
	
	int zbij = 0; // domyslnie ustawieamy ze nikogo nie zbijamy
	int i;
	int poz_pio_bije; // pozycja pionka ktory ruszyl i sprawdzimy czy kogos zbija
	poz_pio_bije = nr_gracza_i_nr_pionka[biezacy_gracz-1][nr_pionka_rusza];

	if ( (biezacy_gracz == 3) and (poz_pio_bije > 0) and (poz_pio_bije < 41) ) //sprawdz czy Green zbija jakiegos pionka Blue
	{ 
		poz_pio_bije = poz_pio_bije + 10; // pozycja Blue jest przesunieta o 10 wzgledem Blue
		if (poz_pio_bije > 40 )
			poz_pio_bije = poz_pio_bije - 40; // jesli poza dopuszczalnym polem to skoryguj o 40
		for (i=0; i<4; i++) // sprawdzamy dla wszystich 4 pionkow Red
		{
			if (poz_pio_bije == nr_gracza_i_nr_pionka[1][i] ) 
				zbij = i + 1;
		}
	}
	
	if ( (biezacy_gracz == 4) and (poz_pio_bije > 0) and (poz_pio_bije < 41) ) //sprawdz czy Yellow zbija jakiegos pionka Blue
	{ 
		poz_pio_bije = poz_pio_bije + 20; // pozycja Green jest przesunieta o 20 wzgledem Blue
		if (poz_pio_bije > 40 )
			poz_pio_bije = poz_pio_bije - 40; // jesli poza dopuszczalnym polem to skoryguj o 40
		for (i=0; i<4; i++) // sprawdzamy dla wszystich 4 pionkow Red
		{
			if (poz_pio_bije == nr_gracza_i_nr_pionka[1][i] ) 
				zbij = i + 1;
		}
	}	
	
	if ( (biezacy_gracz == 1) and (poz_pio_bije > 0) and (poz_pio_bije < 41) ) //sprawdz czy Red zbija jakiegos pionka Blue
	{ 
		poz_pio_bije = poz_pio_bije + 30; // pozycja Yellow jest przesunieta o 30 wzgledem Blue
		if (poz_pio_bije > 40 )
			poz_pio_bije = poz_pio_bije - 40; // jesli poza dopuszczalnym polem to skoryguj o 40
		for (i=0; i<4; i++) // sprawdzamy dla wszystich 4 pionkow Red
		{
			if (poz_pio_bije == nr_gracza_i_nr_pionka[1][i] ) 
				zbij = i + 1;
		}
	}	
	return zbij;
}

int spr_bicie_r(int nr_gracza_i_nr_pionka[4][4], int biezacy_gracz, int nr_pionka_rusza) // sprawdzamy, którego pionka zbiæ czerwonemu
{
	/*	
	pozycje pol bialych:
	plansza nr :     1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40
	
	Red    gracz1:   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40
	Blue   gracz2:  31  32  33  34  35  36  37  38  39  40   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30
	Green  gracz3:  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20
	Yellow gracz4:  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40   1   2   3   4   5   6   7   8   9  10
	*/
	
	int zbij = 0; // domyslnie ustawiamy ze nikogo nie zbijamy
	int i;
	int poz_pio_bije; // pozycja pionka ktory ruszyl i sprawdzimy czy kogos zbija
	poz_pio_bije = nr_gracza_i_nr_pionka[biezacy_gracz-1][nr_pionka_rusza];

	if ( (biezacy_gracz == 2) and (poz_pio_bije > 0) and (poz_pio_bije < 41) ) //sprawdz czy Blue zbija jakiegos pionka Red
	{ 
		poz_pio_bije = poz_pio_bije + 10; // pozycja Blue jest przesunieta o 10 wzgledem Red
		if (poz_pio_bije > 40 )
			poz_pio_bije = poz_pio_bije - 40; // jesli poza dopuszczalnym polem to skoryguj o 40
		for (i=0; i<4; i++) // sprawdzamy dla wszystich 4 pionkow Red
		{
			if (poz_pio_bije == nr_gracza_i_nr_pionka[0][i] ) 
				zbij = i + 1;
		}
	}
	
	if ( (biezacy_gracz == 3) and (poz_pio_bije > 0) and (poz_pio_bije < 41) ) //sprawdz czy Green zbija jakiegos pionka Red
	{ 
		poz_pio_bije = poz_pio_bije + 20; // pozycja Green jest przesunieta o 20 wzgledem Red
		if (poz_pio_bije > 40 )
			poz_pio_bije = poz_pio_bije - 40; // jesli poza dopuszczalnym polem to skoryguj o 40
		for (i=0; i<4; i++) // sprawdzamy dla wszystich 4 pionkow Red
		{
			if (poz_pio_bije == nr_gracza_i_nr_pionka[0][i] ) 
				zbij = i + 1;
		}
	}	
	
	if ( (biezacy_gracz == 4) and (poz_pio_bije > 0) and (poz_pio_bije < 41) ) //sprawdz czy Yellow zbija jakiegos pionka Red
	{ 
		poz_pio_bije = poz_pio_bije + 30; // pozycja Yellow jest przesunieta o 30 wzgledem Red
		if (poz_pio_bije > 40 )
			poz_pio_bije = poz_pio_bije - 40; // jesli poza dopuszczalnym polem to skoryguj o 40
		for (i=0; i<4; i++) // sprawdzamy dla wszystich 4 pionkow Red
		{
			if (poz_pio_bije == nr_gracza_i_nr_pionka[0][i] ) 
				zbij = i + 1;
		}
	}	
	return zbij;
}

int nastepny_gracz(int biezacy_gracz, int ilosc_graczy, int nr_gracza_i_nr_pionka[4][4])
{
	biezacy_gracz ++;
	if (biezacy_gracz > ilosc_graczy)
		biezacy_gracz = 1; // po ostatnim graczu bedzie pierwszy
	
	// sprawdz 1 raz czy osoba ktora ma teraz grac juz skonczyla gre i wszystkie pionki sa na mecie
	if ( (nr_gracza_i_nr_pionka[biezacy_gracz-1][0]==44) and (nr_gracza_i_nr_pionka[biezacy_gracz-1][1]==43) and (nr_gracza_i_nr_pionka[biezacy_gracz-1][2]==42) and (nr_gracza_i_nr_pionka[biezacy_gracz-1][3]==41) )
	{
		biezacy_gracz ++;
		if (biezacy_gracz > ilosc_graczy)
			biezacy_gracz = 1;
		// sprawdz 2 raz czy osoba ktora ma teraz grac juz skonczyla gre i wszystkie pionki sa na mecie
		if ( (nr_gracza_i_nr_pionka[biezacy_gracz-1][0]==44) and (nr_gracza_i_nr_pionka[biezacy_gracz-1][1]==43) and (nr_gracza_i_nr_pionka[biezacy_gracz-1][2]==42) and (nr_gracza_i_nr_pionka[biezacy_gracz-1][3]==41) )
		{
			biezacy_gracz ++;
			if (biezacy_gracz > ilosc_graczy)
				biezacy_gracz = 1;
			// sprawdz 3 raz czy osoba ktora ma teraz grac juz skonczyla gre i wszystkie pionki sa na mecie
			if ( (nr_gracza_i_nr_pionka[biezacy_gracz-1][0]==44) and (nr_gracza_i_nr_pionka[biezacy_gracz-1][1]==43) and (nr_gracza_i_nr_pionka[biezacy_gracz-1][2]==42) and (nr_gracza_i_nr_pionka[biezacy_gracz-1][3]==41) )	
			{
				biezacy_gracz ++;
				if (biezacy_gracz > ilosc_graczy)
					biezacy_gracz = 1;	
				// sprawdz 4 raz ostatni czy osoba ktora ma teraz grac juz skonczyla gre i wszystkie pionki sa na mecie
				// pytamy sami siebie ( zostal ostatni gracz ) czy jest na mecie i moze grac
				if ( (nr_gracza_i_nr_pionka[biezacy_gracz-1][0]==44) and (nr_gracza_i_nr_pionka[biezacy_gracz-1][1]==43) and (nr_gracza_i_nr_pionka[biezacy_gracz-1][2]==42) and (nr_gracza_i_nr_pionka[biezacy_gracz-1][3]==41) )
					return 0; // nikt juz nie gra . koniec gry
			}
		}
	}
	return biezacy_gracz;
}

#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include <time.h>


using namespace std;


const unsigned int N = 10;
const unsigned int M = 10;
const unsigned int K = 10;
const unsigned int L = 5;
const char nieznane = '#';
const char pudlo = '.';
const char jednomasztowiec = '1';
const char dwumasztowiec = '2';
const unsigned int MLP = 5;
const unsigned int MP = (K * 1) + (L * 2);
const unsigned int pusto = '0';
const unsigned int R = 10;

struct plansza {

	char pole_gry[N][M];
	char statki[N][M];

};

struct rekord {

	unsigned int miejsce;
	unsigned int wyniki_graczy;
	string gracze;

};

plansza gra;
rekord tablica[R];

void wypelnij_plansze_poczatkowa(plansza* p) {

	for (unsigned int i = 0; i < N; i++) {
		for (unsigned int j = 0; j < M; j++) {
			p->pole_gry[i][j] = nieznane;
		}
	}
}

void wyswietl_plansze(plansza* p) {

	for (unsigned int i = 0; i < N; i++) {
		for (unsigned int j = 0; j < M; j++) {
			if (j == 0) {
				cout << endl;
				cout << p->pole_gry[i][j];
			}
			else if ((i == (N - 1)) && (j == (M - 1))) {
				cout << p->pole_gry[i][j];
				cout << endl << endl;
			}
			else {
				cout << p->pole_gry[i][j];
			}
		}
	}
}


void wyswietl_statki(plansza* p) {

	for (unsigned int i = 0; i < N; i++) {
		for (unsigned int j = 0; j < M; j++) {


			if (j == 0) {
				cout << endl;
				if (p->statki[i][j] == '0') {
					cout << '.';
				}
				else {
					cout << p->statki[i][j];
				}
			}
			else if ((i == (N - 1)) && (j == (M - 1))) {
				if (p->statki[i][j] == '0') {
					cout << '.';
				}
				else
				{
					cout << p->statki[i][j];
				}
				cout << endl << endl;
			}
			else {
				if (p->statki[i][j] == '0') {
					cout << '.';
				}
				else
				{
					cout << p->statki[i][j];
				}
			}
		}
	}
}

void strzal(plansza* p, plansza* s, unsigned int* t, unsigned int* ch, unsigned int* pp) {

	int wysokosc;
	int szerokosc;
	cout << "Podaj wysokosc strzalu (1-" << N << "): ";
	cin >> wysokosc;
	wysokosc = wysokosc - 1;
	cout << endl;
	cout << "Podaj szerokosc strzalu (1-" << M << ") :";
	cin >> szerokosc;
	szerokosc = szerokosc - 1;
	cout << endl;
	if (wysokosc >= 0 && wysokosc < N && szerokosc >= 0 && szerokosc < M) {
		if (p->pole_gry[wysokosc][szerokosc] == nieznane) {
			if (s->statki[wysokosc][szerokosc] == jednomasztowiec) {
				p->pole_gry[wysokosc][szerokosc] = jednomasztowiec;
				(*t) += 1;
				(*pp) = 0;
			}
			else if (s->statki[wysokosc][szerokosc] == dwumasztowiec) {
				p->pole_gry[wysokosc][szerokosc] = dwumasztowiec;
				(*t) += 1;
				(*pp) = 0;
			}
			else
			{
				p->pole_gry[wysokosc][szerokosc] = pudlo;
				(*ch) += 1;
				(*pp) += 1;
			}
		}
		else {
			cout << "Pole jest juz odkryte";
			cout << endl;
			system("pause");
		}
	}
	else {
		cout << "Niepoprawne Dane !";
		cout << endl;
		system("pause");
	}

}

void wyswietl_punkty(unsigned int t, unsigned int ch, unsigned int pp) {
	cout << "Liczba strzalow trafionych wynosi : " << t << endl;
	cout << "Liczba strzalow nietrafionych wynosi : " << ch << endl;
	cout << "Liczba strzalow nietrafionych pod rzad wynosi : " << pp << endl;
}

void generuj_statki(plansza* s) {
	srand(time(NULL));
	int losowa1;
	int losowa2;

	for (unsigned int i = 0; i < K;) {
		losowa1 = (rand() % N);
		losowa2 = (rand() % M);

		if (s->statki[losowa1][losowa2] == pusto) {
			s->statki[losowa1][losowa2] = jednomasztowiec;
			i = i + 1;
		}
	}

	for (unsigned int i = 0; i < L;) {
		losowa1 = (rand() % N);
		losowa2 = (rand() % M);

		if (s->statki[losowa1][losowa2] == pusto) {
			unsigned int cztery;
			cztery = (rand() % 4) + 1;
			switch (cztery) {
			case 1:
				if (losowa2 != 0 && s->statki[losowa1][losowa2 - 1] == pusto) {
					s->statki[losowa1][losowa2] = dwumasztowiec;
					s->statki[losowa1][losowa2 - 1] = dwumasztowiec;
					i = i + 1;
				}
				break;
			case 2:
				if (losowa2 != (M - 1) && s->statki[losowa1][losowa2 + 1] == pusto) {
					s->statki[losowa1][losowa2] = dwumasztowiec;
					s->statki[losowa1][losowa2 + 1] = dwumasztowiec;
					i = i + 1;
				}
				break;
			case 3:
				if (losowa1 != 0 && s->statki[losowa1 - 1][losowa2] == pusto) {
					s->statki[losowa1][losowa2] = dwumasztowiec;
					s->statki[losowa1 - 1][losowa2] = dwumasztowiec;
					i = i + 1;
				}
				break;
			case 4:
				if (losowa1 != (N - 1) && s->statki[losowa1 + 1][losowa2] == pusto) {
					s->statki[losowa1][losowa2] = dwumasztowiec;
					s->statki[losowa1 + 1][losowa2] = dwumasztowiec;
					i = i + 1;
				}
				break;
			}
		}
	}
}

void wypelnij_statki(plansza* p) {

	for (unsigned int i = 0; i < N; i++) {

		for (unsigned int j = 0; j < M; j++) {
			p->statki[i][j] = pusto;
		}
	}
}

int powtorka(rekord* tab,string nazwa) {
	int index = -1;

	for (unsigned int i = 0; i < R; i++) {
		if (nazwa == tab[i].gracze) {
			index = i;
		}
	}

	return index;
}

void ustal_rekordy(rekord* tab, unsigned int wynik, string nazwa) {

	int pamiec1 = wynik;
	int pamiec2 = 0;
	string pamieca = nazwa;
	string pamiecb = "brak";
	int sprawdz = powtorka(tablica, nazwa);

	if (sprawdz != -1 && tab[sprawdz].wyniki_graczy < wynik) {
		tab[sprawdz].wyniki_graczy = wynik;
		for (int i = sprawdz; i >= 0; i =  i - 1) {
			if (tab[i].wyniki_graczy > tab[i-1].wyniki_graczy && i - 1 >= 0 ) {

				pamiec2 = tab[i].wyniki_graczy;
				pamiecb = tab[i].gracze;
				tab[i].wyniki_graczy = tab[i-1].wyniki_graczy;
				tab[i].gracze = tab[i-1].gracze;
				tab[i-1].wyniki_graczy = pamiec2;
				tab[i-1].gracze = pamiecb;

			}
		
		}
	}
	else if(sprawdz != -1 && tab[sprawdz].wyniki_graczy >= wynik){

	}
	else{
		for (unsigned int i = 0; i < R; i++) {

			if (tab[i].wyniki_graczy < pamiec1) {

				pamiec2 = tab[i].wyniki_graczy;
				pamiecb = tab[i].gracze;
				tab[i].wyniki_graczy = pamiec1;
				tab[i].gracze = pamieca;
				pamiec1 = pamiec2;
				pamieca = pamiecb;

			}
		}
	}
}

void wyswietl_rekordy(rekord* tab) {
	system("cls");
	cout << "Oto " << R <<" najlepszych graczy" << endl;
	for (unsigned int i = 0; i < R; i++) {
		cout << tab[i].miejsce << " " << tab[i].gracze << " " << tab[i].wyniki_graczy << endl;
	}
	cout << endl;
	system("pause");
}

void czysc_rekordy(rekord* tab) {
	ofstream plik_output("rekordy.txt");
	for (unsigned int i = 0; i < R; i++) {
		tab[i].miejsce = i + 1;
		plik_output << tab[i].miejsce << endl;
		tab[i].gracze = "brak";
		plik_output << tab[i].gracze << endl;
		tab[i].wyniki_graczy = 0;
		plik_output << tab[i].wyniki_graczy << endl;
	}
}

void wczytaj_rekordy(rekord* tab) {
	ifstream plik_input("rekordy.txt");
		for (unsigned int i = 0; i < R; i++) {
			plik_input >> tab[i].miejsce;
			plik_input >> tab[i].gracze;
			plik_input >> tab[i].wyniki_graczy;
		}
}

void zapisz_rekordy(rekord* tab) {
	ofstream plik_output("rekordy.txt");
	for (unsigned int i = 0; i < R; i++) {
		plik_output << tab[i].miejsce << endl;
		plik_output << tab[i].gracze << endl;
		plik_output << tab[i].wyniki_graczy << endl;
	}
}

void instrukcja() {
	system("cls");
	cout << "Witaj w grze w STATKI !" << endl << endl;
	cout << "Aby zagarc wybierz opcje : Rozpocnij Gre" << endl;
	cout << "Aby wyswietlic tablice rekordow wybierz opcje : Wyswietl Tablice Rekordow" << endl;
	cout << "Aby wyswietlic instrukcje wybierz opcje : Wysweitl Instrukcje" << endl;
	cout << "Aby wylaczyc gre wybierz opcje : Wyjdz z gry" << endl << endl;
	cout << "Aby oddac strzal w grze podaj parametry wysokosci i szerokosci w podanych miejscach" << endl << endl;
	system("pause");

}


int main() {

	



	
	ifstream plik_rekordy("rekordy.txt");
	if (!plik_rekordy) {
		czysc_rekordy(tablica);
	}
	else{
		wczytaj_rekordy(tablica);
	}



	int opt;
	do {
		system("cls");
		cout << "Wybierz opcje:" << endl;
		cout << "1: Rozpocznij Gre" << endl;
		cout << "2: Wyswietl Tablice Rekordow" << endl;
		cout << "3: Wyswietl instrukcje" << endl;
		cout << "0: Wyjdz z gry" << endl << endl;

		cout << "Podaj swoj wybor: ";
		cin >> opt;

		unsigned int chybienia = 0;
		unsigned int trafienia = 0;
		string obecny_gracz;
		unsigned int wynik_gracza;
		unsigned int pod_rzad = 0;

		switch (opt) {
		case 1:
			wypelnij_plansze_poczatkowa(&gra);
			wypelnij_statki(&gra);
			generuj_statki(&gra);



			cout << endl;
			cout << "Podaj nazwe gracza : ";
			cin >> obecny_gracz;
			system("cls");
			do {
				system("cls");
				wyswietl_punkty(trafienia, chybienia,pod_rzad);
				wyswietl_plansze(&gra);
				strzal(&gra, &gra, &trafienia, &chybienia,&pod_rzad);
			} while (pod_rzad != MLP && trafienia != MP);

			system("cls");
			wyswietl_punkty(trafienia, chybienia,pod_rzad);
			wyswietl_statki(&gra);
			wynik_gracza = trafienia;
			ustal_rekordy(tablica, wynik_gracza, obecny_gracz);
			zapisz_rekordy(tablica);
			if (pod_rzad == MLP) {
				cout << "Prykro nam, niestety przegrana..." << endl;
			}
			else if (trafienia == MP) {
				cout << "Gratuacje ! Zwyciestwo !" << endl;
			}
			system("pause");
			system("cls");
			break;
		case 2: wyswietl_rekordy(tablica);
			break;
		case 3: instrukcja();
			break;
		case 0:
			break;
		default:
			cout << "Niepoprawna opcja!" << endl << endl;
			system("pause");
			break;
		}

	} while (opt != 0);

	return 0;
}




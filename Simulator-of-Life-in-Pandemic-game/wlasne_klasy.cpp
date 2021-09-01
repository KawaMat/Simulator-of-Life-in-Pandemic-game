#include<iostream>
#include"wlasne_klasy.h"


using namespace std;

Jedzenie::Jedzenie()
{
}

Jedzenie::Jedzenie(string n, int w,int c) {
	nazwa = n;
	if(w>=0)
		wartosc = w;
	if (c >= 0)
		cena = c;
}


void Portfel::dodaj(int i) {
	if (i >= 0)
		zawartosc += i;
}
void Portfel::odejmij(int i) {
	if (i > zawartosc)
		zawartosc = 0;
	else
		zawartosc -= i;
}
int Portfel::wyswietl() {
	return zawartosc;
}
Portfel::Portfel(int i) {
	zawartosc = i;
}



void Dziennik::wyswietl_dziennik() {
	if (ilosc_poch == 0) {
		cout << "brak pochwal\n";
	}
	else {
		for (int i = 1; i <= ilosc_poch; i++) {

			cout << "+ Pochwala No." << i << " - Wyzdrowiala kolejna osoba. Gratulacje!" << endl;
		}
	}
	cout << endl;
	if (ilosc_nag == 0) {
		cout << "brak nagan\n";
		
	}
	else {
		for (int i = 1; i <= ilosc_nag; i++) {

			cout << "- Nagana No." << i << " - Kolejna ofiara nie zyje." << endl;
		}
	}
	cout << endl;
	
}
Dziennik::Dziennik(int n, int p) {
	ilosc_nag = n;
	ilosc_poch = p;
}


///////czeka na interface chorego zeby wyswietlac dane;
int Kwarantanna::podaj_zawartosc() { 
	if (zaj_miej == 0) {
		cout << "______________________________________"<<endl;
		cout << "Brak chorych pod kwarantanna" << endl;
		
	}
	else {
		for (int i = 0; i < zaj_miej; i++) {

			cout << "miejsce " << i + 1 << ". " << endl << "ID:\t" << lista_chorych[i].pokaz_id() << endl
				<< "imie:\t" << lista_chorych[i].pokaz_imie() << endl
				<< "zycie:\t" << lista_chorych[i].pokaz_pkt_zycia() << endl
				<< "ekwipunek:\t" << lista_chorych[i].pokaz_jedzenie_chorego() << endl
				<< "raport:\n\"" << lista_chorych[i].pokaz_raport() << "\"" << endl
				<< "________________________________" << endl<<endl;
		}
	}
	return zaj_miej;
}
void Kwarantanna::dodaj_chorego(Chory a) {
	if (zaj_miej == 10) {
		cout << "______________________________________";
		cout << endl << "W kwarantannie brakuje wolnych lozek.\nPoczekaj na wolne miejsce lub usun jednego z chorych samodzielnie.";
	}
	else {
		
		lista_chorych[zaj_miej] = a;
		zaj_miej++;
	}
}
int Kwarantanna::usun_chorego(int id) {
	int temp;
	int flaga = 0;
		for (int i = 0; i < zaj_miej; i++) {
			if (lista_chorych[i].ID == id) {
				temp = lista_chorych[i].ID;
				if (i < 9) {
					for (int k = i; k < zaj_miej; k++) {
						lista_chorych[k] = lista_chorych[k + 1];
					}
					zaj_miej--;
				}
				else {
					zaj_miej--;
				}
				flaga = 1;
			}

				

		}
		if (flaga == 0) {
			//cout << endl << "W kwarantannie nie istnieje pacjent o takim numerze ID...\n\n";
			
		}
		return temp;
}

Chory& Kwarantanna::pokaz_chorego_po_id(int a)
{
	
	return lista_chorych[a];
}


Jedzenie Chory::odbierz_jedz_choremu()
{
	if (jedzenie_chorego.nazwa != "brak") {
		Jedzenie temp = jedzenie_chorego;
		jedzenie_chorego.nazwa = "brak";
		jedzenie_chorego.wartosc = 0;
		jedzenie_chorego.cena = 0;
		return temp;
	}
	
}

void Chory::nakarm_chorego()
{
	if (jedzenie_chorego.nazwa != "brak") {
		pkt_zycia += jedzenie_chorego.wartosc;
		jedzenie_chorego.nazwa = "brak";
		jedzenie_chorego.wartosc = 0;
		jedzenie_chorego.cena = 0;
		cout << "______________________________________";
		cout <<endl<<"Zjadl i od razu sie poprawilo..." << endl;
	}
	else {
		cout << "______________________________________";
		cout << "\nKieszenie chorego sa puste..." << endl;
	}
}
void Chory::aktualizuj(int id, string im, string rap, int pkt_z, float odp, string naz,int war,int cena)
{
	ID = id;
	imie = im;
	raport = rap;
	pkt_zycia = pkt_z;
	odpornosc = odp;
	jedzenie_chorego.nazwa = naz;
	jedzenie_chorego.wartosc = war;
	jedzenie_chorego.cena = cena;

}
void Chory::dodaj_jedzenie(Jedzenie a)
{
	jedzenie_chorego = a;
};

Chory::Chory(int id, string im, string rap, int pkt_z, float odp, string naz_jedz, int wart_jedz, int cen_jedz)
{
	ID = id;
	imie = im;
	raport = rap;
	pkt_zycia = pkt_z;
	odpornosc = odp;
	jedzenie_chorego.nazwa = naz_jedz;
	jedzenie_chorego.wartosc = wart_jedz;
	jedzenie_chorego.cena = cen_jedz;
}


Gracz::Gracz(string a, int b, float c) {
	imie = a;
	pkt_zycia = b;
	odpornosc = c;
}
void Gracz::pokaz_ekwipunek()
{
	cout << "EKWIPUNEK:\n\n";
	for (int i = 0; i < 5; i++) {
		cout <<i+1<<". ";
		if (i >= ilosc_jedz)
			cout << "puste"<<endl;
		else {
			cout << ekwipunek[i].nazwa << "\t" << "energia:" << ekwipunek[i].wartosc << "\t" << "cena:" << ekwipunek[i].cena << endl;
		}
	}
}

void Gracz::dodaj_jedzenie(Jedzenie a)
{
	if (ilosc_jedz == 5) {
		cout << endl << "Brak miejsca w ekwipunku";
		return;
	}
	ilosc_jedz++;
 	ekwipunek[ilosc_jedz-1] = a;
}

Jedzenie Gracz::usun_jedzenie(int a)
{
	Jedzenie temp = ekwipunek[a - 1];
	for (int i = a - 1; i < ilosc_jedz; i++) {
		if (a == ilosc_jedz) {
			ilosc_jedz--;
			break;
		}
		ekwipunek[i] = ekwipunek[i + 1];
		ilosc_jedz--;
	}
	return temp;
}

void Gracz::zjedz(int a)


{
	cout << "______________________________________";
	if (ekwipunek[a - 1].nazwa == "szczepionka") {
		cout << "\n\"...nareszcie - co za ulga!. Musze zdobyc tego wiecej zeby chronic zone i dzieciaki...\""
			<< "\n\n Czy to sie kiedys skonczy...\n\n";
		exit(0);
	}
	cout << endl << "Zjedzono " << ekwipunek[a-1].nazwa <<" +"<<ekwipunek[a-1].wartosc <<" pkt zycia." << endl;
	pkt_zycia += ekwipunek[a-1].wartosc;
	for (int i = a-1; i < ilosc_jedz; i++) {
		if (a == ilosc_jedz) {
			ilosc_jedz--;
			break;
		}
		ekwipunek[i] = ekwipunek[i + 1];
		ilosc_jedz--;
	}
	
}

void Gracz::sprzedaj(Portfel &p, int a)
{
	cout << "______________________________________";
	cout << endl << "Sprzedano " << ekwipunek[a - 1].nazwa << " +" << ekwipunek[a - 1].cena << " PLN." << endl;
	p.dodaj(ekwipunek[a - 1].cena);
	for (int i = a - 1; i < ilosc_jedz; i++) {
		if (a == ilosc_jedz) {
			ilosc_jedz--;
			break;
		}
		ekwipunek[i] = ekwipunek[i + 1];
		ilosc_jedz--;
	}
}

string Gracz::pokaz_ekwipunek(int i)
{
	return ekwipunek[i-1].nazwa;
}



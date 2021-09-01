#include<iostream>
#include<fstream>
#define MAX_MIEJSC 5
#define KASA_NA_START 5

using namespace std; 

class Czlowiek {

public:
	Czlowiek() {};
	~Czlowiek() {};
	virtual int pokaz_pkt_zycia() = 0;
	virtual string pokaz_imie() = 0;

};
class Jedzenie {
	friend class Chory;
	friend class Gracz;
	string nazwa;
	int wartosc, cena;

public:
	Jedzenie();
	Jedzenie(string, int, int);
};

class Chory :public Czlowiek{
	friend class Kwarantanna;
	

	int ID;
	string imie;
	string raport;   //opis pobierany z ploiku zgodnie z ID razem z innymi punktami
	int pkt_zycia;
	float odpornosc; //wspolczynnik przetrwania
	Jedzenie jedzenie_chorego; //produkt przekazywany graczowi
	
	
public:
	
	Chory() {};
	Chory(int id, string im, string rap, int pkt_z, float odp, string naz_jedz, int wart_jedz, int cen_jedz);// podczas tworzenia chorego powstanie nowy nr ID losowy ktory bedzie zapisywany w mainie do tablicy chorych ktorzy zostali wywolani zeby nie bylo powtorek 
	inline int pokaz_id() { return ID; };
	inline string pokaz_imie() { return imie; };
	inline string pokaz_raport() { return raport; };
	inline int pokaz_pkt_zycia() { return pkt_zycia; };
	inline float pokaz_odpornosc() { return odpornosc; };
	inline void zmien_pkt_zycia(int a) {pkt_zycia = a; };
	inline string pokaz_jedzenie_chorego() { return jedzenie_chorego.nazwa; };
	Jedzenie odbierz_jedz_choremu();
	string get_nazw_jedz() { return jedzenie_chorego.nazwa; };
	int get_wart_jedz() { return jedzenie_chorego.wartosc; };
	int get_cen_jedz() { return jedzenie_chorego.cena; };
	void nakarm_chorego();
	void aktualizuj(int, string, string, int, float, string,int, int);
	void dodaj_jedzenie(Jedzenie);
	void operator=  (Jedzenie a) {      /////// Przeci¹zenie operatora przypisania, by choremu dodawac pkt zycia z jedzenia.
		this->pkt_zycia += a.wartosc;
	}

};

class Portfel {
	friend class Gra;
	friend class Gracz;
	int zawartosc;
public:
	int wyswietl();
	void dodaj(int);
	void odejmij(int);
	Portfel(int i=KASA_NA_START);
	void zeruj() { zawartosc = 0; };
	
};

class Dziennik {
	friend class Gracz;
	friend class Gra;
	int ilosc_poch, ilosc_nag;

public:
	inline void dodaj_poch() { ilosc_poch++; };
	inline void dodaj_nag() { ilosc_nag++; };
	void wyswietl_dziennik();
	Dziennik(int=0, int=0);
	int get_poch() { return ilosc_poch; };
	int get_nag() { return ilosc_nag; };
	void set_poch(int a) {  ilosc_poch =a; };
	void set_nag( int a) {  ilosc_nag=a; };
}; //wyswielanie nagrod i nagan za bledy	   

class Kwarantanna { //spis ID chorych ktorzy sa w kwarantannie
	friend class Gra;

	int zaj_miej=0;
	Chory lista_chorych[MAX_MIEJSC];
	
	
	

public:

	Kwarantanna() {};
	int podaj_zawartosc();
	void dodaj_chorego(Chory);
	int usun_chorego(int);
	inline int czy_pusty() { return zaj_miej; };
	inline int zaj_miejsca() { return zaj_miej; };
	Chory &pokaz_chorego_po_id(int);
	void zaj_miejsca_set(int a) { zaj_miej = a; };
	void czyszczenie(void) { zaj_miej = 0; };
	
};

class Gracz :public Czlowiek {

	friend class Kwarantanna;
	friend class Dziennik;
	friend class Gra;

	string imie;
	int pkt_zycia;
	float odpornosc =-3; //wspolczynnik przetrwania
	Jedzenie ekwipunek[5]; //produkt przekazywany graczowi
	int ilosc_jedz = 0;
	string stan = "Wpadlem jak sliwka w...eeh szkoda gadac";

public:

	Gracz() {};
	Gracz(string a, int b, float c);
	 // podczas tworzenia chorego powstanie nowy nr ID losowy ktory bedzie zapisywany w mainie do tablicy chorych ktorzy zostali wywolani zeby nie bylo powtorek 
	inline string pokaz_imie() { return imie; };
	inline void zmien_imie(string i) { imie = i; };
	inline int pokaz_pkt_zycia() { return pkt_zycia; };
	inline void zmien_pkt_zycia(int a) { pkt_zycia = a; };
	inline float pokaz_odpornosc() { return odpornosc; };
	void pokaz_ekwipunek();
	void dodaj_jedzenie(Jedzenie);
	Jedzenie usun_jedzenie(int);
	void zjedz(int);
	inline int czy_pusty() { return ilosc_jedz; };
	void sprzedaj(Portfel&,int) ;
	inline void stan_set(string s) { stan = s; };
	inline string stan_get() { return stan; };
	string pokaz_ekwipunek(int);
	inline int pokaz_ilosc_jedz(void) { return ilosc_jedz; };
	inline void ilosc_jedz_set(int a) { ilosc_jedz = a; };
	string get_nazw_jedz(int a) { return ekwipunek[a].nazwa; };
	int get_wart_jedz(int a) { return ekwipunek[a].wartosc; };
	int get_cen_jedz(int a) { return ekwipunek[a].cena; };
	void odpornosc_set(float a) { odpornosc = a; };
};

class Gra { //////zapis wczytanie
	friend class Menu;

public:
	void zapisz();
	void wczytaj();

};

class Menu {

};


template<class T> void redukcja_zdrowia(T &a, int losowa) {
	

	a.zmien_pkt_zycia(a.pokaz_pkt_zycia() - losowa*3);
		
	
	
	
	 
};	
#include <iostream>
#include"wlasne_klasy.h"
#include<vector>
#include <cstdlib>
#include <ctime>
#include<fstream>
#include<string>
#define BAZA_CHORYCH 10
#define ZYCIE_POCZ 35
#define ODPORNOSC_POCZ -3
#define CENA_SZCZEPIONKI 20

using namespace std;


int main() {

	Gracz gracz("name", ZYCIE_POCZ, ODPORNOSC_POCZ);
	Chory chory;

	fstream plik, zapis;

	Dziennik dziennik;
	Portfel portfel;
	Kwarantanna kwarantanna;
	Czlowiek* czlowiek = &gracz;   //polimorficzny wskaŸnik klasy bazowej. Pozwala prze³¹czaæ obslugê klasy Gracz i Chory (podawanie imienia i ilosc pkt. zycia)
	string imie;
	cout << "Podaj swoje imie: ";
	cin >> imie;
	gracz.zmien_imie(imie);

	int czy_nowy = 1;
	vector<int> rejestr_id; ////////////// !!!!!!!!!!!!!!!!


	cout << endl << endl << gracz.pokaz_imie()<<", od teraz na twoje barki spada o wiele wieksza odpowiedzialnosc - odpowiedzialnosc za cale spoleczenstwo.\n"
		<<"Wirus wyniszczajacy kraj zmutowal do przerazliwie zjadliwej formy...zabija w mgnieniu oka dzieci i starcow.\n"
		<<"Za sciana stoja chorzy na COVID-20, a na twoim biurku leza raporty opisujace stan zdrowia tych chorych."
		<<" Po przeanalizowaniu raportu i przyjrzeniu sie choremu musisz zdecydowac czy ma zajac miejsce w kwarantannie i miec szanse wyzdrowiec,\nczy nie...\n"
		<<"Choc nikt sie nie domysla, ty wiesz doskonale ze ta goraczka, ktora meczy cie od 2 dni to nie przeziebienie...\n"
		<<"Zeby nie tracic zdrowia musisz jesc regularnie. Chorzy w kwarantannie moga wyzrowiec, gdzy wartosc ich zdrowia osiagnie 100 pkt.(za 3 wyzdrowienia dostajesz nagrode), lub umrzec (jesli umra 3 osoby tracisz ta robote).\n"
		<<"W czasie gdy przegladasz teczke stan zdrowia wszystkich w kwarantannie, jak rowniez twoj, ulega zmianie - sledz to na biezaco i przeciwdzialaj.\n\n"<< endl << endl;




	Jedzenie chleb("Chleb", 5, 2);/////////////////////Testowanie jedzenia

	gracz.dodaj_jedzenie(chleb);

	cout << "Ispektorze " << czlowiek->pokaz_imie() << ", szkoda czasu - zaczynajmy!" << endl << endl; ///// polimorfizm ...
	int flaga_wyjscia = 1;
	while (flaga_wyjscia) {
		int wybor;
		cout << "\n\t.    -     .    -    .     -      .     -      .     -\n"
			"\t|\t1. Przegladaj teczki chorych\t4. Portfel	|\n"
			"\t|\t2. Kwarantanna\t\t\t5. Dziennik	|\n"
			"\t|\t3. Ekwipunek\t\t\t6. Opcje	|\n" <<
			"\t.    -     .    -    .     -      .     -      .     -\n";
		int flaga = 1;
		while (flaga) {
			while (!(cin >> wybor)) {
				cin.clear();
				while (cin.get() != '\n') {
					continue;
				}
				cout << "Podaj numer wybranej opcji." << endl;
				continue;
			}
			if ((wybor < 1 || wybor > 6)) {
				cout << "Podany numer nie odpowiada zadnej z opcji - sprobuj ponownie." << endl;
				continue;
			}
			else
				flaga = 0;
		}

		switch (wybor) {
		case 1: {cout << "______________________________________";
			if (czy_nowy == 1) {
				Jedzenie jedz;
				int flaga_while = 1;
				int wylosowana_liczba;
				bool flaga = 0;
				do {
					flaga = 0;
					wylosowana_liczba = (rand() % 10) + 1;

					for (int i = 0; i < rejestr_id.size(); i++) {
						if (wylosowana_liczba == rejestr_id[i]) {
							flaga = 1;
						}
					}

				} while (flaga);

				rejestr_id.push_back(wylosowana_liczba);


				string linia;
				int licznik_linii = 0;
				string st_id = "id " + to_string(wylosowana_liczba);
				string tab[7];

				plik.open("chorzy.txt", ios::in);
				if (!plik.good()) {
					cout << endl << "BLAD OTWARCIA PLIKU!" << endl;
				}



				while (getline(plik, linia)) {
					if (linia == st_id) {
						for (int i = 0; i < 7; i++) {
							getline(plik, tab[i]);
						}
						break;
					}

				}
				plik.close();
				int pkt, wart, cena;
				float odp;

				chory.aktualizuj(wylosowana_liczba, tab[0], tab[1], stoi(tab[2]), stof(tab[3]), tab[4], stoi(tab[5]), stoi(tab[6]));

				czy_nowy = 0;

			}
			//////////


			for (int i = 0; i < kwarantanna.czy_pusty(); i++) { //// zmiana stanu zdrowia po otwarciu kolejnej teczki

				int losowa = (rand() % 10) + 1;
				if (losowa < (5 - kwarantanna.pokaz_chorego_po_id(i).pokaz_odpornosc())) {
					redukcja_zdrowia(kwarantanna.pokaz_chorego_po_id(i), losowa); ////////////// uzycie szablonu funkcji
					if (kwarantanna.pokaz_chorego_po_id(i).pokaz_pkt_zycia() <= 0) {
						cout << "\n\n\t\t\t(W KWARANTANNIE ZMARL CHORY - NAGANA!)"<<endl<<endl;
						rejestr_id.push_back(kwarantanna.usun_chorego(kwarantanna.pokaz_chorego_po_id(i).pokaz_id()));
						dziennik.dodaj_nag();
						if (dziennik.get_nag() == 3) {
							cout << "Nie spisales sie, zostajesz odsuniety. "
								<< "Koniec...";
							exit(0);
						}
					}
				}
				else {
					kwarantanna.pokaz_chorego_po_id(i).zmien_pkt_zycia(kwarantanna.pokaz_chorego_po_id(i).pokaz_pkt_zycia() + losowa/2);
					if (kwarantanna.pokaz_chorego_po_id(i).pokaz_pkt_zycia() >= 100) {
						cout << "\n\n\t\t\t(W KWARANTANNIE WYZDROWIAL CHORY - POCHWALA!)"<<endl<<endl;
						rejestr_id.push_back(kwarantanna.usun_chorego(kwarantanna.pokaz_chorego_po_id(i).pokaz_id()));
						dziennik.dodaj_poch();
						if (dziennik.get_poch() == 3) {
							cout << "Swietnie sie spisales - w ostatnim czasie wyzdrowia³y 3 osoby, dostajesz premiê +10 PLN. Gratulacje!";
							portfel.dodaj(10);
								
							
						}
					}
				}

			}
			int losowa = (rand() % 10) + 1;
			//cout << losowa << endl;
			if (losowa < (5 - gracz.pokaz_odpornosc())) {
				redukcja_zdrowia(gracz, losowa); ////////////// uzycie szablonu funkcji
				if (gracz.pokaz_pkt_zycia() <= 0) {
					cout << endl << endl << "\t\tOslabienie wynikajace z niedozywienia doprowadzilo do konca twojej gry, zwanej zyciem.\n\n\n";
					exit(0);
				}
				switch (losowa) {
				case 1: gracz.stan_set("Chyba pora umierac..."); break;
				case 2: gracz.stan_set("Nie wiem ile jeszcze wytrzymam..."); break;
				case 3: gracz.stan_set("Troche ostatnio oslablem..."); break;
				case 4: gracz.stan_set("Czuje lekkie pogorszenie..."); break;

				}
			}
			/*else {
				
				gracz.zmien_pkt_zycia(gracz.pokaz_pkt_zycia() + losowa);
				switch (losowa) {
				case 5: gracz.stan_set("Lekka poprawa..."); break;
				case 6: gracz.stan_set("Czuje sie lepiej..."); break;
				case 7: gracz.stan_set("Calkiem niezle sie czuje..."); break;
				case 8: gracz.stan_set("Moze dozyje do swiat..."); break;
				case 9: gracz.stan_set("Zdecydowana poprawa..."); break;
				case 10: gracz.stan_set("O wiele lepiej!..."); break;
				}
			}*/


			int flaga_wyjscia2 = 1;
			while (flaga_wyjscia2) {
				cout << endl << "Raport dot. " << chory.pokaz_imie() << ":" << endl
					<< "\"" << chory.pokaz_raport() << "\"" << endl << endl
					<< "punkty zycia: " << chory.pokaz_pkt_zycia() << "\tzawartosc kieszeni:" << chory.pokaz_jedzenie_chorego() << endl << endl
					<< "1. Wroc\t\t2. Wyslij do kwarantanny\t3. Unieszkodliw\t\t4. Pozwol zjesc\n\n";
				int wyb;


				int flaga = 1;
				while (flaga) {
					while (!(cin >> wyb)) {
						cin.clear();
						while (cin.get() != '\n') {
							continue;
						}
						cout << "Podaj numer wybranej opcji." << endl;
						continue;
					}
					if ((wyb < 1 || wyb > 4)) {
						cout << "Podany numer nie odpowiada zadnej z opcji - sprobuj ponownie." << endl;
						continue;
					}
					else
						flaga = 0;
				}

				switch (wyb) {
				case 1: { flaga_wyjscia2 = 0; break; }
				case 2: {cout << "______________________________________" << endl;
					if (kwarantanna.czy_pusty() == 5) {
						cout << "Brak miejsca w kwarantannie - poczekaj az sie zwolni, lub usun jednego z przebywajacych tam chorych\n";
						break;
					}
					kwarantanna.dodaj_chorego(chory);
					cout << chory.pokaz_imie() << " zostal dodany do kwarantanny" << endl;
					flaga_wyjscia2 = 0;
					czy_nowy = 1;
					break;
				}
				case 3: {cout << "______________________________________" << endl;
					cout << chory.pokaz_imie() << " zostal unieszkodliwiony." << endl;
					flaga_wyjscia2 = 0;
					czy_nowy = 1;
					break;
				}
					
				case 4: {if (chory.pokaz_jedzenie_chorego() == "brak") {
					cout << "______________________________________" << endl
						<< "Ten pacjent nic przy sobie nie ma..." << endl;
					break;
				}

					  chory.nakarm_chorego();
					  break;
				}
				}

			}
			break;
		}

		case 2: {cout << "______________________________________" << endl;
			if (kwarantanna.zaj_miejsca() == 0) {
				cout << "Brak chorych pod kwarantanna" << endl;
				break;
			}

			int flaga_wyjscia2 = 1;
			while (flaga_wyjscia2) {
				kwarantanna.podaj_zawartosc();
				cout << "1. Wroc\t\t2. Zwolnij miejsce (-5 PLN)\t3. Odbierz jedzenie\t4. Pozwol zjesc\t\t5.Oddaj jedzenie\n\n";
				int wyb;



				int flaga = 1;
				while (flaga) {
					while (!(cin >> wyb)) {
						cin.clear();
						while (cin.get() != '\n') {
							continue;
						}
						cout << "Podaj numer wybranej opcji." << endl;
						continue;
					}
					if ((wyb < 1 || wyb > 5)) {
						cout << "Podany numer nie odpowiada zadnej z opcji - sprobuj ponownie." << endl;
						continue;
					}
					else
						flaga = 0;
				}

				switch (wyb) {
				case 1: {
					flaga_wyjscia2 = 0;
					break;
				}
				case 2: {
					if (portfel.wyswietl() < 5) {
						cout << "Nie masz tyle pieniedzy zeby poniesc konsekwencje swojej zlej decyzji o przydziale miejsca w kwarantannie" << endl;
						break;
					}
					cout << endl << "Podaj ID chorego, ktrego chcesz usunac: ___\b\b\b";
					int id;


					while (!(cin >> id)) {
						cin.clear();
						while (cin.get() != '\n') {
							continue;
						}
						cout << endl << "Podaj ID chorego, ktrego chcesz usunac: ___\b\b\b";

					}

					cout << "______________________________________" << endl;

					int flaga = 1;
					for (int i = 0; i < kwarantanna.zaj_miejsca(); i++) {
						if (kwarantanna.pokaz_chorego_po_id(i).pokaz_id() == id)
							flaga = 0;
					}
					if (flaga) {
						cout << endl << "W kwarantannie nie istnieje pacjent o takim numerze ID...\n\n";
						break;
					}


					cout << "\"Zmarnowales tylko miejsce i czas na jakiegos zdechlaka, slono za to zaplacisz...\" "
						<< endl << endl << "Pacjent zostal unieszkodliwiony, jednak zle decyzje kosztuja - potracono -5 PLN" << endl;
					portfel.odejmij(5);

					rejestr_id.push_back(kwarantanna.usun_chorego(id)); ///////  usuwanie chorego i zapisanie jego ID do rejestru nieistniejacych juz chorych, aby ponownie nie byl wylosowany

					flaga_wyjscia2 = 0;
					break;
				}
				case 3: { if (gracz.pokaz_ilosc_jedz() == 5) {
					cout
						<< "Ekwipunek jest pelny - zrob wpierw miejsce." << endl;
					break;
				}

					  int id;
					  cout << endl << "Podaj ID chorego, ktorego chcesz przeszukac: ___\b\b\b";
					  while (!(cin >> id)) {
						  cin.clear();
						  while (cin.get() != '\n') {
							  continue;
						  }
						  cout << endl << "Podaj ID chorego, ktorego chcesz przeszukac: ___\b\b\b";

					  }
					  cout << "______________________________________" << endl;

					  int flaga = 1;
					  for (int i = 0; i < kwarantanna.zaj_miejsca(); i++) {
						  if (kwarantanna.pokaz_chorego_po_id(i).pokaz_id() == id)
							  flaga = 0;
					  }
					  if (flaga) {
						  cout << endl << "W kwarantannie nie istnieje pacjent o takim numerze ID...\n\n";
						  break;
					  }

					  for (int i = 0; i < 5; i++) {
						  if (id == kwarantanna.pokaz_chorego_po_id(i).pokaz_id()) {

							  if (kwarantanna.pokaz_chorego_po_id(i).pokaz_jedzenie_chorego() == "brak") {
								  cout << "Ten pacjent juz nic przy sobie nie ma...\n" << endl;
								  continue;
							  }
							  cout << "Po przeszukaniu skonfiskowano " << kwarantanna.pokaz_chorego_po_id(i).pokaz_jedzenie_chorego() << endl << endl;
							  gracz.dodaj_jedzenie(kwarantanna.pokaz_chorego_po_id(i).odbierz_jedz_choremu());

						  }
					  }



					  break;
				}
				case 4: {
					int id;
					cout << endl << "Podaj ID chorego, ktoremu wolno zjesc: ___\b\b\b";
					while (!(cin >> id)) {
						cin.clear();
						while (cin.get() != '\n') {
							continue;
						}
						cout << endl << "Podaj ID chorego, ktoremu wolno zjesc: ___\b\b\b";

					}
					
					int flaga = 1;
					for (int i = 0; i < kwarantanna.zaj_miejsca(); i++) {
						if (kwarantanna.pokaz_chorego_po_id(i).pokaz_id() == id)
							flaga = 0;
					}
					if (flaga) {
						cout << endl << "W kwarantannie nie istnieje pacjent o takim numerze ID...\n\n";
						break;
					}
					for (int i = 0; i < 5; i++) {
						if (id == kwarantanna.pokaz_chorego_po_id(i).pokaz_id()) {
							if (kwarantanna.pokaz_chorego_po_id(i).pokaz_jedzenie_chorego() == "brak") {
								cout << "______________________________________" << endl
									<< "Ten pacjent juz nic przy sobie nie ma...\n" << endl;
								continue;
							}
							kwarantanna.pokaz_chorego_po_id(i).nakarm_chorego();

						}
					}
					break;
				}
				case 5: {
					if (gracz.pokaz_ilosc_jedz() == 0) {
						cout << "Twoj ekwipunek jest pusty." << endl;
						break;
					}
					int wyb;
					cout << endl << "Podaj ID chorego, ktorego chcesz dokarmic jesli ma puste kieszenie: ___\b\b\b";
					while (!(cin >> wyb)) {
						cin.clear();
						while (cin.get() != '\n') {
							continue;
						}
						cout << endl << "Podaj ID chorego, ktorego chcesz dokarmic jesli ma puste kieszenie: ___\b\b\b";

					}
					int flaga = 1;
					for (int i = 0; i < kwarantanna.zaj_miejsca(); i++) {
						if (kwarantanna.pokaz_chorego_po_id(i).pokaz_id() == wyb)
							flaga = 0;
					}
					if (flaga) {
						cout << endl << "W kwarantannie nie istnieje pacjent o takim numerze ID...\n\n";
						break;
					}
					for (int i = 0; i < 5; i++) {
						if (wyb == kwarantanna.pokaz_chorego_po_id(i).pokaz_id()) {
							if (kwarantanna.pokaz_chorego_po_id(i).pokaz_jedzenie_chorego() != "brak") {
								cout << "______________________________________" << endl;
								cout << endl << "Ten chory posiada swoje jedzenie." << endl;
								break;
							}

							gracz.pokaz_ekwipunek();
							cout << endl << "Co chcesz podarowac chorujacemu?: ";

							cin >> wyb;
							cout << endl << gracz.pokaz_ekwipunek(wyb) << endl;
							if (gracz.pokaz_ekwipunek(wyb) == "szczepionka") {

								cout << endl << "______________________________________" << endl
									<< "\"[...] chciales dobrze, wyszlo jak zawsze - w tej strzykawce jest szczepionka z czarnego rynku.\nWyobrazales sobie ze nikt nie zauwazy jak podasz cos pacjentowi pod sciasla obserwacja?! Jestes zwolniony dyscyplinarnie, policja juz po ciebie jedzie!\n\n";
								exit(0);
							}
							kwarantanna.pokaz_chorego_po_id(i).dodaj_jedzenie(gracz.usun_jedzenie(wyb));
							cout << "______________________________________" << endl
								<< kwarantanna.pokaz_chorego_po_id(i).pokaz_jedzenie_chorego() << " przekazano choremu.\n\n";
							break;
						}
					}



				}
				}
				if (kwarantanna.czy_pusty()) {
					flaga_wyjscia2 = 0;
				}
			}
			break;
		}

		case 3: {cout << "______________________________________" << endl;
			if (gracz.czy_pusty() == 0) {
				cout << endl << "Ekwipunek jest pusty" << endl;
				continue;
			}
			gracz.pokaz_ekwipunek();
			int wyb = 0;
			cout << endl << "1. Posil sie\t2. Sprzedaj\t3. Wroc\n";
			int flaga = 1;
			while (flaga) {
				while (!(cin >> wyb)) {
					cin.clear();
					while (cin.get() != '\n') {
						continue;
					}
					cout << "Podaj numer wybranej opcji." << endl;
					continue;
				}
				if ((wyb < 1 || wyb > 3)) {
					cout << "Podany numer nie odpowiada zadnej z opcji - sprobuj ponownie." << endl;
					continue;
				}
				else
					flaga = 0;
			}
			cout << "______________________________________" << endl;
			if (wyb == 1) {
				wyb = 0;
				while (wyb == 0) {
					cout << endl << "Co chcesz zjesc? __\b\b";
					cin >> wyb;
					if (wyb > gracz.czy_pusty()) {
						cout << "Brak takiego produktu";
						wyb = -1;
						continue;
					}
					gracz.zjedz(wyb);
					break;
				}

			}
			else if (wyb == 2) {

				cout << endl << "Co chcesz sprzedac? __\b\b";
				cin >> wyb;
				if (wyb > gracz.czy_pusty()) {
					cout << "Brak takiego produktu";
					wyb = -1;
					continue;
				}
				gracz.sprzedaj(portfel, wyb);
				break;
			}
			else {
				break;
			}
			break; }


		case 4: {cout << "______________________________________" << endl
			<< "PORTFEL:\n\n";
			cout << "Posiadasz obecnie: " << portfel.wyswietl() << " PLN." << endl;
			portfel.wyswietl();
			
			int wyb = 0;
			cout << endl << "1. Wroc\t\t2. Kup szczepionke i przewij to pieklo (-"<<CENA_SZCZEPIONKI<<" PLN)\n";
			cin >> wyb;
			cout << "______________________________________" << endl;
			if (wyb == 1) {
				break;
			}
			else if (wyb == 2) {
				if (gracz.czy_pusty() == 5) {
					cout << "Brak miejsca w ekwipunku..." << endl;
					break;
				}
				if (portfel.wyswietl() >= 20) {
					cout << "\n\"[...] trzymaj, uzyj tego rozsadnie i pod zadnym pozorem nie mow nikomu skad to masz...\"\n\n";
					Jedzenie szczepionka("szczepionka", 99999, 0);
					portfel.odejmij(CENA_SZCZEPIONKI);
					gracz.dodaj_jedzenie(szczepionka);

					break;
				}
				else {
					break;
				}
				break;
			}
			break;
		}
		case 5: { cout << "______________________________________" << endl;
			cout << "DZIENNIK:\n\n";
			dziennik.wyswietl_dziennik();
			cout << endl << "Moj stan zdrowia: \n"
				<< "\"" << gracz.stan_get() << "\"  - " << gracz.pokaz_pkt_zycia() << " pkt. zdrowia\n";
			
			break;
		}

		case 6: {

			int flaga_wyjscia2 = 1;
			while (flaga_wyjscia2) {
				cout << "1. Wroc\t\t2. Zapisz\t3. Wczytaj stan ostatniej gry\n\n";
				int wyb;



				int flaga = 1;
				while (flaga) {
					while (!(cin >> wyb)) {
						cin.clear();
						while (cin.get() != '\n') {
							continue;
						}
						cout << "Podaj numer wybranej opcji." << endl;
						continue;
					}
					if ((wyb < 1 || wyb > 5)) {
						cout << "Podany numer nie odpowiada zadnej z opcji - sprobuj ponownie." << endl;
						continue;
					}
					else
						flaga = 0;
				}

				switch (wyb) {
				case 1: {
					flaga_wyjscia2 = 0;
					break;
				}
				case 2: {

					zapis.open("zapis.txt", ios::out);
					zapis << gracz.czy_pusty() << endl;
					zapis << kwarantanna.czy_pusty() << endl;
					zapis << portfel.wyswietl() << endl;
					zapis << dziennik.get_poch() << endl << dziennik.get_nag() << endl;

					

					zapis << gracz.pokaz_imie() << endl
						<< gracz.pokaz_pkt_zycia() << endl
						<< gracz.pokaz_odpornosc() << endl

						<< gracz.stan_get() << endl;
					for (int i = 0; i < gracz.czy_pusty(); i++) {
						zapis << gracz.get_nazw_jedz(i) << endl;
						zapis << gracz.get_wart_jedz(i) << endl;
						zapis << gracz.get_cen_jedz(i) << endl;
					}
					for (int i = 0; i < kwarantanna.czy_pusty(); i++) {
						zapis << kwarantanna.pokaz_chorego_po_id(i).pokaz_id() << endl;
						zapis << kwarantanna.pokaz_chorego_po_id(i).pokaz_imie() << endl;
						zapis << kwarantanna.pokaz_chorego_po_id(i).pokaz_raport() << endl;
						zapis << kwarantanna.pokaz_chorego_po_id(i).pokaz_pkt_zycia() << endl;
						zapis << kwarantanna.pokaz_chorego_po_id(i).pokaz_odpornosc() << endl;
						zapis << kwarantanna.pokaz_chorego_po_id(i).get_nazw_jedz() << endl;
						zapis << kwarantanna.pokaz_chorego_po_id(i).get_wart_jedz() << endl;
						zapis << kwarantanna.pokaz_chorego_po_id(i).get_cen_jedz() << endl;
					}
					zapis << rejestr_id.size()<<endl;
					for (int i = 0; i < rejestr_id.size(); i++) {
						zapis << rejestr_id[i] << endl;
					}


					zapis.close();
					cout << "______________________________________" << endl;
					cout << "Zapisano stan gry." << endl;
					break;
				}

				case 3: {

					string linia;
					int licznik_linii = 0;


					zapis.open("zapis.txt", ios::in);
					if (!zapis.good()) {
						cout << endl << "BLAD OTWARCIA PLIKU ZAPISU!" << endl;
					}

					vector<string> dane;
					

					while (getline(zapis, linia)) {

						dane.push_back(linia);
						
						licznik_linii++;
					}
					zapis.close();
					
					gracz.ilosc_jedz_set(stoi(dane[0]));
					
					kwarantanna.zaj_miejsca_set(stoi(dane[1]));
					portfel.zeruj();
					portfel.dodaj(stoi(dane[2]));
					dziennik.set_poch(stoi(dane[3]));
					dziennik.set_nag(stoi(dane[4]));
					
					gracz.zmien_imie(dane[5]);
					gracz.zmien_pkt_zycia(stoi(dane[6]));
					
					gracz.odpornosc_set(stof(dane[7]));
					gracz.stan_set(dane[8]);

					int z = gracz.pokaz_ilosc_jedz();
					int k = kwarantanna.czy_pusty();
					if (z != 0) {
						for (int i = 0; i < z; i++) {
							gracz.usun_jedzenie(i);
						}
						for (int j = 0; j < z; j++) {
							Jedzenie temp(dane[9 + j * 3], stoi(dane[10 + j * 3]), stoi(dane[11 + j * 3]));
							gracz.dodaj_jedzenie(temp);
						}				
						
					}
					
					if (k != 0){
						kwarantanna.czyszczenie();
						for (int i = 0; i < k; i++) {
							//kwarantanna.usun_chorego();
						}
						for (int j = 0; j < k; j++){
							Chory temp(stoi(dane[z*3+9+j*8]), dane[z * 3 + 10 + j * 8], dane[z * 3 + 11 + j * 8], stoi(dane[z * 3 + 12 + j * 8]), stof(dane[z * 3 + 13 + j * 8]), dane[z * 3 + 14 + j * 8], stoi(dane[z * 3 + 15 + j * 8]), stoi(dane[z * 3 + 16 + j * 8]));
							
							kwarantanna.dodaj_chorego(temp);
						}

					}

					gracz.zmien_imie(dane[5]);
					gracz.zmien_pkt_zycia(stoi(dane[6]));
					cout << "Wczytano!" << endl;
					cout << gracz.pokaz_imie() << ", witaj ponownie." << endl;
					break;
				}
					

				}

			}

		}

		}
	}
}
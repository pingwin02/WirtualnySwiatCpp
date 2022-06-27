#include "Swiat.h"
#include "Czlowiek.h"

#include "Wilk.h"
#include "Owca.h"
#include "Lis.h"
#include "Zolw.h"
#include "Antylopa.h"

#include "Trawa.h"
#include "Mlecz.h"
#include "Guarana.h"
#include "WilczeJagody.h"
#include "BarszczSosnowskiego.h"

Swiat::Swiat() {
	this->rozmiarX = 0;
	this->rozmiarY = 0;
	this->numerTury = 0;
	this->pokazujDziennik = false;
	this->plansza = nullptr;
}

Swiat::Swiat(int rozmiarX, int rozmiarY) {
	this->rozmiarX = rozmiarX;
	this->rozmiarY = rozmiarY;
	this->numerTury = 0;
	this->pokazujDziennik = false;

	setPlansza(rozmiarX, rozmiarY);
}

void Swiat::sortujOrganizmy() {
	sort(organizmy.begin(), organizmy.end(),
		[](const Organizm* lewy, const Organizm* prawy) {
			if (lewy->getInicjatywa() > prawy->getInicjatywa()) {
				return 1;
			}
			else if (lewy->getInicjatywa() == prawy->getInicjatywa() && lewy->getWiek() > prawy->getWiek()) {
				return 1;
			}
			else {
				return 0;
			};
		});
}

void Swiat::usunMartwe() {
	for (int i = 0; i < organizmy.size(); i++) {
		if (!organizmy[i]->getZyje()) {
			delete organizmy[i];
			organizmy.erase(organizmy.begin() + i);
			organizmy.shrink_to_fit();
		}
	}
}

void Swiat::wykonajTure() {

	system("CLS");

	sortujOrganizmy();

	if (numerTury) {
		for (int i = 0; i < organizmy.size(); i++) {
			if (organizmy[i]->getZyje()) {
			organizmy[i]->setWiek(organizmy[i]->getWiek() + 1);
			organizmy[i]->akcja();
			dodajWpis("---");
			}
		}
	}

	usunMartwe();

	sortujOrganizmy();

	cout << "Tura nr " << numerTury << endl << endl;

	drukujOrganizmy();

	for (int i = 0; i < organizmy.size(); i++) {
		int ostatnioUrodzil = organizmy[i]->getNarodzony();
		if (ostatnioUrodzil) {
			organizmy[i]->setNarodzony(--ostatnioUrodzil);
		}
	}
	numerTury++;

}

int Swiat::getRozmiarX() const {
	return rozmiarX;
}

int Swiat::getRozmiarY() const {
	return rozmiarY;
}

void Swiat::setPokazujDziennik(bool d) {
	this->pokazujDziennik = d;
}

bool Swiat::getPokazujDziennik() const
{
	return pokazujDziennik;
}

void Swiat::setPlansza(int _x, int _y) {

	zwolnijPamiec();

	Organizm*** plansza = new Organizm** [_y];

	for (int i = 0; i < _y; i++) {
		Organizm** planszaX = new Organizm* [_x];
		plansza[i] = planszaX;
		for (int j = 0; j < _x; j++) {
			plansza[i][j] = nullptr;
		}
	}
	this->plansza = plansza;
	this->rozmiarX = _x;
	this->rozmiarY = _y;
	this->numerTury = 0;

}

Organizm*** Swiat::getPlansza() const
{
	return this->plansza;
}

void Swiat::drukujOrganizmy() {
	cout << "Na swiecie jest " << organizmy.size() << " organizmow:" << endl;
	for (int i = 0; i < organizmy.size() && i < 10; i++) {
		cout << organizmy[i] << endl;
		if (i == 9) {
			cout << "..." << endl;
		}
	}
	cout << endl;
}

void Swiat::rysujSwiat() {

	SetConsoleTitle(L"Damian Jankowski s188597 Wirtualny Swiat v1.0 M - menu ESC - wyjdz");

	cout << endl;

	cout << " ";
	for (int k = 0; k < rozmiarX; k++) {
		cout << k % 10;
	}
	cout << endl;
	for (int i = 0; i < rozmiarY; i++) {
		cout << i % 10;
		for (int j = 0; j < rozmiarX; j++) {
			if (plansza[i][j] != nullptr) {
				cout << plansza[i][j]->rysowanie();
			}
			else {
				cout << ' ';
			}
		}
		cout << endl;
	}

	if (pokazujDziennik) {
		cout << "Dziennik:" << endl << endl;

		for (int i = 0; i < dziennik.size(); i++) {
			cout << dziennik[i] << endl;
		}
	}

	dziennik.clear();
	dziennik.shrink_to_fit();
}

vector<Organizm*> Swiat::getOrganizmy() const {
	return organizmy;
}

void Swiat::dodajWpis(string wiad)
{
	dziennik.push_back(wiad);
}

void Swiat::dodajWpis(Organizm* o, int x1, int y1, int x2, int y2)
{
	dziennik.push_back(o->getNazwa() + "(" + to_string(x1) + "," + to_string(y1) + ") chce isc ("
		+ to_string(x2) + "," + to_string(y2) + ")");
}

void Swiat::setOrganizmy(vector<Organizm*> v) {
	this->organizmy = v;
}

void Swiat::dodajOrganizm(Organizm* nowyOrganizm) {
	if (!nowyOrganizm->SprawdzLokacje(nowyOrganizm->getX(), nowyOrganizm->getY())) {
		if (plansza[nowyOrganizm->getY()][nowyOrganizm->getX()] != nullptr) {
			cout << "To miejsce (" << nowyOrganizm->getX() << "," << nowyOrganizm->getY() << ") jest juz zajete!" << endl;
			delete nowyOrganizm;
		}
		else {
			organizmy.push_back(nowyOrganizm);
			plansza[nowyOrganizm->getY()][nowyOrganizm->getX()] = nowyOrganizm;
		}
	}
	else {
		delete nowyOrganizm;
	}
}

void Swiat::dodajOrganizm(char znak, int polozenieX, int polozenieY, int sila, int inicjatywa, int wiek) {

	Organizm* nowy = nullptr;

	switch (znak) {
		case WILK: {
			nowy = new Wilk(this, polozenieX, polozenieY);
			break;
		}
		case ANTYLOPA: {
			nowy = new Antylopa(this, polozenieX, polozenieY);
			break;
		}
		case CZLOWIEK: {
			nowy = new Czlowiek(this, polozenieX, polozenieY);
			break;
		}
		case CZLOWIEK_S: {
			Czlowiek* nowy = new Czlowiek(this, polozenieX, polozenieY);
			nowy->setCooldown(UMIEJETNOSC_COOLDOWN);
			nowy->setZnak(CZLOWIEK_S);
			nowy->setSila(sila);
			nowy->setInicjatywa(inicjatywa);
			nowy->setWiek(wiek);
			dodajOrganizm(nowy);
			break;
		}
		case LIS: {
			nowy = new Lis(this, polozenieX, polozenieY);
			break;
		}
		case OWCA: {
			nowy = new Owca(this, polozenieX, polozenieY);
			break;
		}
		case ZOLW: {
			nowy = new Zolw(this, polozenieX, polozenieY);
			break;
		}
		case BARSZCZ: {
			nowy = new BarszczSosnowskiego(this, polozenieX, polozenieY);
			break;
		}
		case GUARANA: {
			nowy = new Guarana(this, polozenieX, polozenieY);
			break;
		}
		case MLECZ: {
			nowy = new Mlecz(this, polozenieX, polozenieY);
			break;
		}
		case TRAWA: {
			nowy = new Trawa(this, polozenieX, polozenieY);
			break;
		}
		case WILCZEJAGODY: {
			nowy = new WilczeJagody(this, polozenieX, polozenieY);
			break;
		}
		default: {
			break;
		}
	}

	if (nowy != nullptr) {
		dodajOrganizm(nowy);
		if (sila != -1 && inicjatywa != -1 && wiek != -1) {
			nowy->setSila(sila);
			nowy->setInicjatywa(inicjatywa);
			nowy->setWiek(wiek);
		}
	}

}

void Swiat::generujSave() {
	ofstream plik;
	string nazwa;
	system("CLS");
	cout << "Podaj nazwe pliku do wygenerowania:" << endl;
	cin >> nazwa;
	nazwa += ".txt";
	plik.open(nazwa);
	plik << rozmiarX << " " << rozmiarY << " " << numerTury << " " << organizmy.size() << endl;
	for (int i = 0; i < organizmy.size(); ++i) {
		plik << organizmy[i]->generujKomende() << endl;
	}
	plik << "#ZAPIS GRY WIRTUALNY SWIAT v1.0#" << endl;
	plik << "# Damian Jankowski s188597#" << endl;
	plik << "#znak polX polY sila inicjatywa wiek#" << endl;
	plik << "#[A]ntylopa [C]zlowiek [S]uperman [L]is [O]wca [W]ilk [Z]olw#" << endl;
	plik << "#[B]arszcz [G]uarana [M]lecz [T]rawa [X]Wilczejagody#" << endl;
	plik << "#Superman - czlowiek z wlaczona umiejetnoscia#" << endl;
	plik.close();

	cout << "Wygenerowano!" << endl;

	system("pause");

}

void Swiat::wczytajSave() {

	ifstream plik;
	string nazwa;
	system("CLS");
	cout << "Podaj nazwe pliku do wczytania:" << endl;
	cin >> nazwa;
	nazwa += ".txt";
	plik.open(nazwa);

	if (!plik.good()) {
		cout << "Plik nie istnieje!" << endl;
	}
	else {
		int x, y, tura, iloscOrg;
		plik >> x >> y >> tura >> iloscOrg;
		setPlansza(x, y);
		numerTury = tura;
		cout << "SWIAT (" << x << "," << y << ") Tura:" << tura << endl;
		while (iloscOrg--) {
			char znak;
			int posx, posy, sila, inicjatywa, wiek;
			plik >> znak >> posx >> posy >> sila >> inicjatywa >> wiek;
			dodajOrganizm(znak, posx, posy, sila, inicjatywa, wiek);
		}

		plik.close();

		drukujOrganizmy();

		cout << "Wczytano!" << endl;
	}

	system("pause");
}

void Swiat::generujGre() {

	random_device device;
	mt19937 gen(device());
	int ilosc, posx, posy, rozmiarX, rozmiarY;
	char gatunki[] = { 'A','L','O','W','Z','B','G','M','T','X' };

	system("CLS");

	cout << "Podaj rozmiar swiata:" << endl;

	do {
		cin >> rozmiarX >> rozmiarY;
	} while (rozmiarX <= 0 && rozmiarY <= 0);

	setPlansza(rozmiarX, rozmiarY);

	cout << "Podaj ilosc organizmow:" << endl;

	cin >> ilosc;

	dodajOrganizm('C', rozmiarX/2, rozmiarY/2, -1, -1, -1);

	while (ilosc > getRozmiarX() * getRozmiarY()) {
		cout << "Za du¿o!";
		cin >> ilosc;
	}

	while (--ilosc) {
		int index = gen() % 10;
		do {
			posx = gen() % getRozmiarX();
			posy = gen() % getRozmiarY();
		} while (plansza[posy][posx] != nullptr);
		dodajOrganizm(gatunki[index], posx, posy, -1, -1, -1);
	}


	drukujOrganizmy();

	cout << "Wygenerowano nowa gre!" << endl;

	system("pause");
}

int Swiat::menu() {
	int klawisz = 0;
	do {

		system("CLS");
		cout << "Wirtualny swiat/C++ v1.0" << endl;
		cout << endl;
		cout << "Autor Damian Jankowski s188597" << endl;
		cout << endl;
		cout << "Poruszanie strzalkami" << endl;
		cout << endl;
		cout << "Pokaz menu - M" << endl;
		cout << endl;
		cout << "Specjalna umiejetnosc - Q" << endl;
		cout << endl;
		cout << "Pokazuj dziennik " << pokazujDziennik << " - Tab" << endl;
		cout << endl;
		cout << "Zapisz/Wczytaj gre - S/W" << endl;
		cout << endl;
		cout << "Generuj nowa gre - N" << endl;
		cout << endl;
		cout << "Zacznij gre/kolejna tura - strzalka" << endl;
		cout << endl;
		cout << "Skoncz gre - ESC" << endl << endl;

		klawisz = _getch();

		if (klawisz == TAB) {
			if (getPokazujDziennik())
				setPokazujDziennik(false);
			else {
				setPokazujDziennik(true);
			}
		}
		else if (klawisz == S_KEY) {
			generujSave();
		}
		else if (klawisz == W_KEY) {
			wczytajSave();
		}
		else if (klawisz == N_KEY) {
			generujGre();
		}
	} while (klawisz != ARROW && klawisz != ESC);

	return klawisz;
}

void Swiat::zwolnijPamiec() {
	for (int i = 0; i < organizmy.size(); i++) {
		delete organizmy[i];
	}

	organizmy.clear();
	organizmy.shrink_to_fit();
	dziennik.clear();
	dziennik.shrink_to_fit();


	for (int i = 0; i < rozmiarY; i++) {
		delete[] plansza[i];
	}
	delete[] plansza;
}

Swiat::~Swiat() {
	zwolnijPamiec();
	cout << "Koniec gry!" << endl;
}
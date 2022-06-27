#include "Organizm.h"
#include "Roslina.h"

char Organizm::rysowanie() const {
	return znak;
}
void Organizm::setZnak(char znak) {
	this->znak = znak;
}
string Organizm::getNazwa() const {
	return nazwa;
}
void Organizm::setNazwa(string nazwa) {
	this->nazwa = nazwa;
}
void Organizm::setX(int x) {
	this->polozenieX = x;
}
void Organizm::setY(int y) {
	this->polozenieY = y;
}
int Organizm::getX() const {
	return this->polozenieX;
}
int Organizm::getY() const {
	return this->polozenieY;
}
std::ostream& operator<<(std::ostream& ostr, Organizm* o) {
	ostr << o->getNazwa() << ": Sila: " << o->getSila() << " Inicjatywa: "
		<< o->getInicjatywa() << " Lokacja(" << o->getX() << "," << o->getY() << ")"
		<< " wiek: " << o->getWiek();
	return ostr;
}
string Organizm::generujKomende() {

	string null = "";
	return null + znak + " " + to_string(polozenieX) + " " + to_string(polozenieY)
		+ " " + to_string(sila) + " " + to_string(inicjatywa) + " " + to_string(wiek);
}

bool Organizm::SprawdzLokacje(int x, int y) const {
	if (x >= swiat->getRozmiarX() || y >= swiat->getRozmiarY() ||
		x < 0 || y < 0) {
		return 1;
	}
	else return 0;
}
void Organizm::kolizja(int x, int y) {

	Organizm*** plansza = swiat->getPlansza();
	Organizm* atakowany = plansza[y][x];

	if (atakowany != nullptr && atakowany != this) {
		if (atakowany->getNazwa() == getNazwa() && atakowany->getNarodzony() == 0 && getNarodzony() == 0) {
			rozmnoz();
		}
		else if ((atakowany->getNazwa() != getNazwa()) && (getZyje() && atakowany->getZyje())) {
			atakowanie(*atakowany);
		}
		else {
			swiat->dodajWpis(getNazwa() + "(" + to_string(getX()) + "," + to_string(getY()) + ") brak miejsca! ");
		}
	}
	else {
		swiat->dodajWpis(getNazwa() + "(" + to_string(getX()) + "," + to_string(getY()) + ") sukces! ");
		plansza[getY()][getX()] = nullptr;
		setX(x);
		setY(y);
		plansza[y][x] = this;
	}

}

void Organizm::atakowanie(Organizm& atakowany) {

	Organizm*** plansza = swiat->getPlansza();

	if (atakowany.czyOdbilAtak(*this)) {
		swiat->dodajWpis(atakowany.getNazwa() + "(" + to_string(atakowany.getX()) + "," + to_string(atakowany.getY()) + ") odbil atak od " + getNazwa());
	}
	else if (atakowany.czyUniknalAtak(*this)) {
		swiat->dodajWpis(atakowany.getNazwa() + "(" + to_string(atakowany.getX()) + "," + to_string(atakowany.getY()) + ") uniknal ataku od " + getNazwa());
	}
	else if (atakowany.getSila() > getSila() || atakowany.getSila() == getSila()) {
		bool zabojczaRoslina = atakowany.czyZjadlSpecjalna(*this);
		if (zabojczaRoslina) {
			swiat->dodajWpis(getNazwa() + "(" + to_string(getX()) + "," + to_string(getY()) + ") doznal efektu od " + atakowany.getNazwa());
		}
		swiat->dodajWpis(atakowany.getNazwa() + "(" + to_string(atakowany.getX()) + "," + to_string(atakowany.getY()) + ") zabil " + getNazwa());
		setZyje(false);
		plansza[getY()][getX()] = nullptr;
	}
	else if (atakowany.getSila() < getSila()) {
		if (dynamic_cast<const Roslina*>(&atakowany)) {
			swiat->dodajWpis(getNazwa() + "(" + to_string(getX()) + "," + to_string(getY()) + ") zjadl " + atakowany.getNazwa());
		}
		if (atakowany.czyZjadlSpecjalna(*this)) {
			swiat->dodajWpis(atakowany.getNazwa() + "(" + to_string(atakowany.getX()) + "," + to_string(atakowany.getY()) + ") doznal efektu od " + getNazwa());
		}
		else {
			swiat->dodajWpis(getNazwa() + "(" + to_string(getX()) + "," + to_string(getY()) + ") zabil " + atakowany.getNazwa());
		}
		atakowany.setZyje(false);
		plansza[atakowany.getY()][atakowany.getX()] = this;
		plansza[getY()][getX()] = nullptr;
		setX(atakowany.getX());
		setY(atakowany.getY());
	}
}

Organizm::MiejsceUrodzenia Organizm::SprawdzMiejsce() const {

	int x[] = { -1,0,1 };
	int y[] = { -1,0,1 };

	MiejsceUrodzenia mu;
	int flaga = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			flaga = 0;
			if (getY() + y[i] > swiat->getRozmiarY() - 1 || getX() + x[j] > swiat->getRozmiarX() - 1 ||
				getY() + y[i] < 0 || getX() + x[j] < 0) {
				continue;
			}
			else {
				Organizm*** plansza = swiat->getPlansza();
				Organizm* miejsce = plansza[getY() + y[i]][getX() + x[j]];
				if (miejsce == nullptr) {
					flaga = 1;
				}
			}
			if (flaga) {
				mu.y = getY() + y[i];
				mu.x = getX() + x[j];
				return mu;
			}
		}
	}
	swiat->dodajWpis("Wokol " + getNazwa() + "(" + to_string(getX()) + "," + to_string(getY()) + ") nie ma miejsca");
	return mu;

}

bool Organizm::czyOdbilAtak(Organizm& atakujacy) {
	return false;
}

bool Organizm::czyUniknalAtak(Organizm& atakujacy) {
	return false;
}

bool Organizm::czyZjadlSpecjalna(Organizm& jedzacy) {
	return false;
}

int Organizm::getSila() const {
	return this->sila;
}
void Organizm::setSila(int sila) {
	this->sila = sila;
}
int Organizm::getNarodzony() const {
	return this->narodzony;
}
void Organizm::setNarodzony(int narodzony) {
	this->narodzony = narodzony;
}
void Organizm::setInicjatywa(int inicjatywa) {
	this->inicjatywa = inicjatywa;
}
int Organizm::getInicjatywa() const {
	return this->inicjatywa;
}
bool Organizm::getZyje() const {
	return zyje;
}
void Organizm::setZyje(bool zyje) {
	this->zyje = zyje;
}
int Organizm::getWiek() const {
	return wiek;
}
void Organizm::setWiek(int wiek) {
	this->wiek = wiek;
}
#include "WilczeJagody.h"

WilczeJagody::WilczeJagody(Swiat* swiat, int polozenieX, int polozenieY) {
	this->swiat = swiat;
	setX(polozenieX);
	setY(polozenieY);
	setSila(X_SILA);
	setInicjatywa(ROSLINA_INICJATYWA);
	setZnak(WILCZEJAGODY);
	setNazwa("WilczeJagody");
}

void WilczeJagody::rozmnoz() {
	MiejsceUrodzenia wynik = SprawdzMiejsce();
	if (wynik.x != -1 && wynik.y != -1) {
		Organizm* dziecko = new WilczeJagody(swiat, wynik.x, wynik.y);
		dziecko->setNarodzony(COOLDOWN_NA_RODZENIE);
		swiat->dodajOrganizm(dziecko);
	}
}

bool WilczeJagody::czyZjadlSpecjalna(Organizm& jedzacy)
{
	Organizm*** plansza = swiat->getPlansza();
	setZyje(false);
	plansza[getY()][getX()] = nullptr;
	return true;
}

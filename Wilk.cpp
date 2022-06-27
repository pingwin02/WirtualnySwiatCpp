#include "Wilk.h"

Wilk::Wilk(Swiat* swiat, int polozenieX, int polozenieY) {
	this->swiat = swiat;
	setX(polozenieX);
	setY(polozenieY);
	setSila(W_SILA);
	setInicjatywa(W_INICJATYWA);
	setZnak(WILK);
	setNazwa("Wilk");
}
void Wilk::rozmnoz() {
	MiejsceUrodzenia wynik = SprawdzMiejsce();
	if (wynik.x != -1 && wynik.y != -1) {
		Organizm* dziecko = new Wilk(swiat, wynik.x, wynik.y);
		dziecko->setNarodzony(COOLDOWN_NA_RODZENIE);
		swiat->dodajOrganizm(dziecko);
		swiat->dodajWpis(getNazwa() + "(" + to_string(getX()) + "," + to_string(getY()) + ") rozmnozyl sie! ");
	}
}

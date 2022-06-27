#include "Guarana.h"

Guarana::Guarana(Swiat* swiat, int polozenieX, int polozenieY) {
	this->swiat = swiat;
	setX(polozenieX);
	setY(polozenieY);
	setSila(G_SILA);
	setInicjatywa(ROSLINA_INICJATYWA);
	setZnak(GUARANA);
	setNazwa("Guarana");
}

void Guarana::rozmnoz() {
	MiejsceUrodzenia wynik = SprawdzMiejsce();
	if (wynik.x != -1 && wynik.y != -1) {
		Organizm* dziecko = new Guarana(swiat, wynik.x, wynik.y);
		dziecko->setNarodzony(COOLDOWN_NA_RODZENIE);
		swiat->dodajOrganizm(dziecko);
	}
}

bool Guarana::czyZjadlSpecjalna(Organizm& jedzacy)
{
	jedzacy.setSila(jedzacy.getSila() + MOC_GUARANY);
	return true;
}

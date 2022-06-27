#include "BarszczSosnowskiego.h"
#include "Zwierze.h"

BarszczSosnowskiego::BarszczSosnowskiego(Swiat* swiat, int polozenieX, int polozenieY) {
	this->swiat = swiat;
	setX(polozenieX);
	setY(polozenieY);
	setSila(B_SILA);
	setInicjatywa(ROSLINA_INICJATYWA);
	setZnak(BARSZCZ);
	setNazwa("BarszczSosnowskiego");
}

void BarszczSosnowskiego::akcja() {

	int x[] = { -1,0,1 };
	int y[] = { -1,0,1 };

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (getY() + y[i] > swiat->getRozmiarY() - 1 || getX() + x[j] > swiat->getRozmiarX() - 1 ||
				getY() + y[i] < 0 || getX() + x[j] < 0) {
				continue;
			}
			else {
				Organizm*** plansza = swiat->getPlansza();
				Organizm* miejsce = plansza[getY() + y[i]][getX() + x[j]];
				if (miejsce != nullptr && dynamic_cast<Zwierze*>(miejsce)) {
					swiat->dodajWpis(getNazwa() + "(" + to_string(getX()) + "," + to_string(getY()) + ") zabil " + miejsce->getNazwa());
					miejsce->setZyje(false);
					plansza[getY() + y[i]][getX() + x[j]] = nullptr;
				}
			}
		}
	}

	Roslina::akcja();
}

void BarszczSosnowskiego::rozmnoz() {
	MiejsceUrodzenia wynik = SprawdzMiejsce();
	if (wynik.x != -1 && wynik.y != -1) {
		Organizm* dziecko = new BarszczSosnowskiego(swiat, wynik.x, wynik.y);
		dziecko->setNarodzony(COOLDOWN_NA_RODZENIE);
		swiat->dodajOrganizm(dziecko);
	}
}

bool BarszczSosnowskiego::czyZjadlSpecjalna(Organizm& jedzacy) {
	Organizm*** plansza = swiat->getPlansza();
	setZyje(false);
	plansza[getY()][getX()] = nullptr;
	return true;
}

#include "Czlowiek.h"

Czlowiek::Czlowiek(Swiat* swiat, int polozenieX, int polozenieY) {
	this->swiat = swiat;
	setX(polozenieX);
	setY(polozenieY);
	setSila(C_SILA);
	setInicjatywa(C_INICJATYWA);
	setZnak(CZLOWIEK);
	setNazwa("Czlowiek");
	this->mnoznik = 1;
	this->cooldown = 0;
}

void Czlowiek::akcja() {

	int y = getY(), x = getX();
	if (GetAsyncKeyState('Q') && cooldown == 0) {
		setCooldown(UMIEJETNOSC_COOLDOWN);
		setZnak(CZLOWIEK_S);
	}
	mnoznik = 1;
	if (cooldown > 5) {
		mnoznik = 2;
		swiat->dodajWpis("Umiejetnosc Szybkosc antylopy aktywna jeszcze przez " + to_string(cooldown - 5) + " tur");
	}
	else if (cooldown < 8 && cooldown > 5) {
		random_device device;
		mt19937 gen(device());
		swiat->dodajWpis("Prawdopodobienstwo 50%");
		mnoznik = gen() % 2 + 1;
	}
	else if (cooldown == 5) {
		setZnak(CZLOWIEK);
	}
	if (cooldown < 6 && cooldown > 0) {
		swiat->dodajWpis("Nie mozesz uzyc umiejetnosci jeszcze przez " + to_string(cooldown) + " tur");
	}
	if (cooldown > 0) {
		cooldown--;
	}

	if (GetAsyncKeyState(VK_UP)) {
		if (getY() > -1 + mnoznik)
			y -= mnoznik;
	}
	if (GetAsyncKeyState(VK_DOWN)) {
		if (getY() < swiat->getRozmiarY() - mnoznik)
			y += mnoznik;
	}
	if (GetAsyncKeyState(VK_RIGHT)) {
		if (getX() < swiat->getRozmiarX() - mnoznik)
			x += mnoznik;
	}
	if (GetAsyncKeyState(VK_LEFT)) {
		if (getX() > -1 + mnoznik)
			x -= mnoznik;
	}
	swiat->dodajWpis(this, getX(), getY(), x, y);
	kolizja(x, y);

}

void Czlowiek::rozmnoz() {
	//Czlowiek sie nie rozmnaza
}

void Czlowiek::setCooldown(int cooldown) {
	if (this->cooldown == 0)
	this->cooldown = cooldown;
}

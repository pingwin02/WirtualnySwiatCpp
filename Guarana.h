#pragma once

#include "Roslina.h"

class Guarana : public Roslina {
public:
	Guarana(Swiat* swiat, int polozenieX, int polozenieY);
	void rozmnoz() override;
	bool czyZjadlSpecjalna(Organizm& jedzacy) override;
};
#pragma once

#include "Roslina.h"

class WilczeJagody : public Roslina {
public:
	WilczeJagody(Swiat* swiat, int polozenieX, int polozenieY);
	void rozmnoz() override;
	bool czyZjadlSpecjalna(Organizm& jedzacy) override;
};
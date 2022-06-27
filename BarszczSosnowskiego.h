#pragma once

#include "Roslina.h"

class BarszczSosnowskiego : public Roslina {
public:
	BarszczSosnowskiego(Swiat* swiat, int polozenieX, int polozenieY);
	void akcja() override;
	void rozmnoz() override;
	bool czyZjadlSpecjalna(Organizm& jedzacy) override;
};
#pragma once

#include "Roslina.h"

class Trawa : public Roslina {
public:
	Trawa(Swiat* swiat, int polozenieX, int polozenieY);
	void rozmnoz() override;
};
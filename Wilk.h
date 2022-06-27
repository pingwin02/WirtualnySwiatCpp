#pragma once

#include "Zwierze.h"

class Wilk : public Zwierze {
public:
	Wilk(Swiat* swiat, int polozenieX, int polozenieY);
	void rozmnoz() override;
};
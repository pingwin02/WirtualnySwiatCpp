#pragma once

#include "Organizm.h"

#include <random>

class Roslina : public Organizm {
public:
	virtual void akcja() override;
	virtual void rozmnoz() = 0;
};
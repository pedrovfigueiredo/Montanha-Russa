/*
 * Parque.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Parque.h"


Parque::Parque(int nPassageiros)
:numPassageiros(nPassageiros)
{
    this->DisplayCount = 1;
    this->distribuidorTicket = 1;
}

Parque::~Parque() {}

int Parque::getNumPassageiros() {
	return numPassageiros;
}

void Parque::setNumPassageiros(int num) {
	numPassageiros = num;
}

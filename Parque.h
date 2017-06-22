/*
 * Parque.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef PARQUE_H_
#define PARQUE_H_
#include <iostream>

class Parque {
public:
	Parque(int nPassageiros);
	virtual ~Parque();

	int getNumPassageiros();
	void setNumPassageiros(int num);
    
    // Similar ao next do algoritmo do ticket
    int DisplayCount;
    int distribuidorTicket;
    int numPassageiros;
};

#endif /* PARQUE_H_ */

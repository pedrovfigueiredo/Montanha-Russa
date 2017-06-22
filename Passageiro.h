/*
 * Passageiro.h
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#ifndef PASSAGEIRO_H_
#define PASSAGEIRO_H_

#include "Thread.h"
#include "Carro.h"
#include <iostream>

class Passageiro: public Thread {
public:
	Passageiro(Carro &c);
	virtual ~Passageiro();
	void entraNoCarro();
	void esperaVoltaAcabar();
	void saiDoCarro();
	void passeiaPeloParque();
	bool parqueFechado();
    int nVoltas;

	void run();
private:
    int idPassageiro_;
    void pegarNovoTicket();
	Carro &carro;
    int ticket;
};

#endif /* PASSAGEIRO_H_ */

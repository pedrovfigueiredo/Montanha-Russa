/*
 * Sincronizador.h
 *
 *  Created on: 18 de abr de 2017
 *      Author: bruno
 */

#ifndef SINCRONIZADOR_H_
#define SINCRONIZADOR_H_

#include <pthread.h>

class Sincronizador {
public:
	static pthread_mutex_t lock;

	Sincronizador();
	virtual ~Sincronizador();
	static int FetchAndAdd(int& num, int incr);
};

#endif /* SINCRONIZADOR_H_ */

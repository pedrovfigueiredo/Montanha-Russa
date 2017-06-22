/*
 * Sincronizador.cpp
 *
 *  Created on: 18 de abr de 2017
 *      Author: bruno
 */

#include "include/Sincronizador.h"

pthread_mutex_t Sincronizador::lock = PTHREAD_MUTEX_INITIALIZER;

Sincronizador::Sincronizador() {
}

Sincronizador::~Sincronizador() {
}

int Sincronizador::FetchAndAdd(int &num, int incr) {
	pthread_mutex_lock(&lock);

	int tmp = num;
	num = num + incr;

	pthread_mutex_unlock(&lock);

	return tmp;
}

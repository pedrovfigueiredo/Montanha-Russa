/*
 * Carro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Carro.h"
#include "Sincronizador.h"
#include <thread>
#include <chrono>

int Carro::capacidade = 0;

Carro::Carro(Parque &p)
:parque(p) {
	this->voltas = 0;
	Carro::capacidade = p.getNumPassageiros() / 2;
	this->nPassageiros = 0;
    this->desembarcando = false;
}

Carro::~Carro() {}

int Carro::getCapacidade(){ return capacidade; }

void Carro::esperaEncher() {
    while (!this->estaCheio()){
        // Se não tiverem mais passageiros no parque, terminar thread
        if (!this->parque.getNumPassageiros()) {
            pthread_mutex_lock(&Sincronizador::lock);
            std::clog << "Não há mais pessoas no parque. Encerrando..." << std::endl;
            pthread_mutex_unlock(&Sincronizador::lock);
            this->terminate();
        }
    }
}

void Carro::daUmaVolta() {
    pthread_mutex_lock(&Sincronizador::lock);
    std::clog << "Carro está na montanha russa..." << std::endl;
    pthread_mutex_unlock(&Sincronizador::lock);
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void Carro::esperaEsvaziar() {
    this->desembarcando = true;
    while (this->nPassageiros > 0);
    pthread_mutex_lock(&Sincronizador::lock);
    std::clog << "Carro vazio.\n";
    pthread_mutex_unlock(&Sincronizador::lock);
    this->desembarcando = false;
}

int Carro::getNVoltas() {
	return voltas;
}

Parque& Carro::getParque() {
	return parque;
}

bool Carro::estaCheio() {
    if (this->nPassageiros < this->capacidade)
        return false;
    
    return true;
}

void Carro::run() {
	while (parque.getNumPassageiros() > 0) {
		esperaEncher();

		daUmaVolta();

		esperaEsvaziar();
        
		voltas++;
        pthread_mutex_lock(&Sincronizador::lock);
        std::clog << "Volta " << voltas << " completa." <<  std::endl;
        pthread_mutex_unlock(&Sincronizador::lock);
        
	}
}

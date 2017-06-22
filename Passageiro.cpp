/*
 * Passageiro.cpp
 *
 *  Created on: 17 de abr de 2017
 *      Author: bruno
 */

#include "include/Passageiro.h"
#include "Sincronizador.h"
#include <thread>
#include <chrono>

#define MAX_NUM_VOLTAS 10

Passageiro::Passageiro(Carro &c)
:carro(c)
{
    this->pegarNovoTicket();
    this->idPassageiro_ = ticket;
    this->nVoltas = 0;
}

Passageiro::~Passageiro() {
    // Decrementa o numero de passageiros no parque
    // Essa operação há de ser atômica, já que mais de uma thread acessa e decrementa essa variável.
    Parque* parque = &carro.getParque();
    Sincronizador::FetchAndAdd(parque->numPassageiros, -1);
    
    pthread_mutex_lock(&Sincronizador::lock);
    std::clog << "Passageiro " << this->idPassageiro_ << " saiu do parque. Número de voltas dadas: " << nVoltas << std::endl;
    pthread_mutex_unlock(&Sincronizador::lock);
}

void Passageiro::entraNoCarro() {
    
    // Só passa do while se tiver lugar disponível no carro, se ticket for igual ao que o display mostrar e se o carro não estiver desembarcando.
    while(this->ticket != (this->carro.getParque()).DisplayCount || carro.estaCheio() || carro.desembarcando);
    
    pthread_mutex_lock(&Sincronizador::lock);
    std::clog << "Passageiro " << this->idPassageiro_ << " entrou no carro.\n";
    pthread_mutex_unlock(&Sincronizador::lock);
    this->carro.nPassageiros++;
    
    ((this->carro.getParque()).DisplayCount)++;
}

void Passageiro::esperaVoltaAcabar() {
    while (!carro.desembarcando){
        if (parqueFechado()) {
            pthread_mutex_lock(&Sincronizador::lock);
            std::clog << "Passageiro " << this->idPassageiro_ << " não pôde completar a volta pois o parque fechou." << std::endl;
            pthread_mutex_unlock(&Sincronizador::lock);
            return;
        }
    }
    this->nVoltas++;
}

void Passageiro::saiDoCarro() {
    // Usa-se fetch-and-add para garantir que todas as 5 threads que saem do carro decrementem de forma atômica a variável de controle nPassageiros, de modo a evitar deadlocks.
    Sincronizador::FetchAndAdd(this->carro.nPassageiros, -1);
    pthread_mutex_lock(&Sincronizador::lock);
    std::clog << "Passageiro " << this->idPassageiro_ << " desembarcou.\n";
    pthread_mutex_unlock(&Sincronizador::lock);
}

void Passageiro::passeiaPeloParque() {
    pthread_mutex_lock(&Sincronizador::lock);
    std::clog << "Passageiro " << this->idPassageiro_ << " passeando pelo parque...\n";
    pthread_mutex_unlock(&Sincronizador::lock);
    std::this_thread::sleep_for(std::chrono::seconds((rand() % 10) + 1));
    //std::this_thread::sleep_for(std::chrono::seconds(3));
    this->pegarNovoTicket();
}

bool Passageiro::parqueFechado() {
	if (this->carro.getNVoltas() < MAX_NUM_VOLTAS)
		return false;

	return true;
}

void Passageiro::pegarNovoTicket(){
    Parque* parque = &carro.getParque();
    this->ticket = Sincronizador::FetchAndAdd(parque->distribuidorTicket, 1);
}

void Passageiro::run() {
	while (!parqueFechado()) {
		entraNoCarro(); // protocolo de entrada

		esperaVoltaAcabar();

		saiDoCarro(); // protocolo de saida

		passeiaPeloParque(); // secao nao critica
        
	}
    
    this->~Passageiro();
    
}


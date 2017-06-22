#include <iostream>
#include <vector>
#include "Thread.h"
#include "Carro.h"
#include "Parque.h"
#include "Passageiro.h"
#include "Sincronizador.h"

int main() {
    
    int numThreads = 10;
    
    Parque* parque;
    Carro* carro;
    std::vector<Passageiro*> passageiros;
    
    parque = new Parque(numThreads);
    carro = new Carro(*parque);
    
    carro->start();
    
    for (auto i = 0; i < numThreads; i++) {
        passageiros.push_back(new Passageiro(*carro));
        passageiros[i]->start();
    }
    
    carro->join();
    
	return 0;
}

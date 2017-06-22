/*
 * Thread.cpp
 *
 *  Created on: 16 de abr de 2017
 *      Author: Suporte
 */

#include "include/Thread.h"
#include <iostream>

Thread::Thread() {}

Thread::~Thread() {}

void Thread::start() {
	pthread_create(&id, NULL, staticRun, this);
}

void Thread::join() {
	pthread_join(id, NULL);
}

pthread_t Thread::getId() {
	return id;
}

void Thread::terminate(){
    pthread_exit(0);
}

void *Thread::staticRun(void *args) {
	Thread *t = (Thread*) args;

	t->run();

	return NULL;
}



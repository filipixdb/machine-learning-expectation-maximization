/*
 * Principal.h
 *
 *  Created on: 13/11/2012
 *      Author: Filipi
 */


#ifndef MAIN_H_
#define MAIN_H_

#include "Algoritmo.h"


class Principal {
public:
	Principal();
	virtual ~Principal();
	int totalAmostras;


private:

	Algoritmo * algoritmo;
	Algoritmo * algoritmoExp;
	Amostra * amostras[50];
	Amostra * amostrasExp[50];

	void iniciaAmostras();
	void iniciaParametros();
	void rodaEtapaE();
	void rodaEtapaM();

	void Go();


};

#endif /* MAIN_H_ */

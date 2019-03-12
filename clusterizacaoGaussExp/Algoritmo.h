/*
 * Algoritmo.h
 *
 *  Created on: 13/11/2012
 *      Author: Filipi
 */

#ifndef ALGORITMO_H_
#define ALGORITMO_H_

#define EPSILON 0.001
#define MAXITERACOES 20

#include "Amostra.h"
#include <boost/math/distributions.hpp>


class Algoritmo {
public:
	Algoritmo();
	Algoritmo(Amostra * a[], int x);
	virtual ~Algoritmo();

	void etapaE(Amostra *amostras[]);
	void etapaM(Amostra *amostras[]);

	double getOldLikelyhood();
	double getNewLikelyhood();

	double calculaLikelihood();

	//para a exponencial
	Algoritmo(Amostra * a[], int x, int ehExponencial);

	void etapaEExp(Amostra *amostras[]);
	void etapaMExp(Amostra *amostras[]);

	double getOldLikelyhoodExp();
	double getNewLikelyhoodExp();

	double calculaLikelihoodExp();

private:

	int totalAmostras;

	Amostra **amostras;

	double mean1;
	double mean2;

	double var1;
	double var2;

	double pi1;
	double pi2;

	double oldLikelyhood;
	double newLikelyhood;

//responsibilities
	double *resp1;
	double *resp2;


	//para a exponencial
	double lambda1;
	double lambda2;

};

#endif /* ALGORITMO_H_ */

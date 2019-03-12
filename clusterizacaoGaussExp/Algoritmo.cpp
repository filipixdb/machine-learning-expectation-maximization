/*
 * Algoritmo.cpp
 *
 *  Created on: 13/11/2012
 *      Author: Filipi
 */

#include "Algoritmo.h"
#include <boost/math/special_functions/log1p.hpp>
#include <boost/math/distributions/normal.hpp>


using namespace std;
using namespace boost::math;

Algoritmo::Algoritmo( ) {

}


Algoritmo::Algoritmo(Amostra **a, int x) {

	totalAmostras = x;

	this->amostras = a;

	//iniciar os parametros das 2 gaussianas
	mean1 = 2.0;
	mean2 = 13.0;

	var1 = 5;
	var2 = 5;

	pi1 = 0.0;
	pi2 = 0.0;

	resp1 = (double*) malloc(totalAmostras * sizeof(double));
	resp2 = (double*) malloc(totalAmostras * sizeof(double));

	for (int i = 0; i<totalAmostras; i++){
		resp1[i] = 0.6;
		resp2[i] = 0.4;

		pi1+=resp1[i];
		pi2+=resp2[i];

	}

	pi1 = pi1/totalAmostras;
	pi2 = pi2/totalAmostras;


	newLikelyhood = 0.0;
	//calcular aqui o likelyhood dos parametros chutados
	oldLikelyhood = calculaLikelihood();

	cout << "Likelyhood inicial: " << oldLikelyhood << endl;

}

Algoritmo::~Algoritmo() {
	// TODO Auto-generated destructor stub
}



void Algoritmo::etapaE(Amostra * amostras[]){

	//preciza ter as means u_k
	//precisa ter as covariancias sum_k
	//precisa ter mixing coeficientes pi_k

	//calcular as responsibilities
	for (int i =0; i < totalAmostras; i++){

		double numerador1;
		double numerador2;

		normal_distribution<> d1(mean1, sqrt(var1));
		normal_distribution<> d2(mean2, sqrt(var2));

		numerador1 = ( pi1 * (pdf( d1, amostras[i]->getValor()) + DBL_MIN) );
		numerador2 = ( pi2 * (pdf( d2, amostras[i]->getValor()) + DBL_MIN) );

		resp1[i] = ( numerador1 / (numerador1+numerador2) );
		resp2[i] = ( numerador2 / (numerador1+numerador2) );

		//cout << "Novos gamas amostra " << i <<  " : " << resp1[i] << " ; " << resp2[i] <<endl;

	}

}

void Algoritmo::etapaM(Amostra * amostras[]){

	//precisa das responsibilities

	//reestimar os parametros

	//calcula N_k ; pi_k ; means
	double N1 = 0.0;
	double N2 = 0.0;
	mean1 = 0.0;
	mean2 = 0.0;
	for (int i = 0; i<totalAmostras; i++){
		N1+=resp1[i];
		N2+=resp2[i];

		mean1 += ( resp1[i] * amostras[i]->getValor() );
		mean2 += ( resp2[i] * amostras[i]->getValor() );

	}

	mean1 = mean1/N1;
	mean2 = mean2/N2;

	pi1 = N1/totalAmostras;
	pi2 = N2/totalAmostras;


	//calcular vars
	var1 = 0.0;
	var2 = 0.0;
	for ( int i =0; i < totalAmostras; i++){
		var1 += ( resp1[i] * (amostras[i]->getValor() - mean1 ) * (amostras[i]->getValor() - mean1 ) );
		var2 += ( resp2[i] * (amostras[i]->getValor() - mean2 ) * (amostras[i]->getValor() - mean2 ) );
	}

	var1 = var1/N1;
	var2 = var2/N2;

}


double Algoritmo::calculaLikelihood(){

	double likelyHood = 0.0;

	normal_distribution<> d1(mean1, sqrt(var1));
	normal_distribution<> d2(mean2, sqrt(var2));


	for (int i = 0; i < totalAmostras; i++){

		double somaLikesAosClusters = 0;

		somaLikesAosClusters += ( pi1 * (pdf( d1, amostras[i]->getValor()) + DBL_MIN) );
		somaLikesAosClusters += ( pi2 * (pdf( d2, amostras[i]->getValor()) + DBL_MIN) );

		//cout << "Amostra " << i << " - LikesAosClusters " << somaLikesAosClusters << " - log " << log(somaLikesAosClusters) << endl;

		likelyHood += log(somaLikesAosClusters);

	}

	return likelyHood;

}


double Algoritmo::getOldLikelyhood(){
	return this->oldLikelyhood;
}

double Algoritmo::getNewLikelyhood(){
	return this->newLikelyhood;
}


//// para a exponencial
Algoritmo::Algoritmo(Amostra **a, int x, int ehExponencial) {

	totalAmostras = x;

	this->amostras = a;

	//iniciar os parametros das 2 gaussianas
	lambda1 = 5.0;
	lambda2 = 20.0;

	pi1 = 0.0;
	pi2 = 0.0;

	resp1 = (double*) malloc(totalAmostras * sizeof(double));
	resp2 = (double*) malloc(totalAmostras * sizeof(double));

	for (int i = 0; i<totalAmostras; i++){
		resp1[i] = 0.4;
		resp2[i] = 0.6;

		pi1+=resp1[i];
		pi2+=resp2[i];

	}

	pi1 = pi1/totalAmostras;
	pi2 = pi2/totalAmostras;


	newLikelyhood = 0.0;
	//calcular aqui o likelyhood dos parametros chutados
	oldLikelyhood = calculaLikelihoodExp();

	cout << "Likelyhood inicial: " << oldLikelyhood << endl;

}


double Algoritmo::calculaLikelihoodExp(){

	double likelyHood = 0.0;

	exponential_distribution<> d1(lambda1);
	exponential_distribution<> d2(lambda2);


	for (int i = 0; i < totalAmostras; i++){

		double somaLikesAosClusters = 0;

		somaLikesAosClusters += ( pi1 * (pdf( d1, amostras[i]->getValor()) + DBL_MIN) );
		somaLikesAosClusters += ( pi2 * (pdf( d2, amostras[i]->getValor()) + DBL_MIN) );

		//cout << "Amostra " << i << " - LikesAosClusters " << somaLikesAosClusters << " - log " << log(somaLikesAosClusters) << endl;

		likelyHood += log(somaLikesAosClusters);

	}

	return likelyHood;

}

void Algoritmo::etapaEExp(Amostra * amostras[]){

	//preciza ter as means u_k
	//precisa ter as covariancias sum_k
	//precisa ter mixing coeficientes pi_k

	//calcular as responsibilities
	for (int i =0; i < totalAmostras; i++){

		double numerador1;
		double numerador2;

		exponential_distribution<> d1(lambda1);
		exponential_distribution<> d2(lambda2);


		numerador1 = ( pi1 * (pdf( d1, amostras[i]->getValor()) + DBL_MIN) );
		numerador2 = ( pi2 * (pdf( d2, amostras[i]->getValor()) + DBL_MIN) );

		resp1[i] = ( numerador1 / (numerador1+numerador2) );
		resp2[i] = ( numerador2 / (numerador1+numerador2) );

		//cout << "Novos gamas amostra " << i <<  " : " << resp1[i] << " ; " << resp2[i] <<endl;

	}

}

void Algoritmo::etapaMExp(Amostra * amostras[]){

	//precisa das responsibilities

	//reestimar os parametros

	//calcula N_k ; pi_k ; means
	double N1 = 0.0;
	double N2 = 0.0;
	lambda1 = 0.0;
	lambda2 = 0.0;
	for (int i = 0; i<totalAmostras; i++){
		N1+=resp1[i];
		N2+=resp2[i];

		lambda1 += ( resp1[i] * amostras[i]->getValor() );
		lambda2 += ( resp2[i] * amostras[i]->getValor() );

	}

	lambda1 = N1/lambda1;
	lambda2 = N2/lambda2;

	pi1 = N1/totalAmostras;
	pi2 = N2/totalAmostras;

}

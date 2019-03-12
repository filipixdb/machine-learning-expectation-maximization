/*
 * Main.cpp
 *
 *  Created on: 13/11/2012
 *      Author: Filipi
 */

#include "Principal.h"

#include "Algoritmo.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>

using namespace std;

Principal::Principal() {
	// TODO Auto-generated constructor stub

	totalAmostras = 0;

	ifstream source;

	source.open("amostras.txt", ios_base::in);

	if (!source){

		cout << "Erro ao abrir arquivo amostras.txt" << endl ;

	}else{

		double x;
		string line;
		while (getline(source, line)){

			istringstream in(line);

			in >> x;

			cout << "Entrada lida: " << x << endl;

			amostras[totalAmostras] = new Amostra(x);
			amostrasExp[totalAmostras] = new Amostra(x);
			totalAmostras++;

		}
	}

	cout << "Terminou de ler as entradas" << endl;
	cout << "Total " << totalAmostras << " lidas" <<endl;

	algoritmo = new Algoritmo(amostras, totalAmostras);
	algoritmoExp = new Algoritmo(amostrasExp, totalAmostras, 1);

	Go();

}

Principal::~Principal() {
	// TODO Auto-generated destructor stub
}


void Principal::Go(){

	int iteracoes = 0;

	while ( ((algoritmo->getNewLikelyhood() - algoritmo->getOldLikelyhood()) > EPSILON ) && (iteracoes < MAXITERACOES) ){

		//roda o E
		algoritmo->etapaE(amostras);

		//roda o M
		algoritmo->etapaM(amostras);

		iteracoes++;

		//faz outras coisas, como exibir resultado
		cout << "Rodou uma iteracao" << endl;

		cout << "LogLike atualizado: " << algoritmo->calculaLikelihood() << endl ;

	}

	iteracoes = 0;

	while ( ((algoritmoExp->getNewLikelyhood() - algoritmoExp->getOldLikelyhood()) > EPSILON ) && (iteracoes < MAXITERACOES) ){

		//roda o E
		algoritmoExp->etapaEExp(amostrasExp);

		//roda o M
		algoritmoExp->etapaMExp(amostrasExp);

		iteracoes++;

		//faz outras coisas, como exibir resultado
		cout << "Rodou uma iteracao Exp" << endl;

		cout << "LogLike Exp atualizado: " << algoritmoExp->calculaLikelihoodExp() << endl ;

	}


}

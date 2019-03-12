/*
 * Amostra.cpp
 *
 *  Created on: 13/11/2012
 *      Author: Filipi
 */

#include "Amostra.h"
#include <iostream>

using namespace std;

Amostra::Amostra() {
	// TODO Auto-generated constructor stub

	this->cluster = 0;
	this->valor = 0.0;

}


Amostra::~Amostra() {
	// TODO Auto-generated destructor stub
}

Amostra::Amostra(double v){
	this->cluster = 0;
	this->valor = v;

	cout << "Criou amostra " << valor << endl;

}


void Amostra::setCluster(int c){
	this->cluster = c;
}

double Amostra::getValor(){
	return this->valor;
}

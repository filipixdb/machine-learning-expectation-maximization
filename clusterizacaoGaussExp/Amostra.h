/*
 * Amostra.h
 *
 *  Created on: 13/11/2012
 *      Author: Filipi
 */

#ifndef AMOSTRA_H_
#define AMOSTRA_H_

class Amostra {
public:
	Amostra();

	Amostra(double v);

	virtual ~Amostra();

	void setCluster(int c);
	double getValor();

private:
	int cluster;
	double valor;
};

#endif /* AMOSTRA_H_ */

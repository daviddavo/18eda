#ifndef __C07_H_
#define __C07_H_

#include "arbin.h"

unsigned int numero_singulares(const Arbin<int>&a, int sumAntes, int & cnt) {
	if (a.esVacio()) return 0;

	int sumDespues = numero_singulares(a.hijoIz(), sumAntes + a.raiz(), cnt)
			+ numero_singulares(a.hijoDer(), sumAntes + a.raiz(), cnt);

	if (sumDespues == sumAntes) cnt++;
	return sumDespues + a.raiz();
}

unsigned int numero_singulares(Arbin<int> const& a) {
	int ret = 0;
	numero_singulares(a, 0, ret);
	return ret;
}

#endif

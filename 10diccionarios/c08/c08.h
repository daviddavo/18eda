#ifndef __C08_H_
#define __C08_H_

#include <iostream>

#include "lista.h"
#include "diccionario.h"

// Clase Puntuacion. Sirve para representar la puntuacion final  (nota)
// obtenida por un alumno.
class Puntuacion {
  public:
    string alumno;
    int nota;	
	Puntuacion(const string& nombre, int puntuacion): alumno(nombre), nota(puntuacion) {}
};

void califica(const Lista<string>& bien, const Lista<string>& mal, Lista<Puntuacion>& listado) {
	Diccionario<string,int> sol = Diccionario<string,int>();

	auto it = bien.cbegin();

	while(it != bien.cend()) {
		if (sol.contiene(it.elem())) {
			sol.inserta(it.elem(), sol.valorPara(it.elem())+1);
		} else {
			sol.inserta(it.elem(), 1);
		}

		it.next();
	}

	it = mal.cbegin();
	while(it != mal.cend()) {
		if (sol.contiene(it.elem())) {
			sol.inserta(it.elem(), sol.valorPara(it.elem())-1);
		} else {
			sol.inserta(it.elem(), -1);
		}

		it.next();
	}

	auto dit = sol.cbegin();
	while (dit != sol.cend()) {
		if (dit.valor() != 0)
			listado.pon_final(Puntuacion(dit.clave(), dit.valor()));

		dit.next();
	}
}


void imprimePuntuaciones(ostream & ss, Lista<Puntuacion>& listado) {
  Lista<Puntuacion>::ConstIterator i = listado.cbegin();
  Lista<Puntuacion>::ConstIterator e = listado.cend();
  while (i != e) {
	  ss << "[" << i.elem().alumno << ":" << i.elem().nota << "]";
      i.next();	  
  }
}

void leeResultados(istream & ss, Lista<string>& bien, Lista<string>& mal) {
	string nombre;
	do {
		ss >> nombre;
		if (nombre != "#") {
			string resultado;
			ss >> resultado;
			if (resultado == "+")
				bien.pon_final(nombre);
			else
				mal.pon_final(nombre);
		}
	} while (nombre != "#");
}

#endif /* __C08_H_ */
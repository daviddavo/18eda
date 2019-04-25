#include "c08.h"
#include <iostream>
#include <string>
using namespace std;

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


void imprimePuntuaciones(Lista<Puntuacion>& listado) {
  Lista<Puntuacion>::ConstIterator i = listado.cbegin();
  Lista<Puntuacion>::ConstIterator e = listado.cend();
  while (i != e) {
	  cout << "[" << i.elem().alumno << ":" << i.elem().nota << "]";
      i.next();	  
  }  
  cout << endl;
}

void leeResultados(Lista<string>& bien, Lista<string>& mal) {
	string nombre;
	do {
		cin >> nombre;
		if (nombre != "#") {
			string resultado;
			cin >> resultado;
			if (resultado == "+")
				bien.pon_final(nombre);
			else
				mal.pon_final(nombre);
		}
	} while (nombre != "#");
}

int main() {
  string comienzo;
  while (cin >> comienzo) {
	 Lista<string> bien;
	 Lista<string> mal;
	 Lista<Puntuacion> listado;
	 leeResultados(bien, mal);
	 califica(bien, mal,listado);
	 imprimePuntuaciones(listado);
  }
  return 0;   
}
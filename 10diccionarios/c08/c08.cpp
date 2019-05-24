#include "c08.h"
#include <string>
using namespace std;

void imprimePuntuaciones(Lista<Puntuacion>& listado) {
	imprimePuntuaciones(cout, listado);
	cout << endl;
}

void leeResultados(Lista<string>& bien, Lista<string>& mal) {
	leeResultados(cin, bien, mal);
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
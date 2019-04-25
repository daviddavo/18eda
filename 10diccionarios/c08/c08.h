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

void califica(const Lista<string>& bien, const Lista<string>& mal, Lista<Puntuacion>& listado);
void imprimePuntuaciones(Lista<Puntuacion>& listado);
void leeResultados(Lista<string>& bien, Lista<string>& mal);
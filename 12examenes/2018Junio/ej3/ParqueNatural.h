#ifndef _PARQUE_NATURAL_H
#define _PARQUE_NATURAL_H

#include "diccionario.h"
#include "lista.h"
#include <string>
using namespace std;


/*
 Excepciones levantadas por las operaciones
*/
class EEcosistemaDuplicado {};

class EEcosistemaNoExiste {};


class ParqueNatural {
public:
   ParqueNatural();
   void an_ecosistema(const string& ecosistema);
   void an_ejemplares(const string& ecosistema, const string& especie, int n);
   Lista<string> lista_especies_ecosistema(const string& ecosistema, int n) const;
   int numero_ejemplares_en_ecosistema(const string& ecosistema, const string& especie) const;
   Lista<string> lista_especies_parque() const;
   int numero_ejemplares_en_parque(const string& especie) const;
   
private:
  /*** Incluir los detalles de representación que se consideren oportunos */
  
};
 
#endif
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

/** Definición de tipos para hacernos la vida más fácil */
typedef string tEcosistema ;
typedef string tEspecie;

class ParqueNatural {
public:

   ParqueNatural();
   void an_ecosistema(const tEcosistema& ecosistema);
   void an_ejemplares(const tEcosistema& ecosistema, const tEspecie& especie, int n);
   Lista<tEspecie> lista_especies_ecosistema(const tEcosistema& ecosistema, int n) const;
   int numero_ejemplares_en_ecosistema(const tEcosistema& ecosistema, const tEspecie& especie) const;
   Lista<tEspecie> lista_especies_parque() const;
   int numero_ejemplares_en_parque(const tEcosistema& especie) const;
   
private:
  /*** Incluir los detalles de representación que se consideren oportunos */
  class InfoEcosistema {
    public:
      void an_ejemplares(const tEspecie & especie, int n);
      int numero_ejemplares(const tEspecie & especie) const;
      Lista<tEspecie> lista_especies(int n) const;

    private:
      Diccionario<tEspecie, unsigned> _nEspecies;
      Lista<tEspecie> _recientes;
  };

  Diccionario<tEspecie, unsigned> _especiesParque;
  Diccionario<tEcosistema, ParqueNatural::InfoEcosistema> _ecosistemasParque;
};
 
#endif
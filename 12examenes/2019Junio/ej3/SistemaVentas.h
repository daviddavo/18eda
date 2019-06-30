#ifndef __VENTAS_H
#define __VENTAS_H

#include <string>
#include "lista.h"
#include "diccionario.h"
#include "DiccionarioHash.h"

typedef std::string tCliente;
typedef std::string tProducto;

/* Excepción levantada por 'an_oferta' 
   cuando dicha operación no puede aplicarse */ 
class EErrorAltaProducto {};

/* Excepción levantada por 'venta' 
   cuando dicha operación no puede aplicarse */ 
class EErrorVenta {};

/* Excepción levantada por 'primero_en_espera' 
   cuando dicha operación no puede aplicarse */ 
class EErrorAccesoListaEspera {};

/* Excepción levantada por 'pon_en_espera',
   'cancela_espera' y 'num_en_espera' cuando
   no existe el producto al que se refieren   */ 
class EProductoNoExiste {};

/* Clase para representar los resultados
   de la operación 'lista_ventas' */
class Venta {
	public:
	   std::string _producto;
	   int _unidades_vendidas;
	   Venta(std::string producto, int unidades_vendidas) {
		   _producto = producto;
		   _unidades_vendidas = unidades_vendidas;
	   }	
	   bool operator==(const Venta & other) const {
		   return _producto == other._producto && _unidades_vendidas == other._unidades_vendidas;
	   }
};

class SistemaVentas {
	public:
	   SistemaVentas();
	   ~SistemaVentas();
	   void an_oferta(const tProducto& producto, unsigned int num_unidades);
	   void pon_en_espera(const tCliente& cliente, const tProducto& producto);
	   void cancela_espera(const tCliente& cliente, const tProducto& producto);
	   unsigned int num_en_espera(const tProducto& producto) const;
	   void venta(const tProducto& producto, unsigned int num_unidades);
	   const std::string& primero_en_espera(const tProducto& producto) const;
	   Lista<Venta> lista_ventas() const;
     private:	   
		class Oferta {
		   public:
		   unsigned restantes;
		   Lista<tCliente> colaClientes;
		   Oferta(unsigned r) : restantes(r) {};
	    };

	    Diccionario<tProducto, int> listaVentas;
	    DiccionarioHash<tProducto, Oferta*> diccOfertas;

};

#endif
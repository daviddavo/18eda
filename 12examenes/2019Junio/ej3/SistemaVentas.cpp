/*

NOMBRE Y APELLIDOS:

*/

#include "SistemaVentas.h"


  /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 
	 
	*/
SistemaVentas::SistemaVentas() {
	/* A IMPLEMENTAR */
	
}

  /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 
	 
	*/
void SistemaVentas::an_oferta(const tProducto& producto, unsigned int num_unidades) {
	/* A IMPLEMENTAR */
	
}

  /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 
	 
	*/
void SistemaVentas::pon_en_espera(const tCliente& cliente, const tProducto& producto) {
	/* A IMPLEMENTAR */

}	
	
   /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	  
	 
	*/
void SistemaVentas::cancela_espera(const tCliente& cliente, const tProducto& producto) {
	/* A IMPLEMENTAR */
}

  /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 
	 
	*/
unsigned int SistemaVentas::num_en_espera(const tProducto& producto) const {
	/* A IMPLEMENTAR */
}

   /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 
	 
	*/
void SistemaVentas::venta(const tProducto& producto, unsigned int num_entradas) {
	/* A IMPLEMENTAR */
}

   /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 
	 
	*/
const string& SistemaVentas::primero_en_espera(const tProducto& producto) const {
	/* A IMPLEMENTAR */
}

    /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 
	 
	*/
Lista<Venta> SistemaVentas::lista_ventas() const {
	/* A IMPLEMENTAR */
}


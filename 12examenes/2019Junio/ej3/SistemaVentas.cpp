/*

NOMBRE Y APELLIDOS:

*/

#include "SistemaVentas.h"

using namespace std;


  /*
	La complejidad de crear listas y diccionarios vacíos: O(1)
	*/
SistemaVentas::SistemaVentas() {
	/* A IMPLEMENTAR */
	
}


SistemaVentas::~SistemaVentas() {
	for (auto it = diccOfertas.cbegin(); it != diccOfertas.cend(); it.next())
		delete it.valor();
}

  /*
	La complejidad de insertar en un arbol binario, o comprobar si el elemento está
	dentro de el otro arbol binario. En ambos casos, en el peor de los casos es O(n)
	*/
void SistemaVentas::an_oferta(const tProducto& producto, unsigned int num_unidades) {
	if (num_unidades <= 0 || diccOfertas.contiene(producto)) throw EErrorAltaProducto();

	diccOfertas.inserta(producto, new Oferta(num_unidades));
	if (!listaVentas.contiene(producto)) listaVentas.inserta(producto, 0);
}

static bool contiene (const Lista<tCliente> & lista, const tCliente & cliente) {
	for (auto it = lista.cbegin(); it != lista.cend(); it.next())
		if (it.elem() == cliente) return true;

	return false;
}

  /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 
	 
	*/
void SistemaVentas::pon_en_espera(const tCliente& cliente, const tProducto& producto) {
	if (!diccOfertas.contiene(producto)) throw EProductoNoExiste();

	Oferta * of = diccOfertas.valorPara(producto);
	if (!contiene(of->colaClientes, cliente))
		of->colaClientes.pon_final(cliente);
}	
	
   /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	  
	 
	*/
void SistemaVentas::cancela_espera(const tCliente& cliente, const tProducto& producto) {
	if (!diccOfertas.contiene(producto)) throw EProductoNoExiste();

	Oferta * of = diccOfertas.valorPara(producto);
	for (auto it = of->colaClientes.begin(); it != of->colaClientes.end(); it.next()) {
		if (it.elem() == cliente) {
			of->colaClientes.eliminar(it);
			return;
		}
	}
}

  /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 
	 
	*/
unsigned int SistemaVentas::num_en_espera(const tProducto& producto) const {
	if (!diccOfertas.contiene(producto)) throw EProductoNoExiste();
	return diccOfertas.valorPara(producto)->colaClientes.longitud();
}

   /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 
	 
	*/
void SistemaVentas::venta(const tProducto& producto, unsigned int num_entradas) {
	if (!diccOfertas.contiene(producto)) throw EProductoNoExiste();
	
	Oferta * of = diccOfertas.valorPara(producto);
	if (of->colaClientes.esVacia()) throw EErrorVenta();
	if (num_entradas > of->restantes) throw EErrorVenta();

	of->colaClientes.quita_ppio();
	if (num_entradas == of->restantes) {
		delete of;
		diccOfertas.borra(producto);
	} else {
		of->restantes -= num_entradas;
	}

	listaVentas.inserta(producto, listaVentas.valorPara(producto)+num_entradas);
}

   /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 
	 
	*/
const string& SistemaVentas::primero_en_espera(const tProducto& producto) const {
	if (!diccOfertas.contiene(producto)) throw EProductoNoExiste();
	Oferta * of = diccOfertas.valorPara(producto);

	if (of->colaClientes.esVacia()) throw EErrorAccesoListaEspera();
	return of->colaClientes.primero();
}

    /*
	 COMPLEJIDAD: Determina aquí, justificadamente, cuál es la complejidad de 
	 la operación
	 
	 
	 
	*/
Lista<Venta> SistemaVentas::lista_ventas() const {
	Lista<Venta> ret;
	for (auto it = listaVentas.cbegin(); it != listaVentas.cend(); it.next())
		ret.pon_final(Venta(it.clave(), it.valor()));

	return ret;
}


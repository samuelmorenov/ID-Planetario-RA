#ifndef __XMLNODELIST__
#define __XMLNODELIST__

#include "xmlparser.h"

/**
 * Clase que gestiona una lista de nodos como las obtenidas por la función 
 * <code>getChildsByTagName()</code> de la clase <code>xmlnode</code>.
 */
class xmlnodelist {
	private:
		vector<xmlnode *> _nodes;
	public:
		/**
		 * Crea una lista de nodos vacía
		 */
		xmlnodelist();
		/**
		 * Añade un nodo a la lista de nodos.
		 * @param nodo 	El nodo a añadir
		 */
		void 		addNode(xmlnode *nodo );
		/**
		 * Obtiene un determinado nodo de la lista
		 * de nodos. 
		 * @param 	Posición del nodo solicitado. 
		 * @returns 	El nodo solicitado o NULL si la posición
		 *		no es válida. 
		 */
		xmlnode*	getNode(int pos);
		/**
		 * Obtiene el tamaño de la colección de nodos
		 * @returns	El tamaño de la lista de nodos
		 */
		int		size();
};
#endif

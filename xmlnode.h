#ifndef __XMLNODE__
#define __XMLNODE__

#include "xmlparser.h"

/** 
 * Define un nodo en el documento XML. Un nodo puede tener un nombre,
 * un contenido de texto y una serie de parámetros como vemos en el
 * siguiente ejemplo:
 * \code
 * <body onload="javascript:alert('Hola');">
 * Hola<b>Mundo</b>
 * </body>
 * \endcode
 * El contenido anterior corresponde a un nodo cuyo nombre es 'body', 
 * que tiene un parámetro de nombre 'onload' y cuyo valor es 
 * "javascript:alert('Hola');" y que tiene un valor de texto 'Hola'. 
 */
 
class xmlnodelist;

class xmlnode {
      private:
             map<string,string> _params;
             string _text;
             string _name;
             vector<xmlnode*> _childs;
             
      public:
      	     	/**
      	     	 * Crea un nuevo nodo especificando el nombre del nodo y
      	     	 * el contenido de texto del mismo. 
      	     	 * @param name		El nombre del nodo, es decir, lo que va inmediatamente
      	     	 *			despues de la apertura del tag '<'.
      	     	 * @param content	El contenido de texto del nodo, es decir, lo que va dentro
      	     	 *			de los tags del mismo. 
      	     	 */
		xmlnode(string name,string content);
		/**
		 * Construye un nodo vacio. 
		 */
		 xmlnode();
		/**
		 * Destruye un nodo y, de manera recursiva, todos los nodos hijos de este nodo
		 * que, a su vez, liberarán a sus hijos liberando asi la estructura completa de
		 * forma recusriva. 
		 */
		~xmlnode();
		/**
		 * Obtiene el numero de hijos que contiene este nodo 
		 * @returns 	El número de hijos del nodo.
		 */
		int 		getChildCount();
		/**
		 * Obtiene el hijo del nodo en la posición <code>index</code>.
		 * @param index Posición del hijo a obtener, comenzando en 0.
		 * @returns 	El hijo en la posición especificada. 
		 */
		xmlnode * 	getChild(int index);
		/**
		 * Obtiene el nombre del nodo.
		 * @returns 	El nombre del nodo. 
		 */
		string 		getNodeName();
		/**
		 * Obtiene el valor de un parámetro determinado del nodo.
		 * @param param El parametro que se desea obtener. 
		 * @returns 	El valor de dicho parámetro. 
		 */
		string 		getNodeParamValue(string param);
		/**
		 * Obtiene el mapa de tipo <code>string,string</code> del nodo
		 * con los pares: parametro,valor.
		 * @returns 	El mapa de valores del nodo. 
		 */
		map<string,string> getNodeParamMap();
		/**
		 * Obtiene el contenido textual del nodo.
		 * @returns 	El texto del nodo. 
		 */
		string 		getNodeText();   
		/**
		 * Añade un hijo al nodo.
		 * @param child El hijo a añadir. 
		 */     
		void 		addChild(xmlnode * child);
		/**
		 * Añade un parámetro con un valor determinado al nodo. 
		 * @param param El nombre del parámetro. 
		 * @param value El valor del parámetro. 
		 */
		void 		addParam(string param,string value);
		/**
		 * Establece el nombre del nodo.
		 * @param name  El nuevo nombre del nodo.
		 */
		void 		setName(string name);
		/** 
		 * Establece el texto del nodo. 
		 * @param text  El nuevo texto del nodo. 
		 */
		void 		setText(string text);	
		/** 
		 * Obtiene una lista de nodos cuyo nombre de tag corresponde
		 * con el nombre pasado como argumento.
		 * @param name	El nombre de tag a buscar.
		 * @returns 	La lista de nodos cuyo tag corresponde con el
		 *		indicado en <code>name</code>
		 */
		xmlnodelist * getChildsByTagName(string name);
		/** 
		 * Obtiene una lista de nodos cuyo id  corresponde
		 * con el id pasado como argumento.
		 * @param id	El id a buscar.
		 * @returns 	La lista de nodos cuyo id corresponde con el
		 *		indicado en <code>id</code>
		 */
		xmlnodelist * getChildsById(string id);			
};
#endif

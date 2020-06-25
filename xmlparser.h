#ifndef __XMLPARSER__
#define __XMLPARSER__

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

#include "xmlnode.h"
#include "xmlnodelist.h"
#include "util.h"

/**
 * Clase que gestiona la estructura de un XML. Puede ser utilizada para leer un XML
 * y generar su estructura de nodos, modificarla o crearla desde cero.
 * La clase <code>xmlparser</code> tiene funciones que permiten la escritura y lectura
 * de ficheros XML.
 */
class xmlparser{
      private:
      		/**
      		 * Puntero para almacenar el nodo padre del documento 
      		 */
		xmlnode * 	_parent;
		/**
		 * Realiza el parsing del XML. Genera todos los nodos partiendo desde un
		 * nodo raíz que es imprescindible. 
		 * Atención: No es un validador de XML. Si el formato del XML no es correcto
		 * el funcionameinto de la función no está definido. 
		 * @param xml	El XML que queremos analizar. 
		 * @param size	La función deja en este parámetro el tamaño del XML parseado
		 *		(Hasta el cierre del tag raíz)
		 * @returns 	El nodo padre del del XML que estamos analizando. 
		 */
		xmlnode * 	parseXML(string xml,int * size) ;
		/**
		 * Limpia los comentarios de un XML, es decir, todos los bloques de texto 
		 * que vatan contenidos entre los bloques <!-- y -->.
		 * @param xml 	El string con el contenido XML.
		 * @returns 	El XML sin los comentarios. 
		 */
		string 		clearComments(string xml);
		/**
		 * Analiza la cabecera de un tag XML. En el análisis de dicha cabecera se
		 * obtendrá el nombre del tag (Al comienzo del mismo y hasta el siguiente
		 * espacio) y los parámetros que contenga hasta el primer caracter '>' 
		 * @param node	El nodo al cual se asignarán los valroes encontrados en la
		 * 		cabecera. 
		 * @param head	La cadena de texto que contendrá los datos de la cabecera. 
		 * 		Ha de contener los caracteres de inicio y cierre del tag XML.
		 */ 
		void 		parseHead(xmlnode * node,string head);
      public:
      		/**
      		 * Recorre el contenido del xml recibido como argumento de forma recursiva
      		 * y genera sobre él una estructura jerárquica de nodos xml.
      		 * @param xml	El string que contiene el xml a ser analizado.
      		 */
		xmlparser(string xml);
		/**
		 * Construye un parser vacio con un nodo raiz, de nombre <root>. Este parser
		 * puede ser utilizado para construir desde cero documentos XML.
		 */
		xmlparser();
		/**
		 * Destruye toda la estructura del xml liberando todos los nodos que lo
		 * componen de forma recursiva. Es necesario llamarlo antes de finalizar
		 * el programa. 
		 */
		~xmlparser();
		/**
		 * Obtiene el nodo padre del xml parseado, del que descienden todos los
		 * demás nodos.
		 * @returns	El nodo padre del xml.
		 */
		xmlnode * 	getParentNode();
		/**
		 * Imprime el arbol del xml de forma recursiva. El segundo argumento
		 * es opcional, el uso más frecuente es:
		 * \code
		 * 	xmlparser * parser = new xmlparser("<root><x>10</x><y>20</y></root>");
		 * 	parser->printTree(parser->getParentNode());
		 * \endcode
		 * @param node	Puntero al nodo desde el que se desea comenzar a imprimir.
		 * @param prof	(Opcional)Profundidad inicial de la tabulación. Utilizado
		 *		internamente por el algoritmo. 
		 */
		void 		printTree(xmlnode * node,int prof=0);
		/**
		 * Escribe el XML a un stream de salida representado por <code>stream</code>
		 * del mismo modo que la función <code>printTree()</code> comenzando desde un
		 * determinado nodo del árbol. 
		 * @param node	 Puntero al nodo desde el que se desea comenzar a imprimir. 
		 * @param stream Referencia al stream en el que queremos escribir. 
		 * @param prof	 (Opcional) Representa la profundidad actual de tabulación.
		 */
		void 		writeTree(xmlnode * node,ofstream &stream,int prof=0);
		/**
		 * Escribe el XML a un stream de salida representado por <code>stream</code>
		 * del mismo modo que la función <code>printTree()</code>.
		 * @param stream Referencia al stream en el que queremos escribir. 
		 */
		void 		writeTree(ofstream &stream);

};

#endif

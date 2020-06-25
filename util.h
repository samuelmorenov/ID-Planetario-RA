#ifndef __UTIL__
#define __UTIL__

#include "xmlparser.h"
/**
 * Elimina los espacios al principio y final de una cadena de
 * texto. 
 * @param s	Cadena de texto a filtrar. 
 * @returns	La cadena sin espacios al principio o final. 
 */
string trim(string s);
/**
 * Reemplaza en la cadena <code>source_str</code> cada aparición
 * de <code>find</code> por la cadena contenida en <code>replc</code>.
 * Por ejemplo, en la cadena "anjjferjjnasjjjjriia" un llamada como:
 * \code
 * replace("anjjferjjnasjjjjriia","jj","bb");
 * \code
 * Produciría la siguiente salida:
 * \code
 * anbbferbbnasbbbbriia
 * \endcode
 * @param source_str	La cadena de origen.
 * @param find		La cadenaque se ha de buscar. 
 * @param replc		La cadena por la que se han de reemplazar las
 *			apariciones de <code>find</code>
 * @returns 		La cadena de origen con los reemplazos correspondientes.
 * 
 */
string replace(string source_str,string find,string replc);
#endif

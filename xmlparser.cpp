#include "xmlparser.h"
#include <iostream>

void xmlparser::parseHead(xmlnode * node,string head){
	bool endtag;
	int pointer;
   
	/* Obtenemos el nombre del tag*/
	node->setName(head.substr(1,(head.find_first_of(" />",1))-1));
	pointer=node->getNodeName().length()+1;
   
   	/* Recorremos el tag en busca de parametros. Asumimos que cada vez que
	encontremos un '=' tendrá a su izquierda un nombre de parametro y a su
	derecha el valor de dicho parametro */
	endtag=false;
	while(!endtag){
		int lookup;
		lookup=head.find("=",pointer);
      
		/* Si no hay más '=' detenemos el bucle */
		if(lookup==string::npos){
			endtag=true;
		} else {
			string param,value;
			param=head.substr(pointer,lookup-pointer);
			pointer=lookup+1;
         		/* Si el valor se abre con dobles comillas, buscamos el cierre de
			dichas comillas*/
			if(head[pointer]=='\"'){
				lookup=head.find("\"",pointer+1);
				value=head.substr(pointer+1,lookup-(pointer+1));
				pointer=lookup+1;
			}
         		/* Si el valor se abre con cmilla simple, buscamos el cierre de la 
			comilla simple*/
			else if(head[pointer]=='\''){
				lookup=head.find("'",pointer+1);
				value=head.substr(pointer+1,lookup-(pointer+1));
				pointer=lookup+1;
			} 
         		/* Si el valor no se abre con ninguna comilla buscamos el siguiente
			espacio, barra o cierre de tag como delimitador del valor */
			else {
				lookup=head.find_first_of(" />",pointer);
				value=head.substr(pointer,lookup-pointer);
				pointer=lookup+1;
			}  
			param=trim(param);
			node->addParam(param,value);
		}
	}
}

string xmlparser::clearComments(string xml){
	int index,lookup;
	string clearxml="";
	
	index=0;
	while(index<xml.length()){
		lookup=xml.find("<!--",index);
		if(lookup==string::npos)
			break;
		clearxml+=xml.substr(index,lookup-index);
		index=xml.find("-->",lookup)+3;
		if(index==string::npos){
			index=xml.length();
		}
	}
	clearxml+=xml.substr(index,xml.length()-index);
	return clearxml;
}
xmlnode * xmlparser::parseXML(string xml,int * size){
	int head_start,head_end,pointer;
	string head,content,endtag_string,tag_string;
	bool endtag;
	vector<xmlnode *> child_nodes;
	xmlnode * node;

	/* Obtenemos la cabecera del tag y el identificador de dicha cabecera*/
	head_start=xml.find("<");
	head_end=xml.find(">");
	head=xml.substr(head_start,(head_end+1)-head_start);
	tag_string=xml.substr(head_start+1,(xml.find_first_of(" />",head_start))-(head_start+1));

	/* Comprobamos si estamos ante un tag sin contenido como
	el siguiente:
	<root param="value" />
	*/
	if(head[head.length()-2] == '/'){
	if(size!=NULL)
		*size=head_end-head_start+1;
		node=new xmlnode();
		node->setText("");
		parseHead(node,head);
		return node;
	}

	/* Si no es un tag vacio recorremos todo el interior del tag en busca de
	otros tags (Que analizaremos de forma recusriva) hasta encontrar el tag de 
	cierre */
	endtag_string="</"+tag_string+">";
	endtag=false;
	pointer=head_end+1;
	while(!endtag){
		int lookup,endtag_pos,cdata;
		lookup=xml.find("<",pointer);
		cdata=xml.find("<![CDATA[",pointer);
		content+=xml.substr(pointer,lookup-pointer);
		endtag_pos=xml.find(endtag_string,pointer);

		/* Comprobamos si el siguiente tag encontrado es el tag de cierre*/
		pointer=lookup;
		if(endtag_pos==lookup){
			endtag=true;
			pointer+=endtag_string.length();
			break;
		}
		/*Comprobamos si hemos encontrado un CDATA <![CDATA[áéíóú]]> */
		else if(cdata==lookup){
		  int cdata_end;
		  
		  cdata_end=xml.find("]]>",lookup);
		  pointer+=9;
		  content+=xml.substr(pointer,cdata_end-pointer);
		  pointer=cdata_end+3;
		}
		/* Si el siguiente tag encontrado no es el de cierre lo analizamos de
		forma recursiva y continuamos a partir del final del mismo*/
		else {
		    int skip;
		    xmlnode * child;
		    
		    child=parseXML(xml.substr(lookup,xml.length()-lookup),&skip);
		    child_nodes.push_back(child);
		    pointer+=skip;
		}
	}
	if(size!=NULL)
	*size=pointer-head_start;  

	/* Creamos el nodo padre y le añadimos todos los hijos encontrados de forma
	recursiva en el bucle anterior*/
	node = new xmlnode();

	node->setText(content);
	parseHead(node,head);

	for(int i=0;i<child_nodes.size();i++){
	node->addChild(child_nodes[i]);
	}
	return node;
}
xmlparser::xmlparser(string xml){
	/* Eliminamos los comentarios y los saltos de línea y tabuladores del
	documento */
	xml=clearComments(xml);
	xml=replace(xml,"\n","");
	xml=replace(xml,"\t","");
	/* Realizamos el anális del XML ya filtrado */
	_parent=parseXML(xml,NULL);
}
xmlparser::xmlparser(){
	/* Creamos un nodo raiz vacio */
	_parent=new xmlnode("root","");
}

xmlparser::~xmlparser(){
	delete _parent;                      
}
xmlnode * xmlparser::getParentNode(){
	return _parent;
}

void xmlparser::printTree(xmlnode * node,int prof){
	map<string,string>::iterator it;
	map<string,string> params;
	
	for(int i=0;i<prof*2;i++){
		cout << " ";
	}
	cout << "|-";
	cout << "<"+node->getNodeName()+">";
	
	params= node->getNodeParamMap();
	if(params.size()==0){
		cout << "[No params]";
	}else {
		for ( it=params.begin() ; it != params.end(); it++ ){
			cout << "["+it->first + "=" + it->second+"]";
		}
	}
	
	cout << ":" + node->getNodeText();
	cout << endl;
	for(int i=0;i<node->getChildCount();i++){
		printTree(node->getChild(i),prof+1);
	}
}
void xmlparser::writeTree(xmlnode * node,ofstream &stream,int prof){
	map<string,string>::iterator it;
	map<string,string> params;
	bool child_line;
	
	for(int i=0;i<prof;i++){
		stream << "\t";
	}
	stream << "<"+node->getNodeName();
	
	params= node->getNodeParamMap();
	if(params.size()!=0){
		for ( it=params.begin() ; it != params.end(); it++ ){
			stream << " "+it->first + "=\"" + it->second +"\"";
		}
	}
	stream << ">";
	
	stream << node->getNodeText();
	
	child_line=false;
	for(int i=0;i<node->getChildCount();i++){
		stream << endl;
		child_line=true;
		writeTree(node->getChild(i),stream,prof+1);
	}
	if(child_line){
		stream << endl;
		for(int i=0;i<prof;i++){
			stream << "\t";
		}
	}
	stream << "</"+node->getNodeName() +">";
}	
void xmlparser::writeTree(ofstream &stream){
	writeTree(getParentNode(),stream);
}

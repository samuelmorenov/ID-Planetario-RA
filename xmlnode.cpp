#include "xmlparser.h"

xmlnode::xmlnode(){
	_text="";
	_name="";
}
xmlnode::xmlnode(string name,string content){
   _text=content;
	_name=name;
}
xmlnode::~xmlnode(){
   for(int i=0;i<_childs.size();i++){
         delete _childs[i]; 
   } 
}
void xmlnode::addChild(xmlnode * child){
   _childs.push_back(child);
}
void xmlnode::addParam(string param,string value){
	_params[param]=value;
}
string xmlnode::getNodeText(){
   return _text;  
}
void xmlnode::setName(string name){
	_name=name;
}
void xmlnode::setText(string text){
	_text=text;
}
string xmlnode::getNodeName(){
   return _name;  
}
string xmlnode::getNodeParamValue(string param){
   map<string,string>::iterator it;
   
   it=_params.find(param);
   if(it==_params.end()){
      return "";
   }
   return _params[param];
}
int xmlnode::getChildCount(){
   return _childs.size();  
}
xmlnode * xmlnode::getChild(int index){
   return _childs[index];
}

map<string,string>  xmlnode::getNodeParamMap(){
	return _params;
}
xmlnodelist * xmlnode::getChildsByTagName(string name){
	xmlnodelist * nodelist=new xmlnodelist();
	for(int i=0;i<(int)_childs.size();i++){
		if(_childs[i]->getNodeName()==name){
			nodelist->addNode(_childs[i]);
		}
	}
	return nodelist;
}
xmlnodelist * xmlnode::getChildsById(string id){
	xmlnodelist * nodelist=new xmlnodelist();
	for(int i=0;i<(int)_childs.size();i++){
		if(_childs[i]->getNodeParamValue("id")==id){
			nodelist->addNode(_childs[i]);
		}
	}
	return nodelist;
}

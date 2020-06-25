#include "xmlnodelist.h"

xmlnodelist::xmlnodelist(){

}
void xmlnodelist::addNode(xmlnode * node){
	_nodes.push_back(node);
}

int xmlnodelist::size(){
	return _nodes.size();
}
xmlnode * xmlnodelist::getNode(int pos){
	return _nodes[pos];
}

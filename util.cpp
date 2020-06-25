#include "xmlparser.h"

string trim(string s){
   int start, end;
   
   start=0;
   for(int i=0;i<s.length();i++){
      if(s[i]==' ') 
         start=i+1;
      else 
         break; 
   }
   end=s.length()-1;
   for(int i=s.length()-1;i>=0;i--){
      if(s[i]==' ') 
         end=i-1; 
      else
         break;
   }
   return s.substr(start,end-start+1);
}
string replace(string source_str,string find,string replc){
	int pos;
	string result=string(source_str);
	while((pos=result.find(find))!=string::npos){
		result=result.replace(pos,find.length(),replc);
	}
	return result;
}

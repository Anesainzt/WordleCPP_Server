#include <iostream>
#include <string.h>
#include "Admin.h"
using namespace std;
Admin::Admin(){

	this->numAdmin= 0;
	this->nombre = new char[];
	this->nombre[0] = '\0';
	this->contrasena = new char[];
	this->contrasena[0] = '\0';
	//Constructor por defecto
}
/*
Admin::Admin(const char* nombre,const char* contrasena, int numAdmin){
	//Cnstructor espec�fico
}
Admin::Admin(const Admin&){
	//Constructor copia
}
Admin::~Admin(){ //Destructor
}
char* Admin::getNombre() const{

}
void Admin::setNombre(const char*){

}
char Admin::getContrasena() const{

}
void Admin::setContrasena(char){

}
int Admin::getNumAdmin(){

}
void Admin::setNumAdmin(int){

}
void Admin::toString(){

}
void Admin::cargarAdministradores(){

}
*/

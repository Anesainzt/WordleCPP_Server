

#ifndef BASEDATOS_H_
#define BASEDATOS_H_

#include "sqlite3.h"

void crearTablas(sqlite3 *db);
void insertarUsuario(sqlite3 *db, char *nombre, char *contrasenia);
void insertarPuntuacion(sqlite3 *db ,char *nombre,char * palabra, int intentos);
void borrarUsuario(sqlite3 *db, char *nombre);
void mostrarUsuarios(sqlite3 *db);
int comprobarUsuarios(sqlite3 *db, char*nombre, char *contra);
void mostrarPuntuaciones(sqlite3 * db,  char * nombre);

#endif /* BASEDATOS_H_ */



#ifndef BASEDATOS_H_
#define BASEDATOS_H_

#include "sqlite3.h"

void crearTablas(sqlite3 *db);
void insertarUsuario(sqlite3 *db, char *nombre, char *contrasenia);
void insertarPuntuacion(sqlite3 *db ,char *nombre,char * palabra, int intentos);
void borrarUsuario(sqlite3 *db, char *nombre);
void borrarPalabra(sqlite3 *db, char *palabra);
void mostrarUsuarios(sqlite3 *db);
int comprobarUsuarios(sqlite3 *db, char*nombre, char *contra);
void mostrarPuntuaciones(sqlite3 * db,  char * nombre);
char * palabraAleatoria(sqlite3 * db,char * tematica);
void insertarUsuario(sqlite3 *db ,char *nombre,char * contra);
void insertarPalabra(sqlite3 *db ,char *palabra,char * tematica);

#endif /* BASEDATOS_H_ */

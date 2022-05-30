#include "BaseDatos.h"
#include <stdio.h>
#include <string.h>
#include "sqlite3.h"

void crearTablas(sqlite3 *db){
	sqlite3_stmt *stmt;

	char sql[] = "create table IF NOT EXISTS puntuacion(usuario varchar2(100) PRIMARY KEY NOT NULL, palabra varchar2(20),intentos int)";
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt); //Ejecuta la sentencia
	sqlite3_finalize(stmt);

	char sql2[] = "create table IF NOT EXISTS usuario(nom varchar2(100) PRIMARY KEY NOT NULL, con varchar2(20))";
	sqlite3_prepare_v2(db, sql2, -1, &stmt, NULL) ;
	sqlite3_step(stmt); //Ejecuta la sentencia
	sqlite3_finalize(stmt);

	char sql3[] = "create table IF NOT EXISTS palabra(palabra varchar2(5) PRIMARY KEY NOT NULL, tematica varchar2(10))";
	sqlite3_prepare_v2(db, sql3, -1, &stmt, NULL) ;
	sqlite3_step(stmt); //Ejecuta la sentencia
	sqlite3_finalize(stmt);
}

void insertarPuntuacion(sqlite3 *db ,char *nombre,char * palabra, int intentos){
	sqlite3_stmt *stmt;

	char sql[100];//

	sprintf(sql, "insert into puntuacion values('%s', '%s', %d)",nombre,palabra, intentos);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

void insertarUsuario(sqlite3 *db ,char *nombre,char * contra){
	sqlite3_stmt *stmt;

	char sql[100];

	sprintf(sql, "insert into usuario values('%s', '%s')",nombre,contra);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

void borrarUsuario(sqlite3 *db, char *nombre){
	sqlite3_stmt *stmt;
	char sql[100];
	sprintf(sql, "delete from usuario where nombre = '%s'",nombre);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

void borrarPalabras(sqlite3 *db, char *palabra){
	sqlite3_stmt *stmt;
	char sql[100];
	sprintf(sql, "delete from palabra where palabra = '%s'",palabra);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}

void mostrarUsuarios(sqlite3 *db){
	int resul;
	sqlite3_stmt *stmt;
	char sql[100],nom[101] ,con[21];

	sprintf(sql,"select * from usuario");
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

	do{
		resul = sqlite3_step(stmt);
		strcpy(nom,(char*)sqlite3_column_text(stmt, 0));
		strcpy(con, (char*)sqlite3_column_text(stmt, 1));
		printf("%s %s\n",nom,con); fflush(stdout);
	}while(resul == SQLITE_ROW);


	sqlite3_finalize(stmt);

}

int comprobarUsuarios(sqlite3 *db, char*nombre, char *contra){
	int resul;
	sqlite3_stmt *stmt;
	char sql[100],/*nom[101] ,*/con[21], nom[20];
	int resultado = 3;
	sprintf(sql,"select * from usuario where nom='%s'",nombre);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	resul = sqlite3_step(stmt);
	if(resul == SQLITE_ROW){
		strcpy(nom, (char*)sqlite3_column_text(stmt, 0));
		strcpy(con, (char*)sqlite3_column_text(stmt, 1));
		if((strcmp(contra,con)==0) && (strcmp(nombre,nom)==0)){// usuario correcto en BD
			resultado = 1;
		}else{
			resultado = 0;    // usuario incorrecto en BD
		}
	}else{
		resultado =3;
	}
	sqlite3_finalize(stmt);
	return resultado;
}

void mostrarPuntuaciones(sqlite3 * db,  char * nombre){
    int resul, intentos;
    sqlite3_stmt * stmt;
    char sql[100],usuario[101] ,palabra[6];

    sprintf(sql,"select * from puntuacion where usuario='%s'", nombre);
    sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

    do{
        resul = sqlite3_step(stmt);


        strcpy(usuario, (char*)sqlite3_column_text(stmt, 0));
        strcpy(palabra, (char*)sqlite3_column_text(stmt, 1));
       intentos = sqlite3_column_int(stmt, 2);
        printf("El usuario:%s ha adivinado la palabra: %s en %d intentos\n",usuario, palabra, intentos); fflush(stdout);
    }while(resul == SQLITE_ROW);


    sqlite3_finalize(stmt);

}

char palabraAleatoria(sqlite3 * db,char * tematica){
	char *palabra = "libro";
	sqlite3_stmt *stmt;
	char sql[100];
	int resul;

	if(strcmp(tematica,"todas") == 0){
		sprintf(sql,"select * from palabra order by rand() limit 1");
		sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
		do{
		   resul = sqlite3_step(stmt);
		  strcpy(palabra, (char*)sqlite3_column_text(stmt, 0));
			sqlite3_finalize(stmt);
			return palabra;
		    }while(resul == SQLITE_ROW);
	}else{
		sprintf(sql,"select * from palabra where tematica = '%s' order by rand() limit 1",tematica);
		sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
		do{
		   resul = sqlite3_step(stmt);
		   printf("HOLA2");
		   fflush(stdout);
		   palabra[0] = '0';
		   strcpy(palabra, (char*)sqlite3_column_text(stmt, 0));
		   printf("HOLA4");
		   fflush(stdout);
	}while(resul == SQLITE_ROW);
		printf("HOLA3");
		fflush(stdout);
		sqlite3_finalize(stmt);
		return palabra;
	}
}

void insertarPalabra(sqlite3 *db ,char *palabra,char * tematica){
	sqlite3_stmt *stmt;

	char sql[100];

	sprintf(sql, "insert into palabra values('%s', '%s')",palabra,tematica);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);
}






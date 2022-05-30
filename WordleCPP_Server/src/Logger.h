#ifndef LOGGER_H_
#define LOGGER_H_

#include <time.h>
#include <stdio.h>

typedef enum
{
   CONSOLA = 1,
   FICHERO = 2,
}TipoLog;

FILE *fichero;
TipoLog tipo;
void inicializarLog(char *nombreLog, TipoLog lt);
void error(char *cad, char* text);
void info(char *cad, char* text);
void logEnFichero(char * text);
void logEnConsola(char * text);


#endif /* LOGGER_H_ */

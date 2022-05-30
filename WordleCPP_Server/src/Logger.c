 #include "Logger.h"
void inicializarLog(char *nombreLog, TipoLog lt) {
	fichero = fopen(nombreLog, "a");
	tipo = lt;
}
void errorBD( char *text) {
	time_t actual = time(0);
	char *fecha = ctime(&actual);
	sprintf( "%s ERROR: %s", fecha, text);
}
void info(char *cad, char *text) {
	time_t actual = time(0);
	char *fecha = ctime(&actual);
	sprintf(cad, "%s INFO SE PUEDE AÑADIR %s", fecha, text);
}
void logEnFichero(char *text) {
	char cad[512];
	errorBD(text);
	if (tipo == FICHERO)
		fprintf(fichero, "%s\n", cad);
	else {
		printf("%s\n", cad);
		fflush(stdout);
	}
}
void logEnConsola(char *text) {
	char cad[512];
	info(cad, text);
	if (tipo == FICHERO)
		fprintf(fichero, "%s\n", cad);
	else {
		printf("%s\n", cad);
		fflush(stdout);
	}
}

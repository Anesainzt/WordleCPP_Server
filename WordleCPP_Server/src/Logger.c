 #include "Logger.h"

void inicializarLog(char *nombreLog, TipoLog lt) {
    fichero = fopen(nombreLog, "a");
    tipo = lt;
}
void error( char*cad, char* text) {
    time_t actual = time(0);
    char *fecha = ctime(&actual);
    sprintf( cad,"%s ERROR: %s", fecha, text);
}
void info(char*cad, char *text) {
    time_t actual = time(0);
    char*fecha = ctime(&actual);
    sprintf(cad, "%s INFO: %s", fecha, text);
}
void logEnFichero(char *text) {
    char cad[512];
    error(cad, text);
    if (tipo == FICHERO)
        fprintf(fichero, "%s\n", cad);
    else {
        printf("%s\n", cad);
        fflush(stdout);
    }
}
void logEnConsola(char*text) {
    char cad[512];
    info(cad, text);
    if (tipo == FICHERO)
        fprintf(fichero, "%s\n", cad);
    else {
        printf("%s\n", cad);
        fflush(stdout);
    }
}

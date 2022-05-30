#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "wordC.h"
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>

#define MAX_NUM_PALABRAS 100
#define LINEA_MAX 2048
#define TAMANYO_NOMBREFICHERO 1024

#define USUARIO "c"
#define CLAVE "13"

void menuUsuario(sqlite3 * db){
	char nombre[51];
	int num = 0;
			printf("\n****BIENVENIDO, JUGADOR****\n \n");
			fflush( stdin);
			printf("1. JUGAR \n");
			fflush( stdin);
			printf("2.Ver puntuaciones \n");
			fflush(stdin);
			printf("3.Cerrar sesion \n");
			fflush(stdin);
			printf("4.Salir \nOpcion: ");
			fflush(stdin);
			fflush( stdout);
			scanf("%d", &num);
			fflush( stdout);
			fflush( stdin);
			switch(num){
						case 1:
							//jugarWordle(db);
							break;
						case 2:
							printf("\nUSUARIO: ");
							fflush(stdout);
							fflush(stdin);
							gets(nombre);
							//mostrarPuntuaciones(db, nombre);
							break;

						case 3:
							menuInicio();
							break;
						case 4:
							exit(0);
							break;
						default:
							printf("Opcion incorrecta \n");
							menuUsuario(db);
							break;
		}
}

int menuInicio(){

    int num = 0;
    printf("\n ****BIENVENIDO A WORDC**** \n \n");
    fflush( stdin);
    printf("1. INICIAR SESION \n");
    fflush( stdin);
    printf("2. REGISTRARSE \n");
    fflush( stdin);
    printf("3.Salir \n Opcion: ");
    fflush(stdin);
    fflush( stdout);
    scanf("%d", &num);
    fflush( stdout);
    fflush( stdin);

    return num;
}
void menuAdministrador(){

	int num = 0;
		printf("\n**** MENU ADMINISTRADOR ****\n \n");
		fflush( stdin);

		printf("1. ANIADIR PALABRA \n");
		fflush( stdin);
		printf("2.BORRAR PALABRA \n");
	    fflush( stdin);
		printf("3.Cerrar sesion \n");
		fflush(stdin);
		printf("4.Salir \nOpcion: ");

		fflush(stdin);
		fflush( stdout);
		scanf("%d", &num);
		fflush( stdout);
		fflush( stdin);
		switch(num){

			case 1:
				//aniadirPalabraFichero();
				break;
			case 2:
				//mostrarPalabradeUnaPosicion();
				break;
			case 3:
				menuInicio();
				break;
			case 4:
				exit(0);
				break;
			default:
				printf("Opcion incorrecta \n");
				menuAdministrador();
				break;
}

}

int numeroDePalabrasEnFichero(char * fichero){ //Cambiar a que devuelva un int (return del cont)

	int cont = 0;
	char ca;

	FILE *pf;

	pf = fopen(fichero, "r");
	if(pf != (FILE *)NULL){
		while(1){
			ca = fgetc(pf);

			if(ca == '\n'){
				cont++;
			}
			if(ca == EOF){ //Si el cararcter es EOF End Of Line hemos llegado al final del fichero
				printf("%d\n", cont); // Numero de filas del fichero
				break;
			}
		}
		fclose(pf);
	}else{
		printf("Error al abrir el fichero");
	}
	return cont;
}



int esAdministrador(char * usuario, char * contra){
	int i, result=0;
	eAdministradores admins;
	admins.numeroAdministadores = numeroDePalabrasEnFichero("administradores.txt");

	admins.listaAdministradores = (sUsuario*)malloc(admins.numeroAdministadores*sizeof(sUsuario));

			FILE* pf = fopen("administradores.txt", "r");

			if(pf != (FILE*)NULL){
				for(i=0;i<admins.numeroAdministadores;i++){
					fscanf(pf,"%s%s",admins.listaAdministradores[i].usuario,admins.listaAdministradores[i].contrasena);
				}
			}
			for(i=0;i<admins.numeroAdministadores;i++){
				if ( (strcmp(admins.listaAdministradores[i].usuario, usuario) == 0) && (strcmp(admins.listaAdministradores[i].contrasena, contra) == 0)) {
					result=1;
					break;
				}
			}
				fclose(pf);


	return result;
}

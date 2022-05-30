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
void jugarWordle(sqlite3 * db){
	HANDLE consola=GetStdHandle(STD_OUTPUT_HANDLE);

	//CARGAR PALABRAS
		//char** listaPalabras= calloc(MAX_NUM_PALABRAS,sizeof(char*));
		//int contadorPalabras=0;
		char* palabra5letras=malloc(6*sizeof(char));
		FILE* ficheroPalabras= fopen("palabras.txt", "r");

		tListaPalabras lp ;
		lp.listaPalabras = calloc(MAX_NUM_PALABRAS,sizeof(char*));
		lp.contadorPalabras = 0;
		while(fscanf(ficheroPalabras, "%s", palabra5letras) != EOF && lp.contadorPalabras < MAX_NUM_PALABRAS){
			lp.listaPalabras[lp.contadorPalabras]= palabra5letras;
			lp.contadorPalabras++;
			palabra5letras=malloc(6*sizeof(char));

		}
		fclose(ficheroPalabras);

		//EMPEZAR JUEGO Y SELECCIONAR UNA PALABRA RANDOM
		srand(time(NULL));
		char* respuesta= lp.listaPalabras[rand()%lp.contadorPalabras];

		// LOOP PARA SEGUIR JUGANDO
		int numIntentos=6;
		bool seHaAcertado=false;
		char* intento= malloc(6*sizeof(char));
		while(numIntentos>0 && !seHaAcertado){
			//RECIBIR PALABRA INSERTADA POR EL USUARIO
			SetConsoleTextAttribute(consola,7);
			printf("\n%d intentos restantes\n", numIntentos);
			fflush(stdout);
			printf("Introduce palabra de 5 letras. Presiona ENTER para verificar.\n ");
			fflush(stdout);
			gets(intento);

			//CONVERTIR LA PALABRA EN MINUSCULA
			for(int i = 0; i<strlen(intento); i++){
				intento[i] = tolower(intento[i]);
			}

			numIntentos--;

			//VER SI SE ACIERTA O NO LA PALABRA
			seHaAcertado=procesarPalabra(respuesta, intento);


		}

		//MOSTRAR MENSAJE DE FIN DE JUEGO
		if (seHaAcertado) {
			int opcion;
			SetConsoleTextAttribute(consola,7);

			printf("\nFelicidades, has acertado la palabra en %d intentos\n", (6-numIntentos));
			fflush(stdout);

			printf("1= Seguir jugando\n2= Salir\n");
			fflush(stdout);

			scanf("%d",&opcion);
			fflush(stdout);
			fflush(stdin);


			switch(opcion){
				case 1:
					jugarWordle(db);
					break;
				case 2:
					exit(0);
					break;

				default:
					printf("Opcion incorrecta \n");
					break;
	}


		}else{
			int opcion;
			SetConsoleTextAttribute(consola,7);


			printf("\nHas agotado los intentos...La palabra correcta era %s\n", respuesta);
			fflush(stdout);

			printf("1= Seguir jugando\n2= Salir\n");
			fflush(stdout);
			fflush(stdin);
			scanf("%d",&opcion);
			fflush(stdin);


			switch(opcion){
							case 1:
									jugarWordle(db);
									break;
							case 2:
									exit(0);
									break;

							default:
									printf("Opcion incorrecta \n");
									break;
								}

		}

		for (int i = 0;  i< lp.contadorPalabras; i++) {
			free(lp.listaPalabras[i]);
		}
		free(lp.listaPalabras);
		free(palabra5letras);
		free(intento);



}
bool procesarPalabra(const char* laRespuesta, const char* elIntento){

	// pista
	//char pista[6]={'-', '-', '-', '-', '-', '\0'};
	char pista[]="-----";
	//indicar si la letra en la respuesta se encuentra en la pista
	bool flagsRespuesta[5]={false,false,false,false,false};

	if(strlen(elIntento)==5){ //NOTA: Equivocarse y no poner una palabra de 5 letras implica perder un intento

		// B=Bien= la letra esta justo en esa posicion de la palabra
		for (int i = 0;  i< 5; i++) {
			if (elIntento[i] == laRespuesta[i]) {
				pista[i] = 'B';
				flagsRespuesta[i]=true;
			}

		}

		// S=Si= la letra en esa posicion esta en algun sitio de la palabra
		for (int i = 0;  i< 5; i++) {
				if (pista[i] == '-') {
					for (int j = 0;  j< 5; j++) {
							if (elIntento[i] == laRespuesta[j] && !flagsRespuesta[j]) {
								//Hay coincidencia en otra posicion y no se ha usado como pista

								pista[i] = 'S';

								flagsRespuesta[j]=true;

								break;//terminar loop porque no queremos m�ltiples pistas para la misma letra
							}
						}
				}
			}
	}else{
		printf("La palabra tiene que ser de 5 letras!\n");
		fflush(stdout);
	}


	for (int i = 0; i < strlen(pista); i++)

	{

		if (pista[i]=='B')
		{
			HANDLE consola=GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(consola,2);
			printf("%c", elIntento[i]);




		}else if (pista[i]=='S'){
			HANDLE consola=GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(consola,6);
			printf("%c", elIntento[i]);




		}else if (pista[i]=='-'){
			HANDLE consola=GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(consola,7);
			printf("%c", elIntento[i]);




		}

	}



	return strcmp(pista, "BBBBB") ==0;//Si coincide con strcmp devuelve 0, significa que se ha acertado la palabra
}


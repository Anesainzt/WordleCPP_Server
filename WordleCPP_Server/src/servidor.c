// IMPORTANT: Winsock Library ("ws2_32") should be linked

#include <stdio.h>
#include <winsock2.h>
#include "sqlite3.h"
#include "BaseDatos.h"
#include "wordC.h"
#include "stdlib.h"
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

#define USUARIO "c"
#define CLAVE "13"

int main(int argc, char *argv[]) {

	WSADATA wsaData;
	SOCKET conn_socket; //el que lleva la conexion
	SOCKET comm_socket; //el que lo comunica
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512]; // lo que yo envio, lo que yo recibo

	printf("\nInitialising Winsock...\n"); // inicializa la libreria
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation creacion del socket( la primera estructura
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");
	// cual es la ip y cual es el puerto
	server.sin_addr.s_addr = inet_addr(SERVER_IP); //INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//BIND (the IP/port with socket)
	if (bind(conn_socket, (struct sockaddr*) &server,
			sizeof(server)) == SOCKET_ERROR) {
		printf("Bind failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	printf("Bind done.\n"); //DEJAR EL SOCKET EN ESPERA

	//LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR) {
		printf("Listen failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	//ACCEPT incoming connections (server keeps waiting for them)
	printf("Waiting for incoming connections...\n");
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET) {
		printf("accept failed with error code : %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),
			ntohs(client.sin_port));

	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);

	printf("Servidor iniciado\n");
	fflush(stdout);

	int fin = 0;
	sqlite3 *db;
	int result = sqlite3_open("bd.db",&db);
		if (result != SQLITE_OK)
		{
			printf("Error al abrir la base de datos\n");
			fflush(stdin);
		}
		crearTablas(db);
	do {
		/*EMPIEZA EL PROGRAMA DEL SERVIDOR*/

		int opcion;
		char nom[20], con[20],usuarioNuevo[51],contraseniaNueva[20];
		int resul,resulRegistro;

		do {
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			sscanf(recvBuff, "%d", &opcion);
			switch (opcion) {
			case 1:

				recv(comm_socket, recvBuff, sizeof(recvBuff), 0); //Recibe el nombre
				sprintf(nom, "%s", recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0); //Recibe la contrase�a
				sprintf(con, "%s", recvBuff);
				//La busca en la BBDD
				if (esAdministrador(nom,con)) {
					resul = 1;
				} else if (strcmp(nom, USUARIO) == 0 && strcmp(con, CLAVE) == 0) { //Comrpobar BBDD de
					resul = 2;
				} else {
					resul = 0;
				}
				sprintf(sendBuff, "%d", resul);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0); //Le envia al cliente 1,2,0
				break;
			case 2:
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0); //Recibe el Usuario nuevo
				sprintf(usuarioNuevo, "%s", recvBuff);
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0); //Recibe la contrasenia nueva
				sprintf(contraseniaNueva, "%s", recvBuff);
				//Lo a�ade en la BBDD



				sprintf(sendBuff, "%d", resulRegistro);
				send(comm_socket, sendBuff, sizeof(sendBuff), 0); //Le envia al cliente 0 o 1
				break;
			case 3:
				fin = 1;
				printf("Fin de la conexion\n");
				fflush(stdout);
				break;
			}
		} while (opcion == 3);

		/*ACABA EL PROGRAMA DEL SERVIDOR*/

	} while (fin == 0);

	// CLOSING the sockets and cleaning Winsock...
	closesocket(comm_socket);
	WSACleanup();

	return 0;
}

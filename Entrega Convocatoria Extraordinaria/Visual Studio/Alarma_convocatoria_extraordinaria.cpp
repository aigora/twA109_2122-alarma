#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <malloc.h>
#include "SerialClass.h"

#define N 50

typedef struct
{
	char ciudad[N];
	char calle[N];
	int numero;
} Direccion;

int menu_ppal(int menu);
void registrardomicilio();
void Definircontraseņa();
int contraseņa();
void cargar_datos_fichero(char[], char[], int);
void imprimir_fichero();




int main(void) {
	Serial* Arduino;
	char puerto[] = "COM3";
	char BufferSalida[10];
	char BufferEntrada[10];
	int bytes, i, Pin, menu;
	int decisionmenu = 0;
	char apagar;
	float numer1 = 50.0;
	char sendon[] = "a";
	char sendoff[] = "b";
	char lectura[5] = "\0";


	setlocale(LC_ALL, "es-ES");

	Arduino = new Serial((char*)puerto);
	printf("\n--------------------BIENVENIDO A SU ALARMA--------------------\n");
	Pin = contraseņa();

	printf("\n--------------------------------------------------------------\n\n");

	decisionmenu = menu_ppal(Pin);

	while (decisionmenu != 6) {
		switch (decisionmenu) {

		case 1:
			if (Arduino->IsConnected()) {

				Arduino->WriteData(sendon, sizeof(sendon) - 1);
				printf("\nLa alarma se ha activado");

				Sleep(500);
				decisionmenu = menu_ppal(Pin);
			}
			else {
				printf("\nArduino no esta conectado");
				decisionmenu = menu_ppal(Pin);
			}
			break;

		case 2:
			printf("\n--------------------HISTORIAL DE DOMICILIOS-------------------\n\n");
			imprimir_fichero();
			printf("--------------------------------------------------------------\n");
			decisionmenu = menu_ppal(Pin);
			break;

		case 3:
			Definircontraseņa();
			decisionmenu = menu_ppal(Pin);
			break;
		case 4:
			if (Arduino->IsConnected()) {

				Arduino->WriteData(sendoff, sizeof(sendoff) - 1);
				printf("\nLa alarma se ha apagado");

				Sleep(500);

				decisionmenu = menu_ppal(Pin);
			}
			else {
				printf("\nArduino no esta conectado");
				decisionmenu = menu_ppal(Pin);
			}
			break;
		case 5:
			registrardomicilio();
			decisionmenu = menu_ppal(Pin);
		}
	}

	printf("\nSistema apagado\n");
	return 0;
}

/*menú función principal*/

int menu_ppal(int Pin) {
	int menu;

	if (Pin == 1) {
		

		printf("\n-----------------------MENU PRINCIPAL-------------------------\n");
		printf("\nSeleccionar la opcion que desee:\n");
		printf("\t1-Encender alarma\n\t2-Historial de domicilio\n\t3-Cambiar contraseņa\n\t4-Apagar alarma\n\t5-Registrar domicilio\n\t6-Salir\n");
		/*Si selecciona encender, el sistema comenzará a funcionar, se activará el sensor y recibiremos informacion.
		Si recibe registro de datos, mostrará las últimas veces que saltó la alarma*/
		scanf_s("%d", &menu);

		while (menu != 1 && menu != 2 && menu != 3 && menu != 4 && menu != 5 && menu != 6)
		{
			printf("Seleccion no valida, introduzca de nuevo su eleccion: ");
			scanf_s("%d", &menu);
		}
	}
	return menu;
}


void registrardomicilio() {

	Direccion casa;
	Direccion* casa1;


	printf("\n--------------------------------------------------------------\n\n");
	printf("\nIntroduzca la ciudad o municipio donde reside: ");
	getchar();
	gets_s(casa.ciudad);
	printf("\nIntroduzca la calle donde reside: ");
	gets_s(casa.calle);
	printf("\nIntroduzca el numero de su vivienda: ");
	scanf_s("%d", &casa.numero);
	
	
	casa1 = (Direccion*)malloc(sizeof(Direccion));

	if (casa1 == NULL) {
		printf("\n Ha habido un error en la asignacion de memoria: \n");
		printf("Intente el registro de datos más tarde \n");
		free(casa1);

	}
	else {
		cargar_datos_fichero(casa.ciudad, casa.calle, casa.numero);
		printf("\n El registro se completó correctamente\n");
	}

	printf("\n--------------------------------------------------------------\n\n");

	

}



void Definircontraseņa() {
	FILE* contraseņa;
	int contraseņafichero, contraseņaantigua, contraseņa1, contraseņa2;
	errno_t e;

	e = fopen_s(&contraseņa, "contraseņa.txt", "rt");

	if (contraseņa == NULL) {
		printf("\nNo se ha podido abrir el fichero\n");
	}
	else {
		fscanf_s(contraseņa, "%d", &contraseņafichero);
		while (!feof(contraseņa)) {
			fscanf_s(contraseņa, "%d", &contraseņafichero);
		}
		fclose(contraseņa);
	}

	printf("\n--------------------------------------------------------------\n\n");

	printf("\nPara cambiar el numero pin, debe introducir el Pin antiguo: ");
	scanf_s("%d", &contraseņaantigua);

	while (contraseņaantigua != contraseņafichero) {
		printf("\nLa contraseņa introducida es incorrecta, introduzcala de nuevo: ");
		scanf_s("%d", &contraseņaantigua);
	}

	if (contraseņaantigua == contraseņafichero) {
		printf("\nContraseņa correcta, introduzca su nuevo Pin: ");
		scanf_s("%d", &contraseņa1);
		printf("\nIntroduzca de nuevo su contraseņa: ");
		scanf_s("%d", &contraseņa2);

		while (contraseņa1 != contraseņa2) {
			printf("\nLas contraseņas no coinciden, ");
			printf("\nEscriba su nuevo Pin: ");
			scanf_s("%d", &contraseņa1);
			printf("\nIntroduzca de nuevo su Pin: ");
			scanf_s("%d", &contraseņa2);
		}

		if (contraseņa1 == contraseņa2) {
			e = fopen_s(&contraseņa, "contraseņa.txt", "wt");
			if (contraseņa == NULL) {
				printf("\nNo se ha podido abrir el fichero\n");
			}
			else {
				fprintf(contraseņa, "%d", contraseņa1);
				fclose(contraseņa);
				printf("\nEl nuevo Pin se ha guardado.");
				printf("\n--------------------------------------------------------------\n\n");
			}
		}

	}


}


int contraseņa() {
	FILE* contraseņa;
	errno_t e;
	int pinreal, pin;

	e = fopen_s(&contraseņa, "contraseņa.txt", "rt");

	if (contraseņa == NULL) {
		printf("\nNo se ha podido abrir el fichero\n");
	}
	else {
		fscanf_s(contraseņa, "%d", &pinreal);
		while (!feof(contraseņa)) {
			fscanf_s(contraseņa, "%d", &pinreal);
		}
		fclose(contraseņa);
	}

	printf("\nPara acceder al menu, debe de introducir el pin: ");
	scanf_s("%d", &pin);
	while (pin != pinreal) {
		printf("\nContraseņa incorrecta, introduzcala de nuevo: ");
		scanf_s("%d", &pin);
	}
	if (pin == pinreal) {
		printf("\nContraseņa correcta\n");
		pin = 1;
	}
	return pin;
}


void cargar_datos_fichero(char ciudad[], char calle[], int numero)
{
	FILE* fichero;
	errno_t e;

	// printf(" %s %d, % s\n", calle, numero, ciudad);
	e = fopen_s(&fichero, "domicilio.txt", "at");
	if (fichero == NULL)
	{
		printf("No se a podido abrir el fichero\n");
	}
	else
	{

		fprintf(fichero, "%s %d, %s\n", calle, numero, ciudad);

		fclose(fichero);
	}


}


void imprimir_fichero()
{
	FILE* fichero;
	errno_t e;

	char calle[10];
	char ciudad[10];
	int numero;
	char cadena;
	int i = 0;


	e = fopen_s(&fichero, "domicilio.txt", "rt");

	if (fichero == NULL)
		printf("No se ha podido abrir el fichero\n");
	else
	{

		while (!feof(fichero))
		{
			fscanf_s(fichero, "%c", &cadena);

			// printf("Calle %s numero %d, %s\n", calle, numero, ciudad);
			printf("%c", cadena);
		}


		fclose(fichero);
	}


}


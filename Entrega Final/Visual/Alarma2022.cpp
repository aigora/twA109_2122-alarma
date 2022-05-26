#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include<time.h>
#include "SerialClass.h"


typedef struct
{
	char ciudad[100];
	char calle[100];
	int numero;
} Direccion;

int menu_ppal(int menu);
void registrardomicilio();
void Definircontraseña();
int contraseña();
void cambio1(char cadena[6], float* numero);
void cambio2(char cadena[5], float* numero);
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
	char sendon[]="a";
	char sendoff[] = "b";
	char lectura[5] = "\0";
	

	setlocale(LC_ALL, "es-ES");

	Arduino = new Serial((char*)puerto);
	printf("\n--------------------BIENVENIDO A SU ALARMA--------------------\n");
	Pin = contraseña();
	
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
				printf("\nVa a acceder al historial: \n");
				imprimir_fichero();
				decisionmenu = menu_ppal(Pin);
				break;

			case 3:
				Definircontraseña();
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
		printf("\nSeleccionar la opcion que desee:\n");
		printf("\t1-Si desea encender la alarma\n\t2-Historial de domicilio\n\t3-Cambiar contraseña\n\t4-Apagar alarma\n\t5-Registrar domicilio\n\t6-Salir\n");
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
	
	char direccion[50];
	Direccion casa;

		printf("\nIntroduzca la ciudad o municipio donde reside: ");
		getchar();
		gets_s(casa.ciudad);
		printf("\nIntroduzca la calle donde reside: ");
		gets_s(casa.calle);
		printf("\nIntroduzca el numero de su vivienda: ");
		scanf_s("%d", &casa.numero);

		cargar_datos_fichero(casa.ciudad, casa.calle, casa.numero);

}

 



	void cambio1(char cadena[6], float* numero) {
	float decenas = 0.00;
	float unidades = 0.00;
	float decimas = 0.00;
	float centesimas = 0.00;

	decenas = cadena[0] - '0';
	unidades = cadena[1] - '0';
	decimas = cadena[3] - '0';
	centesimas = cadena[4] - '0';

	*numero = (decenas * 10) + (unidades)+(decimas / 10) + (centesimas / 100);

}

void cambio2(char cadena[5], float* numero)
{
	float unidades = 0.00;
	float decimas = 0.00;
	float centesimas = 0.00;

	unidades = cadena[0] - '0';
	decimas = cadena[2] - '0';
	centesimas = cadena[3] - '0';

	*numero = (unidades)+(decimas / 10) + (centesimas / 100);
}


void Definircontraseña() {
	FILE* contraseña;
	int contraseñafichero, contraseñaantigua, contraseña1,  contraseña2;
	errno_t e;

	e = fopen_s(&contraseña, "contraseña.txt", "rt");

	if (contraseña == NULL) {
		printf("\nNo se ha podido abrir el fichero\n");
	}
	else {
		fscanf_s(contraseña, "%d", &contraseñafichero);
		while (!feof(contraseña)) {
			fscanf_s(contraseña, "%d", &contraseñafichero);
		}
		fclose(contraseña);
	}

	printf("\nPara cambiar el numero pin, debe introducir el Pin antiguo: ");
	scanf_s("%d", &contraseñaantigua);

	while (contraseñaantigua != contraseñafichero) {
		printf("\nLa contraseña introducida es incorrecta, introduzcala de nuevo: ");
		scanf_s("%d", &contraseñaantigua);
	}

	if (contraseñaantigua == contraseñafichero) {
		printf("\nContraseña correcta, introduzca su nuevo Pin: ");
		scanf_s("%d", &contraseña1);
		printf("\nIntroduzca de nuevo su contraseña: ");
		scanf_s("%d", &contraseña2);

		while(contraseña1 != contraseña2) {
			printf("\nLas contraseñas no coinciden, ");
			printf("\nEscriba su nuevo Pin: ");
			scanf_s("%d", &contraseña1);
			printf("\nIntroduzca de nuevo su Pin: ");
			scanf_s("%d", &contraseña2);
		}

		if (contraseña1 == contraseña2) {
			e = fopen_s(&contraseña, "contraseña.txt", "wt");
			if (contraseña == NULL) {
				printf("\nNo se ha podido abrir el fichero\n");
			}
			else {
				fprintf(contraseña, "%d", contraseña1);
				fclose(contraseña);
				printf("\nEl nuevo Pin se ha guardado.");
			}
		}
		
	}


}


int contraseña() {
	FILE* contraseña;
	errno_t e;
	int pinreal, pin;

	e = fopen_s(&contraseña, "contraseña.txt", "rt");

	if (contraseña == NULL) {
		printf("\nNo se ha podido abrir el fichero\n");
	}
	else {
		fscanf_s(contraseña, "%d", &pinreal);
		while (!feof(contraseña)) {
			fscanf_s(contraseña, "%d", &pinreal);
		}
		fclose(contraseña);
	}
	
	printf("\nPara acceder al menu, debe de introducir el pin: ");
	scanf_s("%d", &pin);
	while (pin != pinreal) {
		printf("\nContraseña incorrecta, introduzcala de nuevo: ");
		scanf_s("%d", &pin);
	}
	if (pin == pinreal) {
		printf("\nContraseña correcta\n");
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


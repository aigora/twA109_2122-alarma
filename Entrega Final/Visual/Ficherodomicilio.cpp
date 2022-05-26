#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define TAM 20;

void cargar_datos_fichero(char[], char[], int );
void imprimir_fichero();

int main()
{
	char* ci;
	char ciudad[20];
	int longitud1;
	
	char* ca;
	char calle[20];
	int longitud2;
	int numero;

	gets_s(ciudad, 20);
	longitud1 = strlen(ciudad);
	// ci = (char*)malloc(sizeof(char)*(longitud1+1));
	// printf("%d   %s\n", longitud1, ciudad);
	// printf("%s\n", ciudad);

	gets_s(calle, 20);
	longitud2 = strlen(calle);
	// ca = (char*)malloc(sizeof(char) * (longitud2 + 1));
	// printf("%d     %s\n", longitud2, calle);

	scanf_s("%d", &numero);
	cargar_datos_fichero(ciudad, calle, numero);

	imprimir_fichero();
}

void cargar_datos_fichero(char ciudad[], char calle[] , int numero) 
{
	FILE* fichero;
	errno_t e;
	
	// printf(" %s %d, % s\n", calle, numero, ciudad);
	e = fopen_s(&fichero, "direcciones.txt", "at");
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


	e = fopen_s(&fichero, "direcciones.txt", "rt");
	
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

// 04631384
// 55946
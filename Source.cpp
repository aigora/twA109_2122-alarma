#include <stdio.h>
#define TAM 20;

void cargar_datos_fichero(char, char, int);
void imprimir_fichero(void);


void cargar_datos_fichero(char ciudad, char calle, int numero) 
{
	FILE* fichero;
	errno_t e;
	


	e = fopen_s(&fichero, "direcciones.txt", "rt");
	if (e == NULL) {
		printf("No se a podido abrir el fichero\n");
	}
	else
	{
		
		while (!feof(fichero))
		{
			fprintf(fichero, "%s %d %s\n", calle, numero, ciudad);
		}

		fclose(fichero);
	}


}


void imprimir_fichero(void)
{
	FILE* fichero;
	errno_t e;

	char calle[10];
	char ciudad[10];
	int numero;



	e = fopen_s(&fichero, "direcciones.txt", "rt");
	

	if (fichero == NULL)
		printf("No se ha podido abrir el fichero\n");
	else
	{
		fscanf_s(fichero, "%s", &calle);
		fscanf_s(fichero, "%d", &numero);
		fscanf_s(fichero, "%s", &ciudad);

		while (!feof(fichero))
		{
			fscanf_s(fichero, "%s", &calle);
			fscanf_s(fichero, "%d", &numero);
			fscanf_s(fichero, "%s", &ciudad);

			printf("Calle %s numero %d, %s\n", calle, numero, ciudad);
			
		}

		
		fclose(fichero);
	}


}
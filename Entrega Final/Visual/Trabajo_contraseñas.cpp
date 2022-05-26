#include <stdio.h>
#include <string.h>
#include <locale.h>


void definir_contrase�a(void);


int main(void)
{
	setlocale(LC_ALL, "es-ES");

	int numero;
	printf("Si desea cambiar numero PIN pulse 1\n");
	scanf_s("%d", &numero);
	if (numero == 1) {
		definir_contrase�a();
	}
	
	

}


void definir_contrase�a(void)
{
	FILE* pass;
	errno_t e;
	int numero;
	int numero_antiguo;
	int numero_nuevo1;
	int numero_nuevo2;


	e = fopen_s(&pass, "password.txt", "rt");
	
	if (pass == NULL)
		printf("No se ha podido abrir el fichero\n");
	else
	{
		fscanf_s(pass, "%d", &numero);
		
		while (!feof(pass))
		{
			fscanf_s(pass, "%d", &numero);
		}

		printf("la password es: %d\n", numero);

		fclose(pass);
	}

	printf("Introduzca numero PIN antiguo: \n");
	scanf_s("%d", &numero_antiguo);

	if (numero_antiguo == numero)
	{
		printf("La contrase�a es correcta\n");

		printf("Introduzca nueva contrase�a: \n");
		scanf_s("%d", &numero_nuevo1);
		printf("Introduzca de nuevo la nueva contrase�a: \n");
		scanf_s("%d", &numero_nuevo2);

		if (numero_nuevo1 == numero_nuevo2)
		{
			

			e = fopen_s(&pass, "password.txt", "wt");

			if (pass == NULL)
				printf("No se ha podido abrir el fichero\n");
			else
			{
				fprintf(pass, "%d", numero_nuevo2);


				fclose(pass);
			}

			printf("La nueva contrase�a es %d", numero_nuevo1);
		}
		else 
			printf("Las contrase�as no coinciden \n");

	}
	else
	{
		printf("El numero PIN es incorrecto: ");

	}

	
}
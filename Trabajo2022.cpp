#include<stdio.h>

int menu_ppal(int menu);



int main(void) {
	int decisionmenu=0;
	char apagar;

	decisionmenu = menu_ppal(decisionmenu);
	if (decisionmenu == 1) {
		printf("\nLa alarma se ha activado");    // Una vez activada la alarma, usted podr� desactivarla cuando desee pulsando 'p'
		printf("\nCuando desee apagarla pulse 'p'");
		scanf_s("%c", &apagar);
		while (apagar != 'p') {
			printf("\nLa alarma no se ha desactivado, pulse 'p' para hacerlo: ");
			scanf_s("%c", &apagar);
		}
		if (apagar == 'p') printf("\nLa alarma se ha apagado");
	}

}

/*men� funci�n principal*/
int menu_ppal(int menu) {

	printf("Seleccionar la opci�n que desee:\n");
	printf("\t1-Si desea encender la alarma.\n\t2-Registro de datos\n");
	/*Si selecciona encender, el sistema comenzar� a funcionar, se activar� el sensor y recibiremos informacion.
	Si recibe registro de datos, mostrar� las �ltimas veces que salt� la alarma*/
	scanf_s("%d", &menu);

	while (menu != 1 && menu !=2)
	{
		printf("Seleccion no valida, introduzca de nuevo su eleccion: ");
		scanf_s("%d", &menu);
	}
	return menu;
}

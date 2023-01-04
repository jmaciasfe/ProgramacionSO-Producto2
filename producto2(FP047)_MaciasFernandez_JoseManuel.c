//Incluimos las librerias necesarias para el correcto funcionamiento del programa
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
//Definimos las siguientes constantes para hacer nuestro proyecto mas funcional
#define MAX_IP_LEN 40
#define MAX_COMMAND_LEN 100
#define MAX_LINE_LEN 255
//Declaramos antes de la funcion main las diferentes funciones y variables que vayamos a usar
void leerArchivo();
void lanzarPing(const char *ip);
void adaptadorRed();
char ip;


int main (void){

    char opcion;
    char archivo[MAX_LINE_LEN];
    //Creamos un menú dónde el usuario pueda escoger que opción desea realizar.
    printf("Que deseas realizar?\n");
    printf("a. Introducir la ruta del archivo a leer: \n");
    printf("b. Leer adaptadores de red\n");
    printf("c. Salir\n");
    scanf ("%c", &opcion);
    //Creamos un bucle while el cual nos va a advertir en el caso de que no seleccionemos una opción disponible y volveremos a entrar en el bucle hasta coger una opción disponible del menú.
    while (opcion != 'a' && opcion != 'A' && opcion != 'b' && opcion != 'B' && opcion != 'c' & opcion != 'C'){
        printf("Opcion no disponible, elija una mostrada en pantalla\n");
        fflush(stdin);
        scanf("%c", &opcion);
    } 
    //Switch el cual va a lanzar la función que escogamos en el menú principal.
    switch (opcion){
        case 'a':
        case 'A': leerArchivo();
            break;
        case 'b':
        case 'B': adaptadorRed();           
            break;
        case 'c':
        case 'C': printf("Has seleccionado salir del programa\n");
            break;
    }

    system("pause");
    return 0;
}
//Función la cual se va a encargar de leer nuestro archivo de texto con las diferentes IP's.
void leerArchivo(){
    //Creamos la variable f de tipo fichero la cual nos va a permitir abrir nuestro archivo
    FILE *f;
	char direcciones[100];
    char ip[MAX_IP_LEN] = { 0 }; 
    //Introducimos la ruta dónde está el archivo que queremos leer. 
	printf("\nIntroduce la ruta del archivo a leer: \n");
	scanf("%s", &direcciones); 
	
	f = fopen(direcciones, "r");
 
	if (f == NULL) {
		printf("Problemas de apertura del archivo\n"); //En el caso que introduzcamos mal la ruta del archivo nos mostrará esté mensaje de error. 
	}
	//En el caso que hayamos accedido correctamente al archivo, lanzará la función "lanzarPing", la cual hará un ping en las direcciones del archivo "direcciones.txt"
	else {
		while(fgets(ip, MAX_IP_LEN, f))
        {
            lanzarPing(ip);
        }
 
		fclose(f);
	}	

    system("pause");
    
}

//Función que hará ping en las direcciones ip de nuestro archivo .txt
void lanzarPing(const char *ip){
    char line[MAX_LINE_LEN] = { 0 };
    char command[MAX_COMMAND_LEN] = { 0 };
    FILE * fp;
 
    snprintf(command, MAX_COMMAND_LEN, "ping %s", ip);
    fp = popen(command, "r");
    if (fp == NULL)//En el caso de que sea NULL, osea que no se haya podido leer el archivo, nos lanzrá un error. 
    {
        
        return;
    }
 
    while (fgets(line, MAX_LINE_LEN, fp) != NULL)
    {
        //Aquí verifica la respuesta del host haciendo ping
        printf("%s", line);
    }
 
    pclose(fp);

    
}
//Función que abre nuestro CMD y muestra la información de nuestro adaptador de red.
void adaptadorRed(){

    char command [50];
        strcpy(command, "ipconfig /all");
        system(command);

    system("pause");

}


#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <stdlib.h>
#include <errno.h>
#include <string.h>
/**
*@method micmp metodo de tipo void que debera comparara una pareja de ficheros dependiendo de la expresión usada a parte listara los fallos y hara un salto de n1:n2 bytes
*@param n1 n2 de tipo entero seran los valores a saltar siendo en default 0; type de tipo entero este servira para decirnos cual de las funciones debe de hacer si solo comparar, listar saltar...
*       fichero1 y fichero2 de tipo char contendran las rutas de los ficheros a comparar.
*/
void micmp(int n1, int n2,int type,char* fichero1, char* fichero2) {

	int fdp1,fdp2;
	//Lectura de ficheros
	printf("__________________________________________________________________\n\n");
	fdp1 = open(fichero1,O_RDONLY);
	if(fdp1 == -1) {
		fprintf(stderr,"el fichero %s no existe o no se ha podido leer.\n",fichero1);
		printf("__________________________________________________________________\n\n");
		return;
	}
	fdp2 = open(fichero2,O_RDONLY);
	if(fdp2 == -1) {
		fprintf(stderr,"el fichero %s no existe o no se ha podido leer.\n",fichero2);
		printf("__________________________________________________________________\n\n");
		return;
		}
	int equals = 1;
	char buffer1[1024], buffer2[1024];
	size_t lenFich1 = read(fdp1,buffer1,1024);
	size_t lenFich2 = read(fdp2,buffer2,1024);
	if(read(fdp1,buffer1,1024) < 0 || read(fdp2,buffer2,1024) < 0) {printf("\n\n se ha producido un error al intentar ejecutar el read"); return;}
	if(lenFich1 != lenFich2){ equals = 2;}
	
	if(strcmp(fichero1,fichero2) == 0 && lenFich1 == lenFich2) { 
		printf("tienen la misma ruta y tamaño ergo deberian ser iguales.\n");	//está condición en mi opinión debería tener un return para acabar ya
											//que si dos ficheros tienen exactamente la misma ruta y tamaño quiere  
	}										//decir que son el mismo no obstante revisamos por si acaso.

	//comprobación de que el salto no sea mayor que el tamaño del fichero	
	if(n1 > lenFich1 || n2 > lenFich2) {
		printf("Error esta intentado saltar una posición superior al tamaño del fichero.\n"); 
		return;
	}
	//apuntamos a la posición pasada por parametro n1 y n2 que por defecto seran 0
	lseek(fdp1,n1,SEEK_SET);
	lseek(fdp2,n2,SEEK_SET);
	//Casos (solo ficheros) y (-i)
	if(type == 0 || type == 2) {
		while(read(fdp1,&buffer1,sizeof(char)) == 1 && read(fdp2,&buffer2,sizeof(char)) == 1) {
			if(*buffer1 != *buffer2) {
				equals = 0; 
				break;
			}
		} 
	//Casos (-l) y (-i -l)
	} else {
		//comprobamos cual es el mas grande para así poder recorrer el mayor
		int rep = 0,len = 0,p = 0;
		
		if(lenFich1 > lenFich2) {		
			len = lenFich1;
			p = n1;
		} else if(lenFich2 > lenFich1) {
			len = lenFich2;
			p = n2;
		} else {
			len = lenFich2;
			p = n2;
			equals = 1;
		}
		
		while(p < len-1) { 
			if(buffer1[n1] != buffer2[n2]) {
				if(rep == 0) {
					printf("Diferencias producidas:\n");
					printf("------------------------------------------------------------------\n");
					equals = 0;	
					rep++;
				}
				if(p >= lenFich1) { //Caso en el que fichero1 se acaba pero fichero2 sigue
					printf("Posición: %d Fichero: %s Caracter: NULL\n",n1+1,fichero1); //imprimimons n1+1 y n2+1 para asi ver las posiciones desde el 1 y no el 0
					printf("Posición: %d Fichero: %s Caracter: %c\n",n2+1,fichero2,buffer2[n2]);								    
					printf("------------------------------------------------------------------\n");
				} else if(p >= lenFich2) { //Caso en el que fichero2 se acaba pero fichero1 sigue	
					printf("Posición: %d Fichero: %s Caracter: %c\n",n1+1,fichero1,buffer1[n1]); 	
					printf("Posición: %d Fichero: %s Caracter: NULL\n",n2+1,fichero2);
					printf("------------------------------------------------------------------\n");
				} else { //Caso en el que se encuentran errores y se extraen
					printf("Posición: %d Fichero: %s Caracter: %c\n",n1+1,fichero1,buffer1[n1]); 	
					printf("Posición: %d Fichero: %s Caracter: %c\n",n2+1,fichero2,buffer2[n2]);
					printf("------------------------------------------------------------------\n");
				}
			}
			p++;
			n1++;
			n2++;
		}
	}
	//comprobación final de que son iguales o no
 	if(equals == 0) {
		printf("sus contenidos son distintos.\n");
	} else if (equals == 1) {
		printf("sus contenidos son iguales.\n");
	} else {		
		printf("sus contenidos son iguales, pero sus tamaños no.\n");	//este tercer caso es cuando equals == 2 que se produce cuando los ficheros
	}									//tienen tamaños diferentes pero exactamente los mismo elementos esto se produce por ejemplo
	//cierre de ficheros							//en los casos en los que se usa -i ya que saltan dejando contenido atras y pueden hacer distintos saltos
	close(fdp1);
	close(fdp2);
	printf("succesfull\n");
	printf("__________________________________________________________________\n\n");
	return;
}


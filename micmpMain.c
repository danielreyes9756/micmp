#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
/**
*main el cual se encargara de obtener los ficheros, -l e -i, tambien pasara a entero los valores de n1 y n2 y hara las llamadas para hacer una cosa u otra (listar, saltar, comparar) 
*/
void micmp(int n1, int n2,int type,char* fichero1, char* fichero2);
int main(int arg, char** argv) {
	
	char* dospuntos, *ptr;
	dospuntos = (char*)malloc(1*sizeof(char));
	if(dospuntos == NULL) {free(dospuntos); return 0;} //comprobamos que la memoria dinamica no esta vacía
	int i=1,type = 0,rep = 0,n1 = 0,n2 = 0;			
	
	while(i < arg) {
		if(strcmp(argv[1],"-i") == 0 && strcmp(argv[3],"-l") == 0) { //con -i y -l
			if(arg % 2 == 0) {
				if(rep == 0) {
					dospuntos = strtok(argv[2],":");
					n1 = atoi(dospuntos);
					dospuntos = strtok(NULL,":");
					n2 = atoi(dospuntos);
					type = 1;	
					i+=3;
					printf("prueba -i -l %s, %s\n",argv[i],argv[i+1]);
					micmp(n1,n2,type,argv[i],argv[i+1]);
				} else {
					printf("prueba -i -l %s, %s\n",argv[i],argv[i+1]);
					micmp(n1,n2,type,argv[i],argv[i+1]);
				}
			} else {
				printf("-i -l pero se necesita un número par de archivos\n");
				return 0;
			}
		} else if(strcmp(argv[1],"-i") == 0) { //con -i pero no -l
			if(arg % 2 != 0) {
				if(rep == 0) {	
					dospuntos = strtok(argv[2],":");
					n1 = atoi(dospuntos);
					dospuntos = strtok(NULL,":");
					n2 = atoi(dospuntos);
					type = 2;	
					i+=2;
					printf("prueba -i %s, %s\n",argv[i],argv[i+1]);
					micmp(n1,n2,type,argv[i],argv[i+1]);

				} else {
					printf("prueba -i %s, %s\n",argv[i],argv[i+1]);
					micmp(n1,n2,type,argv[i],argv[i+1]);
				}
			} else {
				printf("-i pero se necesita un número par de archivos\n");
				return 0;
			}
			
		} else if(strcmp(argv[1],"-l") == 0) { //con -l pero no -i
			if(arg % 2 == 0) {	
				if(rep == 0) {	
					type = 3;
					i+=1;
					printf("prueba -l %s, %s\n",argv[i],argv[i+1]);		
					micmp(n1,n2,type,argv[i],argv[i+1]);						
				} else {
					printf("prueba -l %s, %s\n",argv[i],argv[i+1]);
					micmp(n1,n2,type,argv[i],argv[i+1]);
				}
			} else {
				printf("-l pero se necesita un número par de archivos\n");
				return 0;
			}
		} else { //solo ficheros.
			if(arg % 2 != 0) {	
				printf("prueba solo archivos %s, %s\n",argv[i],argv[i+1]);
				micmp(n1,n2,type,argv[i],argv[i+1]);
			} else {
				printf("solo archivos se necesita un número par de archivos\n");
				return 0;
			}
		}
		i+=2;
		rep++;
	}
	dospuntos = NULL;
	free(dospuntos);
	return 0;
}

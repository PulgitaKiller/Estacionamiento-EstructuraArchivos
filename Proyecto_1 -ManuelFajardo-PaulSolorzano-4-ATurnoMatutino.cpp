#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <locale.h>

int main(){
	setlocale(LC_ALL, "spanish");
	FILE *storage, *ticketE, *ticketS;
	
	//Archivo Binario
	storage = fopen ("STRORAGE.inv", "rb+");
	if (storage == NULL){
		storage = fopen ("STRORAGE.inv", "wb+");
		if (storage == NULL){
			puts ( "No se puede abrir el archivo.");
			exit(0);
		}
	}
	
	//Archivo Texto Entrantes
	ticketE = fopen ("TICKET.txt", "r+");
	if (ticketE == NULL){
		ticketE = fopen ("TICKET.txt", "w+");
		if (ticketE == NULL){
			puts ( "No se puede abrir el archivo.");
			exit(0);
		}
	}
	
	//Archivo Texto Salientes
	ticketS = fopen ("PAGOS.txt", "r+");
	if (ticketS == NULL){
		ticketS = fopen ("PAGOS.txt", "w+");
		if (ticketS == NULL){
			puts ( "No se puede abrir el archivo.");
			exit(0);
		}
	}
	
	//Datos Entrantes
	struct carro{
		int autoID; //Matricula
		int ticketID; //Numero de Ticket
		int entradaID; //Entrada del Auto
	};
	struct carro lugar;
	
	//Variables
	int usuario;
	int admin = 1234; //Permite ver los vehiculos, modificar tarifas, etc...
	int ticketNID; //Ticket para buscar, editar, etc
	float coste = 15.5;
	float costeF;
	int horaS;
	char opc;
	long int rectam;
	int band=0;	
	rectam = sizeof (lugar);
	
	//Inicio
	while (1){ 
		
		rewind(storage);
		system("cls");
		printf("\n|==============================================|\n");
		printf("|\t\tParking MAPA                   |\n");
		printf("|==============================================|\n");
		printf("|                           (0)CONFIGURACIONES |\n");
		printf("|                                              |\n");
		printf("|      (1) GENERAR TICKET     (2)PAGAR         |\n");
		printf("|                                       2.0 ver|\n");
		printf("|==============================================|\n\n");
		printf("\tSELECCIONE UNA OPCIÓN: ");
		fflush(stdin);
		opc = getche();
		
		switch(opc){
			case '0':
				system("cls");
				printf("\n|==============================================|\n");
				printf("|\t\tConfiguraciones                |\n");
				printf("|==============================================|\n");
				printf("|                                              |\n");
				printf("| Contraseña:                                  |\n");
				scanf("%d",& usuario);
				printf("|                                              |\n");
				printf("|==============================================|\n");
				if(usuario == admin){
					system("cls");
					printf("\n|==============================================|\n");
					printf("|\t\tConfiguraciones                |\n");
					printf("|==============================================|\n");
					printf("|      (1) MOSTRAR TODO       (2) BORRAR       |\n");
					printf("|                                              |\n");
					printf("|      (3) MODIFICAR          (4) APAGAR       |\n");
					printf("|                                              |\n");
					printf("|                             (0) SALIR        |\n");
					printf("|                                              |\n");
					printf("|==============================================|\n\n");
					printf("\tSELECCIONE UNA OPCIÓN: ");
					fflush(stdin);
					opc = getche();
					
					switch(opc){
						case '0':
							system("PAUSE");
							break;
						
						case '1':
							system("cls");
							rewind(storage);
							printf("\n|==============================================|\n");
							printf("|\t\tConfiguraciones                |\n");
							printf("|==============================================|\n");	
							while(fread(&lugar, rectam, 1, storage) == 1){
								printf("-Número de Ticket: %d \n-Matricula: %d   \n-Entrada: %d \n", lugar.ticketID, lugar.autoID, lugar.entradaID);
								printf("|                                              |\n");
								printf("|==============================================|\n\n");
							}
							system("PAUSE");
							break;
							
						case '3':
							system("cls");
							printf("\n|==============================================|\n");
							printf("|\t\tConfiguraciones                |\n");
							printf("|==============================================|\n");
							printf("|                                              |\n");
							printf("| Ingrese el Nuevo Precio x Hora:              |\n");
							scanf("%f",& coste);
							printf("|                                              |\n");
							printf("|==============================================|\n");
							system("PAUSE");
							break;
						
						case '4':
							system("cls");
							printf("\n|==============================================|\n");
							printf("|\t\tConfiguraciones                |\n");
							printf("|==============================================|\n");
							printf("|                                              |\n");
							printf("|       Gracias por utiliza PIXEL MAPA         |\n");
							printf("|               Apagando...                    |\n");
							printf("|                                              |\n");
							printf("|==============================================|\n\n");
							system("PAUSE");
							exit(0);
								
					}
					system("PAUSE");
					break;
			} else {
				printf("Usuario Incorrecto\n");
				system("PAUSE");
			}
			break;
			
			case '1':
				system("cls");
				fseek (storage,0,SEEK_END);
				fseek (ticketE,0,SEEK_END);
				printf("\n|==============================================|");
				printf("\n|               GENERAR TICKET                 |\n");
				printf("|==============================================|\n");
				printf("|                                              |\n");
				//Registro Matricula
				printf("| Ingrese el Número de Matricula:              |\n");
				scanf("%d",& lugar.autoID);
				//Asigancion ID Ticket por random
				printf("|                                              |\n");
				lugar.ticketID = rand()& 979 - 20;
				printf("| Su Número de Ticket es: %d                   |", lugar.ticketID);
				//Hora de Entrada
				printf("\n|                                              |\n");
				printf("| Ingrese Hora de Entrada(24hrs):              |\n");
				scanf("%d",& lugar.entradaID);
				printf("|                                              |\n");
				printf("|==============================================|\n");
				//Imprimimos el Ticket en el .txt
				fprintf(ticketE, "|==============================================|\n"
				"|\t\tParking MAPA                   |\n"
				"|==============================================|\n"
				"   Matricula: %d        Numero Ticket: %d      \n"
				"            Hora Entrada: %d                  \n"
				"|==============================================|\n"
				, lugar.autoID, lugar.ticketID, lugar.entradaID);
				//Ticket Binario
				fwrite (&lugar, rectam, 1, storage);
				system("PAUSE");
				break;
				
			case '2':
				system("cls");
				fseek (storage,0,SEEK_END);
				fseek (ticketE,0,SEEK_END);
				fseek (ticketS,0,SEEK_END);
				printf("\n|==============================================|");
				printf("\n|                   PAGAR                      |\n");
				printf("|==============================================|\n");
				printf("|                        PAGO X HORA = %f    |\n", coste);
				printf("| Ingrese el Número de Ticket:                 |\n");
				scanf("%d",& ticketNID);
				printf("|                                              |\n");
				rewind(storage);
				while(fread(&lugar, rectam, 1, storage)){
					if(ticketNID == lugar.ticketID){
						printf("| Ingrese el Tiempo(24hrs):                    |\n");
						scanf("%d",& horaS);
						if(horaS > 24){
							printf("|  ¡EL COSTO AUMENTO POR DURAR MAS DE UN DÍA!  |\n");
							costeF = horaS * (coste + 25);
							printf("            Pago a Realizar: %f              \n", costeF);
							printf("|                                              |\n");
							printf("|==============================================|\n");
							fprintf(ticketS, "|==============================================|\n"
							"|\t\tParking MAPA                   |\n"
							"|==============================================|\n"
							"   Matricula: %d        Numero Ticket: %d      \n"
							"            Hora Entrada: %d                  \n"
							"            Pago realizado: %f                \n"
							"                ¡PAGADO!                      \n"
							"|==============================================|\n"
							, lugar.autoID, lugar.ticketID, lugar.entradaID, costeF);
							lugar.ticketID = NULL;
							lugar.autoID = NULL;
							lugar.entradaID = NULL;
							system("PAUSE");
						} else {
							costeF = horaS * coste;
							printf("            Pago a Realizar: %f              \n", costeF);
							printf("|                                              |\n");
							printf("|==============================================|\n");
							fprintf(ticketS, "|==============================================|\n"
							"|\t\tParking MAPA                   |\n"
							"|==============================================|\n"
							"   Matricula: %d        Numero Ticket: %d      \n"
							"            Hora Entrada: %d                  \n"
							"            Pago realizado: %f                \n"
							"                ¡PAGADO!                      \n"
							"|==============================================|\n"
							, lugar.autoID, lugar.ticketID, lugar.entradaID, costeF);
							lugar.ticketID = NULL;
							lugar.autoID = NULL;
							lugar.entradaID = NULL;
							system("PAUSE");
						}
					}
					if(ticketNID != lugar.ticketID){
						printf("\n\t ¡ERROR! \nEl Número de Ticket no existe \n\n");
						system("PAUSE");
						break;
					}
				}
				break;
		}
	}
}

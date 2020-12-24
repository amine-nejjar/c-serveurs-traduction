#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

int main(){
	int dsc,con,i,cp=0;
	struct  sockaddr_in adrSrv;
	char * reqt=calloc(1024,sizeof(char));
	char * reps=calloc(1024,sizeof(char));
	char * exit=calloc(1024,sizeof(char));
	char * choice=calloc(1024,sizeof(char));
	char * answer=calloc(1024,sizeof(char));
	adrSrv.sin_family=AF_INET;
	adrSrv.sin_port=htons(2525);
	inet_aton("127.0.0.1",&(adrSrv.sin_addr)); //2012.13.45.1
	strcpy(choice,"5");
	
	while(strcmp(choice,"4")!=0){
		system("clear");
		printf("-------------------------------------------------------------------------------------------------------------\n");
		printf("--------------------------------------------THE TRANSLATION SERVER-------------------------------------------\n");
		printf("-------------------------------------------------------------------------------------------------------------\n\n\n");
		printf("Hello and welcome to our translator, please chose your option : \n");
		printf("      ------------------------------------------\n");
		printf("     | 1-ENGLISH => FRENCH                      |\n");
		printf("     | 2-ENGLISH => Dutch(Netherland)           |\n");
		printf("     | 3-ENGLISH => JAPENESE(LATINE LETTERS)    |\n");
		printf("     | 4-Exit the translation server            |\n");

		printf("      ------------------------------------------\n\n\n");
		printf("Your option : ");
		memset(choice,'\0',1024);
		scanf("%s",choice);	
		while(strcmp(choice,"1")!=0 && strcmp(choice,"2")!=0 && strcmp(choice,"3")!=0 && strcmp(choice,"4")!=0){
			system("clear");
			printf("-------------------------------------------------------------------------------------------------------------\n");
			printf("--------------------------------------------THE TRANSLATION SERVER-------------------------------------------\n");
			printf("-------------------------------------------------------------------------------------------------------------\n\n\n");
			printf("Hello and welcome to our translator, please chose your option : \n");
			printf("      ------------------------------------------\n");
			printf("     | 1-ENGLISH => FRENCH                      |\n");
			printf("     | 2-ENGLISH => Dutch(Netherland)           |\n");
			printf("     | 3-ENGLISH => JAPENESE(LATINE LETTERS)    |\n");
			printf("     | 4-Exit the translation server            |\n");

			printf("      ------------------------------------------\n\n");
			printf("INVALIDE CHOICE. PLEASE CHOOSE 1,2,3 or 4\n");
			printf("Your option : ");
			memset(choice,'\0',1024);
			scanf("%s",choice);
			system("clear");
			printf("\n");

		}
		if(strcmp(choice,"4")==0){
			break;
		}else{
			cp=0;
			while(1){
				memset(&adrSrv.sin_zero,'0',8);
				dsc=socket(PF_INET,SOCK_STREAM,6);
				con=connect(dsc,(struct sockaddr*)&adrSrv,sizeof(struct sockaddr));


				system("clear");
				printf("-------------------------------------------------------------------------------------------------------------\n");
				printf("--------------------------------------------THE TRANSLATION SERVER-------------------------------------------\n");
				printf("---------------------------------------(type 0 to go back to main menu)--------------------------------------\n");
				if(cp==0){
					printf("\n\n\n\n");;
			
				}
				else{
					printf("\n\n\n");
				}
				recv(dsc, reps, 1024, 0);memset(reps,'\0',1024);//bienvenue ...
				recv(dsc, reps, 1024, 0);memset(reps,'\0',1024);//devise

				send(dsc, choice, 1024, 0);
				
				recv(dsc, reps, 1024, 0);
				if(cp!=0){
					printf("%s\n",answer);memset(answer,'\0',1024)
;				}
				printf("%s",reps);memset(reps,'\0',1024);//enter a word to translate
				scanf("%s",reqt);
				if(strcmp(reqt,"0")==0){close(dsc);break ;}
				send(dsc, reqt, 1024, 0);memset(reqt,'\0',1024);
				recv(dsc, reps, 1024, 0);//response from languageserver
				strcpy(answer,reps);memset(reps,'\0',1024);cp++;
				close(dsc);
			}
			
		}		
		
	}
	system("clear");
	printf("-------------------------------------------------------------------------------------------------------------\n");
	printf("--------------------------------------------THE TRANSLATION SERVER-------------------------------------------\n");
	printf("-------------------------------------------------------------------------------------------------------------\n\n\n");
	printf("          Thank you for using our server !      \n");
	printf("      ------------------------------------------\n");
	printf("     |                À bientôt                 |\n");
	printf("     |              See you later               |\n");
	printf("     |             Tot  binnenkort              |\n");
	printf("     |     Mata chikaiuchini o ai shimashou     |\n");
	printf("      ------------------------------------------\n\n\n");
	scanf("%s",reqt);
	
return 0;
}

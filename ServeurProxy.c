#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <ctype.h>

int main(){
	int dss, dsc, lgAdrClt,i,cpt=0;
	int dscFR,dscDutch,dscJP;
	struct  sockaddr_in adrSrv,adrClt;
	struct  sockaddr_in SrvFR,SrvDutch,SrvJP;
	char * reqt1=calloc(1024,sizeof(char));
	char * reqt2=calloc(1024,sizeof(char));
	char * reps=calloc(1024,sizeof(char));
	//configuration du serveur
	adrSrv.sin_family=AF_INET;
	adrSrv.sin_port=htons(2525);
	inet_aton("127.0.0.1",&(adrSrv.sin_addr)); //2012.13.45.1
	memset(&adrSrv.sin_zero,'0',8);//initialiser l'address
	//creation de socket
	dss=socket(PF_INET,SOCK_STREAM,6);
	bind(dss,(struct sockaddr*)&adrSrv,sizeof(struct sockaddr));//associer l'address du server au socket qu'on a creer
	listen(dss,10);//ecouter à une nouvelle connexion (10=BACKLOG : nombre de connexions alloués)
	while(1){
		dsc = accept(dss, (struct sockaddr*)&adrClt, (socklen_t*)&lgAdrClt);//accepter la connection => accept(int socket,address client, size of structur)

		strcpy(reps,"------------------------------- WELCOME TO THE TRANSLATION SERVER ------------------------------\n\n\n");
		send(dsc, reps, 1024, 0);//1024 : size of data we want to send (byte) // 0 : flag
		memset(reps,'\0',1024);// liberer reps de la memoire ( resete ) 

		strcpy(reps,"Chose one of the languages FR | Dutch | Japenese:\n\n");
		send(dsc, reps, 1024, 0);
		memset(reps,'\0',1024);

		//memset(reqt1,'\0',1024);
		recv(dsc, reqt1, 1024, 0);// recieve data
			if(strcmp(reqt1,"1")==0){
				printf("heeere");
				memset(reqt1,'\0',1024);
				strcpy(reps,"enter a word to translate to french : ");
			   	send(dsc, reps, 1024, 0);
			   	memset(reps,'\0',1024);
				
				recv(dsc, reqt2, 1024, 0);
				//configuration address 
				SrvFR.sin_family=AF_INET;
				adrSrv.sin_port=htons(2527);
				inet_aton("127.0.0.1",&(adrSrv.sin_addr));// modif d adresse
				memset(&adrSrv.sin_zero,'0',8);

				dscFR=socket(PF_INET,SOCK_STREAM,6);//creation de socket qui va connecter au serveur euro
				connect(dscFR,(struct sockaddr*)&adrSrv,sizeof(struct sockaddr));//se connecter au server
				send(dscFR, reqt2, 1024, 0);//envoyer le montant
				
				memset(reqt2,'\0',1024);
				recv(dscFR, reqt2, 1024, 0);
				send(dsc, reqt2, 1024, 0);
				close(dscFR);
			}
			else if(strcmp(reqt1,"2")==0){
				memset(reqt1,'\0',1024);
				strcpy(reps,"enter a word to translate to Dutch : ");
			    	send(dsc, reps, 1024, 0);
			    	memset(reps,'\0',1024);
				
				recv(dsc, reqt2, 1024, 0);
				
				SrvDutch.sin_family=AF_INET;
				adrSrv.sin_port=htons(2526);
				inet_aton("127.0.0.1",&(adrSrv.sin_addr)); // modification d address
				memset(&adrSrv.sin_zero,'0',8);
				dscDutch=socket(PF_INET,SOCK_STREAM,6);
				connect(dscDutch,(struct sockaddr*)&adrSrv,sizeof(struct sockaddr));
				send(dscDutch, reqt2, 1024, 0);
				
				memset(reqt2,'\0',1024);
				recv(dscDutch, reqt2, 1024, 0);
				send(dsc, reqt2, 1024, 0);
				close(dscDutch);
			}else if(strcmp(reqt1,"3")==0){
				memset(reqt1,'\0',1024);
				strcpy(reps,"enter a word to translate to Japenese : ");
			    	send(dsc, reps, 1024, 0);
			    	memset(reps,'\0',1024);
				
				recv(dsc, reqt2, 1024, 0);
				
				SrvJP.sin_family=AF_INET;
				adrSrv.sin_port=htons(2528);
				inet_aton("127.0.0.1",&(adrSrv.sin_addr)); // modification d address
				memset(&adrSrv.sin_zero,'0',8);
				dscJP=socket(PF_INET,SOCK_STREAM,6);
				connect(dscJP,(struct sockaddr*)&adrSrv,sizeof(struct sockaddr));
				send(dscJP, reqt2, 1024, 0);
				
				memset(reqt2,'\0',1024);
				recv(dscJP, reqt2, 1024, 0);
				send(dsc, reqt2, 1024, 0);
				close(dscJP);
			}

		close(dsc);

	}
return 0;
}

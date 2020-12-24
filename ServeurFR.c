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


char *mot(FILE *fichier){
	char *mot=(char*)malloc(100*sizeof(char)),actuel;int k=0;
	actuel=getc(fichier);
	if(actuel==EOF) {return NULL;}
	while(actuel!='*'){
		if(actuel!='*'){
			mot[k]=actuel;}
		actuel=getc(fichier);
		k++;
	}
	mot[k]='\0';

	return mot;	
}

FILE *ouvrir(int i){
	FILE *fichier=NULL;
	if(i==0){
		fichier=fopen("dictionnaries/anglaise.txt","r");
	}
	else if(i==1){
		fichier=fopen("dictionnaries/francaise.txt","r");
	}else if(i==2){
		fichier=fopen("dictionnaries/type.txt","r");
	}
	
	return fichier;
}
char *get_word_by_position(int position,int choice){
	char *mot=(char*)malloc(100*sizeof(char)),actuel;int k;
	FILE *fichier;
	if(choice==1){
		fichier=ouvrir(1);
	}
	else if(choice==2){		
		fichier=ouvrir(2);
	}
	for(int i=1;i<position;i++){
		actuel=getc(fichier);
		while(actuel!='*'){
			actuel=getc(fichier);}
	}
	k=0;
	actuel=getc(fichier);
	while(actuel!='*'){
			mot[k]=actuel;
			actuel=getc(fichier);
			k++;}
	mot[k]='\0';
	fclose(fichier);
	return mot;
}
int existe_en_dict(char *chaine){// verfier si un mot existe bien, revoie 1 si oui 0 sinon
	
	FILE *fichier;int taille=strlen(chaine);
	int cpt=1;
	char *mots;
	fichier=ouvrir(0);
	mots=mot(fichier);
	while(mots!=NULL){
		if(strcmp(chaine,mots)==0){
			fclose(fichier);
			return cpt;
		}
		free(mots);
		mots=mot(fichier);
		cpt++;
	}
	
	fclose(fichier);
	return 0;	
}

int main(){
	int dss, dsc, lgAdrClt,i,nbr;
	struct  sockaddr_in adrSrv,adrClt;
	char * reqt=calloc(1024,sizeof(char));
	char * fr=calloc(1024,sizeof(char));
	char * type=calloc(1024,sizeof(char));
	char * reps=calloc(1024,sizeof(char));

	//configuration d'address du serveur
	adrSrv.sin_family=AF_INET;
	adrSrv.sin_port=htons(2527);
	inet_aton("127.0.0.1",&(adrSrv.sin_addr));// modification d adresse
	memset(&adrSrv.sin_zero,'0',8);

	dss=socket(PF_INET,SOCK_STREAM,6);//creation de socket
	bind(dss,(struct sockaddr*)&adrSrv,sizeof(struct sockaddr));
	listen(dss,10);
	while(1){
		dsc = accept(dss, (struct sockaddr*)&adrClt, (socklen_t*)&lgAdrClt);
        	recv(dsc, reqt, 1024, 0);

		nbr=existe_en_dict(reqt);	
		if(nbr==0){
			strcpy(reps,"sorry, your word doesn't existe in our dictionnary, your can try at translate.google.com ");
		}else{
		fr=get_word_by_position(nbr,1);
		type=get_word_by_position(nbr,2);
		strcpy(reps,"| the word ");
		strcat(reps,reqt);
		strcat(reps," ( ");
		strcat(reps,type);
		strcat(reps," ) translates in french : ");
		strcat(reps,fr);
		strcat(reps," |");	
		}

		send(dsc, reps, 1024, 0);
		memset(reps,'\0',1024);
		memset(reqt,'\0',1024);
		
		
		
		close(dsc);
		
	}
return 0;
}

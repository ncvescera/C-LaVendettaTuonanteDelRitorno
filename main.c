#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRLEN 50
#define FSTUDENTE "studente.txt"
#define FDOCENTE "docente.txt"
#define FDIRIGENTE "dirigente.txt"

void substring(char stringa[], char ruolo[]);
void replace(char* stringa, char vecchio, char nuovo);

int main(){
    
    char *data; 
    char stringa[MAXSTRLEN+1];
    char ruolo[MAXSTRLEN+1];
    char temp[MAXSTRLEN+1];
    
    FILE *puntafile;
    
    data = getenv("QUERY_STRING"); //il vaolore che viene passatro tramite un form risiede dentro ad una variabile d'ambiente chiamata QUERY_STRING
    sscanf(data,"%s",stringa);     // getenv permette di prendere quella variabile e restituisce un puntatore a char
    
    substring(stringa,ruolo);
 
    printf("Content-type:text\n\n");
    printf("<html>\n");
    printf("<body>\n");
    printf("<center><h1>%s</h1><br>",ruolo);
    
    if(strcmp(ruolo,"studente")==0)
       puntafile=fopen(FSTUDENTE,"r");
    
    if(strcmp(ruolo,"docente")==0)
       puntafile=fopen(FDOCENTE,"r");
    
    if(strcmp(ruolo,"dirigente")==0)
       puntafile=fopen(FDIRIGENTE,"r");
    
    fscanf(puntafile,"%s",temp);
    replace(temp,'+',' ');
    printf("%s",temp);
  
    printf("</center></body>\n");
    printf("</html>\n");
    fclose(puntafile);

}
void substring(char stringa[], char ruolo[]){
    int lunghezza = strlen(stringa);
    int i;
    int j=0;
    
//inizia dopo 6 caratteri perchè il contenuto dell'array stringa è: (es.)"ruolo=studente"
    for(i=6;i<lunghezza;i++){   
        ruolo[j]=stringa[i];
        j++;
    }
    ruolo[j]='\0'; //viene aggiunto il terminatore di stringa altrimenti stampava caratteri a caso
}
void replace(char* stringa, char vecchio, char nuovo){
    int i;
    for(i=0;i<strlen(stringa);i++){
        if(stringa[i]==vecchio)
            stringa[i]=nuovo;
  }
}

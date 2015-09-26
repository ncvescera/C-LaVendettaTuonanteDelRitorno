#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FSTUDENTE "studente.txt"
#define FDOCENTE "docente.txt"

void substring(char stringa[], char ruolo[]);
void replace(char* stringa, char vecchio, char nuovo);

int main(){
    
    char *data; 
    char stringa[50];
    char ruolo[50];
    char temp[50];
    
    FILE *puntafile;
    
    data = getenv("QUERY_STRING");
    sscanf(data,"%s",stringa);
    
    substring(stringa,ruolo);
 
    printf("Content-type:text\n\n");
    printf("<html>\n");
    printf("<body>\n");
    printf("<center><h1>%s</h1><br>",ruolo);
    
    if(strcmp(ruolo,"studente")==0)
       puntafile=fopen(FSTUDENTE,"r");
    
    if(strcmp(ruolo,"docente")==0)
       puntafile=fopen(FDOCENTE,"r");
     
    fscanf(puntafile,"%s",temp);
    replace(temp,'+',' ');
    printf("%s",temp);

    
    
    printf("</center></body>\n");
    printf("</html>\n");


}
void substring(char stringa[], char ruolo[]){
    int lunghezza = strlen(stringa);
    int i;
    int j=0;
    
    
    for(i=6;i<lunghezza;i++){   
        ruolo[j]=stringa[i];
        j++;
    }
    ruolo[j]='\0';
}
void replace(char* stringa, char vecchio, char nuovo){
    int i;
    for(i=0;i<strlen(stringa);i++){
        if(stringa[i]==vecchio)stringa[i]=nuovo;
  }
}
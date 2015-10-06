#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRLEN 200
#define FSTUDENTE "studente.txt"
#define FDOCENTE "docente.txt"
#define FDIRIGENTE "dirigente.txt"

struct s_record{
    char ruolo[MAXSTRLEN+1];
    char dati[MAXSTRLEN+1];
};
typedef struct s_record record;
void substring(char stringa[], char ruolo[]);
void replace(char* stringa, char vecchio, char nuovo);

int main(){
    /*
    char studente[MAXSTRLEN+1];
    char dirigente[MAXSTRLEN+1];
    char docente[MAXSTRLEN+1];
    */
    int i = 0;
    int cont;
    record *array;
    FILE *puntafileTemp;
    char temp[MAXSTRLEN+50];
    FILE *puntafileRuoli;
    
    puntafileRuoli = fopen("ruoli.txt","r");
    while(!feof(puntafileRuoli)){
        fgets(temp,MAXSTRLEN+1,puntafileRuoli);
        i++;
    }
    
    array = (record*)malloc(i*sizeof(record));
    fseek(puntafileRuoli,0,SEEK_SET); //si scosta di 0 pisizioni dall'inizio del file (SEEK_SET è l'inizio del file)
    i=0;
    while(!feof(puntafileRuoli)){
        fscanf(puntafileRuoli,"%s\n",array[i].ruolo);
        //fgets(array[i].ruolo,MAXSTRLEN+1,puntafileRuoli);
        i++;
    }
    printf("%s,%s,%s",array[0].ruolo,array[1].ruolo,array[2].ruolo);
    
    cont = i;
    i = 0;
    while(cont>0){
        strcat(array[i].ruolo,".txt");
        puntafileTemp = fopen(array[i].ruolo,"r");
        fscanf(puntafileTemp,"%s",array[i].dati);
        replace(array[i].dati,'+',' ');
        fclose(puntafileTemp);
        cont --;
        i++;
    }
    
    printf("\n\n%s",array[1].dati);
    
    FILE *puntafileHTML;
    puntafileHTML = fopen("index.html","w");
    /*
    data = getenv("QUERY_STRING"); //il vaolore che viene passatro tramite un form risiede dentro ad una variabile d'ambiente chiamata QUERY_STRING
    sscanf(data,"%s",stringa);     // getenv permette di prendere quella variabile e restituisce un puntatore a char
    
    substring(stringa,ruolo);
     */
    //fprintf(puntafileHTML,"Content-type:text\n\n");
    
    fprintf(puntafileHTML,"<html>\n");
    fprintf(puntafileHTML,"<head><title>LaPaginaPseudodinamica</title></head>");
    fprintf(puntafileHTML,"<body>\n");
    //form
    fprintf(puntafileHTML,"<form name=\"frm\"><center><h1>Seleziona il campo da stampare</h1><br><table><tr><td width=\"320px\"><select name=\"sel\" class=\"form-control\" style=\"width:300px;\" onchange=\"aggiornaHidden(this)\"><option value=\"\"  selected=\"selected\">Seleziona</option>");
    cont = i;
    for(i=0;i<cont;i++)
        fprintf(puntafileHTML,"<option value=\"<h1>%s</h1>%s\">%s</option>",array[i].ruolo,array[i].dati,array[i].ruolo);
    
    fprintf(puntafileHTML,"</select></td></tr></talbe></form>");
    //scriptJS
    fprintf(puntafileHTML,"<SCRIPT type=\"text/javascript\">\nfunction aggiornaHidden(sel){var f = document.frm;f.value = sel.options[sel.selectedIndex].value; ; document.write(\"<center>\"+f.value+\"</center>\");}</SCRIPT>");
    
  
    fprintf(puntafileHTML,"</center></body>\n");
    fprintf(puntafileHTML,"</html>\n");
    fclose(puntafileHTML);
    
    return(EXIT_SUCCESS);
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
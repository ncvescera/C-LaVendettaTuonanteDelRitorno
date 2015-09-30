#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRLEN 200
#define FSTUDENTE "studente.txt"
#define FDOCENTE "docente.txt"
#define FDIRIGENTE "dirigente.txt"

void substring(char stringa[], char ruolo[]);
void replace(char* stringa, char vecchio, char nuovo);

int main(){
    
    char studente[MAXSTRLEN+1];
    char dirigente[MAXSTRLEN+1];
    char docente[MAXSTRLEN+1];
    
    
    FILE *puntafileDOCENTE;
    puntafileDOCENTE = fopen("docente.txt","r");
    fscanf(puntafileDOCENTE,"%s",docente);
    replace(docente,'+',' ');
    
    FILE *puntafileDIRIGENTE;
    puntafileDIRIGENTE = fopen("dirigente.txt","r");
    fscanf(puntafileDIRIGENTE,"%s",dirigente);
    replace(dirigente,'+',' ');
    
    FILE *puntafileSTUDENTE;
    puntafileSTUDENTE = fopen("studente.txt","r");
    fscanf(puntafileSTUDENTE,"%s",studente);
    replace(studente,'+',' ');
    
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
    fprintf(puntafileHTML,"<form name=\"frm\"><center><h1>Seleziona il campo da stampare</h1><br><table><tr><td width=\"320px\"><select name=\"sel\" class=\"form-control\" style=\"width:300px;\" onchange=\"aggiornaHidden(this)\"><option value=\"\"  selected=\"selected\">Seleziona</option><option value=\"<h1>Docente</h1>%s\">Docente</option><option value=\"<h1>Dirigente</h1>%s\">Dirigente</option><option value=\"<h1>Studente</h1>%s\">Studente</option></select></td><td></td></tr></table></form>",docente,dirigente,studente);
    //scriptJS
    fprintf(puntafileHTML,"<SCRIPT type=\"text/javascript\">\nfunction aggiornaHidden(sel){var f = document.frm;f.value = sel.options[sel.selectedIndex].value; ; document.write(\"<center>\"+f.value+\"</center>\");}</SCRIPT>");
    
  
    fprintf(puntafileHTML,"</center></body>\n");
    fprintf(puntafileHTML,"</html>\n");
    fclose(puntafileHTML);

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
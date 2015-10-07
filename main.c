#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRLENRUOLO 30
#define MAXSTRLEN 200

struct s_record{
    char ruolo[MAXSTRLENRUOLO+1];
    char dati[MAXSTRLEN+1];
};
typedef struct s_record record;

void replace(char* stringa, char vecchio, char nuovo);

int main(){
    
    int i = 0;
    int cont;
    char temp[MAXSTRLEN];
    record *array;
    FILE *puntafileRuoli;
    FILE *puntafileTemp;
    
    puntafileRuoli = fopen("ruoli.txt","r");
    while(!feof(puntafileRuoli)){
        fgets(temp,MAXSTRLENRUOLO+1,puntafileRuoli); //legge riga per riga e conta le righe
        i++;
    }
    
    array = (record*)malloc(i*sizeof(record)); //dichiaro l'arrey dinamico di record
    
    fseek(puntafileRuoli,0,SEEK_SET); //si scosta di 0 pisizioni dall'inizio del file (SEEK_SET è l'inizio del file)
    
    i=0;
    while(!feof(puntafileRuoli)){
        fscanf(puntafileRuoli,"%s\n",array[i].ruolo);
        i++;
    }
    
    cont = i;
    i = 0;
    while(cont>0){
        strcat(array[i].ruolo,".txt");
        puntafileTemp = fopen(array[i].ruolo,"r");
        fscanf(puntafileTemp,"%s",array[i].dati);
        replace(array[i].dati,'+',' ');
        replace(array[i].dati,'-','\n');
        fclose(puntafileTemp);
        cont --;
        i++;
    }
        
    FILE *puntafileHTML;
    puntafileHTML = fopen("index.html","w");
    
    fprintf(puntafileHTML,"<html>\n");
    fprintf(puntafileHTML,"<head><title>LaPaginaPseudodinamica</title></head>");
    fprintf(puntafileHTML,"<body>\n");
    //form
    fprintf(puntafileHTML,"<form name=\"frm\"><center><h1>Seleziona il campo da stampare</h1><br><table><tr><td width=\"320px\"><select name=\"sel\" class=\"form-control\" style=\"width:373px;\" onchange=\"changeTextarea(this)\"><option value=\"\"  selected=\"selected\">Seleziona</option>");
    
    cont = i;
    for(i=0;i<cont;i++)
        fprintf(puntafileHTML,"<option value=\"%s\">%s</option>",array[i].dati,array[i].ruolo);
    fprintf(puntafileHTML,"</select><textarea id=\"area\" rows=\"20\" cols=\"50\"></textarea> </td></tr></talbe></form> ");
    
    //scriptJS
    fprintf(puntafileHTML,"<SCRIPT type=\"text/javascript\">\nfunction changeTextarea(sel){var f = document.frm;f.value = sel.options[sel.selectedIndex].value; ;area.value=f.value;}</SCRIPT>");
        
    fprintf(puntafileHTML,"</center></body>\n");
    fprintf(puntafileHTML,"</html>\n");
    
    fclose(puntafileHTML);
    return(EXIT_SUCCESS);
}

void replace(char* stringa, char vecchio, char nuovo){
    int i;
    for(i=0;i<strlen(stringa);i++){
        if(stringa[i]==vecchio)
            stringa[i]=nuovo;
  }
}
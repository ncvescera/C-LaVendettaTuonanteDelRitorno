#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRLENRUOLO 30
#define MAXSTRLEN 200

struct s_dati{
    char studente[MAXSTRLENRUOLO+1];
    int lunghezza;
};
typedef struct s_dati dati;

struct s_record{
    char ruolo[MAXSTRLENRUOLO+1];
    dati elementi[MAXSTRLEN+1];
};
typedef struct s_record record;

void replace(char* stringa, char vecchio, char nuovo);

int main(){
    
    int i = 0;
    int k = 0;
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
        k = 0;
        while(!feof(puntafileTemp)){
            fscanf(puntafileTemp,"%s",array[i].elementi[k].studente);
            replace(array[i].elementi[k].studente,'+',' ');
            k++;
        }
        array[i].elementi[i].lunghezza = k;
        //replace(array[i].dati,'-','\n');
        fclose(puntafileTemp);
        cont --;
        i++;
    }
    /*
    int j;
    cont = i;
    for(i=0;i<cont;i++){
        k = array[i].elementi[i].lunghezza;
        j = 0;
        while(k){
            printf("%s\n",array[i].elementi[j].studente);
            k--;
            j++;
        }
        
    }*/
    int j;
     
    FILE *puntafileHTML;
    puntafileHTML = fopen("index.html","w");
    
    fprintf(puntafileHTML,"<html>\n");
    fprintf(puntafileHTML,"<head><title>LaPaginaPseudodinamica</title></head>");
    fprintf(puntafileHTML,"<body>\n");
    //form
    fprintf(puntafileHTML,"<center><form name=\"frm\">\n<h1>Seleziona il campo da stampare</h1><br>\n<table><tr><td width=\"320px\">\n<select id=\"select\" name=\"sel\" class=\"form-control\" style=\"width:373px;\" autofocus onchange=\"printNames()\">\n\t<option value=\"\"  selected=\"selected\">Seleziona</option>\n");
    
    //scrive le varie option 
    cont = i;
    for(i=0;i<cont;i++){
        fprintf(puntafileHTML,"\t<option value=\'[");
        k = array[i].elementi[i].lunghezza;
        j = 0;
        while(k-2){
            fprintf(puntafileHTML,"\"%s\",",array[i].elementi[j].studente);
            k--;
            j++;
        }
        fprintf(puntafileHTML,"\"%s\"",array[i].elementi[j].studente);
        fprintf(puntafileHTML,"]\'>%s</option>\n",array[i].ruolo);
    }
    fprintf(puntafileHTML,"</select>\n</td>\n</tr>\n</table>\n</form> ");
    
    //scriptJS
    fprintf(puntafileHTML,"<SCRIPT type=\"text/javascript\">\nfunction printNames(){\nvar e = document.getElementById(\'select\');\nvar array = JSON.parse(e.options[e.selectedIndex].value);\nvar ruolo = e.options[e.selectedIndex].text;\narray = array.sort();\nvar i = 0;document.getElementById(\'prova\').innerHTML = \"\";\ndocument.getElementById(\'prova\').innerHTML=\"<h1>\"+ruolo+\"</h1>\";\nfor(i=0;i<array.length;i++){document.getElementById(\'prova\').innerHTML += array[i]+\"<br>\";}\n}\n</SCRIPT>\n");
    fprintf(puntafileHTML,"<div id=\"prova\"></div></center>"); 
    fprintf(puntafileHTML,"</body>\n");
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

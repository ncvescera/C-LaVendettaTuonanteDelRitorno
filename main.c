#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRLEN 30


struct s_record{
    char ruolo[MAXSTRLEN+1];
    char persona[MAXSTRLEN+1];
};
typedef struct s_record record;

void replace(char* stringa, char vecchio, char nuovo);
void ordinaDati(record *dato, int dim);

int main(){
    
    int i = 0;
    //int k = 0; in caso di necessità
    int cont;
    char temp[MAXSTRLEN];
    record *array;
    FILE *puntafileDati;
    
    puntafileDati = fopen("dati.txt","r");
    while(!feof(puntafileDati)){
        fgets(temp,MAXSTRLEN+1,puntafileDati); //legge riga per riga e conta le righe
        i++;
    }
    
    array = (record*)malloc(i*sizeof(record)); //dichiaro l'arrey dinamico di record
    
    fseek(puntafileDati,0,SEEK_SET); //si scosta di 0 pisizioni dall'inizio del file (SEEK_SET è l'inizio del file)
    
    i=0;
    while(!feof(puntafileDati)){
        fscanf(puntafileDati,"%[^-]-%s\n",array[i].persona,array[i].ruolo); //scanset: divide la stringa in 2 parti, la parte prima del - la mette in persona 
        replace(array[i].persona,'+',' ');                                  //e quella dopo in ruolo
        i++;
    }
    cont = i;
    
    ordinaDati(array,cont);
    
    /* in caso di necessità
    for(i=0;i<cont;i++){
        printf("%s-%s\n",array[i].persona,array[i].ruolo);
    }
    */
     
    FILE *puntafileHTML;
    puntafileHTML = fopen("index.html","w");
    
    fprintf(puntafileHTML,"<html>\n");
    fprintf(puntafileHTML,"<head>\n\t<title>LaPaginaPseudodinamica</title></head>\n");
    fprintf(puntafileHTML,"<body>\n");
    
    //form
    fprintf(puntafileHTML,"<center>\n"
                          "\t<h1>Seleziona il campo da stampare</h1><br>\n"
                          "\t<table>\n\t\t<tr>\n\t\t<td width=\"320px\">\n"
                          "\t\t\t<select id=\"select\" name=\"sel\" class=\"form-control\" style=\"width:373px;\" autofocus onchange=\"printNames()\">\n"
                          "\t\t\t\t<option value=\"\"  selected=\"selected\">Seleziona</option>\n");
    
    //scrive le varie option 
    cont = i;
    i=0;
    fprintf(puntafileHTML,"\t\t\t\t<option value=\'[");
    fprintf(puntafileHTML,"\"%s\"",array[i].persona);
    for(i=1;i<cont;i++){
        if(strcmp(array[i-1].ruolo,array[i].ruolo)!=0){
            fprintf(puntafileHTML,"]\'>%s</option>\n",array[i-1].ruolo);
            fprintf(puntafileHTML,"\t\t\t\t<option value=\'[");
        }
        if(strcmp(array[i-1].ruolo,array[i].ruolo)!=0)
        fprintf(puntafileHTML,"\"%s\"",array[i].persona);

        else
        fprintf(puntafileHTML,",\"%s\"",array[i].persona);    
    }
    
    fprintf(puntafileHTML,"]\'>%s</option>\n",array[i-1].ruolo);
    fprintf(puntafileHTML,"\t\t\t</select>\n\t\t</td>\n\t\t</tr>\n\t</table>\n");
    
    //scriptJS
    fprintf(puntafileHTML,"<SCRIPT type=\"text/javascript\">\n"
                          "function printNames(){\n"
                          "var e = document.getElementById(\'select\');\n"
                          "var array = JSON.parse(e.options[e.selectedIndex].value);\n"
                          "var ruolo = e.options[e.selectedIndex].text;\n"
                          "array = array.sort();\n"
                          "var i = 0;document.getElementById(\'prova\').innerHTML = \"\";\n"
                          "document.getElementById(\'prova\').innerHTML=\"<h2>\"+ruolo+\"</h2>\";\n"
                          "for(i=0;i<array.length;i++){document.getElementById(\'prova\').innerHTML += array[i]+\"<br>\";}\n}\n"
                          "</SCRIPT>\n");
    fprintf(puntafileHTML,"\t<div id=\"prova\"></div>\n</center>\n"); 
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
void ordinaDati(record *dato, int dim){
    int i,j;
    record temp;
    
    for(i=0;i<dim-1;i++){
        for(j=0;j<dim-1;j++){
            if((strcmp(dato[j].ruolo,dato[j+1].ruolo)) > 0){
                temp=dato[j];
                dato[j]=dato[j+1];
                dato[j+1]=temp;
            }
        }
    }
}
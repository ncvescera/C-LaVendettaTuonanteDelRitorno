#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRLENRUOLO 30
#define MAXSTRLEN 20

struct s_dati{
    char studente[MAXSTRLENRUOLO+1];
    int lunghezza;
};
typedef struct s_dati dati;

struct s_record{
    char ruolo[MAXSTRLENRUOLO+1];
    dati elementi[MAXSTRLEN+1];
    char persona[MAXSTRLEN+1];
};
typedef struct s_record record;

void replace(char* stringa, char vecchio, char nuovo);
void ordinaDati(record *dato, int dim);

int main(){
    
    int i = 0;
    int k = 0;
    int cont;
    char temp[MAXSTRLEN];
    record *array;
    FILE *puntafileDati;
    FILE *puntafileTemp;
    
    puntafileDati = fopen("dati.txt","r");
    while(!feof(puntafileDati)){
        fgets(temp,MAXSTRLENRUOLO+1,puntafileDati); //legge riga per riga e conta le righe
        i++;
    }
    
    array = (record*)malloc(i*sizeof(record)); //dichiaro l'arrey dinamico di record
    
    fseek(puntafileDati,0,SEEK_SET); //si scosta di 0 pisizioni dall'inizio del file (SEEK_SET è l'inizio del file)
    
    i=0;
    while(!feof(puntafileDati)){
        fscanf(puntafileDati,"%[^-]-%s\n",array[i].persona,array[i].ruolo);
        replace(array[i].persona,'+',' ');
        i++;
    }
    cont = i;
    k = i;
    ordinaDati(array,cont);
    
    for(i=0;i<cont;i++){
        printf("%s-%s\n",array[i].persona,array[i].ruolo);
    }
    
    
    /*i = 0;
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
    fprintf(puntafileHTML,"<center>"
                          "<form name=\"frm\">\n"
                          "<h1>Seleziona il campo da stampare</h1><br>\n"
                          "<table><tr><td width=\"320px\">\n"
                          "<select id=\"select\" name=\"sel\" class=\"form-control\" style=\"width:373px;\" autofocus onchange=\"printNames()\">\n"
                          "\t<option value=\"\"  selected=\"selected\">Seleziona</option>\n");
    
    //scrive le varie option 
    cont = k;
    j=0;
    i=0;
    fprintf(puntafileHTML,"\t<option value=\'[");
    fprintf(puntafileHTML,"\"%s\",",array[i].persona);
    for(i=1;i<cont;i++){
        if(strcmp(array[i-1].ruolo,array[i].ruolo)!=0){
            fprintf(puntafileHTML,"]\'>%s</option>\n",array[i].ruolo);
            fprintf(puntafileHTML,"\t<option value=\'[");
        }
        //strcpy(temp,array[i].ruolo);
        //j=0;
        //while(strcmp(array[j].ruolo,array[j+1].ruolo)==0){
        fprintf(puntafileHTML,"\"%s\",",array[i].persona);
           // j++;
           
        //}
        
        //fprintf(puntafileHTML,"\"%s\"",array[i].persona);
       //if(strcmp(array[i].ruolo,array[i+1].ruolo)!=0)
            
        
    }
    fprintf(puntafileHTML,"]\'>%s</option>\n",array[i].ruolo);
    fprintf(puntafileHTML,"</select>\n</td>\n</tr>\n</table>\n</form> ");
    
    //scriptJS
    fprintf(puntafileHTML,"<SCRIPT type=\"text/javascript\">\n"
                          "function printNames(){\n"
                          "var e = document.getElementById(\'select\');\n"
                          "var array = JSON.parse(e.options[e.selectedIndex].value);\n"
                          "var ruolo = e.options[e.selectedIndex].text;\n"
                          "ruolo = ruolo.substring(0,ruolo.indexOf(\".\"));\n"
                          "array = array.sort();\n"
                          "var i = 0;document.getElementById(\'prova\').innerHTML = \"\";\n"
                          "document.getElementById(\'prova\').innerHTML=\"<h1>\"+ruolo+\"</h1>\";\n"
                          "for(i=0;i<array.length;i++){document.getElementById(\'prova\').innerHTML += array[i]+\"<br>\";}\n}\n"
                          "</SCRIPT>\n");
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
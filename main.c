#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRLEN 30

struct s_strings{
    char s[MAXSTRLEN+1];
    int lunghezza;
};
typedef struct s_strings strings;
struct s_record{
    char ruolo[MAXSTRLEN+1];
    char persona[MAXSTRLEN+1];
};
typedef struct s_record record;

void replace(char* stringa, char vecchio, char nuovo);
void ordinaDati(record *dato, int dim);

int main(){
    
    int k;
    int i = 0;
    int lenghtRuoli = 0; //in caso di necessità
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
    fprintf(puntafileHTML,"<head>\n\t<title>LaPaginaPseudodinamica</title>\n");
    fprintf(puntafileHTML,"<meta charset=\"UTF-8\">\n");
    fprintf(puntafileHTML,"<script src=\"Chart.js-master/Chart.min.js\"></script></head>\n");
    fprintf(puntafileHTML,"<body>\n");
    
    //select
    fprintf(puntafileHTML,"<center>\n"
                          "\t<h1>Seleziona il campo da stampare</h1><br>\n"
                          "\t<table>\n\t\t<tr>\n\t\t<td width=\"320px\">\n"
                          "\t\t\t<select id=\"select\" name=\"sel\" class=\"form-control\" style=\"width:373px;\" autofocus onchange=\"printNames()\">\n"
                          "\t\t\t\t<option value=\"\"  selected=\"selected\">Seleziona</option>\n");
    
    //scrive le varie option e conta i ruoli
    strings ruoli[cont];
    lenghtRuoli = 0;
    cont = i;
    i = 0;
    fprintf(puntafileHTML,"\t\t\t\t<option value=\'[");
    fprintf(puntafileHTML,"\"%s\"",array[i].persona);
    for(i=1;i<cont;i++){
        if(strcmp(array[i-1].ruolo,array[i].ruolo)!=0){
            fprintf(puntafileHTML,"]\'>%s</option>\n",array[i-1].ruolo);
            fprintf(puntafileHTML,"\t\t\t\t<option value=\'[");
            
            strcpy(ruoli[lenghtRuoli].s, array[i-1].ruolo);
            lenghtRuoli++;
            
        }
        if(strcmp(array[i-1].ruolo,array[i].ruolo)!=0)
        fprintf(puntafileHTML,"\"%s\"",array[i].persona);

        else
        fprintf(puntafileHTML,",\"%s\"",array[i].persona);    
    }
    
    fprintf(puntafileHTML,"]\'>%s</option>\n",array[i-1].ruolo);
    
    strcpy(ruoli[lenghtRuoli].s, array[i-1].ruolo);
    lenghtRuoli++;
    
    fprintf(puntafileHTML,"\t\t\t</select>\n"
                          "\t\t</td>\n"
                          "\n\t\t<td>\n"
                          "\t\t\t<button id=\"bottone\" type=\"button\" onclick=\"riduci()\">↑</button>\n"
                          "\t\t</td>\n"
                          "\t\t</tr>\n"
                          "\t</table>\n");
    
    //scriptJS-stampaDati
    fprintf(puntafileHTML,"<SCRIPT type=\"text/javascript\">\n"
                          "function printNames(){\n"
                          "var e = document.getElementById(\'select\');\n"
                          "var array = JSON.parse(e.options[e.selectedIndex].value);\n"
                          "var ruolo = e.options[e.selectedIndex].text;\n"
                          "array = array.sort();\n"
                          "var i = 0;document.getElementById(\'titolo\').innerHTML = \"\";\n"
                          "document.getElementById('nomi').innerHTML = \"\";\n"
                          "document.getElementById(\'titolo\').innerHTML=\"<h2>\"+ruolo+\"</h2>\";\n"
                          "for(i=0;i<array.length;i++){document.getElementById(\'nomi\').innerHTML += array[i]+\"<br>\";}\n}\n\n"
                          "function riduci(){\n"
                          "if(document.getElementById(\"nomi\").style.display == \"none\"){\n"
                          "document.getElementById(\"nomi\").style.display = \"block\";\n"
                          "document.getElementById(\"bottone\").textContent = \"↑\";\n"
                          "}\n"
                          "else {\n"
                          "document.getElementById(\"nomi\").style.display = \"none\";\n"
                          "document.getElementById(\"bottone\").textContent = \"↓\";}}\n"
                          "</SCRIPT>\n");
    
    //tabella ruoli-grafico
    fprintf(puntafileHTML,"\n<br>\n<table width=1500px>\n"
                          "\t\t<tr>\n"
                          "\t\t<td width=\"50%\" style=\"border-right: 1px solid black;padding-left:30em;\">\n"
                          "\t\t\t<div id=\"titolo\"></div>\n"
                          "\t\t\t<div id=\"nomi\"></div>\n"
                          "\t\t</td>\n"
                          "\t\t<td width=\"50%\" style=\"padding-left:4em;\">\n"
                          "\t\t\t<canvas id=\"barre\" width=\"500px\" height=\"400px\"></canvas>\n"
                          "\t\t</td>\n"
                          "\t\t</tr>\n"
                          "</table>\n");
    fprintf(puntafileHTML,"</center>\n"); 
    
    //scriptJS-crea grfico
    fprintf(puntafileHTML,"<script>\n"
                          "var datiSerie = {\n"
                          "labels : [");
    
    for(i=0;i<lenghtRuoli;i++)
        ruoli[i].lunghezza = 0; //lunghezza deve essere inizializzato a 0 dato che nella dichiarazione del record non posso mettere = 0;
    
    for(i=0;i<lenghtRuoli;i++){
        for(k=0;k<cont;k++){
            if((strcmp(ruoli[i].s,array[k].ruolo))==0) 
                ruoli[i].lunghezza ++;                  //conta quante persone appartengono ad un ruolo
        }
    }
    
    fprintf(puntafileHTML,"\"%s\"",ruoli[0].s);
    for(i=1;i<lenghtRuoli;i++){
        fprintf(puntafileHTML,",\"%s\"",ruoli[i].s);
    }
    fprintf(puntafileHTML,"],\n");
    
    fprintf(puntafileHTML,"datasets : [\n"
			  "{\n"
				"fillColor : \"rgba(220,0,220,0.5)\",\n"
				"strokeColor : \"rgba(220,0,220,0.8)\",\n"
				"highlightFill: \"rgba(220,0,220,0.75)\",\n"
				"highlightStroke: \"rgba(220,0,220,1)\",\n"
				"pointColor: \"rgba(220,0,220,.8)\",\n"
				"pointStrokeColor: \"#fff\",\n"
				"pointHighlightFill: \"#fff\",\n"
				"pointHighlightStroke: \"rgba((220,0,220,1)\",\n"
				"data : [");
    
    fprintf(puntafileHTML,"%d",ruoli[0].lunghezza);
    for(i=1;i<lenghtRuoli;i++)
        fprintf(puntafileHTML,",%d",ruoli[i].lunghezza);
    
    fprintf(puntafileHTML,"]\n");
    fprintf(puntafileHTML,"}\n");
    fprintf(puntafileHTML,"]\n");
    fprintf(puntafileHTML,"};\n");
    fprintf(puntafileHTML,"var barre = document.getElementById(\"barre\").getContext(\"2d\");\n"); // Accede all'elemento con id=barre 
    fprintf(puntafileHTML,"new Chart(barre).Bar(datiSerie);\n");   // Crea il grafico
    fprintf(puntafileHTML,"</script>\n");  
    
    fprintf(puntafileHTML,"</body>\n");
    fprintf(puntafileHTML,"</html>\n");
    
    fclose(puntafileDati);
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
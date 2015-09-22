//Proviamo a fare l'esercizio di Fiorucci!

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRLEN 30
#define N 2

struct s_studente{
    char nome[MAXSTRLEN+1];
    char cognome[MAXSTRLEN+1];
    int eta;
    char classe[MAXSTRLEN+1];
};
typedef struct s_studente studente;

void popola(studente elenco[], int n){ //potrebbe essere migliorata aggiungendo i parametri #file-name# e #method#
    FILE *puntafile;
    int i;
    
    for(i=0;i<n;i++){
        printf("nome:");
        scanf("%s",elenco[i].nome);
        printf("cognome:");
        scanf("%s",elenco[i].cognome);
        printf("eta:");
        scanf("%d",&(elenco[i].eta));
        printf("classe:");
        scanf("%s",elenco[i].classe);
    }
    
    puntafile=fopen("dati.dat","wb");
    i=0;
    fwrite(elenco,sizeof(studente),n,puntafile);
    fclose(puntafile);
    
    printf("\n\n\n");
}

int main(int argc, char** argv) {
    FILE *puntafile;
    studente elenco[N];
    int i;
    int quantoLetto;
    
   
    popola(elenco,N);
    
    
    puntafile=fopen("dati.dat","rb");
    
    while(!feof(puntafile)){
        quantoLetto=fread(elenco,sizeof(studente),1,puntafile);
        for(i=0;i<quantoLetto;i++){
            printf("Nome: %s\n",elenco[i].nome);
            printf("Cognome: %s\n",elenco[i].cognome);
            printf("Età: %d\n",elenco[i].eta);
            printf("Classe: %s\n",elenco[i].classe);

         } //ora fnziona, il file è anche leggermente criptato. L'output è corretto. 
    }
    
    /*
    //for(newI=0;newI<i;newI++){
        
        
    //}
    /*studente elenco;

    char *rif; //potrebbe essere tile per poter capire quando è l'eof per evitare di scrivere 2 volte l'ultimo carattere 
    //sicuramente c'è un modo migliore che si può attuare qprendo il file in rb, prima va scritto il file .dat
   
    puntafile = fopen("dati.txt","r");
   
 
        rif=fgets(elenco.nome,MAXSTRLEN+1,puntafile);
        rif=fgets(elenco.cognome,MAXSTRLEN+1,puntafile);
        rif=fgets(elenco.eta,MAXSTRLEN+1,puntafile);
        rif=fgets(elenco.classe,MAXSTRLEN+1,puntafile);
        //printf("%c",rif);
   
    
    printf("Nome: %s",elenco.nome);
    printf("Cognome: %s",elenco.cognome);
    printf("Età: %s",elenco.eta);
    printf("Classe: %s",elenco.classe);*/ 
    
    return (EXIT_SUCCESS);
}


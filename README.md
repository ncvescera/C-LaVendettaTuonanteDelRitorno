# C-LaVendettaTuonanteDelRitorno
Questo codice C preleva i dati dal file dati.txt, li ordina per ruolo, li formatta in JSON, crea una pagina html che popola con una select al cui interno saranno presenti i dati in formato Json. L'utente potrà selezionare uno trai i vari ruoli presenti nella select e uno script JS prenderà i dati relativi al campo selezionato per poi ordinarli e stamparli a video.
## Procedimento
* Viene aperto il file dati.txt
* Si scorre il file per vedere il numero di righe che poi verrà slvato nella variabile cont
* Vene generato un vettore dinamico in base al numero di righe perchè ogni posizione del vettore conerrà una riga
* Ogni posizione del vettore contiene un record di 2 stringhe: Ruolo e Persona
* Si torna in cima al file per leggerlo nuovamente e memorizzare le righe in ogni cella dell'array precedentemente creato
* L'arrey viene ordinato in base al ruolo per poter popolare la select più facilmente
* Viene creato il file index.html, al cui interno si scrivono i soliti tag html
* Vengono formattati i dati del vettore in Json e poi scritti all'interno della select
* Chiusura del file index.html
* FINE

## Principali difficoltà
* Formattare i dati in Json (Maledette virgole !)
* Utilizzare JS nel modo corretto
* Utilizzare l'array di record nel modo giusto per poter stampare le option

## Perchè solo 2 funzioni ?
Non ritengo utile creare delle funzioni per poter stampare una pecifica pagina html su file o uno script JS, quindi le uniche 2 fnzioni veramente utili che si possono utilizzare sono:
* `void ordinaDati(record *dato, int dim)` che può essere riadattata per ogni tipo di dato
* `void replace(char* stringa, char vecchio, char nuovo)` anchessa riadattabile per tutte le stringhe



#!/usr/bin/python

come = raw_input("[0]Crea nuovo file\t [1]Modifica file gia' esistente\n>")
if come:
	method = "a"
else :
	method = "w"

stringa = raw_input("Inserisci il nome del file da creare (cone estensione): ")
#print stringa
ruoli = open("ruoli.txt","a")
ruoli.write(stringa)
ruoli.close
myfile = open(stringa,method)
formattazione = raw_input("Che formato vuoi?\n[c]Formattazione C \t [py]Formattazione Pthon\n> ")
if formattazione == "c":
	aCapo = "<br>"
else:
	aCapo = "-"
inserito = " "
while inserito != "exit":
	inserito = raw_input("Inserisci nome (exit per terminare): ")
	if inserito != "exit":
		cognome = raw_input("Inserisci cognome: ")
		myfile.write(inserito+"+"+cognome+aCapo)
print "Operazione Terminata!"
myfile.close

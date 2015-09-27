#!/usr/bin/python


stringa = raw_input("Inserisci il nome del file da creare (cone estensione): ")
#print stringa
myfile = open(stringa,"w")
formattazione = raw_input("Che formato vuoi?\n[c]Formattazione C \t [py] Formattazione Pthon\n> ")
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

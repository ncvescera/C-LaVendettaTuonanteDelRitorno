#!/usr/bin/python
import cgi

output = ""
form = cgi.FieldStorage()
ruolo = form.getvalue('ruolo')

if ruolo == "studente":
	myfile = open("studente.txt","r")

if ruolo == "docente":
	myfile = open("docente.txt","r")
	
output = myfile.read()

myfile.close

print "Content-type:text/html\r\n\r\n"
print "<html>"
print "<body>"
print "<center><h1>"+ruolo+"</h1>"
print output.replace("-","<br>").replace("+","\t")
print "</center></body>"
print "</html>"

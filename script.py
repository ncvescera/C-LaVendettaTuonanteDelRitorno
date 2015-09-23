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

print "Content-type:text/html\r\n\r\n"
print "<html>"
print "<body>"
print "<h1>"+ruolo+"</h1>"
print output.replace("-","<br>").replace("+","\t")
print "</body>"
print "</html>"

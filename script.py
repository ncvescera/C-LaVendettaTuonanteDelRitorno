#!/usr/bin/python
import webbrowser
new = 2 # open in a new tab, if possible 

print "Sto operando ..."
print "Genero file index.html ..."
myfileHTML = open("index.html","w")
myfileDirigente = open("dirigente.txt","r")
myfileDocente = open("docente.txt","r")
myfileStudente = open("studente.txt","r")

print "Popolo il file index.html ..."
myfileHTML.write("<html>")
myfileHTML.write("<head><title>LaPaginaPseudoDinamica</title></head>")
myfileHTML.write("<body>")

dirigente = myfileDirigente.read() 
docente = myfileDocente.read()
studente = myfileStudente.read()


myfileHTML.write("<form name=\"frm\"><center><h1>Seleziona il campo da stampare</h1><br><table><tr><td width=\"320px\"><select name=\"sel\" class=\"form-control\" style=\"width:300px;\" onchange=\"aggiornaHidden(this)\"><option value=\"\"  selected=\"selected\">Seleziona</option><option value=\""+"<h1>Docente</h1>"+docente.replace("+","\t").replace("-","<br>")+"\">Docente</option><option value=\""+"<h1>Dirigente</h1>"+dirigente.replace("+","\t").replace("-","<br>")+"\">Dirigente</option><option value=\""+"<h1>Studente</h1>"+studente.replace("+","\t").replace("-","<br>")+"\">Studente</option></select></td><td></td></tr></table></form>")

myfileHTML.write("<SCRIPT type=\"text/javascript\">\nfunction aggiornaHidden(sel){var f = document.frm;f.value = sel.options[sel.selectedIndex].value; ; document.write(\"<center>\"+f.value+\"</center>\");}</SCRIPT>")

myfileHTML.write("</center></body>")
myfileHTML.write("</html>")

print "Operazione Terminata\n"

myfileHTML.close
myfileDocente.close
myfileDirigente.close
myfileStudente.close

#url = "file:///root/Documenti/C-LaVendettaTuonanteDelRitorno/index.html"
url = "index.html"
webbrowser.open(url,new=new)

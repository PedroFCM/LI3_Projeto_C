
#Compilar/criar pdf
latex:
	pdflatex Report_LI3.tex

#Open pdf
open:
	mkdir tmp
	mv Report_LI3.aux Report_LI3.log Report_LI3.out tmp/
	xdg-open Report_LI3.pdf

images:
	mkdir images
	mv *.png images/

#Clear log files
clean:
	rm Report_LI3.pdf
	rm -r tmp
run: test

test: test.cpp
	g++ test.cpp -o test -O2

report: report.pdf

report.pdf: report.tex
	xelatex report.tex
	rm report.aux report.log

clean:
	rm test report.pdf

.PHONY: run report clean
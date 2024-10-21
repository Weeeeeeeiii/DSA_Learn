ALL:
	g++ List.cpp -o List -std=c++20 -O2

report:
	xelatex report.tex
	rm report.aux report.log

clean:
	rm -f report.aux report.log List

.PHONY: ALL report

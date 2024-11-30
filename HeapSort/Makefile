test: test.cpp HeapSort
	g++ test.cpp -o test -std=c++20 -O2

report: report.pdf

report.pdf: report.tex
	xelatex report.tex
	rm report.aux report.log

clean:
	rm main test report.pdf

.PHONY: report clean
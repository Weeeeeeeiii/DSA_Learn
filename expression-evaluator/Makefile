main: main.cc expression_evaluator.h infix_to_postfix.h
	g++ main.cc -o main -O2 -std=c++20

test: test.cc expression_evaluator.h infix_to_postfix.h
	g++ test.cc -o test -O2 -std=c++20

report: report.pdf

report.pdf: report.tex
	xelatex report.tex
	rm report.aux report.log

clean:
	rm main test report.pdf

.PHONY: report clean
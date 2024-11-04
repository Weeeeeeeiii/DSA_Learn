ALL: run report

run:
	g++ test_BST.cpp -o test_BST -std=c++20 -O2

report:
	xelatex report.tex
	rm report.aux report.log

clean:
	rm -f report.aux report.log List report.pdf test_BST

.PHONY: ALL report run

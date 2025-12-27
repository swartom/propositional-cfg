##
# Propositional DCFG
#
# @file prop.c
# @version 0.1

run:
	gcc -lm prop.c -o prop
	./prop > test.txt
	python visualiser.py
PHONY: run

# end

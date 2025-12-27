##
# Propositional DCFG
#
# @file prop.c
# @version 0.1

run:
	gcc -lm prop.c -o prop
	./prop > test.txt

PHONY: run

# end

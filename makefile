.PHONY: .DEFAULT_GOAL
.DEFAULT_GOAL: task1

task1: stree.c
	gcc -o stree stree.c 




.PHONY: clean
clean: 
	-rm stree

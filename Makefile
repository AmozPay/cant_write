.PHONY:	all


all:
	gcc -o cant_write main.c
	mv cant_write ~/.cant_write
	echo "~/.cant_write" >> ~/.zshrc
	echo "~/.cant_write" >> ~/.bashrc

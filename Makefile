
all:
	gcc main.c utils/*.c modules/*.c db/*.c -o PolDep.exe

debug:
	gcc -g main.c utils/*.c modules/*.c db/*.c -o PolDep.exe --all-warnings
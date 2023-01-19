CC = gcc 
CFLAGS = -Wall -Werror -Wextra 

sshell: sshell.o
	$(CC) -o sshell $(CFLAGS) sshell.o 

sshell.o: sshell.c
	$(CC) $(CFLAGS) -c sshell.c

clean:
	rm -f *.o sshell *.out
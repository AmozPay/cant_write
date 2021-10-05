#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <signal.h>


int stuck = 1;

void sighandler(int signo)
{
   if (signo == SIGINT)
   	printf("\nDon't try to escape!!! >:)\n");
   else if (signo == SIGTSTP) {
      printf("Congratulations, you made it!\n");
      printf("Now go edit your .zshrc and .bashrc and remove the last line.\n");
      printf("This message will self destruct in 15 seconds...\n");
      sleep(5);
      printf("This message will self destruct in 10 seconds...\n");
      sleep(5);
      printf("This message will self destruct in 5 seconds...\n");
      sleep(5);
      char *args[] = {"/usr/bin/clear", NULL};
      execv(args[0], args);
      stuck = 0;
   }
   return;
}

int main (int argc, char *argv[])
{
   char *message = "I love getting trolled\n"; //default message


   if (argc == 2) {
      message = argv[1]; // you can give your own custom message
   }
   int len = strlen(message);
   /* get terminal attributes */
   struct termios termios;
   tcgetattr(STDIN_FILENO, &termios); //get terminal attributes

   termios.c_lflag &= ~ECHO; // deactivate printing the char
   termios.c_lflag &= ~(ICANON); // deactivate need for \n
   tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios); //set terminal attributes

   signal(SIGINT, sighandler); // don't try to escape >:)
   signal(SIGTSTP, sighandler);
   /* read a char but write message instead */
   int c = 0;
   int i = 0;
   while (stuck) {
      c = getc(stdin);
      write(1, (message + i), 1);
      i = (i + 1) % len;
   }

   /* enable echo */
   termios.c_lflag &= ~ECHO;
   tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios);
   return 0;
}


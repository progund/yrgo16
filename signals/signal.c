#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

static int keep_working=1;

void sig_handler(int sig)
{
  int count;
  printf ("sig_handler (%d)\n", sig);

  switch (sig)
    {
    case SIGINT:
      printf ("SIGINT ....uh oh, will halt... soon\n");
      keep_working=0;
      for (count=0; count<10; count++)
        {
          printf (" wait some more"); fflush(stdout);
          usleep(1000*300);
        }
      printf ("SIGINT handled, will halt\n");
      break;
    case SIGUSR1:
      printf ("SIGUSR1 ....uh oh\n");
      break;
    case SIGSEGV:
      printf ("SIGSEGV ....seg fault\n");
      exit(1);
      break;
    case SIGUSR2:
      printf ("SIGUSR2 ....will read from crap mem\n");
      printf ("string at %d\n", 0x123);
      printf ("string at %s\n", (char*)0x123);
      break;
    default:
      printf ("another signal\n");
      break;
    }
}


int
main(void)
{

  printf ("Starting up.....\n");

  printf ("pid=%d\n", getpid());

  printf ("Setting up a signal handler\n");
  signal(SIGINT, sig_handler);
  signal(SIGUSR1, sig_handler);
  signal(SIGUSR2, sig_handler);
  signal(SIGSEGV, sig_handler);

  while (keep_working)
    {
      printf (".");
      fflush(stdout);
      usleep(1000*1000);
    }
  
  printf ("Go die fucker!\n");
  exit(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main( void )
  {
    sigset_t set, oset, pset;

    sigemptyset( &set );
    sigaddset( &set, SIGINT );
    sigprocmask( SIG_BLOCK, &set, &oset );
    printf( "Old set was %8.8ld.\n", oset );
    printf( "Old set was %8.8ld.\n", set );

    sigpending( &pset );
    printf( "Pending set is %8.8ld.\n", pset );

    kill( getpid(), SIGINT );

    sigpending( &pset );
    printf( "Pending set is %8.8ld.\n", pset );

    sigprocmask( SIG_SETMASK, &set, &oset );
    printf( "Pending set is %8.8ld.\n", set );

    /* The program terminates with a SIGINT */
    return( EXIT_SUCCESS );
  }
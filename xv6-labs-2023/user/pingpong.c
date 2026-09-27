#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// Use pipe to create a pipe.
// Use fork to create a child.
// Use read to read from a pipe, and write to write to a pipe.
// Use getpid to find the process ID of the calling process.
// User programs on xv6 have a limited set of library functions available to them. You can see the list in user/user.h; the source (other than for system calls) is in user/ulib.c, user/printf.c, and user/umalloc.c.


int
main(int argc, char *argv[])
{
  int p2c[2];
  int c2p[2];
  char buf[1];

  // creates an pipe for parent to child 
  
  // pipe for child to parent
  pipe(p2c);
  pipe(c2p);
  int pid = fork(); // create child process and return child ID
  if (pid == 0) {
    // Child reads from pipe
    close(p2c[1]);
    if(read(p2c[0], buf, 1) > 1) {
      fprintf(2, "child: failed to received ping\n");
      exit(1);
    }
    close(p2c[0]);

    fprintf(1, "%d: received ping\n", getpid());

    // child write to pipe
    close(c2p[0]);
    if(write(c2p[0], buf, 1) > 1) {
      fprintf(2, "child: failed to write\n");
      exit(1);
    }
    close(c2p[1]);

    exit(0);
  } else {
    // parent write to pipe
    close(p2c[0]); // close the reads show the parent can write to 1
    
    if(write(p2c[1], "x", 1) > 1) {
      fprintf(2, "parent: failed to write to pipe\n");
      exit(1);
    }
    close(p2c[1]);

    // parent read from pipe
    close(c2p[1]);
    if (read(c2p[0], buf, 1) > 1) {
      fprintf(2, "parent: failed to read ping\n");
      exit(1);
    }
    fprintf(1, "%d: received pong\n", getpid());

    close(c2p[0]);

    wait(0);
    exit(0);
  }



}

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
  int p[2];
  const int BSIZE = 4;
  char buf[BSIZE];

  // creates an pipe for parent to child 
  
  // pipe for child to parent
  pipe(p);
  int pid = fork(); // create child process and return child ID
  if (pid == 0) {
    // Child reads from pipe
    close(p[1]);
    read(p[0], buf, BSIZE);
    fprintf(2, "%d: received ping\n", getpid());
    close(p[0]);
  } else {
    // parent write to pipe
    close(p[0]); // close the reads show the parent can write to 1
    write(p[1], "A", 16);
    close(p[1]);
    wait(0);
  }

  int np[2];
  char nbuf[16];
  pipe(np);

  if (pid == 0) {
    //child write to pipe
    close(np[0]);
    write(np[1], "A", 16);
    close(np[1]);
    wait(0);
  } else {
    //parent read from pipe
    close(np[0]);
    read(np[0], nbuf, 16);
    fprintf(2, "%d: received pong\n", getpid());
    close(np[0]);
  }
  exit(0);

}

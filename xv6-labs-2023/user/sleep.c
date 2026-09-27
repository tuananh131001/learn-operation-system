#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  // If user forget putting argumen t  user got error
  // argv is put as string , use atoi to convert (see user/ulib.c).
  //
  if(argc == 1) {
    fprintf(2, "Usage: sleep <number>...\n");
    exit(1);
  }
  int sleepTime = atoi(argv[1]);

  sleep(sleepTime);

  exit(0);

}

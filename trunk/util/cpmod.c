#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
  struct stat st;

  if (argc != 3)
    {
      fprintf(stderr, "usage: %s reference target\n", argv[0]);
      exit(1);
    }
  if (stat(argv[1], &st))
    {
      perror(argv[1]);
      exit(1);
    }
  if (chmod(argv[2], st.st_mode))
    {
      perror(argv[2]);
      exit(1);
    }
  return 0;
}


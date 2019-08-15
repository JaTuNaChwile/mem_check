#include <stdlib.h>

#define _GNU_SOURCE
#include <lib_mem_check.h>


int main(void)
{

  int * a = malloc(4*4);
  char * str = calloc(0, 16);
  
  a = realloc((void *)a, 4);
  a = realloc((void *)a, 0);

  int * b = malloc(4*4);

  free(b);

  return 0;
}

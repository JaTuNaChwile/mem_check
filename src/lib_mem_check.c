#include <lib_mem_check.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef LIB_MEM_CHECK
#define LIB_MEM_CHECK


// undefining 
#undef malloc
#undef calloc
#undef realloc
#undef free


#define DEFAULT_MEMORY_CALLS 2048
/*******************************************************************************
 * Utility data structures
 ******************************************************************************/
typedef struct
{
  void * ptr;
  char * func_name;
  unsigned long line;
  char * filename;

} mem_node;


mem_node memory_[DEFAULT_MEMORY_CALLS] = {0};
unsigned long mem_idx = 0;


/*******************************************************************************
 * Utility functions
 ******************************************************************************/

void mem_scanner(void) __attribute__((destructor));

void record_mem(const char * file, const unsigned long line, const char * func)
{
  memory_[mem_idx].filename = (char *) file;
  memory_[mem_idx].line = (unsigned long) line;
  memory_[mem_idx].func_name = (char *) func;
  mem_idx++;
}


void mem_scanner(void)
{
  for(size_t i = 0; i<DEFAULT_MEMORY_CALLS; i++)
  {
    if(memory_[i].ptr != NULL)
    {
      fprintf(stderr, "mem_check: Memory at address 0x%p was not free'd. At"
      " file %s:%ld in function %s\n", memory_[i].ptr, memory_[i].filename,
      memory_[i].line, memory_[i].func_name);
    }
  }

}

/*******************************************************************************
 * Mem function replacements
 * ****************************************************************************/
void *malloc_replacer(size_t size)
{
  void * addr = NULL;

  addr = malloc(size);

  memory_[mem_idx].ptr = addr;

  return addr;
}


void free_replacer(void *ptr)
{
  unsigned int idx_ = 0;

  for(size_t i = 0; i<DEFAULT_MEMORY_CALLS; i++)
  {
    if(memory_[i].ptr == ptr)
    {
      free(ptr);
      memset(&memory_[i], 0, sizeof(mem_node));
      break;
    }
  }
}


void *calloc_replacer(size_t nmemb, size_t size);
void *realloc_replacer(void *ptr, size_t size);

#ifdef _GNU_SOURCE
void *reallocarray_replacer(void *ptr, size_t nmemb, size_t size);
#endif


#endif
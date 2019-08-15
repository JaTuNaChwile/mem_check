/******************************************************************************
 * @author Patryk "JaTuNaChwile" Gawroński
 * @license GNU GPL 3.0
 * 
*******************************************************************************/
#include <stdlib.h>



/*******************************************************************************
 * Utility functions
 ******************************************************************************/
void record_mem(const char * file, const unsigned long line, const char * func);


/*******************************************************************************
 * Mem function replacements
 * ****************************************************************************/
void *malloc_replacer(size_t size);
void free_replacer(void *ptr);
void *calloc_replacer(size_t nmemb, size_t size);
void *realloc_replacer(void *ptr, size_t size);

#ifdef _GNU_SOURCE
void *reallocarray_replacer(void *ptr, size_t nmemb, size_t size);
#endif


#define malloc(size) malloc_replacer(size); record_mem(__FILE__, __LINE__, __func__)
#define free(ptr) free_replacer(ptr); record_mem(__FILE__, __LINE__, __func__)
#define calloc(nmemb, size) calloc_replacer(nmemb, size); record_mem(__FILE__, __LINE__, __func__)
#define realloc(ptr, size)  realloc_replacer(ptr, size); record_mem(__FILE__, __LINE__, __func__)

#ifdef _GNU_SOURCE
#define rellococarray(ptr, nmemb, size) reallocarray_replacer(ptr, nmemb, size);
#endif

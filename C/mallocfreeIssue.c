
/*
 Recently joined to a new project to fix some core dump issue. There are some typical coding issues that I recorded in here.

 During troubleshooting for our project, I found a core dump that occurred in calling free() duplicated. 
 Because malloc(), first free() and second free() were distributed in different functions or source files, so it was hard to figure out the bug.
 The source code style is same as the malloc_free_bad().
  
 malloc_free_work() can work, after the first free(), we should reset the pointer to NULL. 
                    at this case, when we do duplicated free(), it won't cause core dump.
 
 malloc_free_good() good style, we should:
                   1) check the malloc() return value. 
                   2) before call free(), we should check pointer value.

 Reference from cplusplus.com:
   void* malloc (size_t size); //  Allocate memory block
    Allocates a block of size bytes of memory, returning a pointer to the beginning of the block.
    The content of the newly allocated block of memory is not initialized, remaining with indeterminate values.
    If size is zero, the return value depends on the particular library implementation (it may or may not be a null pointer), 
      but the returned pointer shall not be dereferenced.

  void free (void* ptr);  //  Deallocate memory block
    A block of memory previously allocated by a call to malloc, calloc or realloc is deallocated, making it available again for further allocations.
    If ptr does not point to a block of memory allocated with the above functions, it causes undefined behavior.
    If ptr is a null pointer, the function does nothing.
    Notice that this function does not change the value of ptr itself, hence it still points to the same (now invalid) location.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void malloc_free_bad()
{
    char *p;

    p = (char*) malloc(128);
    strcpy(p, "hello world !");

    free(p);

    // duplicated free, will cause core dump.
    free(p);
}

void malloc_free_work()
{
    char *p;

    p = (char*) malloc(128);
    strcpy(p, "hello world !");
    printf("%s\n", p);

    free(p);
    p = NULL;

    // duplicated free, because p has reset to NULL, won't cause core dump.
    free(p);
}

void malloc_free_good()
{
    char *p=NULL;

    if ((p = (char*) malloc(128)) == NULL) {
        return;
    }
    strcpy(p, "welcome to the C world !");
    printf("%s\n", p);

    if (p) {
        free(p);
        p = NULL;
    }

    // duplicated free, check the p value, if NULL, won't do duplicated free.
    if (p) {
        free(p);
        p = NULL;
    }
}

int main()
{
//    malloc_free_bad();
    malloc_free_work();
    malloc_free_good();
}



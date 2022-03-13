/*
 Recently joined to a new project to fix some core dump issue. There are some typical coding issues that I recorded in here.  

 During troubleshooting, found a core dump was hit in va_arg():
   detail can see the comments in myCat_old_version().

 I checked the va_start() / va_arg() / va_end() from cplusplus.com
   
   void va_start (va_list ap, paramN); 
        Initialize a variable argument list,Initializes ap to retrieve the additional arguments after parameter paramN.
        A function that invokes va_start, shall also invoke va_end before it returns.
        Parameters
            ap -  Uninitialized object of type va_list.
                After the call, it carries the information needed to retrieve the additional arguments using va_arg.
                If ap has already been passed as first argument to a previous call to va_start or va_copy, it shall be passed to va_end before calling this function.
            paramN - Name of the last named parameter in the function definition. The arguments extracted by subsequent calls to va_arg are those after paramN.
        Note: C
            The parameter shall not be a parameter declared with register storage class, with function or array type, or with a type that is not compatible with the type that results after application of the default argument promotions.

    type va_arg (va_list ap, type)
        Retrieve next argument
        This macro expands to an expression of type type with the value of the current argument in the variable arguments list identified by ap.
        Each call to this macro modifies the state of ap so that the next call to this macro will expand to the argument that follows the one it evaluates to.
        Notice that va_arg cannot determine the actual type of the argument passed to the function, but uses whatever type is passed as the type macro argument as its type.

 Note 1:
   In C/C++, the arguments' sequence of in stack are from right to left.

 I changed the function to myCat_new_version_1() and myCat_new_version_2(), both are working well in Linux.
 Note 2:
    Make sure the length of s1 is enough!
*/
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

// Function: combine all of the arguments(sub string) into a whole a string then return the string.
char* myCat_old_version(char *, ...)
{
    va_list  arglist;
    char *to;
    char *dest;
    char *from;

//    va_start(arglist, from);      // Error 1: from isn't initialisted.    
    to = dest = va_arg(arglist, char*);  // Error 2: dest is not used in this function.

    while ((from = va_arg(arglist, char*)) != (char*)0) {
        to += sprintf(to, "%s", from); 
    }

    va_end(arglist);

    return (to);    // Error 3: after the while loop, the "to" is NOT the first index (NOT the string address).
}

char* myCat_new_version_1(char *s1, ...)
{
    va_list  arglist;

    char *to;
    char *from;

    to = s1;
    to += strlen(s1);

    va_start(arglist, s1);
    while ((from = va_arg(arglist, char*)) != NULL) {
        to += sprintf(to, "%s", from); 
    }

    va_end(arglist);

    return (s1); 
}

char* myCat_new_version_2(char *s1, ...)
{
    va_list  arglist;

    char *to;
    char *from;

    to = s1;

    va_start(arglist, s1);      // point to first argument, also it is last one in stack.    
    while ((from = va_arg(arglist, char*)) != NULL) {
        sprintf(to, "%s%s", to, from); 
    }

    va_end(arglist);

    return (s1);    // return the s1's address.
}

int main()
{
    {
        char s1[32] = "hello";
        char s2[] = " ";
        char s3[] = "world";

        myCat_new_version_1(s1, s2, s3);
        printf("result = %s", s1);
    }

    {
        char s1[32] = "Good";
        char s2[] = " ";
        char s3[] = "Morning, ";
        char s4[] = "Cindy.";

        myCat_new_version_2(s1, s2, s3, s4);
        printf("result = %s", s1);
    }

    return 0;
}





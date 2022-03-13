
/*
 Recently joined to a new project to fix some core dump issue. There are some typical coding issues that I recorded in here.
 
 During troubleshooting, found the password that used to connect to db-server are different in getenv() and in calling "connect the db-server".
 Used gdb to debug it, and found the password was defined as passwd[8], and in environment(.bash_profile) its value's lenght over 8.
 That is typical menory overflow issue.

 Reference from cplusplus.com:
    char * strcpy ( char * destination, const char * source );
        Copies the C string pointed by source into the array pointed by destination, including the terminating null character (and stopping at that point).
        To avoid overflows, the size of the array pointed by destination shall be long enough to contain the same C string as source 
           (including the terminating null character), and should not overlap in memory with source.
    Parameters
        destination
            Pointer to the destination array where the content is to be copied.
        source
            C string to be copied.
    Return Value
        destination is returned.  

 result / display:
    address: global_s1=00007ff66d05d055.
    address: global_s2=00007ff66d05d060.
    address:        s3=00007ff66d05d040.
    address:        s4=00007ff66d05d048.

    before overflow:
    global_s2[13]=aaaaaaaaaaaa.
    s4[13]       =bbbbbbbbbbbb.

    after overflow:
    global_s1[4] =123456789012.
    global_s2[13]=2.
    s3[2]        =ABCDEFGHIJK.
    s4[13]       =IJK.
*/

#include <stdio.h>
#include <string.h>


static char global_s1[4];
static char global_s2[13];

char s3[2];
char s4[13];

void strcpyOverflow()
{
    printf("address: global_s1=%p.\n", global_s1);
    printf("address: global_s2=%p.\n", global_s2);
    printf("address:        s3=%p.\n", s3);
    printf("address:        s4=%p.\n", s4);

    strcpy(global_s2, "aaaaaaaaaaaa");  // 12a
    strcpy(s4, "bbbbbbbbbbbb"); // 12b
 
    printf("\nbefore overflow:\n");    
    printf("global_s2[13]=%s.\n", global_s2);
    printf("s4[13]       =%s.\n", s4);

    char tmp1[] = "123456789012";
    strcpy(global_s1, tmp1);            // overflow

    char tmp2[] = "ABCDEFGHIJK";
    strcpy(s3, tmp2);                   // overflow

    printf("\nafter overflow:\n");    
    printf("global_s1[4] =%s.\n", global_s1);
    printf("global_s2[13]=%s.\n", global_s2);
    printf("s3[2]        =%s.\n", s3);
    printf("s4[13]       =%s.\n", s4);

}


int main()
{
    strcpyOverflow();

    return 0;
}

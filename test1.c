#include <stdio.h>
#include <string.h>

typedef struct {
    int eror;
} test;
int main()
{
    test tist;
    printf("%d", tist.eror);
    tist.eror = 4;
    printf("%d", tist.eror);
}
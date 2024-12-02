#include <stdio.h>
#include <string.h>

int main()
{
    int age;
    int gender;
    printf("Enter your age: ");
    scanf("%d", &age);

    if (age <= 12 ){
        printf ("Your age is %d and you are a child ", age);
    }
    else{
        if(age <= 19){
            printf("Your age is %d and you are a teen", age);
        }
        else{
            if (age <= 59){
                printf("Your age is %d and you are a adult", age);
            }
            else{
                printf("Your age is %d and you are a senior",age);
            }
        }
    }






    return 0;
}
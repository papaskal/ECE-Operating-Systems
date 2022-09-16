#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>


int main(int argc, char **argv){

    if (argc != 3){
        printf("Invalid input. Please provide exactly 2 positive numbers.\n");
        return -1;
    }

    int n = atoi(argv[1]);
    if (n<1){
        printf("Invalid input. I need a positive number to denote the nymber of chilren.\n");
        return -1;
    }
    int a = atoi(argv[2]);
    if (a<1){
        printf("Invalid input. I can only calculate the factorial of a positive number.\n");
        return -1;
    }

    if (a < n)
        n = a;

    int **pd = (int**)malloc(n*sizeof(int*));
    for (int i=0; i<=n; i++){
        pd[i] = (int*)malloc(2*sizeof(int));
        pipe(pd[i]);
    }
    
    pid_t child=1;
    //int status;
    long long unsigned int  f=0;
    unsigned int l=0, k=0;

    for (l=0; l<n && child; l++){
        if ((child = fork()) < 0){
            perror("Error. Fork is invalid\n");
            return -1;
        }
    }
    l--;

    if (!child){
        while (k + n <= a){
            close(pd[l][1]);                                                    //Child l receives from pipe [l] and sends to pipe [l+1]
            read(pd[l][0], &k, sizeof(k));
            close(pd[l][1]);
            read(pd[l][0], &f, sizeof(f));
            
            f *= ++k;
            
            printf("Child %d: Factorial so far is: %llu\n", l+1, f);
            
            close(pd[(l+1)%n][0]);                                              //mod(n) completes the circle of pipes
            write(pd[(l+1)%n][1], &k, sizeof(k));
            close(pd[(l+1)%n][0]);
            write(pd[(l+1)%n][1], &f, sizeof(f));
        }
        if (k == a){           
            printf("Child %d: Total factorial is %llu\n", l+1, f);    
        }
        exit(0);
    }
    else{
        k = 0;
        f = 1;
        close(pd[0][0]);
        write(pd[0][1], &k, sizeof(k));
        close(pd[0][0]);
        write(pd[0][1], &f, sizeof(f));

        for (int i=0; i<n; i++)
            wait(NULL);
        //wait(&status);
        //printf("Done waiting\n");

    }


    return 0;
}
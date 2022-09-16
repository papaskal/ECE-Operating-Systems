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

    pid_t child=1;
    //int status;
    long long unsigned int  f=0;
    unsigned int l=0, k=0;


    int pd[2];
    int *pd_out = pd;
    int *pd_in;
    
    pipe(pd_out);

    for (l=0; l<n && child; l++){               //Every time we create a child, we give it the last pd_out as its pd_in
        pd_in = pd_out;                         //And create a new pd_out
        pd_out = (int *)malloc(2*sizeof(int));
        pipe(pd_out);
        if ((child = fork()) < 0){
            perror("Error. Fork is invalid\n");
            return -1;
        }
    }

    if (l==n)                               //Complete the circle (pd is the first pipe)
        pd_out = pd;

    if (!child){                            //Each child knows only its own pd_in and pd_out    
        while (k + n <= a){
            close(pd_in[1]);
            read(pd_in[0], &k, sizeof(k));
            close(pd_in[1]);
            read(pd_in[0], &f, sizeof(f));
            
            f *= ++k;
            
            printf("Child %d: Factorial so far is: %llu\n", l, f);
            
            close(pd_out[0]);
            write(pd_out[1], &k, sizeof(k));
            close(pd_out[0]);
            write(pd_out[1], &f, sizeof(f));
        }
        if (k == a){           
            printf("Child %d: Total factorial is %llu\n", l, f);    
        }
        exit(0);
    }
    else{
        k = 0;
        f = 1;
        close(pd[0]);
        write(pd[1], &k, sizeof(k));
        close(pd[0]);
        write(pd[1], &f, sizeof(f));

        for (int i=0; i<n; i++)
            wait(NULL);
        //wait(&status);
        //printf("Done waiting\n");

    }


    return 0;
}
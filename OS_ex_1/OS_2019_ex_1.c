#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>



int main(){
    int status;
    pid_t child;

                                    //F START
    child = fork();                 //f->c1
    if (child<0){
        printf("ERROR\n");
        _exit(0);
    }
    else if (child==0){                     //C1 START
        child = fork();                     //c1->c3
        if (child<0){
            printf("ERROR\n");
            _exit(0);
        }
        else if (child==0){                         //C3 START
            for (int i=0; i<10; i++){
                printf("C3 Process %d is executed, my father is %d\n", getpid(), getppid());
                sleep(1);
            }
            _exit(0);
        }                                           //C3 END
        else {
            child = fork();                  //c1->c4
            if (child<0){
                printf("ERROR\n");
                _exit(0);
            }
            else if (child==0){                     //C4 START                
                for (int i=0; i<10; i++){
                    printf("C4 Process %d is executed, my father is %d\n", getpid(), getppid());
                    sleep(1);
                }
                _exit(0);
            }                                       //C4 END
            else{
                for (int i=0; i<10; i++){
                    printf("C1 Process %d is executed, my father is %d\n", getpid(), getppid());
                    sleep(1);
                }
                wait(&status);
                wait(&status);
                _exit(0);
            }                               //C1 END
        }
    }
    else {
        child = fork();             //f->c2
        if (child<0){
            printf("ERROR\n");
            _exit(0);
        }
        else if (child==0){                 //C2 START
            child = fork();                 //c2->c5
            if (child<0){
            printf("ERROR\n");
            _exit(0);
            }
            else if (child==0){                     //C5 START            
                for (int i=0; i<10; i++){
                    printf("C5 Process %d is executed, my father is %d\n", getpid(), getppid());
                    sleep(1);
                }
            _exit(0);
            }                                       //C5 END
            else {            
                for (int i=0; i<10; i++){
                    printf("C2 Process %d is executed, my father is %d\n", getpid(), getppid());
                    sleep(1);
                }
                wait(&status);
                _exit(0);
            }                               //C2 END
        }
        else {
            for (int i=0; i<10; i++){
                printf("F  Process %d is executed, my father is %d\n", getpid(), getppid());
                sleep(1);
            }
            wait(&status);
            wait(&status);                      
            _exit(0);
        }                           //F END
    }

    return 0;
}
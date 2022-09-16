#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void handler(int num){
}

int main(int argc, char **argv){

    int c, n=1;

    int status;
    pid_t child[5];

                                    //F START
    child[0] = fork();                 //f->c1
    if (child[0]<0){
        printf("ERROR\n");
        _exit(0);
    }
    else if (child[0]==0){                     //C1 START
        for (int n=1; n<=5; n++){
            pause();                            //C1 END
            printf(Child1 &d is executed (n), getpid());
            sleep(1);
            printf(Child1 &d is executed (n), getpid());
            sleep(1);
            printf(Child1 &d is executed (n), getpid());
            sleep(1);
        }
        exit(0);
    }
    else {
        child[1] = fork();             //f->c2
        if (child[1]<0){
            printf("ERROR\n");
            _exit(0);
        }
        else if (child[1]==0){                 //C2 START
            pause();
            exit(0);                              //C2 END
        }
        else {
            child[2] = fork();             //f->c2
            if (child[2]<0){
                printf("ERROR\n");
                _exit(0);
            }
            else if (child[2]==0){                 //C2 START
                pause();
                exit(0);
                                            //C2 END
            }
            else {
                child[3] = fork();             //f->c2
                if (child[3]<0){
                    printf("ERROR\n");
                    _exit(0);
                }
                else if (child[3]==0){                 //C2 START
                    pause();
                    exit(0);    
                                                //C2 END
                }
                else {
                    child[4] = fork();             //f->c2
                    if (child[4]<0){
                        printf("ERROR\n");
                        _exit(0);
                    }
                    else if (child[4]==0){                 //C2 START
                        pause();
                        exit(0);    
                                                    //C2 END
                    }
                    else {
                        int order[argc];
                        for (int i=1; i<argc; i++){
                            c = argv[j][0] - '0' - 1;
                            if (c<0 || c>argc-1){
                                    printf("ERROR\n");
                                    exit(0);
                                }
                            order[i-1] = c;
                        }
                        for (int i=0; i<4; i++)
                            for (int j=1; j<argc; j++)
                                kill(child[order[j]], SIGINT);
                        
                        for (int i=1; i<argc; i++)
                            kill(child[order[j]], SIGTERM);
                        
                    } 
                }     
            }  
        }                           //F END
    }

    return 0;
}
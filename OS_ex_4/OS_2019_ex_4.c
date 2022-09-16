#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

void crit(int l, int p){
    printf("Child %d %d starts executing the critical section vvvvvvvvvvvv\n", l, p);
    for(int i=0; i<5; i++)
        printf("Child %d %d executes a critical section\n", l, p);
    printf("Child %d %d finished executing the critical section ^^^^^^^^^^\n", l, p);
}

void non_crit(int l, int p){
    for(int i=0; i<7; i++)
        printf("Child %d %d executes a non critical section\n", l, p);
}




int main(int argc, char **argv){

    int pd[2];
    pipe(pd);
    int w=0, l=0;

    pid_t child=1;
    
    for (l=0; l<3 && child; l++){
        if ((child = fork()) < 0){
            perror("Error. Fork is invalid\n");
            return -1;
        }
    }
    
    if (!child){                    
        if (l==1){                              //Child 1
            //close(pd[1]);
            read(pd[0], &w, sizeof(w));         //crit
            crit(l, getpid());   
            write(pd[1], &w, sizeof(w));     

            non_crit(l, getpid());              //non_crit
            non_crit(l, getpid());              //non_crit

            read(pd[0], &w, sizeof(w));         //crit
            crit(l, getpid());   
            write(pd[1], &w, sizeof(w));     

            non_crit(l, getpid());              //non_crit

            read(pd[0], &w, sizeof(w));         //crit
            crit(l, getpid());   
            write(pd[1], &w, sizeof(w));     
            
            exit(0);
        }

        if (l==2){                              //Child 2
            non_crit(l, getpid());              //non_crit

            read(pd[0], &w, sizeof(w));         //crit
            crit(l, getpid());   
            write(pd[1], &w, sizeof(w));     

            non_crit(l, getpid());              //non_crit

            read(pd[0], &w, sizeof(w));         //crit
            crit(l, getpid());   
            write(pd[1], &w, sizeof(w));     

            non_crit(l, getpid());              //non_crit

            read(pd[0], &w, sizeof(w));         //crit
            crit(l, getpid());   
            write(pd[1], &w, sizeof(w));     
            
            exit(0);
        }
        
        if (l==3){                              //Child 2
            
            read(pd[0], &w, sizeof(w));         //crit
            crit(l, getpid());   
            write(pd[1], &w, sizeof(w));     

            non_crit(l, getpid());              //non_crit

            read(pd[0], &w, sizeof(w));         //crit
            crit(l, getpid());   
            write(pd[1], &w, sizeof(w));     

            non_crit(l, getpid());              //non_crit

            read(pd[0], &w, sizeof(w));         //crit
            crit(l, getpid());   
            write(pd[1], &w, sizeof(w));     
        
            non_crit(l, getpid());              //non_crit
            
            exit(0);
        }
        
    }
    else{
        write(pd[1], &w, sizeof(w));     
        while (wait(NULL)>0);
    }
    
    return 0;
}
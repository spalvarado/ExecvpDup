
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>
#include <string>
#include <cstring>
#include <sys/wait.h>

#define MAX_CHAR 250
    using namespace std;



    int main(int argc, char *argv[]) {
    char* args[3];
    char charray[17];
    string input = "1.cpp";
    string wc = "wc";
    args[0]=(char*)wc.c_str();
    args[1] = (char*)input.c_str();
    args[2] = NULL;

        int fd[2], rc;

            if(pipe(fd)==-1){
                //pipe failure
                printf("Error: Pipe has failed");
            }

            rc = fork();

            if(rc < 0){
                printf("Error: Fork has failed");
            }
            else if(rc ==0){
                //child process
                close(fd[0]);
                dup2(fd[1],STDOUT_FILENO);
                execvp(args[0], args);
            }
            else{
                //parent process
                close(fd[1]);
                wait(NULL);
                read(fd[0], charray, 17);
                for(int i =0; i< 17; i++){
                    cout<<charray[i];
                }
                cout<<"\n";
            }
        return 0;
    }




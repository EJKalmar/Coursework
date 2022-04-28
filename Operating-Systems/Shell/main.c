/*
 * main.c
 *
 * CSC360 Assignment 1 - Shell
 * Jonathan Kalmar
 * V00762777
 * June 5, 2020
 *
 */

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

//process struct for background processes
typedef struct{
    char *name;
    pid_t pid;
    char *status;
}process;

//initiate array for 5 background processes
process p1 = {NULL, 0, NULL};
process p2 = {NULL, 0, NULL};
process p3 = {NULL, 0, NULL};
process p4 = {NULL, 0, NULL};
process p5 = {NULL, 0, NULL};

process *bgp[5] = {&p1,&p2,&p3,&p4,&p5};

//current number of background processes
int num_bg = 0;

int cd(char *args[15]){
    //error handling
    if(args[1] == NULL){
        printf("Error: enter directory.\n");
    }
    else{
        if(chdir(args[1])==-1){
            perror("");
        }
    }
    return 0;
}

int pwd(char *args[15]){
    char directory[256];
    getcwd(directory, sizeof(char)*256);
    printf("%s\n", directory);
    return 0;
}

int bg(char *args[15]){
    //error handling
    if(args[1] == NULL){
        printf("Error: enter command.\n");
        return 0;
    }
    if(num_bg>4){
        printf("Error: too many background processes already running.\n");
        return 0;
    }
    //shift index
    char *new_args[15];
    for(int i=0;i<14;i++){
        new_args[i] = args[i+1];
    }
    new_args[14] = NULL;
    //fork
    pid_t pid = fork();
    if (pid < 0){
        //error
        printf("fork() error.\n");
        return -1;
    }
    else if (pid == 0) {
        //child
        execvp(new_args[0], new_args);
        //if we reach here then execvp failed, terminate the child process.
        printf("invalid command.\n");
        exit(0);
    }
    else{
        //save background process information in the first open slot
        int j=0;
        for(int i=0;i<5;i++){
            if(bgp[i]->name == NULL){
                j=i;
                break;
            }
        }
        bgp[j]->name = new_args[0];
        bgp[j]->pid = pid;
        bgp[j]->status = "R";
        num_bg++;
    }
    return 0;
}

int bglist(){
    for(int i=0;i<5;i++){
        if(bgp[i]->name != NULL){
            printf("%i[%s]: %i %s\n", i+1, bgp[i]->status, bgp[i]->pid, bgp[i]->name);
        }
    }
    printf("Total Background jobs: %i.\n", num_bg);
    return 0;
}

int bgkill(char *args[15]){
    //error handling
    if(args[1] == NULL){
        printf("Error: enter job number.\n");
        return 0;
    }
    int index = atoi(args[1])-1;
    if (index < 0 || index > 4 || bgp[index]->name==NULL){
        printf("Error: no background process with given index.\n");
        return 0;
    }
    //get the pid of the job to kill & send SIGTERM signal to kill the process
    pid_t kpid = bgp[index]->pid;
    printf("%i: %s has been terminated.\n", index+1, bgp[index]->name);
    int status = kill(kpid, SIGTERM);
    if(strcmp(bgp[index]->status, "S")==0){
        kill(kpid, SIGCONT);
    }
    return status;
}

int start(char *args[15]){
    //error handling
    if(args[1] == NULL){
        printf("Error: enter job number.\n");
        return 0;
    }
    int index = atoi(args[1])-1;
    if (index < 0 || index > 4 || bgp[index]->name==NULL){
        printf("Error: no background process with given index.\n");
        return 0;
    }
    if (strcmp(bgp[index]->status, "R")==0){
        printf("Error: process is already running.\n");
        return 0;
    }
    //change status of the job to "R" and send SIGCONT signal to continue the process
    pid_t spid = bgp[index]->pid;
    bgp[index]->status = "R";
    return kill(spid, SIGCONT);
}

int stop(char *args[15]){
    //error handling
    if(args[1] == NULL){
        printf("Error: invalid job number.\n");
        return 0;
    }
    int index = atoi(args[1])-1;
    if (index < 0 || index > 4 || bgp[index]->name==NULL){
        printf("Error: no background process with given index.\n");
        return 0;
    }
    if(strcmp(bgp[index]->status, "S")==0){
        printf("Error: process is already stopped.\n");
        return 0;
    }
    //change status of the job to "S" and send SIGSTOP signal to stop the process
    pid_t spid = bgp[index]->pid;
    bgp[index]->status = "S";
    return kill(spid, SIGSTOP);
}

int special(char *args[15]){
    //check if the command is a special case & execute if so
    if (strcmp(args[0], "bg")==0){
        return bg(args);
    }
    else if (strcmp(args[0], "pwd")==0){
        return pwd(args);
    }
    else if (strcmp(args[0], "cd")==0){
        return cd(args);
    }
    else if (strcmp(args[0], "bglist")==0){
        return bglist();
    }
    else if (strcmp(args[0], "bgkill")==0){
        return bgkill(args);
    }
    else if (strcmp(args[0], "start")==0){
        return start(args);
    }
    else if (strcmp(args[0], "stop")==0){
        return stop(args);
    }
    else{
        return -2;
    }
}

//execute an arbitrary command
int basic(char *args[15]){
    int status;
    pid_t pid = fork();
    if (pid < 0){
        //error
        printf("fork() error\n");
    }
    else if (pid == 0) {
        //child
        execvp(args[0], args);
        //if we reach here then execvp failed, terminate the child process.
        printf("invalid command\n");
        exit(0);
    }
    else{
        //parent waits until child terminates
        wait(&status);
    }
    return 0;
}

int main ( void )
{
    for (;;)
    {
        //print current directory as prompt
        char directory[256];
        getcwd(directory, sizeof(char)*256);
        printf("%s> ", directory);
        
        //read line
        char *cmd = readline ("");
        
        //check to see if any background processes have finished & remove them from bglist.
        pid_t wpid = waitpid(-1,NULL, WNOHANG);
        while (wpid > 0 ){
            int index;
            for(int i=0;i<5;i++){
                index = i;
                if (bgp[index]->pid == wpid){
                    break;
                }
            }
            bgp[index]->name = NULL;
            bgp[index]->pid = 0;
            bgp[index]->status = NULL;
            num_bg--;
            wpid = waitpid(-1,NULL, WNOHANG);
        }
        //split line into a list of arguments
        char    *args[15];
        int i=0;
        char *arg = strsep(&cmd, " ");
        while (arg != NULL){
            args[i] = arg;
            i++;
            arg = strsep(&cmd, " ");
        }
        //indicate end of args
        args[i]=NULL;
        
        //exit if prompted
        if (strcmp(args[0], "exit")==0){
            free(cmd);
            exit(1);
        }
        
        //free memory allocated for readline
        free(cmd);
        
        //perform special command if indicated, else attempt basic execution
        if (special(args)==-2){
            basic(args);
        }
    }
    return 0;
}

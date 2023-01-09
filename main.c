//Nima Moazzen
//401106599

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

void createfile(char* commands[]);
void cat(char* commands[]);

int main()
{
    while(1)
    {
        char* command = (char*) calloc(2000 , sizeof(char));
        gets(command);

        char *delim = strtok(command, " ");

        char* commandseperated[10]; //saving commands in an array
        int length = 0;
        for (int i = 0; delim != NULL ; i++)
        {
            commandseperated[i] = delim;
            delim = strtok(NULL," ");
            length++;
        }

        if(strcmp(commandseperated[0] , "exit") == 0)
        {
            break;
        }

        if (strcmp(commandseperated[0],"createfile") == 0 && strcmp(commandseperated[1],"--file") == 0)
        {
            createfile(commandseperated);
        }

        if (strcmp(commandseperated[0],"cat") == 0 && strcmp(commandseperated[1],"--file") == 0)
        {
            cat(commandseperated);
        } 

        else
        {
            printf("Invalid command\n");
        }
    }
}


void createfile(char* commands[])
{
    char* mydir[10]; //saving the directory in an array
    char* mydelim = strtok(commands[2],"/");
    int mylength = 0;
    FILE* file;

    for (int i = 0; mydelim != NULL; i++)
    {
        mydir[i] = mydelim;
        mydelim = strtok(NULL,"/");
        mylength++;
    }

    chdir(mydir[0]);

    for (int i = 1; i < mylength - 1; i++)
    {
        if(chdir(mydir[i]) == 0)
        {
            continue;
        }

        else if (chdir(mydir[i]) == -1)
        {
            mkdir(mydir[i]);
            chdir(mydir[i]);
        }
    }

    int check = 1;

    file = fopen(mydir[mylength-1],"r");

    if (file == NULL)
    {
        file = fopen(mydir[mylength-1],"w");
    }
    else
    {
        printf("A file with this name already exits!");
        check = 0;
    }

    if(check)
        printf("The file is successfully created!\n");
    
    fclose(file);
}

void cat(char* commands[])
{
    char* mydir[10]; //saving the directory in an array
    char* mydelim = strtok(commands[2],"/");
    int mylength = 0;
    char c;
    FILE* file;

    for (int i = 0; mydelim != NULL; i++)
    {
        mydir[i] = mydelim;
        mydelim = strtok(NULL,"/");
        mylength++;
    }

    chdir(mydir[0]);

    for (int i = 1; i < mylength - 1; i++)
    {
        if(chdir(mydir[i]) == 0)
        {
            continue;
        }

        else if (chdir(mydir[i]) == -1)
        {
            mkdir(mydir[i]);
            chdir(mydir[i]);
        }
    }

    file = fopen(mydir[mylength-1],"r");

    if(file == NULL)
    {
        printf("There is no file with this name\n");
    }

    c = fgetc(file);

    while(c != EOF)
    {
        printf("%c",c);
        c = fgetc(file);
    }

    fclose(file);

    printf("\n");
}
//Nima Moazzen
//401106599

//version 2 - createfile and cat - needs a lot of debugging

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

int mylength;

void getdirectory(char** , char*);
void back();
void createfile();
void cat();

int main()
{
    char firstcommand[30] , secondcommand[30];
    int invalid = 1;
    while(1)
    {
        scanf("%s",firstcommand);

        if (strcmp(firstcommand , "exit") == 0)
        {
            invalid = 0;
            break;
        }

    //CreateFile
        if(strcmp(firstcommand , "createfile") == 0)
        {
            getchar();
            scanf("%s",secondcommand);
            if(strcmp(secondcommand , "--file") == 0)
            {
                invalid = 0;
                createfile();
            }
        }

    //Cat
        if(strcmp(firstcommand , "cat") == 0)
        {
            getchar();
            scanf("%s",secondcommand);
            if(strcmp(secondcommand , "--file") == 0)
            {
                invalid = 0;
                cat();
            }
            else
            {
                printf("invalid command\n");
                continue;
            }
        }

        else if(invalid)
        {
            printf("invalid command\n");
            invalid = 0;
            continue;
        }
        invalid = 1;
    }
}

void getdirectory(char** step2 , char* step1)
{
    int flag = 1 , index = 0;
    
    mylength = 0;
    while (flag == 1)
    {
        char x;
        scanf("%c",&x);
        if(x != '"' && x != '\n')
        {
            *(step1+index) = x;
            index++;
        }
        if(x == '\n')
        {
            flag = 0;
        }
    }

    char* mydelim = strtok(step1,"/");

    for (int i = 0; mydelim != NULL; i++)
    {
        step2[i] = mydelim;
        mydelim = strtok(NULL,"/");
        mylength++;
    }
}

void back()
{
    for(int i = 1 ; i < mylength ; i++)
    {
        chdir("..");
    }
    mylength = 0;
}

void createfile()
{
    getchar();
    char dir[100];
    char* mydir[10];
    
    getdirectory(mydir,dir);
    
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

    FILE* file;

    file = fopen(mydir[mylength-1] , "r");

    if (file == NULL)
    {
        // printf("%s\n",mydir[mylength-1]);
        file = fopen(mydir[mylength-1],"w");
        file = fopen(mydir[mylength-1],"r");
        if(file != NULL)
            printf("The file is successfully created!\n");
    }
    else 
    {
        printf("A file with this name already exits!\n");
    }

    fclose(file);
    back();
}

void cat()
{
    getchar();
    char dir[100];
    char* mydir[10];
    char c;

    getdirectory(mydir,dir);

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

    FILE* file;
    file = fopen(mydir[mylength-1],"r");

    if(file == NULL)
    {
        printf("There is no file with this name");
    }

    c = fgetc(file);

    while(c != EOF)
    {
        printf("%c",c);
        c = fgetc(file);
    }

    fclose(file);

    back();
    printf("\n");
}
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
void copyfile(FILE* , FILE*);
void createfile();
void cat();
void insertfile();

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

    //Insert
        if(strcmp(firstcommand , "insertfile") == 0)
        {
            getchar();
            scanf("%s",secondcommand);
            if(strcmp(secondcommand , "--file") == 0)
            {
                invalid = 0;
                insertfile();
            }
            else
            {
                printf("invalid command1\n");
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
        if(x != '"' && x != '\n' && x != '-')
        {
            step1[index] = x;
            index++;
        }
        if(x == '\n')
        {
            flag = 0;
        }
        if(x == '-')
        {
            if (step1[index-1] == ' ')
                step1[index-1] = '\0';
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

void copyfile(FILE* file1 , FILE* file2)
{
    char c;

    c = fgetc(file1);
    while (c != EOF)
    {
        fputc(c,file2);
        c = fgetc(file1);
    }
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

void insertfile()
{
    getchar();
    char dir[100] , mystr[1000];
    char c;
    char* mydir[10];
    int row , column , rowgone = 0 , columngone = 0;

    getdirectory(mydir,dir);
    printf("-----------\n");
    printf("%sk\n",mydir[0]);
    printf("%sk\n",mydir[1]);
    printf("%sk\n",mydir[2]);
    printf("-----------\n");
 
    FILE* firstfile;
    FILE* secondfile;
    FILE* thirdfile;

    // getchar();
    char thirdcommand[30];
    scanf("%s",thirdcommand);

    printf("thirdcommand is %s\n",thirdcommand);
    printf("-------------\n");

    if(strcmp(thirdcommand , "-str") == 0)
    {
        getchar();
        char first = getchar();
        
        if(first == '"')
        {
            int i = 0 ;
            int flag = 1;
            while(flag == 1)
            {
                scanf("%c",&mystr[i]);
                // printf("\t%c\n",mystr[i]);
                if(mystr[i] == '"')
                {
                    mystr[i] = '\0';
                    flag = 0;
                }
                i++;
            }
        }

        printf("first check mystr is %s\n",mystr);

        getchar();

        char fourthcommand[30];

        scanf("%s",fourthcommand);

        if(strcmp(fourthcommand , "--pos") == 0)
        {
            scanf("%d:%d",&row,&column);
        }

        else
        {
            printf("invalid command\n");
            return;   
        }

        printf("just checkng , mystr = %s,\t row and column : %d %d\n",mystr,row,column);
        printf("------------------\n");

        chdir(mydir[0]);

        for(int i = 1 ; i < mylength - 1 ; i++)
        {
            if(chdir(mydir[i]) == 0)
            {
                continue;
            }
            else if(chdir(mydir[i]) == -1)
            {
                printf("there is no directory named %s\n",mydir[i]);
                return;
            }
        }

        firstfile = fopen(mydir[mylength-1],"r");
        if(firstfile == NULL)
        {
            printf("%s doesn't exist in this folder!\n",mydir[mylength-1]);
            return;
        }
        else
        {
            secondfile = fopen("zapas.txt","w");

    //writing the final text in another file
            c = fgetc(firstfile);
            while (rowgone != row-1)
            {
                fputc(c,secondfile);
                if(c == '\n')
                    rowgone++;
                c = fgetc(firstfile);   
            }

            while(columngone != column-1)
            {
                fputc(c , secondfile);
                columngone++;
                c = fgetc(firstfile);
            }

            fputc(c,secondfile);

            for(int i = 0 ; mystr[i] != '\0' ; i++)
            {
                fputc(mystr[i],secondfile);
            }

            c = fgetc(firstfile);
            while(c != EOF)
            {
                fputc(c,secondfile);
                c = fgetc(firstfile);
            }

            fclose(firstfile);
            fclose(secondfile);

            if(remove(mydir[mylength-1]) == 0){}
    //copying our second file in the first file and deleting it
            thirdfile = fopen(mydir[mylength-1],"w");
            secondfile = fopen("zapas.txt","r");
            copyfile(secondfile,thirdfile);

            fclose(thirdfile);
            fclose(secondfile);

            if(remove("zapas.txt") == 0)
            {
                printf("your text inserted succesfully\n");
            }
        }
    }

    else
    {
        printf("invalid command2\n");
        return;
    }
    back();
}
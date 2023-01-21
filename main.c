//Nima Moazzen
//401106599

// Added Remove - needs debug

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

int mylength , row , column , size;

void getdirectory(char** , char*);
int gotodir(char**);
void back();
void copyfile(FILE* , FILE*);
int getcommands2(char*, char*, char*);
void createfile();
void cat();
void insertfile();
void removestr();


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
        if(strcmp(firstcommand , "insertstr") == 0)
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

    //Remove    
        if(strcmp(firstcommand , "removestr") == 0)
        {
            getchar();
            scanf("%s",secondcommand);
            if(strcmp(secondcommand , "--file") == 0)
            {
                invalid = 0;
                removestr();
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

int gotodir(char** mydir)
{
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
            return 0;
        }
    }
    return 1;
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
    fclose(file1);
    fclose(file2);
}

int getcommands2(char* thirdcommand , char* fourthcommand , char* flag)
{
    scanf("%s",thirdcommand);
    if(strcmp(thirdcommand,"-pos") == 0)
    {
        scanf("%d:%d",&row,&column);

        scanf(" %s",fourthcommand);
        if(strcmp(fourthcommand,"-size") == 0)
        {
            scanf("%d",&size);
            scanf(" %s",flag);

        }
        else
        {
            printf("Invalidcommand\n");
            return 0;
        }
    }
    else
    {
        printf("Invalid command\n");
        return 0;
    }
    return 1;
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

    if(gotodir(mydir) == 0)
        return;

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
    FILE* firstfile;
    FILE* secondfile;
    char thirdcommand[30];

    getdirectory(mydir,dir);
    scanf("%s",thirdcommand);

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
                
                if(mystr[i] == '-' && mystr[i-1] == ' ' && mystr[i-2] == '"')
                {
                    mystr[i-2] = '\0';
                    flag = 0;
                }
                i++;
            }
        }
        char fourthcommand[30];

        scanf("%s",fourthcommand);

        if(strcmp(fourthcommand , "-pos") == 0)
        {
            scanf("%d:%d",&row,&column);
        }

        else
        {
            printf("invalid command\n");
            return;   
        }

        if(gotodir(mydir) == 0)
            return;

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
            while (rowgone != row-1)
            {
                c = fgetc(firstfile);  
                fputc(c,secondfile);
                if(c == '\n')
                    rowgone++;   
            }

            while(columngone != column)
            {
                c = fgetc(firstfile);
                fputc(c , secondfile);
                columngone++;
            }

            for(int i = 0 ; mystr[i] != '\0' ; i++)
            {
                if(mystr[i] == '\\' && mystr[i+1] == '\\' && mystr[i+2] == 'n')
                {
                    fprintf(secondfile,"\\n");
                    i+=2;
                }
                else if (mystr[i] == '\\' && mystr[i+1] == 'n')
                {
                    fprintf(secondfile,"\n");
                    i++;
                }
                else
                {
                    fputc(mystr[i],secondfile);
                }
            }

            
            while(c != EOF)
            {
                c = fgetc(firstfile);
                fputc(c,secondfile);
            }

            fclose(firstfile);
            fclose(secondfile);

    //copying our second file in the first file and deleting it
            firstfile = fopen(mydir[mylength-1],"w");
            secondfile = fopen("zapas.txt","r");
            copyfile(secondfile,firstfile);

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

void removestr()
{
    getchar();
    char dir[100];
    char c;
    char* mydir[10];
    int rowgone = 0 , columngone = 0;

    getdirectory(mydir,dir);

    FILE* firstfile;
    FILE* secondfile;

    char thirdcommand[30] , fourthcommand[30] , flag[2];

    if(getcommands2(thirdcommand,fourthcommand,flag) == 0)
        return;

    printf("checking the inputs : mydir[1] %s , size %d , pos %d:%d , flag %s\n",mydir[1],size,row,column,flag);
    
    if(strcmp(flag,"-f") == 0)  //front
    {
        if(gotodir(mydir) == 0)
            return;
        firstfile = fopen(mydir[mylength-1],"r");
        if(firstfile == NULL)
        {
            printf("There is no file named %s!\n",mydir[mylength-1]);
            return;   
        }
        secondfile = fopen("zapas.txt","w");
        while(rowgone != row-1)
        {
            c = fgetc(firstfile);
            fputc(c,secondfile);
            if(c == '\n')
                rowgone++;
        }
        while(columngone != column)
        {
            c = fgetc(firstfile);
            fputc(c,secondfile);
            columngone++;
        }
        for(int i = 0 ; i < size ; i++)
        {
            c = fgetc(firstfile);
        }

        while (c != EOF)
        {
            c = fgetc(firstfile);
            fputc(c,secondfile);
        }

        fclose(firstfile);
        fclose(secondfile);

        firstfile = fopen(mydir[mylength-1],"w");
        secondfile = fopen("zapas.txt","r");
        copyfile(secondfile,firstfile);

        if(remove("zapas.txt") == 0)
        {
            printf("Removing was succesfull!\n");
            return;
        }
    }
    if(strcmp(flag,"-b") == 0)  //back
    {
        gotodir(mydir);
        firstfile = fopen(mydir[mylength-1],"r");
        if(firstfile == NULL)
        {
            printf("There is no file named %s!\n",mydir[mylength-1]);
            return;
        }
        secondfile = fopen("zapas.txt","w");

        while (rowgone != row-1)
        {
            c = fgetc(firstfile);
            fputc(c,secondfile);
            if(c == '\n')
                rowgone++;            
        }
        while (columngone != column)
        {
            c = fgetc(firstfile);
            fputc(c,secondfile);
            columngone++;
        }

        if(size > column && row > 1)
            size +=2;
        else if(size > column && row == 1)
            size = column;
        
        fseek(secondfile,(-1 * size),SEEK_CUR);
        while(c != EOF)
        {
            c = fgetc(firstfile);
            fputc(c,secondfile);
        }

        fclose(firstfile);
        fclose(secondfile);

        firstfile = fopen(mydir[mylength-1],"w");
        secondfile = fopen("zapas.txt","r");
        copyfile(secondfile,firstfile);

        if(remove("zapas.txt") == 0)
        {
            printf("Removing was seccesfull!\n");
        }
    }
}
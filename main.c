//Nima Moazzen
//401106599

//find grep replace are ignored - compare added and debugged

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <windows.h>

int mylength , row , column , size , rowgone , columngone;

void getdirectory(char** , char*);
int gotodir(char**);
void back();
void copyfile(FILE* , FILE*);
int getcommands2(char*, char*, char*);
int gotopos1(FILE*,int , int , char); //For functions which don't need a second file (like copystr)
int gotopos2(FILE*, FILE*, int, int, char); //For functions which need second file and they have limits (like cutstr and removestr)
void gotopos3(FILE*, FILE*, int, int, char); //For functions which need a second file and they are for inserting without limits (like insertstr and pastestr)
void delete(char*,int);
int maxi(int,int);
int mini(int,int);

void createfile();
void cat();
void insertfile();
void removestr();
void copytoclipboard(const char*);
void copystr();
void cutstr();
void pastestr();
void find();
void compare();


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
                continue;
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
                continue;
            }
        }
    //Copy     
        if(strcmp(firstcommand , "copystr") == 0)
        {
            getchar();
            scanf("%s",secondcommand);
            if(strcmp(secondcommand , "--file") == 0)
            {
                invalid = 0;
                copystr();
                continue;
            }
        }

    //Cut    
        if(strcmp(firstcommand , "cutstr") == 0)
        {
            getchar();
            scanf("%s",secondcommand);
            if(strcmp(secondcommand , "--file") == 0)
            {
                invalid = 0;
                cutstr();
                continue;
            }
        }

    //Paste  
        if(strcmp(firstcommand , "pastestr") == 0)
        {
            getchar();
            scanf("%s",secondcommand);
            if(strcmp(secondcommand , "--file") == 0)
            {
                invalid = 0;
                pastestr();
                continue;
            }
        }

    //Find
        if(strcmp(firstcommand,"find") == 0)
        {
            getchar();
            scanf("%s",secondcommand);
            if(strcmp(secondcommand,"--str") == 0)
            {
                invalid = 0;
                find();
                continue;
            }
        }

    //Compare    
        if(strcmp(firstcommand,"compare") == 0)
        {
            getchar();
            invalid = 0;
            compare();
            continue;
        }

    //Invalid Input
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
    int withoutspace = 0;
    
    mylength = 0;
    while (flag == 1)
    {
        char x;
        scanf("%c",&x);
        if(index == 0 && x != '"')
            withoutspace = 1;

        if(x != '"' && x != '\n' && x != '-')
        {
            step1[index] = x;
            index++;
        }
        if(x == '\n')
        {
            flag = 0;
        }
        if(withoutspace == 1 && x == ' ')
        {
            step1[index] = '\0';
            flag = 0;
            getchar();
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
    while(fopen("main.c","r") == NULL)
    {
        chdir("..");
    }
    chdir("root");

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

void copytoclipboard(const char* word)
{
    const size_t len = strlen(word) + 1;
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), word , len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
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

int gotopos1(FILE* file1 , int row , int column , char c)
{
    while (rowgone != row - 1)
    {
        c = fgetc(file1);
        if(c == EOF)
        {
            printf("Out of Limit\n");
            return 0;
        }
        if(c == '\n')
            rowgone++;
    }
    while (columngone != column)
    {
        c = fgetc(file1);
        if(c == EOF)
        {
            printf("Out of Limit");
            return 0;
        }
        columngone++;
    }
    return 1;
}

int gotopos2(FILE* file1, FILE* file2, int row , int column , char c)
{
    while (rowgone != row - 1)
    {
        c = fgetc(file1);
        if(c == EOF)
        {
            printf("Out of Limit\n");
            return 0;
        }
        fputc(c,file2);
        if(c == '\n')
            rowgone++;
    }
    while (columngone != column)
    {
        c = fgetc(file1);
        if(c == EOF)
        {
            printf("Out of Limit");
            return 0;
        }
        fputc(c,file2);
        columngone++;
    }
    return 1;
}

void gotopos3(FILE* file1, FILE* file2, int row , int column , char c)
{
    while (rowgone != row - 1)
    {
        c = fgetc(file1);
        if(c == EOF)
        {
            c = '\n';
        }
        fputc(c,file2);
        if(c == '\n')
            rowgone++;
    }
    while (columngone != column)
    {
        c = fgetc(file1);
        if(c == EOF)
        {
            c = ' ';
        }
        fputc(c,file2);
        columngone++;
    }
}

void delete(char* str,int index)
{
    for(int i = index ; i < strlen(str) ; i++)
    {
        str[i] = str[i+1];
    }
}

int maxi(int a ,int b)
{
    if(a > b)
        return a;
    else
        return b;
}

int mini(int a ,int b)
{
    if(a > b)
        return b;
    else
        return a;
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
    rowgone = 0 , columngone = 0;
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

            gotopos3(firstfile,secondfile,row,column,c);

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
    rowgone = 0 , columngone = 0;

    getdirectory(mydir,dir);

    FILE* firstfile;
    FILE* secondfile;

    char thirdcommand[30] , fourthcommand[30] , flag[2];

    if(getcommands2(thirdcommand,fourthcommand,flag) == 0)
        return;
    
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

        if(gotopos2(firstfile,secondfile,row,column,c) == 0) return;

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
            size ++;
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
            return;
        }
    }
    back();
}

void copystr()
{
    getchar();
    char dir[100] , mystr[10000];
    char c;
    char* mydir[10];
    rowgone = 0 , columngone = 0;

    getdirectory(mydir,dir);

    FILE* firstfile;

    char thirdcommand[30] , fourthcommand[30] , flag[2];

    if(getcommands2(thirdcommand,fourthcommand,flag) == 0)
        return;

    if(strcmp(flag,"-f") == 0) //front
    {
        if(gotodir(mydir) == 0)
            return;
        firstfile = fopen(mydir[mylength-1],"r");
        if(firstfile == NULL)
        {
            printf("There is no file named %s!\n",mydir[mylength-1]);
            return;   
        }

        if(gotopos1(firstfile,row,column,c) == 0) return;

        for(int i = 0 ; i < size ; i++)
        {
            c = fgetc(firstfile);
            if(c == EOF)
            {
                mystr[i] = '\0';
                break;
            }
            else
                mystr[i] = c;
        }
        fclose(firstfile);

        copytoclipboard(mystr);
        printf("Copying is done!\n");
        return;
    }

    if(strcmp(flag,"-b") == 0) //back
    {
        if(gotodir(mydir) == 0)
            return;
        firstfile = fopen(mydir[mylength-1],"r");
        if(firstfile == NULL)
        {
            printf("There is no file named %s!\n",mydir[mylength-1]);
            return;   
        }

        while(rowgone != row-1)
        {
            c = fgetc(firstfile);
            if(c == '\n')
                rowgone++;
        }
        while(columngone != column)
        {
            c = fgetc(firstfile);
            columngone++;
        }

        if(size > column && row > 1)
            fseek(firstfile,(-1 * (size+1)),SEEK_CUR);

        else if(size > column && row == 1)
        {
            size = column;
            fseek(firstfile,(-1 * size),SEEK_CUR);
        }
        else
            fseek(firstfile,(-1 * size),SEEK_CUR);

        for(int i = 0 ; i < size ; i++)
        {
            c = fgetc(firstfile);
            mystr[i] = c;
        }

        fclose(firstfile);

        copytoclipboard(mystr);
        printf("Copying is done\n");
        return;
    }
    back();
}

void cutstr()
{
    getchar();
    char dir[100] , mystr[10000];
    char c;
    char* mydir[10];
    rowgone = 0 , columngone = 0;

    getdirectory(mydir,dir);

    FILE* firstfile;
    FILE* secondfile;

    char thirdcommand[30] , fourthcommand[30] , flag[2];

    if(getcommands2(thirdcommand,fourthcommand,flag) == 0)
        return;

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
        
        if(gotopos2(firstfile,secondfile,row,column,c) == 0) return;

        for(int i = 0 ; i < size ; i++)
        {
            c = fgetc(firstfile);
            if(c == EOF)
            {
                mystr[i] = '\0';
                break;
            }
            else
            {
                mystr[i] = c;
            }
        }

        while (c != EOF)
        {
            c = fgetc(firstfile);
            fputc(c,secondfile);
        }

        copytoclipboard(mystr);

        fclose(firstfile);
        fclose(secondfile);

        firstfile = fopen(mydir[mylength-1],"w");
        secondfile = fopen("zapas.txt","r");
        copyfile(secondfile,firstfile);

        if(remove("zapas.txt") == 0)
        {
            printf("Cutting was succesfull!\n");
            return;
        }
        back();
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
            fseek(firstfile,(-1 * (size+1)),SEEK_CUR);
        else if(size > column && row == 1)
        {
            size = column;
            fseek(firstfile,(-1 * size),SEEK_CUR);
        }
        else
            fseek(firstfile,(-1 * size),SEEK_CUR);

        for(int i = 0 ; i < size ; i++)
        {
            c = fgetc(firstfile);
            mystr[i] = c;
        }

        if(size > column && row > 1)
            size ++;
        else if(size > column && row == 1)
            size = column;
        
        fseek(secondfile,(-1 * size),SEEK_CUR);

        while(c != EOF)
        {
            c = fgetc(firstfile);
            fputc(c,secondfile);
        }

        copytoclipboard(mystr);

        fclose(firstfile);
        fclose(secondfile);

        firstfile = fopen(mydir[mylength-1],"w");
        secondfile = fopen("zapas.txt","r");
        copyfile(secondfile,firstfile);

        if(remove("zapas.txt") == 0)
        {
            printf("Cutting was seccesfull!\n");
            return;
        }
    }
}

void pastestr()
{
    getchar();
    char dir[100] , thirdcommand[30];
    char c;
    char* mydir[10];
    rowgone = 0 , columngone = 0;

    getdirectory(mydir,dir);

    FILE* firstfile;
    FILE* secondfile;

    scanf("%s",thirdcommand);

    if(strcmp(thirdcommand , "-pos") == 0)
    {
        if(gotodir(mydir) == 0)
            return;

        scanf("%d:%d",&row,&column);
        printf("checking the inputs , pos %d:%d , mydir[1] %s\n",row,column,mydir[1]);
        firstfile = fopen(mydir[mylength-1],"r");
        secondfile = fopen("zapas.txt","w");

        OpenClipboard(0);
        HANDLE text = GetClipboardData(CF_TEXT);
        char* mytext = (char*) text;
        CloseClipboard();
        
        gotopos3(firstfile,secondfile,row,column,c);

        fprintf(secondfile,mytext);
        // for(int i = 0 ; i < strlen(mytext) ; i++)
        // {
        //     fputc(mytext[i],secondfile);
        // }

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
            printf("Pasting is complete\n");
            return;
        }
    }   
    else
    {
        printf("Invalid Command!\n");
        return;
    }
    back();
}

void find() 
{
    char mystr[10000] , thirdcommand[30];
    char c , dir[1000];
    int position = 0;
    char* mydir[10];
    FILE* firstfile;

    getchar();
    char first = getchar();
       
    if(first == '"')
    {
        int a = 0 ;
        int flag = 1;
        while(flag == 1)
        {
            scanf("%c",&mystr[a]);
            if(mystr[a] == '-' && mystr[a-1] == ' ' && mystr[a-2] == '"')
            {
                mystr[a-2] = '\0';
                flag = 0;
            }
            a++;
        }
        scanf("%s",thirdcommand);
        if(strcmp(thirdcommand,"-file") == 0) 
        {
            getchar();
            getdirectory(mydir,dir);
        }
    }
    else
    {
        mystr[0] = first;
        scanf("%s",mystr+1);

        scanf("%s",thirdcommand);
        if(strcmp(thirdcommand,"--file") == 0) 
        {
            getchar();
            getdirectory(mydir,dir);
        }
    }

    gotodir(mydir);

    firstfile = fopen(mydir[mylength-1],"r");
    if(firstfile == NULL)
    {
        printf("There is no file named %s!\n",mydir[mylength-1]);
        return;
    }

    char addstring[10000];
    c = fgetc(firstfile);
    int count = 0;
    while (c != EOF)
    {
        addstring[count] = c;
        count++;
        c = fgetc(firstfile);
    }

    //Starting the main part

    // printf("checking the inputs : mydir[0] %s , mydir[1] %s , mystr %s\n",mydir[0],mydir[1],mystr);

    char last = getchar();

    printf("%c\n",last);
    if(last == 'c') //for count option
    {
        int counter = 0;
        for(int i = 0 ; i <= count ; i++)
        {
            int flag = 0;
            if(addstring[i] == mystr[0])
            {
                flag = 1;
                for(int j = 1 ; j < strlen(mystr) ; j++)
                {
                    if(addstring[i+j] != mystr[j])
                    {
                        flag = 0;
                        break;
                    }
                } 
            }
            if (flag == 1)
            {
                counter++;
            }
        }
        printf("%d\n",counter);
        return;
    }

    else if(last == 'a') //for "at" option
    {
        int n , kol = 0;
        getchar() ,   scanf("%d",&n);
        printf("the number input is %d\n",n);
        int counter = 0;
        for(int i = 0 ; i <= count ; i++)
        {
            int flag = 0;
            if(addstring[i] == mystr[0])
            {
                flag = 1;
                for(int j = 1 ; j < strlen(mystr) ; j++)
                {
                    if(addstring[i+j] != mystr[j])
                    {
                        flag = 0;
                        break;
                    }
                } 
            }
            if (flag == 1)
            {
                counter++;
            }
            if(counter == n)
            {
                printf("%d\n",i);
                kol = 1;
                return;
            }
        }
        if(kol == 0)
        {   
            printf("-1\n");
            return;
        }
    }

    //Regular Situation with wildcards
    

    if(mystr[0] == '*')
    {
        delete(mystr,0);

        for(int i = count ; i >= 0 ; i--)
        {
            if(addstring[i] == mystr[strlen(mystr)-1])
            {
                int flag = 1;
                for(int j = 0 ; j < strlen(mystr) ; j--)
                {
                    if(addstring[i-j] != mystr[strlen(mystr)-j])
                    {
                        flag = 0;
                        break;
                    }
                }
                if(flag == 1)
                {
                    printf("%d\n",i);
                    return;
                }
            }
            if(i == count)
            {
                printf("-1\n");
                return;
            }
        }
    }

    else if(mystr[strlen(mystr)-1] == '*' && mystr[strlen(mystr)-1] != '\\')
        mystr[strlen(mystr)-1] = '\0';


    for(int i = 0 ; i <= count ; i++)
    {
        if(addstring[i] == mystr[0])
        {
            int flag = 1;
            for(int j = 1 ; j < strlen(mystr) ; j++)
            {
                if(addstring[i+j] != mystr[j])
                {
                    flag = 0;
                    break;
                }
            }
            if(flag == 1)
            {
                printf("%d\n",i);
                return;
            }
        }
        if(i == count)
        {
            printf("-1\n");
            return;
        }
    }
}

void compare()
{
    char c ,dir1[1000] , dir2[1000] ,text1[10000] , text2[10000];
    char* mydir1[10];
    char* mydir2[10];
    char* line1[1000];
    char* line2[1000];
    FILE* file1;
    FILE* file2;

    getdirectory(mydir1,dir1);

    if(gotodir(mydir1) == 0) return;
    file1 = fopen(mydir1[mylength-1],"r");
    
    if(file1 == NULL)
    {
        printf("There is no file named %s\n",mydir1[mylength-1]);
        return;
    }

    back();
    getdirectory(mydir2,dir2);

    if(gotodir(mydir2) == 0) return;
    file2 = fopen(mydir2[mylength-1],"r");
    
    if(file2 == NULL)
    {
        printf("There is no file named %s\n",mydir2[mylength-1]);
        return;
    }

    //puting the text file in an array for easier access
    c = fgetc(file1);
    int index = 0;
    while (c != EOF)
    {
        text1[index] = c;
        if(text1[index-1] == '\n' && text1[index] == '\n') //for text files with empty lines
        {
            text1[index] = ' ';
            index++;
            text1[index] = '\n';
        }
        index++;
        c = fgetc(file1);
    }
    text1[index] = '\0';

    c = fgetc(file2);
    index = 0;
    while (c != EOF)
    {
        text2[index] = c;
        if(text2[index-1] == '\n' && text2[index] == '\n') //for text files with empty lines
        {
            text2[index] = ' ';
            index++;
            text2[index] = '\n';
        }
        index++;
        c = fgetc(file2);
    }
    text2[index] = '\0';

    printf("len matin.txt = %d and len ali.txt = %d\n",strlen(text2),strlen(text1));

    //making our arrays 2 dimensional by \n
    int len1 = 0 , len2 = 0;

    char* mydelim = strtok(text1,"\n");

    for (int i = 0; mydelim != NULL; i++)
    {
        line1[i] = mydelim;
        mydelim = strtok(NULL,"\n");
        len1++;
    }

    char* mydelim2 = strtok(text2,"\n");

    for (int i = 0; mydelim2 != NULL; i++)
    {
        line2[i] = mydelim2;
        mydelim2 = strtok(NULL,"\n");
        len2++;
    }

    printf("--%s---\n",line2[3]);

    for(int i = 0 ; i < maxi(len1,len2) ; i++)
    {
        if(i >= mini(len1,len2) && line2[i] == NULL)
        {
            printf("-------#%d-#%d-------\n",i+1,maxi(len1,len2));
            for(int j = i ; j < maxi(len1,len2) ; j++)
            {
                printf("%s\n",line1[j]);
            }
            return;
        }
        else if(i >= mini(len1,len2) && line1[i] == NULL)
        {
            printf("-------#%d-#%d-------\n",i+1,maxi(len1,len2));
            for(int j = i ; j < maxi(len1,len2) ; j++)
            {
                printf("%s\n",line2[j]);
            }
            return;
        }
        else if(i < mini(len1,len2) && strcmp(line1[i],line2[i]) != 0)
        {
            printf("-------Line #%d-------\n",i+1);
            printf("%s\n%s\n",line1[i],line2[i]);
        }
    }
}
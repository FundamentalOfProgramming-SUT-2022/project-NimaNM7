//Nima Moazzen
//401106599

//Find is complete and debugged
//next step : Replace
//Tree and Auto indent are after that
//Arman will be ignored

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <windows.h>

int mylength , row , column , size , rowgone , columngone , indexfind , cntfind;

void getdirectory(char** , char*);
int gotodir(char**);
void back();
void copyfile(FILE* , FILE*);
int getcommands2(char*, char*, char*);
int gotopos1(FILE*,int , int , char); //For functions which don't need a second file (like copystr)
int gotopos2(FILE*, FILE*, int, int, char); //For functions which need second file and they have limits (like cutstr and removestr)
void gotopos3(FILE*, FILE*, int, int, char); //For functions which need a second file and they are for inserting without limits (like insertstr and pastestr)
void delete(char*,int);
void addtostr(char*,int,char);
int maxi(int,int);
int mini(int,int);
int filetostr(FILE*,char*,char*,char**);
int findpos(char*,char*,char*);
void findpos2(char*,char*,char*,int);
int* findpos3(char*,char*);
void getstr(char*);

void createfile();
void cat();
void insertfile();
void removestr();
void copytoclipboard(const char*);
void copystr();
void cutstr();
void pastestr();
void find();
void replace();
void grep();
void compare();
void closingpairs();


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

    //Replace
        if(strcmp(firstcommand,"replace") == 0)
        {
            getchar();
            scanf("%s",secondcommand);
            if(strcmp(secondcommand,"--str1") == 0)
            {
                invalid = 0;
                replace();
                continue;
            }
        }

    //Grep
        if(strcmp(firstcommand,"grep") == 0)
        {
            getchar();
            invalid = 0;
            grep();
            continue;
        }

    //Compare    
        if(strcmp(firstcommand,"compare") == 0)
        {
            getchar();
            invalid = 0;
            compare();
            continue;
        }
    
    // //Closing Pairs
    //     if(strcmp(firstcommand,"auto-indent") == 0)
    //     {
    //         getchar();
    //         invalid = 0;
    //         closingpairs();
    //         continue;
    //     }

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
        if(x == 10)
        {
            flag = 0;
            break;
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
            {
                step1[index-1] = '\0';
                flag = 0;
            }
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


void addtostr(char* str,int index,char c)
{
    for(int i = strlen(str)+1 ; i > index ; i--)
    {
        str[i] = str[i-1];
    }
    str[index] = c;
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

int filetostr(FILE* file,char* filename, char* str1, char** str2)
{
    int len = 0;
    char c;
    file = fopen(filename,"r");
    if(file == NULL)
    {
        printf("There is no file named %s\n",filename);
        return -1;
    }

    c = fgetc(file);
    int index = 0;
    while (c != EOF)
    {
        str1[index] = c;
        if(str1[index-1] == '\n' && str1[index] == '\n')
        {
            str1[index] = ' ';
            index++;
            str1[index] = '\n';
        }
        index++;
        c = fgetc(file);
    }

    char* mydelim = strtok(str1,"\n");
    for (int i = 0; mydelim != NULL; i++)
    {
        str2[i] = mydelim;
        mydelim = strtok(NULL,"\n");
        len++;
    }
    fclose(file);
    return len;
}

void getstr(char* mystr)
{
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
    }
    else
    {
        mystr[0] = first;
        scanf("%[^ ]s",mystr+1);
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

        getstr(mystr);

        char fourthcommand[30];

        scanf("%s",fourthcommand);

        if(strcmp(fourthcommand , "-pos") == 0 || strcmp(fourthcommand,"--pos") == 0)
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

int findpos(char* text,char* word,char* type) //for regular , count and byword (it returns the pos of first found string or number of found strings)
{
    int flag;
    cntfind = 0;
    for(indexfind = 0 ; indexfind < strlen(text) ; indexfind++)
    {
        if(text[indexfind] == word[0])
        {
            flag = 1;
            for(int j = 0 ; j < strlen(word) ; j++)
            {
                if(text[indexfind+j] != word[j])
                {
                    flag = 0 ;
                    break;
                }
            }
            if(flag == 1)
            {
                cntfind++;
                if(strcmp(type,"reg") == 0)
                    return indexfind;
            }
        }
    }
    if(strcmp(type ,"count") == 0)
        return cntfind;

    return -1;
}

void findpos2(char* text,char* word,char* type,int gobro) //for at and all (it doesnt return anything and has one more argument (for finding the repeats))
{
    int flag;
    cntfind = 0;
    for(indexfind = 0 ; indexfind < strlen(text) ; indexfind++)
    {
        if(text[indexfind] == word[0])
        {
            flag = 1;
            for(int j = 0 ; j < strlen(word) ; j++)
            {
                if(text[indexfind+j] != word[j])
                {
                    flag = 0 ;
                    break;
                }
            }
            if(flag == 1)
            {
                cntfind++;
                if(strcmp(type,"at") == 0 && cntfind == gobro)
                { 
                    printf("%d\n",indexfind);
                    return;
                }
                if(strcmp(type,"all") == 0)
                    printf("%d ",indexfind);

                if(strcmp(type,"byword") == 0) //for combination of all and byword
                {
                    int cntby = 0;
                    for(int i = 0 ; i < indexfind ; i++)
                    {
                        if(text[i] == ' ' || text[i] == '\n')
                            cntby++;                        
                    }
                    printf("%d ",cntby);
                }
                if(strcmp(type,"bywordat") == 0)
                {
                    int cntby = 0;
                    for(int i = 0 ; i < indexfind ; i++)
                    {
                        if(text[i] == ' ' || text[i] == '\n')
                            cntby++;                        
                    }
                    if(cntfind == gobro)
                    {
                        printf("%d\n",cntby);
                    }
                }
            }
        }
    }
    if(gobro > cntfind)
    {
        printf("Couldn't found your string %d times (%d found)\n",gobro,cntfind);
        return;
    }
}

int* findpos3(char* text,char* word) //for Replace , it puts all answers in an array
{
    int* answers = (int*)calloc(1000,sizeof(int));
    int flag, cnt = 0;
    for(int i = 0 ; i < strlen(text) ; i++)
    {
        if(text[i] == word[0])
        {
            flag = 1;
            for(int j = 0 ; j < strlen(word) ; j++)
            {
                if(text[i+j] != word[j])
                {
                    flag = 0;
                    break;
                }
            }
            if(flag == 1)
            {
                answers[cnt] = i;   
                cnt++;
            }
        }
    }
    if(cnt == 0)
        answers[0] = -1;

    return answers;
}

int get2ops()
{
    char last = getchar();
    if(last == ' ')
    {
        char last2 = getchar();
        if(last2 == '-')
            return 1;
    }
    return 0;
}

void find() 
{
    char mystr[1000] , thirdcommand[30] , text[10000];
    char c , dir[1000];
    char* mydir[10];

    getchar();
    getstr(mystr);

    scanf("%s",thirdcommand);
    if(strcmp(thirdcommand,"--file") == 0 || strcmp(thirdcommand,"-file") == 0)
    {
        getchar();
        getdirectory(mydir,dir);
    }

    for(int i = 0 ; i < strlen(mystr)-1 ; i++) //for handling "\*""
    {
        if(mystr[i] == '*' && mystr[i-1] == '\\')
            delete(mystr,i-1);
    }

    if(mystr[strlen(mystr)-1] == '*') //for handling wildcards like "nima*"
        mystr[strlen(mystr)-1] = '\0';
    
    if(mystr[0] == '*') //for handling wildcards like "*nima" (its not complete but better than nothing)
        delete(mystr,0);


    if(gotodir(mydir) == 0) return;
    FILE* myfile = fopen(mydir[mylength-1],"r");
    if(myfile == NULL) 
    {
        printf("There is no file named %s\n",mydir[mylength-1]);
        return;
    }
    int counter = 0;
    c = fgetc(myfile);
    while(c != EOF)
    {
        text[counter] = c;
        counter++;
        c = fgetc(myfile);
    }
    text[counter+1] = '\0';

    char last,mytype[30],secondtype[20];
    int gobro = 0;
    scanf("%s",mytype);

    if(strcmp(mytype,"at") == 0)
    {
        scanf("%d",&gobro);
        if(get2ops())
        {
            scanf("%s",secondtype);
            if(strcmp(secondtype,"byword") == 0)
            {
                findpos2(text,mystr,"bywordat",gobro);
                return;
            }
            if(strcmp(secondtype,"all") == 0)
            {
                printf("all and at cannot be combined\n");
                return;
            }
            if(strcmp(secondtype,"count") == 0)
            {
                printf("count and at cannot be combined\n");
                return;
            }
        }
        findpos2(text,mystr,"at",gobro);
        return;
    }
    else if(strcmp(mytype,"count") == 0)
    {
        printf("%d\n",findpos(text,mystr,"count"));
        return;
    }
    else if(strcmp(mytype,"all") == 0)
    {
        if(get2ops())
        {
            scanf("%s",secondtype);
            if(strcmp(secondtype,"byword") == 0)
            {
                findpos2(text,mystr,"byword",gobro);
                printf("\n");
                return;
            }
            if(strcmp(secondtype,"at") == 0)
            {
                printf("at and all cannot be combined\n");
                return;
            }
        }
        findpos2(text,mystr,"all",gobro);
        printf("\n");
        return;
    }
    else if(strcmp(mytype,"byword") == 0)
    {
        if(get2ops())
        {
            scanf("%s",secondtype);
            if(strcmp(secondtype,"all") == 0)
            {
                findpos2(text,mystr,"byword",gobro);
                printf("\n");
                return;
            }
            if(strcmp(secondtype,"at") == 0)
            {
                scanf("%d",&gobro);
                findpos2(text,mystr,"bywordat",gobro);
                return;
            }
        }
        int num;
        int k = findpos(text,mystr,"reg");
        if(k == -1) 
        {
            printf("%d\n",k);
            return;
        }
        for(int i = 0 ; i < k ; i++)
        {
            if(text[i] == ' ' || text[i] == '\n')
                num++;
        }
        printf("%d\n",num);
    }
    else if(strcmp(mytype,"reg") == 0)
    {
        printf("%d\n",findpos(text,mystr,"reg"));
        return;
    }
    back();
    memset(secondtype, '\0', strlen(secondtype));
    memset(mytype , '\0' , strlen(mytype));
}

void replace()
{
    char c,text[10000],str1[1000],str2[1000],dir[1000],thirdcommand[30],fourthcommand[30];
    char* mydir[1000];
    getchar();
    getstr(str1);
    scanf("%s",thirdcommand);
    if(strcmp(thirdcommand,"--str2") == 0 || strcmp(thirdcommand,"-str2") == 0)
    {
        getchar();
        getstr(str2);
        scanf("%s",fourthcommand);
    }
    else return;
    if(strcmp(fourthcommand,"--file") == 0 || strcmp(fourthcommand,"-file") == 0)
    {
        getchar();
        getdirectory(mydir,dir);
    }
    else return;

    // printf("just checking : str1 = %s , str2 = %s , thirdcommand = %s , fourthcommand = %s , mydir[0] = %s , filename = %s\n",str1,str2,thirdcommand,fourthcommand,mydir[0],mydir[mylength-1]);
    if(gotodir(mydir) == 0) return;
    FILE* file = fopen(mydir[mylength-1],"r");
    if(file == NULL)
    {
        printf("There is no file named \"%s\" in this folder!\n",mydir[mylength-1]);
        return;
    }
    int index = 0;
    c = fgetc(file);
    while(c != EOF)
    {
        text[index] = c;
        index++;
        c = fgetc(file);
    }
    text[index+1] = '\0';
    char mytype[10];
    scanf("%s",mytype);

    int* ans = findpos3(text,str1); //position of answers in an array
    if(ans[0] == -1) 
    {
        printf("Your string was not found\n");
        return;
    }
    fclose(file);
    file = fopen(mydir[mylength-1],"w");
    
    if(strcmp(mytype,"all") == 0)
    {
        
    }
    if(strcmp(mytype,"at") == 0)
    {
        int gobro;
        scanf("%d",&gobro);
        int ind = ans[gobro-1];
        for(int i = 0 ; i < ind ; i++)
        {
            fputc(text[i],file);
        }
        fprintf(file,str2);
        for(int i = ind + strlen(str1) ; text[i+1] != '\0' ; i++)
        {
            fputc(text[i],file);
        }
        printf("Replacing was succesfull\n");
        fclose(file);
        return;
    }
    if(strcmp(mytype,"reg") == 0)
    {
        int ind = ans[0];
        for(int i = 0 ; i < ind ; i++)
        {
            fputc(text[i],file);
        }
        fprintf(file,str2);
        for(int i = ind + strlen(str1) ; text[i+1] != '\0' ; i++)
        {
            fputc(text[i],file);
        }
        printf("Replacing was succesfull\n");
        fclose(file);
        return;
    }
    back();
}

void grep()
{
    char dir[1000] , text[10000], secondcommand[30] , mystr[1000] , filename[1000];
    char* mydir[100];
    char* lines[1000];
    int len;
    FILE* file;
    scanf("%s",secondcommand);
    if(strcmp(secondcommand,"--str") == 0) //without options
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
                if(mystr[i] == '/' && mystr[i-1] == ' ' && mystr[i-2] == '"')
                {
                    mystr[i-2] = '\0';
                    flag = 0;
                }
                i++;
            }
        }

        while (1)
        {
            // printf("before checking the inputs : mydir[0] = %s , mydir[1] = %s , lines[1] = %s , mystr = %s , len = %d\n",mydir[0],mydir[1],lines[1],mystr,len);
            getdirectory(mydir,dir);
            if(gotodir(mydir) == 0) return;
            strcpy(filename,mydir[mylength-1]);
            len = filetostr(file,filename,text,lines);

            // printf("after checking the inputs : mydir[0] = %s , mydir[1] = %s , filename = %s , lines[1] = %s , mystr = %s , len = %d\n",mydir[0],mydir[1],filename,lines[1],mystr,len);
            if(len == -1) return;
            
            for(int i = 0 ; i < len ; i++)
            {
                if(strstr(lines[i],mystr) != NULL)
                {
                    printf("%s : %s\n",filename,lines[i]);
                }
            }
            // filename[0] = '\0' , lines[0] = '\0' , filename[0] = '\0' , text[0] = '\0' , mydir[0] = '\0' , dir[0] = '\0';
            memset(mydir, '\0', sizeof(mydir));
            memset(lines, '\0', sizeof(lines));
            memset(filename, '\0', sizeof(filename));
            memset(dir, '\0', sizeof(dir));
            memset(text, '\0', sizeof(text));
            // printf("haji feshar chie %d %d %d %d %d\n",strlen(filename),strlen(filename),strlen(text),strlen(mydir),strlen(dir));
        }
    }
    else if(strcmp(secondcommand,"-c") == 0) //option "c"
    {
        int counter = 0;
        char thirdcommand[30];
        scanf("%s",thirdcommand);
        if(strcmp(thirdcommand,"--str") == 0)
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
                    if(mystr[i] == '/' && mystr[i-1] == ' ' && mystr[i-2] == '"')
                    {
                        mystr[i-2] = '\0';
                        flag = 0;
                    }
                    i++;
                }
            }

            while (1)
            {
                // printf("before checking the inputs : mydir[0] = %s , mydir[1] = %s , lines[1] = %s , mystr = %s , len = %d\n",mydir[0],mydir[1],lines[1],mystr,len);
                getdirectory(mydir,dir);
                if(gotodir(mydir) == 0) return;
                strcpy(filename,mydir[mylength-1]);
                len = filetostr(file,filename,text,lines);

                // printf("after checking the inputs : mydir[0] = %s , mydir[1] = %s , filename = %s , lines[1] = %s , mystr = %s , len = %d\n",mydir[0],mydir[1],filename,lines[1],mystr,len);
                if(len == -1) return;
                
                for(int i = 0 ; i < len ; i++)
                {
                    if(strstr(lines[i],mystr) != NULL)
                    {
                        counter++;
                    }
                }
                // filename[0] = '\0' , lines[0] = '\0' , filename[0] = '\0' , text[0] = '\0' , mydir[0] = '\0' , dir[0] = '\0';
                memset(mydir, '\0', sizeof(mydir));
                memset(lines, '\0', sizeof(lines));
                memset(filename, '\0', sizeof(filename));
                memset(dir, '\0', sizeof(dir));
                memset(text, '\0', sizeof(text));
                // printf("haji feshar chie %d %d %d %d %d\n",strlen(filename),strlen(filename),strlen(text),strlen(mydir),strlen(dir));
                printf("%d\n",counter);
            }
            
        }
    }
    else if(strcmp(secondcommand,"-l") == 0) //option "l"
    {
        int counter = 0;
        char thirdcommand[30];
        scanf("%s",thirdcommand);
        if(strcmp(thirdcommand,"--str") == 0)
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
                    if(mystr[i] == '/' && mystr[i-1] == ' ' && mystr[i-2] == '"')
                    {
                        mystr[i-2] = '\0';
                        flag = 0;
                    }
                    i++;
                }
            }

            while (1)
            {
                // printf("before checking the inputs : mydir[0] = %s , mydir[1] = %s , lines[1] = %s , mystr = %s , len = %d\n",mydir[0],mydir[1],lines[1],mystr,len);
                getdirectory(mydir,dir);
                if(gotodir(mydir) == 0) return;
                strcpy(filename,mydir[mylength-1]);
                len = filetostr(file,filename,text,lines);

                // printf("after checking the inputs : mydir[0] = %s , mydir[1] = %s , filename = %s , lines[1] = %s , mystr = %s , len = %d\n",mydir[0],mydir[1],filename,lines[1],mystr,len);
                if(len == -1) return;
                
                for(int i = 0 ; i < len ; i++)
                {
                    if(strstr(lines[i],mystr) != NULL)
                    {
                        printf("%s\n",filename);
                        break;
                    }
                }
                // filename[0] = '\0' , lines[0] = '\0' , filename[0] = '\0' , text[0] = '\0' , mydir[0] = '\0' , dir[0] = '\0';
                memset(mydir, '\0', sizeof(mydir));
                memset(lines, '\0', sizeof(lines));
                memset(filename, '\0', sizeof(filename));
                memset(dir, '\0', sizeof(dir));
                memset(text, '\0', sizeof(text));
                // printf("haji feshar chie %d %d %d %d %d\n",strlen(filename),strlen(filename),strlen(text),strlen(mydir),strlen(dir));
            }
            
        }
    }
}

void compare()
{
    char dir1[1000] , dir2[1000] ,text1[10000] , text2[10000];
    char* mydir1[100];
    char* mydir2[100];
    char* line1[1000];
    char* line2[1000];
    FILE* file1;
    FILE* file2;
    int len1 , len2;

    getdirectory(mydir1,dir1);

    if(gotodir(mydir1) == 0) return;
    
    len1 = filetostr(file1,mydir1[mylength-1],text1,line1);

    getdirectory(mydir2,dir2);
    if(gotodir(mydir2) == 0) return;
    len2 = filetostr(file2,mydir2[mylength-1],text2,line2);

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
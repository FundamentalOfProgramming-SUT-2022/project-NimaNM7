#include <curses.h>
#include "test7.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//it doesn't work

void openfile(char* text,char* filename)
{   
    char* mydir[100];
    char dir[1000];
    getdirectory(mydir,dir);
    gotodir(mydir);
    strcpy(filename,mydir[mylength-1]);
    // printw("filename is %s\n",filename);
    
    //opening file and puting its text in an array named "text"
    FILE* file = fopen(filename,"r");
    int cnt = 0;
    char c = fgetc(file);
    while (c != EOF)
    {
        text[cnt] = c;
        cnt++;
        c = fgetc(file);
    }
    text[cnt+1] = '\0';
}


int main()
{
    initscr();
    cbreak();
    keypad(stdscr,TRUE);
    start_color();
    WINDOW* upwin = newwin(3,120,0,20);
    WINDOW* mainwin = newwin(40,120,3,20);
    WINDOW* downwin = newwin(3,120,43,20);
    refresh();
    box(upwin,0,20);
    box(mainwin,3,20);
    box(downwin,43,20);
    wborder(upwin,(int)'|',(int)'|',(int)'-',(int)'-',(int)'.',(int)'.',(int)'.',(int)'.');
    wborder(mainwin,(int)'|',(int)'|',(int)' ',(int)' ',(int)'.',(int)'.',(int)'.',(int)'.');
    wborder(downwin,(int)'|',(int)'|',(int)'-',(int)'-',(int)'.',(int)'.',(int)'.',(int)'.');
    wrefresh(upwin);
    wrefresh(mainwin);
    wrefresh(downwin);

    move(44,21);

       
    char* mydir[100];
    char c,dir[1000];

    while(1)
    {
        int cnt = 0;
        cbreak();
        char command[30] = { 0 } , filename[100] = { 0 };
        //getting the command

        char c = getch();
        while(c != ' ') 
        {
            if(c == EOF || c == '$') return 0;
            command[cnt] = c;
            cnt++;
            c = getch();
        }

        if(strcmp(command,":end") == 0) break; //breaking 

        if(strcmp(command,":open") == 0) //open command
        {
            char text[10000] = { 0 };
            int saved = 0; 
            int mode = 0; 
            
            openfile(text,filename);
            mvwprintw(mainwin,1,1,text);  //printing it on the screen
            wclear(downwin);
            move(3,20);
            
            refresh();
            if(saved == 0) 
            {
                init_pair(7,COLOR_CYAN,COLOR_BLACK); 
                attron(COLOR_PAIR(7) | A_BLINK);
                mvwprintw(upwin,1,1,"%s (+)",filename);
                attroff(COLOR_PAIR(7) | A_BLINK);
            } 
                
            mvwprintw(upwin,1,60,"Normal");
        
            wrefresh(upwin);
            wrefresh(mainwin);
            wrefresh(downwin);
        }
    }
    getch();
    endwin();
}
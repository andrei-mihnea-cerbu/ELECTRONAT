#ifndef ERROR_PANELS_MAIN_MENU_H_INCLUDED
#define ERROR_PANELS_MAIN_MENU_H_INCLUDED

#include <windows.h>

//Andrei CERBU pana jos

void succes_panel_main_menu(int W, int H){
    int width=W/4,height=H/4;
    POINT cursorPos;
    bool click;
    char text[]="Loading\0";
    int k=4, poz=8, timp=0;

    int panel=initwindow(width,height,"Loading panel",W/3,H/3,0,0);


    while(k){
        settextstyle(COMPLEX_FONT,0,width/123);
        outtextxy(width/2-width/5,height/3+height/20,text);
        strcat(text,".");
        --k;
        delay(1500-timp);
        timp+=500;
    }
    closegraph(panel);

}


void error_code_main_menu(int W, int H, int error){
    int width=W/4,height=H/4;
    POINT cursorPos;
    bool click; char c;

    int panel=initwindow(width,height,"Error",W/3,H/3,0,0);

    //first message
    if(error==-1){
        settextstyle(COMPLEX_FONT,0,width/160);
        outtextxy(width/6,height/3+height/20,"Error opening project");
    }
    else if(error==-2){
        settextstyle(COMPLEX_FONT,0,width/160);
        outtextxy(width/6+width/35,height/3+height/20,"Incorrect file type");
    }

    //second message
    settextstyle(COMPLEX_FONT,0,width/213);
    outtextxy(width/4+width/15,height/2,"Please try again");

    //button for exit
    rectangle(width/2-width/10,height/2+height/8,width/2+width/10,height/2+height/4);
    settextstyle(COMPLEX_FONT,0,width/213);
    outtextxy(width/2-width/20,height/2+height/7,"Back");

    while(true){
        GetCursorPos(&cursorPos);
        ScreenToClient(GetForegroundWindow(), &cursorPos);
        click=ismouseclick(WM_LBUTTONDOWN);
        bool menu=0;
        if((cursorPos.x>width/2-width/10&&cursorPos.x<width/2+width/10)&&(cursorPos.y>height/2+height/8&&cursorPos.y<height/2+height/4))
            menu=1;
        if(click&&menu){
            closegraph(panel);
            break;
        }
        if(kbhit()){
            c=getch();
            if(c==13){
                closegraph(panel);
                break;
            }
        }
    }
}

#endif // ERROR_PANELS_MAIN_MENU_H_INCLUDED

#ifndef STARTUP_PAGE_H_INCLUDED
#define STARTUP_PAGE_H_INCLUDED

#include "open_save.h"
#include "functii_auxiliare.h"

//Andrei CERBU pana jos

void background_image(int W, int H, char*current_path){
    readimagefile(path_for_images("bg_main_menu.jpg",current_path),0,0,W,H);
}

void create_panels_startup_page(int W, int H, float R){
    setlinestyle(SOLID_LINE,0,7);
    setcolor(WHITE);
    rectangle(W/6,H/4,W/6+R*H/6,H/4+R*H/6);//upper left
    rectangle(W/3,H/4,W/3+R*H/6,H/4+R*H/6);//upper right
    rectangle(W/6,3*H/4-R*H/6,W/6+R*H/6,3*H/4);//down left
    rectangle(W/3,3*H/4-R*H/6,W/3+R*H/6,3*H/4);//down right
}

void create_texts_startup_page(int W, int H, float R){
    setcolor(WHITE);
    settextstyle(COMPLEX_FONT,0,W/240);
    outtextxy(W/2+W/20,H/2-H/26,"ElectronAT");
    settextstyle(COMPLEX_FONT,0,W/450);
    outtextxy(W/2-W/22,H/30,"MAIN MENU");
    setlinestyle(SOLID_LINE,0,4); setcolor(WHITE);
    line(W/2-W/20,H/15,W/2+W/20,H/15);
}

void create_icons_startup_page(int W, int H, char* current_path){
    //!"New Project" icon

    //rectangle
    setlinestyle(SOLID_LINE,0,4);
    setcolor(BLACK);
    rectangle(W/5,H/3-H/17,W/6+W/14,H/3+H/20);
    //plus sign
    setcolor(YELLOW);
    line(W/5-W/500,H/3-H/14,W/5-W/500,H/3-H/20);
    line(W/5-W/150,H/3-H/16,W/5+W/300,H/3-H/16);
    readimagefile(path_for_images("patrat_stang_sus.jpg",current_path),W/5,H/3-H/17,W/6+W/14,H/3+H/20);

    //!"Open Project" icon

    //rectangle
    setlinestyle(SOLID_LINE,0,4);
    setcolor(BLACK);
    rectangle(W/3+W/80,H/3-H/32,W/3+W/12,H/3+H/23);
    readimagefile(path_for_images("patrat_dreapta_sus_alb.jpg",current_path),W/3+W/80,H/3-H/32,W/3+W/12,H/3+H/23);

    //arrow
    //base
    setcolor(BLACK);
    line(W/3+W/23,H/3,W/3+W/19,H/3);//base
    line(W/3+W/23,H/3,W/3+W/23,H/3-H/25);//upleft
    line(W/3+W/19,H/3,W/3+W/19,H/3-H/25);//upright
    readimagefile(path_for_images("patrat_dreapta_sus_galben.jpg",current_path),W/3+W/23,H/3-H/25,W/3+W/19,H/3);

    //fill the arrow with yellow lines
    //on width
    setcolor(YELLOW);
    line(W/3+W/26,H/3-H/24,W/3+W/18+W/500,H/3-H/24);
    line(W/3+W/25,H/3-H/23,W/3+W/19+W/300,H/3-H/23);
    line(W/3+W/25-W/1290,H/3-H/22,W/3+W/19+W/235,H/3-H/22);
    line(W/3+W/25+W/1290,H/3-H/21,W/3+W/18,H/3-H/21);
    line(W/3+W/25+W/500,H/3-H/20,W/3+W/18-W/500,H/3-H/20);
    line(W/3+W/23,H/3-H/19-H/1000,W/3+W/19,H/3-H/19-H/1000);
    line(W/3+W/23,H/3-H/18+H/700,W/3+W/19,H/3-H/18+H/700);
    line(W/3+W/23+W/500,H/3-H/18,W/3+W/19-W/1000,H/3-H/18);
    line(W/3+W/22,H/3-H/17,W/3+W/20,H/3-H/17);
    line(W/3+W/21,H/3-H/17,W/3+W/20,H/3-H/17);
    line((W/3+W/27+W/3+W/17)/2,H/3-H/25,(W/3+W/27+W/3+W/17)/2,H/3-H/25);
    //on hight
    line((W/3+W/27+W/3+W/17)/2,H/4+H/45,(W/3+W/27+W/3+W/17)/2,H/3-H/25);
    line((W/3+W/27+W/3+W/17)/2-W/500,H/4+H/45,(W/3+W/27+W/3+W/17)/2,H/3-H/25);
    line((W/3+W/27+W/3+W/17)/2+W/600,H/4+H/48,(W/3+W/27+W/3+W/17)/2,H/3-H/25);
    //arrow sides
    setcolor(BLACK);
    line(W/3+W/27,H/3-H/25,W/3+W/17,H/3-H/25);//triangebase
    line((2*W/3+W/27+W/17)/2,H/4+H/60,W/3+W/27,H/3-H/25);//triangleleftside
    line((2*W/3+W/27+W/17)/2,H/4+H/60,W/3+W/17,H/3-H/25);//trianglerightside

    //!"Info" icon

    setlinestyle(SOLID_LINE,0,7);
    setcolor(YELLOW);
    arc((W/3+H/6)/2,3*H/4-H/9,0,90,W/50);
    arc((W/3+H/6)/2,3*H/4-H/9,90,160,W/50);
    arc((W/3+H/6)/2,3*H/4-H/9,270,0,W/50);
    line(W/5+W/80,3*H/4-H/13,W/5+W/80,3*H/4-H/25);
    setlinestyle(SOLID_LINE,0,3);
    circle(W/5+W/80,3*H/4-H/50,5);

    //!"Exit" Icon

    setlinestyle(SOLID_LINE,0,7);
    setcolor(YELLOW);
    line(W/3+W/50,3*H/4-H/7,W/3+W/13,3*H/4-H/40);
    line(W/3+W/50,3*H/4-H/40,W/3+W/13,3*H/4-H/7);

}

void draw_main_menu(int W, int H, float R, char *current_path){
    background_image(W,H,current_path);
    create_panels_startup_page(W,H,R);
    create_icons_startup_page(W,H,current_path);
    create_texts_startup_page(W,H,R);
}

#endif // STARTUP_PAGE_H_INCLUDED

#ifndef WORKPLACE_PAGE_H_INCLUDED
#define WORKPLACE_PAGE_H_INCLUDED

#include "drawing_components.h"
#include "stare_table.h"
#include "zoom_rotate_fader_workplace.h"
#include "functii_auxiliare.h"

void create_workbench_workplace(int W, int H, float R){
    setlinestyle(SOLID_LINE,0,0);
    setcolor(GREEN);

    rectangle(W/8*R,H/12*R,7*W/8*R,11*H/12*R);
}

//Tudor ILADE && Andrei Cerbu
void create_top_menu_workplace(int W, int H, float R, int width_rectangle, int height_rectangle){
    setlinestyle(SOLID_LINE,0,3);
    setcolor(WHITE);

    rectangle(width_rectangle*3*R,0,width_rectangle*4*R, height_rectangle*R);
    rectangle(width_rectangle*4*R,0,width_rectangle*5*R, height_rectangle*R);
    rectangle(width_rectangle*5*R,0,width_rectangle*6*R, height_rectangle*R);
    rectangle(width_rectangle*6*R,0,width_rectangle*7*R, height_rectangle*R);
    rectangle(width_rectangle*7*R,0,width_rectangle*8*R, height_rectangle*R);
    rectangle(width_rectangle*8*R,0,width_rectangle*9*R, height_rectangle*R);
}

void create_left_menu_workplace(int W, int H, float R, int width_rectangle, int height_rectangle){
    setlinestyle(SOLID_LINE,0,3);
    setcolor(WHITE);

    rectangle(0,(height_rectangle*3)*R,width_rectangle*R,(height_rectangle*4)*R);
    rectangle(0,(height_rectangle*4)*R,width_rectangle*R,(height_rectangle*5)*R);
    rectangle(0,(height_rectangle*5)*R,width_rectangle*R,(height_rectangle*6)*R);
    rectangle(0,(height_rectangle*6)*R,width_rectangle*R,(height_rectangle*7)*R);
    rectangle(0,(height_rectangle*7)*R,width_rectangle*R,(height_rectangle*8)*R);
    rectangle(0,(height_rectangle*8)*R,width_rectangle*R,(height_rectangle*9)*R);
    rectangle(0,(height_rectangle*9)*R,width_rectangle*R,(height_rectangle*10)*R);
    rectangle(0,(height_rectangle*10)*R,width_rectangle*R,(height_rectangle*11)*R);
    rectangle(0,(height_rectangle*11)*R,width_rectangle*R,(height_rectangle*12)*R);
}

void create_right_menu_workplace(int W, int H, float R, int width_rectangle, int height_rectangle){
    setlinestyle(SOLID_LINE,0,3);
    setcolor(WHITE);

    rectangle((W-width_rectangle)*R,(height_rectangle*2)*R,W,(height_rectangle*3)*R);
    rectangle((W-width_rectangle)*R,(height_rectangle*3)*R,W,(height_rectangle*4)*R);
    rectangle((W-width_rectangle)*R,(height_rectangle*4)*R,W,(height_rectangle*5)*R);
    rectangle((W-width_rectangle)*R,(height_rectangle*5)*R,W,(height_rectangle*6)*R);
    rectangle((W-width_rectangle)*R,(height_rectangle*6)*R,W,(height_rectangle*7)*R);
    rectangle((W-width_rectangle)*R,(height_rectangle*7)*R,W,(height_rectangle*8)*R);
}

void create_undo_redo_menu_workplace(int W, int H, float R, int width_rectangle, int height_rectangle){
    setlinestyle(SOLID_LINE,0,2);
    setcolor(WHITE);

    //Undo
    arc((width_rectangle+2*width_rectangle/9)/2*R,14.6*height_rectangle*R,250,170,width_rectangle/5);
    line((width_rectangle+2*width_rectangle/9)/2*R-width_rectangle/5,14.6*height_rectangle*R,(width_rectangle+2*width_rectangle/9)/2*R-width_rectangle/4,14.3*height_rectangle*R);
    line((width_rectangle+2*width_rectangle/9)/2*R-width_rectangle/5,14.6*height_rectangle*R,(width_rectangle+2*width_rectangle/9)/2*R-width_rectangle/30,14.4*height_rectangle*R);

    //Redo
    arc((16*width_rectangle/9+width_rectangle)/2,14.6*height_rectangle*R,10,270,width_rectangle/5);
    line((16*width_rectangle/9+width_rectangle)/2+width_rectangle/5,14.6*height_rectangle*R,(16*width_rectangle/9+width_rectangle)/2-width_rectangle/30,14.4*height_rectangle*R);
    line((16*width_rectangle/9+width_rectangle)/2+width_rectangle/5,14.6*height_rectangle*R,(16*width_rectangle/9+width_rectangle)/2+width_rectangle/4,14.25*height_rectangle*R);
}

void create_drawing_line_type_menu_workplace(int W, int H, int R, int width_rectangle, int height_rectangle, int color){
    setcolor(color);
    setlinestyle(SOLID_LINE,0,1);

    rectangle((W-width_rectangle)*R,(height_rectangle*11.1)*R,W-width_rectangle/9,(height_rectangle*12.1)*R);
    rectangle((W-width_rectangle)*R,(height_rectangle*12.1)*R,W-width_rectangle/9,(height_rectangle*13.1)*R);
    rectangle((W-width_rectangle)*R,(height_rectangle*13.1)*R,W-width_rectangle/9,(height_rectangle*14.1)*R);
    rectangle((W-width_rectangle)*R,(height_rectangle*14.1)*R,W-width_rectangle/9,(height_rectangle*15.1)*R);
}


//Andrei Cerbu
void create_zoom_rotate_panel_workplace(int W, int H, int R, int width_rectangle, int height_rectangle, int color){
    setcolor(color);
    setlinestyle(SOLID_LINE,0,0);

    fader rrotate;

    rrotate.Centru.x=(W-width_rectangle)*R+4*W/225;
    rrotate.Centru.y=((height_rectangle*16.95)+(height_rectangle*19.7))*R/2;

    //desenare dreptunghiurile exterioare
    rectangle((W-width_rectangle)*R,(height_rectangle*16.1)*R,(W-width_rectangle)*R+4*W/225*2,(height_rectangle*20.1)*R);
    rectangle((W-width_rectangle)*R+4*W/225*3,(height_rectangle*16.1)*R,W-width_rectangle/9,(height_rectangle*20.1)*R);

    //desenare glisator rotate
    rectangle(rrotate.Centru.x-W/140,rrotate.Centru.y-H/70,rrotate.Centru.x+W/140,rrotate.Centru.y+H/70);
    line((W-width_rectangle)*R+4*W/225,(height_rectangle*16.5)*R,(W-width_rectangle)*R+4*W/225,(height_rectangle*19.7)*R);

    //desenare glisator zoom
    fader zzom;
    zzom.Centru.x=(W-width_rectangle)*R+4*W/225*4;
    zzom.Centru.y=((height_rectangle*16.95)+(height_rectangle*19.7))*R/2;

    rectangle(zzom.Centru.x-W/140,zzom.Centru.y-H/70,zzom.Centru.x+W/140,zzom.Centru.y+H/70);
    line((W-width_rectangle)*R+4*W/225*4,(height_rectangle*16.5)*R,(W-width_rectangle)*R+4*W/225*4,(height_rectangle*19.7)*R);
}

//Tudor ILADE
void draw_black_zoom_rotate_panel(int W, int H, int R, int width_rectangle, int height_rectangle, int id){
    if(id == 1)
    {
        setcolor(BLACK);
        fader rrotate;
        rrotate.Centru.x=(W-width_rectangle)*R+4*W/225;
        rrotate.Centru.y=((height_rectangle*16.95)+(height_rectangle*19.7))*R/2;
        rectangle(rrotate.Centru.x-W/140,rrotate.Centru.y-H/70,rrotate.Centru.x+W/140,rrotate.Centru.y+H/70);
        line((W-width_rectangle)*R+4*W/225,(height_rectangle*16.5)*R,(W-width_rectangle)*R+4*W/225,(height_rectangle*19.7)*R);

    }
    else if(id == 2)
    {
        setcolor(BLACK);
        fader zzom;
        zzom.Centru.x=(W-width_rectangle)*R+4*W/225*4;
        zzom.Centru.y=((height_rectangle*16.95)+(height_rectangle*19.7))*R/2;

        rectangle(zzom.Centru.x-W/140,zzom.Centru.y-H/70,zzom.Centru.x+W/140,zzom.Centru.y+H/70);
        line((W-width_rectangle)*R+4*W/225*4,(height_rectangle*16.5)*R,(W-width_rectangle)*R+4*W/225*4,(height_rectangle*19.7)*R);

    }
}

int betweenBars(int W, int H, int R, int width_rectangle, int height_rectangle, int x, int y, int id){
    if(x>(W-width_rectangle)*R && x<(W-width_rectangle)*R+4*W/225*2 && y>height_rectangle*16.1*R && y<(height_rectangle*20.1)*R && id == 1)
        return 1;
    if(x>(W-width_rectangle)*R+4*W/225*3 && x<W-width_rectangle/9 && y>height_rectangle*16.1*R && y<(height_rectangle*20.1)*R && id == 2)
        return 2;
    return 0;
}

//Andrei CERBU pana jos
void print_text_on_workplace_page(int W, int H, int R, int width_rectangle, int height_rectangle, int rect_w, int rect_h, char* str){
    int text_w=textwidth(str);
    int text_h=textheight(str);

    float x=(width_rectangle+(rect_w-text_w)/2);
    float y=(height_rectangle+(rect_h-text_h)/2);

    outtextxy(x,y,str);
}

void create_text_workplace(int W, int H, float R){
    int width_rectangle, height_rectangle, FONT;

    if(W<=1920)
        FONT=1;
    else FONT=3;

    settextstyle(EUROPEAN_FONT,HORIZ_DIR,FONT);
    setcolor(WHITE);

    ///TOP TEXT

    width_rectangle=W/12;
    height_rectangle=H/24;

    print_text_on_workplace_page(W,H,R,width_rectangle*3*R,0,width_rectangle,height_rectangle,"Start panel");
    print_text_on_workplace_page(W,H,R,width_rectangle*4*R,0,width_rectangle,height_rectangle,"Open");
    print_text_on_workplace_page(W,H,R,width_rectangle*5*R,0,width_rectangle,height_rectangle,"Save");
    print_text_on_workplace_page(W,H,R,width_rectangle*6*R,0,width_rectangle,height_rectangle,"Save as");
    print_text_on_workplace_page(W,H,R,width_rectangle*7*R,0,width_rectangle,height_rectangle,"Help");
    print_text_on_workplace_page(W,H,R,width_rectangle*8*R,0,width_rectangle,height_rectangle,"Reset");

    ///RIGHT TEXT

    width_rectangle = W/9;
    height_rectangle = H/16;

    print_text_on_workplace_page(W,H,R,(W-width_rectangle)*R,(height_rectangle*2),width_rectangle,height_rectangle,"Check integrity");
    print_text_on_workplace_page(W,H,R,(W-width_rectangle)*R,(height_rectangle*3),width_rectangle,height_rectangle,"Zoom/Rotate");
    print_text_on_workplace_page(W,H,R,(W-width_rectangle)*R,(height_rectangle*4),width_rectangle,height_rectangle,"Delete comp.");
    print_text_on_workplace_page(W,H,R,(W-width_rectangle)*R,(height_rectangle*5),width_rectangle,height_rectangle,"Delete link");
    print_text_on_workplace_page(W,H,R,(W-width_rectangle)*R,(height_rectangle*6),width_rectangle,height_rectangle,"Update comp.");
    print_text_on_workplace_page(W,H,R,(W-width_rectangle)*R,(height_rectangle*7),width_rectangle,height_rectangle,"Line type");
}
void create_bulb(int W, int H, int R, int width_rectangle, int height_rectangle, int color){
    /*setfillstyle(SOLID_FILL,color);
    circle(W-width_rectangle/2,height_rectangle,W/100);
    floodfill(W-width_rectangle/2,height_rectangle,WHITE);

    line(W-width_rectangle/2-width_rectangle/20,height_rectangle+W/120,W-width_rectangle/2-width_rectangle/20,1.6*(height_rectangle)*R);
    line(W-width_rectangle/2+width_rectangle/20,height_rectangle+W/120,W-width_rectangle/2+width_rectangle/20,1.6*(height_rectangle)*R);

    line((W-width_rectangle/2-width_rectangle/20)*R,1.6*(height_rectangle)*R,(W-width_rectangle/2+width_rectangle/20)*R,1.6*(height_rectangle)*R);*/
}


void messages_log_panel(char* str, int W, int H, float R, int width_rectangle, int height_rectangle){

    setlinestyle(SOLID_LINE,0,2);
    setcolor(WHITE);

    rectangle(3.5*width_rectangle*R,15*height_rectangle*R,5.5*width_rectangle*R,15.7*height_rectangle*R);

    int text_w=textwidth(str);
    int text_h=textheight(str);

    int rect_w=width_rectangle*R;
    int rect_h=0.7*height_rectangle*R;

    float x=(4*width_rectangle+(rect_w-text_w)/2)*R;
    float y=(15*height_rectangle+(rect_h-text_h)/2)*R;

    outtextxy(x,y,str);
}

void draw_components_left_panel(int W, int H, float R){
    int X=W/8,Y=H/16;

    struct componenta CMP[30];

    construct_resistor(W/10,H/16,R,7*X/16,7*Y/2,0,1.0,CMP);
    draw_component(CMP,6,WHITE);

    construct_fuse(W/10,H/16,R,7*X/16,9*Y/2,0,1.0,CMP);
    draw_component(CMP,5,WHITE);

    construct_electrical_cell(W/10,H/16,R,7*X/16,11*Y/2,0,1.0,CMP);
    draw_component(CMP,7,WHITE);

    construct_dioda(W/10,H/16,R,7*X/16,13*Y/2,0,1.0,CMP);
    draw_component(CMP,9,WHITE);

    construct_ampermeter(W/10,H/16,R,7*X/16,15*Y/2,0,1.0,CMP);
    draw_component(CMP,12,WHITE);

    construct_voltmeter(W/10,H/16,R,7*X/16,17*Y/2,0,1.0,CMP);
    draw_component(CMP,10,WHITE);

    construct_capacitor(W/10,H/16,R,7*X/16,19*Y/2,0,1.0,CMP);
    draw_component(CMP,7,WHITE);

    construct_bulb(W/10,H/16,R,7*X/16,21*Y/2,0,1.0,CMP);
    draw_component(CMP,8,WHITE);

    construct_transistor(W/10,H/16,R,7*X/16,23*Y/2,0,1.0,CMP);
    draw_component(CMP,11,WHITE);
}

void drawing_line_type(int W, int H, float R, int width_rectangle, int height_rectangle, int color){
    setcolor(color);
    setlinestyle(SOLID_LINE,0,0);

    drawLine((W-width_rectangle)*R+width_rectangle/5,height_rectangle*11.1+height_rectangle/6,W-width_rectangle/5,height_rectangle*12.1-height_rectangle/6,color,1);
    drawLine((W-width_rectangle)*R+width_rectangle/5,height_rectangle*12.1+height_rectangle/6,W-width_rectangle/5,height_rectangle*13.1-height_rectangle/6,color,4);
    drawLine((W-width_rectangle)*R+width_rectangle/5,height_rectangle*13.1+height_rectangle/6,W-width_rectangle/5,height_rectangle*14.1-height_rectangle/6,color,3);
    drawLine((W-width_rectangle)*R+width_rectangle/5,height_rectangle*14.1+height_rectangle/6,W-width_rectangle/5,height_rectangle*15.1-height_rectangle/6,color,2);
}

void draw_images(int W, int H, float R, char *current_path)
{
    readimagefile(path_for_images("icon.jpg",current_path),W/70+W/70,W/70+W/70,W/15+W/70,W/15+W/70);

    readimagefile(path_for_images("becstins.jpg",current_path),W-W/9+W/34,0.2*H/16,W-W/6.5+W/34,1.6*H/16);
}

void draw_working_table(int W, int H, float R, char *current_path){
    cleardevice();

    draw_images(W,H,R,current_path);

    create_workbench_workplace(W,H,R);
    create_top_menu_workplace(W,H,R,W/12,H/24);
    create_left_menu_workplace(W,H,R,W/9,H/16);
    create_right_menu_workplace(W,H,R,W/9,H/16);
    create_undo_redo_menu_workplace(W,H,R,W/18,H/16);
    create_zoom_rotate_panel_workplace(W,H,R,W/10,H/22,WHITE);
    create_text_workplace(W,H,R);
    create_bulb(W,H,R,W/9,H/16,WHITE);

    messages_log_panel("Logs",W,H,R,W/9,H/16);

    draw_components_left_panel(W,H,R);
}

#endif // WORKPLACE_PAGE_H_INCLUDED

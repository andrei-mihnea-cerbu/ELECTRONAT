#ifndef CHANGE_COLOR_PANEL_H_INCLUDED
#define CHANGE_COLOR_PANEL_H_INCLUDED

#include "startup_page.h"
#include "workplace_page.h"


//Andrei CERBU pana jos

void change_color_icon_startup_page(int var, int W, int H, int R)
{
    switch(var)
    {
    case 1:
        setlinestyle(SOLID_LINE,0,7);
        setcolor(RED);
        rectangle(W/6,H/4,W/6+R*H/6,H/4+R*H/6);
        break;
    case 2:
        setlinestyle(SOLID_LINE,0,7);
        setcolor(RED);
        rectangle(W/3,H/4,W/3+R*H/6,H/4+R*H/6);
        break;
    case 3:
        setlinestyle(SOLID_LINE,0,7);
        setcolor(RED);
        rectangle(W/6,3*H/4-R*H/6,W/6+R*H/6,3*H/4);
        break;
    case 4:
        setlinestyle(SOLID_LINE,0,7);
        setcolor(RED);
        rectangle(W/3,3*H/4-R*H/6,W/3+R*H/6,3*H/4);
        break;
    case 0:
        setcolor(WHITE);
        create_panels_startup_page(W,H,R);
        break;
    }
}

void change_color_icon_top_menu_workplace_page(int W, int H, int R, int val){
    int width_rectangle = W/12;
    int height_rectangle = H/24;

    switch(val){
    case 1:
        setlinestyle(SOLID_LINE,0,3);
        setcolor(RED);
        rectangle(3*width_rectangle*R,0,4*width_rectangle*R, height_rectangle*R);
        break;
    case 2:
        setlinestyle(SOLID_LINE,0,3);
        setcolor(RED);
        rectangle(4*width_rectangle*R,0,5*width_rectangle*R, height_rectangle*R);
        break;
    case 3:
        setlinestyle(SOLID_LINE,0,3);
        setcolor(RED);
        rectangle(5*width_rectangle*R,0,6*width_rectangle*R, height_rectangle*R);
        break;
    case 4:
        setlinestyle(SOLID_LINE,0,3);
        setcolor(RED);
        rectangle(6*width_rectangle*R,0,7*width_rectangle*R, height_rectangle*R);
        break;
    case 5:
        setlinestyle(SOLID_LINE,0,3);
        setcolor(RED);
        rectangle(7*width_rectangle*R,0,8*width_rectangle*R, height_rectangle*R);
        break;
    case 6:
        setlinestyle(SOLID_LINE,0,3);
        setcolor(RED);
        rectangle(8*width_rectangle*R,0,9*width_rectangle*R, height_rectangle*R);
        break;
    case 0:
        setlinestyle(SOLID_LINE,0,3);
        setcolor(WHITE);
        create_top_menu_workplace(W,H,R,W/12,H/24);
        break;
    }
}

void change_color_icon_left_menu_workplace_page(int W, int H, int R, int val){
    int width_rectangle = W/9;
    int height_rectangle = H/16;

    switch(val){
    case 1:
        setlinestyle(SOLID_LINE,0,2);
        setcolor(RED);
        rectangle(0,(height_rectangle*3)*R,width_rectangle*R,(height_rectangle*4)*R);
        break;
    case 2:
        setlinestyle(SOLID_LINE,0,2);
        setcolor(RED);
        rectangle(0,(height_rectangle*4)*R,width_rectangle*R,(height_rectangle*5)*R);
        break;
    case 3:
        setlinestyle(SOLID_LINE,0,2);
        setcolor(RED);
        rectangle(0,(height_rectangle*5)*R,width_rectangle*R,(height_rectangle*6)*R);
        break;
    case 4:
        setlinestyle(SOLID_LINE,0,2);
        setcolor(RED);
        rectangle(0,(height_rectangle*6)*R,width_rectangle*R,(height_rectangle*7)*R);
        break;
    case 5:
        setlinestyle(SOLID_LINE,0,2);
        setcolor(RED);
        rectangle(0,(height_rectangle*7)*R,width_rectangle*R,(height_rectangle*8)*R);
        break;
    case 6:
        setlinestyle(SOLID_LINE,0,2);
        setcolor(RED);
        rectangle(0,(height_rectangle*8)*R,width_rectangle*R,(height_rectangle*9)*R);
        break;
    case 7:
        setlinestyle(SOLID_LINE,0,2);
        setcolor(RED);
        rectangle(0,(height_rectangle*9)*R,width_rectangle*R,(height_rectangle*10)*R);
        break;
    case 8:
        setlinestyle(SOLID_LINE,0,2);
        setcolor(RED);
        rectangle(0,(height_rectangle*10)*R,width_rectangle*R,(height_rectangle*11)*R);
        break;
    case 9:
        setlinestyle(SOLID_LINE,0,2);
        setcolor(RED);
        rectangle(0,(height_rectangle*11)*R,width_rectangle*R,(height_rectangle*12)*R);
        break;
    case 0:
        setlinestyle(SOLID_LINE,0,3);
        setcolor(WHITE);
        create_left_menu_workplace(W,H,R,W/9,H/16);
        break;
    }
}

void change_color_icon_right_menu_workplace_page(int W, int H, int R, int val){
    int width_rectangle = W/9;
    int height_rectangle = H/16;

    switch(val){
    case 1:
        setlinestyle(SOLID_LINE,0,3);
        setcolor(RED);
        rectangle((W-width_rectangle)*R,2*height_rectangle*R,W,3*height_rectangle*R);
        break;
    case 2:
        setlinestyle(SOLID_LINE,0,3);
        setcolor(RED);
        rectangle((W-width_rectangle)*R,3*height_rectangle*R,W,4*height_rectangle*R);
        break;
    case 3:
        setlinestyle(SOLID_LINE,0,3);
        setcolor(RED);
        rectangle((W-width_rectangle)*R,4*height_rectangle*R,W,5*height_rectangle*R);
        break;
    case 4:
        setlinestyle(SOLID_LINE,0,3);
        setcolor(RED);
        rectangle((W-width_rectangle)*R,5*height_rectangle*R,W,6*height_rectangle*R);
        break;
    case 5:
        setlinestyle(SOLID_LINE,0,3);
        setcolor(RED);
        rectangle((W-width_rectangle)*R,6*height_rectangle*R,W,7*height_rectangle*R);
        break;
    case 6:
        setlinestyle(SOLID_LINE,0,3);
        setcolor(RED);
        rectangle((W-width_rectangle)*R,7*height_rectangle*R,W,8*height_rectangle*R);
        break;
    case 0:
        setlinestyle(SOLID_LINE,0,3);
        setcolor(WHITE);
        create_right_menu_workplace(W,H,R,W/9,H/16);
        break;
    }
}

void change_color_icon_undo_redu_menu_workplace_page(int W, int H, int R, int val){
    int width_rectangle = W/18;
    int height_rectangle = H/16;

    switch(val){
    case 1:
        setlinestyle(SOLID_LINE,0,3);
        setcolor(RED);
        rectangle(2*width_rectangle/9,14.2*height_rectangle*R,width_rectangle,15*height_rectangle*R);
        break;
    case 2:
        setlinestyle(SOLID_LINE,0,3);
        setcolor(RED);
        rectangle(width_rectangle,14.2*height_rectangle*R,16*width_rectangle/9,15*height_rectangle*R);
        break;
    case 0:
        setlinestyle(SOLID_LINE,0,3);
        setcolor(WHITE);
        create_undo_redo_menu_workplace(W,H,R,W/18,H/16);
        break;
    }
}

void change_color_icon_drawing_line_type_menu_workplace(int W, int H, int R, int val, int condition){
    int width_rectangle = W/10;
    int height_rectangle = H/22;

    switch(val){
        case 1:
        setlinestyle(SOLID_LINE,0,1);
        setcolor(RED);
        rectangle((W-width_rectangle)*R,(height_rectangle*11.1)*R,W-width_rectangle/9,(height_rectangle*12.1)*R);
        break;
    case 4:
        setlinestyle(SOLID_LINE,0,1);
        setcolor(RED);
        rectangle((W-width_rectangle)*R,(height_rectangle*12.1)*R,W-width_rectangle/9,(height_rectangle*13.1)*R);
        break;
    case 2:
        setlinestyle(SOLID_LINE,0,1);
        setcolor(RED);
        rectangle((W-width_rectangle)*R,(height_rectangle*13.1)*R,W-width_rectangle/9,(height_rectangle*14.1)*R);
        break;
    case 3:
        setlinestyle(SOLID_LINE,0,1);
        setcolor(RED);
        rectangle((W-width_rectangle)*R,(height_rectangle*14.1)*R,W-width_rectangle/9,(height_rectangle*15.1)*R);
        break;
    case 0:
        if(!condition){
            setlinestyle(SOLID_LINE,0,1);
            setcolor(WHITE);
            create_drawing_line_type_menu_workplace(W,H,R,W/10,H/22,WHITE);
        }
        break;
    }
}

void change_color_icon_zoom_rotate_menu_workplace_page(int W, int H, int R, int width_rectangle, int height_rectangle, int color){
    setcolor(color);
    setlinestyle(SOLID_LINE,0,2);

    rectangle((W-width_rectangle)*R,(height_rectangle*16.1)*R,(W-width_rectangle)*R+4*W/225*2,(height_rectangle*20.1)*R);
    rectangle((W-width_rectangle)*R+4*W/225*3,(height_rectangle*16.1)*R,(W-width_rectangle)*R+4*W/225*5,(height_rectangle*20.1)*R);
}

#endif // CHANGE_COLOR_PANEL_H_INCLUDED

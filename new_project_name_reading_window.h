#ifndef NEW_PROJECT_NAME_READING_WINDOW_H_INCLUDED
#define NEW_PROJECT_NAME_READING_WINDOW_H_INCLUDED

#include <winuser.h>

#define KEY_LEFT  75
#define KEY_RIGHT 77


//Andrei CERBU pana jos

int menu_selection_reading_window(int W, int H, int x, int y){
    //enter button
    if((x>W/2-W/10&&x<W/2+W/10)&&(y>H/2+3*H/12-H/12&&y<H/2+3*H/12+H/12))
        return 1;

    //back button
    if((x>W-3*W/32-3*W/40&&x<W-3*W/32+3*W/40)&&(y>H/10-2*H/30&&y<H/10+2*H/30))
        return 2;
    return 0;
}

void print_text_on_new_project_name_reading_page(int W, int H, int R, int width_rectangle, int height_rectangle, int rect_w, int rect_h, char* str){
    int text_w=textwidth(str);
    int text_h=textheight(str);

    float x=(width_rectangle+(rect_w-text_w)/2);
    float y=(height_rectangle+(rect_h-text_h)/2);

    outtextxy(x,y,str);
}

void draw_new_project_name_reading_window(int W, int H, float R, int cursor){
    int width_rectangle, height_rectangle;
    int font1, font2;

    if(W*4<=1920)
        font1=1,font2=2;
    else font1=2,font2=3;

    setlinestyle(SOLID_LINE,0,1);
    settextstyle(COMPLEX_FONT,0,font1);

    //text_box
    width_rectangle=W/2;
    height_rectangle=H/3+13*H/72;

    rectangle(width_rectangle-W/4,height_rectangle-5*H/72,width_rectangle+W/4,height_rectangle+5*H/72);
    line(W/2-W/5-W/80+W/31*cursor,H/3+H/9,W/2-W/5-W/80+W/31*cursor,H/3+H/4);

    //enter_button
    width_rectangle=W/2;
    height_rectangle=H/2;

    rectangle(width_rectangle-W/10,height_rectangle+2*H/12,width_rectangle+W/10,height_rectangle+4*H/12);
    print_text_on_new_project_name_reading_page(W,H,R,width_rectangle-W/10,height_rectangle+2*H/12,W/5,H/6,"Enter");

    //back_button
    width_rectangle=W-3*W/32;
    height_rectangle=H/10;

    rectangle(width_rectangle-3*W/40,height_rectangle-2*H/30,width_rectangle+3*W/40,height_rectangle+2*H/30);
    print_text_on_new_project_name_reading_page(W,H,R,width_rectangle-3*W/40,height_rectangle-2*H/30,3*W/20,2*H/15,"Back");

    //text
    settextstyle(COMPLEX_FONT,0,font2);

    width_rectangle=W/2;
    height_rectangle=H/2-4*H/20;

    print_text_on_new_project_name_reading_page(W,H,R,width_rectangle-3*W/10,height_rectangle-H/20,3*W/5,H/10,"TYPE THE NAME HERE:");
}

void print_text_on_new_project_screen(int W, int H, char aux[], int nr_elem){
    setlinestyle(SOLID_LINE,0,W/120);
    if(nr_elem>14) nr_elem-=14;
    else nr_elem=0;
    strcpy(aux, aux+nr_elem);
    outtextxy(W/2-W/5-W/60,H/3+H/9+H/50,aux);
}

int new_project_name_reading_window(int W, int H, float R, char filename[]){

    int project_window1=initwindow(W,H,"New Project panel",W/3,H/3,0,0);

    POINT cursorPos;
    char aux[10000],c, ex;
    filename[0]=0;
    int nr_elem=0, poz=0, cursor=0, xMouse, yMouse;
    bool modif=0;

    draw_new_project_name_reading_window(W,H,R,poz);

    while(true){
        GetCursorPos(&cursorPos);
        ScreenToClient(GetForegroundWindow(), &cursorPos);

        if(kbhit()){
            c=getch();
            if(c&&c!=224){
                if(c==8&&nr_elem&&poz){
                    strcpy(filename+poz-1,filename+poz);
                    nr_elem--;
                    --poz;
                }
                else if(c==13){
                    closegraph(project_window1);
                    return 1;
                }
                else if(nr_elem<10000&&c>=' '&&c<='~'){
                    for(int i=nr_elem; i>poz; i--)
                        filename[i]=filename[i-1];
                    filename[poz]=c;
                    ++poz;
                    ++nr_elem;
                    filename[nr_elem]=0;
                }
            }
            else{
                switch(ex=getch()){
                case KEY_LEFT:
                    if(poz>0)
                        --poz;
                    break;
                case KEY_RIGHT:
                    if(poz<nr_elem)
                        ++poz;
                    break;
                }
            }
            if(poz>14)
                cursor=14;
            else cursor=poz;

            //create new frame
            cleardevice();

            draw_new_project_name_reading_window(W,H,R,poz);
            strcpy(aux,filename);
            print_text_on_new_project_screen(W,H,aux,nr_elem);
        }
        else if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN,xMouse,yMouse);
            switch(menu_selection_reading_window(W,H,xMouse,yMouse)){
            case 1://Enter was pressed
                closegraph(project_window1);
                return 1;
                break;
            case 2://back was pressed
                closegraph(project_window1);
                return 2;
                break;
            case 0:
                clearmouseclick(WM_LBUTTONDOWN);
                break;
            }
        }
    }
}

#endif // NEW_PROJECT_NAME_READING_WINDOW_H_INCLUDED

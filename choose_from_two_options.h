#ifndef CHOOSE_FROM_TWO_OPTIONS_H_INCLUDED
#define CHOOSE_FROM_TWO_OPTIONS_H_INCLUDED


//Andrei CERBU pana jos

void print_text_on_choose_from_two_options_page(int W, int H, int R, int width_rectangle, int height_rectangle, int rect_w, int rect_h, char* str){
    int text_w=textwidth(str);
    int text_h=textheight(str);

    float x=(width_rectangle+(rect_w-text_w)/2);
    float y=(height_rectangle+(rect_h-text_h)/2);

    outtextxy(x,y,str);
}

void draw_pannels_choose_from_two_options_menu(int W, int H, int R){
    setlinestyle(SOLID_LINE,0,1);
    setcolor(WHITE);

    int width_rectangle;
    int height_rectangle;

    width_rectangle=W/4;
    height_rectangle=H/2;

    rectangle(width_rectangle-W/5,height_rectangle-H/8,width_rectangle+W/5,height_rectangle+H/8);//latest project

    width_rectangle=3*W/4;
    height_rectangle=H/2;

    rectangle(width_rectangle-W/5,height_rectangle-H/8,width_rectangle+W/5,height_rectangle+H/8);//new project

    width_rectangle=W-3*W/32;
    height_rectangle=H/10;

    rectangle(width_rectangle-3*W/40,height_rectangle-2*H/30,width_rectangle+3*W/40,height_rectangle+2*H/30);//back
}

void put_text_on_choose_from_two_options_menu(int W, int H, int R){
    int font;
    int width_rectangle;
    int height_rectangle;

    if(W*4<=1920)
        font=1;
    else font=2;

    settextstyle(COMPLEX_FONT,0,font);

    width_rectangle=W/4;
    height_rectangle=H/2;

    print_text_on_choose_from_two_options_page(W,H,R,width_rectangle-W/5,height_rectangle-H/8,2*W/5,H/4,"Last Project");

    width_rectangle=3*W/4;
    height_rectangle=H/2;

    print_text_on_choose_from_two_options_page(W,H,R,width_rectangle-W/5,height_rectangle-H/8,2*W/5,H/4,"New Project");

    width_rectangle=W-3*W/32;
    height_rectangle=H/10;

    print_text_on_choose_from_two_options_page(W,H,R,width_rectangle-3*W/40,height_rectangle-2*H/30,3*W/20,2*H/15,"Back");
}

void change_color_to_choose_from_two_options_menu(int W, int H, int R, int val){
    int width_rectangle;
    int height_rectangle;

    switch(val){
    case 1:
        setlinestyle(SOLID_LINE,0,1);
        setcolor(RED);

        width_rectangle=W/4;
        height_rectangle=H/2;

        rectangle(width_rectangle-W/5,height_rectangle-H/8,width_rectangle+W/5,height_rectangle+H/8);//latest project

        break;
    case 2:
        setlinestyle(SOLID_LINE,0,1);
        setcolor(RED);

        width_rectangle=3*W/4;
        height_rectangle=H/2;

        rectangle(width_rectangle-W/5,height_rectangle-H/8,width_rectangle+W/5,height_rectangle+H/8);//new project

        break;
    case 3:
        setlinestyle(SOLID_LINE,0,1);
        setcolor(RED);

        width_rectangle=W-3*W/32;
        height_rectangle=H/10;

        rectangle(width_rectangle-3*W/40,height_rectangle-2*H/30,width_rectangle+3*W/40,height_rectangle+2*H/30);//back

        break;
    case 0:
        draw_pannels_choose_from_two_options_menu(W,H,R);
        break;
    }
}

int menu_selection_choose_from_two_options(int W, int H, int R, int x, int y){
    int width_rectangle;
    int height_rectangle;

    width_rectangle=W/4;
    height_rectangle=H/2;

    if(x>width_rectangle-W/5&&x<width_rectangle+W/5&&y>height_rectangle-H/8&&y<height_rectangle+H/8)
        return 1;

    width_rectangle=3*W/4;
    height_rectangle=H/2;

    if(x>width_rectangle-W/5&&x<width_rectangle+W/5&&y>height_rectangle-H/8&&y<height_rectangle+H/8)
        return 2;

    width_rectangle=W-3*W/32;
    height_rectangle=H/10;

    if(x>width_rectangle-3*W/40&&x<width_rectangle+3*W/40&&y>height_rectangle-2*H/30&&y<height_rectangle+2*H/30)
        return 3;

    return 0;
}

int choose_from_two_options(int W, int H, float R){
    POINT cursorPos;

    int panel=initwindow(W,H,"Choose",W,H,false,false);

    draw_pannels_choose_from_two_options_menu(W,H,R);
    put_text_on_choose_from_two_options_menu(W,H,R);

    do{
        GetCursorPos(&cursorPos);
        ScreenToClient(GetForegroundWindow(),&cursorPos);

        change_color_to_choose_from_two_options_menu(W,H,R,menu_selection_choose_from_two_options(W,H,R,cursorPos.x,cursorPos.y));

        if(ismouseclick(WM_LBUTTONDOWN)){
            if(menu_selection_choose_from_two_options(W,H,R,cursorPos.x,cursorPos.y)){
                closegraph(panel);
                return menu_selection_choose_from_two_options(W,H,R,cursorPos.x,cursorPos.y);
            }
            else clearmouseclick(WM_LBUTTONDOWN);
        }
    }
    while(true);
}

#endif // CHOOSE_FROM_TWO_OPTIONS_H_INCLUDED

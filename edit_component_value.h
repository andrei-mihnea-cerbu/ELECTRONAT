#ifndef EDIT_COMPONENT_VALUE_H_INCLUDED
#define EDIT_COMPONENT_VALUE_H_INCLUDED

#include <winuser.h>


using namespace std;

#define KEY_LEFT  75
#define KEY_RIGHT 77


//Andrei CEREBU pana jos

void creare_nume_componenta(int indx, char nume_componenta[], char unitate_masura[])
{
    switch(indx)
    {
    case 1:
        strcpy(nume_componenta,"Rezistor");
        strcpy(unitate_masura,"Ohm");
        break;
    case 2:
        strcpy(nume_componenta,"Fuse");
        strcpy(unitate_masura,"Ohm");
        break;
    case 3:
        strcpy(nume_componenta,"Battery");
        strcpy(unitate_masura,"Volts");
        break;
    case 4:
        strcpy(nume_componenta,"Dioda");
        strcpy(unitate_masura,"Ohm");
        break;
    case 5:
        strcpy(nume_componenta,"Ampermeter");
        strcpy(unitate_masura,"Ohm");
        break;
    case 6:
        strcpy(nume_componenta,"Voltmeter");
        strcpy(unitate_masura,"Ohm");
        break;
    case 7:
        strcpy(nume_componenta,"Capacitor");
        strcpy(unitate_masura,"Farad");
        break;
    case 8:
        strcpy(nume_componenta,"Transistor");
        strcpy(unitate_masura,"Ohm");
        break;
    case 9:
        strcpy(nume_componenta,"Light bulb");
        strcpy(unitate_masura,"Ohm");
        break;
    }
}

int menu_selection_edit_value_window(int W, int H, int x, int y)
{
    //enter button
    if((x>W/2-W/10&&x<W/2+W/10)&&(y>H/2+3*H/12-H/12&&y<H/2+3*H/12+H/12))
        return 1;

    //back button
    if((x>W-3*W/32-3*W/40&&x<W-3*W/32+3*W/40)&&(y>H/10-2*H/30&&y<H/10+2*H/30))
        return 2;
    return 0;
}

void print_text_on_edit_value_page(int W, int H, int R, int width_rectangle, int height_rectangle, int rect_w, int rect_h, char* str)
{
    int text_w=textwidth(str);
    int text_h=textheight(str);

    float x=(width_rectangle+(rect_w-text_w)/2);
    float y=(height_rectangle+(rect_h-text_h)/2);

    outtextxy(x,y,str);
}

void draw_edit_value_window(int W, int H, float R, int cursor, char nume_componenta[], char unitate_masura[])
{
    int width_rectangle, height_rectangle;
    int font1, font2;

    if(W*4<=1920)
        font1=1,font2=3;
    else font1=2,font2=4;

    setlinestyle(SOLID_LINE,0,1);
    settextstyle(COMPLEX_FONT,0,font1);

    //text_box
    width_rectangle=W/2;
    height_rectangle=H/3+13*H/72;

    rectangle(width_rectangle-W/4,height_rectangle-5*H/72,width_rectangle+W/4,height_rectangle+5*H/72);
    line(W/2-W/5-W/80+W/31*cursor,H/3+H/9,W/2-W/5-W/80+W/31*cursor,H/3+H/4);

    //enter_button
    width_rectangle=W/2;
    height_rectangle=H/2+3*H/12;

    rectangle(width_rectangle-W/10,height_rectangle-H/12,width_rectangle+W/10,height_rectangle+H/12);
    print_text_on_edit_value_page(W,H,R,width_rectangle-W/10,height_rectangle-H/12,W/5,H/6,"Enter");

    //back_button
    width_rectangle=W-3*W/32;
    height_rectangle=H/10;

    rectangle(width_rectangle-3*W/40,height_rectangle-2*H/30,width_rectangle+3*W/40,height_rectangle+2*H/30);
    print_text_on_edit_value_page(W,H,R,width_rectangle-3*W/40,height_rectangle-2*H/30,3*W/20,2*H/15,"Back");

    //unitate de masura
    width_rectangle=W/2+4*W/12;
    height_rectangle=H/3+13*H/72;

    print_text_on_edit_value_page(W,H,R,width_rectangle-W/12,height_rectangle-5*H/72,W/6,5*H/36,unitate_masura);

    settextstyle(EUROPEAN_FONT,0,font2);

    //nume componenta
    width_rectangle=W/2;
    height_rectangle=H/2-4*H/20;

    print_text_on_edit_value_page(W,H,R,width_rectangle-3*W/10,height_rectangle-H/20,3*W/5,H/10,nume_componenta);
}

void print_number_on_edit_value_screen(int W, int H, char aux[], int nr_elem)
{
    setlinestyle(SOLID_LINE,0,W/120);
    if(nr_elem>14) nr_elem-=14;
    else nr_elem=0;
    strcpy(aux,aux+nr_elem);

    settextstyle(COMPLEX_FONT,0,1);
    outtextxy(W/2-W/5-W/60,H/3+H/9+H/30,aux);
}

int det_numar_elemente(char number_initial[])
{
    int nr_elem=0, i=0;
    while(number_initial[i]!=0)
    {
        ++nr_elem;
        ++i;
    }
    return nr_elem;
}


void convert_value_to_string(char number[], int nr)
{
    int lenght=0;

    do
    {
        number[lenght]=nr%10+'0';
        nr/=10;
        lenght+=1;
    }
    while(nr);


    for(int i=0; i<lenght/2; i++)
    {
        char t = number[i];
        number[i] = number[lenght-i-1];
        number[lenght-i-1] = t;
    }


}

int convert_string_to_value(char number[])
{
    int nr=0;

    for(int i=0; i<strlen(number); i++)
    {

        if(number[i]<'0'|| number[i]>'9')
            return -1;
        nr=nr*10+(number[i]-'0');
    }
    return nr;
}



int edit_value_window(int W, int H, float R, int indx, int value)
{

    char number[10000];
    convert_value_to_string(number, value);


    int project_window1=initwindow(W/4,H/4,"Edit component",W/3,H/3,0,0);

    POINT cursorPos;
    char aux[10000], c, ex, number_initial[100000], unitate_masura[10],
         nume_componenta[20];

    int nr_elem=0, poz=0, cursor=0, xMouse, yMouse,
        nr_elem_number_initial=det_numar_elemente(number_initial);

    bool modif=false, afisare_numar_initial=false;

    strcpy(number_initial,number);//se copiaza numarul initial

    creare_nume_componenta(indx,nume_componenta,unitate_masura);

    draw_edit_value_window(W/4,H/4,R,poz,nume_componenta,unitate_masura);

    while(true)
    {
        GetCursorPos(&cursorPos);
        ScreenToClient(GetForegroundWindow(), &cursorPos);

        if(kbhit())
        {
            c=getch();
            if(c&&c!=224)
            {
                if(c==8&&nr_elem&&poz)
                {
                    strcpy(number+poz-1,number+poz);
                    nr_elem--;
                    --poz;
                }
                else if(c==13)
                {
                    closegraph(project_window1);
                    return 0;
                }
                else if(nr_elem<10000&&c>=' '&&c<='~')
                {
                    for(int i=nr_elem; i>poz; i--)
                        number[i]=number[i-1];
                    number[poz]=c;
                    ++poz;
                    ++nr_elem;
                    number[nr_elem]=0;
                }
            }
            else
            {
                switch(ex=getch())
                {
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
            draw_edit_value_window(W/4,H/4,cursor,poz,nume_componenta,unitate_masura);
            strcpy(aux,number);
            print_number_on_edit_value_screen(W/4,H/4,aux,nr_elem);
            if(nr_elem==0)
                afisare_numar_initial=false;
        }
        if(afisare_numar_initial==false)
        {
            afisare_numar_initial=true;

            cleardevice();
            draw_edit_value_window(W/4,H/4,cursor,poz,nume_componenta,unitate_masura);
            strcpy(aux,number_initial);
            print_number_on_edit_value_screen(W/4,H/4,aux,nr_elem_number_initial);
        }
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN,xMouse,yMouse);
            switch(menu_selection_edit_value_window(W/4,H/4,xMouse,yMouse))
            {
            case 1://Enter was pressed
            {
                int val = convert_string_to_value(number);
                if(val==-1)
                {
                    //mesaj eroare
                }
                else
                {
                    closegraph(project_window1);
                    memset(number, 0, 10000);
                    memset(number_initial, 0, 10000);
                    memset(aux, 0, 10000);
                    return val;
                }
                break;
            }
            case 2://back was pressed
                strcpy(number,number_initial);
                closegraph(project_window1);
                memset(number, 0, 10000);
                memset(number_initial, 0, 10000);
                memset(aux, 0, 10000);
                return value;
                break;
            case 0:
                clearmouseclick(WM_LBUTTONDOWN);
                break;
            }
        }
    }
}

#endif // EDIT_COMPONENT_VALUE_H_INCLUDED

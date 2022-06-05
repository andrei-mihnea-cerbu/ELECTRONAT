#ifndef MENU_SELECTION_H_INCLUDED
#define MENU_SELECTION_H_INCLUDED


//Andrei CERBU
int menu_selection_startup_page(int W, int H, int R, int x, int y)
{
    if((x>W/6&&x<W/6+R*H/6)&&(y>H/4&&y<H/4+R*H/6))
        return 1;
    if((x>W/3&&x<W/3+R*H/6)&&(y>H/4&&y<H/4+R*H/6))
        return 2;
    if((x>W/6&&x<W/6+R*H/6)&&(y>3*H/4-R*H/6&&y<3*H/4))
        return 3;
    if((x>W/3&&x<W/3+R*H/6)&&(y>3*H/4-R*H/6&&y<3*H/4))
        return 4;
    return 0;
}

int top_menu_workplace_page(int W, int H, int R, int x, int y)
{
    int width_rectangle = W/12;
    int height_rectangle = H/24;

    if((x>width_rectangle*3*R&&x<(width_rectangle*4)*R)&&(y>0&&y<height_rectangle*R))
        return 1;
    if((x>width_rectangle*4*R&&x<width_rectangle*5*R)&&(y>0&&y<height_rectangle*R))
        return 2;
    if((x>width_rectangle*5*R&&x<width_rectangle*6*R)&&(y>0&&y<height_rectangle*R))
        return 3;
    if((x>width_rectangle*6*R&&x<width_rectangle*7*R)&&(y>0&&y<height_rectangle*R))
        return 4;
    if((x>width_rectangle*7*R&&x<width_rectangle*8*R)&&(y>0&&y<height_rectangle*R))
        return 5;
    if((x>width_rectangle*8*R&&x<width_rectangle*9*R)&&(y>0&&y<height_rectangle*R))
        return 6;
    return 0;
}

int left_menu_workplace_page(int W, int H, float R, int x, int y)
{
    int width_rectangle = W/9;
    int height_rectangle = H/16;

    if((x>0&&x<(width_rectangle-width_rectangle/9)*R)&&(y>(height_rectangle*3)*R&&y<(height_rectangle*4)*R))
        return 1;
    if((x>0&&x<(width_rectangle-width_rectangle/9)*R)&&(y>(height_rectangle*4)*R&&y<(height_rectangle*5)*R))
        return 2;
    if((x>0&&x<(width_rectangle-width_rectangle/9)*R)&&(y>(height_rectangle*5)*R&&y<(height_rectangle*6)*R))
        return 3;
    if((x>0&&x<(width_rectangle-width_rectangle/9)*R)&&(y>(height_rectangle*6)*R&&y<(height_rectangle*7)*R))
        return 4;
    if((x>0&&x<(width_rectangle-width_rectangle/9)*R)&&(y>(height_rectangle*7)*R&&y<(height_rectangle*8)*R))
        return 5;
    if((x>0&&x<(width_rectangle-width_rectangle/9)*R)&&(y>(height_rectangle*8)*R&&y<(height_rectangle*9)*R))
        return 6;
    if((x>0&&x<(width_rectangle-width_rectangle/9)*R)&&(y>(height_rectangle*9)*R&&y<(height_rectangle*10)*R))
        return 7;
    if((x>0&&x<(width_rectangle-width_rectangle/9)*R)&&(y>(height_rectangle*10)*R&&y<(height_rectangle*11)*R))
        return 8;
    if((x>0&&x<(width_rectangle-width_rectangle/9)*R)&&(y>(height_rectangle*11)*R&&y<(height_rectangle*12)*R))
        return 9;
    return 0;
}

int right_menu_workplace_page(int W, int H, float R, int x, int y)
{
    int width_rectangle = W/9;
    int height_rectangle = H/16;

    if(x>(W-width_rectangle)*R&&x<W&&(y>(height_rectangle*2)*R&&y<(height_rectangle*3)*R))
        return 1;
    if(x>(W-width_rectangle)*R&&x<W&&(y>(height_rectangle*3)*R&&y<(height_rectangle*4)*R))
        return 2;
    if(x>(W-width_rectangle)*R&&x<W&&(y>(height_rectangle*4)*R&&y<(height_rectangle*5)*R))
        return 3;
    if(x>(W-width_rectangle)*R&&x<W&&(y>(height_rectangle*5)*R&&y<(height_rectangle*6)*R))
        return 4;
    if(x>(W-width_rectangle)*R&&x<W&&(y>(height_rectangle*6)*R&&y<(height_rectangle*7)*R))
        return 5;
    if(x>(W-width_rectangle)*R&&x<W&&(y>(height_rectangle*7)*R&&y<(height_rectangle*8)*R))
        return 6;
    return 0;

}


//Tudor ILADE
int undo_redo_menu_workplace_page(int W, int H, float R, int x, int y)
{
    int width_rectangle = W/18;
    int height_rectangle = H/16;

    if(x>=2*width_rectangle/9&&x<=width_rectangle&&y>=14.2*height_rectangle*R&&y<=15*height_rectangle*R)
        return 1;
    if(x>=width_rectangle&&x<=16*width_rectangle/9&&y>=14.2*height_rectangle*R&&y<=15*height_rectangle*R)
        return 2;
    return 0;
}

//Tudor Ilade
int line_type_menu_workplace(int W, int H, float R, int x, int y)
{
    int width_rectangle = W/10;
    int height_rectangle = H/22;

    if((x>(W-width_rectangle)*R&&x<W-width_rectangle/9)&&(y>(height_rectangle*11.1)*R&&y<(height_rectangle*12.1)*R))
        return 1;
    if((x>(W-width_rectangle)*R&&x<W-width_rectangle/9)&&(y>(height_rectangle*12.1)*R&&y<(height_rectangle*13.1)*R))
        return 4;
    if((x>(W-width_rectangle)*R&&x<W-width_rectangle/9)&&(y>(height_rectangle*13.1)*R&&y<(height_rectangle*14.1)*R))
        return 2;
    if((x>(W-width_rectangle)*R&&x<W-width_rectangle/9)&&(y>(height_rectangle*14.1)*R&&y<(height_rectangle*15.1)*R))
        return 3;
    return 0;
}

//Tudor Ilade

SWITCHSTATE turnLight(int W, int H, float R, int x, int y, SWITCHSTATE switcher)
{
    if((x>W-W/6.5+W/15)*R&&x<(W-W/9+W/12.5)*R&&(y>0.2*H/16&&y<1.6*H/16*R))
    {
        switcher.inOut = true;
        if(switcher.bulb==2)
            switcher.bulb = 1;
        else if(switcher.bulb==1)
            switcher.bulb = 2;
        return switcher;
    }

    switcher.inOut = false;
    switcher.bulb = 2;
    return switcher;
}



#endif // MENU_SELECTION_H_INCLUDED

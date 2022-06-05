#ifndef ZOOM_ROTATE_FADER_WORKPLACE_H_INCLUDED
#define ZOOM_ROTATE_FADER_WORKPLACE_H_INCLUDED


//Andrei CERBU
struct point
{
    int x, y;
};

struct fader
{
    point Centru;
    int angle;
    float R_ZOOM;
};


//Andrei CERBU && Tudor Ilade
void create_zoom_rotate_fader_workplace(int W, int H, int R, int width_rectangle, int height_rectangle, int y, int id, int color)
{

    if(id==1)
    {
        fader rrotate;
        rrotate.Centru.x=(W-width_rectangle)*R+4*W/225;
        rrotate.Centru.y=((height_rectangle*16.95)+(height_rectangle*19.7))*R/2;
        if(y>((height_rectangle*16.5)*R)&&y<(height_rectangle*19.7)*R)
        {
            setcolor(color);
            setlinestyle(SOLID_LINE,0,0);
            rectangle(rrotate.Centru.x-W/140,y-H/70,rrotate.Centru.x+W/140,y+H/70);
            setlinestyle(SOLID_LINE,0,0);
            line((W-width_rectangle)*R+4*W/225,(height_rectangle*16.5)*R,(W-width_rectangle)*R+4*W/225,(height_rectangle*19.7)*R);


        }
        else if(y<((height_rectangle*16.4)*R))
        {
            setcolor(color);
            setlinestyle(SOLID_LINE,0,0);
            rectangle(rrotate.Centru.x-W/140,((height_rectangle*16.4)*R),rrotate.Centru.x+W/140,(height_rectangle*16.4)*R+2*H/70);
            setlinestyle(SOLID_LINE,0,0);
            line((W-width_rectangle)*R+4*W/225,(height_rectangle*16.5)*R,(W-width_rectangle)*R+4*W/225,(height_rectangle*19.7)*R);
        }
        else if(y>(height_rectangle*19.7)*R)
        {
            setcolor(color);
            setlinestyle(SOLID_LINE,0,0);
            rectangle(rrotate.Centru.x-W/140,(height_rectangle*19.7)*R-2*H/70,rrotate.Centru.x+W/140,(height_rectangle*19.7)*R);
            setlinestyle(SOLID_LINE,0,0);
            line((W-width_rectangle)*R+4*W/225,(height_rectangle*16.5)*R,(W-width_rectangle)*R+4*W/225,(height_rectangle*19.7)*R);
        }
    }
    else if(id == 2)
    {

        fader zzom;
        zzom.Centru.x=(W-width_rectangle)*R+4*W/225*4;
        zzom.Centru.y=((height_rectangle*16.95)+(height_rectangle*19.7))*R/2;

        if(y-H/70>((height_rectangle*16.5)*R)&&y+H/70<(height_rectangle*19.7)*R)
        {
            setcolor(color);
            setlinestyle(SOLID_LINE,0,0);
            rectangle(zzom.Centru.x-W/140,y-H/70,zzom.Centru.x+W/140,y+H/70);
            setlinestyle(SOLID_LINE,0,0);
            line((W-width_rectangle)*R+4*W/225*4,(height_rectangle*16.5)*R,(W-width_rectangle)*R+4*W/225*4,(height_rectangle*19.7)*R);

        }
        else if(y-H/70<((height_rectangle*16.4)*R))
        {
            setcolor(color);
            setlinestyle(SOLID_LINE,0,0);
            rectangle(zzom.Centru.x-W/140,((height_rectangle*16.4)*R),zzom.Centru.x+W/140,(height_rectangle*16.4)*R+2*H/70);
            setlinestyle(SOLID_LINE,0,0);
            line((W-width_rectangle)*R+4*W/225*4,(height_rectangle*16.5)*R,(W-width_rectangle)*R+4*W/225*4,(height_rectangle*19.7)*R);
        }
        else if(y+H/70>(height_rectangle*19.7)*R)
        {
            setcolor(color);
            setlinestyle(SOLID_LINE,0,0);
            rectangle(zzom.Centru.x-W/140,(height_rectangle*19.7)*R-2*H/70,zzom.Centru.x+W/140,(height_rectangle*19.7)*R);
            setlinestyle(SOLID_LINE,0,0);
            line((W-width_rectangle)*R+4*W/225*4,(height_rectangle*16.5)*R,(W-width_rectangle)*R+4*W/225*4,(height_rectangle*19.7)*R);
        }
    }
}

//Andrei Cerbu
int determine_angle_fader_position(int W, int H, int R, int width_rectangle, int height_rectangle, int x, int y)
{

    fader rrotate, zzom;
    rrotate.Centru.x=(W-width_rectangle)*R+4*W/225;
    rrotate.Centru.y=((height_rectangle*16.95)+(height_rectangle*19.7))*R/2;

    zzom.Centru.x=(W-width_rectangle)*R+4*W/225*4;
    zzom.Centru.y=((height_rectangle*16.95)+(height_rectangle*19.7))*R/2;


    if(x>rrotate.Centru.x-W/140&&x<rrotate.Centru.x+W/140&&y>rrotate.Centru.y-H/70&&y<rrotate.Centru.y+H/70)
        return 1;
    if(x>zzom.Centru.x-W/140 && x< zzom.Centru.x+W/140 && y>zzom.Centru.y-H/70 && zzom.Centru.y+H/70)
        return 2;
    return 0;
}

#endif // ZOOM_ROTATE_FADER_WORKPLACE_H_INCLUDED

#ifndef DRAWING_COMPONENTS_H_INCLUDED
#define DRAWING_COMPONENTS_H_INCLUDED

#include <graphics.h>
#include <windows.h>
#include <cmath>
#include <math.h>

using namespace std;

//Andrei CERBU pana jos

struct coordonate
{
    float x, y;
};

typedef struct dreptunghi
{
    coordonate TL, TR, BR, BL;
} drepunghi;

typedef struct componenta
{
    int line_width=0;
    int branch;
    float points[8];
};

struct dreptunghi create_struct_rectangle(float w1, float w2, float h1, float h2)
{
    dreptunghi D;
    D.TL.x=w1,D.TL.y=h1;
    D.TR.x=w2,D.TR.y=h1;
    D.BL.x=w1,D.BL.y=h2;
    D.BR.x=w2,D.BR.y=h2;
    return D;
}

struct dreptunghi translate_rectangle(drepunghi D, coordonate C)
{
    D.TL.x-=C.x,D.TL.y-=C.y;
    D.TR.x-=C.x,D.TR.y-=C.y;
    D.BR.x-=C.x,D.BR.y-=C.y;
    D.BL.x-=C.x,D.BL.y-=C.y;
    return D;
}

struct coordonate determine_points(float pointX, float pointY, float beta)
{
    coordonate C;
    C.x=cos(beta)*pointX-sin(beta)*pointY;
    C.y=sin(beta)*pointX+cos(beta)*pointY;
    return C;
}

struct componenta RotateRectangle(coordonate C, drepunghi D, int angle, int branch)
{
    componenta CMP;

    if(branch<=2) //componenta care trebuie sa se invarta
    {
        double beta=-(double)(angle%360)*M_PI/180.0;
        D.TL=determine_points(D.TL.x,D.TL.y,beta);
        D.TR=determine_points(D.TR.x,D.TR.y,beta);
        D.BR=determine_points(D.BR.x,D.BR.y,beta);
        D.BL=determine_points(D.BL.x,D.BL.y,beta);
        if(branch==1)
        {
            float point[8]=
            {
                (D.TL.x+C.x),(D.TL.y+C.y),
                (D.TR.x+C.x),(D.TR.y+C.y),
                (D.BR.x+C.x),(D.BR.y+C.y),
                (D.BL.x+C.x),(D.BL.y+C.y)
            };
            for(int i=0; i<8; i++)
                CMP.points[i]=point[i];
        }
        else if(branch==2)
        {
            CMP.points[0]=D.TL.x+C.x;
            CMP.points[1]=D.TL.y+C.y;
            CMP.points[2]=D.BR.x+C.x;
            CMP.points[3]=D.BR.y+C.y;
        }
    }
    if(branch==3) /*componenta care nu trebuie sa se invarta*/
    {
        CMP.points[0]=D.TL.x;
        CMP.points[1]=D.TL.y;
        CMP.points[2]=D.BR.x;
        CMP.points[3]=D.BR.y;
    }
    if(branch==4) /*cerc*/
    {
        CMP.points[0]=D.TL.x;
        CMP.points[1]=D.TL.y;
        CMP.points[2]=D.TR.x;
    }

    CMP.branch=branch;
    return CMP;
}


void construct_resistor(int W, int H, float R, int X, int Y, int angle, float zoom, struct componenta CMP[])
{
    int width = W/8, height = H/4;
    float w1, w2, h1, h2, w, h;

    dreptunghi D;
    coordonate C;
    C.x=X, C.y=Y;

    //chenar
    w1=-(width*4-width/1.7)*R*zoom+X, w2=(width*4-width/1.7)*R*zoom+X,
    h1=-(height*2-height/2.7)*R*zoom+Y, h2=(height*2-height/2.7)*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[1]=RotateRectangle(C,D,angle,1);

    //conector stanga
    w1=-3.3*width*R*zoom+X, w2=-3*width*R*zoom+X,
    h1=-height/3*R*R*zoom+Y, h2=height/3*R*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[2]=RotateRectangle(C,D,angle,1);

    //conector drept
    w1=3*width*R*zoom+X, w2=3.3*width*R*zoom+X,
    h1=-height/3*R*R*zoom+Y, h2=height/3*R*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[3]=RotateRectangle(C,D,angle,1);

    //corp
    w1=-3*width/2*R*zoom+X, w2=3*width/2*R*zoom+X,
    h1=-height*R*zoom+Y, h2=height*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[4]=RotateRectangle(C,D,angle,1);

    //linie stanga
    w1=-3*width*R*zoom+X, w2=-3*width/2*R*zoom+X,
    h1=Y, h2=Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[5]=RotateRectangle(C,D,angle,1);

    //linie dreapta
    w1=3*width/2*R*zoom+X, w2=3*width*R*zoom+X,
    h1=Y, h2=Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[6]=RotateRectangle(C,D,angle,1);
}

void construct_fuse(int W, int H, float R, int X, int Y, int angle, float zoom, struct componenta CMP[])
{
    int width = W/8, height = H/4;
    float w1, w2, h1, h2, w, h;

    dreptunghi D;
    coordonate C;
    C.x=X, C.y=Y;

    //chenar
    w1=-(width*4-width/1.7)*R*zoom+X, w2=(width*4-width/1.7)*R*zoom+X,
    h1=-(height*2-height/2.7)*R*zoom+Y, h2=(height*2-height/2.7)*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[1]=RotateRectangle(C,D,angle,1);

    //conector stanga
    w1=-3.3*width*R*zoom+X, w2=-3*width*R*zoom+X,
    h1=-height/3*R*R*zoom+Y, h2=height/3*R*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[2]=RotateRectangle(C,D,angle,1);

    //conector drept
    w1=3*width*R*zoom+X, w2=3.3*width*R*zoom+X,
    h1=-height/3*R*R*zoom+Y, h2=height/3*R*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[3]=RotateRectangle(C,D,angle,1);

    //corp
    w1=-3*width/2*R*zoom+X, w2=3*width/2*R*zoom+X,
    h1=-height*R*zoom+Y, h2=height*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[4]=RotateRectangle(C,D,angle,1);

    //linie
    w1=-3*width*R*zoom+X, w2=3*width*R*zoom+X,
    h1=Y, h2=Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[5]=RotateRectangle(C,D,angle,1);
}

void construct_electrical_cell(int W, int H, float R, int X, int Y, int angle, float zoom, struct componenta CMP[])
{
    int width = W/8, height = H/4;
    float w1, w2, h1, h2, w, h;

    dreptunghi D;
    coordonate C;
    C.x=X, C.y=Y;

    //chenar
    w1=-(width*4-width/1.7)*R*zoom+X, w2=(width*4-width/1.7)*R*zoom+X,
    h1=-(height*2-height/2.7)*R*zoom+Y, h2=(height*2-height/2.7)*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[1]=RotateRectangle(C,D,angle,1);

    //conector stanga
    w1=-3.3*width*R*zoom+X, w2=-3*width*R*zoom+X,
    h1=-height/3*R*R*zoom+Y, h2=height/3*R*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[2]=RotateRectangle(C,D,angle,1);

    //conector drept
    w1=3*width*R*zoom+X, w2=3.3*width*R*zoom+X,
    h1=-height/3*R*R*zoom+Y, h2=height/3*R*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[3]=RotateRectangle(C,D,angle,1);

    //borna minus
    w1=-width/4*R*zoom+X, w2=-width/4*R*zoom+X,
    h1=-4*height/3*R*zoom+Y, h2=4*height/3*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[4]=RotateRectangle(C,D,angle,1);

    //borna plus
    w1=width/4*R*zoom+X, w2=width/4*R*zoom+X,
    h1=-15*height/8*R*zoom+Y, h2=15*height/8*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[5]=RotateRectangle(C,D,angle,1);

    //linie stanga
    w1=-3*width*R*zoom+X, w2=-width/4*R*zoom+X,
    h1=Y, h2=Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[6]=RotateRectangle(C,D,angle,1);

    //linie dreapta
    w1=width/4*R*zoom+X, w2=3*width*R*zoom+X,
    h1=Y, h2=Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[7]=RotateRectangle(C,D,angle,1);
}

void construct_dioda(int W, int H, float R, int X, int Y, int angle, float zoom, struct componenta CMP[])
{
    int width = W/8, height = H/4;
    float w1, w2, h1, h2, w, h;

    dreptunghi D;
    coordonate C;
    C.x=X, C.y=Y;

    //chenar
    w1=-(width*4-width/1.7)*R*zoom+X, w2=(width*4-width/1.7)*R*zoom+X,
    h1=-(height*2-height/2.7)*R*zoom+Y, h2=(height*2-height/2.7)*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[1]=RotateRectangle(C,D,angle,1);

    //conector stanga
    w1=-3.3*width*R*zoom+X, w2=-3*width*R*zoom+X,
    h1=-height/3*R*R*zoom+Y, h2=height/3*R*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[2]=RotateRectangle(C,D,angle,1);

    //conector drept
    w1=3*width*R*zoom+X, w2=3.3*width*R*zoom+X,
    h1=-height/3*R*R*zoom+Y, h2=height/3*R*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[3]=RotateRectangle(C,D,angle,1);

    //linie blocaj
    w1=width*R*zoom+X, w2=width*R*zoom+X,
    h1=-height*R*zoom+Y, h2=height*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[4]=RotateRectangle(C,D,angle,1);

    //linie stanga
    w1=-3*width*R*zoom+X, w2=-width*R*zoom+X,
    h1=Y, h2=Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[5]=RotateRectangle(C,D,angle,1);

    //linie dreapta
    w1=width*R*zoom+X, w2=3*width*R*zoom+X,
    h1=Y, h2=Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[6]=RotateRectangle(C,D,angle,1);

    ///TRIUNGHI
    //baza
    w1=-width*R*zoom+X, w2=-width*R*zoom+X,
    h1=-height*R*zoom+Y, h2=height*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[7]=RotateRectangle(C,D,angle,1);

    //latura sus->jos
    w1=-width*R*zoom+X, w2=width*R*zoom+X,
    h1=-height*R*zoom+Y, h2=Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[8]=RotateRectangle(C,D,angle,2);

    //latura jos->sus
    w1=-width*R*zoom+X, w2=width*R*zoom+X,
    h1=height*R*zoom+Y, h2=Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[9]=RotateRectangle(C,D,angle,2);
}

void construct_ampermeter(int W, int H, float R, int X, int Y, int angle, float zoom, struct componenta CMP[])
{
    int width = W/8, height = H/4;
    float w1, w2, h1, h2, w, h;

    dreptunghi D;
    coordonate C;
    C.x=X, C.y=Y;

    //chenar
    w1=-(width*4-width/1.7)*R*zoom+X, w2=(width*4-width/1.7)*R*zoom+X,
    h1=-(height*2-height/2.7)*R*zoom+Y, h2=(height*2-height/2.7)*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[1]=RotateRectangle(C,D,angle,1);

    //conector stanga
    w1=-3.3*width*R*zoom+X, w2=-3*width*R*zoom+X,
    h1=-height/3*R*R*zoom+Y, h2=height/3*R*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[2]=RotateRectangle(C,D,angle,1);

    //conector dreapta
    w1=3*width*R*zoom+X, w2=3.3*width*R*zoom+X,
    h1=-height/3*R*R*zoom+Y, h2=height/3*R*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[3]=RotateRectangle(C,D,angle,1);

    //linie stanga
    w1=-3*width*R*zoom+X, w2=-width*R*zoom+X,
    h1=Y, h2=Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[4]=RotateRectangle(C,D,angle,1);

    //linie dreapta
    w1=width*R*zoom+X, w2=3*width*R*zoom+X,
    h1=Y, h2=Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[5]=RotateRectangle(C,D,angle,1);

    ///litera A
    //talpa dreapta
    w1=width/3*R*zoom+X, w2=39*width/84*R*zoom+X,
    h1=height/3*R*zoom+Y, h2=height/3*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    CMP[6]=RotateRectangle(C,D,angle,3);
    CMP[6].line_width=3;

    //picior drept
    w1=width/10*R*zoom+X, w2=2*width/5*R*zoom+X,
    h1=-height/2*R*zoom+Y, h2=height/3*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    CMP[7]=RotateRectangle(C,D,angle,3);
    CMP[7].line_width=3;

    //tapla stanga
    w1=-39*width/84*R*zoom+X, w2=-width/3*R*zoom+X,
    h1=height/3*R*zoom+Y, h2=height/3*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    CMP[8]=RotateRectangle(C,D,angle,3);
    CMP[8].line_width=3;

    //picior stang
    w1=-width/10*R*zoom+X, w2=-2*width/5*R*zoom+X,
    h1=-height/2*R*zoom+Y, h2=height/3*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    CMP[9]=RotateRectangle(C,D,angle,3);
    CMP[9].line_width=3;

    //palarie
    w1=-width/10*R*zoom+X, w2=width/5*R*zoom+X,
    h1=-height/2*R*zoom+Y, h2=-height/2*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    CMP[10]=RotateRectangle(C,D,angle,3);
    CMP[10].line_width=3;

    //linie mijloc
    w1=-width/4*R*zoom+X, w2=width/4*R*zoom+X,
    h1=-height/12*R*zoom+Y, h2=-height/12*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    CMP[11]=RotateRectangle(C,D,angle,3);
    CMP[11].line_width=3;

    //centru
    w1=X*R*zoom, w2=width*R*zoom,
    h1=Y*R*zoom, h2=Y*R*zoom;
    D=create_struct_rectangle(w1,w2,h1,h2);
    CMP[12]=RotateRectangle(C,D,angle,4);
}

void construct_voltmeter(int W, int H, float R, int X, int Y, int angle, float zoom, struct componenta CMP[])
{
    int width = W/8, height = H/4;
    float w1, w2, h1, h2, w, h;

    dreptunghi D;
    coordonate C;
    C.x=X, C.y=Y;

    //chenar
    w1=-(width*4-width/1.7)*R*zoom+X, w2=(width*4-width/1.7)*R*zoom+X,
    h1=-(height*2-height/2.7)*R*zoom+Y, h2=(height*2-height/2.7)*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[1]=RotateRectangle(C,D,angle,1);

    //conector stanga
    w1=-3.3*width*R*zoom+X, w2=-3*width*R*zoom+X,
    h1=-height/3*R*R*zoom+Y, h2=height/3*R*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[2]=RotateRectangle(C,D,angle,1);

    //conector dreapta
    w1=3*width*R*zoom+X, w2=3.3*width*R*zoom+X,
    h1=-height/3*R*R*zoom+Y, h2=height/3*R*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[3]=RotateRectangle(C,D,angle,1);

    //linie stanga
    w1=-3*width*R*zoom+X, w2=-width*R*zoom+X,
    h1=Y, h2=Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[4]=RotateRectangle(C,D,angle,1);

    //linie dreapta
    w1=width*R*zoom+X, w2=3*width*R*zoom+X,
    h1=Y, h2=Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[5]=RotateRectangle(C,D,angle,1);

    ///litera V
    //talpa dreapta
    w1=width/3*R*zoom+X, w2=39*width/84*R*zoom+X,
    h1=-height/3*R*zoom+Y, h2=-height/3*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    CMP[6]=RotateRectangle(C,D,angle,3);
    CMP[6].line_width=3;

    //picior drept
    w1=X*R*zoom, w2=2*width/5*R*zoom+X,
    h1=height/2*R*zoom+Y, h2=-height/3*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    CMP[7]=RotateRectangle(C,D,angle,3);
    CMP[7].line_width=3;

    //tapla stanga
    w1=-39*width/84*R*zoom+X, w2=-width/3*R*zoom+X,
    h1=-height/3*R*zoom+Y, h2=-height/3*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    CMP[8]=RotateRectangle(C,D,angle,3);
    CMP[8].line_width=3;

    //picior stang
    w1=X*R*zoom, w2=-2*width/5*R*zoom+X,
    h1=height/2*R*zoom+Y, h2=-height/3*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    CMP[9]=RotateRectangle(C,D,angle,3);
    CMP[9].line_width=3;

    //centru
    w1=X*R*zoom, w2=width*R*zoom,
    h1=Y*R*zoom, h2=Y*R*zoom;
    D=create_struct_rectangle(w1,w2,h1,h2);
    CMP[10]=RotateRectangle(C,D,angle,4);
}

void construct_capacitor(int W, int H, float R, int X, int Y, int angle, float zoom, struct componenta CMP[])
{
    int width = W/8, height = H/4;
    float w1, w2, h1, h2, w, h;

    dreptunghi D;
    coordonate C;
    C.x=X, C.y=Y;

    //chenar
    w1=-(width*4-width/1.7)*R*zoom+X, w2=(width*4-width/1.7)*R*zoom+X,
    h1=-(height*2-height/2.7)*R*zoom+Y, h2=(height*2-height/2.7)*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[1]=RotateRectangle(C,D,angle,1);

    //conector stanga
    w1=-3.3*width*R*zoom+X, w2=-3*width*R*zoom+X,
    h1=-height/3*R*R*zoom+Y, h2=height/3*R*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[2]=RotateRectangle(C,D,angle,1);

    //conector drept
    w1=3*width*R*zoom+X, w2=3.3*width*R*zoom+X,
    h1=-height/3*R*R*zoom+Y, h2=height/3*R*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[3]=RotateRectangle(C,D,angle,1);

    //borna minus
    w1=-width/4*R*zoom+X, w2=-width/4*R*zoom+X,
    h1=-4*height/3*R*zoom+Y, h2=4*height/3*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[4]=RotateRectangle(C,D,angle,1);

    //borna plus
    w1=width/4*R*zoom+X, w2=width/4*R*zoom+X,
    h1=-4*height/3*R*zoom+Y, h2=4*height/3*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[5]=RotateRectangle(C,D,angle,1);

    //linie stanga
    w1=-3*width*R*zoom+X, w2=-width/4*R*zoom+X,
    h1=Y, h2=Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[6]=RotateRectangle(C,D,angle,1);

    //linie dreapta
    w1=width/4*R*zoom+X, w2=3*width*R*zoom+X,
    h1=Y, h2=Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[7]=RotateRectangle(C,D,angle,1);
}

void construct_bulb(int W, int H, float R, int X, int Y, int angle, float zoom, struct componenta CMP[])
{
    int width = W/8, height = H/4;
    float w1, w2, h1, h2, w, h;

    dreptunghi D;
    coordonate C;
    C.x=X, C.y=Y;

    //chenar
    w1=-(width*4-width/1.7)*R*zoom+X, w2=(width*4-width/1.7)*R*zoom+X,
    h1=-(height*2-height/2.7)*R*zoom+Y, h2=(height*2-height/2.7)*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[1]=RotateRectangle(C,D,angle,1);

    //conector stanga
    w1=-3.3*width*R*zoom+X, w2=-3*width*R*zoom+X,
    h1=-height/3*R*R*zoom+Y, h2=height/3*R*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[2]=RotateRectangle(C,D,angle,1);

    //conector dreapta
    w1=3*width*R*zoom+X, w2=3.3*width*R*zoom+X,
    h1=-height/3*R*R*zoom+Y, h2=height/3*R*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[3]=RotateRectangle(C,D,angle,1);

    //linie stanga
    w1=-3*width*R*zoom+X, w2=-width*R*zoom+X,
    h1=Y*R*zoom, h2=Y*R*zoom;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[4]=RotateRectangle(C,D,angle,1);

    //linie dreapta
    w1=width*R*zoom+X, w2=3*width*R*zoom+X,
    h1=Y*R*zoom, h2=Y*R*zoom;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[5]=RotateRectangle(C,D,angle,1);

    //bec linie stanga
    w1=-2*width/5*R*zoom+X, w2=2*width/5*R*zoom+X,
    h1=-height*R*zoom+Y, h2=height*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    CMP[6]=RotateRectangle(C,D,angle,3);

    //bec linie dreapta
    w1=2*width/5*R*zoom+X, w2=-2*width/5*R*zoom+X,
    h1=-height*R*zoom+Y, h2=height*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    CMP[7]=RotateRectangle(C,D,angle,3);

    //cerc
    w1=X*R*zoom, w2=width*R*zoom,
    h1=Y*R*zoom, h2=Y*R*zoom;
    D=create_struct_rectangle(w1,w2,h1,h2);
    CMP[8]=RotateRectangle(C,D,angle,4);
}

void construct_transistor(int W, int H, float R, int X, int Y, int angle, float zoom, struct componenta CMP[])
{
    int width = W/8, height = H/4;
    float w1, w2, h1, h2, w, h;

    dreptunghi D;
    coordonate C;
    C.x=X, C.y=Y;

    //chenar
    w1=-2*width*R*zoom+X, w2=width*R*zoom+X,
    h1=-(height*2-height/2.7)*R*zoom+Y, h2=(height*2-height/2.7)*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[1]=RotateRectangle(C,D,angle,1);

    //conector stanga
    w1=-1.8*width*R*zoom+X, w2=-1.5*width*R*zoom+X,
    h1=-0.3*height*R*zoom+Y, h2=0.3*height*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[2]=RotateRectangle(C,D,angle,1);

    //conector top
    w1=0.65*width*R*zoom+X, w2=0.95*width*R*zoom+X,
    h1=-1.5*height*R*zoom+Y, h2=-height*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[3]=RotateRectangle(C,D,angle,1);

    //conector bot
    w1=0.65*width*R*zoom+X, w2=0.95*width*R*zoom+X,
    h1=height*R*zoom+Y, h2=1.5*height*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[4]=RotateRectangle(C,D,angle,1);

    //linie centru
    w1=-0.1*width*R*zoom+X, w2=-0.1*width*R*zoom+X,
    h1=-height/2*R*zoom+Y, h2=height/2*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[5]=RotateRectangle(C,D,angle,1);

    //linie centru bot
    w1=-0.1*width*R*zoom+X, w2=0.8*width*R*zoom+X,
    h1=(height-height/1.2)*R*zoom+Y, h2=3*height/5.5*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[6]=RotateRectangle(C,D,angle,2);

    //linie centru top
    w1=-0.1*width*R*zoom+X, w2=0.8*width*R*zoom+X,
    h1=(-(height-height/1.2))*R*zoom+Y, h2=-3*height/5.5*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[7]=RotateRectangle(C,D,angle,2);

    //linie conector stanga
    w1=-1.5*width*R*zoom+X, w2=-0.1*width*R*zoom+X,
    h1=Y*R*zoom, h2=Y*R*zoom;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[8]=RotateRectangle(C,D,angle,1);

    //linie conector top
    w1=0.8*width*R*zoom+X, w2=0.8*width*R*zoom+X,
    h1=-height/2*R*zoom+Y, h2=-height*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[9]=RotateRectangle(C,D,angle,1);

    //linie conector bot
    w1=0.8*width*R*zoom+X, w2=0.8*width*R*zoom+X,
    h1=height/2*R*zoom+Y, h2=height*R*zoom+Y;
    D=create_struct_rectangle(w1,w2,h1,h2);
    D=translate_rectangle(D,C);
    CMP[10]=RotateRectangle(C,D,angle,1);

    //centru
    w1=X*R*zoom, w2=0.6*width*R*zoom,
    h1=Y*R*zoom, h2=Y*R*zoom;
    D=create_struct_rectangle(w1,w2,h1,h2);
    CMP[11]=RotateRectangle(C,D,angle,4);
}

void draw_component(struct componenta CMP[], int n, int color)
{
    setcolor(color);
    for(int i=2; i<=n; i++)
    {
        setlinestyle(SOLID_LINE,0,CMP[i].line_width);

        switch(CMP[i].branch)
        {
        case 1:
            for(int j=0; j<8; j+=2)
                line(CMP[i].points[j],CMP[i].points[j+1],CMP[i].points[(j+2)%8],CMP[i].points[(j+3)%8]);
            break;
        case 2:
            line(CMP[i].points[0],CMP[i].points[1],CMP[i].points[2],CMP[i].points[3]);
            break;
        case 3:
            line(CMP[i].points[0],CMP[i].points[1],CMP[i].points[2],CMP[i].points[3]);
            break;
        case 4:
            circle(CMP[i].points[0],CMP[i].points[1],CMP[i].points[2]);
            break;
        }
    }
}

void draw_components_on_working_table(int type, int W, int H, int X, int Y, float R, int angle, float zoom, int color, struct componenta CMP[])
{

    switch(type)
    {
    case 1:
        construct_resistor(W/10,H/16,R,X,Y,angle,zoom,CMP);
        draw_component(CMP,6,color);
        break;
    case 2:
        construct_fuse(W/10,H/16,R,X,Y,angle,zoom,CMP);
        draw_component(CMP,5,color);
        break;
    case 3:
        construct_electrical_cell(W/10,H/16,R,X,Y,angle,zoom,CMP);
        draw_component(CMP,7,color);
        break;
    case 4:
        construct_dioda(W/10,H/16,R,X,Y,angle,zoom,CMP);
        draw_component(CMP,9,color);
        break;
    case 5:
        construct_ampermeter(W/10,H/16,R,X,Y,angle,zoom,CMP);
        draw_component(CMP,12,color);
        break;
    case 6:
        construct_voltmeter(W/10,H/16,R,X,Y,angle,zoom,CMP);
        draw_component(CMP,10,color);
        break;
    case 7:
        construct_capacitor(W/10,H/16,R,X,Y,angle,zoom,CMP);
        draw_component(CMP,7,color);
        break;
    case 8:
        construct_bulb(W/10,H/16,R,X,Y,angle,zoom,CMP);
        draw_component(CMP,8,color);
        break;
    case 9:
        construct_transistor(W/10,H/16,R,X,Y,angle,zoom,CMP);
        draw_component(CMP,11,color);
        break;
    }
}

#endif // DRAWING_COMPONENTS_H_INCLUDED

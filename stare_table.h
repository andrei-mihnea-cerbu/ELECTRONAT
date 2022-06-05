#ifndef STARE_TABLE_H_INCLUDED
#define STARE_TABLE_H_INCLUDED

///LIBRARIES
#include <vector>
#include <stack>
#include <conio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <filesystem>
#include <bits/stdc++.h>
#include "drawing_components.h"
#include "functii_auxiliare.h"

using namespace std;


//Tudor Ilade  -  in afara de functiile facute de Andrei
struct punctLegatura
{
    int type;
    int x,y;
    int xConnection, yConnection;
    int ndxParent;
    int sd;
};

typedef struct RECTANGLE
{
    float left;
    float top;
    float right;
    float bottom;
    int xCenter;
    int yCenter;
};


struct SWITCHSTATE{
    int bulb=2;
    bool inOut;
};

typedef struct RECTANGLE_FULL
{
    struct
    {
        float x, y;
    } left_top, right_top, left_bottom, right_bottom;
} RECTANGLE_FULL;

struct BinaryCMP
{
    int type;
    char name[512];
    int x;
    int y;
    float R;
    int angle;
    float zoom;
    int value=0;
    bool conectat;
    RECTANGLE outsideRect;
    RECTANGLE rect;
    RECTANGLE nodes[3];
    RECTANGLE_FULL coordinates[4];
    int size_of_linkings;
    punctLegatura legatura[256];
};

struct COMPONENTE
{
    int type;
    char name[512];
    int x1;
    int y1;
    float R;
    int nr_puncte_legatura;
    bool connectat;
    int angle=0;
    float zoom=1.0;
    int value=0;
    RECTANGLE nodes[3];
    RECTANGLE_FULL coordinates[4];
    RECTANGLE rect;
    RECTANGLE outsideRect;
    vector<pair<punctLegatura,punctLegatura>>legatura;
};

struct SITUATIA_TABLEI
{
    int ans;
    char path_file[1024];
    char path_to_dir[1024];
    bool open=false;
    bool light = false;
    vector<COMPONENTE> v;
    vector<pair<punctLegatura, punctLegatura>>p;
};

struct HISTORY
{
    stack<SITUATIA_TABLEI>UNDO;
    stack<SITUATIA_TABLEI>REDO;
    stack<char*>LOG;
};


//Andrei Cerbu
struct RECTANGLE_FULL generate_coordinates_full(struct componenta CMP)
{
    struct RECTANGLE_FULL structt;

    structt.left_top.x=CMP.points[0];
    structt.left_top.y=CMP.points[1];
    structt.right_top.x=CMP.points[2];
    structt.right_top.y=CMP.points[3];
    structt.right_bottom.x=CMP.points[4];
    structt.right_bottom.y=CMP.points[5];
    structt.left_bottom.x=CMP.points[6];
    structt.left_bottom.y=CMP.points[7];

    return structt;
}

struct RECTANGLE generate_coordinates(struct componenta CMP)
{
    struct RECTANGLE RECT;
    RECT.left=CMP.points[0];
    RECT.top=CMP.points[1];
    RECT.right=CMP.points[4];
    RECT.bottom=CMP.points[5];
    RECT.xCenter=(CMP.points[0]+CMP.points[4])/2;
    RECT.yCenter=(CMP.points[1]+CMP.points[5])/2;
    return RECT;
}

struct RECTANGLE initialize_RECT()
{
    struct RECTANGLE RECT;

    RECT.left=1000000.0;
    RECT.top=1000000.0;
    RECT.bottom=0.0;
    RECT.right=0.0;

    return RECT;
}

RECTANGLE generate_maximum_rotation(int W, int H, float R, int X, int Y, float zoom, int type)
{
    RECTANGLE RECT;
    componenta CMP;

    RECT = initialize_RECT();

    if(type!=9)
    {
        for(int i=0; i>=-90; i--)
        {
            int width = W/8, height = H/4;
            float w1, w2, h1, h2, w, h;

            dreptunghi D;
            coordonate C;
            C.x=X, C.y=Y;

            w1=-(width*4-width/1.7)*R*zoom+X, w2=(width*4-width/1.7)*R*zoom+X,
            h1=-(height*2-height/2.7)*R*zoom+Y, h2=(height*2-height/2.7)*R*zoom+Y;
            D=create_struct_rectangle(w1,w2,h1,h2);
            D=translate_rectangle(D,C);
            CMP=RotateRectangle(C,D,i,1);

            RECT.left=min(RECT.left,CMP.points[6]);
            RECT.top=min(RECT.top,CMP.points[1]);
            RECT.right=max(RECT.right,CMP.points[2]);
            RECT.bottom=max(RECT.bottom,CMP.points[5]);
        }
    }
    else if(type==9)
    {
        for(int i=0; i>=-90; i--)
        {
            int width = W/8, height = H/4;
            float w1, w2, h1, h2, w, h;

            dreptunghi D;
            coordonate C;
            C.x=X, C.y=Y;

            w1=-2*width*R*zoom+X, w2=width*R*zoom+X,
            h1=-(height*2-height/2.7)*R*zoom+Y, h2=(height*2-height/2.7)*R*zoom+Y;
            D=create_struct_rectangle(w1,w2,h1,h2);
            D=translate_rectangle(D,C);
            CMP=RotateRectangle(C,D,i,1);

            RECT.left=min(RECT.left,CMP.points[6]);
            RECT.top=min(RECT.top,CMP.points[1]);
            RECT.right=max(RECT.right,CMP.points[2]);
            RECT.bottom=max(RECT.bottom,CMP.points[5]);
        }
    }

    return RECT;
}

void generate_rectangle_full_struct(struct RECTANGLE_FULL RECT_FULL[], componenta CMP[], int type)
{
    if(type!=9)
    {
        RECT_FULL[1]=generate_coordinates_full(CMP[1]);
        RECT_FULL[2]=generate_coordinates_full(CMP[2]);
        RECT_FULL[3]=generate_coordinates_full(CMP[3]);
    }
    else if(type==9)
    {
        RECT_FULL[1]=generate_coordinates_full(CMP[1]);
        RECT_FULL[2]=generate_coordinates_full(CMP[2]);
        RECT_FULL[3]=generate_coordinates_full(CMP[3]);
        RECT_FULL[4]=generate_coordinates_full(CMP[4]);
    }
}

void generate_rectangle_struct(RECTANGLE RECT[], componenta CMP[], int type)
{
    if(type!=9)
    {
        RECT[1]=generate_coordinates(CMP[1]);
        RECT[2]=generate_coordinates(CMP[2]);
        RECT[3]=generate_coordinates(CMP[3]);
    }
    else if(type==9)
    {
        RECT[1]=generate_coordinates(CMP[1]);
        RECT[2]=generate_coordinates(CMP[2]);
        RECT[3]=generate_coordinates(CMP[3]);
        RECT[4]=generate_coordinates(CMP[4]);
    }
}

int convert_y_to_angle(int y, int top_fader)
{
    return (top_fader-y)*3;
}

int convert_angle_to_y(int angle, int top_fader)
{
    //if(angle == 0)
    return top_fader-angle/3;
}

float convert_y_to_zoom(int y, int center_fader)
{
    float conversion;
    y=-(y-center_fader);
    conversion=1.0*y/260;
    return conversion;
}

int convert_zoom_to_y(float zoom, int center_fader)
{
    return center_fader-zoom*260;
}





//Tudor ILADE pana jos


int getIndexOfComponent(SITUATIA_TABLEI project, int x, int y, float R)
{
    for(int i=0; i<project.v.size(); i++)
    {
        if(x>=project.v[i].outsideRect.left && x <= project.v[i].outsideRect.right &&
                (y>=project.v[i].outsideRect.top && y<=project.v[i].outsideRect.bottom))
        {
            return i;
        }
    }
    return -1;
}

componenta CMP[30];


///Verifica daca a fost dat click pe o legatura

int isLinking(SITUATIA_TABLEI project, int w, int h, int x, int y, float R,componenta CMP[], int ndxCmp=-1)
{
    int ndx = getIndexOfComponent(project, x,y,R);
    if(ndx == - 1)
        return 0;
    if(ndx == ndxCmp)
        return 0;
    COMPONENTE cmp = project.v[ndx];
    if(cmp.type != 9)
    {

        if(x>=cmp.coordinates[1].left_top.x && x <= cmp.coordinates[1].right_bottom.x &&
                (y>=cmp.coordinates[1].right_top.y&&y<=cmp.coordinates[1].left_bottom.y))
        {
            return 1;
        }

        if(x>=cmp.coordinates[1].left_bottom.x && x <= cmp.coordinates[1].right_top.x &&
                (y>=cmp.coordinates[1].left_top.y && y<=cmp.coordinates[1].right_bottom.y))
        {
            return 1;
        }
        if(x>=cmp.coordinates[1].right_bottom.x && x <= cmp.coordinates[1].left_top.x &&
                (y>=cmp.coordinates[1].left_bottom.y&&y<=cmp.coordinates[1].right_top.y))
        {

            return 1;
        }
        if(x>=cmp.coordinates[1].right_top.x && x <= cmp.coordinates[1].left_bottom.x &&
                (y>=cmp.coordinates[1].right_bottom.y&&y<=cmp.coordinates[1].left_top.y))
        {
            return 1;
        }


        if(x>=cmp.coordinates[2].left_bottom.x && x <= cmp.coordinates[2].right_top.x &&
                (y>=cmp.coordinates[2].left_top.y && y<=cmp.coordinates[2].right_bottom.y))
        {
            return 2;
        }
        if(x>=cmp.coordinates[2].right_bottom.x && x <= cmp.coordinates[2].left_top.x &&
                (y>=cmp.coordinates[2].left_bottom.y&&y<=cmp.coordinates[2].right_top.y))
        {
            return 2;

        }
        if(x>=cmp.coordinates[2].left_top.x && x <= cmp.coordinates[2].right_bottom.x &&
                (y>=cmp.coordinates[2].right_top.y&&y<=cmp.coordinates[2].left_bottom.y))
        {
            return 2;
        }
        if(x>=cmp.coordinates[2].right_top.x && x <= cmp.coordinates[2].left_bottom.x &&
                (y>=cmp.coordinates[2].right_bottom.y&&y<=cmp.coordinates[2].left_top.y))
        {
            return 2;
        }


        return 0;
    }

    else
    {
        if(x>=cmp.coordinates[1].left_bottom.x && x <= cmp.coordinates[1].right_top.x &&
                (y>=cmp.coordinates[1].left_top.y && y<=cmp.coordinates[1].right_bottom.y))
        {
            return 1;
        }
        if(x>=cmp.coordinates[1].right_bottom.x && x <= cmp.coordinates[1].left_top.x &&
                (y>=cmp.coordinates[1].left_bottom.y&&y<=cmp.coordinates[1].right_top.y))
        {

            return 1;
        }
        if(x>=cmp.coordinates[1].left_top.x && x <= cmp.coordinates[1].right_bottom.x &&
                (y>=cmp.coordinates[1].right_top.y&&y<=cmp.coordinates[1].left_bottom.y))
        {
            return 1;
        }
        if(x>=cmp.coordinates[1].right_top.x && x <= cmp.coordinates[1].left_bottom.x &&
                (y>=cmp.coordinates[1].right_bottom.y&&y<=cmp.coordinates[1].left_top.y))
        {
            return 1;
        }



        if(x>=cmp.coordinates[2].left_bottom.x && x <= cmp.coordinates[2].right_top.x &&
                (y>=cmp.coordinates[2].left_top.y && y<=cmp.coordinates[2].right_bottom.y))
        {
            return 2;
        }
        if(x>=cmp.coordinates[2].right_bottom.x && x <= cmp.coordinates[2].left_top.x &&
                (y>=cmp.coordinates[2].left_bottom.y&&y<=cmp.coordinates[2].right_top.y))
        {

            return 2;
        }
        if(x>=cmp.coordinates[2].left_top.x && x <= cmp.coordinates[2].right_bottom.x &&
                (y>=cmp.coordinates[2].right_top.y&&y<=cmp.coordinates[2].left_bottom.y))
        {
            return 2;
        }
        if(x>=cmp.coordinates[2].right_top.x && x <= cmp.coordinates[2].left_bottom.x &&
                (y>=cmp.coordinates[2].right_bottom.y&&y<=cmp.coordinates[2].left_top.y))
        {
            return 2;
        }


        if(x>=cmp.coordinates[3].left_bottom.x && x <= cmp.coordinates[3].right_top.x &&
                (y>=cmp.coordinates[3].left_top.y && y<=cmp.coordinates[3].right_bottom.y))
        {
            return 3;
        }
        if(x>=cmp.coordinates[3].right_bottom.x && x <= cmp.coordinates[3].left_top.x &&
                (y>=cmp.coordinates[3].left_bottom.y&&y<=cmp.coordinates[3].right_top.y))
        {

            return 3;
        }
        if(x>=cmp.coordinates[3].left_top.x && x <= cmp.coordinates[3].right_bottom.x &&
                (y>=cmp.coordinates[3].right_top.y&&y<=cmp.coordinates[3].left_bottom.y))
        {
            return 3;
        }
        if(x>=cmp.coordinates[3].right_top.x && x <= cmp.coordinates[3].left_bottom.x &&
                (y>=cmp.coordinates[3].right_bottom.y&&y<=cmp.coordinates[3].left_top.y))
        {
            return 3;
        }

        return 0;
    }
    return 0;
}



///Deseneaza linia de legatura
void drawLine(int x1, int y1, int x2, int y2, int cul, int type)
{
    if(type==1)
    {
        setcolor(cul);
        line(x1,y1,(x1+x2)/2,y1);
        line((x1+x2)/2,y1,(x1+x2)/2,y2);
        line((x1+x2)/2,y2,x2,y2);
    }
    else if(type==2)
    {
        setcolor(cul);
        line(x1,y1,x1,y2);
        line(x1,y2,x2,y2);

    }
    else if(type==3)
    {
        setcolor(cul);
        line(x1,y1,x2,y1);
        line(x2,y1,x2,y2);
    }
    else if(type==4)
    {
        setcolor(cul);
        line(x1,y1,x1,(y1+y2)/2);
        line(x1,(y1+y2)/2,x2,(y1+y2)/2);
        line(x2,(y1+y2)/2,x2,y2);

    }
}


///Functie care creaza un obiect pe tabla
SITUATIA_TABLEI creare_obiect(SITUATIA_TABLEI &tabla, int type, int x, int y, int w, int h, float R, RECTANGLE RECT[], RECTANGLE_FULL RECT_FULL[], RECTANGLE outSideRect)
{
    COMPONENTE cmp;
    cmp.x1 = x;
    cmp.y1 = y;
    cmp.type = type;
    cmp.R = R;
    int W = w/10;
    int H = h/16;
    int width = W/8;
    int height = H/4;
    cmp.outsideRect = outSideRect;
    cmp.rect.bottom=RECT[1].bottom;
    cmp.rect.top=RECT[1].top;
    cmp.rect.left=RECT[1].left;
    cmp.rect.right=RECT[1].right;
    cmp.nodes[0] = RECT[2];
    cmp.nodes[1] = RECT[3];
    cmp.nodes[2] = RECT[4];
    cmp.coordinates[0]=RECT_FULL[1];
    cmp.coordinates[1]=RECT_FULL[2];
    cmp.coordinates[2]=RECT_FULL[3];
    cmp.coordinates[3]=RECT_FULL[4];

    cmp.zoom = 1.0;
    tabla.v.push_back(cmp);
    return tabla;
}
///Verifica coliziuni pe tabla
bool isColision(RECTANGLE outSideRectangle,int h,int w,SITUATIA_TABLEI tabla, int R, int type, int ndxCmp = -1)
{
    int H = h/16;
    int W = w/10;
    RECTANGLE t;
    int width_rectangle = w/8;
    int height_rectangle = h/12;
    t.left = width_rectangle*R;
    t.top = height_rectangle*R;
    t.right = (w-width_rectangle-width_rectangle/8)*R;
    t.bottom = (h-height_rectangle)*R;
    if(outSideRectangle.left<t.left || outSideRectangle.right>t.right || outSideRectangle.top < t.top || outSideRectangle.bottom > t.bottom)
    {
        return true;
    }
    if(!tabla.v.empty())
    {
        for(int i=0; i<tabla.v.size(); i++)
        {
            if(i != ndxCmp)
            {
                if(outSideRectangle.top<=tabla.v[i].outsideRect.bottom && outSideRectangle.left<=tabla.v[i].outsideRect.right &&
                        outSideRectangle.bottom>=tabla.v[i].outsideRect.bottom&&outSideRectangle.right>=tabla.v[i].outsideRect.right)
                    return true;

                if(outSideRectangle.top<=tabla.v[i].outsideRect.bottom && outSideRectangle.right>=tabla.v[i].outsideRect.left&&
                        outSideRectangle.bottom>tabla.v[i].outsideRect.bottom&&outSideRectangle.left<tabla.v[i].outsideRect.left)
                    return true;

                if(outSideRectangle.top==tabla.v[i].outsideRect.top && outSideRectangle.right==tabla.v[i].outsideRect.right&&
                        outSideRectangle.bottom==tabla.v[i].outsideRect.bottom && outSideRectangle.left==tabla.v[i].outsideRect.left)
                    return true;

                if(outSideRectangle.right>=tabla.v[i].outsideRect.left && outSideRectangle.left<=tabla.v[i].outsideRect.left&&
                        outSideRectangle.top<=tabla.v[i].outsideRect.top && outSideRectangle.bottom>=tabla.v[i].outsideRect.top)
                    return true;

                if(outSideRectangle.left<=tabla.v[i].outsideRect.right && outSideRectangle.right>=tabla.v[i].outsideRect.right&&
                        outSideRectangle.bottom>=tabla.v[i].outsideRect.top && outSideRectangle.top<=tabla.v[i].outsideRect.top)
                    return true;

                if(outSideRectangle.left>=tabla.v[i].outsideRect.left&&outSideRectangle.right<=tabla.v[i].outsideRect.right&&
                        outSideRectangle.bottom>=tabla.v[i].outsideRect.top&&outSideRectangle.top<=tabla.v[i].outsideRect.top)
                    return true;

                if(outSideRectangle.left>=tabla.v[i].outsideRect.left&&outSideRectangle.right<=tabla.v[i].outsideRect.right&&
                        outSideRectangle.top<=tabla.v[i].outsideRect.bottom&&outSideRectangle.bottom>=tabla.v[i].outsideRect.bottom)
                    return true;

                if(outSideRectangle.right>=tabla.v[i].outsideRect.left&&outSideRectangle.left<=tabla.v[i].outsideRect.left&&
                        outSideRectangle.top>=tabla.v[i].outsideRect.top&&outSideRectangle.bottom<=tabla.v[i].outsideRect.bottom)
                    return true;

                if(outSideRectangle.left<=tabla.v[i].outsideRect.right&&outSideRectangle.right>=tabla.v[i].outsideRect.right&&
                        outSideRectangle.top>=tabla.v[i].outsideRect.top&&outSideRectangle.bottom<=tabla.v[i].outsideRect.bottom)
                    return true;
            }
        }
    }
    return false;
}

///Sterge tabla si tot ce a fost desenat
SITUATIA_TABLEI stergere_tabla(SITUATIA_TABLEI tabla)
{
    tabla.v.clear();
    tabla.p.clear();
    return tabla;
}

///Deseneaza componentele ce au fost luate prin citirea fisierului binar
void draw_components_from_file(SITUATIA_TABLEI tabla, int W, int H)
{
    struct componenta CMP[30];

    for(int i=0; i<tabla.v.size(); i++)
    {
        draw_components_on_working_table(tabla.v[i].type,W,H, tabla.v[i].x1, tabla.v[i].y1, tabla.v[i].R,tabla.v[i].angle,tabla.v[i].zoom,WHITE,CMP);
    }
    for(int i=0; i<tabla.p.size(); i++)
    {
        drawLine(tabla.p[i].first.x, tabla.p[i].first.y, tabla.p[i].second.x,tabla.p[i].second.y,WHITE, tabla.p[i].first.type);
    }
}


int isComponentselected(SITUATIA_TABLEI project,int x, int y, float R)
{
    if(project.v.size()>0)
        for(int i=0; i<project.v.size(); i++)
        {

            if(x>=project.v[i].outsideRect.left && x <= project.v[i].outsideRect.right&&
                    (y>=project.v[i].outsideRect.top&&y<=project.v[i].outsideRect.bottom))
                return project.v[i].type;
        }

    return 0;
}


void drawComponentsXSelected(SITUATIA_TABLEI project, int ndx, int W, int H, int R, int color)
{
    componenta CMP[30];

    for(int i=0; i<project.v.size(); i++)
        if(i!=ndx)
            draw_components_on_working_table(project.v[i].type,W,H,project.v[i].x1,project.v[i].y1,project.v[i].R,project.v[i].angle,project.v[i].zoom,WHITE,CMP);

    if(!project.p.empty())
        for(int i=0; i<project.p.size(); i++)
            if(project.p[i].first.ndxParent!=ndx && project.p[i].second.ndxParent!=ndx)
                drawLine(project.p[i].first.x,project.p[i].first.y,project.p[i].second.x,project.p[i].second.y,color,project.p[i].first.type);
}

void draw_black(SITUATIA_TABLEI project, int ndxCmp, int color)
{
    int x,y;
    int xConnection, yConnection;
    for(int i=0; i<project.v[ndxCmp].legatura.size(); i++)
    {
        if(project.v[ndxCmp].legatura[i].first.ndxParent == ndxCmp)
            drawLine(project.v[ndxCmp].legatura[i].first.x,project.v[ndxCmp].legatura[i].first.y,project.v[ndxCmp].legatura[i].second.x,project.v[ndxCmp].legatura[i].second.y, color,project.v[ndxCmp].legatura[i].first.type);
        else if(project.v[ndxCmp].legatura[i].second.ndxParent == ndxCmp)
            drawLine(project.v[ndxCmp].legatura[i].second.xConnection,project.v[ndxCmp].legatura[i].second.yConnection,project.v[ndxCmp].legatura[i].second.x,project.v[ndxCmp].legatura[i].second.y, color,project.v[ndxCmp].legatura[i].second.type);
    }
}


void drawAllComponents(SITUATIA_TABLEI project, int W, int H, int R, int color)
{
    componenta CMP[30];
    RECTANGLE RECT[5];
    int cl;
    if(color == YELLOW)
        cl = WHITE;
    else
        cl = color;

    if(!project.v.empty())
        for(int ndxCmp=0; ndxCmp<project.v.size(); ndxCmp++)
        {
            draw_components_on_working_table(project.v[ndxCmp].type,W,H,project.v[ndxCmp].x1,project.v[ndxCmp].y1,project.v[ndxCmp].R,project.v[ndxCmp].angle,project.v[ndxCmp].zoom,cl,CMP);
        }

    if(!project.p.empty())
        for(int i=0; i<project.p.size(); i++)
            drawLine(project.p[i].first.x,project.p[i].first.y,project.p[i].second.x,project.p[i].second.y,color,project.p[i].first.type);
}



int outSideTable(int x, int y, int h, int w, int R,RECTANGLE outSideRect, int type=-1)
{
    if(type==-1)
    {
        RECTANGLE t;
        int width_rectangle = w/8;
        int height_rectangle = h/12;
        t.left = width_rectangle*R;
        t.top = height_rectangle*R;
        t.right = 7*width_rectangle*R;
        t.bottom = 11*height_rectangle*R;

        if(x<t.left || x>t.right || y < t.top || y > t.bottom)
            return 1;
        return 0;
    }
    RECTANGLE t;
    int H = h/16;
    int W = w/10;
    int width_r = W/8*R;
    int height_r = H/4*R;
    int width_rectangle = w/8;
    int height_rectangle = h/12;

    t.left = width_rectangle*R;
    t.top = height_rectangle*R;
    t.right = 7*width_rectangle*R;
    t.bottom = 11*height_rectangle*R;
    if(outSideRect.left<t.left-5|| outSideRect.right>t.right+10|| outSideRect.top < t.top-34 || outSideRect.bottom > t.bottom + 34)
        return 1;
    return 0;
}


void draw_moving_line(SITUATIA_TABLEI project, int ndxCmp, int color, int W, int H, int R, RECTANGLE RECT[])
{
    for(int i = 0; i<project.p.size(); i++)

        if(project.p[i].first.ndxParent == ndxCmp)
        {
            if(project.v[project.p[i].first.ndxParent].type == 9)
            {

                if(project.p[i].first.sd == 1)
                {
                    drawLine(project.p[i].first.x,project.p[i].first.y,project.p[i].second.x, project.p[i].second.y, BLACK,project.p[i].first.type);
                    drawLine(RECT[2].xCenter,RECT[2].yCenter,project.p[i].second.x,project.p[i].second.y, color,project.p[i].first.type);
                }
                else if(project.p[i].first.sd == 2)
                {
                    drawLine(project.p[i].first.x,project.p[i].first.y,project.p[i].second.x, project.p[i].second.y, BLACK,project.p[i].first.type);
                    drawLine(RECT[3].xCenter, RECT[3].yCenter, project.p[i].second.x,project.p[i].second.y, color,project.p[i].first.type);
                }
                else if(project.p[i].first.sd == 3)
                {
                    drawLine(project.p[i].first.x,project.p[i].first.y,project.p[i].second.x, project.p[i].second.y, BLACK,project.p[i].first.type);
                    drawLine(RECT[4].xCenter, RECT[4].yCenter, project.p[i].second.x,project.p[i].second.y, color,project.p[i].first.type);
                }
            }
            else if(project.v[project.p[i].first.ndxParent].type != 9)
            {
                if(project.p[i].first.sd == 1)
                {
                    drawLine(project.p[i].first.x,project.p[i].first.y,project.p[i].second.x,project.p[i].second.y, BLACK,project.p[i].first.type);
                    drawLine(RECT[2].xCenter,RECT[2].yCenter,project.p[i].second.x,project.p[i].second.y, color,project.p[i].first.type);
                }
                else if(project.p[i].first.sd == 2)
                {
                    drawLine(project.p[i].first.x,project.p[i].first.y,project.p[i].second.x,project.p[i].second.y, BLACK,project.p[i].first.type);
                    drawLine(RECT[3].xCenter,RECT[3].yCenter,project.p[i].second.x,project.p[i].second.y, color,project.p[i].first.type);
                }
            }
        }
        else if(project.p[i].second.ndxParent == ndxCmp)
        {
            if(project.v[project.p[i].second.ndxParent].type == 9)
            {
                if(project.p[i].second.sd==1)
                {
                    int type;
                    if(project.p[i].second.type == 2)
                        type = 3;
                    else if(project.p[i].second.type == 3)
                        type = 2;
                    else
                        type = project.p[i].second.type;

                    drawLine(project.p[i].second.x,project.p[i].second.y,project.p[i].first.x,project.p[i].first.y, BLACK,type);
                    drawLine(RECT[2].xCenter,RECT[2].yCenter,project.p[i].first.x,project.p[i].first.y, color,type);
                }
                else if(project.p[i].second.sd == 2)
                {
                    int type;
                    if(project.p[i].second.type == 2)
                        type = 3;
                    else if(project.p[i].second.type == 3)
                        type = 2;
                    else
                        type =project.p[i].second.type;

                    drawLine(project.p[i].second.x,project.p[i].second.y,project.p[i].first.x,project.p[i].first.y, BLACK,type);
                    drawLine(RECT[3].xCenter,RECT[3].yCenter,project.p[i].first.x, project.p[i].first.y, color,type);

                }
                else if(project.p[i].second.sd == 3)
                {
                    int type;
                    if(project.p[i].second.type == 2)
                        type = 3;
                    else if(project.p[i].second.type == 3)
                        type = 2;
                    else
                        type = project.p[i].second.type;

                    drawLine(project.p[i].second.x,project.p[i].second.y,project.p[i].first.x,project.p[i].first.y, BLACK,type);
                    drawLine(RECT[4].xCenter,RECT[4].yCenter,project.p[i].first.x, project.p[i].first.y, color,type);
                }
            }
            else if(project.v[project.p[i].second.ndxParent].type != 9)
            {
                if(project.p[i].second.sd==1)
                {
                    int type;
                    if(project.p[i].second.type == 2)
                        type = 3;
                    else if(project.p[i].second.type == 3)
                        type = 2;
                    else
                        type = project.p[i].second.type;
                    drawLine(project.p[i].second.x,project.p[i].second.y,project.p[i].first.x,project.p[i].first.y, BLACK,type);
                    drawLine(RECT[2].xCenter,RECT[2].yCenter,project.p[i].first.x,project.p[i].first.y, color,type);
                }
                else if(project.p[i].second.sd==2)
                {
                    int type;
                    if(project.p[i].second.type == 2)
                        type = 3;
                    else if(project.p[i].second.type == 3)
                        type = 2;
                    else
                        type = project.p[i].second.type;

                    drawLine(project.p[i].second.x,project.p[i].second.y,project.p[i].first.x,project.p[i].first.y, BLACK,type);
                    drawLine(RECT[3].xCenter,RECT[3].yCenter,project.p[i].first.x,project.p[i].first.y, color,type);
                }

            }
        }
}


void drawAllLinesBack(SITUATIA_TABLEI project,int ndxCmp,int W,int H,int R)
{
    int width = W/10/8;
    int height = H/16/4;

    int width_centered = 4*width*R;
    int height_centered = 2*height*R;

    if(project.v[ndxCmp].type != 9)
    {
        for(int i=0; i<project.p.size(); i++)
        {
            if(project.p[i].first.ndxParent == ndxCmp)
            {
                if(project.p[i].first.sd == 2)
                    drawLine(project.p[i].first.x,project.p[i].first.y,project.p[i].second.x,project.p[i].second.y, BLACK,project.p[i].first.type);
                else
                    drawLine(project.p[i].first.x,project.p[i].first.y,project.p[i].second.x,project.p[i].second.y, BLACK,project.p[i].first.type);
            }
            if(project.p[i].second.ndxParent == ndxCmp)
            {
                if(project.p[i].second.sd==1)
                {
                    int type;
                    if(project.p[i].second.type == 2)
                        type = 3;
                    else if(project.p[i].second.type == 3)
                        type = 2;
                    else
                        type = project.p[i].second.type;
                    drawLine(project.p[i].second.x,project.p[i].second.y,project.p[i].first.x,project.p[i].first.y, BLACK,type);
                }
                else
                {
                    int type;
                    if(project.p[i].second.type == 2)
                        type = 3;
                    else if(project.p[i].second.type == 3)
                        type = 2;
                    else
                        type = project.p[i].second.type;
                    drawLine(project.p[i].second.x,project.p[i].second.y,project.p[i].first.x,project.p[i].first.y, BLACK,type);
                }
            }
        }
    }
    if(project.v[ndxCmp].type == 9)
    {
        for(int i=0; i<project.p.size(); i++)
        {
            if(project.p[i].first.ndxParent == ndxCmp)
            {
                if(project.p[i].first.sd == 1)
                    drawLine(project.p[i].first.x,project.p[i].first.y,project.p[i].second.x,project.p[i].second.y, BLACK,project.p[i].first.type);
                else if(project.p[i].first.sd == 2)
                    drawLine(project.p[i].first.x,project.p[i].first.y,project.p[i].second.x,project.p[i].second.y, BLACK,project.p[i].first.type);
                else if(project.p[i].first.sd == 3)
                    drawLine(project.p[i].first.x,project.p[i].first.y,project.p[i].second.x,project.p[i].second.y, BLACK,project.p[i].first.type);
            }
            if(project.p[i].second.ndxParent == ndxCmp)
            {
                if(project.p[i].second.sd==1)
                {
                    int type;
                    if(project.p[i].second.type == 2)
                        type = 3;
                    else if(project.p[i].second.type == 3)
                        type = 2;
                    else
                        type = project.p[i].second.type;

                    drawLine(project.p[i].second.x,project.p[i].second.y,project.p[i].first.x,project.p[i].first.y, BLACK,type);
                }
                else if(project.p[i].second.sd == 2)
                {
                    int type;
                    if(project.p[i].second.type == 2)
                        type = 3;
                    else if(project.p[i].second.type == 3)
                        type = 2;
                    else
                        type = project.p[i].second.type;
                    drawLine(project.p[i].second.x,project.p[i].second.y,project.p[i].first.x,project.p[i].first.y, BLACK,type);
                }
                else
                {
                    int type;
                    if(project.p[i].second.type == 2)
                        type = 3;
                    else if(project.p[i].second.type == 3)
                        type = 2;
                    else
                        type = project.p[i].second.type;
                    drawLine(project.p[i].second.x,project.p[i].second.y,project.p[i].first.x,project.p[i].first.y, BLACK,type);
                }
            }
        }
    }
}

SITUATIA_TABLEI actualizareTabla(SITUATIA_TABLEI project, int ndxCmp, int x, int y, int w, int h, int R, int angle,float zoom,RECTANGLE RECT[], RECTANGLE_FULL RECT_FULL[], RECTANGLE outSideRectangle)
{
    int width = w/10/8;
    int height = h/16/4;
    int width_centered = 4*width*R;
    int height_centered = 2*height*R;
    project.v[ndxCmp].x1 = x;
    project.v[ndxCmp].y1 = y;
    int H = h/16;
    int W = w/10;
    int width_r = W/8*R;
    int height_r = H/4*R;
    project.v[ndxCmp].outsideRect = outSideRectangle;
    project.v[ndxCmp].rect = RECT[1];
    project.v[ndxCmp].nodes[0] = RECT[2];
    project.v[ndxCmp].nodes[1] = RECT[3];
    project.v[ndxCmp].nodes[2] = RECT[4];
    project.v[ndxCmp].coordinates[0] = RECT_FULL[1];
    project.v[ndxCmp].coordinates[1] = RECT_FULL[2];
    project.v[ndxCmp].coordinates[2] = RECT_FULL[3];
    project.v[ndxCmp].coordinates[3] = RECT_FULL[4];


    if(angle != project.v[ndxCmp].angle)
        project.v[ndxCmp].angle = angle;
    if(zoom != project.v[ndxCmp].zoom)
        project.v[ndxCmp].zoom = zoom;


    if(project.v[ndxCmp].type == 9)
    {
        for(int i=0; i<project.v[ndxCmp].legatura.size(); i++)
        {
            if(project.v[ndxCmp].legatura[i].first.ndxParent == ndxCmp)
            {
                if(project.v[ndxCmp].legatura[i].first.sd == 1)
                {
                    project.v[ndxCmp].legatura[i].first.x =project.v[ndxCmp].nodes[0].xCenter;
                    project.v[ndxCmp].legatura[i].first.y =project.v[ndxCmp].nodes[0].yCenter;
                    project.v[ndxCmp].legatura[i].second.xConnection =project.v[ndxCmp].nodes[0].xCenter;
                    project.v[ndxCmp].legatura[i].second.yConnection =project.v[ndxCmp].nodes[0].yCenter;
                    for(int j = 0; j<project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura.size(); j++)
                    {
                        if(project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].first.ndxParent == ndxCmp &&
                                project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].second.ndxParent == project.v[ndxCmp].legatura[i].second.ndxParent)
                        {
                            project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].first.x = project.v[ndxCmp].nodes[0].xCenter;
                            project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].first.y = project.v[ndxCmp].nodes[0].yCenter;
                            project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].second.xConnection =  project.v[ndxCmp].nodes[0].xCenter;
                            project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].second.yConnection = project.v[ndxCmp].nodes[0].yCenter;
                        }
                    }
                }
                else if(project.v[ndxCmp].legatura[i].first.sd == 2)
                {
                    project.v[ndxCmp].legatura[i].first.x = project.v[ndxCmp].nodes[1].xCenter;
                    project.v[ndxCmp].legatura[i].first.y = project.v[ndxCmp].nodes[1].yCenter;
                    project.v[ndxCmp].legatura[i].second.xConnection = project.v[ndxCmp].nodes[1].xCenter;
                    project.v[ndxCmp].legatura[i].second.yConnection = project.v[ndxCmp].nodes[1].yCenter;
                    for(int j = 0; j<project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura.size(); j++)
                    {
                        if(project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].first.ndxParent == ndxCmp &&
                                project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].second.ndxParent == project.v[ndxCmp].legatura[i].second.ndxParent)
                        {
                            project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].first.x =  project.v[ndxCmp].nodes[1].xCenter;
                            project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].first.y =  project.v[ndxCmp].nodes[1].yCenter;
                            project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].second.xConnection =  project.v[ndxCmp].nodes[1].xCenter;
                            project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].second.yConnection =  project.v[ndxCmp].nodes[1].yCenter;
                        }
                    }
                }
                else if(project.v[ndxCmp].legatura[i].first.sd == 3)
                {
                    project.v[ndxCmp].legatura[i].first.x =project.v[ndxCmp].nodes[2].xCenter;
                    project.v[ndxCmp].legatura[i].first.y =project.v[ndxCmp].nodes[2].yCenter;
                    project.v[ndxCmp].legatura[i].second.xConnection =project.v[ndxCmp].nodes[2].xCenter;
                    project.v[ndxCmp].legatura[i].second.yConnection =project.v[ndxCmp].nodes[2].yCenter;
                    for(int j = 0; j<project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura.size(); j++)
                    {
                        if(project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].first.ndxParent == ndxCmp &&
                                project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].second.ndxParent == project.v[ndxCmp].legatura[i].second.ndxParent)
                        {
                            project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].first.x = project.v[ndxCmp].nodes[2].xCenter;
                            project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].first.y = project.v[ndxCmp].nodes[2].yCenter;
                            project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].second.xConnection = project.v[ndxCmp].nodes[2].xCenter;
                            project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].second.yConnection = project.v[ndxCmp].nodes[2].yCenter;
                        }
                    }
                }
            }
            if(project.v[ndxCmp].legatura[i].second.ndxParent == ndxCmp)
            {
                if(project.v[ndxCmp].legatura[i].second.sd==1)
                {
                    project.v[ndxCmp].legatura[i].second.x = project.v[ndxCmp].nodes[0].xCenter;
                    project.v[ndxCmp].legatura[i].second.y = project.v[ndxCmp].nodes[0].yCenter;
                    project.v[ndxCmp].legatura[i].first.xConnection =project.v[ndxCmp].nodes[0].xCenter;
                    project.v[ndxCmp].legatura[i].first.yConnection =project.v[ndxCmp].nodes[0].yCenter;
                    for(int j = 0; j<project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura.size(); j++)
                    {
                        if(project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].second.ndxParent == ndxCmp &&
                                project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].first.ndxParent == project.v[ndxCmp].legatura[i].first.ndxParent)
                        {
                            project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].second.x = project.v[ndxCmp].nodes[0].xCenter;
                            project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].second.y = project.v[ndxCmp].nodes[0].yCenter;
                            project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].first.xConnection =  project.v[ndxCmp].nodes[0].xCenter;
                            project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].first.yConnection =project.v[ndxCmp].nodes[0].yCenter;
                        }
                    }
                }
                else if(project.v[ndxCmp].legatura[i].second.sd==2)
                {
                    project.v[ndxCmp].legatura[i].second.x = project.v[ndxCmp].nodes[1].xCenter;
                    project.v[ndxCmp].legatura[i].second.y = project.v[ndxCmp].nodes[1].yCenter;
                    project.v[ndxCmp].legatura[i].first.xConnection = project.v[ndxCmp].nodes[1].xCenter;
                    project.v[ndxCmp].legatura[i].first.yConnection =project.v[ndxCmp].nodes[1].yCenter;
                    for(int j = 0; j<project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura.size(); j++)
                    {
                        if(project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].second.ndxParent == ndxCmp &&
                                project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].first.ndxParent == project.v[ndxCmp].legatura[i].first.ndxParent)
                        {
                            project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].second.x =  project.v[ndxCmp].nodes[1].xCenter;
                            project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].second.y = project.v[ndxCmp].nodes[1].yCenter;
                            project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].first.xConnection =   project.v[ndxCmp].nodes[1].xCenter;
                            project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].first.yConnection =project.v[ndxCmp].nodes[1].yCenter;
                        }
                    }
                }
                else if(project.v[ndxCmp].legatura[i].second.sd==3)
                {
                    project.v[ndxCmp].legatura[i].second.x = project.v[ndxCmp].nodes[2].xCenter;
                    project.v[ndxCmp].legatura[i].second.y = project.v[ndxCmp].nodes[2].yCenter;
                    project.v[ndxCmp].legatura[i].first.xConnection =project.v[ndxCmp].nodes[2].xCenter;
                    project.v[ndxCmp].legatura[i].first.yConnection =project.v[ndxCmp].nodes[2].yCenter;
                    for(int j = 0; j<project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura.size(); j++)
                    {
                        if(project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].second.ndxParent == ndxCmp &&
                                project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].first.ndxParent == project.v[ndxCmp].legatura[i].first.ndxParent)
                        {
                            project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].second.x = project.v[ndxCmp].nodes[2].xCenter;
                            project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].second.y = project.v[ndxCmp].nodes[2].yCenter;
                            project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].first.xConnection =  project.v[ndxCmp].nodes[2].xCenter;
                            project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].first.yConnection =project.v[ndxCmp].nodes[2].yCenter;
                        }
                    }
                }
            }
        }
    }
    if(project.v[ndxCmp].type != 9)
    {
        for(int i=0; i<project.v[ndxCmp].legatura.size(); i++)
        {
            if(project.v[ndxCmp].legatura[i].first.ndxParent == ndxCmp)
            {
                if(project.v[ndxCmp].legatura[i].first.sd == 2)
                {
                    project.v[ndxCmp].legatura[i].first.x =project.v[ndxCmp].nodes[1].xCenter;
                    project.v[ndxCmp].legatura[i].first.y =project.v[ndxCmp].nodes[1].yCenter;
                    project.v[ndxCmp].legatura[i].second.xConnection =project.v[ndxCmp].nodes[1].xCenter;
                    project.v[ndxCmp].legatura[i].second.yConnection =project.v[ndxCmp].nodes[1].yCenter;
                    for(int j = 0; j<project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura.size(); j++)
                    {
                        if(project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].first.ndxParent == ndxCmp &&
                                project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].second.ndxParent == project.v[ndxCmp].legatura[i].second.ndxParent)
                        {
                            project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].first.x = project.v[ndxCmp].nodes[1].xCenter;
                            project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].first.y = project.v[ndxCmp].nodes[1].yCenter;
                            project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].second.xConnection =  project.v[ndxCmp].nodes[1].xCenter;
                            project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].second.yConnection = project.v[ndxCmp].nodes[1].yCenter;

                        }
                    }
                }
                else
                {
                    project.v[ndxCmp].legatura[i].first.x =project.v[ndxCmp].nodes[0].xCenter;
                    project.v[ndxCmp].legatura[i].first.y = project.v[ndxCmp].nodes[0].yCenter;
                    project.v[ndxCmp].legatura[i].second.xConnection =project.v[ndxCmp].nodes[0].xCenter;
                    project.v[ndxCmp].legatura[i].second.yConnection =project.v[ndxCmp].nodes[0].yCenter;
                    for(int j = 0; j<project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura.size(); j++)
                    {
                        if(project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].first.ndxParent == ndxCmp &&
                                project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].second.ndxParent == project.v[ndxCmp].legatura[i].second.ndxParent)
                        {
                            project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].first.x =project.v[ndxCmp].nodes[0].xCenter;
                            project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].first.y = project.v[ndxCmp].nodes[0].yCenter;
                            project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].second.xConnection = project.v[ndxCmp].nodes[0].xCenter;
                            project.v[project.v[ndxCmp].legatura[i].second.ndxParent].legatura[j].second.yConnection = project.v[ndxCmp].nodes[0].yCenter;

                        }
                    }
                }
            }
            if(project.v[ndxCmp].legatura[i].second.ndxParent == ndxCmp)
            {
                if(project.v[ndxCmp].legatura[i].second.sd==1)
                {
                    project.v[ndxCmp].legatura[i].second.x =project.v[ndxCmp].nodes[0].xCenter;
                    project.v[ndxCmp].legatura[i].second.y = project.v[ndxCmp].nodes[0].yCenter;
                    project.v[ndxCmp].legatura[i].first.xConnection =project.v[ndxCmp].nodes[0].xCenter;
                    project.v[ndxCmp].legatura[i].first.yConnection =project.v[ndxCmp].nodes[0].yCenter;
                    for(int j = 0; j<project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura.size(); j++)
                    {
                        if(project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].second.ndxParent == ndxCmp &&
                                project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].first.ndxParent == project.v[ndxCmp].legatura[i].first.ndxParent)
                        {
                            project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].second.x = project.v[ndxCmp].nodes[0].xCenter;
                            project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].second.y = project.v[ndxCmp].nodes[0].yCenter;
                            project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].first.xConnection = project.v[ndxCmp].nodes[0].xCenter;
                            project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].first.yConnection = project.v[ndxCmp].nodes[0].yCenter;
                        }
                    }
                }
                else
                {
                    project.v[ndxCmp].legatura[i].second.x =project.v[ndxCmp].nodes[1].xCenter;
                    project.v[ndxCmp].legatura[i].second.y = project.v[ndxCmp].nodes[1].yCenter;
                    project.v[ndxCmp].legatura[i].first.xConnection =project.v[ndxCmp].nodes[1].xCenter;
                    project.v[ndxCmp].legatura[i].first.yConnection =project.v[ndxCmp].nodes[1].yCenter;
                    for(int j = 0; j<project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura.size(); j++)
                    {
                        if(project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].second.ndxParent == ndxCmp &&
                                project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].first.ndxParent == project.v[ndxCmp].legatura[i].first.ndxParent)
                        {
                            project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].second.x = project.v[ndxCmp].nodes[1].xCenter;
                            project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].second.y = project.v[ndxCmp].nodes[1].yCenter;
                            project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].first.xConnection =  project.v[ndxCmp].nodes[1].xCenter;
                            project.v[project.v[ndxCmp].legatura[i].first.ndxParent].legatura[j].first.yConnection = project.v[ndxCmp].nodes[1].yCenter;
                        }
                    }
                }
            }
        }
    }
    for(int i=0; i<project.p.size(); i++)
    {
        if(project.v[project.p[i].first.ndxParent].type != 9)
        {
            if(project.p[i].first.ndxParent == ndxCmp)
            {
                if(project.p[i].first.sd == 2)
                {
                    project.p[i].first.x =project.v[ndxCmp].nodes[1].xCenter;
                    project.p[i].first.y =project.v[ndxCmp].nodes[1].yCenter;
                    project.p[i].second.xConnection =project.v[ndxCmp].nodes[1].xCenter;
                    project.p[i].second.yConnection =project.v[ndxCmp].nodes[1].yCenter;
                }
                else
                {
                    project.p[i].first.x =project.v[ndxCmp].nodes[0].xCenter;
                    project.p[i].first.y = project.v[ndxCmp].nodes[0].yCenter;
                    project.p[i].second.xConnection =project.v[ndxCmp].nodes[0].xCenter;
                    project.p[i].second.yConnection =project.v[ndxCmp].nodes[0].yCenter;
                }
            }
        }
        if(project.v[project.p[i].second.ndxParent].type != 9)
        {
            if(project.p[i].second.ndxParent == ndxCmp)
            {
                if(project.p[i].second.sd==1)
                {
                    project.p[i].second.x =project.v[ndxCmp].nodes[0].xCenter;
                    project.p[i].second.y = project.v[ndxCmp].nodes[0].yCenter;
                    project.p[i].first.xConnection =project.v[ndxCmp].nodes[0].xCenter;
                    project.p[i].first.yConnection =project.v[ndxCmp].nodes[0].yCenter;
                }
                else
                {
                    project.p[i].second.x =project.v[ndxCmp].nodes[1].xCenter;
                    project.p[i].second.y =project.v[ndxCmp].nodes[1].yCenter;
                    project.p[i].first.xConnection =project.v[ndxCmp].nodes[1].xCenter;
                    project.p[i].first.yConnection =project.v[ndxCmp].nodes[1].yCenter;
                }
            }
        }
        if(project.v[project.p[i].first.ndxParent].type == 9)
        {
            if(project.p[i].first.ndxParent == ndxCmp)
            {

                if(project.p[i].first.sd == 1)
                {
                    project.p[i].first.x =project.v[ndxCmp].nodes[0].xCenter;
                    project.p[i].first.y =project.v[ndxCmp].nodes[0].yCenter;
                    project.p[i].second.xConnection =project.v[ndxCmp].nodes[0].xCenter;
                    project.p[i].second.yConnection =project.v[ndxCmp].nodes[0].yCenter;
                }
                else if(project.p[i].first.sd == 2)
                {
                    project.p[i].first.x =project.v[ndxCmp].nodes[1].xCenter;
                    project.p[i].first.y =project.v[ndxCmp].nodes[1].yCenter;
                    project.p[i].second.xConnection =project.v[ndxCmp].nodes[1].xCenter;
                    project.p[i].second.yConnection =project.v[ndxCmp].nodes[1].yCenter;
                }
                else if(project.p[i].first.sd == 3)
                {
                    project.p[i].first.x =project.v[ndxCmp].nodes[2].xCenter;
                    project.p[i].first.y =project.v[ndxCmp].nodes[2].yCenter;
                    project.p[i].second.xConnection =project.v[ndxCmp].nodes[2].xCenter;
                    project.p[i].second.yConnection =project.v[ndxCmp].nodes[2].yCenter;
                }
            }
        }
        if(project.v[project.p[i].second.ndxParent].type == 9)
        {
            if(project.p[i].second.ndxParent == ndxCmp)
            {
                if(project.p[i].second.sd==1)
                {
                    project.p[i].second.x =project.v[ndxCmp].nodes[0].xCenter;
                    project.p[i].second.y = project.v[ndxCmp].nodes[0].yCenter;
                    project.p[i].first.xConnection =project.v[ndxCmp].nodes[0].xCenter;
                    project.p[i].first.yConnection =project.v[ndxCmp].nodes[0].yCenter;
                }
                else if(project.p[i].second.sd == 2)
                {
                    project.p[i].second.x =project.v[ndxCmp].nodes[1].xCenter;
                    project.p[i].second.y = project.v[ndxCmp].nodes[1].yCenter;
                    project.p[i].first.xConnection =project.v[ndxCmp].nodes[1].xCenter;
                    project.p[i].first.yConnection =project.v[ndxCmp].nodes[1].yCenter;
                }
                else if(project.p[i].second.sd == 3)
                {
                    project.p[i].second.x =project.v[ndxCmp].nodes[2].xCenter;
                    project.p[i].second.y = project.v[ndxCmp].nodes[2].yCenter;
                    project.p[i].first.xConnection =project.v[ndxCmp].nodes[2].xCenter;
                    project.p[i].first.yConnection =project.v[ndxCmp].nodes[2].yCenter;
                }
            }
        }
    }
    return project;
}

SITUATIA_TABLEI deleteComponent(SITUATIA_TABLEI project, int ndx)
{
    project.v.erase(project.v.begin()+ndx);
    for(int i = 0; i<project.p.size(); i++)
        if(project.p[i].first.ndxParent == ndx)
        {
            project.p.erase(project.p.begin()+i);
            i--;
        }

    for(int i = 0; i<project.p.size(); i++)
        if(project.p[i].second.ndxParent == ndx)
        {
            project.p.erase(project.p.begin()+i);
            i--;
        }

    for(int i = 0; i<project.p.size(); i++)
    {
        if(project.p[i].first.ndxParent > ndx)
            project.p[i].first.ndxParent-=1;
        if(project.p[i].second.ndxParent > ndx)
            project.p[i].second.ndxParent-=1;
    }

    for(int i = 0; i < project.v.size(); i++)
        for(int j=0; j<project.v[i].legatura.size(); j++)
            if(project.v[i].legatura[j].first.ndxParent == ndx)
            {
                project.v[i].legatura.erase(project.v[i].legatura.begin()+j);
                j--;
            }

    for(int i = 0; i < project.v.size(); i++)
        for(int j=0; j<project.v[i].legatura.size(); j++)
            if(project.v[i].legatura[j].second.ndxParent == ndx)
            {
                project.v[i].legatura.erase(project.v[i].legatura.begin()+j);
                j--;
            }

    for(int i = 0; i < project.v.size(); i++)
        for(int j=0; j<project.v[i].legatura.size(); j++)
        {
            if(project.v[i].legatura[j].first.ndxParent > ndx)
            {
                project.v[i].legatura[j].first.ndxParent--;
            }
            if(project.v[i].legatura[j].second.ndxParent > ndx)
            {
                project.v[i].legatura[j].second.ndxParent--;
            }
        }

    return project;
}

int checkLineTypeLink(int type, int x, int y,  int x1, int y1, int x2, int y2)
{
    if(type==1)
    {
        if(x>x1 && x <= (x1+x2)/2 && y<y1+3 && y > y1-3)
            return 1;
        if(x<x1 && x > (x1+x2)/2 && y<y1+3 && y > y1-3)
            return 1;
        if(x>(x1+x2)/2-3 && x<(x1+x2)/2+3 && y<y1 && y>y2)
            return 1;
        if(x>(x1+x2)/2-3 && x<(x1+x2)/2+3 && y>y1 && y<y2)
            return 1;
        if(x>(x1+x2)/2 && x < x2 && y<y2+3 && y > y2-3)
            return 1;
        if(x < (x1+x2)/2 && x > x2 && y<y2+3 && y > y2-3)
            return 1;
        return 0;
    }
    else if(type == 2)
    {
        if(x>x1-3 && x<x1+3 && y>=y1 && y<=y2)
            return 2;
        if(x>x1-3 && x<x1+3 && y<=y1 && y>=y2)
            return 2;
        if(x>x1 && x<x2 && y>y2-3 && y < y2 + 3)
            return 2;
        if(x<x1 && x>x2 && y>y2-3 && y < y2 + 3)
            return 2;
        return 0;
    }
    else if(type == 3)
    {
        if(x>x1 && x < x2 && y>y1-3 && y<y1+3)
            return 3;
        if(x<x1 && x > x2 && y>y1-3 && y<y1+3)
            return 3;
        if(x>x2-3 && x < x2 + 3 && y>y1 && y < y2)
            return 3;
        if(x>x2-3 && x < x2 + 3 && y<y1 && y > y2)
            return 3;
        return 0;
    }
    else if(type == 4)
    {
        if(x>x1-3 && x<x1+3 && y>y1 &&  y<(y1+y2)/2)
            return 4;
        if(x>x1-3 && x<x1+3 && y<y1 &&  y>(y1+y2)/2)
            return 4;
        if(x>x1 && x < x2 && y>(y1+y2)/2-3 && y < (y1+y2)/2+3)
            return 4;
        if(x<x1 && x > x2 && y>(y1+y2)/2-3 && y < (y1+y2)/2+3)
            return 4;
        if(x>x2-3 && x < x2+3 && y > (y1+y2)/2 && y < y2)
            return 4;
        if(x>x2-3 && x < x2+3 && y < (y1+y2)/2 && y > y2)
            return 4;
        return 0;
    }
}


int isLinkSelected(SITUATIA_TABLEI project, int x, int y)
{
    for(int i = 0; i < project.p.size(); i++)
        if(checkLineTypeLink(project.p[i].first.type, x, y, project.p[i].first.x, project.p[i].first.y, project.p[i].first.xConnection, project.p[i].first.yConnection))
            return i;
    return -1;
}


SITUATIA_TABLEI stergeLegatura(SITUATIA_TABLEI project, int ndxLink)
{
    pair<punctLegatura, punctLegatura>P= project.p[ndxLink];
    drawLine(P.first.x, P.first.y,P.first.xConnection, P.first.yConnection, BLACK, P.first.type);
    project.p.erase(project.p.begin()+ndxLink);

    for(int i = 0; i< project.v.size(); i++)
        for(int j = 0; j<project.v[i].legatura.size(); j++)
            if(project.v[i].legatura[j].first.ndxParent == P.first.ndxParent && project.v[i].legatura[j].second.ndxParent == P.second.ndxParent)
            {
                project.v[i].legatura.erase(project.v[i].legatura.begin()+j);
                j--;
            }
    return project;
}

///Actualizeaza stiva curenta
HISTORY actualizareStiva(HISTORY stiva, SITUATIA_TABLEI project)
{
    stiva.UNDO.push(project);
    return stiva;
}

///Verifica daca s-a schimbat panel ul
int checkIfCurrentTable(SITUATIA_TABLEI project, SITUATIA_TABLEI proj)
{
    if(project.v.size()!= proj.v.size())
        return 0;
    if(proj.p.size()!= proj.p.size())
        return 0;
    return 1;
}

///Functia care actualizeaza stiva de Undo si Redo
SITUATIA_TABLEI URfnc(HISTORY &stiva, int UndoRedo, SITUATIA_TABLEI proj)
{
    SITUATIA_TABLEI project;
    if(UndoRedo==1)
    {
        if(stiva.UNDO.size()>0)
        {
            if(stiva.UNDO.size()==1)
            {
                stiva.REDO.push(stiva.UNDO.top());
                stiva.UNDO.pop();
                return project;
            }
            stiva.REDO.push(stiva.UNDO.top());
            stiva.UNDO.pop();
            project = stiva.UNDO.top();
            return project;
        }
        else
            return proj;
    }
    else if(UndoRedo==2)
    {
        if(stiva.REDO.size()>0)
        {
            project = stiva.REDO.top();
            stiva.REDO.pop();
            stiva.UNDO.push(project);
            return project;
        }
        else
            return proj;
    }
}

///Functie care goleste stiva de memorie pt undo si redo
HISTORY emptyStack(HISTORY stackk)
{
    while(!stackk.UNDO.empty())
    {
        stackk.UNDO.pop();
    }
    while(!stackk.REDO.empty())
    {
        stackk.REDO.pop();
    }
    return stackk;
}


///Functie responsabila de a verifica daca circuitul este conectat
int checkIntegrity(SITUATIA_TABLEI project)
{
    //cmp != 9
    vector<int>nodIntraStg(project.v.size()+project.p.size());
    vector<int>nodIeseStg(project.v.size()+project.p.size());
    vector<int>nodIntraDreapta(project.v.size()+project.p.size());
    vector<int>nodIeseDr(project.v.size()+project.p.size());


    //cmp==9
    vector<int>nodIntraStg9(project.v.size()+project.p.size());
    vector<int>nodIeseStg9(project.v.size()+project.p.size());
    vector<int>nodIeseJos(project.v.size()+project.p.size());
    vector<int>nodIntraJos(project.v.size()+project.p.size());
    vector<int>nodIntraSus(project.v.size()+project.p.size());
    vector<int>nodIeseSus(project.v.size()+project.p.size());


    for(int j = 0; j<project.p.size(); j++)
    {
        if(project.v[project.p[j].first.ndxParent].type != 9)
        {

            if(project.p[j].first.sd == 1)
                nodIeseStg[project.p[j].first.ndxParent]++;
            if(project.p[j].first.sd == 2)
                nodIeseDr[project.p[j].first.ndxParent]++;
        }
        if(project.v[project.p[j].second.ndxParent].type != 9)
        {
            if(project.p[j].second.sd == 1)
                nodIntraStg[project.p[j].second.ndxParent]++;
            if(project.p[j].second.sd == 2)
                nodIntraDreapta[project.p[j].second.ndxParent]++;
        }
        if(project.v[project.p[j].first.ndxParent].type == 9)
        {
            if(project.p[j].first.sd == 1)
                nodIntraStg9[project.p[j].first.ndxParent]++;
            if(project.p[j].first.sd == 2)
                nodIntraSus[project.p[j].first.ndxParent]++;
            if(project.p[j].first.sd == 3)
                nodIntraJos[project.p[j].first.ndxParent]++;
        }
        if(project.v[project.p[j].second.ndxParent].type == 9)
        {
            if(project.p[j].second.sd == 1)
                nodIeseStg9[project.p[j].second.ndxParent]++;
            if(project.p[j].second.sd == 2)
                nodIeseSus[project.p[j].second.ndxParent]++;
            if(project.p[j].second.sd == 3)
                nodIeseJos[project.p[j].second.ndxParent]++;
        }
    }

    if(project.v.size()==0)
        return 0;

    for(int i = 0; i<project.v.size(); i++)
    {
        if(project.v[i].type != 9)
        {
            if(nodIntraStg[i]==0 && nodIeseStg[i]==0 && nodIntraDreapta[i]>=0 && nodIeseDr[i]>=0)//Toate intra din dreapta, restul 0
                return 0;
            if(nodIntraStg[i]>=0 && nodIeseStg[i]>=0 && nodIntraDreapta[i]==0 && nodIeseDr[i]==0)//Toate intra din dreapta, restul 0
                return 0;
        }
    }

    for(int i=0; i<project.v.size(); i++)
    {
        if(project.v[i].type == 9)
        {
            if(nodIntraStg9[i]==0 && nodIeseStg9[i]==0 && nodIntraJos[i]>=0 && nodIeseJos[i]>=0 && nodIntraSus[i]>=0 && nodIeseSus[i]>=0)//stanga este 0
                return 0;
            if(nodIntraStg9[i]>=0 && nodIeseStg9[i]>=0 && nodIntraJos[i]==0 && nodIeseJos[i]==0 && nodIntraSus[i]>=0 && nodIeseSus[i]>=0)//jos este 0
                return 0;
            if(nodIntraStg9[i]>=0 && nodIeseStg9[i]>=0 && nodIntraJos[i]>=0 && nodIeseJos[i]>=0 && nodIntraSus[i]==0 && nodIeseSus[i]==0)//sus este 0
                return 0;
        }
    }
    return 1;
}



///Functie responsabila de a deschide pagina html
void openHtml(char *current_path)
{

    LPCTSTR helpFile = path_for_images("prezentare.html",current_path);
    ShellExecute(NULL, "open",  helpFile, NULL, NULL, SW_SHOWNORMAL);

    return;

}

///Functie care verifica proprietatile "Circuitului Fericit"
bool turnBulbOn(SITUATIA_TABLEI project)
{
    // 2 electrical power // 2 resitors// 1 bulb // 1 transistor // 1 voltmeter // 1 ampermeter// 1 diode // 1 fuse  // 1 capacitor
    if(project.light)
        return true;
    int circuit[12];
    for(int i=0; i<12; i++)
        circuit[i]=0;

    if(project.v.empty())
        return false;
    int connected = checkIntegrity(project);
    if(connected)
    {
        for(int i=0; i<project.v.size(); i++)
            circuit[project.v[i].type]++;


        if(circuit[1]==2 && circuit[2] == 1 &&  circuit[3] == 2 &&  circuit[4] == 1 &&  circuit[5] == 1 &&
                circuit[6] == 1 &&  circuit[7] == 1 &&  circuit[8] == 1 &&  circuit[9] == 1)
            return true;
    }
    return false;

}


void colorLines(SITUATIA_TABLEI project, int color)
{
    if(!project.p.empty())
        for(int i=0; i<project.p.size(); i++)
            drawLine(project.p[i].first.x,project.p[i].first.y,project.p[i].second.x,project.p[i].second.y,color,project.p[i].first.type);
}






#endif // STARE_TABLE_H_INCLUDED

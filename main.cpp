///LIBRARIES
#include <iostream>
#include <graphics.h>
#include <string.h>
#include <winuser.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <filesystem>

///HEADERS
#include "startup_page.h"
#include "workplace_page.h"
#include "menu_selection.h"
#include "stare_table.h"
#include "new_project_name_reading_window.h"
#include "drawing_components.h"
#include "messages_panels_main_menu.h"
#include "open_save.h"
#include "change_color_panel.h"
#include "messages_log_panel.h"
#include "edit_component_value.h"
#include "zoom_rotate_fader_workplace.h"
#include "choose_from_two_options.h"
#include "functii_auxiliare.h"

using namespace std;



//Tudor ILADE && Andrei CERBU

int main()
{

    //Tudor Ilade
    DWORD W = GetSystemMetrics(SM_CXSCREEN);
    DWORD H = GetSystemMetrics(SM_CYSCREEN);
    POINT cursorPos;

    RECTANGLE RECT[5];
    RECTANGLE_FULL RECT_FULL[5];
    RECTANGLE MAXIMUM_ROTATION_RECT;

    SWITCHSTATE switcher;
    SITUATIA_TABLEI project;
    HISTORY stackk;

    float R = (float)(W/H), zoom;

    bool panel=false, click_l=false, aprinde=false, turnOn;

    char filename[1024], *current_directory=create_fixed_path();

    int x, y, ans, xMouse, yMouse, component_selected,
        linking, right_menu, left_menu, top_menu, bulb=1,
        undoRedo, type=1, type_line, ndxCmp, cmp, legNdx,
        menu_select,center_fader=36.2*H/32*R, color=WHITE,
        top_fader=19.7*H/22*R, angle, slider, indx;

    int main_window=initwindow(W,H,"Electron");
    draw_main_menu(W,H,R,current_directory);

    while(true)
    {
        //TudorIlade
        //Main Menu
        if(panel==0)
        {
            GetCursorPos(&cursorPos);
            ScreenToClient(GetForegroundWindow(), &cursorPos);

            change_color_icon_startup_page(menu_selection_startup_page(W,H,R,cursorPos.x,cursorPos.y),W,H,R);

            if(ismouseclick(WM_LBUTTONDOWN))
            {
                getmouseclick(WM_LBUTTONDOWN, x, y);
                menu_select=menu_selection_startup_page(W,H,R,x,y);

                switch(menu_select)
                {
                case 0:
                    clearmouseclick(WM_LBUTTONDOWN);
                    break;
                case 1:
                    if(project.open)
                    {
                        //Andrei CERBU
                        int value=choose_from_two_options(W/4,H/4,R);
                        setcurrentwindow(main_window);
                        switch(value)
                        {
                        case 1:
                            draw_working_table(W,H,R,current_directory);

                            drawAllComponents(project,W,H,R,WHITE);
                            panel=1;
                            break;
                        case 2:
                            if(new_project_name_reading_window(W/4,H/4,R,filename)==1)
                            {
                                panel=1;
                                setcurrentwindow(main_window);
                                project=create_project(project,filename);
                                project.open = true;
                                draw_working_table(W,H,R,current_directory);
                            }
                            else
                            {
                                panel=0;
                                setcurrentwindow(main_window);
                            }
                            break;
                        }
                    }
                    //Tudor Ilade
                    else
                    {
                        if(new_project_name_reading_window(W/4,H/4,R,filename)==1)
                        {

                            panel=1;
                            setcurrentwindow(main_window);
                            project=create_project(project,filename);
                            project.open = true;
                            draw_working_table(W,H,R,current_directory);

                        }
                        else
                        {
                            panel=0;
                            setcurrentwindow(main_window);
                        }
                    }
                    break;
                case 2:
                    //Tudor ILADE
                    project=open_dialog(1,project);
                    if(project.ans==-2||project.ans==-1||project.ans==-3)
                    {
                        if(project.ans!=-3)
                            error_code_main_menu(W,H,project.ans);
                        setcurrentwindow(main_window);
                        panel=0;
                    }
                    else
                    {
                        succes_panel_main_menu(W,H);
                        panel=1;
                        setcurrentwindow(main_window);
                        project.open = true;
                        draw_working_table(W,H,R,current_directory);

                        delay(10);
                        draw_components_from_file(project,W,H);
                    }
                    break;
                case 3:
                    openHtml(current_directory);
                    break;
                case 4:
                    closegraph();
                    return 0;
                    break;
                }
            }
        }
        //Workbench
        else if(panel==1)
        {
            GetCursorPos(&cursorPos);
            ScreenToClient(GetForegroundWindow(), &cursorPos);

            change_color_icon_top_menu_workplace_page(W,H,R,top_menu_workplace_page(W,H,R,cursorPos.x,cursorPos.y));
            change_color_icon_left_menu_workplace_page(W,H,R,left_menu_workplace_page(W,H,R,cursorPos.x,cursorPos.y));
            change_color_icon_right_menu_workplace_page(W,H,R,right_menu_workplace_page(W,H,R,cursorPos.x,cursorPos.y));
//Tudor ILADE
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                getmouseclick(WM_LBUTTONDOWN,x,y);

                top_menu=top_menu_workplace_page(W,H,R,x,y);
                left_menu=left_menu_workplace_page(W,H,R,x,y);
                right_menu=right_menu_workplace_page(W,H,R,x,y);
                undoRedo=undo_redo_menu_workplace_page(W,H,R,x,y);
                component_selected=isComponentselected(project,x,y,R);
                linking=isLinking(project, W,H,x,y,R,CMP);
                switcher=turnLight(W,H,R,x,y,switcher);

                turnOn = turnBulbOn(project);
                if(turnBulbOn(project)&&aprinde)
                    color=YELLOW;
                else //apelez functia aici de stingere
                {
                    readimagefile(path_for_images("becstins.jpg",current_directory),W-W/9+W/34,0.2*H/16,W-W/6.5+W/34,1.6*H/16);
                    color=WHITE;
                }

                if(!turnBulbOn(project) && color==YELLOW)
                {
                    color = WHITE;
                    readimagefile(path_for_images("becstins.jpg",current_directory),W-W/9+W/34,0.2*H/16,W-W/6.5+W/34,1.6*H/16);
                }
//Tudor ILADE
                if(left_menu)
                {
                    messages_log_panel("                                                     ",W,H,R,W/9,H/16);
                    do
                    {
                        if(ismouseclick(WM_LBUTTONDOWN))
                        {
                            getmouseclick(WM_LBUTTONDOWN,xMouse,yMouse);
                            if(!top_menu_workplace_page(W,H,R,xMouse,yMouse) && !left_menu_workplace_page(W,H,R,xMouse,yMouse) &&
                                !right_menu_workplace_page(W,H,R,xMouse,yMouse) && !undo_redo_menu_workplace_page(W,H,R,xMouse,yMouse)&&left_menu)
                            {
                                draw_components_on_working_table(left_menu,W,H,xMouse,yMouse,R,0,1.0,BLACK,CMP);
                                drawAllComponents(project, W, H, R, color);
                                generate_rectangle_struct(RECT, CMP, left_menu);
                                generate_rectangle_full_struct(RECT_FULL,CMP, left_menu);
                                MAXIMUM_ROTATION_RECT=generate_maximum_rotation(W/10,H/16,R,xMouse, yMouse,1.0,left_menu);
                                if(!isColision(MAXIMUM_ROTATION_RECT,H,W,project,R,left_menu))
                                {
                                    draw_components_on_working_table(left_menu,W,H,xMouse,yMouse,R,0,1.0,WHITE,CMP);
                                    generate_rectangle_struct(RECT, CMP,left_menu);
                                    generate_rectangle_full_struct(RECT_FULL,CMP, left_menu);
                                    project=creare_obiect(project,left_menu,xMouse,yMouse,W,H,R, RECT, RECT_FULL, MAXIMUM_ROTATION_RECT);
                                    stackk=actualizareStiva(stackk,project);
                                    messages_log_panel("                                                     ",W,H,R,W/9,H/16);
                                    messages_log_panel("Done!",W,H,R,W/9,H/16);
                                }
                                else{
                               messages_log_panel("                                                     ",W,H,R,W/9,H/16);
                                messages_log_panel("Colision!",W,H,R,W/9,H/16);
                                }
                            }
                            else if(left_menu_workplace_page(W,H,R,xMouse,yMouse)!=left_menu)
                                left_menu=left_menu_workplace_page(W,H,R,xMouse,yMouse),
                                change_color_icon_left_menu_workplace_page(W,H,R,0),
                                change_color_icon_left_menu_workplace_page(W,H,R,left_menu_workplace_page(W,H,R,xMouse,yMouse));
                            else if(left_menu_workplace_page(W,H,R,xMouse,yMouse)==left_menu)
                                break;
                            else if(top_menu_workplace_page(W,H,R,xMouse,yMouse))
                                break;
                            else if(right_menu_workplace_page(W,H,R,xMouse,yMouse))
                                break;
                            else if(undo_redo_menu_workplace_page(W,H,R,xMouse,yMouse))
                                break;
                        }
                    }
                    while(true);
                }
//Tudor ILADE
                else if(top_menu)
                {
                    messages_log_panel("                                  ",W,H,R,W/9,H/16);
                    switch(top_menu)
                    {
                    case 1:
                        panel=0;

                        delay(50);
                        succes_panel_main_menu(W,H);
                        delay(50);
                        setcurrentwindow(main_window);
                        cleardevice();
                        draw_main_menu(W,H,R,current_directory);
                        break;
                    case 2:
                        project=open_dialog(1,project);
                        if(project.ans==-2||project.ans==-1||project.ans==-3)
                        {
                            if(project.ans!=-3)
                                error_code_main_menu(W,H,project.ans);
                            setcurrentwindow(main_window);
                        }
                        else
                        {
                            succes_panel_main_menu(W,H);
                            setcurrentwindow(main_window);

                            delay(10);
                            draw_working_table(W,H,R,current_directory);


                            delay(10);

                            draw_components_from_file(project,W,H);
                            stackk=emptyStack(stackk);
                        }
                        break;
                    case 3:
                        ans = save_project(project, project.path_file);
                        if(ans==-1)
                        {
                            error_code_main_menu(W,H,ans);
                            setcurrentwindow(main_window);
                        }
                        else
                        {
                            succes_panel_main_menu(W,H);
                            setcurrentwindow(main_window);
                            delay(10);
                        }
                        break;
                    case 4:
                        project=open_dialog(2,project);
                        if(project.ans==-1||project.ans==-3)
                        {
                            if(project.ans!=-3)
                                error_code_main_menu(W,H,project.ans);
                            setcurrentwindow(main_window);
                        }
                        else
                        {
                            succes_panel_main_menu(W,H);
                            setcurrentwindow(main_window);

                            delay(10);
                            draw_working_table(W,H,R,current_directory);


                            delay(10);

                            draw_components_from_file(project,W,H);
                        }
                        break;
                    case 5:
                         openHtml(current_directory);
                        break;
                    case 6:
                        project=stergere_tabla(project);
                        actualizareStiva(stackk,project);

                        cleardevice();
                        draw_working_table(W,H,R,current_directory);


                        break;
                    }
                }
                else if(right_menu)
                {
//Andrei CERBU
                    switch(right_menu)
                    {
                    case 1://check integrity
                        if(checkIntegrity(project)){
                        messages_log_panel("                                  ",W,H,R,W/9,H/16);
                        messages_log_panel("Connected!",W,H,R,W/9,H/16);
                        }
                        else{
                        messages_log_panel("                                  ",W,H,R,W/9,H/16);
                        messages_log_panel("Disconnected!",W,H,R,W/9,H/16);
                        }
                        break;
                    case 2:
                        messages_log_panel("Choose a component!",W,H,R,W/9,H/16);
                        clearmouseclick(WM_LBUTTONDOWN);
                        int last_y;
                        do
                        {
                            if(ismouseclick(WM_LBUTTONDOWN))
                            {
                                getmouseclick(WM_LBUTTONDOWN,x,y);
                                if(isComponentselected(project,x,y,R))
                                {
                                    int ndxCmp=getIndexOfComponent(project, x,y,R);
                                    change_color_icon_zoom_rotate_menu_workplace_page(W,H,R,W/10,H/22,RED);
                                    clearmouseclick(WM_LBUTTONDOWN);
                                    //create_zoom_rotate_panel_workplace(W,H,R,W/10,H/22,BLACK);
                                    //create_zoom_rotate_fader_workplace(W,H,R,W/10,H/22,convert_angle_to_y(project.v[ndxCmp].angle, top_fader),1,WHITE);
                                    //create_zoom_rotate_fader_workplace(W,H,R,W/10,H/22,convert_zoom_to_y(project.v[ndxCmp].zoom, center_fader),2,WHITE);
                                    do
                                    {

                                        if(ismouseclick(WM_LBUTTONDOWN))
                                        {
                                            getmouseclick(WM_LBUTTONDOWN, x, y);
                                            clearmouseclick(WM_LBUTTONDOWN);
                                            slider = determine_angle_fader_position(W,H,R,W/10,H/22,x,y);

                                            if(slider)
                                            {


                                                draw_black_zoom_rotate_panel(W,H,R,W/10,H/22, slider);
                                                draw_components_on_working_table(project.v[ndxCmp].type,W,H,project.v[ndxCmp].x1,project.v[ndxCmp].y1,R,project.v[ndxCmp].angle,project.v[ndxCmp].zoom,BLACK,CMP);
                                                do
                                                {
                                                    yMouse=mousey();
                                                    xMouse=mousex();
                                                    if(betweenBars(W,H, R, W/10, H/22, xMouse, yMouse, slider))
                                                    {
                                                        if(slider==1)
                                                        {
                                                            angle=convert_y_to_angle(yMouse,top_fader);
                                                            draw_components_on_working_table(project.v[ndxCmp].type,W,H,project.v[ndxCmp].x1,project.v[ndxCmp].y1,R,angle,project.v[ndxCmp].zoom,WHITE,CMP);
                                                            generate_rectangle_struct(RECT, CMP, project.v[ndxCmp].type);
                                                            generate_rectangle_full_struct(RECT_FULL,CMP, project.v[ndxCmp].type);
                                                            draw_moving_line(project,ndxCmp,color,W,H,R,RECT);

                                                            create_zoom_rotate_fader_workplace(W,H,R,W/10,H/22,last_y,slider,BLACK);
                                                            create_zoom_rotate_fader_workplace(W,H,R,W/10,H/22,yMouse,slider,WHITE);

                                                            delay(50);

                                                            draw_components_on_working_table(project.v[ndxCmp].type,W,H,project.v[ndxCmp].x1,project.v[ndxCmp].y1,R,angle,project.v[ndxCmp].zoom,BLACK,CMP);
                                                            generate_rectangle_struct(RECT, CMP, project.v[ndxCmp].type);
                                                            generate_rectangle_full_struct(RECT_FULL,CMP,project.v[ndxCmp].type);
                                                            draw_moving_line(project,ndxCmp,BLACK,W,H,R,RECT);
                                                            create_zoom_rotate_fader_workplace(W,H,R,W/10,H/22,yMouse,slider,BLACK);
                                                        }
                                                        else
                                                        {
                                                            zoom=convert_y_to_zoom(yMouse,center_fader);
                                                            draw_components_on_working_table(project.v[ndxCmp].type,W,H,project.v[ndxCmp].x1,project.v[ndxCmp].y1,R,project.v[ndxCmp].angle,zoom,WHITE,CMP);
                                                            generate_rectangle_struct(RECT, CMP, type);
                                                            generate_rectangle_full_struct(RECT_FULL,CMP, type);
                                                            draw_moving_line(project,ndxCmp,color,W,H,R,RECT);

                                                            create_zoom_rotate_fader_workplace(W,H,R,W/10,H/22,last_y,slider,BLACK);
                                                            create_zoom_rotate_fader_workplace(W,H,R,W/10,H/22,yMouse,slider,WHITE);

                                                            delay(50);

                                                            draw_components_on_working_table(project.v[ndxCmp].type,W,H,project.v[ndxCmp].x1,project.v[ndxCmp].y1,R,project.v[ndxCmp].angle,zoom,BLACK,CMP);
                                                            draw_moving_line(project,ndxCmp,BLACK,W,H,R,RECT);
                                                            create_zoom_rotate_fader_workplace(W,H,R,W/10,H/22,yMouse,slider,BLACK);
                                                        }
                                                        last_y = yMouse;
                                                    }
                                                    else
                                                    {
                                                        create_zoom_rotate_fader_workplace(W,H,R,W/10,H/22,last_y,slider,WHITE);
                                                        if(slider==1)
                                                        {
                                                            draw_components_on_working_table(project.v[ndxCmp].type,W,H,project.v[ndxCmp].x1,project.v[ndxCmp].y1,R,angle,project.v[ndxCmp].zoom,WHITE,CMP);
                                                            generate_rectangle_struct(RECT, CMP, project.v[ndxCmp].type);
                                                            generate_rectangle_full_struct(RECT_FULL,CMP, project.v[ndxCmp].type);
                                                            draw_moving_line(project,ndxCmp,color,W,H,R,RECT);

                                                            create_zoom_rotate_fader_workplace(W,H,R,W/10,H/22,last_y,slider,BLACK);
                                                            create_zoom_rotate_fader_workplace(W,H,R,W/10,H/22,last_y,slider,WHITE);

                                                            delay(50);

                                                            draw_components_on_working_table(project.v[ndxCmp].type,W,H,project.v[ndxCmp].x1,project.v[ndxCmp].y1,R,angle,project.v[ndxCmp].zoom,BLACK,CMP);
                                                            generate_rectangle_struct(RECT, CMP, project.v[ndxCmp].type);
                                                            generate_rectangle_full_struct(RECT_FULL,CMP,project.v[ndxCmp].type);
                                                            draw_moving_line(project,ndxCmp,BLACK,W,H,R,RECT);
                                                        }
                                                        else
                                                        {
                                                            draw_components_on_working_table(project.v[ndxCmp].type,W,H,project.v[ndxCmp].x1,project.v[ndxCmp].y1,R,project.v[ndxCmp].angle,zoom,WHITE,CMP);
                                                            generate_rectangle_struct(RECT, CMP, type);
                                                            generate_rectangle_full_struct(RECT_FULL,CMP, type);
                                                            draw_moving_line(project,ndxCmp,color,W,H,R,RECT);

                                                            create_zoom_rotate_fader_workplace(W,H,R,W/10,H/22,last_y,slider,BLACK);
                                                            create_zoom_rotate_fader_workplace(W,H,R,W/10,H/22,last_y,slider,WHITE);

                                                            delay(50);

                                                            draw_components_on_working_table(project.v[ndxCmp].type,W,H,project.v[ndxCmp].x1,project.v[ndxCmp].y1,R,project.v[ndxCmp].angle,zoom,BLACK,CMP);
                                                            draw_moving_line(project,ndxCmp,BLACK,W,H,R,RECT);
                                                        }
                                                    }

                                                    if(ismouseclick(WM_LBUTTONDOWN))
                                                        break;
                                                }
                                                while(true);
                                                clearmouseclick(WM_LBUTTONDOWN);
                                                create_zoom_rotate_fader_workplace(W,H,R,W/10,H/22,yMouse,slider,WHITE);
                                                if(slider==1)
                                                {
                                                    draw_components_on_working_table(project.v[ndxCmp].type,W,H,project.v[ndxCmp].x1,project.v[ndxCmp].y1,R,angle,project.v[ndxCmp].zoom,WHITE,CMP);
                                                    generate_rectangle_struct(RECT, CMP, type);
                                                    generate_rectangle_full_struct(RECT_FULL,CMP, type);

                                                    draw_moving_line(project,ndxCmp,WHITE,W,H,R,RECT);
                                                    project = actualizareTabla(project, ndxCmp,project.v[ndxCmp].x1,project.v[ndxCmp].y1,W,H,R,angle,project.v[ndxCmp].zoom, RECT, RECT_FULL, project.v[ndxCmp].outsideRect);
                                                    stackk=actualizareStiva(stackk,project);
                                                    drawAllComponents(project, W,H,R,color);

                                                }
                                                else
                                                {
                                                    draw_components_on_working_table(project.v[ndxCmp].type,W,H,project.v[ndxCmp].x1,project.v[ndxCmp].y1,R,project.v[ndxCmp].angle,zoom,BLACK,CMP);
                                                    generate_rectangle_full_struct(RECT_FULL, CMP, type);
                                                    generate_rectangle_struct(RECT, CMP, type);
                                                    MAXIMUM_ROTATION_RECT = generate_maximum_rotation(W/10,H/16,R,project.v[ndxCmp].x1, project.v[ndxCmp].y1,zoom, R);
                                                    draw_moving_line(project,ndxCmp,color,W,H,R,RECT);

                                                    project = actualizareTabla(project, ndxCmp,project.v[ndxCmp].x1,project.v[ndxCmp].y1,W,H,R,project.v[ndxCmp].angle,zoom, RECT, RECT_FULL, MAXIMUM_ROTATION_RECT);
                                                    stackk=actualizareStiva(stackk,project);
                                                    drawAllComponents(project, W,H,R,color);

                                                }
                                            }
                                        }
                                        if(right_menu_workplace_page(W,H,R,x,y)==2)
                                            break;

                                    }
                                    while(true);
                                    create_zoom_rotate_fader_workplace(W,H,R,W/10,H/22,convert_angle_to_y(angle, top_fader),1,BLACK);
                                    create_zoom_rotate_fader_workplace(W,H,R,W/10,H/22,convert_zoom_to_y(zoom, center_fader),2,BLACK);
                                    create_zoom_rotate_panel_workplace(W,H,R,W/10,H/22,WHITE);
                                }
                                if(right_menu_workplace_page(W,H,R,x,y)==2)
                                    break;
                            }
                        }
                        while(true);
                        change_color_icon_zoom_rotate_menu_workplace_page(W,H,R,W/10,H/22,WHITE);

                    messages_log_panel("                                                     ",W,H,R,W/9,H/16);
                       messages_log_panel("Done!",W,H,R,W/9,H/16);

                        break;
                    case 3://delete component
//Tudor ILADE
                       messages_log_panel("Choose a component!",W,H,R,W/9,H/16);
                        do
                        {
                            click_l=ismouseclick(WM_LBUTTONDOWN);
                            getmouseclick(WM_LBUTTONDOWN,xMouse,yMouse);

                            if(click_l)
                            {
                                cmp=getIndexOfComponent(project,xMouse,yMouse,R);
                                if(right_menu_workplace_page(W,H,R,xMouse,yMouse)==3)
                                    break;
                                if(cmp!=-1)
                                {
                                    draw_components_on_working_table(project.v[cmp].type,W,H,project.v[cmp].x1, project.v[cmp].y1,project.v[cmp].R,project.v[cmp].angle,project.v[cmp].zoom,BLACK,CMP);
                                    drawAllLinesBack(project,cmp,W,H,R);
                                    project=deleteComponent(project,cmp);
                                    stackk=actualizareStiva(stackk,project);
                                    drawAllComponents(project,W,H,R,color);
                                }
                            }
                        }
                        while(true);

                       messages_log_panel("                                                     ",W,H,R,W/9,H/16);
                       messages_log_panel("Done!",W,H,R,W/9,H/16);

                        break;
                    case 4://Delete linking
//Tudor Ilade
                       messages_log_panel("Choose a linking!",W,H,R,W/9,H/16);
                        do
                        {
                            if(ismouseclick(WM_LBUTTONDOWN))
                            {
                                getmouseclick(WM_LBUTTONDOWN,xMouse,yMouse);
                                legNdx=isLinkSelected(project,xMouse,yMouse);

                                if(legNdx!=-1)
                                {
                                    project=stergeLegatura(project,legNdx);
                                    stackk=actualizareStiva(stackk,project);

                                    drawAllComponents(project,W,H,R,color);
                                }
                                else if(right_menu_workplace_page(W,H,R,xMouse,yMouse)||!right_menu_workplace_page(W,H,R,xMouse,yMouse))
                                    break;
                            }
                        }
                        while(true);

                        messages_log_panel("                                                     ",W,H,R,W/9,H/16);
                        messages_log_panel("Done!",W,H,R,W/9,H/16);

                        break;
                    case 5:
                       messages_log_panel("Choose a component!",W,H,R,W/9,H/16);
                        do
                        {
                            if(ismouseclick(WM_LBUTTONDOWN))
                            {

                                getmouseclick(WM_LBUTTONDOWN,xMouse,yMouse);
                                if(isComponentselected(project,xMouse,yMouse,R))
                                {
                                    cmp=getIndexOfComponent(project,xMouse,yMouse,R);
                                    indx=project.v[cmp].type;
                                    int value_cmp=edit_value_window(W,H,R,indx, project.v[cmp].value);
                                    project.v[cmp].value=value_cmp;


                                    setcurrentwindow(main_window);
                                    break;
                                }
                                else break;
                            }
                        }
                        while(true);
                        setcurrentwindow(main_window);

                    messages_log_panel("                                                     ",W,H,R,W/9,H/16);
                    messages_log_panel("Done!",W,H,R,W/9,H/16);

                        break;
//Tudor Ilade
                    case 6://Select linking type
                       messages_log_panel("Choose a linking type!",W,H,R,W/9,H/16);

                        delay(40);

                        create_drawing_line_type_menu_workplace(W,H,R,W/10,H/22,WHITE);
                        drawing_line_type(W,H,R,W/10,H/22,WHITE);

                        do
                        {
                            xMouse=mousex();
                            yMouse=mousey();
                            if(type)
                                change_color_icon_drawing_line_type_menu_workplace(W,H,R,type,type);
                            change_color_icon_drawing_line_type_menu_workplace(W,H,R,line_type_menu_workplace(W,H,R,xMouse,yMouse),type);


                            if(ismouseclick(WM_LBUTTONDOWN))
                            {
                                getmouseclick(WM_LBUTTONDOWN,xMouse,yMouse);
                                if(line_type_menu_workplace(W,H,R,xMouse,yMouse)==0)
                                    break;
                                else if(type==0||line_type_menu_workplace(W,H,R,xMouse,yMouse)&&line_type_menu_workplace(W,H,R,xMouse,yMouse)!=type)
                                    type=line_type_menu_workplace(W,H,R,xMouse,yMouse);
                                else if(line_type_menu_workplace(W,H,R,xMouse,yMouse)==type)
                                    type=0;
                            }
                        }
                        while(true);

                        delay(50);

                        create_drawing_line_type_menu_workplace(W,H,R,W/10,H/22,BLACK);
                        drawing_line_type(W,H,R,W/10,H/22,BLACK);

                        messages_log_panel("                                                     ",W,H,R,W/9,H/16);
                        messages_log_panel("Done!",W,H,R,W/9,H/16);

                        break;
                    }
                }
//Tudor Ilade
                else if(undoRedo)
                {
                    messages_log_panel("                                  ",W,H,R,W/9,H/16);
                    switch(undoRedo)
                    {
                    case 1://Undo
                        do
                        {
                            getmouseclick(WM_LBUTTONDBLCLK,xMouse,yMouse);
                            drawAllComponents(project,W,H,R,BLACK);
                            project=URfnc(stackk,undoRedo,project);
                            drawAllComponents(project,W,H,R,color);
                        }
                        while(undo_redo_menu_workplace_page(W,H,R,xMouse,yMouse)==1);
                        break;
                    case 2://Redo
                        do
                        {
                            getmouseclick(WM_LBUTTONDBLCLK,xMouse,yMouse);
                            drawAllComponents(project,W,H,R,BLACK);
                            project=URfnc(stackk,undoRedo,project);
                            drawAllComponents(project,W,H,R,color);
                        }
                        while(undo_redo_menu_workplace_page(W,H,R,xMouse,yMouse)==2);
                        break;
                    }
                }
//Tudor Ilade
                else if(component_selected && !linking)
                {
                    messages_log_panel("                                  ",W,H,R,W/9,H/16);
                    ndxCmp=getIndexOfComponent(project,x,y,R);
                    getmouseclick(WM_LBUTTONDBLCLK,xMouse,yMouse);
                    clearmouseclick(WM_LBUTTONDBLCLK);

                    draw_components_on_working_table(project.v[ndxCmp].type,W,H,project.v[ndxCmp].x1,project.v[ndxCmp].y1,project.v[ndxCmp].R,project.v[ndxCmp].angle,project.v[ndxCmp].zoom,BLACK,CMP);
                    generate_rectangle_struct(RECT, CMP, project.v[ndxCmp].type);
                    generate_rectangle_full_struct(RECT_FULL,CMP, project.v[ndxCmp].type);
                    draw_moving_line(project, ndxCmp, BLACK, W,H,R,RECT);
                    do
                    {
                        click_l=ismouseclick(WM_LBUTTONDOWN);
                        x=mousex();
                        y=mousey();
                        MAXIMUM_ROTATION_RECT = generate_maximum_rotation(W/10,H/16,R,x,y,project.v[ndxCmp].zoom, project.v[ndxCmp].type);
                        if(click_l)
                        {
                            getmouseclick(WM_LBUTTONDOWN,x,y);
                            break;
                        }
                        if(outSideTable(x,y,H,W,R,MAXIMUM_ROTATION_RECT, project.v[ndxCmp].type))
                        {

                            messages_log_panel("A depasit limitele tablei!",W,H,R,W/9,H/16);
                            delay(50);
                            break;
                        }
                        if(xMouse!=x||yMouse!=y)
                        {
                            draw_components_on_working_table(project.v[ndxCmp].type,W,H,x,y,R,project.v[ndxCmp].angle,project.v[ndxCmp].zoom,WHITE,CMP);
                            generate_rectangle_struct(RECT, CMP, project.v[ndxCmp].type);
                            generate_rectangle_full_struct(RECT_FULL,CMP, project.v[ndxCmp].type);
                            draw_moving_line(project, ndxCmp,color,W,H,R, RECT);

                            delay(40);

                            draw_components_on_working_table(project.v[ndxCmp].type,W,H,x,y,R,project.v[ndxCmp].angle,project.v[ndxCmp].zoom,BLACK,CMP);
                            generate_rectangle_struct(RECT, CMP, project.v[ndxCmp].type);
                            generate_rectangle_full_struct(RECT_FULL,CMP, project.v[ndxCmp].type);
                            draw_moving_line(project,ndxCmp,BLACK,W,H,R, RECT);
                            drawComponentsXSelected(project, ndxCmp, W, H, R, color);
                        }
                    }
                    while(true);
                    MAXIMUM_ROTATION_RECT = generate_maximum_rotation(W/10,H/16,R,x,y,1.0, project.v[ndxCmp].type);
                    if(!isColision(MAXIMUM_ROTATION_RECT,H,W,project,R,project.v[ndxCmp].type,ndxCmp))
                    {
                        drawAllLinesBack(project,ndxCmp,W,H,R);
                        draw_components_on_working_table(project.v[ndxCmp].type,W,H,x,y,R,project.v[ndxCmp].angle,project.v[ndxCmp].zoom,BLACK,CMP);
                        generate_rectangle_struct(RECT, CMP,project.v[ndxCmp].type);
                        generate_rectangle_full_struct(RECT_FULL, CMP, project.v[ndxCmp].type);
                        project=actualizareTabla(project,ndxCmp,x,y,W,H,project.v[ndxCmp].R,project.v[ndxCmp].angle,project.v[ndxCmp].zoom, RECT, RECT_FULL, MAXIMUM_ROTATION_RECT);
                        stackk=actualizareStiva(stackk, project);
                        drawAllComponents(project,W, H, R, color);
                       messages_log_panel("                                  ",W,H,R,W/9,H/16);
                       messages_log_panel("Done!",W,H,R,W/9,H/16);
                    }
                    else
                    {
                        messages_log_panel("                                  ",W,H,R,W/9,H/16);
                        messages_log_panel("Coliziune",W,H,R,W/9,H/16);
                        drawAllComponents(project, W, H, R, color);
                    }

                }
//Tudor Ilade
                else if(linking)
                {
                    messages_log_panel("                                  ",W,H,R,W/9,H/16);
                    punctLegatura leg1, leg2;
                    int ndx = getIndexOfComponent(project,x,y,R);
                    COMPONENTE cmp = project.v[ndx];
                    leg1.x = x;
                    leg1.y = y;
                    leg1.sd = linking;
                    leg1.type = type;
                    xMouse = mousex();
                    yMouse = mousey();
                    click_l=0;
                    do
                    {
                        drawLine(leg1.x,leg1.y, xMouse,yMouse, WHITE,leg1.type);
                        delay(50);
                        drawLine(leg1.x,leg1.y, xMouse,yMouse, BLACK,leg1.type);
                        drawAllComponents(project, W,H,R, WHITE);

                        xMouse=mousex();
                        yMouse=mousey();
                        if(outSideTable(xMouse,yMouse,H,W,R,MAXIMUM_ROTATION_RECT))
                        {
                            delay(50);
                            break;
                        }
                        click_l = ismouseclick(WM_LBUTTONDOWN);
                        if(click_l)
                            break;


                    }
                    while(true);
                    click_l=0;
                    clearmouseclick(WM_LBUTTONDOWN);
                    clearmouseclick(click_l);
                    xMouse = mousex();
                    yMouse = mousey();
                    int leg = isLinking(project,W,H,xMouse,yMouse,R,CMP,ndx);
                    if(leg)
                    {
                        int ndx2 = getIndexOfComponent(project,xMouse,yMouse,R);
                        drawLine(leg1.x,leg1.y, xMouse,yMouse, WHITE,leg1.type);
                        leg1.xConnection = xMouse;
                        leg1.yConnection = yMouse;
                        leg1.ndxParent = ndx;
                        leg2.sd = leg;
                        leg2.x = xMouse;
                        leg2.y = yMouse;
                        leg2.ndxParent = ndx2;
                        leg2.xConnection = leg1.x;
                        leg2.yConnection = leg1.y;
                        leg2.type = leg1.type;
                        pair<punctLegatura, punctLegatura>PAIR;
                        PAIR.first = leg1;
                        PAIR.second = leg2;
                        project.p.push_back(PAIR);
                        project.v[ndx].legatura.push_back(PAIR);
                        project.v[ndx2].legatura.push_back(PAIR);
                        drawAllComponents(project, W,H,R, color);
                        stackk = actualizareStiva(stackk, project);
                    }
                    else
                    {
                        drawLine(leg1.x,leg1.y, xMouse,yMouse, BLACK,leg1.type);
                        drawAllComponents(project, W,H,R, color);
                    }
                    messages_log_panel("Done!",W,H,R,W/9,H/16);
                }
//Tudor Ilade
                else if(switcher.inOut)
                {
                    messages_log_panel("                                  ",W,H,R,W/9,H/16);
                    if(switcher.bulb==1)//aprinde becu
                    {
                        if(turnOn)
                        {
                            readimagefile(path_for_images("bec_aprins.jpg",current_directory),W-W/9+W/34,0.2*H/16,W-W/6.5+W/34,1.6*H/16);
                            color=YELLOW;
                            aprinde=true;
                            messages_log_panel("Happy Circuit!",W,H,R,W/9,H/16);
                            drawAllComponents(project, W,H,R,color);
                            delay(100);
                        }
                        else
                        {
                            color=WHITE;
                            messages_log_panel("Not working!",W,H,R,W/9,H/16);

                        }
                    }
                    else if(switcher.bulb==2)//stinge becu
                    {
                        if(turnOn)
                        {
                            readimagefile(path_for_images("becstins.jpg",current_directory),W-W/9+W/34,0.2*H/16,W-W/6.5+W/34,1.6*H/16);
                            aprinde=false;
                            color=WHITE;
                            drawAllComponents(project,W,H,R,color);
                            delay(100);

                            messages_log_panel("Light off!",W,H,R,W/9,H/16);
                        }
                        else
                        {
                            color=WHITE;
                            messages_log_panel("Not working!",W,H,R,W/9,H/16);

                        }
                    }
                }
            }
        }
    }
}


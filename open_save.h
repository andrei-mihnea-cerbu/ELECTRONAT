#ifndef OPEN_SAVE_H_INCLUDED
#define OPEN_SAVE_H_INCLUDED
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
#include "drawing_components.h"
#include "stare_table.h"



//Tudor ILADE toate functiile


///Functie responsabila de crearea fisierului de proiect in directorul Projects
char* path_for_projects_directory(int type=0)
{
    //se creaza path-ul catre directorul unde vor fi salvate proiectele
    char cwd[256];
    getcwd(cwd, 256);
    char* dir = new char[40];
    char* path = new char[strlen(cwd)+12+strlen(dir)];
    *path = '\0';
    *dir = '\0';
    strcat(dir, "Projects");
    strcat(path, cwd);
    if(type==1)
        return path;
    strcat(path,"\\");
    strcat(path,dir);

    //Se verifica existenta directorului pentru proiecte
    bool isDir = false;
    struct stat info;
    if(stat(path,&info)!=0)
        isDir = false;
    else if(info.st_mode & S_IFDIR)
        isDir = true;
    if(isDir==0)
    {
        //Directorul nu exista, deci
        int check = mkdir(path);
        if(!check)
        {
            return path;
        }
    }
    else
    {
        //Directorul exista, deci returnam path-ul
        return path;
    }
}


///Functie responsabila de crearea unui proiect care returneaza path-ul catre fisier ul unde se va salva proiectul
SITUATIA_TABLEI create_project(SITUATIA_TABLEI tabla,char* file_name)
{
    char* path_to_file = new char[strlen(path_for_projects_directory())+strlen(file_name)+5];
    path_to_file = path_for_projects_directory();
    strcpy(tabla.path_to_dir,path_to_file);
    strcat(path_to_file, "\\");
    strcat(path_to_file, file_name);
    strcat(path_to_file, "\.AT");
    strcpy(tabla.path_file,path_to_file);
    FILE* project;
    project = fopen(path_to_file, "wb+");
    if(project==NULL)
    {
        exit(1);
        tabla.ans=-1;
        return tabla;
    }
    char header[2] = {'A', 'T'};
    fwrite(&header, sizeof(header),1,project);
    fclose(project);
    return tabla;
}


///Functie responsabila de salvarea tablei actuale in proiectul deschis. (se va folosi si pentru save as)
int save_project(SITUATIA_TABLEI &table, char* path)
{
    FILE* project;
    project = fopen(path, "wb+");
    if(project == NULL)
    {
        return -1;
    }
    char header[2] = {'A', 'T'};
    fwrite(&header, sizeof(header),1,project);

    if(table.v.size()!=0)
    {
        for(int i=0; i<table.v.size(); i++)
        {
            BinaryCMP bnr;
            bnr.type = table.v[i].type;
            bnr.x = table.v[i].x1;
            bnr.y = table.v[i].y1;
            bnr.conectat = table.v[i].connectat;
            bnr.rect = table.v[i].rect;
            bnr.R = table.v[i].R;
            bnr.angle = table.v[i].angle;
            bnr.zoom = table.v[i].zoom;
            bnr.value = table.v[i].value;
            bnr.outsideRect = table.v[i].outsideRect;
            bnr.coordinates[0] = table.v[i].coordinates[0];
            bnr.coordinates[1] = table.v[i].coordinates[1];
            bnr.coordinates[2] = table.v[i].coordinates[2];
            bnr.coordinates[3] = table.v[i].coordinates[3];
            bnr.nodes[0] = table.v[i].nodes[0];
            bnr.nodes[1] = table.v[i].nodes[1];
            bnr.nodes[2] = table.v[i].nodes[2];
            bnr.nodes[3] = table.v[i].nodes[3];
            strcpy(bnr.name,table.v[i].name);
            if(!table.v[i].legatura.empty())
            {
                for(int j = 0; j<table.v[i].legatura.size(); j++)
                {
                    bnr.legatura[2*j] = table.v[i].legatura[j].first;
                    bnr.legatura[2*j+1] = table.v[i].legatura[j].second;
                }
            }
            bnr.size_of_linkings = table.v[i].legatura.size();
            fwrite(&bnr, sizeof(bnr), 1, project);
        }
    }
    fclose(project);
    return 1;
}

///Functie responsabila pentru deschiderea unui proiect.
SITUATIA_TABLEI open_project(char* path)
{
    FILE* project_file;
    SITUATIA_TABLEI tabla;
    BinaryCMP cmp;
    project_file = fopen(path, "rb");
    if(project_file == NULL)
    {
        tabla.ans = -1;
        return tabla;
    }
    char c1[1] = {fgetc(project_file)};
    char c2[1] = {fgetc(project_file)};
    if(c1[0]!='A'&&c2[0]!='T')
    {
        tabla.ans = -2;
        return tabla;
    }
    while(fread(&cmp,sizeof(cmp),1,project_file)!=0)
    {
        COMPONENTE cmp_table;
        cmp_table.type = cmp.type;
        cmp_table.angle = cmp.angle;
        cmp_table.zoom = cmp.zoom;
        cmp_table.x1 = cmp.x;
        cmp_table.y1 = cmp.y;
        cmp_table.connectat = cmp.conectat;
        strcpy(cmp_table.name, cmp.name);
        cmp_table.rect = cmp.rect;
        cmp_table.R = cmp.R;
        cmp_table.value = cmp.value;
        cmp_table.outsideRect = cmp.outsideRect;
        cmp_table.coordinates[0] = cmp.coordinates[0];
        cmp_table.coordinates[1] = cmp.coordinates[1];
        cmp_table.coordinates[2] = cmp.coordinates[2];
        cmp_table.coordinates[3] = cmp.coordinates[3];

        cmp_table.nodes[0] = cmp.nodes[0];
        cmp_table.nodes[1] = cmp.nodes[1];
        cmp_table.nodes[2] = cmp.nodes[2];
        cmp_table.nodes[3] = cmp.nodes[3];
        int sz = cmp.size_of_linkings;
        for(int i = 0; i<sz; i++)
        {
            pair<punctLegatura, punctLegatura>PAIR;
            PAIR.first = cmp.legatura[2*i];
            PAIR.second = cmp.legatura[2*i+1];
            cmp_table.legatura.push_back(PAIR);
        }
        tabla.v.push_back(cmp_table);

    }
    for(int i =0; i<tabla.v.size(); i++)
    {
        for(int j = 0; j<tabla.v[i].legatura.size(); j++)
        {
            tabla.p.push_back(tabla.v[i].legatura[j]);
        }
    }

    for(int i = 0; i<tabla.p.size(); i++)
    {
        for(int k = i+1; k<tabla.p.size(); k++)
        {
            if(tabla.p[i].first.ndxParent == tabla.p[k].first.ndxParent && tabla.p[i].second.ndxParent == tabla.p[k].second.ndxParent)
            {
                tabla.p.erase(tabla.p.begin()+k);
            }
        }
    }
    tabla.ans = 1;
    strcpy(tabla.path_file,path);
    strcpy(tabla.path_to_dir,path_for_projects_directory(1));
    fclose(project_file);
    return tabla;
}


///Functie responsabila de deschiderea unei casute de dialog unde user-ul poate salva/crea etc, proiectul

//Internet && Tudor Ilade
SITUATIA_TABLEI open_dialog(int type,SITUATIA_TABLEI tabla)
{
    OPENFILENAME ofn;
    char szFileName[MAX_PATH] = "";
    char szPathDir[MAX_PATH] = "";
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFilter = "AT Files (*.AT)\0*.AT\0All Files (*.*)\0*.*\0";
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "bin";
    if(type==1)
    {
        ofn.lpstrFile = szFileName;
        if(GetOpenFileName(&ofn))
        {
            SITUATIA_TABLEI tabla;
            tabla = open_project(szFileName);
            return tabla;
        }
        else
        {
            tabla.ans = -3;
            return tabla;
        }
    }
    else
    {
        ofn.lpstrInitialDir = tabla.path_to_dir;
        ofn.lpstrFile = tabla.path_file;
        if(GetSaveFileName(&ofn))
        {
            int ans = save_project(tabla,ofn.lpstrFile);
            tabla.ans = ans;
            return tabla;
        }
        else
        {
            tabla.ans = -3;
            return tabla;
        }
    }
}


#endif // OPEN_SAVE_H_INCLUDED

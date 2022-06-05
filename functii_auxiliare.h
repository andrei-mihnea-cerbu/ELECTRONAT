#ifndef FUNCTII_AUXILIARE_H_INCLUDED
#define FUNCTII_AUXILIARE_H_INCLUDED

//Tudor Ilade
///Functie responsabila pentru a gasi calea absoluta a imaginilor folosite in proiect, indiferent de locatia proiectului pe dispozitiv
char* path_for_images(char* filename, char *path)
{
    char *path_for_file=new char[strlen(path)+strlen(filename)+4];
    *path_for_file='\0';
    strcat(path_for_file,path);
    strcat(path_for_file,"\\");
    strcat(path_for_file,filename);

    return path_for_file;
}

char* create_fixed_path(){
    char cwd[256];
    getcwd(cwd,256);
    char* path = new char[strlen(cwd)+4];
    *path = '\0';
    strcat(path,cwd);
    return path;
}

#endif // FUNCTII_AUXILIARE_H_INCLUDED

#include<iostream>
#include<fstream>
#include<unistd.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>
using namespace std;
int main()
{
    char path[100],subdirpath[100],img[100];
    struct dirent *entry;
    struct stat statbuf;
    DIR *dir=opendir(path);
    for(;(entry=readdir(dir))!=nullptr;)
    {
        stat(entry->d_name,&statbuf);
        if(strcmp(".",entry->d_name)==0||strcmp("..",entry->d_name)==0)
            continue;
        strcpy(subdirpath,path);
        strcat(subdirpath,"/");
        strcat(subdirpath,entry->d_name);
        float i=0,size=0;
        DIR *subdir=opendir(subdirpath);
        for(;(entry=readdir(subdir))!=nullptr;)
        {
            stat(entry->d_name,&statbuf);
            if(strcmp(".",entry->d_name)==0||strcmp("..",entry->d_name)==0)
                continue;
            strcpy(img,subdirpath);
            strcat(img,"/");
            strcat(img,entry->d_name);
            stat(img,&statbuf);
            size+=statbuf.st_size;
            i++;
        }
        cout<<subdirpath<<"average:"<<size/i<<"kB"<<endl;
    }
    return 0;
}

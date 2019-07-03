//输入同目录下的另一个文件夹名，计算其下子文件夹内文件的平均文件大小。
#define PATHBUF 100
#include<iostream>
#include<fstream>
#include<unistd.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>
#include<vector>
#include<algorithm>
using namespace std;
struct info
{
    info(int diravs,char dirname[])
    {
        avs=diravs;
        strcpy(dir,dirname);
    }
    int avs;
    char dir[PATHBUF];
};
bool sortfun(const info a,const info b)
{
    return a.avs>b.avs;
}
int main()
{
    char *path=getcwd(NULL,PATHBUF),dname[PATHBUF];
    cin>>dname;
    strcat(path,"/");
    strcat(path,dname);
    cout<<path<<endl;
    vector<info>dirinfo;
    struct dirent *entry;
    struct stat statbuf;
    DIR *dir=opendir(path);
    for(;(entry=readdir(dir))!=NULL;)
    {
        stat(entry->d_name,&statbuf);
        if(strcmp(".",entry->d_name)==0||strcmp("..",entry->d_name)==0)
            continue;
        char subdirpath[PATHBUF],subdirname[PATHBUF];
        strcpy(subdirpath,path);
        strcat(subdirpath,"/");
        strcat(subdirpath,entry->d_name);
        strcpy(subdirname,entry->d_name);
        int i=0;
        float size=0;
        DIR *subdir=opendir(subdirpath);
        for(;(entry=readdir(subdir))!=NULL;)
        {
            stat(entry->d_name,&statbuf);
            if(strcmp(".",entry->d_name)==0||strcmp("..",entry->d_name)==0)
                continue;
            char img[PATHBUF];
            strcpy(img,subdirpath);
            strcat(img,"/");
            strcat(img,entry->d_name);
            stat(img,&statbuf);
            size+=statbuf.st_size;
            i++;
        }
        int avs=size/i/1000;
        if(avs>150)
        {
            info *targetdir=new info(avs,subdirname);
            dirinfo.push_back(*targetdir);
            delete targetdir;
        }
    }
    sort(dirinfo.begin(),dirinfo.end(),sortfun);
    ofstream n;
    n.open("info.txt",ios::trunc);
    for(vector<info>::iterator t=dirinfo.begin();t!=dirinfo.end();n<<t->dir<<' '<<t++->avs<<'\n');
    return 0;
}

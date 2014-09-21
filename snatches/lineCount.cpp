#include "../IO/Computer/FileSystem.h"

int totalLines;
void printFiles(string directory, string name, void* cl){
    FileSystem* f=(FileSystem*)cl;
    char c=name[name.length()-1];
    if(c=='p'||c=='h'){
        cout << name << endl;
        int lines=f->getLineCount(directory+name);
        if(lines!=-1)
            totalLines+=lines;
    }
}
int main(int argc, char* argv[]){
    totalLines=0;
    FileSystem f;
    if(argc==1){
        f.recursiveMapFiles("~/Documents/Developement/c++/jade/",printFiles, &f);
    }else{
        f.recursiveMapFiles(string(argv[1]),printFiles, &f);
    }
    cout << totalLines << endl;
    return 0;
}
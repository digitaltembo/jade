#include "FileSystem.h"

using namespace std;

FileSystem::FileSystem(){
    root=new struct File;
    root->name="";
    root->parent=NULL;
    root->childCount=0;
    root->flags=0;
    currentLocation=root;
    char pathname[256];
    try{
        getcwd(pathname, 256);
    }catch(int e){
    }
    currentPath=string(pathname);
    unsigned pos=1,ppos=0;
    while((pos=currentPath.find('/',pos+1))!=string::npos){
        currentLocation=addAndReturnChild(currentLocation, currentPath.substr(ppos+1,pos-ppos-1));
        ppos=pos;
    }
    currentLocation=addAndReturnChild(currentLocation, currentPath.substr(ppos+1));
    currentPath+='/';
}

int FileSystem::mkdir(string dirname){
    if(dirname[0]!='/'){
        if(dirname[0]!='.')
            currentLocation->flags&=~FILE_SCANNED;
        makeFullPath(dirname);
    }
    int err=::mkdir(dirname.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if(err==-1){
        return errno;
    }
    return 0;
}

int FileSystem::rmdir(string dirname){
    makeFullPath(dirname);
    int err=::rmdir(dirname.c_str());
    if(err==-1){
        perror("Could not delete directory: ");
        return errno;
    }
    return 0;
}
int FileSystem::rmfile(string filename){
    makeFullPath(filename);
    int err=::remove(filename.c_str());
    if(err!=0){
        perror("Could not delete file: ");
    }
    return err;
}

int FileSystem::cd(string dirname){
    if(dirname[0]=='/'){
        if(!isFolder(dirname))
            return -1;
        currentLocation=root;
        struct File* tmp;
        string folderName;
        unsigned pos=0,ppos=0;
        while((pos=dirname.find('/',pos+1))!=string::npos){
            folderName=dirname.substr(ppos+1,pos-ppos-1);
            if((tmp=getChild(currentLocation,folderName))==NULL){
                currentLocation=addAndReturnChild(currentLocation,folderName);
            }else{
                currentLocation=tmp;
            }
            ppos=pos;
        }
        folderName=dirname.substr(ppos+1);
        if((tmp=getChild(currentLocation,folderName))==NULL){
            currentLocation=addAndReturnChild(currentLocation,folderName);
        }else{
            currentLocation=tmp;
        }
        currentPath=dirname;
    }else{
        if(dirname[0]=='.'){
            if(dirname[1]=='.'){
                return cd(makeFullPath(dirname));
            }
            
            return 0;
        }
        if(!isFolder(dirname))
            return 1;
        struct File* tmp;
        string folderName;
        unsigned pos=0;
        int ppos=-1;
        while((pos=dirname.find('/',pos+1))!=string::npos){
            folderName=dirname.substr(ppos+1,pos-ppos-1);
            if((tmp=getChild(currentLocation,folderName))==NULL){
                currentLocation=addAndReturnChild(currentLocation,folderName);
            }else{
                currentLocation=tmp;
            }
            ppos=pos;
        }
        folderName=dirname.substr(ppos+1);
        if((tmp=getChild(currentLocation,folderName))==NULL){
            currentLocation=addAndReturnChild(currentLocation,folderName);
        }else{
            currentLocation=tmp;
        }
        currentPath+=dirname;
    }
    
    if(currentPath[currentPath.length()-1]!='/')
        currentPath+='/';
    return 0;
}
vector<string> FileSystem::ls(){
    vector<string> s;
    dirp=opendir(currentPath.c_str());
    if(dirp==NULL){
        return s;
    }
    struct dirent* d;
    string fname;
    while((d=readdir(dirp))!=NULL){
        if(d->d_name[0]=='.'&&((d->d_name[1]=='.'&&d->d_name[2]=='\0') || d->d_name[1]=='\0'))
            continue;
        fname=string(d->d_name);
        s.push_back(fname);
        addChild(currentLocation, fname);
    }
    currentLocation->flags |= FILE_SCANNED;
    closedir(dirp);
    return s;
}

vector<string> FileSystem::ls(string filepath){
    makeFullPath(filepath);
    vector<string> s;
    dirp=opendir(filepath.c_str());
    if(dirp==NULL){
        return s;
    }
    struct dirent* d;
    string fname;
    while((d=readdir(dirp))!=NULL){
        if(d->d_name[0]=='.'&&((d->d_name[1]=='.'&&d->d_name[2]=='\0') || d->d_name[1]=='\0'))
            continue;
        s.push_back(string(d->d_name));
    }
    closedir(dirp);
    return s;
}

int FileSystem::cp(string filepath, string newLocation){
   makeFullPath(filepath);
   makeFullPath(newLocation);
   
   if(!fileExists(filepath)){
       cerr << "File " << filepath << " doesn't exist\n";
       return 1;
   }
   if(fileExists(newLocation)){
       cerr << "File " << filepath << " already exists\n";
       return 2;
   }
   ifstream toCopy(filepath.c_str());
   ofstream newFile(newLocation.c_str());
   newFile << toCopy.rdbuf();
   newFile.close();
   toCopy.close();
   return 0;
}

int FileSystem::mv(string filepath, string newLocation){
    int err=cp(filepath, newLocation);
    if(err==0){
        return rmfile(filepath);
    }
    return err;
}

int FileSystem::rename(string filepath, string name){
    makeFullPath(filepath);
    makeFullPath(name);
    if(::rename(filepath.c_str(), name.c_str())!=0){
        int e=errno;
        perror("Failed to copy file");
        return e;
    }
    return 0;
}

int FileSystem::mapFiles(FileMapFunction f, void* cl){
    dirp=opendir(currentPath.c_str());
    if(dirp==NULL){
        cerr << "Could not open director " << currentPath << endl;
        return 1;
    }
    struct dirent* d;
    string fname;
    while((d=readdir(dirp))!=NULL){
        if(d->d_name[0]=='.'&&((d->d_name[1]=='.'&&d->d_name[2]=='\0') || d->d_name[1]=='\0'))
            continue;
        fname=string(d->d_name);
        if(isFile(currentPath+fname))
            (*f)(currentPath, fname, cl);
    }
    closedir(dirp);
    return 0;
}

int FileSystem::mapFolders(FileMapFunction f, void* cl){
    dirp=opendir(currentPath.c_str());
    if(dirp==NULL){
        cerr << "Could not open directory " << currentPath << endl;
        return 1;
    }
    struct dirent* d;
    string fname;
    vector<string> folders;
    while((d=readdir(dirp))!=NULL){
        if(d->d_name[0]=='.'&&((d->d_name[1]=='.'&&d->d_name[2]=='\0') || d->d_name[1]=='\0'))
            continue;
        fname=string(d->d_name);
        folders.push_back(fname);
    }
    closedir(dirp);
    for(int i=0,j=folders.size();i<j;i++)
       if(isFolder(currentPath+folders[i]))
            (*f)(currentPath, folders[i], cl);
    return 0;
}

int FileSystem::mapFilesAndFolders(FileAndFolderMapFunction f, void* cl){
    dirp=opendir(currentPath.c_str());
    if(dirp==NULL){
        cerr << "Could not open directory " << currentPath << endl;
        return 1;
    }
    struct dirent* d;
    string fname;
    while((d=readdir(dirp))!=NULL){
        if(d->d_name[0]=='.'&&((d->d_name[1]=='.'&&d->d_name[2]=='\0') || d->d_name[1]=='\0'))
            continue;
        fname=string(d->d_name);
        (*f)(currentPath, fname,isFile(currentPath+fname), cl);
    }
    closedir(dirp);
    return 0;
}


int FileSystem::mapFiles(string path, FileMapFunction f, void* cl){
    dirp=opendir(makeFullDirPath(path).c_str());
    if(dirp==NULL){
        cerr << "Could not open directory " << currentPath << endl;
        return 1;
    }
    struct dirent* d;
    string fname;
    while((d=readdir(dirp))!=NULL){
        if(d->d_name[0]=='.'&&((d->d_name[1]=='.'&&d->d_name[2]=='\0') || d->d_name[1]=='\0'))
            continue;
        fname=string(d->d_name);
        if(isFile(path+fname))
            (*f)(path, fname, cl);
    }
    closedir(dirp);
    return 0;
}

int FileSystem::mapFolders(string path, FileMapFunction f, void* cl){
    dirp=opendir(makeFullDirPath(path).c_str());
    if(dirp==NULL){
        cerr << "Could not open directory " << currentPath << endl;
        return 1;
    }
    struct dirent* d;
    string fname;
    vector<string> folders;
    while((d=readdir(dirp))!=NULL){
        if(d->d_name[0]=='.'&&((d->d_name[1]=='.'&&d->d_name[2]=='\0') || d->d_name[1]=='\0'))
            continue;
        fname=string(d->d_name);
        folders.push_back(fname);
    }
    closedir(dirp);
    for(int i=0,j=folders.size();i<j;i++)
       if(isFolder(path+folders[i]))
            (*f)(path, folders[i], cl);
       
    return 0;
}

int FileSystem::mapFilesAndFolders(string path, FileAndFolderMapFunction f, void* cl){
    dirp=opendir(makeFullDirPath(path).c_str());
    if(dirp==NULL){
        cerr << "Could not open directory " << currentPath << endl;
        return 1;
    }
    struct dirent* d;
    string fname;
    while((d=readdir(dirp))!=NULL){
        if(d->d_name[0]=='.'&&((d->d_name[1]=='.'&&d->d_name[2]=='\0') || d->d_name[1]=='\0'))
            continue;
        fname=string(d->d_name);
        (*f)(path, fname, isFile(path+fname), cl);
    }
    closedir(dirp);
    return 0;
}   
int FileSystem::recursiveMapFiles(FileMapFunction f, void* cl){
    return recursiveMapFiles(currentPath, f, cl);
}
int FileSystem::recursiveMapFiles(string path, FileMapFunction f, void* cl){
    makeFullDirPath(path);
    stack<string, deque<string> > folders;
    folders.push(path);
    struct dirent* d;
    string fname, fpath;
    
    while(!folders.empty()){
        path=folders.top();
        folders.pop();
        dirp=opendir(path.c_str());
        if(dirp==NULL){
            cerr << "Could not open directory " << path << endl;
            continue;
        }
        while((d=readdir(dirp))!=NULL){
            if(d->d_name[0]=='.'&&((d->d_name[1]=='.'&&d->d_name[2]=='\0') || d->d_name[1]=='\0'))
                continue;
            fname=string(d->d_name);
            fpath=path+fname;
            if(stat(fpath.c_str(),&info)==-1)
                 continue;
            if(S_ISREG(info.st_mode))
                (*f)(path, fname, cl);
            else if(S_ISDIR(info.st_mode))
                folders.push(fpath+'/');
        }
        closedir(dirp);
    }
    return 0;
}

bool FileSystem::fileExists(string path){
    makeFullPath(path);
    return stat(path.c_str(),&info)==0;
}

bool FileSystem::isFolder(string path){
    makeFullPath(path);
    if(stat(path.c_str(),&info)==-1)
        return false;
    return S_ISDIR(info.st_mode);
}
bool FileSystem::isFile(string path){
    makeFullPath(path);
    if(stat(path.c_str(),&info)==-1)
        return false;
    return S_ISREG(info.st_mode);
}

int FileSystem::getFileSize(string path){
    makeFullPath(path);
    if(stat(path.c_str(),&info)==-1)
        return -1;
    return info.st_size;
}

string FileSystem::getCurrentLocation(){
    return currentPath;
}
string& FileSystem::makeFullDirPath(string& myPath){
    makeFullPath(myPath);
    if(myPath[myPath.length()-1]!='/')
        myPath.push_back('/');
    return myPath;
}
string& FileSystem::makeFullPath(string& myPath){
    if(myPath[0]!='/'){
        if(myPath[0]=='.'){
            bool updating=true;
            int count=1;
            int i=0;
            while(updating){
                switch(i%3){
                    case 2:
                        updating=(myPath[i]=='/');
                        break;
                    case 1:
                        updating=(myPath[i]=='.');
                        if(updating)
                            count++;
                        break;
                    case 0:
                        updating=(myPath[i]=='.');
                        break;
                }
                i++;
            }
            string::size_type pos=string::npos;
            for(int j=0;j<count;j++){
                pos=currentPath.find_last_of('/',pos-1);
                if(pos==string::npos)
                    break;
            }
            if(pos==string::npos){
                myPath=currentPath;
                return myPath;
            }
            myPath=currentPath.substr(0,pos+1)+myPath.substr(i-1);
        }else if(myPath[0]=='~'){
            if(myPath[1]=='/'){
                //UNIQUE TO MEEE!!!!"
                myPath="/home/nolan"+myPath.substr(1);
            }else{
                myPath="/home/"+myPath.substr(1);
            }
        }else{
            myPath=currentPath+'/'+myPath;
        }
    }
    return myPath;
}

int FileSystem::getWordCount(string filename){
    makeFullPath(filename);
    FILE* f=fopen(filename.c_str(), "r");
    if(f==NULL){
        cerr << "Couldn't open file " << filename << endl;
        return -1;
    }
    int c, pc=' ';
    int words=0;
    while((c=fgetc(f))!=EOF){
        if((c==' '||c=='\n'||c=='\t') &&pc!=' '&&pc!='\n'&&pc!='\t')
            words++;
        pc=c;
    }
    return words;
}

int FileSystem::getLineCount(string filename){
    makeFullPath(filename);
    FILE* f=fopen(filename.c_str(), "r");
    if(f==NULL){
        cerr << "Couldn't open file " << filename << endl;
        return -1;
    }
    int c;
    int lines=0;
    while((c=fgetc(f))!=EOF)
        if(c=='\n')
            lines++;
    return lines+1;
}

int FileSystem::getLineCount(string filename, bool countingBlankLines){
    makeFullPath(filename);
    FILE* f=fopen(filename.c_str(), "r");
    if(f==NULL){
        cerr << "Couldn't open file " << filename << endl;
        return -1;
    }
    int c;
    int lines=0;
    if(countingBlankLines){
        while((c=fgetc(f))!=EOF)
            if(c=='\n')
                lines++;
    }else{
        int pc='\n';
        while((c=fgetc(f))!=EOF){
            if(c=='\n'&&pc!='\n')
                lines++;
            if(c!=' '&& c!='\t')
                pc=c;
        }
    }
    return lines+1;
}

string FileSystem::getExtension(string filepath){
    string::size_type pos=filepath.find_last_of('.'), pos2=filepath.find_last_of('/');
    if(pos==string::npos){
        return "";
    }else if(pos2==string::npos){
        return filepath.substr(pos+1);
    }else if(pos2>pos){
        return "";
    }
    return filepath.substr(pos+1);
}
    
    
struct File* FileSystem::addChild(struct File* parent, string child){
    struct File* c=new struct File;
    c->name=child;
    c->parent=parent;
    c->childCount=0;
    c->flags=0;
    parent->children.push_back(c);
    parent->childCount++;
    return parent;
}
struct File* FileSystem::addAndReturnChild(struct File* parent, string child){
    struct File* c=new struct File;
    c->name=child;
    c->parent=parent;
    c->childCount=0;
    c->flags=0;
    parent->children.push_back(c);
    parent->childCount++;
    return c;
}

struct File* FileSystem::getChild(struct File* parent, string child){
    for(int i=0,j=parent->childCount;i<j;i++)
        if(child.compare(parent->children[i]->name)==0)
            return parent->children[i];
    return NULL;
}

File::~File(){
    for(int i=0;i<childCount;i++)
        delete children[i];
}
FileSystem::~FileSystem(){
    delete root;
}

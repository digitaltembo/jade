/****************************************************************************
 *   Last Modified: 7/31                                                    *
 *   Compiler Flags: None                                                   *
 *                                                                          *
 *   Links:                                                                 *
 *   http://pubs.opengroup.org/onlinepubs/7908799/xsh/dirent.h.html         *
 ****************************************************************************/

#ifndef FILESYSTEM
#define FILESYSTEM

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <string>

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stack>
#include <deque>
#include <vector>

using namespace std;

typedef void (*FileMapFunction)(std::string directory, std::string name, void* cl);
typedef void (*FileAndFolderMapFunction)(std::string directory, std::string name, bool isFile, void* cl);

const int IS_FILE=1;
const int FILE_SCANNED=3;

struct File{
    std::string name;
    vector<struct File*> children;
    struct File* parent;
    int childCount;
    unsigned char flags;
    ~File();
};

class FileSystem{
public:
    FileSystem();
   ~FileSystem();
    void readFileSystem();
    int mkdir(std::string dirname);
    int rmdir(std::string dirname);
    int rmfile(std::string filename);
    int cd(std::string dirname);
    
    vector<std::string> ls();
    vector<std::string> ls(std::string filepath);
    
    int mv(std::string filepath, std::string newLocation);
    int cp(std::string filepath, std::string newLocation);
    int rename(std::string filepath, std::string newLocation);
    
    bool fileExists(std::string path);
    bool isFile(std::string path);
    bool isFolder(std::string path);
    
    
    int mapFiles(FileMapFunction f, void* cl);
    int mapFolders(FileMapFunction f, void* cl);
    int mapFilesAndFolders(FileAndFolderMapFunction f, void* cl);
    
    int mapFiles(std::string path, FileMapFunction f, void* cl);
    int mapFolders(std::string path, FileMapFunction f, void* cl);
    int mapFilesAndFolders(std::string path, FileAndFolderMapFunction f, void* cl);

    int recursiveMapFiles(FileMapFunction f, void* cl);
    int recursiveMapFiles(std::string path, FileMapFunction f, void* cl);
    
    std::string getCurrentLocation();
    std::string& makeFullDirPath(std::string& myPath);
    std::string& makeFullPath(std::string& myPath);
    FILE** locateChanges();
    
    void writeFile(std::string filepath, std::string* lines);
    
    int getFileSize(std::string path);

    int getWordCount(std::string filepath);
    int getLineCount(std::string filepath);
    int getLineCount(std::string filepath, bool countingBlankLines);
    
    std::string getExtension(std::string filepath);
    
private:
    struct stat info;
    DIR* dirp;
    std::string currentPath;
    struct File* root;
    struct File* currentLocation;
    
    struct File* addChild(struct File* parent, std::string child);
    struct File* addAndReturnChild(struct File* parent, std::string child);
    struct File* getChild(struct File* parent, std::string child);    
};

#endif
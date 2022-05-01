#include<iostream>
using namespace std;

//#define SWITCH
#define PLAYSTATION4

class FileSystem{
public:
    static FileSystem& instance();

    virtual ~FileSystem(){}
    virtual char* readFile(char* path)=0;
    virtual void writeFile(char* path, char* contents)=0;
    virtual void loadFileSystem()=0;

    friend class PS4FileSystem;
    friend class NSFileSystem;
private:
    FileSystem(){}
};

class PS4FileSystem : public FileSystem{
public:
    virtual char* readFile(char* path){
        // �Ҵ��� ���� IO API�� ����Ѵ�...
        return path;
    }
    virtual void writeFile(char* path, char* contents){
        // �Ҵ��� ���� IO API�� ����Ѵ�...
    }
    virtual void loadFileSystem(){
        cout << "PS4" << endl;
    }
};

class NSFileSystem : public FileSystem{
public:
    virtual char* readFile(char* path){
        // ���ٵ��� ���� IO API�� ����Ѵ�...
        return path;
    }
    virtual void writeFile(char* path, char* contents){
        // ���ٵ��� ���� IO API�� ����Ѵ�...
    }
    virtual void loadFileSystem(){
        cout << "SWITCH" << endl;
    }
};

FileSystem& FileSystem::instance(){
    #ifdef PLAYSTATION4
        static FileSystem* instance = new PS4FileSystem();
    #elif defined SWITCH
        static FileSystem* instance = new NSFileSystem();
    #endif
    return *instance;
}
int main(){
    FileSystem& fs = FileSystem::instance();

    //FileSystem& fs = new NSFileSystem();  // error!
    //FileSystem fs2; // error!

    fs.loadFileSystem();   
    return 0;
}
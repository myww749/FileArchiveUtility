
#include "FileRec.h"
#include <string>

//Accessors
string FileRec::getFileName(){
    return this->filename;
}

string FileRec::getTempname(){
    return this->tempname;
}
timespec FileRec::getModiftyTime(){
    return this->modifyTime;
}

int FileRec::getLength(){
    return this->length;
}

int FileRec::getVersion(){
    return this->version;
}

int FileRec::getFileHash(){
    return this->fileHash;
}

int FileRec::getRecentHash(){
    return this->recentHash;
}

int FileRec::getRefnumber(){
    return this->refnumber;
}

int FileRec::getBlockHashes(int index){
    return this->blockhashes.at(index);
}

int FileRec::getVersionids(int index){
    return this->versionids.at(index);
}

string FileRec::getComments(int index){
    return this->comments.at(index);
}

//Mutator
void FileRec::setFileName(string filename){
    this->filename = filename;
}

void FileRec::setTempname(string tempname){
    this->tempname = tempname;
}

void FileRec::setModiftyTime(time_t time){
    
    this->modifyTime = time;
}

void FileRec::setLength(int length){
    this->length = length;
}

void FileRec::setVersion(int version){
    this->version = version;
}

void FileRec::setFileHash(int fileHash){
    this->fileHash = fileHash;
}

void FileRec::setRecentHash(int recentHash){
    this->recentHash =recentHash;
}

void FileRec::setRefnumber(int refnumber){
    this->refnumber =refnumber;
}

void FileRec::setBlockHashes(int index, int value){
    this->blockhashes.at(index) = value;
}

void FileRec::setVersionids(int index, int value){
    this->versionids.at(index) = value;
}

void FileRec::setComments(int index, string value){
    this->comments.at(index) = value;
}

// Read a file and determines values
void FileRec::createData(string filename){
    
    ifstream afile(filename);
    
    //Create a char pointer to read in the file
    char* fileContents;

    //Open the file for read
    ifstream afile(filename,ios::in | ios::binary | ios::ate);
    
    //Find the size of the file
    afile.seekg(0,afile.end);
    
    int length = afile.tellg();
    
    afile.seekg(0, afile.beg);
    
    string temp("temp");
    
    //Set the name and the length of the file
    setFileName(filename);
    
    filename += temp;
    
    setTempname(filename);
    
    setLength(length);
    
    
    //Set the modify time
    struct stat STAT;
    struct utimbuf new_times;
    
    if(stat(filename.c_str(), &STAT) <0)
    {
        perror(filename.c_str());
        exit(0);
    }
    
    setModiftyTime(STAT.st_mtime);
     
    //Read in the file
    if(afile.is_open()){
        
        //Allocate the memory for char[]
        fileContents = new char[length];
        
        //The the contents
        if(!afile.read(fileContents,length))
        {
            cout<<"Fail to read"<<endl;
        }
        
    }
    
    //convert the char* to string 
    string tempContent(fileContents,length);
    stringstream str(tempContent);
    
    int hash;
    
    hash<std::string> hash_fn;
    
    //Hash the content to integer
    hash = hash_fn(str);
    
    setRecentHash(hash);
    
    
    afile.close();
    
    
}

//Transfer record
void FileRec::transferRec(){
    
}

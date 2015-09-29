
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

void FileRec::setModiftyTime(){
    
    //This function only work on Linux
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &this->modifyTime);
    
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
    
    afile.seekg(0,afile.end);
    
    int length = afile.tellg();
    
    afile.seekg(0, afile.beg);
    
    setFileName(filename);
    
    setLength(length);
    
    std::hash<std::string> hash_fn;
    
    int hash = hash_fn(length);
    
    string fileHash = std::to_string(hash);
    
    setFileHash(fileHash);
    
    afile.close();
    
    
}

//Transfer record
void FileRec::transferRec(){
    
}
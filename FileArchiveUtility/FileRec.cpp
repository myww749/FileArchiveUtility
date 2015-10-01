
#include "FileRec.h"

using namespace std;

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

void FileRec::setModiftyTime(timespec time) {
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

    if ( index < (int)this->blockhashes.size() ) {
        this->blockhashes[index] = value;
    } else {
        this->blockhashes.push_back(value);
    }
    
}

void FileRec::setVersionids(int index, int value) {
    
    if ( index < (int)this->versionids.size() ) {
        this->versionids[index] = value;
    } else {
        this->versionids.push_back(value);
    }
    
}

void FileRec::setComments(int index, string value) {
  
    if ( index < (int)this->comments.size() ) {
        this->comments[index] = value;
    } else {
        this->comments.push_back(value);
    }
    
}

// Read a file and determines values
void FileRec::createData(string filename) {

    //Create a char pointer to read in the file
    char* fileContents = NULL;

    //Open the file for read
    ifstream afile(filename.c_str(), ios::in | ios::binary | ios::ate);
    
    //Find the size of the file
    afile.seekg(0, ios::end);
    
    int length = afile.tellg();
    afile.seekg(0, ios::beg);
    string temp("temp");
    
    //Set the name and the length of the file
    setFileName(filename);
    filename += temp;
    setTempname(filename);
    setLength(length);
    
    timespec* ts = NULL;
    
    //Set the modify time CHECKING THE PLATFORM
#ifdef __APPLE__
    
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    ts->tv_sec = mts.tv_sec;
    ts->tv_nsec = mts.tv_nsec;
    
#else
    if ( clock_gettime(CLOCK_REALTIME, ts) == -1) {
        cerr << "Error: Could not get time in func: FileRec::createData" << end;
    }
#endif
    
    setModiftyTime(*ts);
     
    //Read in the file
    if(afile.good()){
        
        //Allocate the memory for char[]
        fileContents = new char[length];
        
        //The the contents
        if(!afile.read(fileContents,length))
        {
            cout<<"Fail to read"<<endl;
        }
    }
    
    //convert the char* to string 
    string tempContent(fileContents, length);
    stringstream str(tempContent);
    
    // continues to get errors for me (brandon) :(
    size_t hash = 0;
    
#ifdef __APPLE__
    //Hash the content to integer
    __gnu_cxx::hash<const char*> hash_fn;
    hash = hash_fn(str.str().c_str());
#else
    std::hash<string> hash_fn;
    hash = hash_fn(str);
#endif
    setRecentHash(hash);
    
    afile.close();
}

//Transfer record
void FileRec::transferRec(){
    
}

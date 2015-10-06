/* 
 * File:   FileArchiver.cpp
 * Author: brq415
 * 
 * Created on 14 September 2015, 11:30 AM
 */

#include "FileArchiver.h"
#include <zlib.h>

using namespace std;

/*
 * Everything needs to be ported over to MySQL, using a web host
 * or it can be done on localhost, a hosted database would make it easier
 * for all team members to get access to the database,
 * it would require no one to change any parts of the code. Should
 * just work :P
 * 
 * This will assume that the database already exists and will not create it if it
 * does not.
 */
FileArchiver::FileArchiver() {
    
    // create the connection
    db = QSqlDatabase::addDatabase(dbDriver);   // QMYSQL driver doesn't exist :(
    db.setHostName(dbHost);
    db.setDatabaseName(dbName);
    db.setUserName(dbUsername);
    db.setPassword(dbPassword);
    
    if ( !db.open() ) { // we have no connection
        cout << "Could not connect to the database at host: " << dbHost.toStdString() << endl;
        cout << "Could be anything." << endl;
        exit(0);
    }
    
    // test a query
    QSqlQuery query1("SELECT * FROM filerec;", db);
    query1.exec();
    
    // TODO: Remove this. It's for testing this function.
    insertNew("myFile.txt", "comment");
}

bool FileArchiver::differs(string filename) {
    
    if ( hashFile(filename) == currentRecord.getRecentHash() ) {
        return false;
    }
    
    return true;
}

bool FileArchiver::exists(string filename) {
    
    // create query and execute it checking if there are any rows returned
    QString query = "SELECT filename FROM filerec;";
    
    
    return true;
}

void FileArchiver::insertNew(string filename, string comment) {
    
    timespec* ts = new timespec();
    string tmpZipFileName = (filename + ".zip");
    
    // first check if the file exists, it would suck if it didn't
    fstream checkExists(filename.c_str(), fstream::in);
    if ( !checkExists.good() ) {
        cerr << "File to insert: " << filename << " does not exist." << endl;
        cerr << "Can not create new database entry, returning." << endl;
        checkExists.close();
        return;
    }
    
    // it's time to create a new filerec.
    currentRecord.setFileName(filename);
    currentRecord.setComments(0, comment);
    currentRecord.setBlockHashes(0, hashFile(filename));
    currentRecord.setFileHash(hashFile(filename));
    currentRecord.setLength(1); // I assume this is the revision count
    currentRecord.setRefnumber(0);
    
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
    
    currentRecord.setModiftyTime(*ts);
    
    delete ts; /* Cleaning your house while your kids are still growing up 
                * is like shoveling the walk before it stops snowing.
                *    - Phyllis Diller
                */
    
    // create a tmp file on disk that is the compressed version of the file
    // being added, this will contain the data to be added to the blob field
    ifstream inFile(filename.c_str(), fstream::binary);
    gzFile outFile = gzopen(tmpZipFileName.c_str(), "wb");
    
    // again check files
    if ( !inFile.good() || !outFile) {
        cerr << "One of the files in compression is bad." << endl;
        return;
    }
    
    const int BUFFER_SIZE = 1024;
    char inBuffer[BUFFER_SIZE];
    
    while ( !inFile.eof() ) {
        inFile.read(inBuffer, BUFFER_SIZE);
        gzwrite(outFile, inBuffer, inFile.gcount());
    }
    
    inFile.close();
    gzclose(outFile);
    
    // now grab all that compressed goodness and send it on it's way to the db
    char* compressedData;
    ifstream tmpZipFile(tmpZipFileName.c_str(), ios::in | ios::binary);
    
    if ( !tmpZipFile.good() ) {
        cerr << "Tmp zip file not found";
        return;
    }
    
    // FIX: Doesn't work properly
    compressedData = new char[BUFFER_SIZE];
    char* leBuffer = new char[BUFFER_SIZE]; // this buffer is French
    while ( !tmpZipFile.eof() ) {
        tmpZipFile.read(leBuffer, BUFFER_SIZE);
        
        // resize compressedFile
        char* newDat = new char[strlen(compressedData) + BUFFER_SIZE];
        strcat(newDat, compressedData);
        strcat(newDat, leBuffer);
        delete[] compressedData;
        compressedData = newDat;
    }
    
#ifdef DEBUG
    
    // check if the data created generates a zip file correctly
    string outTest = "DEBUGZIP.zip";
    ofstream outputZip(outTest.c_str(), ios::out | ios::binary);
    cout << "debug zip running" << endl;
    outputZip.write(compressedData, sizeof(compressedData));
    outputZip.close();
    
#endif
    
    // delete the temporary zip file
    
    // convert timespec in FileRec to something storable in database
    
    // update database
    
    // make sure memory is clear
}

void FileArchiver::update(string filename, string comment) {
    // this will occur if the file already exists and there are differences
    
    // create a new hash and make it the latest and add the changes to the database
    
    // make sure to compress changes using gzip
}

void FileArchiver::retrieveVersion(int versionnum, string filename, string retrievetofilename) {
    // versionnum is the row index in the database of the file for filename and output it to the 
   
    // retrievetofilename
    
    // make sure to decompress
}

int FileArchiver::getCurrentVersionNumber(string filename) {
    // get the last row integer for the filename, that indicate the lastest version
}

size_t FileArchiver::getHashOfLastSaved(string filename) {
    // simply return the hash value of the most recent version of a file
}

bool FileArchiver::getComment(string filename, int versionnum) {
    // get the comment stored with the filename at row number versionnum
}

vector<int> FileArchiver::getVersionInfo(string filename) {
    // returns all versions of a file as integers
}

void FileArchiver::setReference(string filename, int versionnum, string comment) {
    // sets the file which acts as the original
    
    // file changes are stored later on in compress format and are added on
}

void FileArchiver::createZipFile(string filename) {
    // zips the contents of the file as filename.zip so we can read it's bytes
    // and store it in the database
}
    
size_t FileArchiver::hashFile(string filename) {
    
    size_t hash = 0;
    string fileContent = "";
    string line = "";
    
    ifstream fileToHash;
    fileToHash.open(filename.c_str(), fstream::in);
    
    if ( fileToHash.good() ) {
        while ( !fileToHash.eof() ) {
            getline(fileToHash, line, '\n');
            fileContent += line + "\n";
            line = "";
        }
    } else {
        return -1;
    }
    
#ifdef __APPLE__
    
    //Hash the content to integer
    __gnu_cxx::hash<const char*> hash_fn;
    hash = hash_fn(fileContent.c_str());
    
#else
    
    std::hash<string> hash_fn;
    hash = hash_fn(filename);
    
#endif
    
    fileToHash.close();
    return hash;
}

FileArchiver::~FileArchiver() {
    db.close();
}


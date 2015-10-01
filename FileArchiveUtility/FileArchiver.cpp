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
 * Call back function used to handle data result set generator from the execution
 * of an SQL statement. Useful for SELECT statements, not really for INSERTS
 * and CREATES etc.
 */
static int callback(void *data, int argc, char **argv, char **azColName) {
    
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for ( i = 0; i < argc; i++ ) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    
    printf("\n");
    return 0;
}

FileArchiver::FileArchiver() {
    
    char* errMsg = 0;
    string sqlStatement = "";
    
    // check if database exists
    fstream databaseFile(DATABASE_FILE);
    
    // CREATE DATABASE IF IT DOES NOT EXIST
    if ( databaseFile.fail() ) {
        databaseFile.close();
        
        // create
        ofstream dbcFile(DATABASE_FILE, fstream::out);
        dbcFile.close();
        
        rc = sqlite3_initialize();
        
        // read sql file and create sql statement and execute
        ifstream sqlFile(CREATE_DATABASE_SQL_FILE.c_str(), fstream::in);
        
        while ( sqlFile.good() ) {
            string tmp;
            getline(sqlFile, tmp, '\n');
            sqlStatement += tmp + " ";
        }
        sqlFile.close();
        
        // create the sql connection
       rc = sqlite3_open(DATABASE_FILE, &this->database);

       if ( rc ) {
           cerr << "Can not open database file." << sqlite3_errmsg(database) << endl;
           exit(0);
       } else {
           cout << "Successful connection." << endl;
       }

       rc = sqlite3_exec(database, sqlStatement.c_str(), NULL, 0, &errMsg);

       if ( rc == SQLITE_OK ) {
           sqlite3_free(errMsg);
           cout << "table created." << endl;
       } else {
           cerr << "SQL statement execution, something went wrong, likely the statement could \n not run because the table exists." << endl;
           cerr << errMsg << endl;
       }        
    } 
    
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
    
    // check if the file already exists in the database, simply query using the filename
    string query = "SELECT * FROM blobtable;";  // JUST FOR TESTING SO FOR, NEEDS CHANGING
    char *errMsg;
    char *data = "Callback!";   // it looks like the results get stored in data, they dont
    
    // FIX: always results in an error, crashes
    rc = sqlite3_exec(database, query.c_str(), callback, (void*)data, &errMsg);

    if ( rc == SQLITE_OK ) {
        sqlite3_free(errMsg);
    } else {
        cout << "Error, could not complete query in function \"exists\"." << endl;
        return false;
    }
    
    // check 
    if ( hasResults ) {
        hasResults = false;
        return true;
    }
    
    return false;
}

void FileArchiver::insertNew(string filename, string comment) {
    
    timespec* ts = new timespec();
    
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
    
    delete ts;
    // create a tmp file on disk that is the compressed version of the file
    // being added, this will contain the data to be added to the blob field
    ifstream inFile(filename.c_str(), fstream::binary);
    gzFile outFile = gzopen((filename + ".zip").c_str(), "wb");
    
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
    
    // now grab all that compresses goodness and send it on it's way to the db
    
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
    sqlite3_close(database);
}


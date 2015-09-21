/* 
 * File:   FileArchiver.cpp
 * Author: brq415
 * 
 * Created on 14 September 2015, 11:30 AM
 */

#include "FileArchiver.h"

FileArchiver::FileArchiver() {
    
    // create the sql connection
    rc = sqlite3_open(DATABASE_FILE, &this->database);
    
    if ( rc ) {
        cerr << "Can not open database file." << sqlite3_errmsg(database) << endl;
        exit(0);
    } else {
        cout << "Successful connection." << endl;
    }

    
    
}

bool FileArchiver::differs(string filename) {
    
}

bool FileArchiver::exists(string filename) {
    
}

void FileArchiver::insertNew(string filename, string comment) {
    
}

void FileArchiver::update(string filename, string comment) {
    
}

void FileArchiver::retrieveVersion(int versionnum, string filename, string retrievetofilename) {
    
}

void FileArchiver::getCurrentVersionNumber(string filename) {
    
}

void FileArchiver::getHashOfLastSaved(string filename) {
    
}

bool FileArchiver::getComment(string filename, int versionnum) {
    
}

vector<int> FileArchiver::getVersionInfo(string filename) {
    
}

void FileArchiver::setReference(string filename, int versionnum, string comment) {
    
}

void FileArchiver::createZipFile(string filename) {
    
}
    
FileArchiver::~FileArchiver() {
    sqlite3_close(database);
}


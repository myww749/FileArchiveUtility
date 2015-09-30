/* 
 * File:   FileArchiver.h
 * Author: bq415
 *
 * Created on 14 September 2015, 11:30 AM
 */

#ifndef FILEARCHIVER_H
#define	FILEARCHIVER_H

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <sqlite3.h>
#include <stdlib.h>
#include <fstream>
#include <ctime>
#include "constants.h"

/*
 * Interacts heavily with the database, creating and modifying versions of files
 * and updating the database according making use of the FileRec class to represent
 * version of files.
 */
class FileArchiver {
public:    
    FileArchiver();
    
    /*
     * Checks whether or not the file being added differs from
     * the most recently added file already in the database.
     */
    bool differs(std::string filename);
    
    /*
     * Checks if the file already exists in the database.
     */
    bool exists(std::string filename);
    
    /*
     * Creates a new inital archived record and, adds all inital information
     * and stored the reference file (original blob data) and creates the hash.
     * This is all sent to the database.
     */
    void insertNew(std::string filename, std::string comment);
    
    /*
     * Does effectively the same thing as insertNew all though it checks
     * if the file as not changed first and creates a new hash and set the most recent
     * version of the file.
     */
    void update(std::string filename, std::string comment);
    
    /*
     * Simply retrieves a version of a file using the specified index.
     */
    void retrieveVersion(int versionnum, std::string filename, std::string retrievetofilename);
    
    /*
     * searches for the table given filename and gets the most recent version number
     */
    int getCurrentVersionNumber(std::string filename);
    
    /*
     * Goes to the database and collects the value curhash from the filerec in question.
     */
    void getHashOfLastSaved(std::string filename);
    
    /*
     * Simply gets the comment for the specific version.
     */
    bool getComment(std::string filename, int versionnum);
    
    /*
     * Returns a vector list of all the indexes of a file.
     */
    std::vector<int> getVersionInfo(std::string filename);
    
    /*
     * The reference is the original version of the file first uploaded.
     * This reads the file and sets the reference which is stored as the version at
     * index 0 in the database.
     */
    void setReference(std::string filename, int versionnum, std::string comment);
    
    /*
     * Compresses the file data before storage to reduce footprint.
     */
    void createZipFile(std::string filename);
    
    virtual ~FileArchiver();
private:
    int rc;
    sqlite3 *database;
    bool hasResults = false; /* Set in call back to false if there are no results,
                              * only use this to check after you execute a query
                              * then reset to false
                              */
};

#endif	/* FILEARCHIVER_H */


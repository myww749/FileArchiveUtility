/* 
 * File:   FileArchiver.h
 * Author: bq415
 *
 * Created on 14 September 2015, 11:30 AM
 */

#ifndef FILEARCHIVER_H
#define	FILEARCHIVER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;


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
    bool differs(string filename);
    
    /*
     * Checks if the file already exists in the database.
     */
    bool exists(string filename);
    
    /*
     * Creates a new inital archived record and, adds all inital information
     * and stored the reference file (original blob data) and creates the hash.
     * This is all sent to the database.
     */
    void insertNew(string filename, string comment);
    
    /*
     * Does effectively the same thing as insertNew all though it checks
     * if the file as not changed first and creates a new hash and set the most recent
     * version of the file.
     */
    void update(string filename, string comment);
    
    /*
     * Simply retrieves a version of a file using the specified index.
     */
    void retrieveVersion(int versionnum, string filename, string retrievetofilename);
    
    
    void getCurrentVersionNumber(string filename);
    
    /*
     * Goes to the database and collects the value curhash from the filerec in question.
     */
    void getHashOfLastSaved(string filename);
    
    /*
     * Simply gets the comment for the specific version.
     */
    bool getComment(string filename, int versionnum);
    // vector<int> getVersionInfo(string filename);
    
    /*
     * The reference is the original version of the file first uploaded.
     * This reads the file and sets the reference which is stored as the version at
     * index 0 in the database.
     */
    void setReference(string filename, int versionnum, string comment);
    
    /*
     * Compresses the file data before storage to reduce footprint.
     */
    void createZipFile(string filename);
    virtual ~FileArchiver();
private:
    
};

#endif	/* FILEARCHIVER_H */


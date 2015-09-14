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

class FileArchiver {
public:
    FileArchiver();
    bool differs(string filename);
    bool exists(string filename);
    void insertNew(string filename, string comment);
    void update(string filename, string comment);
    void retrieveVersion(int versionnum, string filename, string retrievetofilename);
    void getCurrentVersionNumber(string filename);
    void getHashOfLastSaved(string filename);
    bool getComment(string filename, int versionnum);
    // vector<int> getVersionInfo(string filename);
    void setReference(string filename, int versionnum, string comment);
    virtual ~FileArchiver();
private:
    
};

#endif	/* FILEARCHIVER_H */


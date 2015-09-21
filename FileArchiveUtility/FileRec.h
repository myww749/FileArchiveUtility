/* 
 * File:   FileRec.h
 * Author: ChenYiTai
 *
 * Created on September 14, 2015, 11:13 AM
 */

#ifndef FILEREC_H
#define	FILEREC_H

#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;

class FileRec{
	private:
		string filename;
		string tempname;
                timespec modifyTime;
		int length;
		int version;
		int fileHash;
		int recentHash;
		int refnumber;
		vector<int> blockhashes;
		vector<int> versionids;
		vector<string> comments;

	public:
                //Constructor
                FileRec(){};
		
                //Accessors
		string getFileName();
		string getTempname();
                timespec getModiftyTime();
		int getLength();
		int getVersion();
		int getFileHash();
		int getRecentHash();
		int getRefnumber();
                int getBlockHashes(int index);
                int getVersionids(int index);
                string getComments(int index);

		//Mutator
		void setFileName(string filename);
		void setTempname(string tempname);
                void setModiftyTime();
		void setLength(int length);
		void setVersion(int version);
		void setFileHash(int fileHash);
		void setRecentHash(int recentHash);
		void setRefnumber(int refnumber);
                void setBlockHashes(int index, int value);
                void setVersionids(int index, int value);
                void setComments(int index, string value);
    
		// Read a file and determines values
		void createData(string filename);

		//Transfer record
		void transferRec();
};

#endif	/* FILEREC_H */


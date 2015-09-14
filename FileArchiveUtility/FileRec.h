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

using namespace std;

class FileRec{
	private:
		string filename;
		string tempname;
		int length;
		int version;
		int fileHash;
		int recentHash;
		int refnumber;
		vector<int> blockhashes;
		vector<int> versionids;
		vector<string> comments;

	public:

		//Accessors

		string getFileName();
		string getTempname();
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


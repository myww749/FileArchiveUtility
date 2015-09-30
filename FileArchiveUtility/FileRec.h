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
#include <sstream>
#include <functional>

//Modified time
#include <time.h>
#include <sys/stat.h>
#include <stdio.h>
#include <utime.h>
#include <string>

class FileRec{
	private:
		std::string filename;
		std::string tempname;
                time_t modifyTime;
		int length;
		int version;
		int fileHash;
		int recentHash;
		int refnumber;
		std::vector<int> blockhashes;
		std::vector<int> versionids;
		std::vector<std::string> comments;

	public:
                //Constructor
                FileRec(){};
		
                //Accessors
		std::string getFileName();
		std::string getTempname();
                time_t getModiftyTime();
		int getLength();
		int getVersion();
		int getFileHash();
		int getRecentHash();
		int getRefnumber();
                int getBlockHashes(int index);
                int getVersionids(int index);
                std::string getComments(int index);

		//Mutator
		void setFileName(std::string filename);
		void setTempname(std::string tempname);
                void setModiftyTime(time_t time);
		void setLength(int length);
		void setVersion(int version);
		void setFileHash(int fileHash);
		void setRecentHash(int recentHash);
		void setRefnumber(int refnumber);
                void setBlockHashes(int index, int value);
                void setVersionids(int index, int value);
                void setComments(int index, std::string value);
    
		// Read a file and determines values
		void createData(std::string filename);

		//Transfer record
		void transferRec();
};

#endif	/* FILEREC_H */


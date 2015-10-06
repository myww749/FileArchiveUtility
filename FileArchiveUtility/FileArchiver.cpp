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
    db.setPort(3306);
    
    if ( !db.open() ) { // we have no connection
        cerr << "Could not connect to the database at host: " << dbHost.toStdString() << endl;
        cerr << "Could be anything." << endl;
    }
    
    // test a query
    QSqlQuery query1("SELECT * FROM filerec;", db);
    query1.exec();
    
}

bool FileArchiver::differs(string filename) {
    
    if ( static_cast<int>(hashFile(filename)) == currentRecord.getRecentHash() ) {
        return false;
    }
    
    return true;
}

bool FileArchiver::exists(string filename) {
    
    // create query and execute it checking if there are any rows returned
    string queryString = "SELECT " + filename + " FROM filerec;";
    QString qQueryString;
    qQueryString.append(queryString.c_str());
    
    QSqlQuery query(db);
    query.exec(qQueryString);
    
    while ( query.next() ) {
        QString name = query.value(0).toString();
        
        if ( name == "" || name == NULL)
            return false;
        
        qDebug() << name;
    }
    
    return true;
}

timespec* FileArchiver::getTime() {
    timespec* ts = new timespec();
    
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
 
    return ts;
}

/*
 * A lot of the inner working of this function can be moved to the
 * update function, this should probably modify the currentFileRec 
 * and then use the update function to add it to the database
 */
void FileArchiver::insertNew(string filename, string comment) {
    string tmpZipFileName = (filename + ".zip");
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
    
    ts = getTime();
    currentRecord.setModiftyTime(*ts);
    
    // create a tmp file on disk that is the compressed version of the file
    // being added, this will contain the data to be added to the blob field
    // now grab all that compressed goodness and send it on it's way to the db
    char* compressedData;
    compressedData = compressFile(filename);
    
#ifdef DEBUG
    
    // check if the data created generates a zip file correctly
    string outTest = filename + ".zip";
    ofstream outputZip(outTest.c_str(), ios::out | ios::binary);
    cout << "debug zip running" << endl;
    outputZip.write(compressedData, sizeof(compressedData));
    outputZip.close();
    
#endif
    
    // TODO: Calls hashFile many times, hashFile is not efficient, it does io
    // store it 
    
    // delete the temporary zip file, all compression data should be saved
    QString filenameQString     = QString::fromStdString(filename);
    QString compressesDatQStr   = QString::fromStdString(string(compressedData));
    
    QString addToBlobTable      = "INSERT INTO blobtable VALUES (" + filenameQString + 
                                    ", " + compressesDatQStr + ");";
    
    // current the curhash and the ovhash are the same
    QString addToFilerec        = "INSERT INTO filerec VALUES(" 
                                + filenameQString + ", " 
                                + hashFile(filename) + ", " 
                                + hashFile(filename) + ", " 
                                + 1 + ", "
                                + 1 + ", " 
                                + strlen(compressedData) + ", " 
                                + ts->tv_nsec + ", " 
                                + ts->tv_sec + ", " 
                                + QString::fromStdString(outTest) + ", " 
                                + QString::fromStdString(outTest) // mentions blobtable_tempname, not sure about this
                                + ts->tv_sec + ", " 
                                + ");";
    
    QString addToCommentsTable  = "INSERT INTO commentstable (filerec, commentnum, commenttxt) VALUES("
                                + filenameQString + ", "
                                + 1 + ", "
                                + QString::fromStdString(comment)
                                + ");";
    
    QString addToFileBlkHashes  = "INSERT INTO fileblkhashes (fileref, blknum, hashval) VALUES("
                                + filenameQString + ", "
                                + 1 + ", "
                                + hashFile(filename) + ", "
                                + ");";
    
    QString addToVersionRec     = "INSERT INTO versionrec (fileref, versionnum, length, mtsec, mtnsec, ovhash) VALUES("
                                + filenameQString + ", "
                                + 1 + ", "
                                + strlen(compressedData) + ", "
                                + ts->tv_nsec + ", "
                                + ts->tv_sec + ", "
                                + hashFile(filename) + ", "
                                + ");";
    
    // update database
    QSqlQuery insertQuery(db);
    insertQuery.exec(addToBlobTable);
    insertQuery.exec(addToFilerec);
    insertQuery.exec(addToCommentsTable);
    insertQuery.exec(addToFileBlkHashes);
    insertQuery.exec(addToVersionRec);
    
    // make sure memory is clear
    delete ts;
    delete[] compressedData;
}

void FileArchiver::update(string filename, string comment) {
    
    // this will occur if the file already exists and there are differences
    timespec* ts = new timespec();
    
    // create a new hash and make it the latest and add the changes to the database
    size_t hash = hashFile(filename);
    
    char* compressedData = compressFile(filename);
    
    currentRecord.addVersion(filename, comment, filename, *ts, strlen(compressedData), currentRecord.getVersion() + 1, hash);
    
    QString filenameQString     = QString::fromStdString(filename);
    QString compressesDatQStr   = QString::fromStdString(string(compressedData));
    
    // do queries
    QString addToBlobTable      = "INSERT INTO blobtable VALUES (" + filenameQString + 
                                    ", " + compressesDatQStr + ");";
    
    QString addToVersionRec     = "INSERT INTO versionrec (fileref, versionnum, length, mtsec, mtnsec, ovhash) VALUES("
                                + filenameQString + ", "
                                + currentRecord.getVersion() + 1 + ", "
                                + strlen(compressedData) + ", "
                                + ts->tv_nsec + ", "
                                + ts->tv_sec + ", "
                                + hashFile(filename) + ", "
                                + ");";
    
    QString addToCommentsTable  = "INSERT INTO commentstable (filerec, commentnum, commenttxt) VALUES("
                                + filenameQString + ", "
                                + currentRecord.getVersion() + 1 + ", "
                                + QString::fromStdString(comment)
                                + ");";
    
    QString addToFileBlkHashes  = "INSERT INTO fileblkhashes (fileref, blknum, hashval) VALUES("
                                + filenameQString + ", "
                                + currentRecord.getVersion() + 1 + ", "
                                + hashFile(filename) + ", "
                                + ");";   
   
    QSqlQuery updateQuery(db);
    updateQuery.exec(addToBlobTable);
    updateQuery.exec(addToVersionRec);
    updateQuery.exec(addToCommentsTable);
    updateQuery.exec(addToFileBlkHashes);
    
    delete ts;
    delete[] compressedData;
}

void FileArchiver::retrieveVersion(int versionnum, string filename, string retrievetofilename) {
    
    // versionnum is the row index in the database of the file for filename and output it to the 
    ofstream outputZipFile;
    QString qFilename = QString::fromStdString(filename);
    QString verQueryStr = "SELECT * FROM versionrec WHERE fileref='" + qFilename + "';";
    
    // version data
    int id = 0;
    QString fileref;
    int length = 0;
    int mtsec = 0;
    int mtnsec = 0;
    int ovhash = 0;
    
    // run the query to get version info
    QSqlQuery query1(db);
    query1.exec(verQueryStr);
    
    for ( int i = 0; i < versionnum; i++ ) {
        query1.next();
        QString tmp = query1.value(0).toString();
        id = query1.value(0).toString().toInt();
        fileref = query1.value(1).toString();
        length = query1.value(2).toString().toInt();
        mtsec = query1.value(3).toString().toInt();
        mtnsec = query1.value(4).toString().toInt();
        ovhash = query1.value(5).toString().toInt();
        
        if ( tmp == "" || tmp == NULL) {
            cerr << "Went too far getting version from db or no data." << endl;
            return;
        }
    }
    
    ostringstream vnConvert;
    ostringstream ovhashConvert;
    
    vnConvert << versionnum;
    ovhashConvert << ovhash;
    
    QString dataQueryStr = QString::fromStdString("SELECT version, data, ovhash FROM blktable WHERE version=" + vnConvert.str() + " AND ovhash=" + ovhashConvert.str() + ";");
    
    // run query to get actual data
    QSqlQuery query2(db);
    query2.exec(dataQueryStr);
    
    // there should only be 1 result
    query1.next();
    
    QString data = query1.value(1).toString();
    
    ostringstream mtConvert;
    ostringstream mtnConvert;
    
    mtConvert << mtsec;
    mtnConvert << mtnsec;
    
    // write out data
    outputZipFile.open(string(filename + "_" + mtConvert.str() + "_" + mtnConvert.str() + ".zip").c_str(), ios::out | ios::binary);
    
    if ( outputZipFile.good() ) {
        outputZipFile << data.toStdString().c_str();
        outputZipFile.close();

    } else {
        cerr << "Could not create output zip file." << endl;
        return;
    }
    
    // retrievetofilename
    
    // make sure to decompress
}

int FileArchiver::getCurrentVersionNumber() {
    currentRecord.getVersion();
}

size_t FileArchiver::getHashOfLastSaved() {
    currentRecord.getRecentHash();
}

string FileArchiver::getComment(int versionnum) {
    // get the comment stored with the filename at row number versionnum
    currentRecord.getCommentsVector()[versionnum];
}

vector<int> FileArchiver::getVersionInfo() {
    return currentRecord.getVersionIdsVector();
}

void FileArchiver::setReference(string filename, int versionnum, string comment) {
    // sets the file which acts as the original
    
    // file changes are stored later on in compress format and are added on
}

char* FileArchiver::compressFile(string filename) {
    string tmpZipFileName = (filename + ".zip");
    char inBuffer[BUFFER_SIZE];
    char* compressedData;
    
    // zips the contents of the file as filename.zip so we can read it's bytes
    // and store it in the database
    ifstream inFile(filename.c_str(), fstream::binary);
    gzFile outFile = gzopen(tmpZipFileName.c_str(), "wb");
    
    // again check files
    if ( !inFile.good() || !outFile) {
        cerr << "One of the files in compression is bad." << endl;
        return NULL;
    }
    
    while ( !inFile.eof() ) {
        inFile.read(inBuffer, BUFFER_SIZE);
        gzwrite(outFile, inBuffer, inFile.gcount());
    }
    
    inFile.close();
    gzclose(outFile);
    
    ifstream tmpZipFile(tmpZipFileName.c_str(), ios::in | ios::binary);
    
    if ( !tmpZipFile.good() ) {
        cerr << "Tmp zip file not found";
        return NULL;
    }
    
    // TODO: Compression does not work properly, reading the compressesData and
    // printing it out results in something very not right :(
    compressedData = new char[BUFFER_SIZE];
    char* leBuffer = new char[BUFFER_SIZE];
    
    while ( !tmpZipFile.eof() ) {
        
        tmpZipFile.read(leBuffer, BUFFER_SIZE);
        
        // resize compressedFile
        char* newDat = new char[strlen(compressedData) + BUFFER_SIZE];
        strcat(newDat, compressedData);
        strcat(newDat, leBuffer);
        delete[] compressedData;
        compressedData = newDat;
        
    }
    
    delete[] leBuffer;
    return compressedData;
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


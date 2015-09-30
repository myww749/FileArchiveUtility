/* 
 * File:   constants.h
 * Author: bq415
 *
 * Created on 20 September 2015, 9:38 PM
 */

#ifndef CONSTANTS_H
#define	CONSTANTS_H

#include <string>

/*
 * Stores constants for system wide usage.
 */

// the name of the sqlite3 database file
const char DATABASE_FILE[] = "persistentstore.db";

// sql file for creating a database
const std::string CREATE_DATABASE_SQL_FILE = "createTables.sql";

// test SQL statement
const char TEST_SQL[] = "CREATE TABLE test ( id INT NOT NULL UNIQUE, name VARCHAR(255) NOT NULL );";

#endif	/* CONSTANTS_H */


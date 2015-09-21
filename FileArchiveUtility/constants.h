/* 
 * File:   constants.h
 * Author: bq415
 *
 * Created on 20 September 2015, 9:38 PM
 */

#ifndef CONSTANTS_H
#define	CONSTANTS_H

/*
 * Stores constants for system wide usage.
 */

// the name of the sqlite3 database file
const char DATABASE_FILE[] = "database.db";

// test SQL statement
const char TEST_SQL[] = "CREATE TABLE test ( id INT NOT NULL UNIQUE, name VARCHAR(255) NOT NULL );";

#endif	/* CONSTANTS_H */


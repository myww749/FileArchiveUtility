CREATE TABLE IF NOT EXISTS blobtable ( 
    tempname VARCHAR(45) NOT NULL, 
    filedata MEDIUMBLOB NOT NULL, 
    PRIMARY KEY (tempname) 
);

CREATE TABLE IF NOT EXISTS filerec ( 
    filename VARCHAR(255) NOT NULL, 
    curhash INT(11) NOT NULL, 
    ovhash INT(11) NOT NULL, 
    currentversion INT(11) NOT NULL, 
    nversions INT(11) NOT NULL, 
    length INT(11) NOT NULL, 
    mtnsec INT(11) NOT NULL, 
    mtsec INT(11) NOT NULL, 
    tempname VARCHAR(45) NOT NULL, 
    blobtable_tempname VARCHAR(45) NOT NULL, 
    PRIMARY KEY (filename), 
    CONSTRAINT fk_filerec_blobtable FOREIGN KEY (blobtable_tempname) REFERENCES blobtable (tempname) 
);

CREATE TABLE IF NOT EXISTS commentstable ( 
    idcommentstable INT(11) NOT NULL, 
    filerec VARCHAR(255) NOT NULL, 
    commentnum INT(11) NOT NULL, 
    commenttxt MEDIUMTEXT NOT NULL, 
    PRIMARY KEY (idcommentstable), 
    CONSTRAINT fk_commentstable_filerec1 FOREIGN KEY (filerec) REFERENCES filerec (filename) 
);

CREATE TABLE IF NOT EXISTS fileblkhashes ( 
    idfileblkhashes INT(11) NOT NULL, 
    fileref VARCHAR(255) NOT NULL, 
    blknum INT(11) NOT NULL, 
    hashval INT(11) NOT NULL, 
    PRIMARY KEY (idfileblkhashes), 
    CONSTRAINT fk_fileblkhashes_filerec1 FOREIGN KEY (fileref) REFERENCES filerec (filename) 
);

CREATE TABLE IF NOT EXISTS versionrec ( 
    idversionrec INT(11) NOT NULL, 
    fileref VARCHAR(255) NOT NULL, 
    versionnum INT(11) NOT NULL, 
    length INT(11) NOT NULL, 
    mtsec INT(11) NOT NULL, 
    mtnsec INT(11) NOT NULL, 
    ovhash INT(11) NOT NULL, 
    PRIMARY KEY (idversionrec), 
    CONSTRAINT fk_versionrec_filerec1 FOREIGN KEY (fileref) REFERENCES filerec (filename) 
);

CREATE TABLE IF NOT EXISTS blktable ( 
    idblktable INT(11) NOT NULL, 
    version INT(11) NOT NULL, 
    length INT(11) NOT NULL, 
    blknum INT(11) NOT NULL, 
    hash INT(11) NOT NULL, 
    data MEDIUMBLOB NOT NULL, 
    CONSTRAINT fk_blktable_filerec1 FOREIGN KEY (version) REFERENCES versionrec (idversionrec) 
);

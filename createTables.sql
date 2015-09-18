DROP SCHEMA IF EXISTS `mydb` ;
CREATE SCHEMA IF NOT EXISTS `mydb` DEFAULT CHARACTER SET latin1 COLLATE
latin1_swedish_ci ;
USE `mydb` ;
-- -----------------------------------------------------
-- Table `mydb`.`FileRec`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `mydb`.`filerec` (
    `filename` VARCHAR(255) NOT NULL ,
    `curhash` INT(11) NOT NULL ,
    `ovhash` INT(11) NOT NULL ,
    `currentversion` INT(11) NOT NULL ,
    `nversions` INT(11) NOT NULL ,
    `length` INT(11) NOT NULL ,
    `mtnsec` INT(11) NOT NULL ,
    `mtsec` INT(11) NOT NULL ,
    `tempname` VARCHAR(45)  NOT NULL,
    `blobtable_tempname` VARCHAR(45) NOT NULL,
    PRIMARY KEY (`filename`),
    CONSTRAINT `fk_filerec_blobtable`
    FOREIGN KEY (`blobtable_tempname` )
    REFERENCES `mydb`.`blobtable` (`tempname`) )
ENGINE = InnoDB;
-- -----------------------------------------------------
-- Table `mydb`.`BlobTable`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `mydb`.`blobtable` (
    `tempname` VARCHAR(45) NOT NULL ,
    `filedata` MEDIUMBLOB NOT NULL ,
   PRIMARY KEY (`tempname`),
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;
-- -----------------------------------------------------
-- Table `mydb`.`CommentsTable`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `mydb`.`commentstable` (
    `idcommentstable` INT(11) NOT NULL ,
    `filerec` VARCHAR(255) NOT NULL ,
    `commentnum` INT(11) NOT NULL ,
    `commenttxt` MEDIUMTEXT NOT NULL ,
    PRIMARY KEY (`idcommentstable`),
  INDEX `fk_commentstable_filerec1` (`idcommentstable` ASC) ,
  CONSTRAINT `fk_commentstable_filerec1`
    FOREIGN KEY (`filerec` )
    REFERENCES `mydb`.`filerec` (`filename` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;
-- -----------------------------------------------------
-- Table `mydb`.`FileBlkHashes`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `mydb`.`fileblkhashes` (
    `idfileblkhashes` INT(11) NOT NULL,
    `fileref` VARCHAR(255) NOT NULL ,
    `blknum` INT(11) NOT NULL ,
    `hashval` INT(11) NOT NULL ,
    PRIMARY KEY (`idfileblkhashes`),
  INDEX `fk_fileblkhashes_filerec1` (`idfileblkhashes` ASC) ,
  CONSTRAINT `fk_fileblkhashes_filerec1`
    FOREIGN KEY (`fileref` )
    REFERENCES `mydb`.`filerec` (`filename` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;
-- -----------------------------------------------------
-- Table `mydb`.`VersionRec`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `mydb`.`versionrec` (
    `idversionrec` INT(11) NOT NULL ,
    `fileref` VARCHAR(255) NOT NULL ,
    `versionnum` INT NOT(11) NOT NULL ,
    `length` INT(11) NOT NULL ,
    `mtsec` INT(11) NOT NULL ,
    `mtnsec` INT(11) NOT NULL ,
    `ovhash` INT(11) NOT NULL ,
    PRIMARY KEY (`idversionrec`),
  INDEX `fk_versionrec_filerec1` (`idversionrec` ASC) ,
  CONSTRAINT `fk_versionrec_filerec1`
    FOREIGN KEY (`fileref` )
    REFERENCES `mydb`.`filerec` (`filename` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

-- -----------------------------------------------------
-- Table `mydb`.`BlkTable`
-- -----------------------------------------------------
CREATE  TABLE IF NOT EXISTS `mydb`.`blktable` (
    `idblktable` INT(11) NOT NULL ,
    `version` INT(11) NOT NULL ,
    `length` INT(11) NOT NULL ,
    `blknum` INT(11) NOT NULL ,
    `hash` INT(11) NOT NULL ,
    `data` MEDIUMBLOB NOT NULL ,
  INDEX `fk_blktable_filerec1` (`idblktable` ASC) ,
  CONSTRAINT `fk_blktable_filerec1`
    FOREIGN KEY (`version` )
    REFERENCES `mydb`.`versionrec` (`idversionrec` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;

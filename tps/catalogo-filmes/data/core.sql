-- MySQL Workbench Synchronization
-- Generated: 2017-11-18 21:44
-- Model: New Model
-- Version: 1.0
-- Project: Catálogo de Filmes
-- Author: Douglas

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL,ALLOW_INVALID_DATES';

CREATE SCHEMA IF NOT EXISTS `catalogo` DEFAULT CHARACTER SET utf8 ;

CREATE TABLE IF NOT EXISTS `catalogo`.`filmes` (
  `idfilme` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `nomeoriginal` VARCHAR(128) NOT NULL,
  `nometraduzido` VARCHAR(128) NOT NULL,
  `ano` INT(4) UNSIGNED NOT NULL,
  `linktrailer` VARCHAR(256) NULL DEFAULT NULL,
  `imdb` VARCHAR(10) NULL DEFAULT NULL,
  `nota` INT(2) UNSIGNED NULL DEFAULT NULL,
  PRIMARY KEY (`idfilme`),
  UNIQUE INDEX `idfilme_UNIQUE` (`idfilme` ASC),
  UNIQUE INDEX `imdb_UNIQUE` (`imdb` ASC))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8;

CREATE TABLE IF NOT EXISTS `catalogo`.`pessoas` (
  `idpessoa` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `nomenascimento` VARCHAR(128) NOT NULL,
  `nomeartistico` VARCHAR(64) NOT NULL,
  `locanascimento` VARCHAR(64) NULL DEFAULT NULL,
  `paises` INT(10) UNSIGNED NULL DEFAULT NULL,
  PRIMARY KEY (`idpessoa`, `nomenascimento`, `nomeartistico`),
  UNIQUE INDEX `iddiretor_UNIQUE` (`idpessoa` ASC),
  INDEX `fk_pessoas_paises_idx` (`paises` ASC),
  CONSTRAINT `fk_pessoas_paises`
    FOREIGN KEY (`paises`)
    REFERENCES `catalogo`.`paises` (`idpais`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8;

CREATE TABLE IF NOT EXISTS `catalogo`.`generos` (
  `idgenero` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `descricao` VARCHAR(32) NOT NULL,
  PRIMARY KEY (`idgenero`),
  UNIQUE INDEX `idgenero_UNIQUE` (`idgenero` ASC),
  UNIQUE INDEX `descricao_UNIQUE` (`descricao` ASC))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8;

CREATE TABLE IF NOT EXISTS `catalogo`.`paises` (
  `idpais` INT(10) UNSIGNED NOT NULL AUTO_INCREMENT,
  `nome` VARCHAR(45) NOT NULL,
  `sigla` VARCHAR(3) NOT NULL,
  PRIMARY KEY (`idpais`),
  UNIQUE INDEX `idpais_UNIQUE` (`idpais` ASC),
  UNIQUE INDEX `nome_UNIQUE` (`nome` ASC),
  UNIQUE INDEX `sigla_UNIQUE` (`sigla` ASC))
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8;

CREATE TABLE IF NOT EXISTS `catalogo`.`filmes_generos` (
  `filmes_idfilme` INT(10) UNSIGNED NOT NULL,
  `generos_idgenero` INT(10) UNSIGNED NOT NULL,
  PRIMARY KEY (`filmes_idfilme`, `generos_idgenero`),
  INDEX `fk_filmes_has_generos_generos1_idx` (`generos_idgenero` ASC),
  INDEX `fk_filmes_has_generos_filmes1_idx` (`filmes_idfilme` ASC),
  CONSTRAINT `fk_filmes_has_generos_filmes1`
    FOREIGN KEY (`filmes_idfilme`)
    REFERENCES `catalogo`.`filmes` (`idfilme`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_filmes_has_generos_generos1`
    FOREIGN KEY (`generos_idgenero`)
    REFERENCES `catalogo`.`generos` (`idgenero`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8;

CREATE TABLE IF NOT EXISTS `catalogo`.`filme_diretor` (
  `filmes_idfilme` INT(10) UNSIGNED NOT NULL,
  `pessoas_idpessoa` INT(10) UNSIGNED NOT NULL,
  PRIMARY KEY (`filmes_idfilme`, `pessoas_idpessoa`),
  INDEX `fk_filmes_has_pessoas_pessoas1_idx` (`pessoas_idpessoa` ASC),
  INDEX `fk_filmes_has_pessoas_filmes1_idx` (`filmes_idfilme` ASC),
  CONSTRAINT `fk_filmes_has_pessoas_filmes1`
    FOREIGN KEY (`filmes_idfilme`)
    REFERENCES `catalogo`.`filmes` (`idfilme`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_filmes_has_pessoas_pessoas1`
    FOREIGN KEY (`pessoas_idpessoa`)
    REFERENCES `catalogo`.`pessoas` (`idpessoa`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8;

CREATE TABLE IF NOT EXISTS `catalogo`.`filme_ator` (
  `filmes_idfilme` INT(10) UNSIGNED NOT NULL,
  `pessoas_idpessoa` INT(10) UNSIGNED NOT NULL,
  PRIMARY KEY (`filmes_idfilme`, `pessoas_idpessoa`),
  INDEX `fk_filmes_has_pessoas_pessoas2_idx` (`pessoas_idpessoa` ASC),
  INDEX `fk_filmes_has_pessoas_filmes2_idx` (`filmes_idfilme` ASC),
  CONSTRAINT `fk_filmes_has_pessoas_filmes2`
    FOREIGN KEY (`filmes_idfilme`)
    REFERENCES `catalogo`.`filmes` (`idfilme`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_filmes_has_pessoas_pessoas2`
    FOREIGN KEY (`pessoas_idpessoa`)
    REFERENCES `catalogo`.`pessoas` (`idpessoa`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8;

CREATE TABLE IF NOT EXISTS `catalogo`.`filme_pais` (
  `filmes_idfilme` INT(10) UNSIGNED NOT NULL,
  `paises_idpais` INT(10) UNSIGNED NOT NULL,
  PRIMARY KEY (`filmes_idfilme`, `paises_idpais`),
  INDEX `fk_filmes_has_paises_paises1_idx` (`paises_idpais` ASC),
  INDEX `fk_filmes_has_paises_filmes1_idx` (`filmes_idfilme` ASC),
  CONSTRAINT `fk_filmes_has_paises_filmes1`
    FOREIGN KEY (`filmes_idfilme`)
    REFERENCES `catalogo`.`filmes` (`idfilme`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_filmes_has_paises_paises1`
    FOREIGN KEY (`paises_idpais`)
    REFERENCES `catalogo`.`paises` (`idpais`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB
DEFAULT CHARACTER SET = utf8;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

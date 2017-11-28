/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `pais`
--

DROP TABLE IF EXISTS `pais`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `pais` (
  `id` int(11) NOT NULL DEFAULT '0',
  `nome` varchar(255) CHARACTER SET utf8 DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `nome` (`nome`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `pais`
--

LOCK TABLES `pais` WRITE;
/*!40000 ALTER TABLE `pais` DISABLE KEYS */;
INSERT INTO `pais` VALUES (1,'Afeganistão'),(2,'África do Sul'),(3,'Åland, Ilhas'),(4,'Albânia'),(5,'Alemanha'),(6,'Andorra'),(7,'Angola'),(8,'Anguilla'),(9,'Antárctida'),(10,'Antigua e Barbuda'),(11,'Antilhas Holandesas'),(12,'Arábia Saudita'),(13,'Argélia'),(14,'Argentina'),(15,'Arménia'),(16,'Aruba'),(17,'Austrália'),(18,'Áustria'),(19,'Azerbeijão'),(20,'Bahamas'),(21,'Bahrain'),(22,'Bangladesh'),(23,'Barbados'),(24,'Bélgica'),(25,'Belize'),(26,'Benin'),(27,'Bermuda'),(28,'Bielo-Rússia'),(29,'Bolívia'),(30,'Bósnia-Herzegovina'),(31,'Botswana'),(32,'Bouvet, Ilha'),(33,'Brasil'),(34,'Brunei'),(35,'Bulgária'),(36,'Burkina Faso'),(37,'Burundi'),(38,'Butão'),(39,'Cabo Verde'),(41,'Camarões'),(40,'Cambodja'),(42,'Canadá'),(43,'Cayman, Ilhas'),(44,'Cazaquistão'),(45,'Centro-africana, República'),(46,'Chade'),(47,'Checa, República'),(48,'Chile'),(49,'China'),(50,'Chipre'),(51,'Christmas, Ilha'),(52,'Cocos, Ilhas'),(53,'Colômbia'),(54,'Comores'),(56,'Congo, República Democrática do (antigo Zaire)'),(55,'Congo, República do'),(57,'Cook, Ilhas'),(58,'Coreia do Sul'),(59,'Coreia, República Democrática da (Coreia do Norte)'),(60,'Costa do Marfim'),(61,'Costa Rica'),(62,'Croácia'),(63,'Cuba'),(64,'Dinamarca'),(65,'Djibouti'),(66,'Dominica'),(67,'Dominicana, República'),(68,'Egipto'),(69,'El Salvador'),(70,'Emiratos Árabes Unidos'),(71,'Equador'),(72,'Eritreia'),(73,'Eslováquia'),(74,'Eslovénia'),(75,'Espanha'),(76,'Estados Unidos da América'),(77,'Estónia'),(78,'Etiópia'),(79,'Faroe, Ilhas'),(80,'Fiji'),(81,'Filipinas'),(82,'Finlândia'),(83,'França'),(84,'Gabão'),(85,'Gâmbia'),(86,'Gana'),(87,'Geórgia'),(88,'Geórgia do Sul e Sandwich do Sul, Ilhas'),(89,'Gibraltar'),(90,'Grécia'),(91,'Grenada'),(92,'Gronelândia'),(93,'Guadeloupe'),(94,'Guam'),(95,'Guatemala'),(96,'Guernsey'),(97,'Guiana'),(98,'Guiana Francesa'),(101,'Guiné Equatorial'),(99,'Guiné-Bissau'),(100,'Guiné-Conacri'),(102,'Haiti'),(103,'Heard e Ilhas McDonald, Ilha'),(245,'Holanda'),(104,'Honduras'),(105,'Hong Kong'),(106,'Hungria'),(107,'Iémen'),(108,'Índia'),(109,'Indonésia'),(246,'Inglaterra'),(111,'Irão'),(110,'Iraque'),(112,'Irlanda'),(113,'Islândia'),(114,'Israel'),(115,'Itália'),(116,'Jamaica'),(117,'Japão'),(118,'Jersey'),(119,'Jordânia'),(120,'Kiribati'),(121,'Kuwait'),(122,'Laos'),(123,'Lesoto'),(124,'Letónia'),(125,'Líbano'),(126,'Libéria'),(127,'Líbia'),(128,'Liechtenstein'),(129,'Lituânia'),(130,'Luxemburgo'),(131,'Macau'),(132,'Macedónia, República da'),(133,'Madagáscar'),(134,'Malásia'),(135,'Malawi'),(136,'Maldivas'),(137,'Mali'),(138,'Malta'),(139,'Malvinas, Ilhas (Falkland)'),(140,'Man, Ilha de'),(141,'Marianas Setentrionais'),(142,'Marrocos'),(143,'Marshall, Ilhas'),(144,'Martinica'),(145,'Maurícia'),(146,'Mauritânia'),(147,'Mayotte'),(148,'Menores Distantes dos Estados Unidos, Ilhas'),(149,'México'),(151,'Micronésia, Estados Federados da'),(152,'Moçambique'),(153,'Moldávia'),(154,'Mónaco'),(155,'Mongólia'),(156,'Montenegro'),(157,'Montserrat'),(150,'Myanmar (antiga Birmânia)'),(158,'Namíbia'),(159,'Nauru'),(160,'Nepal'),(161,'Nicarágua'),(162,'Níger'),(163,'Nigéria'),(164,'Niue'),(165,'Norfolk, Ilha'),(166,'Noruega'),(167,'Nova Caledónia'),(168,'Nova Zelândia (Aotearoa)'),(169,'Oman'),(170,'Países Baixos (Holanda)'),(171,'Palau'),(172,'Palestina'),(173,'Panamá'),(174,'Papua-Nova Guiné'),(175,'Paquistão'),(176,'Paraguai'),(177,'Peru'),(178,'Pitcairn'),(179,'Polinésia Francesa'),(180,'Polónia'),(181,'Porto Rico'),(182,'Portugal'),(183,'Qatar'),(184,'Quénia'),(185,'Quirguistão'),(186,'Reino Unido da Grã-Bretanha e Irlanda do Norte'),(187,'Reunião'),(188,'Roménia'),(189,'Ruanda'),(190,'Rússia'),(191,'Saara Ocidental'),(194,'Saint Pierre et Miquelon'),(195,'Salomão, Ilhas'),(193,'Samoa (Samoa Ocidental)'),(192,'Samoa Americana'),(197,'San Marino'),(200,'Santa Helena'),(201,'Santa Lúcia'),(196,'São Cristóvão e Névis (Saint Kitts e Nevis)'),(198,'São Tomé e Príncipe'),(199,'São Vicente e Granadinas'),(202,'Senegal'),(203,'Serra Leoa'),(204,'Sérvia'),(205,'Seychelles'),(206,'Singapura'),(207,'Síria'),(208,'Somália'),(209,'Sri Lanka'),(210,'Suazilândia'),(211,'Sudão'),(212,'Suécia'),(213,'Suíça'),(214,'Suriname'),(215,'Svalbard e Jan Mayen'),(216,'Tailândia'),(217,'Taiwan'),(218,'Tajiquistão'),(219,'Tanzânia'),(220,'Terras Austrais e Antárticas Francesas (TAAF)'),(221,'Território Britânico do Oceano Índico'),(222,'Timor-Leste'),(223,'Togo'),(225,'Tonga'),(224,'Toquelau'),(226,'Trindade e Tobago'),(227,'Tunísia'),(228,'Turks e Caicos'),(229,'Turquemenistão'),(230,'Turquia'),(231,'Tuvalu'),(232,'Ucrânia'),(233,'Uganda'),(234,'Uruguai'),(235,'Usbequistão'),(236,'Vanuatu'),(237,'Vaticano'),(238,'Venezuela'),(239,'Vietname'),(240,'Virgens Americanas, Ilhas'),(241,'Virgens Britânicas, Ilhas'),(242,'Wallis e Futuna'),(243,'Zâmbia'),(244,'Zimbabwe');
/*!40000 ALTER TABLE `pais` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2017-11-27 21:19:50
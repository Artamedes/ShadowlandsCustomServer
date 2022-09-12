DROP TABLE IF EXISTS `custom_instance_zone`;
create table `custom_instance_zone` (
	`zone` int (10),
	`customZone` int (10),
	`radius` float ,
	`x` float ,
	`y` float ,
	`z` float ,
	`maxPlayerCount` int (10),
	`comment` varchar (750)
); 
insert into `custom_instance_zone` (`zone`, `customZone`, `radius`, `x`, `y`, `z`, `maxPlayerCount`, `comment`) values('7334','20000','80','-1766','6371','57','80','Withered J\'im - Azsuna world boss');
insert into `custom_instance_zone` (`zone`, `customZone`, `radius`, `x`, `y`, `z`, `maxPlayerCount`, `comment`) values('7334','20001','150','-1155','6115','43','80','Calarmir - Azsuna world boss');
insert into `custom_instance_zone` (`zone`, `customZone`, `radius`, `x`, `y`, `z`, `maxPlayerCount`, `comment`) values('7334','20002','100','-1159','6987','0','80','Levantus - Azsuna world boss');
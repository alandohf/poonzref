ALTER TABLE tbl_name ADD INDEX index_name  (column_list)
ALTER TABLE tbl_name ADD UNIQUE index_name  (column_list)
ALTER TABLE tbl_name ADD PRIMARY KEY index_name  (column_list) 

ALTER TABLE tbl_name DROP INDEX index_name
ALTER TABLE tbl_name DROP PRIMARY KEY 
 

SHOW INDEX FROM student; 


mysql> ALTER TABLE student 
-> ADD PRIMARY KEY(id),
-> ADD INDEX mark(english,Chinese,history);  

mysql> ALTER TABLE student DROP PRIMARY KEY,
    -> DROP INDEX mark; 
 
mysql> SHOW INDEX FROM student;
 


CREATE UNIQUE INDEX index_name ON tbl_name (column_list)
CREATE INDEX index_name ON tbl_name (column_list)


DROP INDEX index_name ON tbl_name
cREATE INDEX mark ON student(english,chinese,history);
DROP INDEX mark ON student;

CREATE TABLE tbl_name
(
…
INDEX index_name (column_list),
KEY index_name (column_list),
UNIQUE index_name (column_list),
PRIMARY KEY index_name (column_list),
…
)


CREATE TABLE tbl_name
( 
  i INT NOT NULL PRIMARY KEY
)

该语句等价于以下的语句:

CREATE TABLE tbl_name
(
  i INT NOT NULL,
  PRIMARY KEY (i)
)



在CREATE TBALE语句中可以某个串列的前缀进行索引（列值的最左边 n 个字符）。

如果对某个串列的前缀进行索引，应用 column_list 说明符表示该列的语法为 col_name(n) 而不用col_name。例如，下面第一条语句创建了一个具有两个 CHAR 列的表和一个由这两列组成的索引。第二条语句类似，但只对每个列的前缀进行索引：

CREATE TABLE tbl_name
(
name CHAR(30),
address CHAR(60),
INDEX (name,address)
)
CREATE TABLE tbl_name
(
name CHAR(30),
address CHAR(60),
INDEX (name(10),address(20))
)

你可以检查所创建表的索引：

mysql> SHOW INDEX FROM tbl_name;

+----------+------------+----------+--------------+-------------+-

| Table    | Non_unique | Key_name | Seq_in_index | Column_name |

+----------+------------+----------+--------------+-------------+-

| tbl_name |          1 | name     |            1 | name        |

| tbl_name |          1 | name     |            2 | address     |

+----------+------------+----------+--------------+-------------+-

在某些情况下，可能会发现必须对列的前缀进行索引。例如，索引行的长度有一个最大上限，因此，如果索引列的长度超过了这个上限，那么就可能需要利用前缀进行索引。在 MyISAM 表索引中，对 BLOB 或 TEXT 列也需要前缀索引。

对一个列的前缀进行索引限制了以后对该列的更改；不能在不删除该索引并使用较短前缀的情况下，将该列缩短为一个长度小于索引所用前缀的长度的列。



mysql.proc table

mysql> CREATE USER 'monty'@'localhost' IDENTIFIED BY 'some_pass';
mysql> GRANT ALL PRIVILEGES ON *.* TO 'monty'@'localhost'
    ->     WITH GRANT OPTION;
mysql> CREATE USER 'monty'@'%' IDENTIFIED BY 'some_pass';
mysql> GRANT ALL PRIVILEGES ON *.* TO 'monty'@'%'
    ->     WITH GRANT OPTION;
mysql> CREATE USER 'admin'@'localhost';
mysql> GRANT RELOAD,PROCESS ON *.* TO 'admin'@'localhost';
mysql> CREATE USER 'dummy'@'localhost';


CREATE USER 'pzw'@'localhost' IDENTIFIED BY 'mysql';
GRANT ALL PRIVILEGES ON *.* TO 'pzw'@'localhost';


SHOW GRANTS FOR 'pzw'@'localhost';


shell> mysql --user=root mysql
mysql> INSERT INTO user
    ->     VALUES('localhost','monty',PASSWORD('some_pass'),
    ->     'Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y');
mysql> INSERT INTO user
    ->     VALUES('%','monty',PASSWORD('some_pass'),
    ->     'Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y',
    ->     'Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y',
    ->     '','','','',0,0,0,0);
mysql> INSERT INTO user SET Host='localhost',User='admin',
    ->     Reload_priv='Y', Process_priv='Y';
mysql> INSERT INTO user (Host,User,Password)
    ->     VALUES('localhost','dummy','');
mysql> FLUSH PRIVILEGES;




shell> mysql --user=root mysql
mysql> CREATE USER 'custom'@'localhost' IDENTIFIED BY 'obscure';
mysql> GRANT SELECT,INSERT,UPDATE,DELETE,CREATE,DROP
    ->     ON bankaccount.*
    ->     TO 'custom'@'localhost';
mysql> CREATE USER 'custom'@'host47.example.com' IDENTIFIED BY 'obscure';
mysql> GRANT SELECT,INSERT,UPDATE,DELETE,CREATE,DROP
    ->     ON expenses.*
    ->     TO 'custom'@'host47.example.com';
mysql> CREATE USER 'custom'@'server.domain' IDENTIFIED BY 'obscure';
mysql> GRANT SELECT,INSERT,UPDATE,DELETE,CREATE,DROP
    ->     ON customer.*
    ->     TO 'custom'@'server.domain';




FLUSH PRIVILEGES;



create table test_tab
as
select name , type , param_list ,returns , body , body_utf8
from mysql.proc
where name = 'simpleproc'
;


select ROUTINE_DEFINITION , ROUTINE_TYPE  , ROUTINE_NAME   from information_schema.ROUTINES
;




mysqldump -t -d -R dbname>xx.sql




/*
* @author wudeyong
* @date 2008-12-16
*/
DELIMITER $$
DROP PROCEDURE IF EXISTS rowstocols$$
CREATE PROCEDURE `email_seperate`()
BEGIN
  -- Get the separated string.
  declare cnt int default 19;
  declare i int default 0;
   select ceil(count(email)/100000)  into @count from email;
  while i &lt; @count
  do
    set @page = i*100000+1;
    set @temp = concat("SELECT email  FROM `email`  WHERE `email` LIKE '%@%' group by email LIMIT ",@page,",100000 into outfile 'c:/test/",i,".txt'");
     prepare pre3 from @temp;
     execute pre3;
     DEALLOCATE prepare pre3;
     set @smn='';
     set i = i + 1;
  end while;
END$$
DELIMITER ;





DELIMITER //

CREATE PROCEDURE productpricing()
BEGIN
   SELECT Avg(prod_price) AS priceaverage
   FROM products;
END //

DELIMITER ;






mysql> delimiter //

mysql> CREATE PROCEDURE simpleproc (OUT param1 INT)
    -> BEGIN
    ->   SELECT COUNT(*) INTO param1 FROM t;
    -> END//
Query OK, 0 rows affected (0.00 sec)

mysql> delimiter ;

mysql> CALL simpleproc(@a);
Query OK, 0 rows affected (0.00 sec)

mysql> SELECT @a;
+------+
| @a   |
+------+
| 3    |
+------+
1 row in set (0.00 sec)






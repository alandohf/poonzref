sys@xe> ;
 select owner,object_type,OBJECT_NAME ,created from all_objects where owner = 'PZW' order by created  asc;
pzw@xe> 
drop package OS_COMMAND;

Package dropped.
pzw@xe> 
drop FUNCTION HOST_COMMAND;

Function dropped.


create or replace library shell_lib
as '/usr/lib/oracle/xe/app/oracle/product/10.2.0/server/lib/extproc.so';
/ 

create or replace function sysrun (syscomm in varchar2)
           return binary_integer
           as language C 
              name "sysrun"
              library shell_lib
              parameters(syscomm string);
           /

select sysrun('/bin/ls -alt') from dual;

select owner||'.'||table_name from all_tables where owner = 'HR'

select TABLE_OWNER, count(0) from DBA_SYNONYMS group by TABLE_OWNER order by 1;
/**
-----------------------usage : exec crsyn('syn_nam','tab_nam');---------------
i**/
create or replace procedure crsyn
(  v_syno_nam in varchar2 
 , v_table_nam in varchar2
)
AUTHID CURRENT_USER
is 
if_obj_exist number;
v_syno_name varchar2(4000) := upper(v_syno_nam);
v_table_name varchar2(4000) := upper(v_table_nam);
v_sql varchar2(4000);
begin
select count(0) into if_obj_exist from ALL_SYNONYMS where SYNONYM_NAME = v_syno_name;

if if_obj_exist > 0 then 

v_sql := 'drop public SYNONYM '||v_syno_name ;
execute immediate v_sql;
end if;
v_sql := ' create public  SYNONYM '||v_syno_name||' for '||v_table_name ;
execute immediate v_sql;
end crsyn;
/
/**
--test :  
pzw@xe> exec crsyn('T_NUMBER','pzw.T_NUMBER');

PL/SQL procedure successfully completed.

pzw@xe> !log 1

system@xe> desc T_NUMBER
 Name					   Null?    Type
 ----------------------------------------- -------- ----------------------------
 NUM1						    NUMBER(5,-2)

**/
--------------------------------------
SELECT job_id,
                sum(decode(DEPARTMENT_ID,10,SALARY)) DEPT10,
                sum(decode(DEPARTMENT_ID,20,SALARY)) DEPT20,
                sum(decode(DEPARTMENT_ID,30,SALARY)) DEPT30,
                sum(decode(DEPARTMENT_ID,40,SALARY)) DEPT40
           FROM emp
       GROUP BY job_id
;
/



lus 中使用绑定变量：
variable x number;
exec :x := 123;
SELECT fname, lname, pcode FROM cust WHERE id =:x; 

system@xe> var name varchar2(100);
system@xe> 
system@xe>  exec :name := 'PROCEDURE';

PL/SQL procedure successfully completed.

system@xe>  select count(0) from all_source where type = :name;
      3720

1 row selected.




http://www.dba-oracle.com/concepts/views.htm

oracle 一般用户没有建视图的权限！

grant create view , drop view to pzw;

system@xe> grant create view to pzw;

Grant succeeded.

system@xe> grant drop view to pzw;
grant drop view to pzw
      *

 CREATE VIEW view_emp
 AS
 SELECT EMPLOYEE_ID empid FROM emp

This command creates a new view called VIEW_EMP. Note that this command does not result in anything being actually stored in the database at all except for a data dictionary entry that defines this view. This means that every time you query this view, Oracle has to go out and execute the view and query the database data. We can query the view like this:

SELECT * FROM view_emp WHERE empid BETWEEN 500 AND 1000;

And Oracle will transform the query into this:

SELECT * FROM (select empid from emp) WHERE empid BETWEEN 500 AND 1000;


http://www.psoug.org/reference/
http://tahiti.oracle.com/
http://www.oracle.com/technology/documentation/index.html
http://www.oracle-base.com/
http://download-west.oracle.com/docs/cd/B10501_01/nav/docindex.htm
http://download-west.oracle.com/docs/cd/B10501_01/index.htm
http://www.oracle.com/pls/db112/portal.all_books
http://www.oaktable.net/
http://infocenter.sybase.com/help/index.jsp

软件体系架构要以业务为核心，业务以数据库为中心，如oracle，可以充分利用数据库的特性，帮助解决复杂的问题。一个常用的规则是：
如果能用单条sql解决，ok
如果不能用单条sql解决，考虑使用PL/SQL
如果不能用PL/SQL解决，考虑使用java存储过程
如果不能用java解决，那么考虑使用c外部过程
如果c都解决不了，那么考虑一下放弃吧

fast parse,soft parse,hard parse的区别
http://hi.baidu.com/edeed/blog/item/5c99e711011d3cc3a6ef3f58.html
有流程图.

http://www.itpub.net/thread-187610-1-1.html

2 一般变量绑定常的动态游标中使用， 那么一般的游标定义
  cursor c1 is select a1,a2,a3 from table1 where ...
   和 declare
     type c1 is ref cursor ;
      begin
     open c1 for 'select a1,a2,a3 from table1 where ..';
     ...
     end;
    这两种有什么区别？

pzw@xe> select * from USER_VIEWS where VIEW_NAME = 'VIEW_EMP';


/* Create a database link from the local XE database
to the remote XE database HR account */
   create database link remote_db
     connect to hr
     identified by hr
     using 'remote_xe';


Imperva  - Protecting the Data that Drives Business

view 可以隐藏表和字段 ， 但view本身呢，其定义呢？

* Predicate pushing. 


 Hence, it is important to make sure you use bind variables instead of literals in SQL code calling views. Thus, our SQL should look something like this instead for best performance:
SELECT * FROM vw_layer_two_dept_100
WHERE empid=:b100;





& |  && 

pzw@xe> select &num1 from dual;
Enter value for num1: 1
old   1: select &num1 from dual
new   1: select 1 from dual
	 1

pzw@xe> /
Enter value for num1: 2
old   1: select &num1 from dual
new   1: select 2 from dual
	 2


pzw@xe> select &&num2 from dual;
Enter value for num2: 111
old   1: select &&num2 from dual
new   1: select 111 from dual
       111

1 row selected.

pzw@xe> /
old   1: select &&num2 from dual
new   1: select 111 from dual
       111

1 row selected.

pzw@xe> define
DEFINE _DATE	       = "23-JUN-10" (CHAR)
DEFINE _CONNECT_IDENTIFIER = "XE" (CHAR)
DEFINE _USER	       = "PZW" (CHAR)
DEFINE _PRIVILEGE      = "" (CHAR)
DEFINE _SQLPLUS_RELEASE = "1002000100" (CHAR)
DEFINE _EDITOR	       = "vi" (CHAR)
DEFINE _O_VERSION      = "Oracle Database 10g Express Edition Release 10.2.0.1.0 - Production" (CHAR)
DEFINE _O_RELEASE      = "1002000100" (CHAR)
DEFINE Y	       = "pzw@xe" (CHAR)
DEFINE NUM	       = "3333" (CHAR)
DEFINE NUM2	       = "111" (CHAR)

----------------------------------------
lvl1/
lvl1/b.sql
lvl1/a.sql

[/home/pzw ]cat lvl1/a.sql
@@b.sql

[/home/pzw ]cat lvl1/b.sql
select 11112122 from dual;


pzw@xe> @lvl1/a
  11112122
------------------------------------------

/etc/oratab



[/home/pzw ]cat  $ORACLE_HOME/config/scripts/startdb.sql
connect / as sysdba
startup
exit




ALTER SESSION 
   SET NLS_DATE_FORMAT = 'YYYY MM DD HH24:MI:SS';


Oracle Database uses the new default date format:

SELECT TO_CHAR(SYSDATE) Today
   FROM DUAL; 

TODAY 
------------------- 
2001 04 12 12:30:38


declare
v_isnull integer := 0 ;
v_field varchar2(30)  ;
cursor c1 is
select CNAME from col
where  tname = upper('r_date')  order by 1; 
cursor c2 is select * from r_date ; 

begin
for crec in c2
loop
for c_rec in c1
loop
--dbms_output.put_line(c_rec.cname);
v_field := c_rec.cname;
if crec.v_field is null then 
 v_isnull  := v_isnull + 1;
end if;
end loop;
dbms_output.put_line(v_isnull);
end loop;

end;
/




 
drop table t_candidates_sum purge;
create table t_candidates_sum
(
code	number
,school	varchar2(128)
,plans	number
,candidates number
,limits	   number
);

drop table t_prikey purge;
create table t_prikey
(
rn	number
,constraint pk_rn primary key(rn)
);

 
insert into t_prikey
select 1 from dual;

insert into t_prikey
select 2 from dual;

insert into t_prikey
select 2 from dual;


ERROR at line 1:
ORA-00001: unique constraint (PZW.PK_RN) violated


t_num_pid

select a.*
,row_number()over( partition by substr(a||b||c||d||e||f ,1,length(a||b||c||d||e||f)-2) order by sid ) pid
from t_num_pid a 
order by sid
;



select a.*
,sid - row_number()over( partition by substr(a||b||c||d||e||f ,1,length(a||b||c||d||e||f)-2) order by sid ) pid
from t_num_pid a
order by sid
;

   

select a.*
,sid - row_number()over( partition by substr(a||b||c||d||e||f ,1,length(a||b||c||d||e||f)-2) order by sid ) pid
,case when length(a||b||c||d||e||f)-2 = 0 then null 
	else sid - row_number()over( partition by substr(a||b||c||d||e||f ,1,length(a||b||c||d||e||f)-2) order by sid ) 
	end pid
from t_num_pid a
order by sid
;


select a.a,a.b,a.c,a.d,a.e,a.f,a.sid
--,sid - row_number()over( partition by substr(a||b||c||d||e||f ,1,length(a||b||c||d||e||f)-2) order by sid ) pid
,case when length(a||b||c||d||e||f)-2 = 0 then null 
        else sid - row_number()over( partition by substr(a||b||c||d||e||f ,1,length(a||b||c||d||e||f)-2) order by sid ) 
        end pid
from t_num_pid a
order by sid
;


alter table t_num_pid add ( comments varchar2(32) );
alter table t_num_pid drop ( comments  );

Table altered.



shutdown immediate;  
startup mount;  
alter system  enable restricted session;  
alter system set JOB_QUEUE_PROCESSES=0;  
alter system set AQ_TM_PROCESSES=0;  
alter database open;  
alter database character set internal_use GB2312;  
shutdown immediate;  
startup;  




shutdown immediate;
startup mount;
alter system enable restricted session ;
alter database open ;
alter database character set internal_use ZHS16GBK ;
shutdown immediate;
startup ;



ALTER TABLE chicken ADD CONSTRAINT chickenREFegg
    FOREIGN KEY (eID) REFERENCES egg(eID)
    INITIALLY DEFERRED DEFERRABLE;
ALTER TABLE egg ADD CONSTRAINT eggREFchicken
    FOREIGN KEY (cID) REFERENCES chicken(cID)
    INITIALLY DEFERRED DEFERRABLE;


ALTER TABLE egg DROP CONSTRAINT eggREFchicken;
ALTER TABLE chicken DROP CONSTRAINT chickenREFegg;
DROP TABLE egg;
DROP TABLE chicken;


show errors trigger <trigger_name>;

select trigger_name from user_triggers;

For more details on a particular trigger:

select trigger_type, triggering_event, table_name, referencing_names, trigger_body
from user_triggers
where trigger_name = '<trigger_name>';

alter trigger <trigger_name> {disable|enable}; 


create or replace trigger <TRIGGER_NAME>
  before insert or update
on <table_name>
  for each row
declare
  <VARIABLE DECLARATIONS>
begin
    <CODE>
exception
    <EXCEPTION HANDLERS>
end <TRIGGER_NAME>;
/



SELECT dbtimezone FROM dual;

ALTER database SET TIME_ZONE = '-05:00';

SELECT entry, to_char(entry_date, 'MM/DD/YY HH:MI AM') FROM dates WHERE entry=5;
This database is in US Eastern time but we want to display the time in US Central.

SELECT entry, to_char(new_time(entry_date, 'EST', 'CST'), 'MM/DD/YY HH:MI AM') FROM dates WHERE entry=5;

SELECT entry, to_char(new_time(entry_date, 'EST', 'PST'), 'MM/DD/YY HH:MI AM') FROM dates WHERE entry=5;

SELECT to_char(new_time(sysdate, 'EST', 'PST'), 'MM/DD/YY HH:MI AM') FROM dual ;

ALTER session SET TIME_ZONE = '+08:00';

alter session set time_zone='+04:00';

select dbtimezone,sessiontimezone from dual;


select CURRENT_TIMESTAMP from dual;


 select SYSTIMESTAMP from dual;

--
pzw>  exec execute immediate ' select 1 from dual ';

PL/SQL procedure successfully completed.

--

 exec execute immediate ' create table t_exec as select 1 a from dual ';

create or replace procedure selectx
(  v_field_nam in varchar2
)
is 
begin
 execute immediate 'select '''|| v_field_nam ||''' from dual ';
end selectx;
/

pzw> ;
  1* select &a from r_date where rownum<10
pzw> /
Enter value for a: dt
old   1: select &a from r_date where rownum<10
new   1: select dt from r_date where rownum<10
20791227
20791226
20791225
20791224
20791223
20791222
20791221
20791220
20791219

9 rows selected.

drop table t_mytable purge;
create table t_mytable
(
 c1	number
,c2	number
);

insert into t_mytable 
select 1 , 2 from dual;
commit;

insert into t_mytable 
select 3 , 4 from dual;
commit;

pzw> select c&num from t_mytable;
Enter value for num: 1
old   1: select c&num from t_mytable
new   1: select c1 from t_mytable
	 1
	 3

2 rows selected.

pzw> select c&num from t_mytable;
Enter value for num: 2
old   1: select c&num from t_mytable
new   1: select c2 from t_mytable
	 2
	 4

2 rows selected.



表一 表名:期初
数量    单价    金额
 10      20      200


日期   入库数量 入库单价 入库金额 出库数量 出库单价 出库金额 结存数量 结存单价 结存金额 
                                                                10       20       200
2010-1-1  20        18      360                                  30      18.67     560
2010-1-2                             5        18.67     93.33     25      18.67   466.67
2010-1-5  30        17      510                                  55      17.76   976.67
2010-1-8                             5         17.76     88.79    50      17.76   887.88
2010-1-20  10       21      210                                  60      18.30   1097.88
2010-1-20                            20         18.30    365.96   40      18.30   731.92



select IIf(IsNull(a.日期),b.日期) 日期
,sum(a.数量) 入库数量
,sum(a.单价) 入库单价
,sum(a.金额) 入库金额
--
,sum(b.数量) 出库数量
,结存单价     出库单价
,sum(b.数量)*结存单价  出库金额
--
,sum(IIf(IsNull(c.数量),0)  + IIf(IsNull(a.数量),0) - IIf(IsNull(b.数量),0) ) 结存数量 
,结存金额/结存数量 结存单价 
,sum(IIf(IsNull(c.数量),0)*c.单价  + IIf(IsNull(a.数量),0)*IIf(IsNull(a.单价),0) - IIf(IsNull(b.数量),0)*IIf(IsNull(b.单价),0) ) 结存金额

from 入库 a
full join 出库 b on a.日期 = b.日期
full join 期初 c on a.日期 = c.数量
;




Declare
      Exception_a  exception;
      Exception_b  exception;
   Begin
       Begin
           Raise  exception_a;
       Exception 
          When exception_b then
              Dbms_output.put_line('this is b');
          When exception_a then
             Raise exception_b;
           Dbms_output.put_line('this is a');
        End;
     Exception
       When others then
       Dbms_output.put_line('this is another a');
End; 







--
drop table students4 purge;
drop type stu4;
create   type stu4 as object
(
 name varchar2(20),
 sex varchar2(2),
 birthday date,
 note varchar2(300),
 member function get_age return number)
;
/
类型已创建。

 create type body stu4 as
 member function get_age return number 
 is 
 v_months number;
 begin
 select floor(months_between(sysdate,birthday)/12) into v_months
 from dual;
 return v_months;
 end;
 end;
 /

主体已创建。

create table students4(
sid number(4)
,student stu4);

表已创建。

insert into students4 values
(1
,stu4('王晓雪'
	,'女'
	,sysdate
	,'my note')
);
commit;

insert into students4 
select 1 , stu4('a','b',sysdate,'c') from dual;

commit;

已创建 1 行。

 select s.student.name,s.student.birthday,s.student.get_age()from students4 s; 



 select 
 students4.student.name
,students4.student.birthday
,students4.student.get_age()
from students4 ; 
 


1	a	1
2	b	2
3	c	3
4	d	4


1	b	a	1
2	c	b	2
3	d	c	3

select datediff(dd,a.addtime,b.addtime)
from 
(select row_number() over (order by addtime) as id,addtime from 某表 where addtime<>(select max(addtime) from 某表)
) a,
(select row_number() over (order by addtime) as id,addtime from 某表 where addtime<>(select min(addtime) from 某表)
) b
where a.id=b.id 

http://zhidao.baidu.com/question/166997973.html?fr=uc_ma_push&fl=red


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




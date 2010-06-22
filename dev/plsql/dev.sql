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





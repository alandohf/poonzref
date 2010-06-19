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


drop procedure pdict;
CREATE OR REPLACE procedure pdict(v_table_name in varchar2 )
IS
v_comments varchar2(4000);
cursor c1 is
select table_name,comments
from dictionary
where  table_name like  '%'||upper(v_table_name)||'%' order by 1;
BEGIN
for c_rec in c1
loop
dbms_output.put_line(trim(c_rec.table_name)||' | '||c_rec.comments);
end loop;
END pdict;
/

exec  pdict('DBA_ROLE');


--authid current 
drop procedure ftab;
CREATE OR REPLACE procedure ftab(v_table_name in varchar2 )
authid current_user
IS
cursor c1 is
select table_name
from user_tables
where  table_name like  '%'||upper(v_table_name)||'%' order by 1;
BEGIN
for c_rec in c1
loop
dbms_output.put_line(trim(c_rec.table_name));
end loop;
END ftab;
/

exec  ftab('DBA_ROLE');
drop procedure ftab;
CREATE OR REPLACE procedure ftab(v_table_name in varchar2 )
authid current_user
IS
cursor c1 is
select table_name
from user_tables
where  table_name like  '%'||upper(v_table_name)||'%' order by 1;
BEGIN
for c_rec in c1
loop
dbms_output.put_line(trim(c_rec.table_name));
end loop;
END ftab;
/




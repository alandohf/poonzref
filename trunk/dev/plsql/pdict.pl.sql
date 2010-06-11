CREATE OR REPLACE procedure pdict(v_table_name in varchar2 )
IS
v_comments varchar2(4000);
cursor c1 is
select table_name,comments
from dictionary
where  table_name like  '%'||upper(v_table_name)||'%';
BEGIN
for c_rec in c1
loop
dbms_output.put_line(trim(c_rec.table_name)||' | '||c_rec.comments);
end loop;
END pdict;
/

exec  pdict('DBA_ROLE');


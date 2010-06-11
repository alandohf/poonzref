CREATE OR REPLACE FUNCTION dict(v_table_name in varchar2 )
RETURN varchar2 
IS
v_comments varchar2(4000);
BEGIN
select comments into v_comments from dictionary where table_name like  '%'||upper(v_table_name)||'%';
return v_comments;
END dict;
/


select dict('DBA_ROLEs') FROM DUAL;	



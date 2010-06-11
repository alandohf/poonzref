CREATE OR REPLACE FUNCTION mega(v_bytes in number )
RETURN number
IS
BEGIN
return v_bytes/1024/1024;
END mega;
/

CREATE OR REPLACE FUNCTION giga(v_bytes in number )
RETURN number
IS
BEGIN
return v_bytes/1024/1024/1024;
END giga;
/



select mega(1024*2*1024) FROM DUAL;
select giga(1024*2*1024) FROM DUAL;
select a.*,mega(bytes) mb,giga(bytes) gb from USER_FREE_SPACE a where rownum < 10 ;




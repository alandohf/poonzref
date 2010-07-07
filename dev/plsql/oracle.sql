http://blog.csdn.net/summerycool/archive/2009/12/31/5112362.aspx
select count(*)
from dba_indexes
where tablespace_name = 'SYSTEM'
and owner not in ('SYS','SYSTEM')
;


select segment_name, count(*)
from dba_extents
where segment_type='INDEX'
and owner=UPPER('&owner')
group by segment_name

analyze table all_tables compute statistics
              *
ERROR at line 1:
ORA-01702: a view is not appropriate here


  1* analyze table hr.employees compute statistics

Table analyzed.


----auto increment

create table my_test (
id number
,my_test_data varchar2(255)
);


create sequence test_seq
start with 1
increment by 1
nomaxvalue; 

create trigger test_trigger
before insert on my_test
for each row
begin
select test_seq.nextval into :new.id from dual;
end;
/


 insert into my_test values(test_seq.nextval, 'voila!');
commit;

drop table my_test purge;
drop sequence test_seq ;
drop trigger test_trigger;

----auto increment  end 



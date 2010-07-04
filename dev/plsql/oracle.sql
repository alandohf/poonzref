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




select owner,sys_connect_by_path(table_name,' ') path
from 
(select owner,table_name ,rownum child,(rownum-1) parent from all_tables where owner='PZW') t
start with parent = 0 
connect by prior child = parent
;



select owner,max(path) path
from (
select owner,sys_connect_by_path(table_name,' ') path
from 
(select owner,table_name ,rownum child,(rownum-1) parent from all_tables where owner='PZW') t
start with parent = 0 
connect by prior child = parent
) o 
group by owner ;


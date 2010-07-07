spool_out(){
    sqlplus -s ${UnP}  <<_eof
	set pagesize 0 linesize 200 feedback off colsep ","
	spool output.txt
	select * from col where COLNO between $1 and $2;
	spool off
_eof
}

awk -v v_no=$1 'BEGIN{FS=",";OFS=","}{if $1 = v_no ) {print $0}  }' >>

1.SQl语句中没有循环的语句。
正确。但pl/sql有。

2.这是shell 和 sqlplus 交互的问题。有多种实现。
途径：
1）可以在shell中处理sql,
2）也可以在plsql中处理调用shell.

1）只需写shell脚本即可。
2）需要配extproc，虽然有效，比较麻烦。不建议。


3.如果让sqlplus 在shell循环，要重复连接很多次，不建议。建议先将所有学号的学生先一次性导出，再每条单独输出处理。


4.我可以给你写个参考参考，但是不知合不合你用，我的是bash :



create table s( sno int, a int);

insert into s values(1,4);
insert into s values(2,5);

create table t( tno int, b int);

insert into t values(1,0);
insert into t values(2,0);

create or replace procedure m
is 
   cursor testSor is select tno,b from t;
   v testsor%rowtype;
BEGIN 
   open testSor;
   Loop
   exit when testsor%notfound;
   fetch testSor into v;
    update t
    set b = v.b;
   end loop;
close testSor;
end m;    
/
             
create or replace trigger p
before update of a on s
for each row
begin
    m;
dbms_output.put_line('procedure m called');
end p;
/          

drop table s purge;
drop table t purge;
drop procedure m ;
drop trigger  p;

 update s set a = 3 where a = 4;


  1*  update s set a = 4 where a = 3
pzw> /
procedure m called

1 row updated.


update s set a = 3 where a = 4;
update t set b  = 3 where b = 0;
http://zhidao.baidu.com/question/164889690.html?push=keyword



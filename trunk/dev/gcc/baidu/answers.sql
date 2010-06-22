--http://zhidao.baidu.com/question/161000319.html?push=category
-- 计算平均价格 
select type
	,avg(priceadvance) avg_price
from titles
group by type


--计算各类数量
select type
        ,count(id) cnt 
from titles
group by type

--平均价格最高
select max(avg_price) max_avg_price 
from (
	select type
        	,avg(priceadvance) avg_price
	from titles
	group by type
) t 


--输出
select 
a.type 
||'类型图书包括'
||b.cnt 
||'本图书，平均价格为'
||a.avg_price
||'，最高！'
from 
(
select type
        ,avg(priceadvance) avg_price
from titles
group by type
) a 
join 
(
	select type
        ,count(id) cnt
	from titles
	group by type
) b on a.type = b.type 
where a.avg_price 
= ( 	select max(avg_price) max_avg_price
	from (
        	select type
                ,avg(priceadvance) avg_price
        	from titles
        	group by type
  ) 
;



BEGIN
declare 
level char(1) := &AA;
v_lvl_nam char(100);
if (level == 'A')  then v_lvl_nam := 'A(90~100)';
  elsif (level == 'B')  then v_lvl_nam := 'B(80~89)';
  else        v_lvl_nam := 'C';
end case;
END;
/


set serverout on
create  or replace procedure qrylvl
is
v_lvl char(1) ;
v_lvl_nam char(100);
begin
v_lvl := '&IA';
    IF v_lvl = 'A' THEN
         v_lvl_nam := 'The owner is SYS';
    ELSIF v_lvl = 'B' THEN
        v_lvl_nam := 'The owner is SYSTEM';
    ELSE
        v_lvl_nam := 'The owner is another value';
    END IF;
dbms_output.put_line(v_lvl_nam);
end qrylvl;
/




set serverout on
declare 
owner varchar2(10) ;
result varchar2(1000);

begin
owner := '&tt';
    IF owner = 'SYS' THEN
         result := 'The owner is SYS';

    ELSIF owner = 'SYSTEM' THEN
        result := 'The owner is SYSTEM';

    ELSE
        result := 'The owner is another value';

    END IF;
dbms_output.put_line(result);
end ;
/
--用 SQL PLUS语言编程：输入一个成绩等级（A~E），显示相应的百分制成绩段A(90~100)B(80~89)C(70~79)D(60~69)E(<60)
set serverout on
declare 
v_lvl char(1) ;
v_lvl_nam char(100);
begin
v_lvl := '&i_lvl';
    IF v_lvl = 'A' THEN
         v_lvl_nam := 'A(90~100)';
    ELSIF v_lvl = 'B' THEN
        v_lvl_nam := 'B(80~89)';
    ELSIF v_lvl = 'C' THEN
        v_lvl_nam := 'C(70~79)';
    ELSIF v_lvl = 'D' THEN
        v_lvl_nam := 'D(60~69)';
    ELSIF v_lvl = 'E' THEN
        v_lvl_nam := 'E(<60)';
    END IF;
dbms_output.put_line(v_lvl_nam);
end ;
/



/**
http://zhidao.baidu.com/question/161013440.html#here
--用 SQL PLUS语言编程：输入一个成绩等级（A~E），显示相应的百分制成绩段
A(90~100)
B(80~89)
C(70~79)
D(60~69)
E(<60)
**/
--通过&读入A，B，C，D，E
--程序开始
set define &
set serverout on
declare 
v_lvl char(1) ;
v_lvl_nam char(100);
begin
v_lvl := upper('&i_lvl');
    IF v_lvl = 'A' THEN
         v_lvl_nam := 'A(90~100)';
    ELSIF v_lvl = 'B' THEN
        v_lvl_nam := 'B(80~89)';
    ELSIF v_lvl = 'C' THEN
        v_lvl_nam := 'C(70~79)';
    ELSIF v_lvl = 'D' THEN 
        v_lvl_nam := 'D(60~69)';
    ELSIF v_lvl = 'E' THEN
        v_lvl_nam := 'E(<60)';
    ELSE 
        v_lvl_nam := 'invaild input!please input from a to e';
    END IF;
dbms_output.put_line(v_lvl_nam);
end ;
/ 

--程序结束

--每次按  '/' 执行，为i_lvl指定 A，B，C，D... 



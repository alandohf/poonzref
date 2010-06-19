--usage:grant execute on package/function/procedure to user；
exec pdict('DBA_'); --fail
--exec sys.pdict('DBA_');
--revoke execute on pdict from pzw;
grant execute on pzw.pdict to pzw;
drop public synonym pdict;
create public synonym pdict for pzw.pdict;
exec pdict('DBA_');
--pub_emp属于public用户，数据库所有用户都可以访问。
drop public synonym r_date;
create public synonym r_date for pzw.r_date;

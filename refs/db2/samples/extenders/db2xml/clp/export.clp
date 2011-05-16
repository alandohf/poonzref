--
-- Testing dxxContent_varchar2file() UDF function
--

connect to mydb;

create table app1 (id int NOT NULL, order db2xml.XMLVarchar);

insert into app1 values (1, '<?xml version="1.0"?><!--DOCTYPE Order SYSTEM "Order.dtd"--><Order key="1"><Customer> 37 </Customer><Status> O </Status><TotalPrice> 131251.81 </TotalPrice><Date> 1996-01-02 </Date><Priority> 5-LOW </Priority><Clerk> Clerk#000000951 </Clerk><ShipPriority> 0 </ShipPriority><Comment> A0xCm5ARNL mxjChn2kC64xA4L6zBg2O5jhg M42izyPO  QlymN1ky5kmSiSgBAQA </Comment></Order>');

select db2xml.Content(order, '/tmp/contenttest.xml') from app1 where ID =1;

drop table app1;

terminate;


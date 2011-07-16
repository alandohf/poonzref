
/**
var enmProfile = new Enumerator(GetObject("winmgmts:").InstancesOf("Win32_NetworkLoginProfile")); 
var arr = new Array("用户名\t最后登录时间"); 
while(!enmProfile.atEnd()) 
{ 
arr.push(enmProfile.item().Name + "\t" + enmProfile.item().LastLogon); 
enmProfile.moveNext(); 
} 
WSH.Echo(arr.join("\r\n"));
**/

/**
aBird = "Robin"; // Assign the text "Robin" to the variable aBird
WSH.Echo(aBird);
var today = new Date(); // Assign today's date to the variable today
WSH.Echo(today);
**/

function TimeDemo(){
   var d, s = "";
   var c = ":";
   d = new Date();
   s += d.getHours() + c;
   s += d.getMinutes() ;
   //s += d.getSeconds() + c;
   //s += d.getMilliseconds();
   return(s);
}
//WSH.Echo(TimeDemo());


while(true){
if ( TimeDemo() == '11:14' ){
WSH.Echo(TimeDemo());
break;
}
}
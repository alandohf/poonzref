##
if [ $(id -u) != "0" ]
then
    echo "You must be root to run the configure script.  Login as root and then run the 
configure script."
    exit 1
fi


##
    init_status()
    {
        return 0
    }
    exit_status()
    {
        exit $?
    }


##
    success_status()
    {
        echo "OK"
        return 0
    }
    failure_status()
    {
        echo "Failed"
        return 1
    }
    exit_status()
    {
        exit $?
    }



[/etc/default ]cat oracle-xe



##

if_fail()
{
    RC="$1"
    REASON="$2"
    if [ "$RC" = "0" ]
    then
        return
    elif [ "$RC" = "2" ]
    then
        return
    fi
    failure_status "${REASON}"
    exit 1
}


##return code check chk


    if [ $? != 0 ]
        then
                return 1
        fi
        return 0


write_sysconfig()
{
        cat >"$CONFIGURATION" <<EOF
    
# Configuration : Check whether configure has been done or not
CONFIGURE_RUN=${CONFIGURE_RUN}

EOF

    if [ $? != 0 ]
        then
                return 1
        fi
        return 0
}

    /bin/chown oracle:dba $ORACLE_HOME/config/scripts/postDBCreation.sql


[/etc/default ]a=1
[/etc/default ]test $a -ne 1
[/etc/default ]echo $?
1
[/etc/default ]test $a -eq 1
[/etc/default ]echo $?
0

        if test -f /tmp/local_listener
        then
                rm -fr /tmp/local_listener
        elif test -f /tmp/local_listener$$
        then
                rm -fr /tmp/local_listener$$
        fi



#!/bin/sh
for i in firefox mozilla konqueror ; do
        if test -x "/usr/bin/$i"; then
                /usr/bin/$i http://127.0.0.1:8080/apex
                exit $?
        fi
done


        $SU -s /bin/bash $ORACLE_OWNER -c "$LSNR  start" > /dev/null 2>&1

       -c, --command COMMAND
           Specify a command that will be invoked by the shell using its -c.

       -s, --shell SHELL
           The shell that will be invoked.

    err=`grep "ORA-44410" $ORACLE_HOME/config/log/*.log`


    echo  alter user sys identified by \"$ORACLE_PASSWORD\"\; \
| $SU -s /bin/bash $ORACLE_OWNER -c "$SQLPLUS -s / as sysdba" > /dev/null 2>&1


[/home/pzw ]echo select 1 from dual\;|sqlplus -s pzw/oracle
	 1

1 row selected.



   echo -n "Starting Oracle Database 10g Express Edition Instance..."
   pmon=`ps -ef | egrep pmon_$ORACLE_SID'\>' | grep -v grep`

   if [ "$pmon" = "" ];
   then
           $SU -s /bin/bash  $ORACLE_OWNER -c "$SQLPLUS -s /nolog @$ORACLE_HOME/config/scripts/startdb.sql" > /dev/null 2>&1
   fi
   echo "Done"

   echo "Installation Completed Successfully."



[/home/pzw ]read var
999
[/home/pzw ]echo $var
999



var 相当于 & / &&



            case "$LINE" in
            "")
            break
            ;;
        *[^0-9]*)
            echo "Invalid http port: $LINE"
            ;;
        *)
            HTTP_PORT=$LINE
            break
            ;;
            esac

## using regular expression in test condition

echo $a | grep "^p"
if [[ $? -eq 0 ]] ; then



 a=package1
 case $a in p* ) echo "true" ;; * ) echo "no" ;;esac
true

??
> Is there any possibility to redirect STDERR to a command like 'xless'
> without redirecting  STDOUT as well?

The trick is to use a spare FD to swap the first two.

mycmd 3>&1 1>&2 2>&3 3>&- | xless
??


http://ubuntuforums.org/showthread.php?t=820403
 Customizing bash's Internal Field Separator (IFS)
I'm running into some weirdness trying to explicitly set the special variable in bash, the Internal Field Separator to be a space, a new line and a tab. This is in GNU bash, version 3.2.39(1)-release (x86_64-pc-linux-gnu)

I would like to be able to explicitly set the Internal Field Separator to be a space, a new line and a tab. I would expect the backslash sequences to be interpreted, but they seem not to be. Despite many HOWTOs, Tutorials, and guides only setup 'one' below successfully assigns all three.

# one
export IFS=`/bin/echo -ne " \t\n"`
echo "$IFS" | cat -vte

These others below fail, usually by making the letters 't' and 'n' into field separators. That is not the behavior I expect, I would expect the backslash sequences to be interpreted properly:

# two
export IFS=" \t\n"
echo "$IFS" | cat -vte

# three
export IFS=$" \t\n"
echo "$IFS" | cat -vte

# four
export IFS=$' \t\n'
echo "$IFS" | cat -vte

Here is the problem in a different form:

$ FOO=$'a\n a';echo $FOO
a a
$ FOO=$"a\n a";echo $FOO
a\n a
$ FOO="a\n a";echo $FOO
a\n a
$ FOO='a\n a';echo $FOO
a\n a
Last edited by Lars Noodén; June 6th, 2008 at 07:42 AM..
Lars Noodén is offline   	Reply With Quote
Lars Noodén
View Public Profile
Visit Lars Noodén's homepage!
Find More Posts by Lars Noodén
Old June 6th, 2008 	  #2
geirha
Ubuntu addict and loving it
 
Join Date: Feb 2007
Beans: 3,800
Ubuntu 9.10 Karmic Koala
	
Re: Customizing bash's Internal Field Separator (IFS)
Seems to be working for me.
Code:

$ IFS=$' \t\n' FOO=$'a b\tc\nd-e'; echo $FOO
a b c d-e
$ IFS=' ' FOO=$'a b\tc\nd-e'; echo $FOO
a b	c
d-e
$ IFS=$'\t' FOO=$'a b\tc\nd-e'; echo $FOO
a b c
d-e
$ IFS=b FOO=$'a b\tc\nd-e'; echo $FOO
a  	c
d-e

geirha is offline   	Reply With Quote
geirha
View Public Profile
Send a private message to geirha
Find More Posts by geirha
Old June 6th, 2008 	  #3
colo
Way Too Much Ubuntu
 
Join Date: Apr 2005
Location: Austria
Beans: 246
Kubuntu
	
Re: Customizing bash's Internal Field Separator (IFS)
Also note that bash's default IFS already consists of " \t\n".
__________________
johannes.truschnigg.info - meine Website.
colo is offline   	Reply With Quote
colo
View Public Profile
Send a private message to colo
Visit colo's homepage!
Find More Posts by colo
Old June 6th, 2008 	  #4
Lars Noodén
Dark Roasted Ubuntu
 
Lars Noodén's Avatar
 
Join Date: Sep 2006
Beans: 1,104
Kubuntu 9.10 Karmic Koala
	
which version and platform?
@geirha: on which platform and for which version of bash is it working for you?

I am finding that it does not work on

GNU bash, version 3.2.39(1)-release (x86_64-pc-linux-gnu)

2.6.24-18-generic #1 SMP Wed May 28 19:28:38 UTC 2008 x86_64 GNU/Linux

$ lsb_release -rcd
Description: Ubuntu 8.04
Release: 8.04
Codename: hardy



[/home/pzw ]expr index 4321 1
4



        case "$LINE" in
        "")
            break
            ;;
        y|Y)
            ORACLE_DBENABLED=true
            break
            ;;
        n|N)
            ORACLE_DBENABLED=false
            break
            ;;
        *)
            echo "Invalid response: $LINE " >&2
            break
        esac



[/home/pzw ]/etc/init.d/oracle-xe configure
You must be root to run the configure script.  Login as root and then run the 
configure script.
[/home/pzw ]/etc/init.d/oracle-xe  stop
You must be root to run the configure script.  Login as root and then run the 
configure script.




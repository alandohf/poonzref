#!/usr/bin/perl
########################################################################
# Licensed Materials - Property of IBM
#
# Governed under the terms of the International
# License Agreement for Non-Warranted Sample Code.
#
# (C) COPYRIGHT International Business Machines Corp. 1996 - 2003
# All Rights Reserved.
#
# US Government Users Restricted Rights - Use, duplication or
# disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#########################################################################
#
# SOURCE FILE NAME: dbuse.pl
#
# SAMPLE: How to use a database 
#
# SQL STATEMENTS USED:
#         CREATE TABLE
#         DROP TABLE
#         DELETE
#
# OUTPUT FILE: dbuse.out (available in the online documentation)
##########################################################################
#
# For more information on the sample programs, see the README file.
#
# For information on developing Perl applications, see the Application
# Development Guide.
#
# For information on using SQL statements, see the SQL Reference.
#
# For the latest information on programming, building, and running DB2
# applications, visit the DB2 application development website:
#     http://www.software.ibm.com/data/db2/udb/ad
##########################################################################/

select STDERR; $|=1;
select STDOUT; $|=1;

use strict;
use warnings; 
use DBI;

# access the module for DB2 Sample Utility functions
use DB2SampUtil;

# check and parse the command line arguments
# call the subroutine CmdLineArgChk from DB2SampUtil.pm
my ($database, $user, $password) = CmdLineArgChk(@ARGV);

# declare return code, statement handler, database handler and local variable
my ($rc, $sth, $dbh, $i);

print "THIS SAMPLE SHOWS HOW TO USE A DATABASE.\n";

# connect to the database
print "\n  Connecting to database...\n";
$dbh = DBI->connect($database, $user, $password, {AutoCommit => 0})
            || die "Can't connect to $database: $DBI::errstr";
print "\n  Connected to database.\n";

# call the subroutine StaticStmtInvoke 
$rc = StaticStmtInvoke();
if ($rc != 0)
{
  print "\nStatic statement execution failed\n";
}

# call the subroutine StaticStmtWithHostVarsInvoke 
$rc = StaticStmtWithHostVarsInvoke();
if ($rc != 0)
{
  print "\nExecuting sql with host variables failed\n";
}

# call the subroutine StmtEXECUTE 
$rc = StmtEXECUTE();
if ($rc != 0)
{
  print "\nExecuting sql with 'do' interface failed\n";
}

# disconnect from the database
print "\n  Disconnecting from database.\n";
$dbh->disconnect
  || die $DBI::errstr;
print "  Disconnected from database.\n";


#######################################################################
# Description : How to use static SQL statements
# Input       : None 
# Output      : Returns 0 on success, exits otherwise
#######################################################################
sub StaticStmtInvoke
{
  print "\n-----------------------------------------------------------";
  print "\nUSE THE SQL STATEMENTS:\n";
  print "  CREATE TABLE\n";
  print "  DROP TABLE\n";
  print "TO SHOW HOW TO USE STATIC SQL STATEMENTS.\n";

  # create a table
  print "\n  Execute the statement\n";
  print "    CREATE TABLE table1(col1 INTEGER)\n";

  my $sql = qq(CREATE TABLE table1(col1 INTEGER));

  # prepare and execute the SQL statement.
  # call the subroutine PrepareExecuteSql() from DB2SampUtil.pm
  $sth = PrepareExecuteSql($dbh, $sql); 

  # commit the transaction or call TransRollback() from DB2SampUtil.pm 
  # if it fails
  $dbh->commit() || 
    TransRollback($dbh);

  # drop the table
  print "\n  Execute the statement\n";
  print "    DROP TABLE table1\n";

  $sql = qq(DROP TABLE table1);

  # prepare and execute the SQL statement
  $sth = PrepareExecuteSql($dbh, $sql);

  # commit the transaction or call TransRollback() from DB2SampUtil.pm 
  # if it fails
  $dbh->commit() || 
    TransRollback($dbh);
  
  # no more data to be fetched from statement handle
  $sth->finish;

  return 0;
} # StaticStmtInvoke

#######################################################################
# Description : How to use host variables to execute SQL statements
# Input       : None
# Output      : Returns 0 on success, exits otherwise
#######################################################################
sub StaticStmtWithHostVarsInvoke
{
  # declare the variables being used
  my $hostVar1;
  my $hostVar2;

  print "\n-----------------------------------------------------------";
  print "\nUSE THE SQL STATEMENTS:\n";
  print "  DELETE\n";
  print "TO SHOW HOW TO USE HOST VARIABLES.\n";

  # execute a statement with host variables
  print "\n  Execute\n";
  print "    DELETE FROM org\n";
  print "      WHERE deptnumb = \$hostVar1 AND\n";
  print "            division = \$hostVar2\n";
  print "  for\n";
  print "    hostVar1 = 15\n";
  print "    hostVar2 = 'Eastern'\n";

  $hostVar1 = 15;
  $hostVar2 = 'Eastern';

  my $sql = qq(DELETE FROM org
               WHERE deptnumb = ? AND
                     division = ? );

  # prepare the sql statement 
  my $sth = $dbh->prepare($sql);

  # execute the sql statement by passing the hostvariables
  $sth->execute($hostVar1, $hostVar2);
  
  # rollback the transaction
  print "\n  Rollback the transaction.\n";
  $dbh->rollback();
 
  return 0;
} # StaticStmtWithHostVarsInvoke

#######################################################################
# Description : How to execute SQL statements with 'do' interface
# Input       : None
# Output      : Returns 0 on success, exits otherwise
#######################################################################
sub StmtEXECUTE
{
  my $hostVarStmt;

  print "\n-----------------------------------------------------------";
  print "\nUSE THE SQL STATEMENTS:\n";
  print "  PREPARE\n";
  print "  EXECUTE\n";
  print "TO SHOW HOW TO USE SQL STATEMENTS WITH 'EXECUTE'.\n";

  # sql statement to be executed
  $hostVarStmt = qq(DELETE FROM org WHERE deptnumb = 15);
  printf "\n  Execute the statement\n";
  printf "    DELETE FROM org WHERE deptnumb = 15\n";

  # execute the sql statement
  $dbh->do($hostVarStmt);
 
  # rollback the transaction
  print "\n  Rollback the transaction.\n";
  $dbh->rollback();
 
  return 0;
} # StmtEXECUTE

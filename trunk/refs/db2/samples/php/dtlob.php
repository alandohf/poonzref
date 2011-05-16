<?php
/****************************************************************************
** Licensed Materials - Property of IBM
**
** Governed under the terms of the International
** License Agreement for Non-Warranted Sample Code.
**
** (C) COPYRIGHT International Business Machines Corp. 1998 - 2003
** All Rights Reserved.
**
** US Government Users Restricted Rights - Use, duplication or
** disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
*****************************************************************************
**
** SOURCE FILE NAME: dtlob.php
**
** SAMPLE: How to use the LOB data type
**
** Note:
** -----
** This sample program creates 2 new files, namely, photo.gif (on Unix) or 
** photo.BMP (on Windows) and resume.TXT in the current working directory.
**
** SQL STATEMENTS USED:
**         SELECT 
**         INSERT
**         DELETE
**
** OUTPUT FILE: dtlob.out (available in the online documentation)
*****************************************************************************
**
** For more information on the sample programs, see the README file.
**
** For information on developing PHP applications, see the Application
** Development Guide.
**
** For information on using SQL statements, see the SQL Reference.
**
** For the latest information on programming, building, and running DB2
** applications, visit the DB2 application development website:
**     http://www.software.ibm.com/data/db2/udb/ad
****************************************************************************/

// include the util_funcs.php file that contains the common functions
include_once("util_funcs.php");

// call the Error handling function defined in util_funcs.php
Error_handler();

// check and parse the command line arguments
CmdLineArgChk($argc, $argv, $dbname, $username, $password);

printf("\nTHIS SAMPLE SHOWS HOW TO USE THE LOB DATA TYPE.\n");

// connect to the database
$dbconn = DbConn($dbname, $username, $password);

// override the auto commit option 
odbc_autocommit($dbconn, FALSE);

if ($dbconn != 0)
{
  // call the BlobFileUse function
  BlobFileUse($dbconn);
 
  // call the ClobUse function
  ClobUse($dbconn);

  //call the ClobFileUse function
  ClobFileUse($dbconn);

  // call the ClobLocatorUse function
  ClobLocatorUse($dbconn);
}

// disconnect from the database
DbDisconn($dbconn);

/***************************************************************************
* Description: The BlobFileUse function shows how to read BLOB data from 
*              a database.
* Input      : ODBC connection id
* Output     : Returns 0 on success, exits otherwise.
***************************************************************************/
function BlobFileUse($dbconn)
{
  printf("--------------------------------------------------------\n");
  printf("\nUSE THE SQL STATEMENT:\n");
  printf("  SELECT \n");
  printf("TO SHOW HOW TO USE A BLOB FILE.\n");

  // get the type of Operating System
  $OS_TYPE = PHP_OS;

  if ($OS_TYPE == 'WINNT')
  {
    $photo_format = 'bitmap';
    $filename = 'photo.BMP'; 
  }
  else
  {
    $photo_format = 'gif';
    $filename = 'photo.gif';
  }

  // read the BLOB data into the file
  printf("\n  Read BLOB data in the file '%s'.\n", $filename);
  
  $sql = "SELECT picture FROM emp_photo".
         "  WHERE photo_format = '$photo_format' AND empno = '000130'";

  // prepare and execute the sql statement
  $res = odbc_exec($dbconn, $sql);

  // the blob_data variable contains the BLOB image data.
  $blob_data = odbc_result($res, "PICTURE");

  if (is_null($blob_data))
  {
    printf("  NULL LOB indicated.\n");
    return 1;
  }
 
  /* the BLOB data returned by ODBC is in Hexadecimal character format.
     The following code in the 'for' loop reads 2 hexadecimal characters from
     the $blob_data variable at a time and converts it into a decimal number 
     which is then converted to an ASCII character and stored into the file
     'photo.gif' or 'photo.BMP'. */

  // $noc has the length of the BLOB image data.
  $noc = strlen($blob_data);
    
  /* Open the file in write mode. If it doesn't 
     exist, create it. */
  $fh = fopen($filename, "w");

  for ($i = 0; $i < $noc; $i = $i+2)
  {
    // read 2 hexadecimal characters into the variable $hchr.
    $hchr = substr($blob_data, $i, 2);
    
    // the decimal value of $hchr is stored into $dchr.
    $dchr = hexdec($hchr);
   
    // the $aschr contains the ASCII value of the $dchr variable.
    $aschr = chr($dchr);

    // store each ASCII value into the file 'photo.gif'.
    fwrite($fh, $aschr);
  }
  
  // close the file handle.
  fclose($fh);

  return 0;
} // BlobFileUse

/***************************************************************************
* Description: The ClobUse function shows how to read CLOB data from a 
*              database.
* Input      : ODBC connection id
* Output     : Returns 0 on success, exits otherwise.
***************************************************************************/
function ClobUse($dbconn)
{
  printf("--------------------------------------------------------\n");
  printf("\nUSE THE SQL STATEMENT:\n");
  printf("  SELECT \n");
  printf("TO SHOW HOW TO USE THE CLOB DATA TYPE.\n");
  printf("\n  READ THE CLOB DATA:\n");
  
  $sql = "SELECT empno, resume FROM emp_resume".
         "  WHERE resume_format = 'ascii' AND empno = '000130'";
 
  // prepare and execute the sql statement
  $res = odbc_exec($dbconn, $sql);

  // set the ODBC Binary mode to get the data as text
  odbc_binmode($res, ODBC_BINMODE_CONVERT);
   
  $empno = odbc_result($res, "EMPNO");

  // the CLOB data in the field 'resume' is stored into the variable $resume
  $resume = odbc_result($res, "RESUME");
  
  if (is_null($resume))
  {
    printf("  NULL LOB indicated.\n");
    return 1;
  }

  $arr = array();

  /* read the CLOB data into an array. Each item in the array contains one 
     line from the CLOB data. */
  $arr = split("\n", $resume);
  
  // $resume_length variable contains the length of the resume 
  $resume_length = strlen($resume);

  printf("\n    Empno: %s\n", $empno);
  printf("    Resume length: %d\n", $resume_length);
  printf("    First 15 lines of the resume:\n");

  // print the first 15 lines from the array 
  for ($i = 1; $i <= 15; $i++)
  {
    printf("       $arr[$i]\n");
  } 

  return 0;
} // ClobUse

/***************************************************************************
* Description: The ClobFileUse function shows how to read CLOB data from a 
*              database and store it into a file.
* Input      : ODBC connection id
* Output     : Returns 0 on success, exits otherwise.
***************************************************************************/
function ClobFileUse($dbconn)
{
  printf("--------------------------------------------------------\n");
  printf("\nUSE THE SQL STATEMENT:\n");
  printf("  SELECT \n");
  printf("TO SHOW HOW TO USE A CLOB FILE.\n");

  $filename = "resume.TXT";
  
  printf("\n  Read CLOB data in the file '%s'.\n", $filename);
  
  $sql = "SELECT resume FROM emp_resume".
         "  WHERE resume_format = 'ascii' AND empno = '000130'";

  // prepare and execute the sql statement
  $res = odbc_exec($dbconn, $sql);
 
  // the CLOB data in the field 'resume' is stored into the variable $resume
  $resume = odbc_result($res, "RESUME");

  if (is_null($resume))
  {
    printf("  NULL LOB indicated.\n");
    return 1;
  }

  // open the file 'resume.TXT'. If it doesn't exist, create it.
  $fh = fopen("resume.TXT", "w");

  // write the CLOB data into the file
  fwrite($fh, $resume);

  // close the file handle
  fclose($fh);

  return 0;  
} // ClobFileUse

/***************************************************************************
* Description: The ClobLocatorUse function shows how to search through CLOB
*              data and to write CLOB data into a database.
* Input      : ODBC connection id
* Output     : Returns 0 on success, exits otherwise.
***************************************************************************/
function ClobLocatorUse($dbconn)
{
  printf("\n--------------------------------------------------------");
  printf("\nUSE THE SQL STATEMENT:\n");
  printf("  SELECT \n");
  printf("  INSERT\n");
  printf("  DELETE\n");
  printf("TO SHOW HOW TO USE THE CLOB LOCATOR.\n");

  printf("\n  **************************************************\n");
  printf("           ORIGINAL RESUME -- VIEW\n");
  printf("  **************************************************\n");

  $sql = "SELECT resume FROM emp_resume".
         "  WHERE empno = '000130' AND resume_format = 'ascii'";
 
  // prepare and execute the sql statement
  $res = odbc_exec($dbconn, $sql);

  // set the ODBC Binary mode to get the data as text
  odbc_binmode($res, ODBC_BINMODE_CONVERT);

  // the CLOB data in the field 'resume' is stored into the variable $resume
  $resume = odbc_result($res, 1);

  // print the CLOB data
  printf($resume);

  printf("\n  ********************************************\n");
  printf("       NEW RESUME -- CREATE\n");
  printf("  ********************************************\n");

  // locate the 'Department Information' in the resume 
  $str_dept = "Department Information";
  $pos1 = strpos($resume, $str_dept);

  printf("\n    Create short resume without Department Info.\n");

  // locate the 'Education' in the resume 
  $str_edu = "Education";
  $pos2 = strpos($resume, $str_edu);
  
  printf("  Append Department Info at the end of Short resume.\n");
  
  // the variable $new_resume contains the modified resume data.
  $new_resume = substr($resume, 1, $pos1 - 1);
  $new_resume = $new_resume.substr($resume, $pos2);
  $new_resume = $new_resume.substr($resume, $pos1, $pos2 - $pos1);

  printf("  Insert the new resume in the database.\n");

  // escape the ' character contained in the modified resume data. 
  $new_resume = str_replace("'", "''", $new_resume);

  $sql = "INSERT INTO emp_resume(empno, resume_format, resume)".
         "  VALUES('000137', 'ascii', '$new_resume')";

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql);

  printf("\n  *************************************\n");
  printf("      NEW RESUME -- VIEW\n");
  printf("  *************************************\n");

  $sql = "SELECT resume FROM emp_resume".
         "  WHERE empno = '000137'";

  // prepare and execute the sql statement
  $res = odbc_exec($dbconn, $sql);

  // set the ODBC Binary mode to get the data as text
  odbc_binmode($res, ODBC_BINMODE_CONVERT);

  /* the variable $new_resume contains the modified resume data read from 
     the database. */
  $new_resume = odbc_result($res, 1);

  printf($new_resume);

  printf("\n  **************************************\n");
  printf("      NEW RESUME -- DELETE\n");
  printf("  **************************************\n");

  $sql = "DELETE FROM emp_resume WHERE empno = '000137'"; 

  // prepare and execute the sql statement
  odbc_exec($dbconn, $sql); 
  
  return 0;
} // ClobLocatorUse

?>

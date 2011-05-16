//***************************************************************************
// Licensed Materials - Property of IBM
//
// Governed under the terms of the International
// License Agreement for Non-Warranted Sample Code.
//
// (C) COPYRIGHT International Business Machines Corp. 1997 - 2006
// All Rights Reserved.
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//***************************************************************************
//
// SOURCE FILE NAME: JCCSimpleGSSEexception.java
//
// SAMPLE: This file is used by JCCSimpleGSSPlugin and JCCKerberosPlugin
//         to handle Exceptions
//
// OUTPUT FILE: None
//***************************************************************************
//
// For more information on the sample programs, see the README file.
//
// For information on developing JDBC applications, see the Application
// Development Guide.
//
// For information on using SQL statements, see the SQL Reference.
//
// For the latest information on programming, compiling, and running DB2
// applications, visit the DB2 application development website at
//     http://www.software.ibm.com/data/db2/udb/ad
//**************************************************************************/


public class JCCSimpleGSSException extends org.ietf.jgss.GSSException
{
  String reason_;
  public JCCSimpleGSSException(int majorCode,String reason)
  {
    super(majorCode);
    reason_ = reason;
  }

  public JCCSimpleGSSException (int majorCode, int minorCode, String minorString, String reason)
  {
    super(majorCode, minorCode, minorString);
    reason_ = reason;
  }

  public String getMessage()
  {
    return super.getMessage() + "  " + reason_;
  }
}

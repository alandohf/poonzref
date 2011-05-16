//**************************************************************************
// Licensed Materials - Property of IBM
// Governed under the terms of the IBM Public License
//
// (C) COPYRIGHT International Business Machines Corp. 2002, 2004        
// All Rights Reserved.
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//***************************************************************************
//
// SOURCE FILE NAME: Example1.java
//    
// SAMPLE: Add a new toolbar button to the Control Center toolbar.
//
// SQL Statements USED: none
//
// OUTPUT FILE: none
//
//  Steps to run the sample:
//  (1) compile this java file (javac Example1.java).
//      To compile on Windows operating systems,
//      your CLASSPATH must include:
//            DRIVE:\sqllib\tools\db2navplug.jar
//            DRIVE:\sqllib\java\Common.jar
//      (where DRIVE: represents the drive on which DB2 is installed).
//
//      To compile on UNIX platforms, your CLASSPATH must include: 
//            /u/db2inst1/sqllib/tools/db2navplug.jar
//            /u/db2inst1/sqllib/java/Common.jar
//      (where /u/db2inst1 represents the directory on which DB2 is installed).
//  (2) create db2plug.zip (zip -r0 db2plug.zip *.class)
//  (3) put db2plug.zip in your classpath.
//      Note: The db2cc command sets the classpath to point to
//        db2plug.zip in the tools directory.
//      On Windows operating systems,
//      put db2plug.zip in the DRIVE:\sqllib\tools directory
//      (where DRIVE: represents the drive on which DB2 is installed).
//
//      On UNIX platforms, 
//      put db2plug.zip in the /u/db2inst1/sqllib/tools directory
//      (where /u/db2inst1 represents the directory on which DB2 is installed).
//  (4) Run the Control Center.
//
// For more information about this sample program, see
// the "Extending the Control Center" appendix in the "Administration Guide".
//
// For more information about the sample programs, see the README file.
//
// For more information about programming in Java, see the
// "Programming in Java" section of the "Application Development Guide".
//
// For more information about building Java applications, see the
// section for your compiler in the "Building Applications" chapter
// for your platform in the "Application Development Guide".
//
// For more information about SQL, see the "SQL Reference".
//
// For more information on DB2 APIs, see the Administrative API Reference.
//
// For the latest information on programming, compiling, and running DB2 
// applications, refer to the DB2 application development website at 
//     http://www.software.ibm.com/data/db2/udb/ad
//**************************************************************************/

import  com.ibm.db2.tools.cc.navigator.*;
import  java.awt.event.*;
import  javax.swing.*;
import  com.ibm.db2.tools.common.*;

public class Example1 implements CCExtension
{

  public CCObject[] getObjects () {
    return null;
  }

  public CCToolbarAction[] getToolbarActions () {
    return new CCToolbarAction[] { new Example1ToolbarAction() };
  }

  class Example1ToolbarAction implements CCToolbarAction {

    public String getHoverHelpText() { return "Example1"; }

    // Supply your own icon. This example uses the Refresh icon.
    public ImageIcon getIcon() {
       return CommonImageRepository.getCommonIcon(CommonImageRepository.WC_NV_REFRESH);
    }

    public void actionPerformed(ActionEvent e) {
      System.out.println("I've been clicked");
    }

  }

}


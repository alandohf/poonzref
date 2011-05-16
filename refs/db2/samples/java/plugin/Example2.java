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
// SOURCE FILE NAME: Example2.java
//    
// SAMPLE: Add new menu actions to Control Center Database objects.
//
// SQL Statements USED: none
//
// OUTPUT FILE: none
//
//  Steps to run the sample:
//  (1) compile this java file (javac Example2.java).
//      To compile on Windows operating systems,
//      your CLASSPATH must include:
//            DRIVE:\sqllib\tools\db2navplug.jar
//      (where DRIVE: represents the drive on which DB2 is installed).
//
//      To compile on UNIX platforms, your CLASSPATH must include: 
//            /u/db2inst1/sqllib/tools/db2navplug.jar
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

public class Example2 implements CCExtension
{

  public CCToolbarAction[] getToolbarActions () {
    return null;
  }

  public CCObject[] getObjects () {
    return new CCObject[] { new CCDatabase() };
  }

  class CCDatabase implements CCObject {

    public String getName () { return null; }
    public boolean isEditable () { return true; }
    public boolean isConfigurable () { return true; }

    public int getType () { return UDB_DATABASE; }

    public CCMenuAction[] getMenuActions () {
      return new CCMenuAction[] { new Example2AAction(),
                                  new Example2BAction(),
                                  new Example2CSeparator(),
                                  new Example2DAction() };
    }
  }

  class Example2AAction implements CCMenuAction {

    public String getMenuText () { return "Example2A Action"; }

    public void actionPerformed (ActionEvent e) {
      System.out.println("Example2A menu item actionPerformed");
    }

  }

  class Example2BAction implements CCMenuAction, Positionable {

    public String getMenuText () { return "Example2B Action"; }

    public void actionPerformed (ActionEvent e) {
      System.out.println("Example2B menu item actionPerformed");
    }

    public int getPosition() {
       return 0;
    }
  }

  class Example2CSeparator implements CCMenuAction, Separator, Positionable {

    public String getMenuText () { return null; }

    public void actionPerformed (ActionEvent e) {}

    public int getPosition() {
       return 1;
    }
  }

  class Example2DAction implements CCMenuAction, SubMenuParent {

    public String getMenuText () { return "Example2D Action"; }

    public void actionPerformed (ActionEvent e) {
      System.out.println("Example2D menu item actionPerformed");
    }

    public CCMenuAction[] getSubMenuActions() {
       return new CCMenuAction[] { new Example2DSubMenuAction() };
    }

  }

  class Example2DSubMenuAction implements CCMenuAction {

    public String getMenuText () { return "Example2D Sub-Menu Action"; }

    public void actionPerformed (ActionEvent e) {
      System.out.println("Example2D sub-menu menu item actionPerformed");
    }

  }

}


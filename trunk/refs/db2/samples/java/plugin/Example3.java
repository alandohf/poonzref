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
// SOURCE FILE NAME: Example3.java
//    
// SAMPLE: Add plugin objects under Database objects in the Control Center tree.
//
// SQL Statements USED: none
//
// OUTPUT FILE: none
//
//  Steps to run the sample:
//  (1) compile this java file (javac Example3Child.java Example3Folder.java Example3.java).
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
import  java.util.*;

public class Example3 implements CCExtension
{

  public CCToolbarAction[] getToolbarActions () {
    return null;
  }

  public CCObject[] getObjects () {
    return new CCObject[] { new CCDatabase() };
  }

  class CCDatabase implements CCTreeObject {
    private String parentName = null;
    private Vector childVector;

    public CCDatabase() {
      childVector = new Vector();
      childVector.addElement(new Example3Folder());
    }

    public CCTableObject[] getChildren() {
      CCTableObject[] children = new CCTableObject[childVector.size()];
      childVector.copyInto(children);
      return children;
    }

    public void setParentName(String name)
    {
      parentName = name;
    }      
    
    public String getName () { return null; }
    public boolean isEditable () { return true; }
    public boolean isConfigurable () { return true; }
    public void getData (Object[] data) { }
    public CCColumn[] getColumns () { return null; }
    public boolean isLeaf () { return false; }
    public int getType () { return UDB_DATABASE; }
    public Icon getIcon (int iconState) { return null; }
    public CCMenuAction[] getMenuActions () { return null; }
  }

}


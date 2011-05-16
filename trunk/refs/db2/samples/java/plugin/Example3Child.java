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
// SOURCE FILE NAME: Example3Child.java
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
import  com.ibm.db2.tools.common.*;
import  java.util.*;


public class Example3Child extends Observable implements CCTableObject {

  private String parentName = null;
  private String name;
  private String state;
  private CCMenuAction[] menuActions;

  public Example3Child(Example3Folder folder, String name, String state) {
    this.name = name;
    this.state = state;
    menuActions = new CCMenuAction[] { new AlterAction(),
                                       new RemoveAction(folder) };
  }
  
  /**
   * No argument contructor
   * This allows the Control Center to call newInstance()
   * to gather information about this class.
   * 
   */
  public Example3Child() {
    super();
  }

  public String getName () { return name; }

  public Icon getIcon (int iconState) {
    return CommonImageRepository.getScaledIcon(CommonImageRepository.WC_NV_REFRESH);
  }

  public void setParentName(String name)
  {
    parentName = name;
  }  
  
  public boolean isEditable () { return false; }
  public boolean isConfigurable () { return false; }

  public int getType () { return CCTypeFactory.getTypeNumber(this.getClass().getName()); }

  public CCColumn[] getColumns () {
    return new CCColumn[] { new NameColumn(),
                            new StateColumn() };
  }

  public void getData (Object[] data) {
    data[0] = this;
    data[1] = state;
  }

  public CCMenuAction[] getMenuActions () {
    return menuActions;
  }

  public void setState(String state) {
    this.state = state;
    setChanged();
    notifyObservers(new CCObjectCollectionEvent(this, CCObjectCollectionEvent.OBJECT_ALTERED, this));
  }

  class NameColumn implements CCColumn {
     public String getName() { return "Name"; }
     public Class getColumnClass() { return CCTableObject.class; }
  } //NameColumn

  class StateColumn implements CCColumn {
     public String getName() { return "State"; }
     public Class getColumnClass() { return String.class; }
  } //StateColumn

  class RemoveAction implements CCMenuAction, MultiSelectable {
    private Example3Folder folder;

    public RemoveAction(Example3Folder folder) {
       this.folder = folder;
    }

    public String getMenuText () { return "Remove"; }

    public int getSelectionMode () { return MultiSelectable.MULTI_HANDLE_ONE; }

    public void actionPerformed (ActionEvent e) {
      Vector childrenVector = (Vector)e.getSource();
      for (int i = 0; i < childrenVector.size(); i++) {
        folder.removeChild((Example3Child)childrenVector.elementAt(i));
      }
    }
  } //RemoveAction

  class AlterAction implements CCMenuAction, CCDefaultMenuAction {
    private int stateNumber = 1;
    public String getMenuText () { return "Alter"; }

    public void actionPerformed (ActionEvent e) {
      ((Example3Child)((Vector)e.getSource()).elementAt(0)).setState("State " + ++stateNumber);
    }
  } //AlterAction
} //Example3Child

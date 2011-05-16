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
// SOURCE FILE NAME: Example3Folder.java
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

  public class Example3Folder extends Observable implements CCTreeObject {
    private String parentName = null;
    private Vector childVector;
    private CCMenuAction[] menuActions = new CCMenuAction[] { new CreateAction() };

    public Example3Folder() {
      childVector = new Vector();
    }

    public CCTableObject[] getChildren () {
      // For simplicity, this example returns a list of 
      // children which are stored in the vector called childVector.
      //
      // A real plugin should reconstruct the children when getChildren is
      // called. This will refresh the list which may include new
      // or changed child objects which may have been created or changed 
      // outside the Control Center since the last time the list was 
      // displayed. The children should be stored in and read from
      // persistent storage so that they are not lost.
      //
      // Also in a real plugin, the list of children returned by getChildren is 
      // dependent on what objects are the parents of this object in Control
      // Center tree.  The parent information is in the parentName string 
      // which is provided by the Control Center call to the setParentName 
      // method.
      //
      // NOTE: In this example, when a refresh is done in the Control Center 
      // from the Database object or higher in the tree, the list of children 
      // under the Example3 Folder will be lost.  This is because a 
      // new Example3Folder is constructed by the Control Center when the 
      // refresh is done.  If this example code read the children in from
      // persistent storage, the children would not be lost.  
      // To keep the example simple, we do not do this.
            
      CCTableObject[] children = new CCTableObject[childVector.size()];
      childVector.copyInto(children);
      return children;
    }

    public void setParentName(String name)
    {
      parentName = name;
    }

    public void getData (Object[] data) {
       data[0] = this;
    }

    public String getName () { return "Example3 Folder"; }

    public int getType () { return CCTypeFactory.getTypeNumber(this.getClass().getName()); }

    public Icon getIcon (int iconState) {
      switch (iconState) {
        case CLOSED_FOLDER:
        return CommonImageRepository.getScaledIcon(CommonImageRepository.NV_CLOSED_FOLDER);

        case OPEN_FOLDER:
        return CommonImageRepository.getScaledIcon(CommonImageRepository.NV_OPEN_FOLDER);

        default:
        return CommonImageRepository.getScaledIcon(CommonImageRepository.NV_CLOSED_FOLDER);
      }
    }

    public boolean isEditable () { return false; }
    public boolean isConfigurable () { return false; }

    public CCColumn[] getColumns () {
       return new CCColumn[] { new NameColumn(),
                               new StateColumn() };
    }

    public boolean isLeaf () { return true; }

    public void addChild(Example3Child child) {
      childVector.addElement(child);
      setChanged();
      notifyObservers(new CCObjectCollectionEvent(this,
                                                  CCObjectCollectionEvent.OBJECT_ADDED,
                                                  child));
    }

    public void removeChild(Example3Child child) {
      childVector.removeElement(child);
      setChanged();
      notifyObservers(new CCObjectCollectionEvent(this,
                                                  CCObjectCollectionEvent.OBJECT_REMOVED,
                                                  child));
    }

    public CCMenuAction[] getMenuActions () {
      return menuActions;
    }
    
    class NameColumn implements CCColumn {
       public String getName() { return "Name"; }
       public Class getColumnClass() { return CCTableObject.class; }
    } //NameColumn

    class StateColumn implements CCColumn {
       public String getName() { return "State"; }
       public Class getColumnClass() { return String.class; }
    } //StateColumn
  
    class CreateAction implements CCMenuAction {
      private int pluginNumber = 0;
      public String getMenuText () { return "Create"; }

      public void actionPerformed (ActionEvent e) {
        Example3Folder folder = (Example3Folder)((Vector)e.getSource()).elementAt(0);
        folder.addChild(new Example3Child(folder, "Plugin " + ++pluginNumber, "State 1"));
      }
    } //CreateAction    
  } //Example3Folder

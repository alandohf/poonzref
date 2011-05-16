README file for DB2 Spatial Extender Samples

*
*
* (C) COPYRIGHT INTERNATIONAL BUSINESS MACHINES CORPORATION 2005.
*
     ALL RIGHTS RESERVED.
*


File: sqllib/samples/extenders/spatial/README_spatial_samples.txt

The DB2 Spatial Extender samples consist of two different demo programs.
  - One sample is based on banking (branches, customers, employees).
    This banking demo is written in SQL scripts run by the command-line
    processor (CLP).
  - The other sample is based on property parcels and natural features
    (flood zones, regions, and so on). This property parcel demo
    is written in C and is compiled and linked into an executable program.
This file briefly introduces each demo and indicates where to look for
further information.


= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
The Banking Demo is implemented in SQL scripts that are run with the DB2
command line processor. You can use the demo and scripts as a tutorial.
The scripts and README file "seBankDemoREADME.txt" are located in the
"bank" subdirectory (sqllib/extenders/samples/spatial/bank).
The following excerpt from that file gives an introduction to the demo:
*****************************************************************************
  Banking Customer Analysis Sample

  This demo illustrates adding a spatial dimension to an existing
  information system. The existing system did not contain any explicit
  location (spatial) data. However, the existing system did contain implicit
  location data in the form of addresses.  By spatially enabling the existing
  database, the user expands the business analysis capabilities of the system.

  A bank that has customers with accounts at two branches needs to use the
  spatial attribute of the existing data along with census demographic data
  to perform various kinds of spatial analysis.  The analysis consists of
  comparing customer, branch, and demographic data, as well as profiling
  customers and doing market analysis.  The bank looks for prospective
  customers by finding average balances for customers within three miles of
  the branch, determining what areas the primary customers live in, and
  searching for similar areas.

  Note: Although this demo focuses on a banking application, it is equally
  applicable to different businesses such as retail, insurance, and so on.
*****************************************************************************

For UNIX, the Banking Demo is driven by a Korn shell script called
"seBankDemoRunBankDemo". To display usage information, enter
       seBankDemoRunBankDemo -h

For Windows, the Banking Demo is driven by a batch file called
"seBankDemoRunBankDemo.bat". To display usage information, enter
       seBankDemoRunBankDemo -h

Before you run the demo, look at the "seBankDemoREADME.txt" file. This
README file describes the prerequisites and explains how to run the demo.

After the Banking Demo runs, the complete record of its actions can be found
in the file "se_bank.log" which is in the "tmp", subdirectory under the home
directory of the user who ran the demo.


= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
The Property Parcel Demo is implemented in C code using the DB2 CLI interface.
The following chapters in the DB2 Spatial Extender and Geodetic Extender
User's Guide provides more information:

  - Chapter 4 gives information about running "runGseDemo" to verify your
    installation. Read that section carefully.

  - Chapter 14 provides a step-by-step overview of all the operations of this
    Demo.  Recommendation:  Review Chapter 14 before you run the "runGseDemo"
    program.

The Property Parcel Demo is located in the sqllib/extenders/samples/spatial
directory and the executable file is "runGseDemo".

To display usage information, enter the following command:
       runGseDemo -h

After you install Spatial Extender on Windows the "runGseDemo" program is
ready to execute.  On Linux or UNIX platforms, you create an instance after
you install Spatial Extender.  On platforms that support both 32-bit and 64-bit
instances, the "runGseDemo" program that is included in the distribution is
the 32-bit program.  If you have created a 64-bit instance, you must rebuild
"runGseDemo" as described below.

Modifying and Rebuilding "runGseDemo"
-------------------------------------
The source code for the "runGseDemo" program is included in the distribution
in case you would like to make modifications or additions to the program.
To modify the program, create a new directory that is not under sqllib and
copy the source and header files (samputil.h, samputil.c, runGseDemo.c) there.
On Windows, you also need the "makefile.nt" file.
On any UNIX platform, you also need the "bldDemo" file.

To recompile and relink the "runGseDemo" program, enter the following command:
For UNIX,
      "bldDemo"
For Windows,
      "nmake -f makefile.nt"

If you are building a 64-bit Windows application on a Windows 32-bit system,
you must change makefile.nt to add "Win64" to the DB2_LIBS parameter:
DB2_LIBS = $(DB2_DIR)\lib\Win64\db2cli.lib $(DB2_DIR)\lib\Win64\db2api.lib
(see Chapter 14 of the DB2 Spatial Extender and Geodetic Extender User's Guide).



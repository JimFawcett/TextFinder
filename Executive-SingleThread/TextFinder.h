#pragma once
/////////////////////////////////////////////////////////////////////
// TextFinder.h - Find text in files within a directory subtree    //
// ver 1.3                                                         //
//-----------------------------------------------------------------//
// Jim Fawcett (c) copyright 2019                                  //
// All rights granted provided this copyright notice is retained   //
//-----------------------------------------------------------------//
// Jim Fawcett, CSE687 - Object Oriented Design, Fall 2018         //
/////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* TextFinder uses the resources of DirExplorerT<Application> and 
* TextSearch to find files in a specified directory tree that match
* a regular expression.
*
* Required Files:
* ---------------
* TextFinder.h, TextFinder.cpp      // find all files matching regex
* DirExplorerT.h, DirExplorerT.cpp  // navigate specified dir tree
* Application.h, Application.cpp    // provides defn's for doDir and doFile
* FileSystem.h, FileSystem.cpp      // Directory and Path classes
* StringUtilities.h                 // Title function
* CodeUtilities.h                   // ProcessCmdLine class
*
* Maintenance History:
* --------------------
* ver 1.3 : 01 Aug 2019
* - changed option storage to std::unordered_map.  That allows users to define
*   custom options that may have a value as well as an option key.

* ver 1.2 : 31 Jul 2019
* - moved processing of searches from Application to TextFinder.  That entailed:
*   - adding callback reference of TextFinder to Application.  Application finds
*     files and directories, and calls back TextFinder instance to process searches.
*   - TextFinder now contains a DirExplorerT<Application> instance which it configures
*     according to command line arguments.
* ver 1.1 : 25 Jun 2019
* - added ProcessCmdLine to process commandline arguments
* ver 1.0 : 03 Jun 2019
* - first release
*
*/

#include <fstream>
#include <regex>
#include "ITextFinder.h"
#include "../DirExplorer-Template/DirExplorerT.h"

class TextFinder : public ITextFinder
{
public:
  bool initialize(int argc, char* argv[]);
  ~TextFinder();
  void usage();
  void path(const std::string& path);
  bool logFile(const std::string& logfile);
  void searchRegEx(const std::string& regEx);
  bool searchFile(const std::string& searchfile);
  void search();
  FileSystem::DirExplorerT<Application>& dirExplorer();
private:
  bool processCmdLine(int argc, char* argv[]);
  bool configureDirExplorerT();
  std::ofstream logStream_;
  std::string regex_ = "";
  FileSystem::DirExplorerT<Application> de_;
};
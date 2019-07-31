#pragma once
/////////////////////////////////////////////////////////////////////
// Application.h - TextFinder application details for navigation   //
// ver 1.2                                                         //
//-----------------------------------------------------------------//
// Jim Fawcett (c) copyright 2015                                  //
// All rights granted provided this copyright notice is retained   //
//-----------------------------------------------------------------//
// Jim Fawcett, CSE687 - Object Oriented Design, Fall 2018         //
/////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  Provides the Application class that implements the application
*  specific parts of navigation for Textfinder, e.g., how to handle
*  file and directory discovery.
*
*  Required Files:
*  ---------------
*  Application.h
*
*  Notes:
*  - Application creates an instance of TextSearch and uses it for
*    each discovered file, so Executive doesn't need to know about
*    that class.
*  - This is a header only package.  Just include it in the same folder
*    as DirExplorerT.
*/
#include <iostream>
#include <fstream>
#include <string>
#include "../TextSearch/TextSearch.h"

class Application
{
public:
  //----< define search's text target >------------------------------

  void searchText(const std::string& text)
  {
    text_ = text;
  }
  //----< hide dirs with no matches >--------------------------------

  void hideDirNoMatch()
  {
    hideDir_ = true;
  }
  //----< handle directory discovery >-------------------------------

  void doDir(const std::string& dirName) {
    currDir_ = dirName;
  }
  //----< handle file discovery >------------------------------------

  void doFile(const std::string& fileName) {
    std::string fullSpec = currDir_ + "\\" + fileName;
    if (hideDir_ == false)
    {
      std::cout << "\n  " << fullSpec;
      if (logStream_.good())
        logStream_ << "\n  " << fullSpec;

    }
    if (ts_.open(fullSpec) && ts_.find(text_))
    {
      if(hideDir_ == true)
      {
        std::cout << "\n  " << fullSpec;
        if (logStream_.good())
          logStream_ << "\n  " << fullSpec;
      }
      std::cout << "\n    found \"" << text_ << "\"\n";
      if(logStream_.good())
        logStream_ << "\n    found \"" << text_ << "\"\n";
      ts_.close();
    }
  }
  //----< set log file >---------------------------------------------

  void logFile(const std::string& logfile)
  {
    logFile_ = logfile;
    logStream_.open(logFile_);
  }
  //----< ignore DirExplorer maxItems_ for current directory >-------

  void showAllInCurrDir(bool show)
  {
    showAll_ = show;
  }
  //----< Application is not responsible for stopping >--------------

  bool done()
  {
    return false;
  }
  //----< close log >------------------------------------------------

  ~Application()
  {
    if(logStream_.good())
      logStream_.close();
  }
private:
  TextSearch ts_;
  bool showAll_ = false;
  std::string currDir_ = "";
  std::string text_ = "";
  bool hideDir_ = false;
  std::string logFile_ = "";
  std::ofstream logStream_;
};
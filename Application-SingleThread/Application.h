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

class TextFinder;

class Application
{
public:
  void textFinder(TextFinder* pTextFinder);
  void searchText(const std::string& text);
  void hideDirNoMatch();
  void doDir(const std::string& dirName);
  void doFile(const std::string& fileName);
  void logFile(const std::string& logfile);
  void showAllInCurrDir(bool show);
  bool done();
  ~Application();
private:
  //TextSearch ts_;
  TextFinder* pTextFinder_ = nullptr;
  bool showAll_ = false;
  std::string currDir_ = "";
  std::string text_ = "";
  bool hideDir_ = false;
  std::string logFile_ = "";
  std::ofstream logStream_;
};
#pragma once
/////////////////////////////////////////////////////////////////////
// Application.h - TextFinder application details for navigation   //
// ver 1.2                                                         //
//-----------------------------------------------------------------//
// Jim Fawcett (c) copyright 2015                                  //
// All rights granted provided this copyright notice is retained   //
//-----------------------------------------------------------------//
// Jim Fawcett, Emeritus Teaching Professor, Syracuse University   //
/////////////////////////////////////////////////////////////////////
/*
*  Package Operations:
*  -------------------
*  Provides Application class that implements application specific
*  parts of navigation for Textfinder, e.g., how to handle file
*  and directory discovery.
*
*  Holds an interface pointer to TextFinder to use it's searchFile
*  method.
*
*  Required Files:
*  ---------------
*  Application.h, Application.cpp
*  TextFinder.h, TextFinder.cpp
*
*  Notes:
*  - Application creates an instance of TextSearch and uses it for
*    each discovered file, so Executive doesn't need to know about
*    that class.  It does that by delegating to TextFinder::searchFile(...).
*/
#include <iostream>
#include <fstream>
#include <string>
#include "../TextSearch/TextSearch.h"
#include "../Executive-SingleThread/ITextFinder.h"

class Application
{
public:
  Application() {}
  Application(const Application& app) = delete;
  Application& operator=(const Application& app) = delete;
  void textFinder(ITextFinder* pTextFinder);
  void searchText(const std::string& text);
  void hideDirNoMatch();
  void doDir(const std::string& dirName);
  void doFile(const std::string& fileName);
  void logFile(const std::string& logfile);
  void showAllInCurrDir(bool show);
  void maxItems(int i);
  bool done();
  ~Application();
private:
  ITextFinder* pTextFinder_ = nullptr;
  bool showAll_ = false;
  std::string currDir_ = "";
  std::string text_ = "";
  bool hideDir_ = false;
  std::string logFile_ = "";
  std::ofstream logStream_;
  int maxItems_ = 0;
};
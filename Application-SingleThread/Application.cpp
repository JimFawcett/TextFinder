/////////////////////////////////////////////////////////////////////
// Application.cpp - TextFinder application details for navigation //
// ver 1.2                                                         //
//-----------------------------------------------------------------//
// Jim Fawcett (c) copyright 2015                                  //
// All rights granted provided this copyright notice is retained   //
//-----------------------------------------------------------------//
// Jim Fawcett, CSE687 - Object Oriented Design, Fall 2018         //
/////////////////////////////////////////////////////////////////////

#include "Application.h"
#include "../Executive-SingleThread/TextFinder.h"

//----< provide callback to TextFinder >---------------------------

void Application::textFinder(TextFinder* pTextFinder)
{
  pTextFinder_ = pTextFinder;
}
//----< define search's text target >------------------------------

void Application::searchText(const std::string& text)
{
  text_ = text;
}
//----< hide dirs with no matches >--------------------------------

void Application::hideDirNoMatch()
{
  hideDir_ = true;
}
//----< handle directory discovery >-------------------------------

void Application::doDir(const std::string& dirName) {
  currDir_ = dirName;
}
//----< handle file discovery >------------------------------------

void Application::doFile(const std::string& fileName) {
  std::string fullSpec = currDir_ + "\\" + fileName;
  bool found = pTextFinder_->searchFile(fullSpec);
  if (hideDir_ == false)
  {
    std::cout << "\n  " << fullSpec;
    if (logStream_.good())
      logStream_ << "\n  " << fullSpec;
  }
  if (found == true)
  {
    if (hideDir_ == true)
    {
      std::cout << "\n  " << fullSpec;
      if (logStream_.good())
        logStream_ << "\n  " << fullSpec;
    }
    std::cout << "\n    found \"" << text_ << "\"\n";
    if (logStream_.good())
      logStream_ << "\n    found \"" << text_ << "\"\n";
  }
}
//----< set log file >---------------------------------------------

void Application::logFile(const std::string& logfile)
{
  logFile_ = logfile;
  logStream_.open(logFile_);
}
//----< ignore DirExplorer maxItems_ for current directory >-------

void Application::showAllInCurrDir(bool show)
{
  showAll_ = show;
}
//----< Application is not responsible for stopping >--------------

bool Application::done()
{
  return false;
}
//----< close log >------------------------------------------------

Application::~Application()
{
  if (logStream_.good())
    logStream_.close();
}

/////////////////////////////////////////////////////////////////////
// TextFinder.cpp - Find text in files within a directory subtree  //
// ver 1.2                                                         //
//-----------------------------------------------------------------//
// Jim Fawcett (c) copyright 2019                                  //
// All rights granted provided this copyright notice is retained   //
//-----------------------------------------------------------------//
// Jim Fawcett, CSE687 - Object Oriented Design, Fall 2018         //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include "../CppUtilities/CodeUtilities/CodeUtilities.h"
#include "TextFinder.h"

using namespace FileSystem;
using namespace Utilities;

std::string usageMsg()
{
  std::ostringstream out;
  out << "\n  TextFinder version 1.3, 24 Jun 2019";
  out << "\n  Finds files with text matching a regex\n";
  out << "\n  usage: TextFinder /P path [/s] [/v] [/H] [/h] [/p pattern]* [/r regex]";
  out << "\n    path = relative or absolute path of starting directory";
  out << "\n    /s for recursive search";
  out << "\n    /v for verbose output - shows commandline processing results";
  out << "\n    /H for hide directories with no match";
  out << "\n    /h show this message and exit";
  out << "\n    pattern is a pattern string of the form *.h,*.log, etc. with no spaces";
  out << "\n    regex is a regular expression specifying targets, e.g., files or dirs\n";
  out << "\n  Example: TextFinder /P .. /s /R \"TEST_ | #ifdef | #pragma once\" /p *.h,*.cpp\n";
  out << "\n  Note: regular expression string must be wrapped in quotes";
  out << "\n";
  return out.str();
}
//----< set custom usage message >-----------------------------------

void TextFinder::usage()
{
  std::cout << usageMsg();
}
//----< set root of search path >------------------------------------

void TextFinder::path(const std::string& path)
{
  de_.path(path);
}
//----< set regular expression pattern >-----------------------------

void TextFinder::searchRegEx(const std::string& regEx)
{
  regex_ = regEx;
}
//----< provide access to internal DirExplorerT<Application> >-------

FileSystem::DirExplorerT<Application>& TextFinder::dirExplorer()
{
  return de_;
}
//----< search file for text matching regex >------------------------

bool TextFinder::searchFile(const std::string& searchfile)
{
  TextSearch ts;
  ts.open(searchfile);
  bool found = ts.find(regex_);
  ts.close();
  return found;
}
//----< search all files in dir tree rooted at path >----------------

void TextFinder::search()
{
  de_.app().textFinder(this);  // give callback reference to Application
  de_.search();                // start DirExplorerT<App> search
}
//----< attempt to open logfile >------------------------------------

bool TextFinder::logFile(const std::string& logfile)
{
  logStream_.open(logfile);
  return logStream_.good();
}
//----< close logfile >----------------------------------------------

TextFinder::~TextFinder()
{
  if (logStream_.good())
    logStream_.close();
}
//----< configure TextFinder's DirExplorerT<Application> >-----------

bool TextFinder::initialize(int argc, char* argv[])
{
  ProcessCmdLine pcl(argc, argv);
  pcl.setUsageMessage(usageMsg());
  pcl.process();

  if (pcl.parseError())
  {
    usage();
    return false;
  }
  if (pcl.hasOption('v'))
  {
    std::cout << "\n  TextFinder";

    pcl.showCmdLine(argc, argv, true);

    std::cout << "\n    path  = " << pcl.path();
    if (pcl.patterns().size() > 0)
    {
      std::cout << "\n    patts = ";
      for (auto patt : pcl.patterns())
      {
        std::cout << patt << " ";
      }
    }
    if (pcl.options().size() > 0)
    {
      std::cout << "\n    optns = ";
      for (auto opt : pcl.options())
      {
        std::cout << opt << " ";
      }
    }
    std::cout << "\n    regex = " << pcl.regex() << "\n";
  }
  else
  {
    std::cout << "\n  TextFinder\n";
  }

  if (pcl.hasOption('h'))
  {
    usage();
    return false;
  }

  searchRegEx(pcl.regex());

  if (pcl.logFile() != "")
  {
    logFile(pcl.logFile());
  }

  std::string path = pcl.path();

  DirExplorerT<Application>& deRef = dirExplorer();

  deRef.path(path);
  deRef.recurse(true);
  for (auto patt : pcl.patterns())
    deRef.addPattern(patt);
  deRef.hideEmptyDirectories(true);
  deRef.app().searchText(pcl.regex());
  if (pcl.hasOption('H'))
    deRef.app().hideDirNoMatch();
  if (pcl.logFile() != "")
    deRef.app().logFile(pcl.logFile());

  return true;
}
//----< program entry point >----------------------------------------

int main(int argc, char* argv[])
{
  TextFinder tf;
  tf.initialize(argc, argv);

  tf.search();

  std::cout << "\n\n";
}


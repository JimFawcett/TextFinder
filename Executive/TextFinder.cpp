/////////////////////////////////////////////////////////////////////
// TextFinder.h - Find text in files within a directory subtree    //
// ver 1.1                                                         //
//-----------------------------------------------------------------//
// Jim Fawcett (c) copyright 2019                                  //
// All rights granted provided this copyright notice is retained   //
//-----------------------------------------------------------------//
// Jim Fawcett, CSE687 - Object Oriented Design, Fall 2018         //
/////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* TextFinder uses the resources of DirExplorerT and TextSearch
* to find files in a specified directory tree that match a 
* regular expression.
*
* Required Files:
* ---------------
* TextFinder.cpp                    // find all files matching regex
* DirExplorerT.h, DirExplorerT.cpp  // navigate specified dir tree
* Application.h, Application.cpp    // provides defn's for doDir and doFile
* FileSystem.h, FileSystem.cpp      // Directory and Path classes
* StringUtilities.h                 // Title function
* CodeUtilities.h                   // ProcessCmdLine class
*
* Maintenance History:
* --------------------
* ver 1.1 : 25 Jun 2019
* - added ProcessCmdLine to process commandline arguments
* ver 1.0 : 03 Jun 2019
* - first release
*
*/

#include <iostream>
#include "../DirExplorer-Template/Application.h"
#include "../DirExplorer-Template/DirExplorerT.h"
#include "../CppUtilities/CodeUtilities/CodeUtilities.h"

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

void usage()
{
  std::cout << usageMsg();
}


int main(int argc, char* argv[])
{
  ProcessCmdLine pcl(argc, argv);
  pcl.setUsageMessage(usageMsg());
  pcl.process();

  if (pcl.parseError())
  {
    usage();
    return 1;
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
    return 1;
  }

  std::ofstream log;
  if (pcl.logFile() != "")
  {
    log.open(pcl.logFile());
    if (!log.good())
    {
      std::cout << "\n  can't open logfile \"" << pcl.logFile() << "\"\n\n";
      return 1;
    }
    else
    {
      std::cout << "\n  opened logfile \"" << pcl.logFile() << "\"\n";
    }
  }

  std::string path = pcl.path();
  DirExplorerT<Application> de(path);
  de.recurse(true);
  for (auto patt : pcl.patterns())
    de.addPattern(patt);
  de.hideEmptyDirectories(true);
  de.app().searchText(pcl.regex());
  if (pcl.hasOption('H'))
    de.app().hideDirNoMatch();
  if (pcl.logFile() != "")
    de.app().logFile(pcl.logFile());
  de.search();

  std::cout << "\n\n";
}


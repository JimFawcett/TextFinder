#pragma once
/////////////////////////////////////////////////////////////////////
// DirExplorerT.h - Template-based directory explorer              //
// ver 1.3                                                         //
//-----------------------------------------------------------------//
// Jim Fawcett (c) copyright 2015                                  //
// All rights granted provided this copyright notice is retained   //
//-----------------------------------------------------------------//
// Jim Fawcett, Emeritus Teaching Professor, Syracuse University   //
/////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* DirExplorerT provides a class, of the same name, that executes a
* depth first search of a directory tree rooted at a specified path.
* Each time it enters a directory, it invokes its member function
* doDir, and for every file in that directory, it invokes doFile.
*
* We call this a "Template Directory Explorer" because, it carries
* out its assigned responsibilities well, and allows the using
* application to modify what the doDir and doFiles do, by using
* a template type parameter to supply those methods.
* This is an improvement over DirExplorerN because the application
* does not need to change any part of the DirExplorerT class.
*
* Required Files:
* ---------------
* DirExplorerT.h, DirExplorerT.cpp
* Application.h, Application.cpp    // provides defn's for doDir and doFile
* FileSystem.h, FileSystem.cpp      // Directory and Path classes
* StringUtilities.h                 // Title function
* CodeUtilities.h                   // ProcessCmdLine class
*
* Maintenance History:
* --------------------
* ver 1.3 : 04 Aug 2019
* - added Utilities::ProcessCmdLine pcl data member
* - removed states duplicated in pcl
* - modified several member functions to accomodate this change
* ver 1.2 : 31 Jul 2019
* - changed hidding code
* ver 1.1 : 16 Aug 2018
* - made no recursion default, added option /s for recursion
* ver 1.0 : 11 Aug 2018
* - first release
*
*/
#include <vector>
#include "../FileSystem/FileSystem.h"
#include "../Application-SingleThread/Application.h"
#include "../CppUtilities/CodeUtilities/CodeUtilities.h"

namespace FileSystem
{
  template<typename App>
  class DirExplorerT
  {
  public:
    using Pattern = std::string;
    using Patterns = std::vector<std::string>;

    static std::string version() { return "ver 1.3"; }

    DirExplorerT();
    DirExplorerT(const std::string& path);

    void path(const std::string& path);
    DirExplorerT<App>& addPattern(const std::string& patt);
    void patterns(const Patterns& patts);
    Patterns& patterns();
    void hideEmptyDirectories(bool hide);
    void maxItems(size_t numFiles);
    void showAllInCurrDir(bool showAllCurrDirFiles);
    bool showAllInCurrDir();
    void recurse(bool doRecurse = true);
    
    void search();
    void find(const std::string& path);
    bool done();

    void showStats();
    size_t fileCount();
    size_t dirCount();

    Application& app() { return app_; }
    Utilities::ProcessCmdLine& pcl();
    void pcl(Utilities::ProcessCmdLine& pcl);

  private:
    Application app_;
    Utilities::ProcessCmdLine pcl_;
    Patterns patterns_;
    bool hideEmptyDir_ = false;
    bool showAll_ = false;      // show files in current dir even if maxItems_ has been exceeded
    size_t dirCount_ = 0;
    size_t fileCount_ = 0;
  };
  //----< return reference to internal pcl instance >----------------

  template<typename App>
  Utilities::ProcessCmdLine& DirExplorerT<App>::pcl()
  {
    return pcl_;
  }
  //----< copy options from pcl arg to internal pcl instance >-------

  template<typename App>
  void DirExplorerT<App>::pcl(Utilities::ProcessCmdLine& pcl)
  {
    for (auto opt : pcl.options())
    {
      pcl_.options()[opt.first] = opt.second;
    }
    for (auto patt : pcl.patterns())
    {
      addPattern(patt);
      pcl_.pattern(patt);
    }
  }
  //----< construct DirExplorerN with default pattern >--------------

  template<typename App>
  DirExplorerT<App>::DirExplorerT()
  {
    patterns_.push_back("*.*");
  }
  //----< construct DirExplorerN with path and default pattern >-----

  template<typename App>
  DirExplorerT<App>::DirExplorerT(const std::string& path)
  {
    pcl_.path(path);
    patterns_.push_back("*.*");
  }
  //----< reset starting path >--------------------------------------

  template <typename App>
  void DirExplorerT<App>::path(const std::string& path)
  {
    pcl_.options()['P'] = path;
  }
  //----< add specified patterns for selecting file names >----------

  template<typename App>
  DirExplorerT<App>& DirExplorerT<App>::addPattern(const std::string& patt)
  {
    if (patterns_.size() == 1 && patterns_[0] == "*.*")
      patterns_.pop_back();
    patterns_.push_back(patt);
    return *this;
  }
  //----< return reference to patterns >-----------------------------

  template<typename App>
  typename DirExplorerT<App>::Patterns& DirExplorerT<App>::patterns()
  {
    return patterns_;
  }
  //----< copy a specified set of patterns >-------------------------

  template<typename App>
  void DirExplorerT<App>::patterns(const Patterns& patts)
  {
    for (auto pat : patts)
    {
      addPattern(pat);
    }
  }
  //----< set option to hide empty directories >---------------------

  template<typename App>
  void DirExplorerT<App>::hideEmptyDirectories(bool hide)
  {
    hideEmptyDir_ = hide;
  }
  //----< set the maximum number of files to display >---------------

  template<typename App>
  void DirExplorerT<App>::maxItems(size_t numFiles)
  {
    pcl_.options()['n'] = std::to_string(numFiles);
    app_.maxItems(numFiles);
  }
  //----< stop display before showing all files in dir >-------------

  template<typename App>
  void DirExplorerT<App>::showAllInCurrDir(bool showAllCurrDirFiles)
  {
    showAll_ = showAllCurrDirFiles;
  }
  //----< stop display before showing all files in dir? >------------

  template<typename App>
  bool DirExplorerT<App>::showAllInCurrDir()
  {
    return showAll_;
  }
  //----< set option to recusively walk dir tree >-------------------

  template<typename App>
  void DirExplorerT<App>::recurse(bool doRecurse)
  {
    if (doRecurse)
      pcl_.options()['r'] = "";
    else
      pcl_.options().erase('r');
  }
  //----< start Depth First Search at path in options >--------------

  template<typename App>
  void DirExplorerT<App>::search()
  {
    if (showAllInCurrDir())
      app_.showAllInCurrDir(true);

    find(pcl_.options()['P']);
  }
  //----< search for directories and their files >-------------------
  /*
    Recursively finds all the dirs and files on the specified path,
    executing doDir when entering a directory and doFile when finding a file
  */
  template<typename App>
  void DirExplorerT<App>::find(const std::string& path)
  {
    ++dirCount_;
    if (done())  // stop searching
      return;

    bool hasFiles = false;
    std::string fpath = FileSystem::Path::getFullFileSpec(path);
    if (!hideEmptyDir_)
      app_.doDir(fpath);

    for (auto patt : patterns_)
    {
      std::vector<std::string> files = FileSystem::Directory::getFiles(fpath, patt);
      if (!hasFiles && hideEmptyDir_)
      {
        if (files.size() > 0)
        {
          app_.doDir(fpath);
          hasFiles = true;
        }
      }
      for (auto f : files)
      {
        ++fileCount_;
        app_.doFile(f);
      }
    }

    if (done())  // stop recursion
      return;

    std::vector<std::string> dirs = FileSystem::Directory::getDirectories(fpath);
  
    for (auto d : dirs)
    {
      if (d == "." || d == "..")
        continue;
      std::string dpath = fpath + "\\" + d;
      if (pcl_.hasOption('s'))
      {
        find(dpath);
      }
      else
      {
        app_.doDir(dpath);
      }
    }
  }
  //----< return number of files processed >-------------------------

  template<typename App>
  size_t DirExplorerT<App>::fileCount()
  {
    return fileCount_;
  }
  //----< return number of directories processed >-------------------

  template<typename App>
  size_t DirExplorerT<App>::dirCount()
  {
    return dirCount;
  }
  //----< show final counts for files and dirs >---------------------

  template<typename App>
  void DirExplorerT<App>::showStats()
  {
    std::cout << "\n  Processed " << fileCount_ << " files";
    std::cout << "\n  Processed " << dirCount_ << " directories";
  }

  template<typename App>
  bool DirExplorerT<App>::done()
  {
    if(pcl_.hasOption('n'))
      return dirCount_ >= stoul(pcl_.options()['n']);
    return false;
  }
}
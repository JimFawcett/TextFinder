#pragma once
/////////////////////////////////////////////////////////////////////
// ITextFinder.h - interface used by DirExplorerT                  //
// ver 1.3                                                         //
//-----------------------------------------------------------------//
// Jim Fawcett (c) copyright 2019                                  //
// All rights granted provided this copyright notice is retained   //
//-----------------------------------------------------------------//
// Jim Fawcett, CSE687 - Object Oriented Design, Fall 2018         //
/////////////////////////////////////////////////////////////////////

#include <string>

struct ITextFinder
{
  ~ITextFinder() {}
  virtual bool searchFile(const std::string& searchfile) = 0;
};
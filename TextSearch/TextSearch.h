#pragma once
/////////////////////////////////////////////////////////////////////
// TextSearch.h - Find text in file                                //
// ver 1.0                                                         //
//-----------------------------------------------------------------//
// Jim Fawcett (c) copyright 2019                                  //
// All rights granted provided this copyright notice is retained   //
//-----------------------------------------------------------------//
// Jim Fawcett, Emeritus Teaching Professor, Syracuse University   //
/////////////////////////////////////////////////////////////////////

#include <string>
#include <fstream>

class TextSearch
{
public:
  ~TextSearch();
  bool open(const std::string& fileSpec);
  bool find(const std::string& regexStr);
  void close();
private:
  std::ifstream in_;
};

/////////////////////////////////////////////////////////////////////
// TextSearch.cpp - Find text in file                              //
// ver 1.0                                                         //
//-----------------------------------------------------------------//
// Jim Fawcett (c) copyright 2019                                  //
// All rights granted provided this copyright notice is retained   //
//-----------------------------------------------------------------//
// Jim Fawcett, Emeritus Teaching Professor, Syracuse University   //
/////////////////////////////////////////////////////////////////////

#include "TextSearch.h"
#include "../FileSystem/FileSystem.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>

bool TextSearch::open(const std::string& fileSpec)
{
  std::string fullSpec = FileSystem::Path::getFullFileSpec(fileSpec);
  in_.open(fullSpec);
  if (in_.good())
  {
    return true;
  }
  std::cout << "\n  failed to open \"" << fullSpec << "\"";
  return false;
}
bool TextSearch::find(const std::string& regexStr)
{
  std::regex re(regexStr);
  std::ostringstream contents;
  contents << in_.rdbuf();
  in_.close();
  return std::regex_search(contents.str(), re);
}

void TextSearch::close()
{
  in_.close();
}

TextSearch::~TextSearch()
{
  in_.close();
}

#ifdef TEST_TEXTSEARCH
int main()
{
  std::cout << "\n  Testing TextSearch";
  std::cout << "\n ====================";

  //std::string regexStr = "tSearch.h|foobar";
  //std::string source = "../TextSearch/TextSearch.h";
  //std::regex re(regexStr);
  //if (regex_search(source, re))
  //  std::cout << "\n  regex found a match with \"" << regexStr << "\"";
  //else
  //  std::cout << "\n  regex did not find a match with \"" << regexStr << "\"";
  //std::cout << std::endl;

  std::string fileSpec = "../TextSearch/TextSearch.h";
  TextSearch ts;
  ts.open(fileSpec);
  if (ts.find("class TextSearch"))
    std::cout << "\n  " << fileSpec << " contains \"class TextSearch\"";
  else
    std::cout << "\n  " << fileSpec << " does not contain \"class TextSearch\"";

  if (ts.find("class Foobar"))
    std::cout << "\n  " << fileSpec << " contains \"class Foobar\"";
  else
    std::cout << "\n  " << fileSpec << " does not contain \"class Foobar\"";

  std::cout << "\n\n";
}
#endif


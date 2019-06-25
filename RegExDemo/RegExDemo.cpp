/////////////////////////////////////////////////////////////////////
// RegExDemo.cpp - Demonstrate searching for regex matches         //
// ver 1.0                                                         //
//-----------------------------------------------------------------//
// Jim Fawcett (c) copyright 2019                                  //
// All rights granted provided this copyright notice is retained   //
//-----------------------------------------------------------------//
// Jim Fawcett, CSE687 - Object Oriented Design, Fall 2018         //
/////////////////////////////////////////////////////////////////////
/*
*  Regex Reference: https://cs.lmu.edu/~ray/notes/regex/
*/
#include <iostream>
#include <regex>

int main()
{
  std::cout << "\n  Demonstrating Regular Expressions";
  std::cout << "\n ===================================\n";

  std::string source = "../TextSearch/TextSearch.h";
  std::cout << "\n  text source = \"" << source << "\"" << std::endl;

  std::string regexStr = std::string("tSearch.h|foobar|[.][.]/TextS");
  std::regex re(regexStr);
  if (std::regex_search(source, re))
    std::cout << "\n  regex found a match with \"" << regexStr << "\"";
    //std::cout << "\n  regex found a match with \"" << R"(tSearch.h|foobar|[.][.]/TextS)" << "\"";
  else
    std::cout << "\n  regex did not find a match with \"" << regexStr << "\"";
  std::cout << std::endl;

  std::smatch matches;
  std::cout << "\n  The following matches were found:";
  while (std::regex_search(source, matches, re)) {
    std::cout << "\n\n  source = \"" << source << "\"";
    for (auto m : matches)
      std::cout << "\n  " << m;
    source = matches.suffix().str();
  }
  std::cout << "\n\n";
  return 0;
}


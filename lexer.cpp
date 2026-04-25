//
// Created by Dom Binks on 16/04/2026.
//

#include <cstdio>
#include "lexer.h"

int gettok() {
  int LastChar = ' ';

  while (isspace(LastChar))
    LastChar = getchar();

  if (isalpha(LastChar)) {
    IdentifierStr = static_cast<char>(LastChar);
    while (isalnum(LastChar = getchar()))
      IdentifierStr += static_cast<char>(LastChar);

    if (IdentifierStr == "def")
      return tok_def;

    if (IdentifierStr == "extern")
      return tok_extern;

    return tok_identifier;
  }

  if (isdigit(LastChar) || LastChar == '.') {
    std::string NumStr;
    do {
      NumStr += static_cast<char>(LastChar);
      LastChar = getchar();
    } while (isdigit(LastChar) || LastChar == '.');

      NumVal = strtod(NumStr.c_str(), nullptr);
      return tok_number;
  }

  if (LastChar == '#') {
    do
      LastChar = getchar();
    while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

    if (LastChar != EOF)
      return gettok();
  }

  if (LastChar == EOF)
    return tok_eof;

  const int ThisChar = LastChar;
  LastChar = getchar();
  return ThisChar;
}

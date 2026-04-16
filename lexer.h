//
// Created by Dom Binks on 16/04/2026.
//

#ifndef KALEIDOSCOPE_TUTORIAL_LEXER_H
#define KALEIDOSCOPE_TUTORIAL_LEXER_H

#include <string>

enum Token {
  tok_eof = -1,

  // commands
  tok_def = -2,
  tok_extern = -3,

  // primary
  tok_identifier = -4,
  tok_number = -5,
};

static std::string IdentifierStr;
static double NumVal;
static int gettok();

#endif //KALEIDOSCOPE_TUTORIAL_LEXER_H

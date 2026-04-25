//
// Created by Dom Binks on 16/04/2026.
//

#include <iostream>
#include "lexer.h"
#include "parser.h"

int main() {
  BinOpPrecedence['<'] = 10;
  BinOpPrecedence['+'] = 20;
  BinOpPrecedence['-'] = 20;
  BinOpPrecedence['*'] = 40;

  //auto LHS = std::make_unique<VariableExprAST>("x");
  //auto RHS = std::make_unique<VariableExprAST>("y");
  //auto Result = std::make_unique<BinaryExprAST>('+', std::move(LHS),
  //                                              std::move(RHS));

  getNextToken();
  bool loop = true;
  while (loop) {
    switch (CurTok) {
    case tok_eof:
      loop = false;
    case ';':
      getNextToken();
      break;
    case tok_def:
      std::cout << "function definition" << std::endl;
      ParseDefinition();
      break;
    case tok_extern:
      std::cout << "function extern" << std::endl;
      ParseExtern();
      break;
    default:
      std::cout << "top level expression" << std::endl;
      ParseTopLevelExpression();
      break;
    }
  }

  return 0;
}
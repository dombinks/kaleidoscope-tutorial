//
// Created by Dom Binks on 16/04/2026.
//

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

  return 0;
}
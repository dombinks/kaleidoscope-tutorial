//
// Created by Dom Binks on 19/04/2026.
//

#ifndef KALEIDOSCOPE_TUTORIAL_PARSER_H
#define KALEIDOSCOPE_TUTORIAL_PARSER_H

#include <memory>
#include <map>
#include "ast.h"

class ExprAST;
class PrototypeAST;

inline int CurTok;
inline std::map<char, int> BinOpPrecedence;

int getNextToken();
std::unique_ptr<ExprAST> LogError(const char *);
std::unique_ptr<PrototypeAST> LogErrorP(const char *);
std::unique_ptr<ExprAST> ParseNumberExpr();
std::unique_ptr<ExprAST> ParseParenExpr();
std::unique_ptr<ExprAST> ParseIdentifierExpr();
std::unique_ptr<ExprAST> ParsePrimary();
int GetTokPrecedence();
std::unique_ptr<ExprAST> ParseExpression();
std::unique_ptr<ExprAST> ParseBinOpRHS(int, std::unique_ptr<ExprAST>);
std::unique_ptr<PrototypeAST> ParsePrototype();
std::unique_ptr<FunctionAST> ParseDefinition();
std::unique_ptr<PrototypeAST> ParseExtern();
std::unique_ptr<FunctionAST> ParseTopLevelExpression();

#endif //KALEIDOSCOPE_TUTORIAL_PARSER_H

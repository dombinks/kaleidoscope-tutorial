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

static int CurTok;
static std::map<char, int> BinOpPrecedence;

static int getNextToken();
std::unique_ptr<ExprAST> LogError(const char *);
std::unique_ptr<PrototypeAST> LogErrorP(const char *);
static std::unique_ptr<ExprAST> ParseNumberExpr();
static std::unique_ptr<ExprAST> ParseParenExpr();
static std::unique_ptr<ExprAST> ParseIdentifierExpr();
static std::unique_ptr<ExprAST> ParsePrimary();
static int GetTokPrecedence();
static std::unique_ptr<ExprAST> ParseExpression();
static std::unique_ptr<ExprAST> ParseBinOpRHS(int, std::unique_ptr<ExprAST>);

#endif //KALEIDOSCOPE_TUTORIAL_PARSER_H

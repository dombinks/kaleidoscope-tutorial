//
// Created by Dom Binks on 19/04/2026.
//

#include <iostream>
#include "lexer.h"
#include "ast.h"
#include "parser.h"


int getNextToken() {
  return CurTok = gettok();
}

std::unique_ptr<ExprAST> LogError(const char *Str) {
  std::cerr << "Error: " << Str << std::endl;
  return nullptr;
}

std::unique_ptr<PrototypeAST> LogErrorP(const char *Str) {
  LogError(Str);
  return nullptr;
}

std::unique_ptr<ExprAST> ParseNumberExpr() {
  std::unique_ptr<NumberExprAST> Result = std::make_unique<NumberExprAST>(NumVal);
  getNextToken();
  return std::move(Result);
}

std::unique_ptr<ExprAST> ParseParenExpr() {
  getNextToken();
  std::unique_ptr<ExprAST> V = ParseExpression();
  if (!V)
    return nullptr;

  if (CurTok != ')')
    return LogError("expected ')'");

  getNextToken();
  return V;
}

std::unique_ptr<ExprAST> ParseIdentifierExpr() {
  std::string IdName = IdentifierStr;

  getNextToken();

  if (CurTok != '(')
    return std::make_unique<VariableExprAST>(IdName);

  getNextToken();
  std::vector<std::unique_ptr<ExprAST>> Args;
  if (CurTok != ')') {
    while (true) {
      if (std::unique_ptr<ExprAST> Arg = ParseExpression())
        Args.push_back(std::move(Arg));
      else
        return nullptr;

      if (CurTok == ')')
        break;

      if (CurTok != ',')
        return LogError("expected ')' or ',' in argument list");

      getNextToken();
    }
  }

  getNextToken();

  return std::make_unique<CallExprAST>(IdName, std::move(Args));
}

std::unique_ptr<ExprAST> ParsePrimary() {
  switch (CurTok) {
    default:
      return LogError("unknown token when expecting an expression");
    case tok_identifier:
      return ParseIdentifierExpr();
    case tok_number:
      return ParseNumberExpr();
    case '(':
      return ParseParenExpr();
  }
}

int GetTokPrecedence() {
  if (!isascii(CurTok))
    return -1;

  int TokPrec = BinOpPrecedence[CurTok];
  if (TokPrec <= 0)
    return -1;

  return TokPrec;
}

std::unique_ptr<ExprAST> ParseExpression() {
  std::unique_ptr<ExprAST> LHS = ParsePrimary();
  if (!LHS)
    return nullptr;

  return ParseBinOpRHS(0, std::move(LHS));
}

std::unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS) {
  while (true) {
    int TokPrec = GetTokPrecedence();

    if (TokPrec < ExprPrec)
      return LHS;

    int BinOp = CurTok;
    getNextToken();

    std::unique_ptr<ExprAST> RHS = ParsePrimary();
    if (!RHS)
      return nullptr;

    int NextPrec = GetTokPrecedence();
    if (TokPrec < NextPrec) {
      RHS = ParseBinOpRHS(TokPrec+1, std::move(RHS));
      if (!RHS)
        return nullptr;
    }

    LHS = std::make_unique<BinaryExprAST>(BinOp, std::move(LHS), std::move(RHS));
  }
}

std::unique_ptr<PrototypeAST> ParsePrototype() {
  if (CurTok != tok_identifier)
    return LogErrorP("expected function name in prototype");

  std::string FnName = IdentifierStr;
  getNextToken();

  if (CurTok != '(')
    return LogErrorP("expected '(' in prototype");

  std::vector<std::string> ArgNames;
  while (getNextToken() == tok_identifier)
    ArgNames.push_back(IdentifierStr);

  if (CurTok != ')')
    return LogErrorP("expected ')' in prototype");

  getNextToken();

  return std::make_unique<PrototypeAST>(FnName, std::move(ArgNames));
}

std::unique_ptr<FunctionAST> ParseDefinition() {
  getNextToken();
  std::unique_ptr<PrototypeAST> Proto = ParsePrototype();
  if (!Proto)
    return nullptr;

  if (std::unique_ptr<ExprAST> Expr = ParseExpression())
    return std::make_unique<FunctionAST>(std::move(Proto), std::move(Expr));

  return nullptr;
}

std::unique_ptr<PrototypeAST> ParseExtern() {
  getNextToken();
  return ParsePrototype();
}

std::unique_ptr<FunctionAST> ParseTopLevelExpression() {
  if (std::unique_ptr<ExprAST> Expr = ParseExpression()) {
	std::string FnName = "__anon_expr";
    std::unique_ptr<PrototypeAST> Proto = std::make_unique<PrototypeAST>(FnName, std::vector<std::string>());
    return std::make_unique<FunctionAST>(std::move(Proto), std::move(Expr));
  }

  return nullptr;
}
// lexer interface (function declarations, enums)

// headers
#pragma once
#include <string>

// GOAL: process a text file and recognize what it says
//   - lexer == scanner
//   - break input up into tokens
//   - each token has a token code and possibly metadata (ex. numerical val of a number)

// (1) token codes
// denote special token codes for some constructs & keywords
// all other characters will retain ascii code [0-255]
enum Token {
  tok_eof = -1,

  // commands
  tok_def = -2,
  tok_extern = -3,

  // primary
  tok_identifier = -4,
  tok_number = -5,
};

// (2) metadata
static string IdentifierStr;  // corresponds to tok_identifier
static double NumVal;         // corresponds to tok_number

int gettok();  // declare func in .cc
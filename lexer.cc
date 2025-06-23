// lexer implementation (gettok, token logic)

// headers
#include "lexer.h"
#include <cctype>
#include <cstdio>

// token metadata
std::string IdentifierStr;
double NumVal;

// return the next token from standard input
static int gettok() {
  static int LastChar = ' ';

  // skip whitespace
  while (isspace(LastChar))
    LastChar = getchar();

    // identifier: [a-zA-Z][a-zA-Z0-9]*
    // saw [a-zA-Z]...
    if (isalpha(LastChar)) {
      IdentifierStr = LastChar;
      // processing corresponding [a-zA-Z0-9]*
      while (isalnum((LastChar = getchar())))
        IdentifierStr += LastChar;

      // reserved keywords
      if (IdentifierStr == "def")
        return tok_def;
      if (IdentifierStr == "extern")
        return tok_extern;

      // identifier code, with metadata stored in IdentifierStr
      return tok_identifier;
    }

    // number: [0-9.]+ --> 0 | [1-9][0-9]* (.[])?
    // TODO: finish the regex and write a corresponding loop
    if (isdigit(LastChar) || LastChar == '.') {
      std::string NumStr;
      do {
        NumStr += LastChar;
        LastChar = getchar();
      } while (isdigit(LastChar) || LastChar == '.');

      NumVal = strtod(NumStr.c_str(), 0);
      return tok_number;
    }

    // ignore comments until end of line
    if (LastChar == '#') {
      // skip to the end of the line
      do
        LastChar = getchar();
      while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

      // return the next token
      if (LastChar != EOF)
        return gettok();
    }

    // end of file
    if (LastChar == EOF)
        return tok_eof;

    // otherwise, just return the character as its ascii value
    int ThisChar = LastChar;
    LastChar = getchar();
    return ThisChar;
}
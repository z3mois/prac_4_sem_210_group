#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <string>
#include <ctype.h>
#include <algorithm>

using namespace std;


enum TypeOfLex {
  LEX_NULL,                                                               /*0*/
  LEX_AND,   LEX_BREAK,  LEX_BOOL,     LEX_DO,    LEX_ELSE,    LEX_IF,    /*6*/
  LEX_FALSE, LEX_INT,    LEX_NOT,      LEX_OR,    LEX_PROGRAM, LEX_READ,  /*12*/
  LEX_THEN,  LEX_TRUE,   LEX_WHILE,    LEX_WRITE, LEX_STRING,  LEX_FOR,   /*18*/
  LEX_GOTO,  LEX_STRUCT,                                                  /*20*/
  LEX_FIN,                                                                /*21*/
  LEX_SEMICOLON, LEX_COMMA,   LEX_COLON,  LEX_ASSIGN,   LEX_LPAREN,       /*26*/
  LEX_RPAREN,    LEX_EQ,      LEX_LSS,    LEX_GTR,      LEX_PLUS,         /*31*/
  LEX_MINUS,     LEX_LBRACE,  LEX_RBRACE, LEX_TIMES,    LEX_SLASH,        /*36*/
  LEX_LEQ,       LEX_NEQ,     LEX_GEQ,    LEX_POINT,                      /*40*/
  LEX_NUM,                                                                /*41*/
  LEX_ID,                                                                 /*42*/
  LEX_STR,                                                                /*43*/
  POLIZ_LABEL,                                                            /*44*/ 
  POLIZ_ADDRESS,                                                          /*45*/
  POLIZ_GO,                                                               /*46*/
  POLIZ_FGO,                                                              /*47*/
  POLIZ_MINUS,                                                            /*48*/
  LEX_OBJECT                                                              /*49*/
};


class Lex {
  private:
    TypeOfLex  typeOfLex_;
    int        value_;
    int        value2_;
    string     str_;
  public:
    Lex (TypeOfLex t = LEX_NULL, int v = 0, int v2 = -1, string s = ""):
        typeOfLex_(t), value_(v), value2_(v2), str_(s) {}
    TypeOfLex getType () const {
      return typeOfLex_;
    }
    int getValue () const {
      return value_;
    }
    int getValue2() const {
      return value2_;
    }
    string getStr () const {
      return str_;
    }
    Lex (const Lex& lex) {
      typeOfLex_ = lex.typeOfLex_;
      value_ = lex.value_;
      value2_ = lex.value2_;
      str_ = lex.str_;
    }
    Lex& operator= (const Lex& lex) {
      if (this == &lex) {
        return *this;
      }
      typeOfLex_ = lex.typeOfLex_;
      value_ = lex.value_;
      value2_ = lex.value2_;
      str_ = lex.str_;
      return *this;
    }
    friend ostream& operator<< (ostream& out, Lex lex);
};


////////////////////////////////////////////////////////////////

// заполняем TID
class Ident { 
  private:
    string     name_;
    bool       declare_;
    TypeOfLex  typeOfLex_;
    bool       assign_;
    int        value_;
    string     str_;
    bool       isStruct_;
    bool       isObject_;
    bool       isLabel_;
    int        valueTypeStruct_;
  public:
    Ident () {
      valueTypeStruct_ = -1;
      value_ = 0;
      str_ = "";
      declare_ = false;
      assign_  = false;
      isStruct_ = false;
      isObject_ = false;
      isLabel_  = false;
    }
    Ident (const string n) {
      name_ = n;
      valueTypeStruct_ = -1;
      value_ = 0;
      str_ = "";
      declare_ = false;
      assign_ = false;
      isStruct_ = false;
      isObject_ = false;
      isLabel_  = false;
    }
    bool operator==(const string& s) const {
      return name_ == s;
    }
    string getName () const {
      return name_;
    }
    bool getDeclare () const {
      return declare_;
    }
    void putDeclare () {
      declare_ = true;
    }
    TypeOfLex getType () const {
     return typeOfLex_;
    }
    void putType (TypeOfLex type) {
      typeOfLex_ = type;
    }
    bool getAssign () const {
      return assign_;
    }
    void putAssign () {
      assign_ = true;
    }
    int getValue () const {
      return value_;
    }
    string getStr() const {
      return str_;
    }
    void putValue (int v) {
      value_ = v;
    }
    void putValue (string s) {
      str_ = s;
    }
    bool isStruct() const {
      return isStruct_;
    }
    void putIsStruct() {
      isStruct_ = true;
    }
    void putIsObject() {
      isObject_ = true;
    }
    bool isObject() const {
      return isObject_;
    }
    void putIsLabel() {
      isLabel_ = true;
    }
    bool isLabel() const {
      return isLabel_;
    }
    void putValueStruct(int i) {
      valueTypeStruct_ = i;
    }
    int getValueStruct() const {
      return valueTypeStruct_;
    }
    Ident& operator= (Ident& ident);
    void outInfo ();
    vector<Ident> tid;
};

void Ident::outInfo () {
  cout << "name: "                 << name_              << endl;
  cout << "declare: "              << declare_           << endl;
  cout << "typeOfLex: "            << typeOfLex_         << endl;
  cout << "assign: "               << assign_            << endl;
  cout << "value: "                << value_             << endl;
  cout << "isStruct: "             << isStruct_          << endl;
  cout << "isObject: "             << isObject_          << endl;
  cout << "isLabel: "              << isLabel_           << endl;
  cout << "value type of struct: " << valueTypeStruct_   << endl;
  if (isObject_ || isStruct_) {
    vector<Ident>::iterator p = tid.begin();
    while ( p != tid.end() ) {
      cout << "\ttype: "     << (*p).getType()    << endl;
      cout << "\tname: "     << (*p).getName()    << endl;
      cout << "\tdeclared: " << (*p).getDeclare() << endl;
      cout << endl;
      ++p;
    }
  }
  cout << endl << endl;
}

Ident& Ident::operator= (Ident& ident) {
  if (this == &ident) {
    return *this;
  }
  if (tid.empty() == 0) {
    tid.clear();
  }
  vector<Ident>::iterator p = ident.tid.begin();
  while (p != ident.tid.end()) {
    tid.push_back(*p);
    ++p;
  }
  return *this;
}


//////////////////////////////////////////////////////////////////


class Scanner {
  private:
    FILE* file_;
    char  currSym_;
    int look (const string buf, const char** list);
    void gc () {
      currSym_ = fgetc(file_);
    }
  public:
    Lex getLex (vector<Ident>& tid);
    Scanner (const char* program);
    void stepBack (int i) {
      fseek (file_, -i, SEEK_CUR);
    }
    static const char*  TW[];
    static const char*  TD[];
    ~Scanner () { 
      fclose(file_); 
    }
};


int Scanner::look (const string buf, const char** list) {
  int i = 0;
  while (list[i]) {
    if (buf == list[i])
      return i;
    ++i;
  }
  return 0;
}


Scanner::Scanner (const char* program) {
  file_ = fopen (program, "r");
  if (file_ == NULL) 
    throw "Wrong name of file!";
}


const char* Scanner::TW[] =  // Word service table
{
  "",         // 0
  "and",      // 1
  "break",    // 2
  "bool",     // 3
  "do",       // 4
  "else",     // 5
  "if",       // 6
  "false",    // 7
  "int",      // 8
  "not",      // 9
  "or",       // 10
  "program",  // 11
  "read",     // 12
  "then",     // 13
  "true",     // 14
  "while",    // 15
  "write",    // 16
  "string",   // 17
  "for",      // 18
  "goto",     // 19
  "struct",   // 20
  NULL
};


const char* Scanner::TD[] =  // Delimiter table
{
  "@",  // 0
  ";",  // 1
  ",",  // 2
  ":",  // 3
  "=",  // 4
  "(",  // 5
  ")",  // 6
  "==", // 7
  "<",  // 8
  ">",  // 9
  "+",  // 10
  "-",  // 11
  "{",  // 12
  "}",  // 13
  "*",  // 14
  "/",  // 15
  "<=", // 16
  "!=", // 17
  ">=", // 18
  ".",  // 19
  NULL
};


vector<Ident> TID;   // Identifier table

// заполняем TID
int putIdent (const string& buf, vector<Ident>& tid) {
  vector<Ident>::iterator k;
  if ( (k = find(tid.begin(), tid.end(), buf)) != tid.end() )
    return k - tid.begin();
  tid.push_back(Ident(buf));
  return tid.size() - 1;
}


ostream& operator<< (ostream& out, Lex lex) {
  string s;
  if ( lex.typeOfLex_ <= 20 )
    s = Scanner::TW[lex.typeOfLex_];

  else if ((lex.typeOfLex_ >= 21) && (lex.typeOfLex_ <= 40))
    s = Scanner::TD[lex.typeOfLex_ - 21];

  else if (lex.typeOfLex_ == 41)
    s = "NUM";

  else if (lex.typeOfLex_ == 42)
    s = TID [lex.value_].getName();

  else if (lex.typeOfLex_ == 43)
    s = "STR";

  else if (lex.typeOfLex_ == 44)
    s = "Label";
  
  else if (lex.typeOfLex_ == 45)
    s = "Addr";
  
  else if (lex.typeOfLex_ == 46)
    s = "!";

  else if (lex.typeOfLex_ == 47)
    s = "!F";

  else if (lex.typeOfLex_ == 48)
    s = "minus";
  
  else if (lex.typeOfLex_ == 49)
    s = "OBJECT";

  else
    throw lex;

  if (lex.str_ != "") {
    out << '(' << s << ',' << lex.str_ << ");" << endl;
  }
  else if (lex.value2_ != -1) {
    out << '(' << s << ',' << lex.value_ << ',' << lex.value2_ << ");" << endl;
  }
  else
    out << '(' << s << ',' << lex.value_ << ");" << endl;
  return out;
}


Lex Scanner::getLex (vector<Ident>& tid) {
  enum state { H, IDENT, NUMB, COM, ALE, NEQ, COM1, COM2, STR };
  int d, j;
  string buf;
  state CS = H;
  do {
    gc();
    if ( currSym_ == EOF && CS != H)
      throw "Unclosed comment or string!";
    else if (currSym_ == EOF)
      return (Lex(LEX_FIN));
    switch(CS) {
        /////////////////  State H  /////////////////////
        case H:   if ( currSym_ == ' '  || currSym_ == '\n' || 
                       currSym_ == '\r' || currSym_ == '\t' );
                  else if ( isalpha(currSym_) ) {
                    buf.push_back(currSym_);
                    CS = IDENT;
                  }
                  else if ( isdigit(currSym_) ) {
                    d = currSym_ - '0';
                    CS = NUMB;
                  }
                  else if ( currSym_ == '/' ) {
                    CS = COM1;
                  }
                  else if ( currSym_ == '=' || currSym_ == '<' || currSym_ == '>' ) {
                    buf.push_back(currSym_);
                    CS = ALE;
                  }
                  else if (currSym_ == '!') {
                    buf.push_back(currSym_);
                    CS = NEQ;
                  }
                  else if (currSym_ == '\"') {
                    CS = STR;
                  }
                  else {
                    buf.push_back(currSym_);
                    if ( (j = look ( buf, TD)) ) {
                      return Lex ( (TypeOfLex)(j+(int)LEX_FIN), j );
                    }
                    else
                      throw currSym_;
                  }
                  break;
      /////////////////  State STR /////////////////////
      case STR:   if ( currSym_ != '\"') {
                    buf.push_back(currSym_);
                  }
                  else {
                    return Lex (LEX_STR, 0,-1, buf);
                  }
                  break;
      /////////////////  State IDENT  /////////////////////
      case IDENT: if ( isalpha(currSym_) || isdigit(currSym_) ) {
                    buf.push_back(currSym_);
                  }
                  else {
                    ungetc (currSym_, file_);
                    if ( (j = look (buf, TW)) ){
                      return Lex ((TypeOfLex)j, j);
                    }
                    else {
                      j = putIdent(buf, tid);
                      return Lex (LEX_ID, j);
                    }
                  }
                  break;
      /////////////////  State NUMB /////////////////////
      case NUMB:  if ( isdigit(currSym_) ) {
                   d = d * 10 + (currSym_ - '0');
                  }
                  else {
                    ungetc (currSym_, file_);
                    return Lex ( LEX_NUM, d);
                  }
                  break;
      /////////////////  State COM1  /////////////////////
      case COM1:  if ( currSym_ == '*' )
                    CS = COM;
                  else {
                    ungetc (currSym_, file_);
                    return Lex (LEX_SLASH, 15);
                  }
                  break;
      /////////////////  State COM2 /////////////////////
      case COM2:  if ( currSym_ == '/')
                    CS = H;
                  else if ( currSym_ != '*')
                    CS = COM;

                  break;
      /////////////////  State COM  /////////////////////
      case COM:   if ( currSym_ == '*' ) {
                    CS = COM2;
                  }
                  break;
      /////////////////  State ALE  /////////////////////
      case ALE:   if ( currSym_ == '=') {
                    buf.push_back(currSym_);
                    j = look ( buf, TD );
                    return Lex ( (TypeOfLex)(j+(int)LEX_FIN), j);
                  }
                  else {
                    ungetc (currSym_, file_);
                    j = look ( buf, TD );
                    return Lex ( (TypeOfLex)(j+(int)LEX_FIN), j );
                  }
                  break;
      /////////////////  State NEQ  /////////////////////
      case NEQ:   if (currSym_ == '=') {
                    buf.push_back(currSym_);
                    j = look ( buf, TD );
                    return Lex ( LEX_NEQ, j );
                  }
                  else
                    throw '!';
                  break;
    }
  } while (true);
}


int main(int argc, char** argv) {
  try {
    Scanner              scanner_(argv[1]);
    Lex                  currLex_;
    TypeOfLex            currType_;
    int                  currValue_;
    do {
    currLex_ = scanner_.getLex(TID);
    currType_ = currLex_.getType();
    currValue_ = currLex_.getValue();
    cout << currLex_ << endl;
    } while(currType_ != LEX_FIN);
    return 0;
  }
  catch (char c) {
    cout << "unexpected symbol " << c << endl;
    return 1;
  }
  catch (Lex l) {
    cout << "unexpected lexeme" << l << endl;
    return 1;
  }
  catch (const char* c) {
    cout << c << endl;
    return 1;
  }
}

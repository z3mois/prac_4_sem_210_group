#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <string>
#include <ctype.h>
#include <algorithm>

using namespace std;


enum TypeOfLex
{
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


class Lex
{
  public:
    Lex (TypeOfLex t = LEX_NULL, int v = 0, int v2 = -1, string s = ""):
        typeOfLex_(t), value_(v), value2_(v2), str_(s) {}
    TypeOfLex getType () const
    {
      return typeOfLex_;
    }
    int getValue () const
    {
      return value_;
    }
    int getValue2() const
    {
      return value2_;
    }
    string getStr () const
    {
      return str_;
    }
    Lex (const Lex& lex) 
    {
      typeOfLex_ = lex.typeOfLex_;
      value_ = lex.value_;
      value2_ = lex.value2_;
      str_ = lex.str_;
    }
    Lex& operator= (const Lex& lex) 
    {
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
  private:
    TypeOfLex  typeOfLex_;
    int        value_;
    int        value2_;
    string     str_;
};


////////////////////////////////////////////////////////////////


class Ident
{
  public:
    Ident ()
    {
      valueTypeStruct_ = -1;
      value_ = 0;
      str_ = "";
      declare_ = false;
      assign_  = false;
      isStruct_ = false;
      isObject_ = false;
      isLabel_  = false;
    }
    Ident (const string n)
    {
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
    string getName () const
    {
      return name_;
    }
    bool getDeclare () const
    {
      return declare_;
    }
    void putDeclare ()
    {
      declare_ = true;
    }
    TypeOfLex getType () const
    {
     return typeOfLex_;
    }
    void putType (TypeOfLex type)
    {
      typeOfLex_ = type;
    }
    bool getAssign () const
    {
      return assign_;
    }
    void putAssign ()
    {
      assign_ = true;
    }
    int getValue () const
    {
      return value_;
    }
    string getStr() const
    {
      return str_;
    }
    void putValue (int v)
    {
      value_ = v;
    }
    void putValue (string s)
    {
      str_ = s;
    }
    bool isStruct() const
    {
      return isStruct_;
    }
    void putIsStruct()
    {
      isStruct_ = true;
    }
    void putIsObject()
    {
      isObject_ = true;
    }
    bool isObject() const
    {
      return isObject_;
    }
    void putIsLabel()
    {
      isLabel_ = true;
    }
    bool isLabel() const
    {
      return isLabel_;
    }
    void putValueStruct(int i)
    {
      valueTypeStruct_ = i;
    }
    int getValueStruct() const
    {
      return valueTypeStruct_;
    }
    Ident& operator= (Ident& ident);
    void outInfo ();
    vector<Ident> tid;
    

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
};

void Ident::outInfo ()
{
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

Ident& Ident::operator= (Ident& ident) 
{
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


class Scanner
{
  public:
    Lex getLex (vector<Ident>& tid);
    Scanner (const char* program);
    void stepBack (int i) 
    {
      fseek (file_, -i, SEEK_CUR);
    }
    static const char*  TW[];
    static const char*  TD[];
    ~Scanner () 
    { 
      fclose(file_); 
    }
  private:
    FILE* file_;
    char  currSym_;
    int look (const string buf, const char** list);
    void gc ()
    {
      currSym_ = fgetc(file_);
    }
};


int Scanner::look (const string buf, const char** list)
{
  int i = 0;
  while (list[i]) {
    if (buf == list[i])
      return i;
    ++i;
  }
  return 0;
}


Scanner::Scanner (const char* program)
{
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


int putIdent (const string& buf, vector<Ident>& tid)
{
  vector<Ident>::iterator k;
  if ( (k = find(tid.begin(), tid.end(), buf)) != tid.end() )
    return k - tid.begin();
  tid.push_back(Ident(buf));
  return tid.size() - 1;
}


ostream& operator<< (ostream& out, Lex lex)
{
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


Lex Scanner::getLex (vector<Ident>& tid) 
{
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
                  else if ( isalpha(currSym_) ) { // a or A (check on letter)
                    buf.push_back(currSym_);
                    CS = IDENT;
                  }
                  else if ( isdigit(currSym_) ) { // check on number
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


//////////////////////////////////////////////////////////////////


class Parser 
{ 
  public:
    vector<Lex> poliz;
    Parser (const char* program): scanner_ (program) {} 
    void analyze();
  private:
    struct Goto_ {
      int valueLabel_;
      int adressGoto_;
    };
    Lex                  currLex_;
    TypeOfLex            currType_;
    int                  currValue_;
    Scanner              scanner_;
    stack <int>          stInt_;
    stack <TypeOfLex>    stLex_;
    static vector<int>   break_;
    static vector<Goto_> goto_;
    
    void  P();
    void  D2();
    void  D1 (vector<Ident>& tid = TID, bool flagIsStruct = false);
    void  D  (TypeOfLex type, vector<Ident>& tid = TID, bool flagIsStruct = false);
    void  D3 (int value = 0);
    void  B1 (bool isCycle = false);
    void  B (bool isCycle = false);
    void  G (Lex currLex, bool isCycle = false);
    void  E (Lex currLex, bool notObject = false, bool isWrite = false);
    void  S (Lex currLex);
    void  E1();
    void  E2();
    void  E3();
    void  E4();
    void  T();
    void  F (bool isMinus = false, bool isNot = false);
    // semantic
    void  dec (TypeOfLex type, vector<Ident>& tid = TID);
    void  decStruct (int value = 0);
    void  checkId (int currValue);
    void  checkLabel (int value);
    void  checkObject();
    void  eqTypeStruct();
    void  checkOp();
    void  checkNot();
    void  checkMinus();
    void  eqType();
    void  eqBool();
    void  checkIdInRead();
    void  gl (vector<Ident>& tid = TID) 
    {
      currLex_ = scanner_.getLex(tid);
      currType_ = currLex_.getType();
      currValue_ = currLex_.getValue();
    }
};


vector<int>   Parser::break_;
vector<Parser::Goto_> Parser::goto_;


void Parser::analyze () 
{
  gl ();
  P();
  if (currType_ != LEX_FIN) {
    throw currLex_;
  }
  //for_each( poliz.begin(), poliz.end(), [](Lex l){ cout << l; });
  vector <Lex>::iterator q = poliz.begin(); 
  int i = 0;
  while (q != poliz.end()) {
    cout << i << ":  " << *q << endl;
    ++i;
    ++q;
  }
  cout << endl << "Yes!!!" << endl;
  cout << endl << endl;
  /*vector<Ident>::iterator p = TID.begin();
  while (p != TID.end()) {
    (*p).outInfo();
    ++p;
  }*/
}
 

void Parser::P () 
{
  if (currType_ == LEX_PROGRAM) {
    gl();
  }
  else {
    throw currLex_;
  }
  if (currType_ == LEX_LBRACE) {
    gl();
  }
  else {
    throw currLex_;
  }
  D2();
  D1();
  B1();
  if (currType_ == LEX_RBRACE) {
    gl();
  }
  else {
    throw currLex_;
  }
  vector<Goto_>::iterator p = goto_.begin();
  int i;
  while (p != goto_.end()) {
    i = p->valueLabel_;
    if (TID[i].getDeclare() == 0) {
      throw "not declared label in goto";
    }
    poliz[p->adressGoto_] = Lex(POLIZ_LABEL, TID[i].getValue());
    ++p;
  }
}


void Parser::D2 () 
{
  if (currType_ == LEX_STRUCT) {
    gl();
    if (TID[currValue_].getDeclare())
      throw "twice initialization of struct";
    if (currType_ != LEX_ID) {
      throw currLex_;
    }
    TID[currValue_].putDeclare();
    TID[currValue_].putType(LEX_STRUCT);
    int index = currValue_;
    TID[index].putIsStruct();
    gl();
    if (currType_ != LEX_LBRACE) {
      throw currLex_;
    }
    gl();
    D1(TID[index].tid, true);
    if (currType_ != LEX_RBRACE) {
      throw currLex_;
    }
    gl();
    if (currType_ != LEX_SEMICOLON) {
      throw currLex_;
    }
    gl();
    D2();
  }
}

 
void Parser::D1 (vector<Ident>& tid, bool flagIsStruct) 
{ 
  if (currType_ == LEX_INT || currType_ == LEX_STRING || currType_ == LEX_BOOL) {
    TypeOfLex oldType = currType_;
    gl(tid);
    D (oldType, tid, flagIsStruct);
    if (currType_ == LEX_SEMICOLON) {
      gl();
    }
    else {
      throw currLex_;
    }
    D1(tid, flagIsStruct);
  }
  else if ( (currType_ == LEX_ID) && (tid[currValue_].isStruct() == 1) ) {
    int oldValue = currValue_;
    gl(tid);
    D3 (oldValue);
    if (currType_ == LEX_SEMICOLON) {
      gl();
    }
    else {
      throw currLex_;
    }
    D1(tid, flagIsStruct);
  }
}


void Parser::D3 (int value)
{
  if (currType_ != LEX_ID) {
    throw currLex_;
  }
  else {
    stInt_.push (currValue_);
    gl();
    while (currType_ == LEX_COMMA) {
      gl();
      if (currType_ != LEX_ID) {
        throw currLex_; 
      }
      else {
        stInt_.push (currValue_);
        gl();
      }
    }
    decStruct(value);
  }
}

 
void Parser::D (TypeOfLex type, vector<Ident>& tid, bool flagIsStruct) {
  if (currType_ != LEX_ID) {
    throw currLex_;
  }
  else {
    stInt_.push (currValue_);
    int oldValue = currValue_;
    gl(tid);
    if ((currType_ == LEX_ASSIGN) && (flagIsStruct == true)) {
      throw "initialization of variable within structure is forboden";
    }
    if (currType_ == LEX_ASSIGN) {
      poliz.push_back (Lex ( POLIZ_ADDRESS, oldValue) );
      gl(tid);
      if (type == LEX_BOOL) {
        if  (currType_ == LEX_TRUE) {
          poliz.push_back (Lex (LEX_TRUE, 1));
        }
        else if (currType_ == LEX_FALSE) {
          poliz.push_back (Lex (LEX_FALSE, 0));
        }
        else { 
          throw currLex_;
        }
      }
      else if (type == LEX_STRING) {
        if (currType_ == LEX_STR) {
          poliz.push_back (currLex_);
        }
        else {
          throw currLex_;
        }
      }
      else if (type == LEX_INT) {
        if (currType_ == LEX_NUM) {
          poliz.push_back (currLex_);
        }
        else { 
          throw currLex_;
        }
      } 
      poliz.push_back (Lex (LEX_ASSIGN) );
      poliz.push_back (Lex(LEX_SEMICOLON,1));
      gl(tid);
    }
    while (currType_ == LEX_COMMA) {
      gl(tid);
      if (currType_ != LEX_ID) {
        throw currLex_;
      }
      else {
        stInt_.push (currValue_);
        oldValue = currValue_;
        gl(tid);
        if ((currType_ == LEX_ASSIGN) && (flagIsStruct == true)) {
          throw "initialization of variable within structure is forboden";
        }
        if (currType_ == LEX_ASSIGN) {
          poliz.push_back (Lex ( POLIZ_ADDRESS, oldValue) );
          gl(tid);
          if (type == LEX_BOOL) {
            if  (currType_ == LEX_TRUE) {
              poliz.push_back (Lex (LEX_TRUE, 1));
            }
            else if (currType_ == LEX_FALSE) {
              poliz.push_back (Lex (LEX_FALSE, 0));
            }
            else { 
              throw currLex_;
            }
          }
          else if (type == LEX_STRING) {
            if (currType_ == LEX_STR) {
              poliz.push_back (currLex_);
            }
            else {
              throw currLex_;
            }
          }
          else if (type == LEX_INT) {
            if (currType_ == LEX_NUM) {
              poliz.push_back ( currLex_ );
            }
            else { 
              throw currLex_;
            }
          } 
          poliz.push_back (Lex (LEX_ASSIGN) );
          poliz.push_back (Lex(LEX_SEMICOLON,1));
          gl(tid);
        }
      }
    }
    dec (type, tid);
  }
}


void Parser::B1 (bool isCycle)
{
  while (currType_ != LEX_RBRACE) {
    B (isCycle);
  }
}


void Parser::B (bool isCycle)
{
  int pl0, pl1, pl2, pl3;
  int l1, l2, l3, l4;
  ///////////////////////////////////////////////////////
  if (currType_ == LEX_IF) {
    gl();
    if (currType_ != LEX_LPAREN) {
      throw currLex_;
    }
    gl();
    E (currLex_);
    eqBool();
    pl2 = poliz.size();
    poliz.push_back (Lex());
    poliz.push_back (Lex(POLIZ_FGO));
    if (currType_ != LEX_RPAREN) {
      throw currLex_;
    }
    gl();
    B (isCycle);
    pl3 = poliz.size();
    poliz.push_back (Lex());
    poliz.push_back (Lex(POLIZ_GO));
    poliz[pl2] = Lex (POLIZ_LABEL, poliz.size());
    if (currType_ == LEX_ELSE) {
      gl();
      B (isCycle);
      poliz[pl3] = Lex(POLIZ_LABEL, poliz.size());
    }
    else {
      throw currLex_;
    }
  } // end if
  ///////////////////////////////////////////////////////
  else if (currType_ == LEX_WHILE) {
    pl0 = poliz.size();
    gl();
    if (currType_ != LEX_LPAREN) {
      throw currLex_;
    }
    gl();
    E (currLex_);
    eqBool();
    pl1 = poliz.size();
    poliz.push_back (Lex());
    poliz.push_back (Lex(POLIZ_FGO));
    if (currType_ != LEX_RPAREN) {
      throw currLex_;
    }
    gl();
    B (true);
    poliz.push_back (Lex(POLIZ_LABEL, pl0));
    poliz.push_back (Lex(POLIZ_GO));
    poliz[pl1] = Lex (POLIZ_LABEL, poliz.size());
    vector<int>::iterator p = break_.begin();
    while (p != break_.end()) { 
      poliz[*p] = Lex (POLIZ_LABEL, poliz.size());
      ++p;
    }
    break_.clear();
  } // end while
  ///////////////////////////////////////////////////////
  else if (currType_ == LEX_FOR) {
    gl();
    if (currType_ != LEX_LPAREN) {
      throw currLex_;
    }
    gl();
    E (currLex_);
    if (currType_ != LEX_SEMICOLON)
      throw currLex_;
    poliz.push_back(currLex_);
    gl();
    l1 = poliz.size();
    E (currLex_);
    eqBool();
    if (currType_ != LEX_SEMICOLON)
      throw currLex_;
    gl();
    l2 = poliz.size();
    poliz.push_back (Lex());
    poliz.push_back (Lex(POLIZ_FGO));
    l3 = poliz.size();
    poliz.size();
    poliz.push_back (Lex());
    poliz.push_back (Lex(POLIZ_GO));
    l4 = poliz.size();
    E (currLex_);
    if (currType_ != LEX_RPAREN)
      throw currLex_;
    poliz.push_back(Lex(LEX_SEMICOLON,1));
    gl();
    poliz.push_back (Lex(POLIZ_LABEL, l1));
    poliz.push_back (Lex(POLIZ_GO));
    poliz[l3] = Lex(POLIZ_LABEL, poliz.size());
    B (true);
    poliz.push_back (Lex(POLIZ_LABEL, l4));
    poliz.push_back (Lex(POLIZ_GO));
    poliz[l2] = Lex (POLIZ_LABEL, poliz.size());
    vector<int>::iterator p = break_.begin();
    while (p != break_.end()) { 
      poliz[*p] = Lex (POLIZ_LABEL, poliz.size());
      ++p;
    }
    break_.clear();
  } // end for
  ///////////////////////////////////////////////////////
  else if (currType_ == LEX_BREAK) {
    if (!isCycle) {
      throw currLex_;
    }
    break_.push_back(poliz.size());
    poliz.push_back (Lex());
    poliz.push_back (Lex(POLIZ_GO));
    gl();
    if (currType_ == LEX_SEMICOLON) {
      gl();
    }
    else {
      throw currLex_;
    }
  } // end break
  ///////////////////////////////////////////////////////
  else if (currType_ == LEX_LBRACE) {
    gl();
    B1 (isCycle);
    if (currType_ == LEX_RBRACE) {
      gl();
    }
    else {
      throw currLex_;
    }
  } // end LBRACE
  ///////////////////////////////////////////////////////
  else if (currType_ == LEX_ID) {
    G (currLex_, isCycle);
  } // end ID
  ///////////////////////////////////////////////////////
  else if (currType_ == LEX_SEMICOLON) {
    gl();
  } // end SEMICOLON
  ///////////////////////////////////////////////////////
  else if (currType_ == LEX_NUM    || currType_ == LEX_STR   ||
           currType_ == LEX_TRUE   || currType_ == LEX_FALSE ||
           currType_ == LEX_LPAREN || currType_ == LEX_MINUS ||
           currType_ == LEX_NOT ) {
    E1 ();
    if (currType_ == LEX_SEMICOLON) {
      poliz.push_back(currLex_);
      gl();
    }
    else {
      throw currLex_;
    }
    
  } // end CONST or LPAREN
  ///////////////////////////////////////////////////////
  else if (currType_ == LEX_READ) {
    gl();
    if (currType_ == LEX_LPAREN) {
      gl();
      if (currType_ == LEX_ID) {
        checkIdInRead();
        if (TID[currValue_].isObject()) {
          int i = currValue_;
          int j;
          gl();
          if (currType_ == LEX_RPAREN) {
            throw "Object in read!";
          }
          else if (currType_ == LEX_POINT) {
            gl(TID[i].tid);
            if (currType_ != LEX_ID) {
              throw currLex_;
            }
            j = currValue_;
            if (!TID[i].tid[j].getDeclare()) {
              throw "wrong field of object";
            }
            poliz.push_back (Lex(POLIZ_ADDRESS,i, j));
            gl();
          }
          else {
          	throw currLex_;
          }
        }
        else {
          poliz.push_back(Lex(POLIZ_ADDRESS, currValue_));
          gl();
        }  
      }
      else {
        throw currLex_;
      }
      if (currType_ == LEX_RPAREN) {
        gl();
        poliz.push_back (Lex(LEX_READ));
      }
      else {
        throw currLex_;
      }
      if (currType_ == LEX_SEMICOLON) {
        gl();
      }
      else {
        throw currLex_;
      }
    }
    else {
      throw currLex_;
    }
  } // end read
  ///////////////////////////////////////////////////////
  else if (currType_ ==  LEX_WRITE) {
    gl();
    if (currType_ == LEX_LPAREN) {
      gl();
      E (currLex_,false,true);
      poliz.push_back (Lex(LEX_WRITE));
      while (currType_ == LEX_COMMA) {
        gl();
        E (currLex_,false,true);
        poliz.push_back (Lex(LEX_WRITE));
      }
      if (currType_ != LEX_RPAREN) {
        throw currLex_;
      }
      gl();
      if (currType_ != LEX_SEMICOLON) {
        throw currLex_;
      }
      gl();
    }
    else {
      throw currLex_;
    }
  } // end write
  ///////////////////////////////////////////////////////
  else if (currType_ == LEX_GOTO) {
    gl();
    if (currType_ != LEX_ID) {
      throw currLex_;
    }
    if (TID[currValue_].getDeclare() && TID[currValue_].isLabel()) {
      poliz.push_back (Lex(POLIZ_LABEL, TID[currValue_].getValue()));
      poliz.push_back (Lex(POLIZ_GO));
    }
    else if (TID[currValue_].getDeclare() && !TID[currValue_].isLabel()) {
      throw "Not label in operator goto";
    }
    else {
      Goto_ g;
      g.adressGoto_ = poliz.size();
      g.valueLabel_ = currValue_;
      goto_.push_back(g);
      poliz.push_back (Lex());
      poliz.push_back (Lex(POLIZ_GO));
    }
    gl();
    if (currType_ != LEX_SEMICOLON) {
      throw currLex_;
    }
    gl();
  } // end goto
  ///////////////////////////////////////////////////////
  else {
    throw currLex_;
  }
}


void Parser::G (Lex currLex, bool isCycle)
{
  int value;
  if (currType_ == LEX_ID) {
    gl();
    if (currType_ == LEX_COLON) {
      value = currLex.getValue();
      checkLabel(value);
      TID[value].putIsLabel();
      TID[value].putDeclare();
      TID[value].putValue (poliz.size());
      gl();
      G (currLex_, isCycle);
    }
    else {
      if (currType_ <= 20) {
        scanner_.stepBack (strlen(Scanner::TW[currValue_]));
      }
      else if ((currType_ >= 22) && (currType_ <= 40)) {
        scanner_.stepBack (strlen(Scanner::TD[currValue_]));
      }
      else {
        throw currLex_;
      }
      currLex_ = currLex;
      currType_ = currLex_.getType();
      currValue_ = currLex_.getValue();
      E (currLex_);
      if (currType_ == LEX_SEMICOLON) {
      	poliz.push_back (Lex(LEX_SEMICOLON,1));
      	gl();
      }
      else {
      	throw currLex_;
      }
    }
  }
  else {
    B (isCycle);
  }
}


void Parser::E (Lex currLex, bool notObject, bool isWrite)
{ 
  int i,j;
  if (currType_ == LEX_ID) {
    gl();
    if (currType_ == LEX_ASSIGN) {
      if (currLex.getType() == LEX_OBJECT) {
        i = currLex.getValue();
        j = currLex.getValue2();
        stLex_.push (TID[i].tid[j].getType());
        poliz.push_back (Lex(POLIZ_ADDRESS, i, j));
        gl();
        E (currLex_, notObject, isWrite);
        eqType();
        poliz.push_back (Lex(LEX_ASSIGN));
      }
      else if (TID[currLex.getValue()].isObject()) {
        if (notObject) {
          throw "wrong types are in =";
        }
        if (isWrite) {
          throw "object in write";
        }
        currLex_ = currLex;
        currType_ = currLex_.getType();
        currValue_ = currLex_.getValue();
        scanner_.stepBack(1);
        S (currLex_);
        
      }
      else {
        checkId (currLex.getValue());
        poliz.push_back (Lex(POLIZ_ADDRESS, currLex.getValue()));
        gl();
        E (currLex_, true, isWrite);
        eqType();
        poliz.push_back (LEX_ASSIGN);
      }
    }
    else if (currType_ == LEX_PLUS  || currType_ == LEX_MINUS ||
             currType_ == LEX_TIMES || currType_ == LEX_SLASH ||
             currType_ == LEX_LSS   || currType_ == LEX_GTR   ) {
      if ((currLex.getType() != LEX_OBJECT) && TID[currLex.getValue()].isObject()) {
        throw "wrong types in operator";
      }
      scanner_.stepBack(1);
      currLex_ = currLex;
      currType_ = currLex_.getType();
      currValue_ = currLex_.getValue();
      E1 ();
    }
    else if (currType_ == LEX_OR    || currType_ == LEX_NEQ   ||
             currType_ == LEX_LEQ   || currType_ == LEX_GEQ   ||
             currType_ == LEX_EQ    ) {
      if ((currLex.getType() != LEX_OBJECT) && TID[currLex.getValue()].isObject()) {
        throw "wrong types in operator";
      }
      scanner_.stepBack(2);
      currLex_ = currLex;
      currType_ = currLex_.getType();
      currValue_ = currLex_.getValue();
      E1 ();
    }
    else if (currType_ == LEX_AND) {
      if ((currLex.getType() != LEX_OBJECT) && TID[currLex.getValue()].isObject()) {
        throw "wrong types in operator";
      }
      scanner_.stepBack(3);
      currLex_ = currLex;
      currType_ = currLex_.getType();
      currValue_ = currLex_.getValue();
      E1 ();
    }
    else if (currType_ == LEX_RPAREN || (currType_ == LEX_SEMICOLON && !isWrite)) {
      if (currType_ == LEX_RPAREN && isWrite &&
          currLex.getType() != LEX_OBJECT && TID[currLex.getValue()].isObject()) {
        throw "object in write";
      }
      else if (currLex.getType() == LEX_OBJECT) {
        i = currLex.getValue();
        j = currLex.getValue2();
        stLex_.push (TID[i].tid[j].getType());
        poliz.push_back (currLex);
      }
      else {
        checkId (currLex.getValue());
        poliz.push_back (currLex);
      }
    }
    else if (currType_ == LEX_COMMA && isWrite) {
      if (currLex.getType() != LEX_OBJECT && TID[currLex.getValue()].isObject()) {
        throw "object in write";
      }
      else if (currLex.getType() == LEX_OBJECT) {
        i = currLex.getValue();
        j = currLex.getValue2();
        stLex_.push (TID[i].tid[j].getType());
        poliz.push_back (currLex);
      }
      else {
        checkId (currLex.getValue());
        poliz.push_back (currLex);
      }
    }
    else if (currType_ == LEX_POINT) {
      i = currLex.getValue();
      if (!TID[i].getDeclare() || !TID[i].isObject()) {
        throw "not declared object";
      }
      gl(TID[i].tid);
      if (currType_ != LEX_ID) {
        throw currLex_;
      }
      if (!TID[i].tid[currValue_].getDeclare()) {
        throw "wrong field of object";
      }
      currLex_ = Lex(LEX_OBJECT, i, currValue_);
      E (currLex_, true, isWrite);
    }
    else {
      throw currLex_;
    }
  }
  else {
    E1 ();
  }
}


void Parser::S (Lex currLex) 
{
  if (currType_ == LEX_ID) {
    checkObject();
    gl();
    if (currType_ == LEX_ASSIGN) {
      poliz.push_back (Lex(POLIZ_ADDRESS, currLex.getValue()));
      gl();
      S (currLex_);
      eqTypeStruct();
      poliz.push_back (Lex(LEX_ASSIGN));
    }
    else {
      poliz.push_back (currLex);
      if (currType_ != LEX_SEMICOLON && currType_ != LEX_RPAREN) {
      	throw currLex_;
      }
    }
  }
  else {
  	throw currLex_;
  }
}


void Parser::checkObject ()
{
  if (!TID[currValue_].isObject()) {
    throw "wrong types in operator =";
  }
  else {
    stInt_.push (TID[currValue_].getValueStruct());
  }
}


void Parser::eqTypeStruct ()
{
  int t = stInt_.top();
  stInt_.pop();
  if (t !=stInt_.top()) {
    throw "wrong types are in =";
  }
}


void Parser::E1 ()
{
  E2 ();
  while (currType_ == LEX_OR) {
    stLex_.push (currType_);
    gl();
    E2 ();
    checkOp();
  }
}


void Parser::E2 ()
{
  E3 ();
  while (currType_ == LEX_AND) {
    stLex_.push (currType_);
    gl();
    E3 ();
    checkOp();
  }
}


void Parser::E3 ()
{
  E4 ();
  if ( currType_ == LEX_LSS || currType_ == LEX_GTR || currType_ == LEX_LEQ ||
       currType_ == LEX_GEQ || currType_ == LEX_EQ  || currType_ == LEX_NEQ  )  { 
    stLex_.push (currType_);
    gl();
    E4 ();
    checkOp();
  }
}


void Parser::E4 () 
{
  T ();
  while (currType_ == LEX_PLUS || currType_ == LEX_MINUS) {
    stLex_.push (currType_);
    gl();
    T ();
    checkOp();
  }
}


void Parser::T ()
{
  F ();
  while (currType_ == LEX_TIMES || currType_ == LEX_SLASH) {
    stLex_.push (currType_);
    gl();
    F ();
    checkOp();
  }
}


void Parser::F (bool isMinus, bool isNot)
{ 
  int i,j;
  if (currType_ == LEX_OBJECT) {
    i = currLex_.getValue();
    j = currLex_.getValue2();
    stLex_.push (TID[i].tid[j].getType());
    poliz.push_back (Lex(LEX_OBJECT, i, j));
    gl();
  }
  else if (currType_ == LEX_ID) {
    if (TID[currValue_].isObject()) {
      i = currValue_;
      gl();
      if (currType_ != LEX_POINT) {
        throw "wrong type in operation";
      }
      gl(TID[i].tid);
      if (currType_ != LEX_ID) {
        throw currLex_;
      }
      j = currValue_;
      if (!TID[i].tid[j].getDeclare()) {
        throw "wrong field of object";
      }
      stLex_.push (TID[i].tid[j].getType());
      poliz.push_back (Lex(LEX_OBJECT, i, j));
      gl();
    }
    else {
      checkId (currValue_);
      poliz.push_back (Lex (LEX_ID, currValue_));
      gl();
    }
  }
  else if (currType_ == LEX_NUM) {
    stLex_.push (LEX_INT);
    poliz.push_back (currLex_);
    gl();
  }
  else if (currType_ == LEX_TRUE) {
    stLex_.push (LEX_BOOL);
    poliz.push_back (Lex(LEX_TRUE, 1));
    gl();
  }
  else if (currType_ == LEX_FALSE) {
    stLex_.push (LEX_BOOL);
    poliz.push_back (Lex (LEX_FALSE, 0));
    gl();
  }
  else if (currType_ == LEX_NOT) {
    if (isMinus) {
      throw currLex_;
    }
    gl();
    F (false, true);
    checkNot();
  }
  else if (currType_ == LEX_LPAREN) {
    gl();
    E (currLex_);
    if ((currType_ == LEX_RPAREN)) {
      gl();
    }
    else {
      throw currLex_;
    }
  }
  else if (currType_ == LEX_STR) {
    stLex_.push (LEX_STRING);
    poliz.push_back (currLex_);
    gl();
  }
  else if (currType_ == LEX_MINUS) {
    if (isNot) {
      throw currLex_;
    }
    gl();
    F (true, false);
    checkMinus();
  }
  else {
    throw currLex_;
  }
}


void Parser::checkNot () 
{
  if (stLex_.top() != LEX_BOOL) {
    throw "wrong type is in not";
  }
  else {
    poliz.push_back (Lex (LEX_NOT));
  }
}


void Parser::checkMinus () 
{
  if (stLex_.top() != LEX_INT) {
    throw "wrong type is in MINUS";
  }
  else {
    poliz.push_back (Lex (POLIZ_MINUS));
  }
}


void Parser::eqType ()
{
  TypeOfLex t = stLex_.top();
  stLex_.pop();
  if (stLex_.empty()) {
    throw "wrong types are in =";
  }
  if (t != stLex_.top()) {
    throw "wrong types are in =";
  }
}


void Parser::eqBool ()
{
  if (stLex_.top() != LEX_BOOL) {
    throw "expression is not boolean";
  }
  stLex_.pop();
}


void Parser::checkId (int currValue)
{
  if (TID[currValue].getDeclare()) {
    if (TID[currValue].isLabel()) {
      throw "wrong using label";
    }
    stLex_.push (TID[currValue].getType());
  }
  else {
    throw "not declared";
  }
}


void Parser::checkLabel (int value)
{
  if (TID[value].getDeclare()) {
    throw "label matches variable or redescribed";
  }
}


void Parser::checkOp () 
{
  TypeOfLex t1, t2, op, t = LEX_INT, r = LEX_BOOL, s = LEX_STR;

  t2 = stLex_.top();
  stLex_.pop();
  op = stLex_.top();
  stLex_.pop();
  t1 = stLex_.top();
  stLex_.pop();
  
  if (t1 == t2 && t1 == LEX_STRING) {
    if (op == LEX_PLUS) {
      stLex_.push (LEX_STRING);
    }
    else if (op == LEX_GTR || op == LEX_LSS || op == LEX_EQ || op == LEX_NEQ) {
      stLex_.push (LEX_BOOL);
    }
    else {
      throw "wrong operation for type string";
    }
  }
  else if (t1 == t2 && t1 == LEX_INT) {
    if (op == LEX_PLUS || op == LEX_MINUS || op == LEX_TIMES || op == LEX_SLASH) {
      stLex_.push (LEX_INT);
    }
    else {
      stLex_.push (LEX_BOOL);
    }
  }
  else if (t1 == t2 && t1 == LEX_BOOL) {
    if (op == LEX_OR || op == LEX_AND) {
      stLex_.push (LEX_BOOL);
    }
    else {
      throw "wrong operation for type bool";
    }
  }
  else {
    throw "wrong types are in operation";
  }
  poliz.push_back (Lex(op));
}

//считывание из стэка номеров строк TID->type param decalre asseign
void Parser::dec (TypeOfLex type, vector<Ident>& tid) 
{
  int i;
  while ( !stInt_.empty()) {
    i = stInt_.top();
    stInt_.pop();
    if ( tid[i].getDeclare() ) {
      throw "twice";
    }
    else {
      tid[i].putDeclare();
      tid[i].putType(type);
    }
  }
}

void Parser::decStruct (int value)
{
  int i;
  while ( !stInt_.empty() ) {
    i = stInt_.top();
    stInt_.pop();
    if (TID[i].getDeclare()) {
      throw "twice";
    }
    else {
      TID[i].putDeclare();
      TID[i].putType(LEX_OBJECT);
      TID[i].putIsObject();
      TID[i].putValueStruct(value);
      TID[i] = TID[value];
    }
  }
}


void Parser::checkIdInRead () 
{
  if ( !TID [currValue_].getDeclare() )
    throw "not declared";
}


///////////////////////////////////////////////////////////////////


class Executer 
{
  public:
    void execute (vector <Lex>& poliz);
  private:
    Lex pcEl_;
    struct Element {
      int val_;
      int val2_;
      string str_;
      bool isString_;
      bool isObject_;
      int getValue () const 
      {
        return val_;
      }
      int getValue2 () const 
      {
        return val2_;
      }
      void putIsObject()
      {
        isObject_ = true;
      }
      Element (int val, int val2 = -1): val_(val), val2_(val2), isString_(false) 
      {
        isObject_ = (val2_== -1) ? false : true;
      }
      Element (string s): str_(s), isString_(true), isObject_(false) {}
      bool isString () { return isString_; }
      operator int () { return val_; }
      operator string () { return str_; }
    };
};


void Executer::execute (vector <Lex>& poliz) 
{
  stack <Element> args;
  int num, i, j, index = 0, size = poliz.size();
  string s1, s2;
  Ident* id;
  while (index < size) {
  	pcEl_ = poliz[index];
  	switch (pcEl_.getType()) {

      case LEX_TRUE:   case LEX_FALSE:    case LEX_NUM:  case POLIZ_LABEL:
        args.push (pcEl_.getValue());
        break;

      case POLIZ_ADDRESS:
        if (pcEl_.getValue2() != -1) {
          i = pcEl_.getValue();
          j = pcEl_.getValue2();
          args.push (Element(i,j));
        }
        else {
          args.push (pcEl_.getValue());
        }
        break;

      case LEX_STR:
        args.push (pcEl_.getStr());
        break;

      case LEX_ID:
        i = pcEl_.getValue();
        if (TID[i].isObject()) {
          args.push (i);
          args.top().putIsObject();
          break;
        }
        else if (TID[i].getAssign()) {
          if (TID[i].getType() == LEX_STRING) {
            args.push (TID[i].getStr());
          }
          else {
            args.push (TID[i].getValue());
          }
        }
        else {
          throw "POLIZ: indefinite identifier";
        }
        break;
      
      case LEX_OBJECT:
        i = pcEl_.getValue();
        j = pcEl_.getValue2();
        id = &(TID[i].tid[j]);
        if ((*id).getAssign()) {
          if ((*id).getType() == LEX_STRING) {
            args.push ((*id).getStr());
          }
          else {
            args.push ((*id).getValue());
          }
        }
        else {
          throw "POLIZ: indefinite identifier";
        }
        break;

      case LEX_SEMICOLON:
        args.pop();
        break;


      case LEX_NOT:
        i = (int) args.top();
        args.pop();
        args.push (!i);
        break;

      case POLIZ_MINUS:
        i = (int) args.top();
        args.pop();
        args.push (-i);
        break;

      case LEX_OR:
        i = (int) args.top();
        args.pop();
        j = (int) args.top();
        args.pop();
        args.push (j || i);
        break;

      case LEX_AND:
        i = (int) args.top();
        args.pop();
        j = (int) args.top();
        args.pop();
        args.push ( j && i );
        break;

      case POLIZ_GO:
        i = (int) args.top();
        args.pop();
        index = i-1;
        break;

      case POLIZ_FGO:
        i = (int) args.top();
        args.pop();
        j = (int) args.top();
        args.pop();
        if ( !j ) {
          index = i-1;
        }
        break;

      case LEX_WRITE:
        if (args.top().isString()) {
          s2 = (string) args.top();
          args.pop();
          cout << s2 << endl;
        }
        else {
          j = (int) args.top();
          args.pop();
          cout << j << endl;
        }
        break;

      case LEX_READ:
        int k;
        if (args.top().isObject_) {
          i = args.top().val_;
          j = args.top().val2_;
          args.pop();
          id = &(TID[i].tid[j]);
          if ((*id).getType() == LEX_INT) {
            cout << "Input int value for " << TID[i].getName() 
                 << "." << (*id).getName() << endl;
            cin >> k;
            (*id).putValue(k);
            (*id).putAssign();
          }
          else if ((*id).getType() == LEX_STRING) {
          	cout << "Input string value for " << TID[i].getName() 
          	     << "." << (*id).getName() << endl;
            cin >> s1;
            (*id).putValue(s1);
            (*id).putAssign();
          }
          else {
            string j;
            while (1) {
          	  cout << "Input boolean value (true or false) for " 
          	       << TID[i].getName() << "." << (*id).getName() << endl;
          	  cin >> j;
          	  if ( j != "true" && j != "false" ) {
              cout << "Error in input: true/false" << endl;
              continue;
          	}
          	k = (j == "true") ? 1 : 0;
          	break;
            }
            (*id).putValue(k);
            (*id).putAssign();
          }
        }
        else {
	      i = (int) args.top();
	      args.pop();
	      if (TID[i].getType() == LEX_INT) {
	        cout << "Input int value for " << TID[i].getName() << endl;
	        cin >> k;
	        TID[i].putValue(k);
	        TID[i].putAssign();
	      }
	      else if (TID[i].getType() == LEX_STRING) {
	        cout << "Input string value for " << TID[i].getName() << endl;
	        cin >> s1;
	        TID[i].putValue(s1);
	        TID[i].putAssign();
	      }
	      else {
	        string j;
	        while (1) {
	          cout << "Input boolean value (true or false) for " << TID[i].getName() << endl;
	          cin >> j;
	          if ( j != "true" && j != "false" ) {
	            cout << "Error in input: true/false" << endl;
	            continue;
	          }
	          k = (j == "true") ? 1 : 0;
	          break;
	        }
	        TID[i].putValue(k);
	        TID[i].putAssign();
	      }
        }
        break;

      case LEX_PLUS:
        if (args.top().isString()) {
          s2 = (string) args.top();
          args.pop();
          s1 = (string) args.top();
          args.pop();
          args.push (s1 + s2); 
        }
        else {
          i = (int) args.top();
          args.pop();
          j = (int) args.top();
          args.pop();
          args.push ( i + j );
        }
        break;

      case LEX_TIMES:
        i = (int) args.top();
        args.pop();
        j = (int) args.top();
        args.pop();
        args.push ( i * j );
        break;

      case LEX_MINUS:
        i = (int) args.top();
        args.pop();
        j = (int) args.top();
        args.pop();
        args.push ( j - i );
        break;

      case LEX_SLASH:
        i = (int) args.top();
        args.pop();
        j = (int) args.top();
        args.pop();
        if (i != 0) {
          args.push(j / i);
          break;
        }
        else {
          throw "POLIZ:divide by zero";
        }

      case LEX_EQ:
        if (args.top().isString()) {
          s2 = (string) args.top();
          args.pop();
          s1 = (string) args.top();
          args.pop();
          args.push (s1 == s2); 
        }
        else {
          i = (int) args.top();
          args.pop();
          j = (int) args.top();
          args.pop();
          args.push ( j == i );
        }
        break;

      case LEX_LSS:
        if (args.top().isString()) {
          s2 = (string) args.top();
          args.pop();
          s1 = (string) args.top();
          args.pop();
          args.push (s1 < s2); 
        }
        else {
          i = (int) args.top();
          args.pop();
          j = (int) args.top();
          args.pop();
          args.push ( j < i );
        }
        break;

      case LEX_GTR:
        if (args.top().isString()) {
          s2 = (string) args.top();
          args.pop();
          s1 = (string) args.top();
          args.pop();
          args.push (s1 > s2); 
        }
        else {
          i = (int) args.top();
          args.pop();
          j = (int) args.top();
          args.pop();
          args.push ( j > i );
        }
        break;

      case LEX_LEQ:
        i = (int) args.top();
        args.pop();
        j = (int) args.top();
        args.pop();
        args.push ( j <= i );
        break;

      case LEX_GEQ:
        i = (int) args.top();
        args.pop();
        j = (int) args.top();
        args.pop();
        args.push ( j >= i );
        break;

      case LEX_NEQ:
        if (args.top().isString()) {
          s2 = (string) args.top();
          args.pop();
          s1 = (string) args.top();
          args.pop();
          args.push (s1 != s2); 
        }
        else {
          i = (int) args.top();
          args.pop();
          j = (int) args.top();
          args.pop();
          args.push ( j != i );
        }
        break;

      case LEX_ASSIGN:
        if (args.top().isObject_) {
          i = (int) args.top();
          args.pop();
          j = (int) args.top();
          args.pop();
          TID[j] = TID[i];
          args.push(i);
          args.top().putIsObject();
        }
        else if (args.top().isString()) {     
          s2 = (string) args.top();
          args.pop();
          if (args.top().isObject_) {
          	i = args.top().val_;
            j = args.top().val2_;
            id = &(TID[i].tid[j]);
            args.pop();
            (*id).putValue(s2);
            (*id).putAssign();
          }
          else {
            j = (int) args.top();
            args.pop();
            TID[j].putValue(s2);
            TID[j].putAssign();
          }
          args.push (s2);
        }
        else {
          num = (int) args.top();
          args.pop();
          if (args.top().isObject_) {
            i = args.top().val_;
            j = args.top().val2_;
            id = &(TID[i].tid[j]);
            args.pop();
            (*id).putValue(num);
            (*id).putAssign();
          }
          else {
            j = (int) args.top();
            args.pop();
            TID[j].putValue(num);
            TID[j].putAssign();
          }
          args.push (num);
        }
        break;

      default:
        throw "POLIZ: unexpected elem";
  	}  // end of switch
  	++ index;
  }  // end of while
  cout << "Finish of executing!!!" << endl;
}


class Interpretator 
{
  public:
    Interpretator (const char* program): pars(program) {}
    void interpretation ();	
  private:  
  	Parser pars;
    Executer E;
};
 

void Interpretator::interpretation () 
{
  pars.analyze ();
  E.execute ( pars.poliz );
}


int main(int argc, char** argv)
{
  try {
    Interpretator I (argv[1]);
    I.interpretation();
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
  catch (const char* c){
    cout << c << endl;
    return 1;
  }
}

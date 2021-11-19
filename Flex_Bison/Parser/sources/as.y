%{
#include <stdio.h>
#include <string.h>

int yyparse();
int yylex();
int yylineno;
void yyerror(const char *s);
extern char savedline[2048];
extern int column;
extern int accent;

%}

%nonassoc "then" /*used to remove conflict shift/reduce  if else*/
%nonassoc ELSE /*used to remove conflict shift/reduce  if else*/

%token IDENT
%token TYPE
%token VOID
%token READE
%token READC
%token PRINT
%token IF
%token ELSE
%token WHILE
%token NUM
%token CHARACTER
%token OR
%token AND
%token EQ
%token RETURN
%token ADDSUB
%token ORDER
%token DIVSTAR
%token FOR
%token CONTINUE 
%token STRUCT

%token INCLUDE /*ajout*/

%%
Prog:  Documentation Decl DeclFoncts
    ;
Documentation:
       Documentation INCLUDE
    |  %empty
    ;
TypeVar:
	   STRUCT IDENT
    |   TYPE
    ;
Decl:
	   Decl Declarateurs ';'
	|  Decl DeclStruct
	|  %empty
	;
DeclVars:
       DeclVars Declarateurs ';'
    | %empty
    ;
DeclStruct:
      STRUCT IDENT '{' DeclarationStruct '}' ';'
    ;
DeclarationStruct:
       ListTypStruct  ';'
    |  DeclarationStruct ListTypStruct  ';'
    ;
Declarateurs:
       Declarateurs ',' IDENT 
    |  TypeVar IDENT 
    ;
DeclFoncts:
       DeclFoncts DeclFonct  
    |  DeclFonct 
    ;
DeclFonct:
       EnTeteFonct Corps 
    ;
EnTeteFonct:
      VOID IDENT '(' Parametres ')'
    |  TypeVar IDENT '(' Parametres ')'
    ;
Parametres:
       VOID 
    |  ListTypVar 
    ;
ListTypVar:
       ListTypVar ',' TypeVar IDENT
    |  TypeVar IDENT 
    ;
ListTypStruct :
       ListTypStruct  ',' TYPE IDENT 
    |  TYPE IDENT
    ;
Corps: '{' DeclVars SuiteInstr '}'
    ;
SuiteInstr:
       SuiteInstr Instr 
    |  %empty
    ;
Instr:
       LValue '=' Exp ';'
    |  READE '(' IDENT ')' ';'
    |  READC '(' IDENT ')' ';'
    |  PRINT '(' Exp ')' ';'
    |  IF '(' Exp ')' Instr         %prec "then"
    |  IF '(' Exp ')' Instr ELSE Instr
    |  WHILE '(' Exp ')' Instr  
    |  FOR '(' For ')' Instr
    |  IDENT '(' Arguments  ')' ';'
    |  RETURN Exp ';' 
    |  RETURN ';' 
    |  CONTINUE ';'
    |  '{' SuiteInstr '}'  
    |  ';'    
    ;

Exp :  Exp OR TB 
    |  TB 
    ;
TB  :  TB AND FB 
    |  FB 
    ;
FB  :  FB EQ M
    |  M
    ;
M   :  M ORDER E
    |  E
    ;
E   :  E ADDSUB T 
    |  T 
    ;    
T   :  T DIVSTAR F
    | F
    ;
F   :  ADDSUB F 

    |  '!' F 
    |  '(' Exp ')' 
    |  NUM 
    |  CHARACTER
    |  LValue
    |  IDENT '(' Arguments  ')' 
    ;
LValue:
       IDENT 
    ;
Arguments:
       ListExp        
    |  %empty
    ;
ListExp:
       ListExp ',' Exp 
    |  Exp 
    ;
For:
	   ';'
	|  Exp ';'
	;
%%


void yyerror(const char *s)
{
	fflush(stdout);
	printf("%s",savedline);
    int accent_div = accent/2; 
    column--;
	printf("\n%*s\n%s near line %d, character %d\n", column-accent_div, "^", s,yylineno,column-accent_div);
}


int main(int argc, char *argv[])
{
   return yyparse();
}

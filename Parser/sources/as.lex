%{
#include <stdio.h>
#include <ctype.h>
#include "as.tab.h"

char savedline[2048];
int column = 0;
int cursor = 0;
int accent = 0;
int control_unidentified = 0;
int save_line = 0;

#undef YY_INPUT
#define YY_INPUT(buf,resultat,max_size) \
    { \
    	if(save_line == 0){\
	    	fscanf(yyin,"%[^\n]",savedline);\
	    	fseek(yyin, cursor, SEEK_SET);\
            save_line = 1;\
		}\
        int c = fgetc(yyin); \
        if(c != EOF)\
            column++;\
        cursor++;\
        resultat = (c == EOF) ? YY_NULL : (buf[0] = c, 1);\
        if(c == '\n' || c =='\r'){\
        	save_line = 0;\
        	column=0;\
        }\
    }
%}

%option yylineno 
%option nounput
%option noyywrap
%option noinput
%x SINGLECOMM
%x BLOCKCOMM

doc "<assert.h>"|"<ctype.h>"|"<stdio.h>"|"<stdlib.h>"|"<math.h>"|"<unistd.h>"|"<errno.h>"|"<complex.h>"|"<fenv.h>"|"<float.h>"|"<string.h>"|"<locale.h>"|"<inttypes.h>"|"<limits.h>"|"<time.h>"|"<stdint.h>"|"<stdarg.h>"|"<stdbool.h>"|"<uchar.h>"|"<wchar.h>"|"<wctype.h>"|"<stddef.h>"
%%

<SINGLECOMM>\n BEGIN INITIAL;
<BLOCKCOMM>\*\/ BEGIN INITIAL;
<SINGLECOMM,BLOCKCOMM>.|" "|\t|\n ;
\/\/ BEGIN SINGLECOMM;
\/\* BEGIN BLOCKCOMM;
" "|\t|\n|\r			{ }	
"#include"[ ]*{doc}		{ return INCLUDE;}
"continue"				{ return CONTINUE; }
"else"					{ return ELSE; }
"if"					{ return IF; }
"return"				{ return RETURN; }
"struct"				{ return STRUCT; }
"reade" 				{ return READE;}
"readc" 				{ return READC;}
"print"  				{ return PRINT; }
"void"					{ return VOID; }
"while"					{ return WHILE; }
[0-9]+  				{ return NUM; }
"int"|"char"	       { return TYPE; }
"&&"					{ return AND; }
"||"					{ return OR; }
"<="|">="|"<"|">"		{ return ORDER; }	
"=="|"!="				{ return EQ; }
"-"|"+"			 		{ return ADDSUB; }
"/"|"*"|"%"					{ return DIVSTAR; }
\'.\' 					{ return CHARACTER;}
[a-zA-Z_][a-zA-Z0-9_]*  { return IDENT;}
.						{ if(control_unidentified == 0){ column++; control_unidentified++;} return yytext[0];  }
<<EOF>>                 { column++; return EOF;}
%%
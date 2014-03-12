/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     TK_CHAR = 258,
     TK_INT = 259,
     TK_STRING = 260,
     TK_BOOL = 261,
     TK_TRUE = 262,
     TK_FALSE = 263,
     TK_NOT = 264,
     TK_WHILE = 265,
     TK_LOOP = 266,
     TK_IF = 267,
     TK_ELSE = 268,
     TK_END = 269,
     TK_NEW = 270,
     TK_RET = 271,
     TK_FUN = 272,
     TK_OPEN_PARENTHESIS = 273,
     TK_CLOSE_PARENTHESIS = 274,
     TK_COMMA = 275,
     TK_COLLON = 276,
     TK_GREATER = 277,
     TK_LESS = 278,
     TK_GREATER_EQUAL = 279,
     TK_LESS_EQUAL = 280,
     TK_EQUAL = 281,
     TK_NOT_EQUAL = 282,
     TK_OPEN_BRACKET = 283,
     TK_CLOSE_BRACKET = 284,
     TK_PLUS = 285,
     TK_MINUS = 286,
     TK_TIMES = 287,
     TK_DIVIDED = 288,
     TK_AND = 289,
     TK_OR = 290,
     TK_NUMINT = 291,
     TK_ID = 292,
     TK_LITERAL_STRING = 293,
     TK_LINE = 294,
     ERROR = 295
   };
#endif
/* Tokens.  */
#define TK_CHAR 258
#define TK_INT 259
#define TK_STRING 260
#define TK_BOOL 261
#define TK_TRUE 262
#define TK_FALSE 263
#define TK_NOT 264
#define TK_WHILE 265
#define TK_LOOP 266
#define TK_IF 267
#define TK_ELSE 268
#define TK_END 269
#define TK_NEW 270
#define TK_RET 271
#define TK_FUN 272
#define TK_OPEN_PARENTHESIS 273
#define TK_CLOSE_PARENTHESIS 274
#define TK_COMMA 275
#define TK_COLLON 276
#define TK_GREATER 277
#define TK_LESS 278
#define TK_GREATER_EQUAL 279
#define TK_LESS_EQUAL 280
#define TK_EQUAL 281
#define TK_NOT_EQUAL 282
#define TK_OPEN_BRACKET 283
#define TK_CLOSE_BRACKET 284
#define TK_PLUS 285
#define TK_MINUS 286
#define TK_TIMES 287
#define TK_DIVIDED 288
#define TK_AND 289
#define TK_OR 290
#define TK_NUMINT 291
#define TK_ID 292
#define TK_LITERAL_STRING 293
#define TK_LINE 294
#define ERROR 295




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;



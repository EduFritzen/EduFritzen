{
module ParserTodo where
import Data.Char
}

%name parserlamb
%tokentype { Token }
%error { parseError }

%token
    lam { TokenLam } 
    var { TokenVar $$ }
    '.' { TokenPoint }
    '(' { TokenOB }
    ')' { TokenCB }

%right '.'
%left APP	

%%

-- regras de producao da gramatica
Term : var                   { Var $1 }
     | lam var '.' Term      { Abs $2 $4 }
     | Term Term  %prec APP  { App $1 $2 }
     | '(' Term ')'          { $2 }

{

parseError :: [Token] -> a
parseError b = error "Parse Error"

data Term = Var Char
          | Abs Char Term
          | App Term Term deriving (Show, Eq)

data Token 
		= TokenVar Char
		| TokenPoint
		| TokenOB
		| TokenCB
		| TokenLam 
	deriving Show

lexer :: String -> [Token]
lexer [] = []
lexer (c:cs)
    | isSpace c = lexer cs
    | c == '.'  = TokenPoint : lexer cs
    | c == '('  = TokenOB : lexer cs
    | c == ')'  = TokenCB : lexer cs
    | isAlpha c = let (a,rest) = span isAlpha (c:cs)
                  in if (a == "lam") then TokenLam : lexer rest
                     else (TokenVar c) : lexer rest 

}
### Tokenize Arithmatic Expression

Given a string of arithmatic, Implement a C++ Class that tokenizes the arithmatic string expression.

eg: 
expression ex = "1+2+3"
## Result
ex.getnexttoken() = 1
ex.getnexttoken() = +
ex.next_token_is_op() = False // because '2' is not operator
ex.next_token_is_int() = True // because '2' is integet

eg:

## Result
expression ex = "    -1+4   -6"

ex.getnexttoken() = -1
ex.getnexttoken() = +
ex.next_token_is_op() = False // because '4' is not operator
ex.next_token_is_int() = True // because '4' is integet

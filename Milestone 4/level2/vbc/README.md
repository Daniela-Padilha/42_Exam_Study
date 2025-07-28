Assignment name  : vbc  
Expected files   : *.c *.h  
Allowed functions: malloc, calloc, realloc, free, printf, isdigit, write  

--------------------------------------------------------------------------------

Write a program that prints the result of a mathematical expression given as argument.

- It must handle addition (`+`), multiplication (`*`), and parentheses.
- All values are single digits between 0 and 9 (inclusive).

Error handling:

- In case of an unexpected symbol, you must print:  
  `"Unexpected token '%c'\n"`
- If the expression ends unexpectedly, you must print:  
  `"Unexpected end of input\n"`
- The same rule applies if you find an unexpected '(' or ')'.
- In case of a syscall failure, you must exit with status code 1.

Examples:

```
./vbc '1' | cat -e  
out: 1$

./vbc '2+3' | cat -e  
out: 5$

./vbc '3*4+5' | cat -e  
out: 17$

./vbc '3+4*5' | cat -e  
out: 23$

./vbc '(3+4)*5' | cat -e  
out: 35$

./vbc '(((((2+2)*2+2)*2+2)*2+2)*2+2)*2' | cat -e  
out: 188$

./vbc '1+'  
out: Unexpected end of input

./vbc '1+2)' | cat -e  
out: Unexpected token ')'
```

File provided: vbc.c

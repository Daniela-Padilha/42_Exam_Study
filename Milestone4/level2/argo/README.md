Assignment name  : argo  
Expected files   : argo.c  
Allowed functions: getc, ungetc, printf, malloc, calloc, realloc, free, isdigit, fscanf, write  

--------------------------------------------------------------------------------

Write a function named `argo` that will parse a JSON file in the structure declared in `argo.h`:

```c
int argo(json dst, FILE *stream);
```
- `dst`    - pointer to the AST that you will create  
- `stream` - the file to parse (see `man FILE`)

Your function must return `1` for success and `-1` for failure.

Error handling:

- If an unexpected token is found, you must print:  
  `"Unexpected token '%c'\n"`
- If the token is EOF, you must print:  
  `"Unexpected end of input\n"`

Restrictions and parsing rules:

- Only handle numbers, strings, and maps.
- Numbers will only be basic ints, as in `scanf("%d")`.
- Handle escaping in strings only for backslashes and quotation marks (no `\n`, `\u`, etc).
- Do **not** handle spaces; treat them as invalid tokens.

> If in doubt about JSON parsing, refer to [RFC 8259](https://datatracker.ietf.org/doc/html/rfc8259), but the format required is simple.
>  
> Tested with the provided main, the output should be exactly the same as the input (except for errors).
>  
> There are some helper functions in `argo.c`.

Examples:

```
echo -n '1' | ./argo /dev/stdin | cat -e  
out: 1$

echo -n '"bonjour"' | ./argo /dev/stdin | cat -e  
out: "bonjour"$

echo -n '"escape! \" "' | ./argo /dev/stdin | cat -e  
out: "escape! \" "$

echo -n '{"tomatoes":42,"potatoes":234}' | ./argo /dev/stdin | cat -e  
out: {"tomatoes":42,"potatoes":234}$

echo -n '{"recursion":{"recursion":{"recursion":{"recursion":"recursion"}}}}' | ./argo /dev/stdin | cat -e  
out: {"recursion":{"recursion":{"recursion":{"recursion":"recursion"}}}}$

echo -n '"unfinished string' | ./argo /dev/stdin | cat -e  
out: Unexpected end of input

echo -n '"unfinished string 2\"' | ./argo /dev/stdin | cat -e  
out: Unexpected end of input

echo -n '{"no value?":}' | ./argo /dev/stdin | cat -e  
out: Unexpected token '}'
```

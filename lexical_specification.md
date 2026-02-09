
# Scanner part 1 - Lexical Specification


## Input language: 
Java

## Token Categories/Types:
ALL the tokens that your language will use.
- (
- )
- {
- }
- =
- +
- -
- *
- /
- %
- <
- >
- #
- .
- [DIGITS]
- [VARIABLES]
- if
- System.out.println
- for
- true
- (Others)




### Keywords: 

These are reserved words in your language 


- if
- System.out.println
- for
- true

### Identifiers: 
Names of variables, functions, and classes. Identifiers are arbitrary sequences of letters, digits, and the underscore character (_). They cannot contain spaces and must not begin with a digit.


### Numbers: could be formatted as integers, or floating point values, or fractions, or in alternate bases such as binary, octal or hexadecimal.

These may be formatted as integers, floating-point values, fractions, or numbers in alternate bases such as binary, octal, or hexadecimal.

**Note:** 
Read Section 3.1 for more information on tokens. Do not forget to include mathematical and logical operators, special symbols, punctuation, comments, and whitespace.


## Formal Specification:

For each token category, write a regular expression (using the basic regular expressions learned in class) that precisely defines how the token is formed from the input character stream.

For example:
- [DIGIS]
[0-9]+
- [VARIABLES]
[a-zA-Z][a-zA-Z0-9/_]*


### Keywords:

```
(if)|(System.out.println)|(for)
```

## Examples: 


Include clear, runnable examples for each token type, showing how they appear in source code. 


### Keywords: 

```
if(true){
	System.out.println("Search it.");
}

if(3==5-2){
	System.out.println("The value is same");
}
```

### Identifiers: 

```
for(i=0; i<10; i++){
	System.out.println("i: " + i);
}
```

### Numbers: 

```
int z = 30;
```

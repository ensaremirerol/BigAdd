# parser.h

* ```c
    void parser(LexicalData* data);
  ```
  Parses given the file in Lexical data, and executes operations if the syntax is true.

* ```c
    void loop(Variable* stack, IdentifierKeeper* identifierKeeper, LexicalData* data, BlockKeeper* blockKeeper,
   bool isShortHandLoop);
  ```
  Creates a loop.

## How does it work?

Parser uses 3 variables to check syntax. These are:
* ```c
    unsigned char flag; (Inital value is LINE_ENDED)
    ```

* ```c
    TokenType currToken;
    ```

* ```c
    Keycode expectedKeycode; (Inital value is bNop)
    ```

The parser expects words that suit the current flag. The parser uses "Bitwise AND" and "Equality Operator" to specify the type of the expected word.

If the Current Words' TokenType is different from the expected type or the Current keyword is
different from the expected keyword, the parser throws an error message using the "err" function.

Otherwise, continues to prepare the current operation.

## How operations executed

If the parser sees no problem with the current word, prepares an operation.
Operation functions kept in Keyword struct. Operation function receives 2 arguments.
These are Variable and IdentifierKeeper.

Parser adds Variables to stack as they come.

At the End of Line, the operation function executes the operation using Variable stack and Identifier keeper.

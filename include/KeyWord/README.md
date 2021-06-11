# KeyWord

## KeyWord Struct

```c
typedef struct keyWordStruct {
    char *keyWord; // keyword
    Keycode expectedKeycode; // Expected keyword after this keyword
    Keycode keycode; // Keywords' keycode
    unsigned char flagsForKeyword; // Expected flag for the use of this keyword
    unsigned char flagsForNextWord; // Flag for next expected word
    void (*operationFunc)(Variable* stack, IdentifierKeeper* identifierKeeper); // Operation for this keyword
    struct keyWordStruct *next;
}KeyWord;
```

Keeps all keywords in a linked list.

## All Flags

Flag               | Binary Value | Decimal Value | Description
---------------    | ------------ | ------------- | -----------
LINE_ENDED         | 0b00000001   | 1             | Indicates current is line ended
STRING_EXPECTED    | 0b00000010   | 2             | A String Constant is expected
INT_EXPECTED       | 0b00000100   | 4             | A Int Constant is expected
IDENTIFIER_USE     | 0b00001000   | 8             | A declared identifier is expected
IDENTIFIER_DECLARE | 0b00100000   | 32            | A not declared identifier is expected
BLOCK_EXPECTED     | 0b01000001   | 65            | A Openblock or start of a new line is expected
NOP                | 0b10000000   | 128           | If flag set to NOP lexical analyzer expecting `expectedKeycode`
IDENTIFIER_EXPECTED| 0b00101000   | 40            | Declared or not declared identifier is expected
KEYWORD_EXPECTED   | 0b11000001   | 193           | A keyword is expected
INT_VAL            | 0b00001100   | 12            | Int Constant or declared identifier is expected
OUT_LIST           | 0b00001110   | 14            | A String Constant, Int Constant or declared Identifier is expected

Parser checks flag status with "Bitwise And" or "=="

After a non-keyword word, the lexical analyzer sets the flag to NOP

## Keycode
```c
typedef enum keycode {bInt, bMove, bAdd, bSub, bOut, bLoop, bOpenBlock, bCloseBlock, bTimes, bNewline, bTo, bEOL, bSeparator,
    bFrom, bNop} Keycode;
```
Keycodes' type is enum and represents Keywords.

## TokenType

```c
typedef enum tokentype {bKeyword, bIntConstant, bStringConstant, bIdentifier,  bEOF, bError} TokenType;
```

Token type represents current tokens type.
Used by lexical analyzer and parser

## All Keywords
Keycode           | Keyword | Expected Keycode | Expected keyword | Expected Flag      | Next Flag            | Operation
-------           | ------- | ---------------- | ---------------- | ------------------ | ---------            | --------
bInt              | int     | 11               | .                | LINE_ENDED         | IDENTIFIER_DECLARE   | identifier
bMove             | move    | 10               | to               | LINE_ENDED         | INT_VAL              | move
bAdd              | add     | 10               | to               | LINE_ENDED         | INT_VAL              | add
bSub              | sub     | 13               | from             | LINE_ENDED         | INT_VAL              | sub
bOut              | out     | 12               | ,                | LINE_ENDED         | OUT_LIST             | out
bLoop             | loop    | 8                | times            | LINE_ENDED         | INT_VAL              | NULL
bOpenBlock        | [       | -1               |                  | BLOCK_EXPECTED     | LINE_ENDED           | NULL
bCloseBlock       | ]       | -1               |                  | LINE_ENDED         | LINE_ENDED           | NULL
bTimes            | times   | -1               |                  | NOP                | BLOCK_EXPECTED       | NULL
bNewLine          | newline | 12               | ,                | OUT_LIST           | NOP                  | NULL
bTo               | to      | 11               | .                | NOP                | IDENTIFIER_USE       | NULL
bEOL              | .       | -1               |                  | NOP                | LINE_ENDED           | NULL
bSeparator        | ,       | 12               | ,                | NOP                | OUT_LIST             | NULL
bFrom             | from    | 11               | .                | NOP                | IDENTIFIER_USE       | NULL

* Keycode: Keywords' code.
* Keyword: Keyword itself.
* Expected KeyCode: Next expected keycode.
* Expected Keyword: Next expected keyword.
* Expected Flag: Expected flag for the use of this KeyWord.
* Next Flag: Flag for next expected "word".
* Operation: Function for keyword

Parser always checks flag first.

If `(flag & KEYWORD_EXPECTED)` bitwise operation is `0`,
parser expects a non-keyword word.

Otherwise, the parser expects a keyword according to the expectedKeycode.

Note: If the Expected keycode is bNop, the parser expects the flag to be LINE_ENDED.
Otherwise, the parser expects the flag to be NOP.

## Keyword Functions

* ```c 
  KeyWord *addKeyWord(char *keyWord, KeyWord *prev, char keycode, char expectedKeyCode, unsigned char flagsForKeyWord,
                    unsigned char flagsForNextKeyWord);
  ```
    * Adds keyword to list.

* ```c 
  KeyWord *createKeyWordLinkedList();
  ```
    * Creates linked list and returns the root of it.

* ```c 
  KeyWord *getKeyWord(char *keyWord, KeyWord *keyWordRoot);
  ```
    * Returns KeyWord pointer using keyWord string(char array). Returns NULL if keyWord not in the list.

* ```c 
  KeyWord *getKeyWordByKeyCode(Keycode keyCode, KeyWord *keyWordRoot);
  ```
    * Same as above. Just uses keyCodes to find KeyWord.

* ```c 
  void freeKeyWordLinkedList(KeyWord *root);
  ```
    * Frees Linked List

* ```c 
  bool isIntConstant(char *str);
  ```
    * Checks given string is an IntConstant or not.

* ```c 
  bool isIdentifier(char *str);
  ```
    * Checks given string is an Identifier or not.

* ```c 
  void identifier(Variable* stack, IdentifierKeeper* identifierKeeper);
  ```
    * Creates identifier.

* ```c 
  void move(Variable* stack, IdentifierKeeper* identifierKeeper);
  ```
    * Moves a value to identifier

* ```c 
  void add(Variable* stack, IdentifierKeeper* identifierKeeper);
  ```
    * Adds a value to identifier

* ```c 
  void sub(Variable* stack, IdentifierKeeper* identifierKeeper);
  ```
    * Subtracts a value to identifier

* ```c 
  void out(Variable* stack, IdentifierKeeper* identifierKeeper);
  ```
    * Prints given values

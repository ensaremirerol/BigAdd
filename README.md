# Lexical Analyzer for BigAdd Language

## Big Add language

BigAdd language is a small programming language that has been designed in order to add and subtract
big integers programmatically and display the result on the screen.

BigAdd is an interpreted language. The BigAdd interpreter works from the command line with the command BA, and takes the script
file’s name as the only attribute.

example: The command `c:\> ba myscript.ba`
must load and execute the script file called myscript.ba

## How to use Lexical Analyzer for BigAdd Language
To analyze a file, you should use following format

- `la <PATH>`

Path is path of file which you want to analyze.

Analyzer will print its working path to help you.

Note: You should include the file extension

### Example command

- `la ./script.ba`

## Lexical analyzers' data structures

### KeyWord

#### KeyWord Struct

```c
typedef struct keyWordStruct {
    char *keyWord; // Keyword
    char expectedKeycode; // Expected keycode after this keyword
    char keycode; // Its' code.
    unsigned char flagsForKeyword; // Expected flag for this keyword to be used
    unsigned char flagsForNextWord; // Expected flag for next "word". (It could be anything (Identifier, String, Int, ...))
    struct keyWordStruct *next; // next Keyword
} KeyWord;
```

Keeps all keywords in a linked list.

### All Flags

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

Lexical analyzer checks flag status with "Bitwise And" or "=="

After a non keyword word, lexical analyzer sets flag to NOP

#### All Keywords
KeyCode | Keyword | Expected Keycode | Expected keyword | Expected Flag      | Next Flag
------- | ------- | ---------------- | ---------------- | ------------------ | ---------
0       | int     | 11               | .                | LINE_ENDED         | IDENTIFIER_DECLARE
1       | move    | 10               | to               | LINE_ENDED         | INT_VAL
2       | add     | 10               | to               | LINE_ENDED         | INT_VAL
3       | sub     | 13               | from             | LINE_ENDED         | INT_VAL
4       | out     | 12               | ,                | LINE_ENDED         | OUT_LIST
5       | loop    | 8                | times            | LINE_ENDED         | INT_VAL
6       | [       | -1               |                  | BLOCK_EXPECTED     | LINE_ENDED
7       | ]       | -1               |                  | LINE_ENDED         | LINE_ENDED
8       | times   | -1               |                  | NOP                | BLOCK_EXPECTED
9       | newline | 12               | ,                | OUT_LIST           | NOP
10      | to      | 11               | .                | NOP                | IDENTIFIER_USE
11      | .       | -1               |                  | NOP                | LINE_ENDED
12      | ,       | 12               | ,                | NOP                | OUT_LIST
13      | from    | 11               | .                | NOP                | IDENTIFIER_USE

#### Keyword Functions

* ```c 
  KeyWord *addKeyWord(char *keyWord, KeyWord *prev, char keycode, char expectedKeyCode, unsigned char flagsForKeyWord,
                    unsigned char flagsForNextKeyWord);
  ```
    * Adds keyword to list.

* ```c 
  KeyWord *createKeyWordLinkedList();
  ```
    * Creates linked list and returns root of it.

* ```c 
  KeyWord *getKeyWord(char *keyWord, KeyWord *keyWordRoot);
  ```
    * Returns KeyWord pointer using keyWord string(char array). Returns NULL if keyWord not in list.

* ```c 
  KeyWord *getKeyWordbyIndex(char keyCode, KeyWord *keyWordRoot);
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
  bool isStringConstant(char *str, LineTracker *tracker);
  ```
  * Checks given string is an StringConstant or not.

### IdentifierKeeper

#### Identifier Struct
```c
typedef struct identifierNode {
  char *name; // Identifier name
  int val; // Identifiers' value (not used yet)
  struct identifierNode *next; // next Identifier
} Identifier;
```

#### IdentifierKeeper Struct
```c
typedef struct identifierKeeper {
  unsigned int size; // root of Linked List
  Identifier *root; // size of list
} IdentifierKeeper;
```

Keeps all declared Identifiers and its values in Linked List. 

#### IdentifierKeeper Functions

* ```c 
  bool isIdentifierDeclared(char *identifierName, IdentifierKeeper *keeper)
  ```
  * Checks given identifier has declared or not.

* ```c 
  bool declareIdentifier(char *identifierName, IdentifierKeeper *keeper);
  ```
  * Declares given identifier name. If it's already declared, returns false.

* ```c 
  IdentifierKeeper *createIdentifierKeeper();
  ```
  * Creates an IdentifierKeeper and returns its pointer.

* ```c 
  void freeIdentifierKeeper(IdentifierKeeper *identifierKeeper);
  ```
  * Frees given IdentifierKeeper.
  

### LineTracker
#### LineTracker Struct
```c
typedef struct lineTracker {
  int currLine;
} LineTracker;
```

Stores current line

#### LineTracker Functions
* ```c 
  int getLine(LineTracker *tracker);
  ```
  * Returns currentLine.

* ```c 
  void incrementLine(LineTracker *tracker)
  ```
  * Increments currentLine one(1).

* ```c 
  LineTracker *createLineTracker();
  ```
  * Creates a LineTracker and returns its pointer.
  

### BlockKeeper
#### Block Struct

```c
typedef struct blockNode {
  int lineStarted; // Where block started
  struct blockNode *nests;
} Block;
```
  
#### BlockKeeperStruct

```c
typedef struct blockKeeper {
  unsigned int totalBlocks;
  Block *root;
} BlockKeeper;
```

Keeps all opened blocks and where it opened.
When two blocks are nested, nested block is linked inside parent block

#### BlockKeeper Functions

* ```c 
  void openBlock(BlockKeeper *blockKeeper, int line);
  ```
  * Opens a new block. Nests new block if already a block opened.

* ```c 
  bool closeBlock(BlockKeeper *blockKeeper);
  ```
  * Closes the deepest block. If there is no block to close, returns false.

* ```c 
  int closeBlockAndGetLine(BlockKeeper *blockKeeper)
  ```
  * Closes the deepest block and returns its startLine. If there is no block to close, returns -1.

* ```c 
  BlockKeeper *createBlockKeeper()
  ```
  * Creates a BlockKeeper and returns its pointer.

* ```c 
  void freeBlockKeeper(BlockKeeper *blockKeeper)
  ```
  * Frees given BlockKeeper.
  

## Lexical Analyzer Helper Functions
Lexical Analyzer has two header files. These are `fileio.h` and `errhandle.h`
* `fileio.h` -> Functions about file operations
* `errhandle.h` -> Functions about error handling

### fileio.h

* ```c 
  FILE *openFile(char *path, char *mode);
  ```
  * Opens file at given path. If it fails, prints error message.

* ```c 
  void strclr(char *str, const int BUFFER_SIZE);
  ```
  * Clears given String(char array). BUFFER_SIZE is size of char array.

* ```c 
  bool skipIgnoreChars(FILE *fPtr, LineTracker *tracker);
  ```
  * Skips all unimportant characters in given file. Unimportant characters are:
    * White Space (' ')
    * Line break ('\n')
    * Carriage return ('\r')
  * Returns true if a character is skipped.

* ```c 
  bool skipCommentBlocks(FILE *fPtr, LineTracker *tracker);
  ```
  * Skips Comment blocks. Returns true if a comment block is skipped

* ```c 
  void seekEOL(FILE *fPtr, LineTracker *tracker);
  ```
  * Seeks to End of Line('.')

* ```c 
  void getWord(char *out, FILE *fPtr, LineTracker *tracker, const int BUFFER_SIZE);
  ```
  * Gets a word in file and writes it to out.
  * There are exceptions at reading. Exceptions are:
    * If first character read is,
      * End Of Line ('.')
      * Separator (',')
      * Open or Close Block ('\[' / '\]')
      
      only write read character and return.
    * If first character read is Lexeme String (' \" '), Reads until another Lexeme String. If can't find 
      another Lexeme String, returns.
      
    * Otherwise, reads until end of word. (Word termination characters are one of above and White space)
  
### errhandle.h

* ```c 
  void resetToEOL(char *word, unsigned char *flag, char *expectedKeycode, FILE *fPtr, LineTracker *tracker);
  ```
  * Resets lexical analyzer. After an error lexical analyzers stops reading and resets itself to new line 
    (After '.' character)


* ```c 
  void err(char *word, KeyWord *root, char *expectedKeycode, unsigned char *flag, FILE *fPtr, LineTracker *tracker);
  ```
  * This function handles all errors.
  * Prints Expected word, read word, line information about error.
  * Resets lexical analyzer

* ```c 
  void checkBlocks(BlockKeeper *blockKeeper);
  ```
  * Checks for blocks which is/are left open.
  * If there is one, Prints information about left open block/s
  
## Main program loop
1. Initialize all necessary structs and variables
2. While loop:
    1. If we reach end of file, exit the loop
    2. Get word using `getWord` function
    3. Check if the word is empty `strcmp(currWord, "")`
    4. Check if the word is keyword
    5. If flag and word do not match, give error and seek to end of line
    6. Else write analysis results to write file.
    7. If word is a keyword, set flag and expectedKeycode. Otherwise, set flag to NOP
  
3. Check if any of the block/s are left open
4. Check if flag is LINE_ENDED
5. Free all allocated memory

    

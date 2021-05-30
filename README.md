#Lexical Analyzer for BigAdd Language
##Big Add language
BigAdd language is a small programming language that has been designed in order to add and subtract
big integers programmatically and display the result on the screen.

BigAdd is an interpreted language. The BigAdd interpreter works from the command line with the command BA, and takes the script
file’s name as the only attribute. The script file is assumed to have the extension .ba .

example: The command `c:\> ba myscript`
must load and execute the script file called myscript.ba

##Lexical analyzers data structures
### KeyWord
####KeyWord Struct
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
####Keyword functions
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

###IdentifierKeeper
####Identifier Struct
```c
typedef struct identifierNode {
char *name; // Identifier name
int val; // Identifiers' value (not used yet)
struct identifierNode *next; // next Identifier
} Identifier;
```
####IdentifierKeeper Struct
```c
typedef struct identifierKeeper {
unsigned int size; // root of Linked List
Identifier *root; // size of list
} IdentifierKeeper;
```
Keeps all declared Identifiers and its values in Linked List. 

####IdentifierKeeper functions

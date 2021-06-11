# word.h

## Word Struct
```c
typedef struct wordStruct{
    char* word;
    unsigned int size;
}Word;
```
Keeps a string and its size.

## Word Functions

* ```c 
  Word* createWord();
  ```
    * Creates a Word Struct and returns its pointer.

* ```c 
  void expandWord(Word* word)
  ```
    * Expands char array in given Word. (Size is 2 times of old size)

* ```c 
  void shrinkWord(Word* word)
  ```
    * Shrinks char array in given Word. (Size predefined)

* ```c 
  void freeWord(Word* word);
  ```
    * Frees given Word.

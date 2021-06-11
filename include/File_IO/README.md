# fileio.h

* ```c 
  FILE *openFile(char *path, char *mode);
  ```
    * Opens file at the given path. If it fails, print an error message.
    
* ```c 
  bool skipIgnoreChars(FILE *fPtr, LineTracker *tracker);
  ```
    * Skips all unimportant characters in given file. Unimportant characters are:
        * White Space (' ')
        * Line break ('\n')
        * Carriage return ('\r')
        * Tab character ('\t'')
    * Returns true if a character skipped.

* ```c 
  bool skipCommentBlocks(FILE *fPtr, LineTracker *tracker);
  ```
    * Skips Comment blocks. Returns true if a comment block skipped

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
        * If the first character read is Lexeme String (' \" '), Reads until another Lexeme String. If can't find another Lexeme String, returns.

        * Otherwise, reads until the end of word. (Word termination characters are one of above, White space and COMMENT_OPEN)
# errhandle.h

* ```c 
  void err(char *word, KeyWord *root, char *expectedKeycode, unsigned char *flag, FILE *fPtr, LineTracker *tracker);
  ```
    * This function handles all errors.
    * Prints Expected word, read word, line information about the error.
    * Resets lexical analyzer

* ```c 
  void checkBlocks(BlockKeeper *blockKeeper);
  ```
    * Checks for blocks which is/are left open.
    * If there is one, Prints information about left open block/s

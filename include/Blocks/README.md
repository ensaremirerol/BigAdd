# blocks.h

## Block Struct

```c
typedef struct blockNode {
    unsigned int lineStarted;
    long long int fPointer;
    long long int *loopCounter;
    bool isIntConstant;
    bool isShortHandLoop;
    struct blockNode *nests;
} Block;
```

## BlockKeeperStruct

```c
typedef struct blockKeeper {
    unsigned int totalBlocks;
    Block *root;
} BlockKeeper;
```

Keeps all opened blocks, where they opened(file position ,via fteel function, and line), its loop counter(pointer to the Identifier value or IntConstant).
When two blocks nested, the nested block linked inside the parent block.

* isIntConstant: Is loop counter a IntConstant? If it is, free loop counter after loop.
* isShortHandLoop: Is it a one line loop? If it is, Decrement loopCounter after End of Line.

## BlockKeeper Functions

* ```c 
  void openBlock(BlockKeeper *blockKeeper, long long int *loopCounter, unsigned int line, unsigned long long int fPointer,
   bool isIntConstant, bool isShortHandLoop);
  ```
    * Opens a new block. Nests new block if already a block opened.

* ```c 
  bool closeBlock(BlockKeeper *blockKeeper);
  ```
    * Closes the deepest block. If there is no block to close, returns false.

* ```c 
  unsigned int closeBlockAndGetLine(BlockKeeper *blockKeeper);
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
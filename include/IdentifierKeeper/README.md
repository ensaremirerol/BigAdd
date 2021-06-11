# identifier.h

## Identifier Struct
```c
typedef struct identifierNode {
  char *name; // Identifier name
  int val; // Identifiers' value (not used yet)
  struct identifierNode *next; // next Identifier
} Identifier;
```

## IdentifierKeeper Struct
```c
typedef struct identifierKeeper {
  unsigned int size; // root of Linked List
  Identifier *root; // size of list
} IdentifierKeeper;
```

Keeps all declared Identifiers and their values in Linked List.

## IdentifierKeeper Functions

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
  

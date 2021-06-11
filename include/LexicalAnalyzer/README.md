# lxanalyzer.h

## LexicalData struct
```c
typedef struct lexicalDataKeeper{
    FILE* fPtr;
    Word* currWord;
    KeyWord *currKeyword;
    unsigned int currLine;
}LexicalData;
```

Keeps lexical analyzers' data.

## Functions

* ```c
    TokenType lexicalAnalyzer(LexicalData* data, KeyWord *root);
    ```
  Gets next word in file and determines its TokenType. If it is a Keyword, assigns currKeyword pointer in
  the data(Lexical Data) to that keywords' pointer.

* ```c
    void freeLexicalData(LexicalData* data);
    ```
  Frees given LexicalData.
  
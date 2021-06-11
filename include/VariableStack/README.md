# variable.h

## Variable Struct
```c
typedef struct variableStack{
    DataType dataType;
    void* data;
    struct variableStack *next;
}Variable;
```

Keeps given variables for operations.

## enum DataType

Data stored in variable as void pointer.
Operation functions casts void pointer according to the dataType.
DataTypes are:
* dIdentifier
* dIntConstant
* dStringConstant

## Variable Functions

* ```c 
  Variable* addVariable(Variable* curr, void* data, DataType type);
  ```
    * Adds given data to given stack

* ```c 
  void freeVariableStack(Variable* curr);
  ```
    * Frees given variable stack


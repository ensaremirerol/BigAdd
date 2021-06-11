#include <stdio.h>
#include "../include/File_IO/fileio.h"
#include "../include/Parser/parser.h"
int main(int argc, char** argv) {
    if (argc == 2){
        char* fPath = malloc(strlen(argv[1]) + 4);
        sprintf(fPath, "%s.ba", argv[1]);
        FILE *fPtr = openFile(fPath, "r");
        LexicalData *data = malloc(sizeof (LexicalData));
        data->fPtr = fPtr;
        data->currLine = 1;
        data->currKeyword = NULL;
        data->currWord = createWord();
        parser(data);
        freeLexicalData(data);
        free(fPath);
        return 0;
    }
}

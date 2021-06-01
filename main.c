#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "fileio.h"
#include "keyword.h"
#include "errhandle.h"
#include "identifier.h"

#define BUFFER_SIZE 1024

int lexical_analyzer(char* fPath) {
    char *wPath;
    size_t len = strlen(fPath);
    wPath = (char *) malloc((sizeof(char) * len) + 1);
    strcpy(wPath, fPath);
    len = strlen(wPath);
    wPath[len - 1] = 'x';
    wPath[len - 2] = 'l';

    // Lexical analyzer variables
    unsigned char flags = LINE_ENDED;
    char expectedKeyCode = -1;
    // END

    // KeyWord
    /*
     * Keeps all keywords.
     * Keyword:
     *  - keyword: keyword. (as char array)
     *  - keycode: it's code.
     *  - expectedKeycode: Expected keycode after this keyword.
     *  - flagsForKeyword: Expected flag for this keyword to be used.
     *  - flagsForNextWord: Expected flag for next "word". (It could be anything (Identifier, String, Int, ...))
     *  - next: next Keyword.
     */
    KeyWord *currKeyWord;
    KeyWord *keyWordRoot;
    keyWordRoot = createKeyWordLinkedList();
    // END

    // IdentifierKeeper
    /*
     * Keeps all declared Identifiers and its values
     * It uses Linked List as Structure
     * Identifier:
     *  - name: Identifier name.
     *  - val: Identifiers' value (not used yet)
     *  - next: next Identifier
     * IdentifierKeeper:
     *  - root: root of Linked List
     *  - size: size of list
     */
    IdentifierKeeper *identifierKeeper;
    identifierKeeper = createIdentifierKeeper();
    // END

    // BlockKeeper
    /*
     * Keeps all all opened blocks and where it opened
     * It uses Linked List as Structure
     * When two blocks are nested, nested block linked inside first block
     * Block:
     *  - lineStarted: Blocks' start line.
     *  - nests: Points nested block.
     * BlockKeeper:
     *  - root: Root of linked list.
     *  - totalBlocks: Count of currently open blocks
     */
    BlockKeeper *blockKeeper;
    blockKeeper = createBlockKeeper();
    // END

    // Files
    FILE *fPtr = openFile(fPath, "r");
    if(fPtr == NULL) return 1;
    FILE *wPtr = openFile(wPath, "w");
    if(wPtr == NULL) return 1;
    // Tracker for current line in Read pointer
    LineTracker *tracker;
    tracker = createLineTracker();
    // END

    char *currWord;
    currWord = malloc(BUFFER_SIZE);

    while (true) {
        // End of file check
        if (feof(fPtr)) break;
        // Gets next word from file
        getWord(currWord, fPtr, tracker, BUFFER_SIZE);
        // In some cases currWord returns empty (""). It usually indicates end of file.
        // So to be sure we go back to the start of the while loop.
        if (strcmp(currWord, "") == 0) continue;
        // Try to get KeyWord according to currWord
        currKeyWord = getKeyWord(currWord, keyWordRoot);
        // If current state of lexical analyzer does not expects keyword
        if ((flags & KEYWORD_EXPECTED) == 0) {
            // Is currWord a keyWord
            if (currKeyWord) {
                /*
                 * If currWord is a keyWord
                 * 1-) This is a Error
                 * 2-) KeyWord is "newline"
                 * "newline" is a Key Word but lexical analyzer treats as a not keyword because of
                 * flags. "newline" KeyWord only can come after "out" keyword (flags==OUT_LIST)
                 */
                // keycode 9 is keycode of "newline"
                if (!(currKeyWord->keycode == 9 && flags == OUT_LIST)) {
                    err(currWord, keyWordRoot, &expectedKeyCode, &flags, fPtr, tracker, BUFFER_SIZE);
                    continue;
                }
                fprintf(wPtr, "Keyword newline\n");
                flags = currKeyWord->flagsForNextWord;
                expectedKeyCode = currKeyWord->expectedKeycode;
                continue;
            }

                // Is currWord a identifier and is it expected?
            else if (isIdentifier(currWord) && (flags & IDENTIFIER_EXPECTED) != 0) {
                // Are we declaring a identifier?
                if ((flags & IDENTIFIER_DECLARE) == IDENTIFIER_DECLARE) {
                    // Declare identifier if not. If it's already declared give error
                    if (!declareIdentifier(currWord, identifierKeeper)) {
                        err(currWord, keyWordRoot, &expectedKeyCode, &flags, fPtr, tracker, BUFFER_SIZE);
                        continue;
                    }
                }
                    // Are we using a identifier?
                else if ((flags & IDENTIFIER_USE) == IDENTIFIER_USE) {
                    // Has identifier declared?
                    if (!isIdentifierDeclared(currWord, identifierKeeper)) {
                        err(currWord, keyWordRoot, &expectedKeyCode, &flags, fPtr, tracker, BUFFER_SIZE);
                        continue;
                    }
                }
                fprintf(wPtr, "Identifier %s\n", currWord);
            }
                // Is currWord a IntConstant and is it expected?
            else if (isIntConstant(currWord) && (flags & INT_EXPECTED) == INT_EXPECTED)
                fprintf(wPtr, "IntConstant %s\n", currWord);
                // Is currWord a String and is it expected?
            else if (isStringConstant(currWord, tracker) && (flags & STRING_EXPECTED) == STRING_EXPECTED)
                fprintf(wPtr, "StringConstant %s\n", currWord);
            else {
                err(currWord, keyWordRoot, &expectedKeyCode, &flags, fPtr, tracker, BUFFER_SIZE);
                // After error we are continue the loop because we don't want to set flag to NOP
                // In err flag reseted.
                continue;
            }
            flags = NOP;
        }
            // If keyword expected (LINE_ENDED or NOP)
        else if (currKeyWord && (flags & KEYWORD_EXPECTED) != 0) {
            /*
             * If
             * 1-) Keywords' flag and keycode matches current flag and expected keycode
             * 2-) Flags' LINE_ENDED BIT is 1 and expected keycode is -1
             * 3-) Flag is NOP, expected keycode is 12(',') and current keywords' keycode is 11('.')
             *     (Exception for "out")
             */
            if (((flags & currKeyWord->flagsForKeyword) == currKeyWord->flagsForKeyword &&
                 expectedKeyCode == currKeyWord->keycode) || ((flags & LINE_ENDED) != 0 && expectedKeyCode == -1) ||
                (flags == NOP && expectedKeyCode == 12 && currKeyWord->keycode == 11)) {
                switch (currKeyWord->keycode) {
                    case 0:
                        fprintf(wPtr, "Keyword int\n");
                        break;
                    case 1:
                        fprintf(wPtr, "Keyword move\n");
                        break;
                    case 2:
                        fprintf(wPtr, "Keyword add\n");
                        break;
                    case 3:
                        fprintf(wPtr, "Keyword sub\n");
                        break;
                    case 4:
                        fprintf(wPtr, "Keyword out\n");
                        break;
                    case 5:
                        fprintf(wPtr, "Keyword loop\n");
                        break;
                    case 6:
                        // Are we expecting a block?
                        if ((flags & BLOCK_EXPECTED) == BLOCK_EXPECTED) {
                            openBlock(blockKeeper, getLine(tracker));
                            fprintf(wPtr, "OpenBlock\n");
                        } else
                            err(currWord, keyWordRoot, &expectedKeyCode, &flags, fPtr, tracker, BUFFER_SIZE);
                        break;
                    case 7:
                        // Is/Are there any block/s?
                        if (closeBlock(blockKeeper))
                            fprintf(wPtr, "CloseBlock\n");
                        else
                            err(currWord, keyWordRoot, &expectedKeyCode, &flags, fPtr, tracker, BUFFER_SIZE);
                        break;
                    case 8:
                        fprintf(wPtr, "Keyword times\n");
                        break;
                    case 9:
                        fprintf(wPtr, "Keyword newline\n");
                        break;
                    case 10:
                        fprintf(wPtr, "Keyword to\n");
                        break;
                    case 11:
                        fprintf(wPtr, "EndOfLine\n");
                        break;
                    case 12:
                        fprintf(wPtr, "Separator\n");
                        break;
                    case 13:
                        fprintf(wPtr, "Keyword from\n");
                        break;
                    default:
                        fprintf(stderr, "Unexpected error! Exiting\n");
                        exit(-1);
                }
                // Set flag and expectedKeyCode to next word.
                flags = currKeyWord->flagsForNextWord;
                expectedKeyCode = currKeyWord->expectedKeycode;

            } else err(currWord, keyWordRoot, &expectedKeyCode, &flags, fPtr, tracker, BUFFER_SIZE);
        } else err(currWord, keyWordRoot, &expectedKeyCode, &flags, fPtr, tracker, BUFFER_SIZE);
    }
    // Is/Are there any block/s left open?
    checkBlocks(blockKeeper);

    // Is line ended after last line?
    if (flags != LINE_ENDED) {
        fprintf(stderr, "No \"End line\"(\".\") character found at line %d\n", getLine(tracker));
    }

    // Free all unused memory and close the files.
    freeIdentifierKeeper(identifierKeeper);
    freeBlockKeeper(blockKeeper);
    freeKeyWordLinkedList(keyWordRoot);
    free(tracker);
    free(currWord);
    free(wPath);
    fclose(fPtr);
    fclose(wPtr);
    return 0;
}

int main(){
    char *pwd = malloc(1000);
    if(getcwd(pwd, 1000) == NULL){
        perror("Error during trying to get working directory");
        return 1;
    }
    char* command = malloc(BUFFER_SIZE);
    char* fPath = malloc(BUFFER_SIZE);
    strclr(command, BUFFER_SIZE);
    strclr(fPath, BUFFER_SIZE);
    printf("%s:\\> ", pwd);
    scanf("%s %s", command, fPath);
    if(strcmp(command, "la") == 0){
        lexical_analyzer(fPath);
    }
    free(pwd);
    free(fPath);
    free(command);
    return 0;
}

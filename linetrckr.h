//
// Created by ensar on 5/20/2021.
//

#ifndef LEXICAL_LINETRCKR_H
#define LEXICAL_LINETRCKR_H

typedef struct lineTracker {
    int currLine;
} LineTracker;

int getLine(LineTracker *tracker) {
    return tracker->currLine;
}

void incrementLine(LineTracker *tracker) {
    tracker->currLine++;
}

LineTracker *createLineTracker() {
    LineTracker *tracker = (LineTracker *) malloc(sizeof(LineTracker));
    tracker->currLine = 1;
    return tracker;
}

#endif //LEXICAL_LINETRCKR_H

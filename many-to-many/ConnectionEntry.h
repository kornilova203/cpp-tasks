//
// Created by Liudmila Kornilova on 26.05.17.
//

#ifndef MANY_TO_MANY_CONNECTIONENTRY_H
#define MANY_TO_MANY_CONNECTIONENTRY_H

#include "BaseEntry.h"

class ConnectionEntry : BaseEntry {
public:
    ConnectionEntry(BaseEntry *left_, BaseEntry *right_) {
        left = left_;
        right = right_;
    }

    int isConnectionEntry() const {
        return 1;
    }

    BaseEntry *left;
    BaseEntry *right;
};


#endif //MANY_TO_MANY_CONNECTIONENTRY_H

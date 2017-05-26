//
// Created by Liudmila Kornilova on 16.05.17.
//

#ifndef MULTIPLETOMULTIPLE_ENTRY_H
#define MULTIPLETOMULTIPLE_ENTRY_H

class BaseEntry {
public:
    virtual int isConnectionEntry() const {
        return 0;
    };
};

#endif //MULTIPLETOMULTIPLE_ENTRY_H

#include "scj_hash.h"

// http://www.cse.yorku.ca/~oz/hash.html
// djb2
unsigned long scj_hash(const char* str) {
        unsigned long hash = 5381;
        int c;
        while ((c = *str++)) {
                hash = ((hash << 5) + hash) + c;
        }
        return hash;
}

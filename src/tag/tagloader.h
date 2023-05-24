#ifndef TAGLOADER_H
#define TAGLOADER_H

#include "ITag.h"

typedef ITag TagChain;

namespace TagLoader {
    TagChain *load();
}

#endif // TAGLOADER_H

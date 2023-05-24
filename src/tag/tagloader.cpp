#include "tagloader.h"

#include "coretag.h"
#include "seqtag.h"


TagChain *TagLoader::load()
{
    CoreTag *core = new CoreTag;
    SeqTag *seq = new SeqTag;

    core->setNext(seq);
    return core;
}

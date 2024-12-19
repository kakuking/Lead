#pragma once

#include <lead/common.h>

LEAD_NAMESPACE_BEGIN

// A thread will handle a block
struct Block {
    int blockSize;
    int blockOffsetX, blockOffsetY;
    int blockLenX, blockLenY;
};

LEAD_NAMESPACE_END
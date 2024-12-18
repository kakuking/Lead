#pragma once

#include <lead/common.h>
#include <lead/sampler.h>

// A thread will handle a block
struct Block {
    int blockSize;
    int blockOffsetX, blockOffsetY;
    int blockLenX, blockLenY;
};

class Renderer {
public:
    Renderer(const Scene* scene) {
        m_scene = scene;
    }

    void setBlocksize(int newSize) {
        m_blocksize = newSize;
    }

protected:
    const Scene* m_scene;
    Sampler* m_sampler;

    int m_blocksize;

    std::vector<Color3f> *image;
};
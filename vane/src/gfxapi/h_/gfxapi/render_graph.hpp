#pragma once

#include "vane/objmanager.hpp"
#include "vane/inplace_set.hpp"
#include <memory>
#include <vector>


namespace vane::gfxapi
{
    class RenderEngine;

    class RenderGraph;
    class RenderNode;
    class RenderNodeGroup;
}


class vane::gfxapi::RenderNode
{
private:

public:
    std::vector<RenderNode*> children;
};



class vane::gfxapi::RenderGraph
{
private:
    RenderNode *mRoot;

public:
    RenderGraph(size_t max_objs = 4096)
    :   mRoot(new RenderNode())
    {

    }

    RenderNode *rootNode()
    {
        return mRoot;
    }


    // int makeNode()
    // {
    //     for (int i=0; i<mNodes.size(); i++)
    //     {
    //         if (mMask[i] == false)
    //         {
    //             new (&mNodes[i]) RenderNode();
    //             mMask[i] = true;
    //             return i;
    //         }
    //     }
    //     return -1;
    // }

    // void freeNode(int idx)
    // {
    //     (&mNodes[idx])->~RenderNode();
    // }
};



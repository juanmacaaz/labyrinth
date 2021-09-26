#pragma once

#include <reactphysics3d/reactphysics3d.h>
using namespace reactphysics3d;

class Common
{
public:
    static PhysicsCommon& getPhysicsInstance()
    {
        static PhysicsCommon instance;
        return instance;
    }

    Common(Common const&) = delete;
    void operator=(Common const&) = delete;
};


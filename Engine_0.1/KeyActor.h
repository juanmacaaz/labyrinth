#pragma once
#include "Key.h"
class KeyActor :
    public Key
{
public:
    KeyActor(GameSpace* space, Vector3 initPosition);
    void update();

public:

    GameSpace* space_c;
};


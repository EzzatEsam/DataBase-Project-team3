#pragma once
#include "Enemy.h"
class Healer :
    public Enemy
{
public:
    Healer(int id, int arrive, int hp, int atk, int relode, int ms);
    void Move();
    void Act();
};


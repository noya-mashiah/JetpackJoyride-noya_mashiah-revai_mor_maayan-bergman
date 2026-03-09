#pragma once
#include "StaticObject.h"

/*
* an abstract class represnts an obstacle in the game
*/

class Obstacles : public StaticObject
{
public:
	Obstacles() = default;

	using StaticObject::StaticObject;

	virtual ~Obstacles() = default;
};

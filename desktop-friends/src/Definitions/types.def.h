#pragma once
#ifndef DF_TYPES
#define DF_TYPES

#include <vector>
#include <utility>
#include <string>
#include "../Entity/Entity.h"

typedef std::vector<Entity> Entities;
typedef std::pair<float, float> Pos;


enum EntityState {
	idle = 0,
	walking,
	happy,
	sleep
};

enum EntityType {
	player = 0,
	visitor,
	enemy,
	object
};

#endif // !DF_TYPES

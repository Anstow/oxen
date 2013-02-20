#pragma once

#include "PhysicsEntity.h"
#include "RenderEntity.h"

class Entity
{
public:
	Entity();
	~Entity();

private:
	PhysicsEntity* m_pPhys;
	RenderEntity* m_pRend;
}

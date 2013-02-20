#pragma once

#include "Networking/NetworkedEntity.h"
#include <list>

class EntityMgr
{
public:
	EntityMgr();
	~EntityMgr();

	void addEntity(NetworkedEntity& entity);
	void addEntityPtr(NetworkedEntity* pEntity);

	void removeEntity(NetworkedEntity& entity);
	void removeEntityPtr(NetworkedEntity* pEntity);
	
	void updateLists();
	
	NetworkedEntity getEntityAtPostition(int postition);
	NetworkedEntity* getEntityPtrAtPostition(int postition);

	int getPositionOfEntity(const NetworkedEntity& entity);
	int getPositionOfEntityPtr(const NetworkedEntity* pEntity);

	bool entityExists(const NetworkedEntity& ent);
	bool entityPtrExists(const NetworkedEntity* pEnt);

private:
	NetworkedEntity** m_pCurrentEntities;
	std::list<NetworkedEntity*> m_addedEntities;
	std::list<int> m_removedEntities;
};

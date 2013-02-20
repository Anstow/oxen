#include "EntityMgr.h"
#include <vector>
#include <iterator>

EntityMgr::EntityMgr()
	:m_pCurrentEntities(0),
	 m_addedEntities(),
	 m_removedEntities()
{
}

EntityMgr::~EntityMgr()
{
	if (m_pCurrentEntities) {
		delete [] m_pCurrentEntities;
	}
}

////////////////////////////////////////////////////////////////////////////////

void EntityMgr::addEntity(NetworkedEntity& entity) {
	m_addedEntities.push_front(&entity);
}

void EntityMgr::addEntityPtr(NetworkedEntity* pEntity) {
	m_addedEntities.push_front(pEntity);
}

////////////////////////////////////////////////////////////////////////////////

void EntityMgr::removeEntity(NetworkedEntity& entity) {
	int entPos = getPositionOfEntity(entity);
	if (entPos > 0) {
		m_removedEntities.push_front(entPos);
	}
}

void EntityMgr::removeEntityPtr(NetworkedEntity* pEntity) {
	int entPos = getPositionOfEntityPtr(pEntity);
	if (entPos > 0) {
		m_removedEntities.push_front(entPos);
	}
}

////////////////////////////////////////////////////////////////////////////////

void EntityMgr::updateLists() {
	// First we sort the removed Entities to make it quicker to remove them
	m_removedEntities.sort();

	std::vector<NetworkedEntity*> templist = std::vector<NetworkedEntity*>();

	int currentEnt = m_removedEntities.front();
	for (int i = 0; i < sizeof m_pCurrentEntities; i++) {
		if (i == currentEnt) {
			m_removedEntities.pop_front();
			if (!m_removedEntities.empty()) {
				currentEnt = m_removedEntities.front();
			}
		} else {
			templist.push_back(m_pCurrentEntities[i]);
		}
	}

	while (!m_removedEntities.empty()) {
		m_removedEntities.pop_front();
	}

	while (!m_addedEntities.empty()) {
		templist.push_back(m_addedEntities.front());
		m_addedEntities.pop_front();
	}
	
	delete m_pCurrentEntities;

	m_pCurrentEntities = new NetworkedEntity*[templist.size()];
	for (int i = 0; i < templist.size(); ++i) {
		m_pCurrentEntities[i] = templist[i];
	}
}

////////////////////////////////////////////////////////////////////////////////

NetworkedEntity EntityMgr::getEntityAtPostition(int postition) {
	return *m_pCurrentEntities[postition];
}

NetworkedEntity* EntityMgr::getEntityPtrAtPostition(int postition) {
	return m_pCurrentEntities[postition];
}

int EntityMgr::getPositionOfEntity(const NetworkedEntity& entity) {
	return getPositionOfEntityPtr(&entity);;
}

int EntityMgr::getPositionOfEntityPtr(const NetworkedEntity* pEntity){
	for (int i = 0; i < sizeof m_pCurrentEntities; ++i){
		if (m_pCurrentEntities[i] == pEntity) {
			return i;
		}
	}
	return -1;
}

////////////////////////////////////////////////////////////////////////////////

bool EntityMgr::entityExists(const NetworkedEntity& ent) {
	return getPositionOfEntity(ent) >= 0;
}

bool EntityMgr::entityPtrExists(const NetworkedEntity* pEnt) {
	return getPositionOfEntityPtr(pEnt) >= 0;
}

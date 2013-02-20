#include "RenderEntity.h"

RenderEntity::RenderEntity(Ogre::SceneNode* pRootNode, Ogre::SceneManager* pSceneMgr)
	: m_pEntityNode(pRootNode->createChildSceneNode())
	, m_pSceneMgr(pSceneMgr)
	, m_pEntity(0)
{
}

RenderEntity::~RenderEntity() {
	// NOTE: The scene manager should be deleted somewhere else so no need to
	//       clean up here, this inculdes not cleaning up the m_pEntityNode and
	//       m_pEntity
}

void RenderEntity::loadMesh(const Ogre::String &sourceSrt) {
	if (m_pEntity) m_pSceneMgr->destroyEntity(m_pEntity);

	m_pEntity = m_pEntity = m_pSceneMgr->createEntity(sourceSrt);
	m_pEntityNode->attachObject(m_pEntity);
}

void RenderEntity::loadMesh(const Ogre::MeshPtr &pMesh) {
	if (m_pEntity) m_pSceneMgr->destroyEntity(m_pEntity);

	m_pEntity = m_pSceneMgr->createEntity(pMesh);
	m_pEntityNode->attachObject(m_pEntity);
}

void RenderEntity::updateDirection(const Ogre::Quaternion &direction) {
	m_pEntityNode->setOrientation(direction);
}

void RenderEntity::updatePosition(const Ogre::Vector3 &position) {
	m_pEntityNode->setPosition(position);
}

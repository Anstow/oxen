#pragma once

#include "InterEntity.h"

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreQuaternion.h>
#include <OgreVector3.h>
#include <OgreEntity.h>
#include <OgreMesh.h>

class RenderEntity
{
public:
	RenderEntity(Ogre::SceneNode* pRootNode, Ogre::SceneManager* pSceneMgr);
	~RenderEntity();

	void loadMesh(const Ogre::String &sourceSrt);
	void loadMesh(const Ogre::MeshPtr &pMesh);

	void updateDirection(const Ogre::Quaternion &direction);
	void updatePosition(const Ogre::Vector3 &position);

	void addInterEntity(InterEntity* interEnt);

private:
	Ogre::SceneNode* m_pEntityNode;
	Ogre::SceneManager* m_pSceneMgr;
	Ogre::Entity* m_pEntity;
};

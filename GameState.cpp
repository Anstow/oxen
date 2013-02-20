#include "GameState.h"

#include <OgrePrerequisites.h>
#include <OgreVector3.h>

GameState::GameState()
	: m_pGameEngine(new Engine()),
	testEnt(0)
{
	// TODO: Load hud
}

GameState::~GameState()
{
	Framework::getSingletonPtr()->m_pLog->logMessage("Delete GameEngine");
	if (m_pGameEngine) delete m_pGameEngine;
	Framework::getSingletonPtr()->m_pLog->logMessage("Delete TestEntity");
	if (testEnt) delete testEnt;
	Framework::getSingletonPtr()->m_pLog->logMessage("Done closing game state");
}

void GameState::enter() {
	// TODO: Do anything which isn't creating the scene for example set the hud
	Framework::getSingletonPtr()->m_pLog->logMessage("Entering GameState...");
	m_bQuit = false;

	// Create the SceneManager
	m_pSceneMgr = Framework::getSingletonPtr()->m_pRoot->createSceneManager(Ogre::ST_GENERIC, "GameSceneMgr");
	m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

	// Create the camera
	m_pCamera = m_pSceneMgr->createCamera("MenuCamera");
	m_pCamera->setPosition(Ogre::Vector3(0, 25, -50));
	m_pCamera->lookAt(Ogre::Vector3(0, 0, 0));
	m_pCamera->setNearClipDistance(1);

	m_pCamera->setAspectRatio(Ogre::Real(Framework::getSingletonPtr()->m_pViewport->getActualWidth()) / Ogre::Real(Framework::getSingletonPtr()->m_pViewport->getActualHeight()));

	Framework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);

	Framework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
	Framework::getSingletonPtr()->m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
	Framework::getSingletonPtr()->m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
	
	createScene();
}

void GameState::createScene() {
	// TODO: create the scene
	testEnt = new RenderEntity(m_pSceneMgr->getRootSceneNode(),m_pSceneMgr);
	testEnt->loadMesh("cube.mesh");

	testEnt2 = new RenderEntity(m_pSceneMgr->getRootSceneNode(),m_pSceneMgr);
	testEnt2->loadMesh("cube.mesh");
	testEnt2->updatePosition(Ogre::Vector3(1.0f,1.0f,1.0f));
}

void GameState::exit() {
	Framework::getSingletonPtr()->m_pLog->logMessage("Leaving GameState...");

	// Remove the camera
	m_pSceneMgr->destroyCamera(m_pCamera);
	if (m_pSceneMgr) {
		Framework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);
		delete testEnt;
		testEnt = 0;
		delete testEnt2;
		testEnt2 = 0;
	}

	// Remove tray data
	Framework::getSingletonPtr()->m_pTrayMgr->clearAllTrays();
	Framework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
	Framework::getSingletonPtr()->m_pTrayMgr->setListener(0);
}

void GameState::update(double timeSinceLastFrame) {
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    Framework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued(m_FrameEvent);
 
    if(m_bQuit == true)
    {
		Framework::getSingletonPtr()->m_pLog->logMessage("Game State Quit");
		popAllAndPushAppState(m_pParent->findByName("MainMenu"));
        return;
    }
}

////////////////////////////////////////////////////////////////////////////////

bool GameState::keyPressed(const OIS::KeyEvent &keyEventRef) {
	if (Framework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE)) {
		m_bQuit = true;
		return true;
	}
	
	Framework::getSingletonPtr()->keyPressed(keyEventRef);
	return true;
}

bool GameState::keyReleased(const OIS::KeyEvent &keyEventRef) {
	Framework::getSingletonPtr()->keyReleased(keyEventRef);
	return true;
}

bool GameState::mouseMoved(const OIS::MouseEvent &evt) {
	if(Framework::getSingletonPtr()->m_pMenuMgr->InjectOISMouseMove(evt)) {
		return true;
	} else if (Framework::getSingletonPtr()->m_pTrayMgr->injectMouseMove(evt)) {
		return true;
	}
	return true;
}

bool GameState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
	if(Framework::getSingletonPtr()->m_pMenuMgr->InjectOISMouseButtonDown(evt, id)) {
		return true;
	} else if(Framework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id)) {
		return true;
	}
    return true;
}
 
bool GameState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
	if(Framework::getSingletonPtr()->m_pMenuMgr->InjectOISMouseButtonUp(evt, id)) {
		return true;
	} else if(Framework::getSingletonPtr()->m_pTrayMgr->injectMouseUp(evt, id)) {
		return true;
	}
    return true;
}

////////////////////////////////////////////////////////////////////////////////

bool GameState::moveCamera() {
	Ogre::Vector2* mousePos = m_pMenuMgr->getPosition();
}

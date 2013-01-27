#include "MainMenu.h"
#include <CEGUIWindow.h>

using namespace Ogre;

////////////////////////////////////////////////////////////////////////////////

MainMenu::MainMenu() {
	m_bQuit = false;
	m_FrameEvent = Ogre::FrameEvent();
}

void MainMenu::enter() {
	Framework::getSingletonPtr()->m_pLog->logMessage("Entering MainMenu...");

	// Create the SceneManager
	m_pSceneMgr = Framework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "MenuScenceMgr");
	m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

	// Create the camera
	m_pCamera = m_pSceneMgr->createCamera("MenuCamera");
	m_pCamera->setPosition(Vector3(0, 25, -50));
	m_pCamera->lookAt(Vector3(0, 0, 0));
	m_pCamera->setNearClipDistance(1);

	m_pCamera->setAspectRatio(Real(Framework::getSingletonPtr()->m_pViewport->getActualWidth()) / Real(Framework::getSingletonPtr()->m_pViewport->getActualHeight()));

	Framework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);

	Framework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
	Framework::getSingletonPtr()->m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
	Framework::getSingletonPtr()->m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);

	createScene();
}

////////////////////////////////////////////////////////////////////////////////

void MainMenu::createScene() {
	try {
		CEGUI::Window* pMenu = CEGUI::WindowManager::getSingleton().loadWindowLayout("MainMenu.layout");
		pushMenu(pMenu);
	} catch (CEGUI::Exception &e) {
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, e.getMessage().c_str(), "Error Parsing Menu");
		shutdown();
	}

}

////////////////////////////////////////////////////////////////////////////////

void MainMenu::exit() {
	Framework::getSingletonPtr()->m_pLog->logMessage("Leaving MainMenu...");

	// Remove the camera
	m_pSceneMgr->destroyCamera(m_pCamera);
	if (m_pSceneMgr) {
		Framework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);
	}

	// Remove tray data
	Framework::getSingletonPtr()->m_pTrayMgr->clearAllTrays();
	Framework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
	Framework::getSingletonPtr()->m_pTrayMgr->setListener(0);
}

////////////////////////////////////////////////////////////////////////////////

bool MainMenu::keyPressed(const OIS::KeyEvent &keyEventRef) {
	if (Framework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE)) {
		m_bQuit = true;
		return true;
	}
	
	Framework::getSingletonPtr()->keyPressed(keyEventRef);
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool MainMenu::keyReleased(const OIS::KeyEvent &keyEventRef) {
	Framework::getSingletonPtr()->keyReleased(keyEventRef);
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool MainMenu::mouseMoved(const OIS::MouseEvent &evt) {
	if(Framework::getSingletonPtr()->m_pMenuMgr->InjectOISMouseMove(evt)) {
		return true;
	} else if (Framework::getSingletonPtr()->m_pTrayMgr->injectMouseMove(evt)) {
		return true;
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////

bool MainMenu::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
	if(Framework::getSingletonPtr()->m_pMenuMgr->InjectOISMouseButtonDown(id)) {
		return true;
	} else if(Framework::getSingletonPtr()->m_pTrayMgr->injectMouseDown(evt, id)) {
		return true;
	}
    return true;
}
 
////////////////////////////////////////////////////////////////////////////////
 
bool MainMenu::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
	if(Framework::getSingletonPtr()->m_pMenuMgr->InjectOISMouseButtonUp(id)) {
		return true;
	} else if(Framework::getSingletonPtr()->m_pTrayMgr->injectMouseUp(evt, id)) {
		return true;
	}
    return true;
}

////////////////////////////////////////////////////////////////////////////////

void MainMenu::update(double timeSinceLastFrame) {
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;
    Framework::getSingletonPtr()->m_pTrayMgr->frameRenderingQueued(m_FrameEvent);
 
    if(m_bQuit == true)
    {
        shutdown();
        return;
    }
}


#include "AppStateManager.h"

#include <OgreWindowEventUtilities.h>

////////////////////////////////////////////////////////////////////////////////

AppStateManager::AppStateManager()
	: m_bShutdown(false)
	, m_pFramework(Framework::getSingletonPtr())
{
}

////////////////////////////////////////////////////////////////////////////////

AppStateManager::~AppStateManager() {
	state_info si;

	// Clears all the running states
    while(!m_ActiveStateStack.empty()) {
		m_ActiveStateStack.back()->exit();
		m_ActiveStateStack.pop_back();
	}


	Framework::getSingletonPtr()->m_pLog->logMessage("Clear states");
	// Removes the preloaded states
	while(!m_States.empty()) {
		si = m_States.back();
        si.state->destroy();
        m_States.pop_back();
	}
}

////////////////////////////////////////////////////////////////////////////////

void AppStateManager::manageAppState(Ogre::String stateName, AppState* state) {
	// Try to create a new state preloaded state
	// TODO: Do I really need to preload states?
	try {
		state_info new_state_info;
		new_state_info.name = stateName;
		new_state_info.state = state;
		m_States.push_back(new_state_info);
	} catch(std::exception& e) {
		delete state;
		throw Ogre::Exception(Ogre::Exception::ERR_INTERNAL_ERROR, "Error while trying to manage a new AppState\n" + Ogre::String(e.what()), "AppStateManager.cpp (41)");
	}
}

////////////////////////////////////////////////////////////////////////////////

AppState* AppStateManager::findByName(Ogre::String stateName) {
	std::vector<state_info>::iterator itr;

	for(itr=m_States.begin();itr!=m_States.end();itr++) {
		if(itr->name==stateName)
			return itr->state;
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////////////

void AppStateManager::start(AppState* state) {
	// Open the specified state
	changeAppState(state);

	int timeSinceLastFrame = 1;
	int startTime = 0;

	// Starts the main game loop
	while(!m_bShutdown) {
		// We need to close if the window is closed.
		if(Framework::getSingletonPtr()->m_pRenderWnd->isClosed()) {
			m_bShutdown = true;
		}

		Ogre::WindowEventUtilities::messagePump();

		// We only run the main game loop if the window is active
		if(Framework::getSingletonPtr()->m_pRenderWnd->isActive()) {
			// Sets the start time of the frame
			startTime = Framework::getSingletonPtr()->m_pTimer->getMillisecondsCPU();

			// Captures input
			Framework::getSingletonPtr()->m_pKeyboard->capture();
			Framework::getSingletonPtr()->m_pMouse->capture();

			// Updates the state on the top of the stack
			m_ActiveStateStack.back()->update(timeSinceLastFrame);

			// Updates OGRE and the graphics
			Framework::getSingletonPtr()->updateOgre(timeSinceLastFrame);
			Framework::getSingletonPtr()->m_pRoot->renderOneFrame();

			// Sets the time since the last frame.
			timeSinceLastFrame = Framework::getSingletonPtr()->m_pTimer->getMillisecondsCPU() - startTime;
		} else {
			// If the window isn't active we sleep for a second
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            Sleep(1000);
#else
            sleep(1);
#endif
		}
	}

	Framework::getSingletonPtr()->m_pLog->logMessage("Main loop quit");
}

////////////////////////////////////////////////////////////////////////////////

void AppStateManager::changeAppState(AppState* state) {
	if (state) {
		if(!m_ActiveStateStack.empty()) {
			m_ActiveStateStack.back()->exit();
			m_ActiveStateStack.pop_back();
		}

		m_ActiveStateStack.push_back(state);
		init(state);
		m_ActiveStateStack.back()->enter();
	}
}

////////////////////////////////////////////////////////////////////////////////

bool AppStateManager::pushAppState(AppState* state) {
	if (state) {
		if(!m_ActiveStateStack.empty()) {
			if(!m_ActiveStateStack.back()->pause())
				return false;
		}

		m_ActiveStateStack.push_back(state);
		init(state);
		m_ActiveStateStack.back()->enter();

		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////

void AppStateManager::popAppState() {
	if(!m_ActiveStateStack.empty()) {
		m_ActiveStateStack.back()->exit();
		m_ActiveStateStack.pop_back();
	}

	if(!m_ActiveStateStack.empty()) {
		init(m_ActiveStateStack.back());
		m_ActiveStateStack.back()->resume();
	} else {
		shutdown();
	}
}

////////////////////////////////////////////////////////////////////////////////

void AppStateManager::popAllAndPushAppState(AppState* state) {
	if (state) {
		while(!m_ActiveStateStack.empty()) {
			m_ActiveStateStack.back()->exit();
			m_ActiveStateStack.pop_back();
		}

		pushAppState(state);
	}
}

////////////////////////////////////////////////////////////////////////////////

void AppStateManager::shutdown() {
	Framework::getSingletonPtr()->m_pLog->logMessage("Shutdown");
	m_bShutdown = true;
}

////////////////////////////////////////////////////////////////////////////////

bool AppStateManager::keyPressed(const OIS::KeyEvent &keyEventRef) {
	if (!m_pFramework->keyPressed(keyEventRef)) {
		if (!m_ActiveStateStack.empty()) return m_ActiveStateStack.back()->keyPressed(keyEventRef);
		return false;
	}
	return true;
}

bool AppStateManager::keyReleased(const OIS::KeyEvent &keyEventRef) {
	if (!m_pFramework->keyReleased(keyEventRef)) {
		if (!m_ActiveStateStack.empty()) return m_ActiveStateStack.back()->keyReleased(keyEventRef);
		return false;
	}
	return true;
}

bool AppStateManager::mouseMoved(const OIS::MouseEvent &evt) {
	if (!m_pFramework->mouseMoved(evt)) {
		if (!m_ActiveStateStack.empty()) return m_ActiveStateStack.back()->mouseMoved(evt);
		return false;
	}
	return true;
}

bool AppStateManager::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
	if (!m_pFramework->mousePressed(evt,id)) {
		if (!m_ActiveStateStack.empty()) return m_ActiveStateStack.back()->mousePressed(evt, id);
		return false;
	}
	return true;
}

bool AppStateManager::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
	if (!m_pFramework->mouseReleased(evt, id)) {
		if (!m_ActiveStateStack.empty()) return m_ActiveStateStack.back()->mouseReleased(evt, id);
		return false;
	}
	return true;
}

inline Ogre::Vector2 AppStateManager::getPosition() {
	return m_pFramework->m_pMenuMgr->getPosition();
}
////////////////////////////////////////////////////////////////////////////////

void AppStateManager::init(AppState* state) {
    Framework::getSingletonPtr()->m_pTrayMgr->setListener(state);

	Framework::getSingletonPtr()->m_pRenderWnd->resetStatistics();
}

#include "OxenApp.h"

#include "MainMenu.h"
#include "GameState.h"

////////////////////////////////////////////////////////////////////////////////

OxenApp::OxenApp() {
	m_pAppStateManager = 0;
}

////////////////////////////////////////////////////////////////////////////////

OxenApp::~OxenApp() {
	delete m_pAppStateManager;
	// If the applictation closes we need to close ogre correctly
	delete Framework::getSingletonPtr();
}

////////////////////////////////////////////////////////////////////////////////

void OxenApp::startApp() {
	new Framework();
	if (!Framework::getSingletonPtr()->initOgre("Oxen", 0, 0)) {
		return;
	}
	
	Framework::getSingletonPtr()->m_pLog->logMessage("Oxen initialized");

	m_pAppStateManager = new AppStateManager();
    Framework::getSingletonPtr()->m_pKeyboard->setEventCallback(m_pAppStateManager);
	Framework::getSingletonPtr()->m_pMouse->setEventCallback(m_pAppStateManager);

	// TODO: reference application states using a enum or even not using this method at all
	MainMenu::create(m_pAppStateManager, "MainMenu");
	GameState::create(m_pAppStateManager, "GameState");

	m_pAppStateManager->start(m_pAppStateManager->findByName("MainMenu"));
}

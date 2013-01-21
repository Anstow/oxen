#include "OxenApp.h"

#include "MainMenu.h"

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

	// TODO: reference application states using a enum
	MainMenu::create(m_pAppStateManager, "MainMenu");

	m_pAppStateManager->start(m_pAppStateManager->findByName("MainMenu"));
}

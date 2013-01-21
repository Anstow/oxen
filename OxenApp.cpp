#include "OxenApp.h"

#include "MainMenu.h"

////////////////////////////////////////////////////////////////////////////////

OxenApp::OxenApp() {
	m_pAppStateManager = 0;
}

////////////////////////////////////////////////////////////////////////////////

OxenApp::~DemoApp() {
	delete m_pAppStateManager;
	// If the applictation closes we need to close ogre correctly
	delete OgreFramework::getSnigletonPtr();
}

////////////////////////////////////////////////////////////////////////////////

void OxenApp::startApp() {
	new OgreFramework();
	if (!OgreFramework::getSnigletonPtr()->initOgre("Oxen", 0, 0)) {
		return;
	}
	
	OgreFramework::getSnigletonPtr()->m_pLog->logMessage("Oxen initialized");

	m_pAppStateManager = new AppStateManager();

	// TODO: reference application states using a enum
	MainMenu::create(m_pAppStateManager, "MainMenu");

	m_pAppStateManager->start(m_pAppStateManager->findByName("MainMenu"));
}

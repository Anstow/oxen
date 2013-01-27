#include "Framework.h"

using namespace Ogre;

////////////////////////////////////////////////////////////////////////////////

template<> Framework* Ogre::Singleton<Framework>::msSingleton = 0;

////////////////////////////////////////////////////////////////////////////////

Framework::Framework() {
	m_pRoot = 0;
	m_pRenderWnd = 0;
	m_pViewport= 0;
	m_pLog= 0;
	m_pTimer= 0;
 
	m_pInputMgr= 0;
	m_pKeyboard= 0;
	m_pMouse= 0;
	m_pTrayMgr= 0;

	m_pMenuMgr = 0;
}

Framework::~Framework() {
	m_pLog->logMessage("Shutdown OGRE...");
	if (m_pTrayMgr) delete m_pTrayMgr;
	if (m_pInputMgr) OIS::InputManager::destroyInputSystem(m_pInputMgr);
	if (m_pRoot) delete m_pRoot;
	if (m_pMenuMgr) delete m_pMenuMgr;
}

bool Framework::initOgre(Ogre::String wndTitle, OIS::KeyListener *pKeyListener, OIS::MouseListener *pMouseListener) {
	// Set up the log manager
    LogManager* logMgr = new Ogre::LogManager();
 
    m_pLog = LogManager::getSingleton().createLog("OgreLogfile.log", true, true, false);
    m_pLog->setDebugOutputEnabled(true);
 
	// Create the root
    m_pRoot = new Ogre::Root();
 
	// TODO: replace the config dialog on start up by some default settings and in game menu
	// show the config dialog
    if(!m_pRoot->restoreConfig() && !m_pRoot->showConfigDialog()) {
        return false;
	}
	// create the render window
    m_pRenderWnd = m_pRoot->initialise(true, wndTitle);
 
	// create the Viewport
    m_pViewport = m_pRenderWnd->addViewport(0);
    m_pViewport->setBackgroundColour(ColourValue(0.5f, 0.5f, 0.5f, 1.0f));
 
	// set no camera
    m_pViewport->setCamera(0);
 
	// Set up OIS (the input system)
    size_t hWnd = 0;
    OIS::ParamList paramList;
    m_pRenderWnd->getCustomAttribute("WINDOW", &hWnd);
 
    paramList.insert(OIS::ParamList::value_type("WINDOW", Ogre::StringConverter::toString(hWnd)));
 
    m_pInputMgr = OIS::InputManager::createInputSystem(paramList);
 
    m_pKeyboard = static_cast<OIS::Keyboard*>(m_pInputMgr->createInputObject(OIS::OISKeyboard, true));
    m_pMouse = static_cast<OIS::Mouse*>(m_pInputMgr->createInputObject(OIS::OISMouse, true));
 
    m_pMouse->getMouseState().height = m_pRenderWnd->getHeight();
    m_pMouse->getMouseState().width  = m_pRenderWnd->getWidth();
 
    if(pKeyListener == 0)
        m_pKeyboard->setEventCallback(this);
    else
        m_pKeyboard->setEventCallback(pKeyListener);
 
    if(pMouseListener == 0)
        m_pMouse->setEventCallback(this);
    else
        m_pMouse->setEventCallback(pMouseListener);
 
	// TODO: Make own resource loading functions to load all the resource locations from one file
	// Load the resources
    Ogre::String secName, typeName, archName;
    Ogre::ConfigFile cf;
    cf.load("resources.cfg");
 
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
        }
    }
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
 
	// TODO: Remove this in final version of any game
	// Set up the information tray
    m_pTrayMgr = new OgreBites::SdkTrayManager("AOFTrayMgr", m_pRenderWnd, m_pMouse, 0);
	m_pTrayMgr->hideCursor();

	// Set up the menu manager
	m_pMenuMgr = new MenuManager(*m_pRenderWnd);
 
	// Create and start our timer for timing between frames 
    m_pTimer = new Ogre::Timer();
    m_pTimer->reset();
	
	// Put the window in the foreground?
    m_pRenderWnd->setActive(true);
 
    return true;
}

////////////////////////////////////////////////////////////////////////////////

bool Framework::keyPressed(const OIS::KeyEvent &keyEventRef) {
    if(m_pKeyboard->isKeyDown(OIS::KC_SYSRQ)) {
        m_pRenderWnd->writeContentsToTimestampedFile("AOF_Screenshot_", ".jpg");
        return true;
    }

    if(m_pKeyboard->isKeyDown(OIS::KC_O)) {
        if(m_pTrayMgr->isLogoVisible()) {
            m_pTrayMgr->hideFrameStats();
            m_pTrayMgr->hideLogo();
        }
        else {
            m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
            m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
        }
    }

	m_pMenuMgr->InjectOISkeyDown(keyEventRef);

    return true;
}

////////////////////////////////////////////////////////////////////////////////

bool Framework::keyReleased(const OIS::KeyEvent &keyEventRef) {
	m_pMenuMgr->InjectOISkeyUp(keyEventRef);

    return true;
}

////////////////////////////////////////////////////////////////////////////////

bool Framework::mouseMoved(const OIS::MouseEvent &evt) {
	m_pMenuMgr->InjectOISMouseMove(evt);

    return true;
}

////////////////////////////////////////////////////////////////////////////////

bool Framework::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
	m_pMenuMgr->InjectOISMouseButtonDown(id);

    return true;
}

////////////////////////////////////////////////////////////////////////////////

bool Framework::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id) {
	m_pMenuMgr->InjectOISMouseButtonUp(id);

    return true;
}

////////////////////////////////////////////////////////////////////////////////

void Framework::updateOgre(double timeSinceLastFrame) {
	CEGUI::System::getSingleton().injectTimePulse(timeSinceLastFrame);
}

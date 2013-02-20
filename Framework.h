#pragma once

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreOverlay.h>
#include <OgreOverlayElement.h>
#include <OgreOverlayManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
 
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
 
#include <SdkTrays.h>
#include "MenuManager.h"

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief This initialized ogre and catches the input for the game
 */
class Framework : public
				  Ogre::Singleton<Framework>
{
public:
	/**
	 * @brief This is the normal constructor for the class
	 */
	Framework();
	/**
	 * @brief This is the destructor for the class it removes the Key and Mouse Listener pointers
	 */
	~Framework();

	/**
	 * @brief This initializes ogre
	 *
	 * @param wndTitle The title of the window
	 * @param pKeyListener The key listener to use
	 * @param pMouseListener The mouse listener to use
	 *
	 * @return True if the initialization of ogre is a success
	 */
	bool initOgre(Ogre::String wndTitle, OIS::KeyListener *pKeyListener = 0, OIS::MouseListener *pMouseListener = 0);
	/**
	 * @brief This is called once per update loop to update ogre, but we don't
	 * currently have anything to update globally and so this doesn't do 
	 * anything.
	 *
	 * @param timeSinceLastFrame the time since the previous update loop
	 */
	void updateOgre(double timeSinceLastFrame);

	/**
	 * @brief This is called when a key is pressed
	 *
	 * @param keyEventRef The key that was pressed
	 *
	 * @return True if input should carry on being processed
	 */
	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	/**
	 * @brief This is called when a key is released
	 *
	 * @param keyEventRef The key that was released
	 *
	 * @return True if input should carry on being processed
	 */
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

	/**
	 * @brief This is called when the mouse is moved
	 *
	 * @param evt The mouse data
	 *
	 * @return True if input should carry on being processed
	 */
	bool mouseMoved(const OIS::MouseEvent &evt);
	/**
	 * @brief This is called when a mouse button is pressed
	 *
	 * @param evt The mouse data
	 * @param id The button that was pressed
	 *
	 * @return True if input should carry on being processed
	 */
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	/**
	 * @brief This is called when a mouse button is released
	 *
	 * @param evt The mouse data
	 * @param id The button that was released
	 *
	 * @return True if input should carry on being processed
	 */
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

	Ogre::Root* m_pRoot;
	Ogre::RenderWindow* m_pRenderWnd;
	Ogre::Viewport* m_pViewport;
	Ogre::Log* m_pLog;
	Ogre::Timer* m_pTimer;

	OIS::InputManager* m_pInputMgr;
	OIS::Keyboard* m_pKeyboard;
	OIS::Mouse* m_pMouse;

	OgreBites::SdkTrayManager* m_pTrayMgr;
	MenuManager* m_pMenuMgr;

private:
	Framework(const Framework&);
	Framework& operator= (const Framework&);
};

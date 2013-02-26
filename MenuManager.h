#pragma once

#include <OgreRenderWindow.h>

// TODO: we probably don't need the entire library so only attach the bits we need
#include "CEGUI.h" 
#include "RendererModules/Ogre/CEGUIOgreRenderer.h"

#include <OISEvents.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <OgreVector2.h>

/**
 * @brief This deals with everything to do with the menu (including mouse cursor)
 */
class MenuManager
{
public:
	/**
	 * @brief Sets up CEGUI, using the window
	 *
	 * @param pWnd The window to render to
	 *
	 * @return The success of setting up CEGUI
	 */
	MenuManager(Ogre::RenderTarget &pWnd);
	/**
	 * @brief Deletes the resources taken by the MenuManager
	 */
	~MenuManager();
	/**
	 * @brief This pushes a Menu onto the stack
	 *
	 * @param pMenu The menu to add to the stack
	 */
	void pushMenu(CEGUI::Window* pMenu);
	/**
	 * @brief This removes the menu from the top of the stack
	 */
	void popMenu(CEGUI::Window* pMenu);

	/**
	 * @brief Injects a key down event
	 *
	 * @param inKey The key data
	 *
	 * @return true
	 */
	bool InjectOISkeyDown(const OIS::KeyEvent &inKey);
	/**
	 * @brief Injects a key up event
	 *
	 * @param inKey The key data
	 *
	 * @return true
	 */
	bool InjectOISkeyUp(const OIS::KeyEvent &inKey);
	/**
	 * @brief Injects and translates a mouse button down event
	 *
	 * @param arg The key data
	 * @param inButton The button ID
	 *
	 * @return Whether the mouse is over the gui
	 */
	bool InjectOISMouseButtonDown(const OIS::MouseEvent &arg, const OIS::MouseButtonID &inButton);
	/**
	 * @brief Injects and translates a mouse botton up event
	 *
	 * @param arg The key data
	 * @param inButton The botton ID
	 *
	 * @return Whether the mouse is over the gui
	 */
	bool InjectOISMouseButtonUp(const OIS::MouseEvent &arg, const OIS::MouseButtonID &inButton);
	/**
	 * @brief Injects the mouse cursor move event including scroll wheel
	 *
	 * @param arg The key data
	 *
	 * @return Whether the mouse is over the gui
	 */
	bool InjectOISMouseMove(const OIS::MouseEvent &arg);
	/**
	 * @brief This injects the mouse cursor position
	 *
	 * @param xPos The x position
	 * @param yPos The y position
	 *
	 * @return true
	 */
	bool InjectOISMousePosition(float xPos, float yPos);

	/**
	 * @brief Get the mouse position on the screen
	 *
	 * @return The position of the mouse in pixels
	 */
	Ogre::Vector2 getMousePos();

private:
	CEGUI::OgreRenderer* renderer;
	CEGUI::Window* m_pRootWnd;
};


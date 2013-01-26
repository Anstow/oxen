#pragma once

#include <OgreRenderWindow.h>

// TODO: we probably don't need the entire library so only attach the bits we need
#include "CEGUI.h" 
#include "RendererModules/Ogre/CEGUIOgreRenderer.h"

#include <OISEvents.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

/**
 * @brief This deals with everything to do with the menu (including mouse cursor)
 */
class MenuManager
{
public:
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
	void popMenu();
	/**
	 * @brief This removes all of the menus from the stack
	 */
	void popAllMenus();

protected:
	MenuManager();
	/**
	 * @brief Sets up CEGUI, using the window
	 *
	 * @param pWnd The window to render to
	 *
	 * @return The success of setting up CEGUI
	 */
	bool init(Ogre::RenderTarget &pWnd);

	/**
	 * @brief Injects a key down event
	 *
	 * @param inKey The key data
	 */
	void InjectOISkeyDown(const OIS::KeyEvent &inKey);
	/**
	 * @brief Injects a key up event
	 *
	 * @param inKey The key data
	 */
	void InjectOISkeyUp(const OIS::KeyEvent &inKey);
	/**
	 * @brief Injects and translates a mouse button down event
	 *
	 * @param inButton The button ID
	 */
	void InjectOISMouseButtonDown(const OIS::MouseButtonID &inButton);
	/**
	 * @brief Injects and translates a mouse botton up event
	 *
	 * @param inButton The botton ID
	 */
	void InjectOISMouseButtonUp(const OIS::MouseButtonID &inButton);
	/**
	 * @brief Injects the mouse button move event including scroll wheel
	 *
	 * @param arg The mouse movement
	 */
	void InjectOISMouseMove(const OIS::MouseEvent &arg);

private:
	CEGUI::OgreRenderer* renderer;
	CEGUI::Window* m_pRootWnd;
	std::vector<CEGUI::Window*> m_Menus;
};


#pragma once

#include "AppState.h"
#include <CEGUIEventArgs.h>

////////////////////////////////////////////////////////////////////////////////

class MainMenu : public AppState
{
public:
	/**
	 * @brief Creates the main menu state
	 */
	MainMenu();

	DECLARE_APPSTATE_CLASS(MainMenu)

	/**
	 * @brief This deals with entering the main menu, setting up the camera and
	 * resetting the game stats
	 */
	void enter();
	/**
	 * @brief Fills the scene with content
	 */
	void createScene();
	/**
	 * @brief Destroys the camera and the SceneManager and the GUI elements
	 */
	void exit();

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

	void update(double timeSinceLastFrame);

private:
	////////////////////////////////////////////////////////////////////////////
	// Button event functions
	////////////////////////////////////////////////////////////////////////////
	/**
	 * @brief This handle the clicking of the exit button.
	 *
	 * @param e The data from the event.
	 */
	bool onExit(const CEGUI::EventArgs& e);

	bool m_bQuit;
};

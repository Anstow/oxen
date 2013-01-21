#pragma once

#include "AppState.h"

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
	 * @brief This deals with entering the main menu
	 */
	void enter();
	void createScene();
	void exit();

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

	void buttonHit(OgreBites::Button* button);

	void update(double timeSinceLastFrame);

private:
	bool m_bQuit;
};

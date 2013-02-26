#pragma once

#include <CEGUIEventArgs.h>
#include <CEGUIWindow.h>

#include "GameSettings.h"
#include "AppState.h"
#include "Engine/Engine.h"
#include "Engine/RenderEntity.h"

////////////////////////////////////////////////////////////////////////////////

class GameState : public AppState
{
public:
	/**
	 * @brief Creates the main menu state
	 */
	GameState();
	~GameState();

	DECLARE_APPSTATE_CLASS(GameState)

	/**
	 * @brief This deals with entering the game, setting up the camera and
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
	bool moveCamera();

	bool m_bQuit;
	CEGUI::Window* m_pHud;
	GameSettings* m_pSettings;
	
	Engine* m_pGameEngine;

	RenderEntity* testEnt;
	RenderEntity* testEnt2;
};

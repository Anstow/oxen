#pragma once

#include "AppState.h"

/**
 * @brief Displays the game state and gathers input
 */
class GameState : public AppState
{
public:
	GameState();

	void enter();
	void exit();
	void pause();
	void resume();

	void update(double timeSinceLastFrame);
}

#pragma once

#include "Framework.h"
#include "AppStateManager.h"

/**
 * @brief This is a central class which runs the game and menus
 */
class OxenApp
{
public:
	/**
	 * @brief The constructor OxenApp
	 */
	OxenApp();
	/*
	 * @brief The destructor for OxenApp
	 */
	~OxenApp();

	/**
	 * @brief Starts the app
	 */
	void startApp();

private:
	/**
	 * @brief This stores the state of the applictation
	 */
	AppStateManager* m_pAppStateManager;
};

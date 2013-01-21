#pragma once

#include "AppState.h"

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief This is the class that manages the game states. It contains the main game loop.
 */
class AppStateManager : public AppStateListener
{
public:
	/**
	 * @brief This stores a loaded game state
	 */
	typedef struct
	{
		Ogre::String name;
		AppState* state;
	} state_info;

	/**
	 * @brief Creates a new AppStateManager
	 */
	AppStateManager();
	/**
	 * @brief Destorys our old AppStateManager
	 */
	~AppStateManager();

	/**
	 * @brief This adds a new preloaded applictation state
	 *
	 * @param stateName The name of the preloaded state
	 * @param state The state that has been preloaded
	 */
	void manageAppState(Ogre::String stateName, AppState* state);

	/**
	 * @brief This finds a preloaded state from its name
	 *
	 * @param stateName The name of the preloaded state
	 *
	 * @return The state found
	 */
	AppState* findByName(Ogre::String stateName);

	/** @brief This is the main loop of the game. It does all the updating and rendering.
	 *
	 * @param state The startup state.
	 */
	void start(AppState* state);
	/**
	 * @brief Exits the current state and starts a new one.
	 *
	 * @param state The state to start.
	 */
	void changeAppState(AppState* state);
	/**
	 * @brief Add a new state to the stack. And starts it.
	 *
	 * @param state Th state to add.
	 *
	 * @return The success of adding the state.
	 */
	bool pushAppState(AppState* state);
	/**
	 * @brief Removes the last state and starts the one bellow, (if this doesn't exist it exits).
	 */
	void popAppState();
	/**
	 * @brief Exits all the states on the stack and enters the new state
	 *
	 * @param state
	 */
    void popAllAndPushAppState(AppState* state);
	/**
	 * @brief You'll never guess what this does...
	 */
	void shutdown();

protected:
	/**
	 * @brief Initializes a new state, with input etc... And resets the debug window statistics.
	 *
	 * @param state
	 */
	void init(AppState *state);

	std::vector<AppState*> m_ActiveStateStack;
	std::vector<state_info> m_States;
	bool m_bShutdown;
};

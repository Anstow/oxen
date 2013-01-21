#pragma once

#include "Framework.h"

class AppState;

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief This will be inherited by the applictation state manager, but in
 * used in App State and so must be defined here
 */
class AppStateListener
{
public:
	/**
	 * @brief constructs the AppStateListener
	 */
	AppStateListener(){};
	/**
	 * @brief destructor for the AppStateListener
	 */
	virtual ~AppStateListener(){};

	/**
	 * @brief Function to add new states to the manager
	 *
	 * @param stateName The name of the state to add. TODO: replace this with an enum
	 * @param state The state to add.
	 */
	virtual void manageAppState(Ogre::String stateName, AppState* state) = 0;

	/**
	 * @brief Function to find a state from its name.
	 *
	 * @param stateName The name of the state TODO: replace this with an enum
	 *
	 * @return The state.
	 */
	virtual AppState* findByName(Ogre::String stateName) = 0;
	/**
	 * @brief Exits the current state and opens the new one
	 *
	 * @param state The state to change to.
	 */
	virtual void changeAppState(AppState *state) = 0;
	/**
	 * @brief Puts a new state on the active stack and swaps to it.
	 *
	 * @param state The state to add.
	 *
	 * @return The success of swapping.
	 */
	virtual bool pushAppState(AppState* state) = 0;
	/**
	 * @brief Removes the last state from the stack and resumes the last state
	 */
	virtual void popAppState() = 0;
	/**
	 * @brief Shutsdown the applictation
	 */
	virtual void shutdown() = 0;
	/**
	 * @brief Removes all the states from the stack and loads a new one
	 *
	 * @param state The state to load.
	 */
    virtual void popAllAndPushAppState(AppState* state) = 0;
};

////////////////////////////////////////////////////////////////////////////////

/**
 * @brief This is a template for the applictation states (currently only menu)
 */
class AppState : public OIS::KeyListener, public OIS::MouseListener, public OgreBites::SdkTrayListener
{
public:
	/**
	 * @brief Move to the state indicated by the name.
	 *
	 * @param parent This is the AppStateListener to put the state in.
	 * @param name This is the name of the state to add.
	 */
	static void create(AppStateListener* parent, const Ogre::String name){};

	/**
	 * @brief This destroy the state
	 */
	void destroy(){delete this;}

	/**
	 * @brief This deals with entering the state 
	 */
	virtual void enter() = 0;
	/**
	 * @brief This is called to exit the state
	 */
	virtual void exit() = 0;
	/**
	 * @brief This pauses the state
	 *
	 * @return The success of pausing
	 */
	virtual bool pause(){return true;}
	/**
	 * @brief This resumes a paused state
	 */
	virtual void resume(){};
	/**
	 * @brief This is the update function for the state
	 *
	 * @param timeSinceLastFrame The time before the last refresh
	 */
	virtual void update(double timeSinceLastFrame) = 0;

protected:
	/**
	 * @brief Constructor for the state
	 */
	AppState(){};

	/**
	 * @brief Finds the state by its name TODO: replace with enum
	 *
	 * @param stateName The name of the state to find
	 *
	 * @return The state found.
	 */
	AppState* findByName(Ogre::String stateName){return m_pParent->findByName(stateName);}
	/**
	 * @brief Handle to the parents changeAppState
	 *
	 * @param state The state to change to
	 * @see AppStateListener::changeAppState()
	 */
	void changeAppState(AppState* state){m_pParent->changeAppState(state);}
	/**
	 * @brief Handle to the parents pushAppState
	 *
	 * @param state The state to push
	 *
	 * @return the success of pushing the state
	 * @see AppStateListener::pushAppState()
	 */
	bool pushAppState(AppState* state){return m_pParent->pushAppState(state);}
	/**
	 * @brief Pops the last state (probably this one)
	 * @see AppStateListener::popAppState()
	 */
	void popAppState(){m_pParent->popAppState();}
	/**
	 * @brief Shuts down the game
	 */
	void shutdown(){m_pParent->shutdown();}
	/**
	 * @brief Handle tho the parents popAllAndPushAppState
	 *
	 * @param state The state to add.
	 * @see AppStateListener::popAllAndPushAppState()
	 */
    void popAllAndPushAppState(AppState* state){m_pParent->popAllAndPushAppState(state);}

	AppStateListener* m_pParent;

	Ogre::Camera* m_pCamera;
	Ogre::SceneManager* m_pSceneMgr;
    Ogre::FrameEvent m_FrameEvent;
};

////////////////////////////////////////////////////////////////////////////////

#define DECLARE_APPSTATE_CLASS(T)										\
static void create(AppStateListener* parent, const Ogre::String name)	\
{																		\
	T* myAppState = new T();											\
	myAppState->m_pParent = parent;										\
	parent->manageAppState(name, myAppState);							\
}

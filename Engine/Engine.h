#pragma once

#include <vector>

/**
 * @brief This updates one frame: acts on input, runs AI, update player positions, etc...
 */
class Engine
{
public:
	Engine();
	~Engine();

	/**
	 * @brief This is the main update loop it runs one frame.
	 */
	void update(double timeSinceLastFrame);
	/**
	 * @brief This pushes the input to the network
	 *
	 * @param inputs The inputs to push
	 */
	//void pushInput(std::vector<Input> &inputs);
	
	//void loadEntity(char* str);

private:
	/**
	 * @brief The input to the game itself is read in.
	 */
	void injectInput();
	/**
	 * @brief This runs the AI for each of the entities and perhaps in the
	 * future the oponents.
	 */
	void runAI();
	/**
	 * @brief This updates the actuall game.
	 */
	void updateEntities();
	/**
	 * @brief This notifies the player of events within the game.
	 */
	void notify();
};

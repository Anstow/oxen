#pragma once

#define INPUT_TYPE_MOVEMENT 0
#define INPUT_TYPE_TARGETING 1

// The problem with this is it has no way of sending pause messages
// or doing anything other than moving or targeting with networkedEntities

/** @brief This struct for moving the data across a network
 */
struct NetworkedInput
{
	/**
	 * @brief The item in the list of networked entities
	 */
	int networkedEntity;
	/**
	 * @brief The type of the input
	 */
	int type;

	/**
	 * @brief The x position of the input
	 */
	float x;
	/**
	 * @brief The y position of the input
	 */
	float y;
	/**
	 * @brief The z position of the input
	 */
	float z;
};

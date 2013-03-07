#pragma once

class GameSettings
{
public:
	GameSettings();
	
	/**
	 * @brief Loads the setting from the file specified
	 *
	 * @param settingLocation The file to load the settings from
	 *
	 * @return Sucess of loading the settings
	 */
	bool loadSettings(char* settingLocation);

	//////////////////////////////////////////////////////////////////////////
	// The settings for the game along with the default values 
	//////////////////////////////////////////////////////////////////////////
	
	/**
	 * @brief How close to the edge of the screen in pixcel to start scrolling
	 */
	int m_fScrollBorderSensitivity;
	/**
	 * @brief How quick to scroll
	 */
	float m_fScrollSpeed;
	/**
	 * @brief How quick to side scroll
	 */
	float m_fSideScrollSpeed;
};

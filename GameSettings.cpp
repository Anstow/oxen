#include "GameSettings.h"

GameSettings::GameSettings()
	: m_fScrollBorderSensitivity(5.0f)
	, m_fSideScrollSpeed(0.5f)
	, m_fScrollSpeed(0.05f)
{
}

bool GameSettings::loadSettings(char* settingLocation) {
	// TODO: Implement
	return true;
}

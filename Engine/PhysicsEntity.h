#pragma once

#include <OgreVector3.h>
#include <OgreMatrix3.h>
#include <OgrePrerequisites.h>

/**
 * @brief This is the base entity class, it contains the update functions
 */
class Entity
{
public:
	Entity();

	virtual void update(double timeSinceLastFrame);
	virtual void updatePositions(double timeSinceLastFrame);
	virtual void destroy();

private:
	/**
	 * @brief The position of the entity
	 */
	Ogre::Vector3 m_positionR;
	/**
	 * @brief The velocity of the entity
	 */
	Ogre::Vector3 m_positionV;
	/**
	 * @brief The acceleration of the entity
	 */
	Ogre::Vector3 m_positionA;
	
	/**
	 * @brief The mass of the object
	 */
	Ogre::Real m_mass;
	
	/**
	 * @brief The facing of the entity
	 */
	Ogre::Vector3 m_angluarR;
	/**
	 * @brief The change in angular velocity of the entity
	 */
	Ogre::Vector3 m_angluarV;
	/**
	 * @brief The angular acceleration of the entity
	 */
	Ogre::Vector3 m_angluarA;

	/**
	 * @brief The moment of intertia for the object 
	 */
	Ogre::Matrix3 m_intertiaTensor;
};

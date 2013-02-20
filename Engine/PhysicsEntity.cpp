#include "PhysicsEntity.h"

void Entity::update(double timeSinceLastFrame) {
}

void Entity::updatePositions(double timeSinceLastFrame) {
	// Update position and velocity
	m_positionR += timeSinceLastFrame * (m_positionV + 0.5f * timeSinceLastFrame * m_positionA);
	m_positionV += timeSinceLastFrame * m_positionA;

	// Update facing and angular velocity
	// TODO: Do the above
}

void Entity::destroy() {
}

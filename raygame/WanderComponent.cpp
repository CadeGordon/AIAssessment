#include "WanderComponent.h"
#include "Transform2D.h"
#include "Actor.h"
#include "Agent.h"
#include "MoveComponent.h"
#include <time.h>

WanderComponent::WanderComponent(float circleDistance, float circleRadius, float wanderForce) : SteeringComponent(nullptr, wanderForce)
{
	m_circleDistance = circleDistance;
	m_circleRadius = circleRadius;
	srand(time(NULL));
}

MathLibrary::Vector2 WanderComponent::calculateForce()
{
	if (getSteeringForce() == 0)
		return { 0,0 };

	//Find the agents position 
	MathLibrary::Vector2 ownerPosition = getOwner()->getTransform()->getWorldPosition();
	MathLibrary::Vector2 Direction = getAgent()->getMoveComponent()->getVelocity().getNormalized();

	//Sets the circle to be infront of the enemy
	m_circlePos = ownerPosition + (Direction * m_circleDistance);

	//Gets a random number in the circle to be able to wander
	float randNum = (rand() % 201);
	MathLibrary::Vector2 randDirection = MathLibrary::Vector2{ (float)cos(randNum), (float)sin(randNum) } * m_circleRadius;

	//Adds the random direction to the circle position
	m_target = randDirection + m_circlePos;

	//Seek to the random point
	MathLibrary::Vector2 desiredVelocity = MathLibrary::Vector2::normalize(m_target - ownerPosition) * getSteeringForce();
	MathLibrary::Vector2 force = desiredVelocity - getAgent()->getMoveComponent()->getVelocity();

	return force;
}

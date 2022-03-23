#pragma once
#include "Component.h"

enum State
{
	IDLE,
	WANDER,
	SEEK,
	PATHFIND
};

class SeekComponent;
class WanderComponent;
class PathFindComponent;

class StateMachineComponent :
	public Component
{
public:
	void start() override;

	State getCurrentState() { return m_currentState; }
	void setCurrentState(State state) { m_currentState = state; }

	void update(float deltaTime) override;

private:
	State m_currentState;
	SeekComponent* m_seekComponent;
	WanderComponent* m_wanderComponent;
	PathFindComponent* m_pathFindComponent;
	float m_seekForce;
	float m_wanderForce;
	float m_seekRange = 300;
	float m_pathFindRange = 50;
};


#include "PathfindEnemy.h"
#include "MazeScene.h"
#include "Wall.h"
#include "raylib.h"
#include "Transform2D.h"
#include "PathfindComponent.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "SeekComponent.h"
#include "WanderComponent.h"
#include "AABBCollider.h"
#include "StateMachineComponent.h"

PathfindEnemy::PathfindEnemy(float x, float y, float maxSpeed, float maxForce, int color, Maze* maze)
	: Agent(x, y, "Ghost", maxSpeed, maxForce)
{
	m_maze = maze;
	getTransform()->setScale({ Maze::TILE_SIZE,Maze::TILE_SIZE });

	m_pathfindComponent = new PathfindComponent(maze);
	m_pathfindComponent->setColor(color);
	addComponent(m_pathfindComponent);
	addComponent(new SpriteComponent("Images/enemy.png"));
	setCollider(new AABBCollider(this));
}

PathfindEnemy::~PathfindEnemy()
{
	delete m_pathfindComponent;
}

void PathfindEnemy::update(float deltaTime)
{
	Agent::update(deltaTime);
}

void PathfindEnemy::draw()
{
	Agent::draw();
}

void PathfindEnemy::onCollision(Actor* other)
{
	if (Wall* wall = dynamic_cast<Wall*>(other)) {
		MathLibrary::Vector2 halfTile = { Maze::TILE_SIZE / 2.0f, Maze::TILE_SIZE / 2.0f };
		MathLibrary::Vector2 position = getTransform()->getWorldPosition();
		position = position + halfTile;
		MathLibrary::Vector2 tilePosition = {
			roundf(position.x / Maze::TILE_SIZE) * Maze::TILE_SIZE,
			roundf(position.y / Maze::TILE_SIZE) * Maze::TILE_SIZE
		};
		tilePosition = tilePosition - halfTile;
		getTransform()->setWorldPostion(tilePosition);

		getMoveComponent()->setVelocity({ 0, 0 });
	}
}

void PathfindEnemy::setTarget(Actor* target)
{
	m_target = target;
	m_pathfindComponent->setTarget(target);
}

Actor* PathfindEnemy::getTarget()
{
	return m_target;
}
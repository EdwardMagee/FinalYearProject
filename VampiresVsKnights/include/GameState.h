#pragma once

enum class GameState : unsigned int { 
	PlayersTurn, 
	PlayersMoved,
	PlayersMoving, 
	EnemyTurn, 
	EnemyMove };
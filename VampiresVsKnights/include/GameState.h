#pragma once

/*! This enum class is used every uppdate to see who's turn it is and weather a not a character should be moving*/

enum class GameState : unsigned int { 
	PlayersTurn,  //!< The game state is now allowing the player to make a move
	PlayersMoved, //!< Processes the action
	PlayersMoving,  //!< Acts upon said action
	EnemyTurn,  //!< Enemies turn
	EnemyMove };  //!< Enemies move
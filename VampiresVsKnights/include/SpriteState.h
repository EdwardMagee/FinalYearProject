#pragma once

/*! Used to see what the state the enemy is in*/

enum class SpriteState : unsigned int {
	AttackingState,  //!< The sprite is currently attacking
	WaitingState,  //!< the sprite is waiting
	FleeingState,  //!< ITS RUNNING 
	HealState  //!< Its healing
};
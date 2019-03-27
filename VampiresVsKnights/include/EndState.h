#pragma once

/*! Enum class thats states all the possible states are at the end of the game */

enum class EndState : unsigned int {
	Defualt, //!< defualt mostly used for when its not ended
	VampireWin, //!< The vamps won
	PlayerWin, //!< The player wins
	EndMenu //!< End the menu 
};
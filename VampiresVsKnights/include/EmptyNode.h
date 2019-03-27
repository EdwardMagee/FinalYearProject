#pragma once
#include "NodeInterface.h"

class SpriteInterface;

/*! This class is designed to be the wall, a node that should not allow the unit to move too*/

class EmptyNode : public NodeInterface
{
public:

	EmptyNode(int p_cost); //!< Constructor
						   /*!
						   \param p_cost what is the cost of the node
						   */
	~EmptyNode(); //!< Deconstructor
	void updateNode(float p_time) override; //!< update method
											/*!
											\param p_time contains information on the time
											*/
	sf::Sprite* getSprite() override; //!< Gets a sprite
	void constructNode(int p_x, int p_y, sf::Texture p_T) override; //!< Constructs the node
																	/*!
																	\param p_x it is the x posiiton 
																	\param p_y it is the y position
																	\param p_T the texture of the node
																	*/
	

	std::string checkNodeType() override; //!< Method to check what type the node is


private:

	

};
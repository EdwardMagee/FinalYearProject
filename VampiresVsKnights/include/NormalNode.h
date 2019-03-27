#pragma once
#include "NodeInterface.h"

class SpriteInterface;

/*! A node that the user can move too*/

class NormalNode : public NodeInterface
{
public:

    NormalNode(int p_cost); //!< Construct Node
							/*!
							\param p_cost the cost of the current node
							*/
	~NormalNode(); //!< Deconstructor
	void updateNode(float p_time) override; //!< Update method
											/*!
											\param p_time contains information on the time
											*/
    sf::Sprite* getSprite() override; //!< Get sprite of node
	void constructNode(int p_x, int p_y, sf::Texture p_T) override; //!< Construct node

	std::string checkNodeType() override; //!< get node type


private:


};
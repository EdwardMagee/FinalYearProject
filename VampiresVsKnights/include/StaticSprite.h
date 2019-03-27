#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteInterface.h"

class NodeInterface;

/*! This class builds up a character in the game*/

class StaticSprite : public SpriteInterface 
{
private:

	

public:

	StaticSprite(int p_col, int p_row, sf::Texture p_T, float p_speed, float p_health, float p_damage); //!< Constructor
																										/*!
																										\param p_col the column the sprite is on 
																										\param p_row the row the sprite is on
																										\param p_t sprite texture 
																										\param p_health the sprites health
																										\param p_damage the damage the sprite can do
																										*/
	~StaticSprite(); //!< Deconstructor
	void update(float p_time) override; //!< update method
										/*!
										\param p_time contains information on the time
										*/
	void message(const std::string p_message) override; //!< message method
														/*!
														\param p_message its a message to the class
														*/
	sf::Sprite* getSprite() override; //!< gets the sprite 
	void setSpritePos(int p_col, int p_row) override; //!< sets the pos of the sprite
													  /*!
													  \param p_row sets the row its in
													  \param p_col used to set what col its in
													  */
	void setNode(NodeInterface* p_NI) override; //!< set node
												/*!
												\param p_NI this node will become m_node
												*/
	NodeInterface* getNode() override; //!< get node

	void setHealth(float p_damageTaken) override; //!< set health
												  /*!
												  \param p_damage taken subtracted from health
												  */
	bool isDoingDamage() override ; //!< is it doing damage
	void doDamage(bool p_bool) override; //!< Do damage 
										 /*!
										 \param p_bool yes or no is it doing damage
										 */
};
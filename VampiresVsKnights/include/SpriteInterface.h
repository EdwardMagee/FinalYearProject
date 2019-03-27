#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteState.h"

class NodeInterface;

/*! States all the information a character should have*/

class SpriteInterface 
{
public:

	 SpriteState getState() { return m_spriteState; } //!< Gets the sprite state
	 virtual sf::Sprite* getSprite() { return m_sprite; }; //!< Gets the sprite
	 virtual void setNode(NodeInterface* p_NI) { m_node = p_NI; }; //!< Sets a node to each sprite
																   /*!
																   \param p_NI this node will become m_node
																   */
	 virtual NodeInterface* getNode() { return m_node; }; //!< Gets the node within each sprite


	 virtual float getSpeed() { return m_speed; }; //!< Sets characater speed
	 virtual float getAttack() { return m_attack;  }; //!< Get attack
	 virtual float getHealth() { return m_health; }; //!< Get Health

	 virtual bool isDoingDamage() = 0; //!< Is it doing damage 
	 virtual void doDamage(bool p_bool) = 0; //!< Do the damage 
											 /*!
											 \param p_bool used to set the damage 
											 */
	 virtual void setHealth(float p_damageTaken) = 0; //!< Takeaways from its current health
													  /*!
													  \param p_damageTaken this is taken away from the health
													  */
	 virtual void setSpritePos(int p_col, int p_row) = 0; //!< Sets its position
														  /*!
														  \param p_row sets the row its in
														  \param p_col used to set what col its in 
														  */

	 virtual void message(const std::string p_message) = 0;	 //!< Gives the sprite a message
															 /*!
															 \param p_message its a message to the class
															 */
	 virtual void update(float p_time) = 0; //!< Update method
											/*!
											\param p_time contains information on the time
											*/
protected:

	sf::Sprite* m_sprite; //!< The sprite of the sprite
	sf::Texture m_texture; //!< Texture
	NodeInterface* m_node; //!< Pointer to a node
	float m_speed; //!< Speed
	float m_attack; //!< Attack
	float m_health; //!< HEALTH
	bool m_isDoingDamage; //!< Is it doing damage
	
	SpriteState m_spriteState; //!< State of the sprite
	
};
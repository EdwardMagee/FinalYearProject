#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class SpriteInterface;

/*! States what each node must have, if i wanted a new type of Node i could inherit from this and not worry about copying this code*/

class NodeInterface 
{
public:
	virtual sf::Sprite* getSprite() = 0; //!< Gets the sprite of the node so its drawn
	virtual void constructNode(int p_row, int p_col, sf::Texture p_T) = 0; //!< Constructs Node
																		   /*!
																		   \param p_row the row the node is on
																		   \param p_col the column the row is on 
																		   \param p_T the texture of the node
																		   */
	virtual void updateNode(float p_time) = 0; //!< Updates the game
											   /*!
											   \param p_time contains information on the time
											   */
	virtual std::string checkNodeType() = 0; //!< Checks the type of the node

	virtual float getG() { return m_gValue;  }; //!< Get the G value
	virtual float getH() { return m_hValue;  }; //!< Get the H value
	virtual float getF() { return m_fValue;  }; //!< Get the F value
	virtual float getTerrainCost() { return m_movementCost; }; //!< Get Cost
	virtual sf::Vector2i getID() { return m_id; }; //!< Get id 

	virtual void setG(float p_g) { m_gValue = p_g; }; //!< Set G
													  /*!
													  \param p_g information on the G value
													  */
	virtual void setF(float p_f) { m_fValue = p_f; }; //!< Set F
													  /*!
													  \param p_f information on the F value
													  */
	virtual void setH(float p_H) { m_hValue = p_H; };//!< Set H
													 /*!
													 \param p_h information on the H value
													 */
	virtual void setDiagonal(bool p_b) { m_isDiagonal = p_b;  }; //!< Set Diagonal method
																 /*!
																 \param p_b information of the m_isDiaognal
																 */

	virtual NodeInterface* getPerant() { return m_perant;  }; //!< Get the perant of the node
	virtual void setPerant(NodeInterface* p_NI) { m_perant = p_NI;  }; //!< Set the perant
																	   /*!
																	   \param p_NI the node that will be set as the perant
																	   */

	virtual bool isDiagonal() { return m_isDiagonal;  }; //!< Is it Diagonal
	

	

protected:
	
	sf::Sprite* m_sprite; //!< Contains node sprite
	sf::Texture m_texture; //!< Contains texture 
	NodeInterface* m_perant; //!< Stores pointer to the perant

	sf::Vector2i m_id; //!< Stores id
	float m_movementCost; //!< stores movment cost
	float m_fValue; //!< Store F
	float m_gValue; //!< Store G
	float m_hValue; //!< Set H
	bool m_isDiagonal; //!< Stores bool 


};
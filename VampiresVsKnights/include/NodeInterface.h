#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class SpriteInterface;

class NodeInterface 
{
public:
	virtual sf::Sprite* getSprite() = 0;
	virtual void constructNode(int p_row, int p_col, sf::Texture p_T) = 0;
	virtual void updateNode(float p_time) = 0;
	virtual SpriteInterface* getSpriteAttachedToNode() = 0;
	virtual bool containSprite(SpriteInterface* p_sprite) = 0;
	virtual void removeSprite() = 0;
	virtual std::string checkNodeType() = 0;

	virtual float getG() { return m_gValue;  };
	virtual float getH() { return m_hValue;  };
	virtual float getF() { return m_fValue;  };
	virtual float getTerrainCost() { return m_movementCost; };
	virtual sf::Vector2i getID() { return m_id; };

	virtual void setG(float p_g) { m_gValue = p_g; };
	virtual void setF(float p_f) { m_fValue = p_f; };
	virtual void setH(float p_H) { m_hValue = p_H; };
	virtual void setDiagonal(bool p_b) { m_isDiagonal = p_b;  };

	virtual NodeInterface* getPerant() { return m_perant;  };
	virtual void setPerant(NodeInterface* p_NI) { m_perant = p_NI;  };

	virtual bool isDiagonal() { return m_isDiagonal;  };
	

	

protected:
	
	sf::Sprite* m_sprite;
	sf::Texture m_texture;
	SpriteInterface* m_spriteUnit;
	NodeInterface* m_perant;

	sf::Vector2i m_id;
	float m_movementCost;
	float m_fValue;
	float m_gValue;
	float m_hValue;
	bool m_isDiagonal;


};
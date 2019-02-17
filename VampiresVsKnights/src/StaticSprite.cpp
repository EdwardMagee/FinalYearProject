#include "../include/StaticSprite.h"

StaticSprite::StaticSprite(int p_col, int p_row, sf::Texture p_T){

	m_texture = p_T;
	m_sprite = new sf::Sprite;
	m_sprite->setTexture(m_texture);
	m_sprite->setPosition((p_col * 64) + 100, (p_row * 64) + 50);

}

StaticSprite::~StaticSprite(){
	delete m_sprite;
	m_sprite = nullptr;
}

void StaticSprite::update(float p_time)
{

}

void StaticSprite::message(const std::string p_message)
{
}

sf::Sprite* StaticSprite::getSprite(){
	return m_sprite;
}

void StaticSprite::setSpritePos(int p_col, int p_row)
{
	m_sprite->setPosition((p_col * 64) + 100, (p_row * 64) + 50);
}

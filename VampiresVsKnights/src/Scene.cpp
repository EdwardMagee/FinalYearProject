#include "../include/Scene.h"

Scene::Scene()
{
	temp = new sf::Sprite;
	temp->setTexture(m_textureHandler->instance()->getTexture("Owl"));
	m_spriteVector.push_back(temp);
}

Scene::~Scene()
{
}

void Scene::updateScene(float p_time)
{
}


bool Scene::loadLevel(std::string p_level)
{
	return false;
}

std::vector<sf::Sprite*> Scene::getSpriteVector(){
	return m_spriteVector;
}

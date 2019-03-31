#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <list>
#include <math.h>


class NodeInterface;
class TextureHandler;
class SpriteInterface;
class FileReaderNodes;

/*! Class that created the two d array and handles all the pathfinding*/

class Graph {

public:

	Graph(std::string p_Nodes); //!< Constructor
								/*!
								\param p_Nodes contains data on where to put nodes
								*/
	~Graph(); //!< Deconstructor
	std::list<NodeInterface*> aStar(sf::Vector2i p_startPos, sf::Vector2i p_endPos, float p_speed, std::vector<SpriteInterface*> p_vectorSprites); //!< A star alogirthm used to find the shortest path to its goal
																																				   /*!
																																				   \param p_startPos this is the start of the search
																																				   \param p_endPos this is the end of the search
																																				   \param p_speed what is units speed
																																				   \param p_vector of sprites so it knows what nodes to advoid
																																				   */
	std::list<NodeInterface*> gatherChildren(NodeInterface* p_currentNode); //!< Gets the all the nodes around the current one
																			/*!
																			\param p_currentNode gets all the nodes around this one
																			*/

	float calculateHValue(sf::Vector2i p_startPos, sf::Vector2i p_endPos); //!< Calculates the distance between the 
																		   /*!
																		   \param p_startPos start of the calcualtion
																		   \param p_endPos goal of the calaculation 
																		   */
	std::list<NodeInterface*> getPath(NodeInterface* p_start, NodeInterface* p_end); //!< returns the trip the unit takes across the board
																					 /*!
																					 \param p_start the start of the path
																					 \param p_endPos end of the path
																					 */
	sf::Vector2i getGoal(NodeInterface* p_Goal, NodeInterface* p_Start, std::vector<SpriteInterface*> p_vectorSprites); //!< Gets the goal that the unit must take
																														/*!
																														\param p_Goal a node interface pointer 
																														\param p_Start so it knows which node is the starting node
																														\param p_vectorSprites so it knows which sprites to advoid
																														*/
	NodeInterface* getNode(sf::Vector2i p_getNode); //!< Gets a node
													/*!
													\param p_getNode id of the desired node
													*/

	std::pair<int, int> getColRow(); //!< Gets the size of the graph
	bool isGoalReached(); //!< Has the goal been reached
	bool isTargetANeighbour(NodeInterface* p_Target, NodeInterface* p_Start);//!< Saves having to use the A* when a unit is next to another
																			 /*!
																			 \param p_Target so it knows which node you want to attack
																			 \param p_Start so it knows which node is the starting node
																			 */
protected:

	static const int m_iCol = 8; //!< How many Columns in game
	static const int m_iRow = 16; //!< How many Rows in the game

	float tempCost; //!< a temp for the cost 
	std::string tempString; //!< a temp containing a string

	std::array<std::array<NodeInterface*, m_iCol>, m_iRow> m_Graph; //!< 2D Array of Nodes
	TextureHandler * m_textureHandler; //!< Get the textures for the nodes
	FileReaderNodes * m_fileReader; //!< gets the node information 

	std::list<NodeInterface*> m_closedList; //!< Closed list for Algorithm
	std::list<NodeInterface*> m_openList; //!< for a star
	std::list<NodeInterface*> m_pathList; //!< used to store the path the player takes
	std::list<NodeInterface*> m_tempList; //!< Stores a temp list
	NodeInterface* m_storeLastG; //!< Stores the last G this will be used to calculate the last node to go to

	bool m_isInClosedList; //!< Bool to determine if a node is the closed list
	bool m_isInOpenList;  //!< Bool to determine if a node is the open list
	bool m_isOccupied; //!< Is the node Occupied
	bool m_reachedGoal; //!< Did the player reach the goal
	bool m_useCurrent; //!< used to tell if there is a custon node from file if not it will give default 


};
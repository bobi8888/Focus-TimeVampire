#pragma once

//int playerCharge = 10;
//int acceptCharge = 2;
//float distance = 0;

class Wall{
private:
	sf::Vector2f centerPosition;
	bool horiztonal;
	float thickness, length;
	sf::VertexArray vertexArray;
public:
	Wall(float centerX, float centerY, bool isHorizontal, float thick, float len);
	sf::VertexArray getVertexArray();
};
#pragma once

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
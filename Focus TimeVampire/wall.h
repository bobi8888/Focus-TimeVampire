#pragma once

class Wall{
private:
	float length = 0, thickness = 0, hyp = 0;
	float angleDegrees = 0, angleRadians = 0, degreeToRadians = M_PI/180;
	float rX = 0, rY = 0, xPrime = 0, yPrime = 0, scaleFactor = 0;
	float playerXPrime = 0, playerYPrime = 0, playerRadius = 0;
	float wallMinX = 888888, wallMinY = 888888, wallMaxX = -888888, wallMaxY = -888888;
	float relativeWallMinX = 888888, relativeWallMinY = 888888, relativeWallMaxX = -888888, relativeWallMaxY = -888888;
	sf::Vector2f playerRelativeMinCoords, playerRelativeMaxCoords;
	sf::Vector2f center;
	sf::Vector2f zeroPosition, firstPosition, secondPosition, thirdPosition;
	sf::Vector2f relativeZeroPosition, relativeFirstPosition, relativeSecondPosition, relativeThirdPosition;
	sf::VertexArray vertexArray, relativeVertexArray;
public:
	Wall(float cenX, float cenY, float len, float hi, float ang, Player* player );
	bool playerIsInBoundingBox(Player* player);
	void setPlayerRelativeMinMaxXY(Player* player);
	bool hasSATCollision(Player* player);
	sf::VertexArray getVertexArray();
	sf::Vector2f getCornerCoords(int position);
	sf::Vector2f getPlayerRelativeMinCoords();
	sf::Vector2f getPlayerRelativeMaxCoords();
	sf::Vector2f getCenter();
	float getLength();
	float getThickness();
	float getAngle();
	void clearVertexArray();
	//sf::Vector2f getZeroPosition();
	//sf::Vector2f getFirstPosition();
	//sf::Vector2f getSecondPosition();
	//sf::Vector2f getThirdPosition();
	//float getXPrime();
	//float getYPrime();
};
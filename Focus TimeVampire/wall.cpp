#include "utils.h"
#include "gameSprite.h"
#include "wall.h"

Wall::Wall(float cenX, float cenY, float length, float thickness, float ang, float playerR) {
	angleRadians = ang * degreeToRadians;

	const float hyp = sqrt(length * length + thickness * thickness);
	const float arcTan = atan(thickness / length);
	const float angleRadiansMinusArcTan = angleRadians - arcTan;
	const float rX = hyp * cos(angleRadiansMinusArcTan) / 2;
	const float rY = hyp * sin(angleRadiansMinusArcTan) / 2;
	const float xPrime = thickness * sin(angleRadians);
	const float yPrime = thickness * cos(angleRadians);
	wallCenter = sf::Vector2f(cenX, cenY);

	zeroPosition = sf::Vector2f(wallCenter.x + rX, wallCenter.y - rY);
	firstPosition = sf::Vector2f(zeroPosition.x - xPrime, zeroPosition.y - yPrime);
	secondPosition = sf::Vector2f(wallCenter.x - rX, wallCenter.y + rY);
	thirdPosition = sf::Vector2f(secondPosition.x + xPrime, secondPosition.y + yPrime);
	vertexArray.setPrimitiveType(sf::Quads);
	vertexArray.resize(5);
	vertexArray[0].position = zeroPosition;
	vertexArray[1].position = firstPosition;
	vertexArray[2].position = secondPosition;
	vertexArray[3].position = thirdPosition;
	vertexArray[4].position = zeroPosition;
	vertexArray[0].color = sf::Color::Blue; //zero
	vertexArray[1].color = sf::Color::Yellow; //first
	vertexArray[2].color = sf::Color::Red; //second
	vertexArray[3].color = sf::Color::Green; //third

	const float wallRelativeZeroX = zeroPosition.x * cos(angleRadians) - zeroPosition.y * sin(angleRadians);
	const float wallRelativeZeroY = zeroPosition.x * sin(angleRadians) + zeroPosition.y * cos(angleRadians);
	relativeZeroPosition = sf::Vector2f(wallRelativeZeroX, wallRelativeZeroY);
	relativeFirstPosition = sf::Vector2f(wallRelativeZeroX, wallRelativeZeroY - thickness);
	relativeSecondPosition = sf::Vector2f(wallRelativeZeroX - length, wallRelativeZeroY - thickness);
	relativeThirdPosition = sf::Vector2f(wallRelativeZeroX - length, wallRelativeZeroY);
	relativeVertexArray.setPrimitiveType(sf::Quads);
	relativeVertexArray.resize(5);
	relativeVertexArray[0].position = relativeZeroPosition;
	relativeVertexArray[1].position = relativeFirstPosition;
	relativeVertexArray[2].position = relativeSecondPosition;
	relativeVertexArray[3].position = relativeThirdPosition;
	relativeVertexArray[4].position = relativeZeroPosition;

	float i = 0;
	while (i <= vertexArray.getVertexCount() - 2) {
		float minXTemp = 0, minYTemp = 0, maxXTemp = 0, maxYTemp = 0;
		minXTemp = std::min(vertexArray[i].position.x, vertexArray[i + 1].position.x);
		maxXTemp = std::max(vertexArray[i].position.x, vertexArray[i + 1].position.x);
		minYTemp = std::min(vertexArray[i].position.y, vertexArray[i + 1].position.y);
		maxYTemp = std::max(vertexArray[i].position.y, vertexArray[i + 1].position.y);
		(minXTemp < wallMinX) ? wallMinX = minXTemp : true;
		(maxXTemp > wallMaxX) ? wallMaxX = maxXTemp : true;
		(minYTemp < wallMinY) ? wallMinY = minYTemp : true;
		(maxYTemp > wallMaxY) ? wallMaxY = maxYTemp : true;
		i++;
	}
	i = 0;
	while (i <= relativeVertexArray.getVertexCount() - 2) {
		float minXTemp = 0, minYTemp = 0, maxXTemp = 0, maxYTemp = 0;
		minXTemp = std::min(relativeVertexArray[i].position.x, relativeVertexArray[i + 1].position.x);
		maxXTemp = std::max(relativeVertexArray[i].position.x, relativeVertexArray[i + 1].position.x);
		minYTemp = std::min(relativeVertexArray[i].position.y, relativeVertexArray[i + 1].position.y);
		maxYTemp = std::max(relativeVertexArray[i].position.y, relativeVertexArray[i + 1].position.y);
		(minXTemp < relativeWallMinX) ? relativeWallMinX = minXTemp : true;
		(maxXTemp > relativeWallMaxX) ? relativeWallMaxX = maxXTemp : true;
		(minYTemp < relativeWallMinY) ? relativeWallMinY = minYTemp : true;
		(maxYTemp > relativeWallMaxY) ? relativeWallMaxY = maxYTemp : true;
		i++;
	}	
	playerXPrime = playerR * sin(angleRadians) + playerR * cos(angleRadians);
	playerYPrime = playerR * cos(angleRadians) - playerR * sin(angleRadians);
}
void Wall::clearVertexArray() {
	vertexArray.clear();
}
bool Wall::playerIsInBoundingBox(Player* player) {
	if (vertexArray.getBounds().intersects(player->getCircle().getGlobalBounds())) {
		return true;
	}
	return false;
}
void Wall::setPlayerRelativeMinMaxXY(Player* player) {
	float relativeX = 0, relativeY = 0;	
	relativeX = abs(playerXPrime - player->getPreviousPosition().x);
	relativeY = abs(playerYPrime - player->getPreviousPosition().y);

	float playerRelativeMinY = cos(angleRadians) * relativeY + sin(angleRadians) * relativeX;
	float playerRelativeMinX = -sin(angleRadians) * relativeY + cos(angleRadians) * relativeX;
	playerRelativeMinCoords = sf::Vector2f(playerRelativeMinX, playerRelativeMinY);

	float playerRelativeMaxY = playerRelativeMinY + player->getCircle().getRadius() * 2;
	float playerRelativeMaxX = playerRelativeMinX + player->getCircle().getRadius() * 2;
	playerRelativeMaxCoords = sf::Vector2f(playerRelativeMaxX, playerRelativeMaxY);
}
bool Wall::hasSATCollision(Player* player) {
	//All must be true
	//if player min X is less than the wall max X 
	bool playerMinXLTwallMaxX = (player->getNormalAxisMinCoords().x < wallMaxX && playerRelativeMinCoords.x < relativeWallMaxX);
	//if player max X is greater than the wall min X
	bool playerMaxXGTwallMinX = (player->getNormalAxisMaxCoords().x > wallMinX && playerRelativeMaxCoords.x > relativeWallMinX);
	//if player max Y is greater than wall min Y
	bool playerMaxYGTwallMinY = (player->getNormalAxisMaxCoords().y > wallMinY && playerRelativeMaxCoords.y > relativeWallMinY);
	//if player min Y is less than wall max Y
	bool playerMinYLTwallMaxY = (player->getNormalAxisMinCoords().y < wallMaxY && playerRelativeMinCoords.y < relativeWallMaxY);
	if (playerMinXLTwallMaxX && playerMaxXGTwallMinX && playerMaxYGTwallMinY && playerMinYLTwallMaxY) {
		return true;
	}
	return false;
}
sf::Vector2f Wall::getWallCenter() {
	return wallCenter;
}
sf::VertexArray Wall::getVertexArray() {
	return vertexArray;
}
//sf::Vector2f Wall::getPlayerRelativeMinCoords() {
//	return playerRelativeMinCoords;
//}
//sf::Vector2f Wall::getPlayerRelativeMaxCoords() {
//	return playerRelativeMaxCoords;
//}
//sf::Vector2f Wall::getCornerCoords(int position) {
//	return vertexArray[position].position;
//}
//float Wall::getThickness() {
//	return thickness;
//}
//float Wall::getLength() {
//	return length;
//}
//float Wall::getAngle() {
//	return angleDegrees;
//}
//sf::Vector2f Wall::getZeroPosition() {
//	return zeroPosition;
//}
//sf::Vector2f Wall::getFirstPosition() {
//	return firstPosition;
//}
//sf::Vector2f Wall::getSecondPosition() {
//	return secondPosition;
//}
//sf::Vector2f Wall::getThirdPosition() {
//	return thirdPosition;
//}
//float Wall::getXPrime() {
//	return xPrime;
//}
//float Wall::getYPrime() {
//	return yPrime;
//}
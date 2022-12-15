sf::Vector2f xy;
using std::vector;
using std::string;
sf::Texture minigameTexture;

class GameSprite {
private:
	float xScale = 1, yScale = 1;
	sf::Sprite sprite;
	sf::Texture texture;

public:
	GameSprite(string spritePNG, float x, float y);
	const sf::Texture getTexture();
	void setNewTexture(sf::Texture& newTexture); 
	void setSprite(sf::Sprite &newSprite);
	const sf::Sprite getSprite();
	void setSpriteScale(float x, float y);
	void setSpritePosition(sf::Vector2f);
	void setSpriteOrigin();
	bool isSpriteClicked(sf::Event event);
	void setRotation(float angle){
		sprite.setRotation(angle);
	}
	void setPosition(sf::Vector2f newPosition){
		sprite.setPosition(newPosition);
	}
};

GameSprite::GameSprite(string spritePNG, float x, float y){
	texture.loadFromFile(spritePNG);
	xScale = x;
	yScale = y;
	sprite.setTexture(texture);
	sprite.setScale(xScale, yScale);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}
const sf::Texture GameSprite::getTexture(){
	return texture;
}
void GameSprite::setNewTexture(sf::Texture& newTexture){
	sprite.setTexture(newTexture);
}
const sf::Sprite GameSprite::getSprite(){
	return sprite;
}
void GameSprite::setSprite(sf::Sprite &newSprite){
	sprite = newSprite;
}
void GameSprite::setSpriteScale(float x, float y){
	sprite.setScale(x,y);
}
void GameSprite::setSpritePosition(sf::Vector2f newPosition) {
	sprite.setPosition(newPosition);
}
void GameSprite::setSpriteOrigin() {
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}
bool GameSprite::isSpriteClicked(sf::Event event) {
	if (event.type = sf::Event::MouseButtonPressed) {
		return false;
	}else if (sprite.getGlobalBounds().contains(translatedMousePosition)) {
		if (event.type = sf::Event::MouseButtonPressed) {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				return true;
			}
		}
	}
	else {
		return false;
	}
}

void drawIdenticalSpriteVector(sf::Texture& texture, vector<GameSprite> vectorOfRooms) {
	for (int i = 0; i < vectorOfRooms.size(); i++) {
		vectorOfRooms.at(i).setNewTexture(texture);
		window.draw(vectorOfRooms.at(i).getSprite());
	}
}
vector<sf::Vector2f> setMinigamePositions(int rows, int columns, const sf::Sprite& roomSprite, float xSpriteSpacing, float ySpriteSpacing) {

	auto xIncrement = xSpriteSpacing + roomSprite.getGlobalBounds().width;
	auto yIncrement = ySpriteSpacing + roomSprite.getGlobalBounds().height;
	float xPosition = window.getSize().x / 2 - xIncrement * (rows - 1) / 2;
	float yPosition = window.getSize().y / 2 - yIncrement * (columns - 1) / 2;
	sf::Vector2f newPosition(xPosition, yPosition);
	vector<sf::Vector2f> roomPositions{ newPosition };

	for (int i = 0; i < rows; i++) {
		if (i > 0) {
			yPosition += yIncrement;
			xPosition = window.getSize().x / 2 - xIncrement * (rows - 1) / 2;
		}
		for (int j = 1; j <= columns; j++) {
			if (j > 1) {
				xPosition += xIncrement;
			}
			newPosition.x = xPosition;
			newPosition.y = yPosition;
			roomPositions.push_back(newPosition);
		}
	}
	return roomPositions;
}
vector <GameSprite> setMinigameVector(string spritePNG, vector<sf::Vector2f> minigamePositions, float xScale, float yScale) {
	vector <GameSprite> minigameVector;
	for (int i = 1; i < minigamePositions.size(); i++) {
		GameSprite minigame(spritePNG, xScale, yScale);
		minigame.setSpritePosition(minigamePositions.at(i));
		minigameVector.push_back(minigame);
	}
	return minigameVector;
}
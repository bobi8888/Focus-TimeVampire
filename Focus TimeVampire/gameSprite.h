#pragma once

//if something is broken is becuase sf::Sprite getSprite isnt const
class GameSprite {
	private:
		sf::Sprite sprite;
		sf::Texture texture;
		int boundry = 40;
		float xScale = 1, yScale = 1;
		bool isVisible = true, isComplete = false, canMove = false;
		friend class DataSpriteVector;
	public:
		GameSprite(string spritePNG, float x, float y);
		const sf::Texture getTexture();
		void setNewTexture(string spritePNG); 
		void setSprite(sf::Sprite &newSprite);
		sf::Sprite getSprite();
		void setRotation(float angle);
		void setPosition(sf::Vector2f newPosition);
		bool getIsVisible();
		void setVisibilty(bool visibility);
		bool getIsComplete();
		void setToComplete();
		bool getCanMove();
		void handleCanMove(sf::Event event,sf::Vector2f translatedMousePosition);
		int getBoundry();
};

class DataSprite : public GameSprite{
	private: 
		string letter, valueAsString, fullDataString;
		long value;
		bool isComplete = false;
	public:
		using GameSprite::GameSprite;
		string getLetter();
		void setLetter(string newLetter);

		long getLongValue();
		void setLongValue(long currentLong);

		string getStringValue();
		void setStringValue(string string);

		string getFullDataString();
		void setFullDataString(string string);

		bool getIsComplete();
		void setToComplete();
};

class DataSpriteVector {
	private:
		vector <DataSprite> dataSpriteVector;
		bool vectorComplete = false;
	public:
		DataSpriteVector();
		DataSpriteVector(int qty, DataSprite dataSprite);
		void setPositions(sf::Vector2f center, int rows, int columns, float rowSpacing, float colSpacing);

		vector <DataSprite> getDataSpriteVector();
		DataSprite getSingleSprite(int index);
		void addSprite(DataSprite dataSprite, int qty);

		void setCanMove(int index, sf::Event event, sf::Vector2f translatedMousePosition);
		void setSpritePosition(int index, sf::Vector2f newPosition);

		void drawSprites(sf::RenderWindow& window, int skipIndex);
		void updateIndividualTexture(int index, string newTexture);

		void checkForCompletion();
		bool getVectorComplete();
		void setSpriteToComplete(int index);

		string getLetter(int index);
		void setLetters();

		long getLongValues(int index);
		void setLongValues();

		string getFullDataStrings(int itr);
		void setFullDataStrings(std::ostringstream& out);

		void setStringValues(std::stringstream& stream);
};

class PlayerSprite : public GameSprite {
private:
	int spriteContactIndex = -1;
	float movementSpeed = 0, radius = 0, vectorSpeed = 0, vectorDirection = 0, distance = 0;
	bool hasContact = false, collision = false;
	sf::CircleShape spriteRadiusCircle;
	sf::Vector2f previousPosition;
public:
	using GameSprite::GameSprite;
	float getMovementSpeed();
	void setMovementSpeed(float speed);
	sf::Vector2f getPreviousPosition();
	void setPreviousPosition(sf::Vector2f currentPosition);
	float getRadius();
	void setRadius(float newRadius);

	sf::CircleShape getSpriteRadiusCircle();
	void initializeSpriteRadiusCircle(float radius, size_t pointcount);
	void setSpriteRadiusCirclePosition(sf::Vector2f playerPosition);

	bool getCollision();
	void setCollision(sf::VertexArray vertexArray);

	sf::Sprite setMovement(sf::RenderWindow& window);

	void handleCollision(sf::VertexArray vertexArray);

	bool hasCircleContactWithSprite(const sf::Sprite& sprite, int boundry);
	int getSpriteContactIndex();
	void setSpriteContactIndex(int itr);
	void handleSpriteContactIndex(DataSpriteVector dataSpriteVector, int boundry);
};
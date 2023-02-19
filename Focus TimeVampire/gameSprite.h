#pragma once

//if something is broken is becuase sf::Sprite getSprite isnt const
class GameSprite {
	private:
		sf::Sprite sprite;
		sf::Texture texture;
		float xScale = 1, yScale = 1;
		bool isVisible = true, isComplete = false, canMove = false;
		friend class TransformableSprite;
		friend class DataSpriteVector;
	public:
		GameSprite(string spritePNG, float x, float y);
		const sf::Texture getTexture();
		void setNewTexture(string spritePNG); 
		void setSprite(sf::Sprite &newSprite);
		sf::Sprite getSprite();
		void setSpritePosition(sf::Vector2f);
		void setRotation(float angle);
		void setPosition(sf::Vector2f newPosition);
		bool getIsVisible();
		void setVisibilty(bool visibility);
		bool getIsComplete();
		void setToComplete();
		bool getCanMove();
		void handleCanMove(sf::Event event,sf::Vector2f translatedMousePosition);
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
		DataSpriteVector(int qty, DataSprite& dataSprite);
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
	float movementSpeed = 0, radius = 0;
	bool hasContact = false;
public:
	using GameSprite::GameSprite;
	float getMovementSpeed();
	void setMovementSpeed(float speed);
	float getRadius();
	void setRadius(float newRadius);
	sf::Sprite setMovement(sf::RenderWindow& window);
	bool hasCircleContact(const sf::Sprite& sprite);
	int getSpriteContactIndex();
	void setSpriteContactIndex(int itr);
	void handleSpriteContactIndex(DataSpriteVector dataSpriteVector);
};
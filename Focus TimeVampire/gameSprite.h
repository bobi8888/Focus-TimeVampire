#pragma once

//if something is broken is becuase sf::Sprite getSprite isnt const
class GameSprite {
	private:
		sf::Sprite sprite;
		sf::Texture texture;
		float xScale = 1, yScale = 1;
		bool isVisible = true, isComplete = false;
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
		DataSpriteVector(int qty, DataSprite& dataSprite);
		vector <DataSprite> getDataSpriteVector();
		DataSprite getSingleSprite(int index);
		void addSprite(DataSprite dataSprite, int qty);

		void setSpritePositions(int rows, int columns, float xSpriteSpacing, float ySpriteSpacing, float initialX, float initialY);
		void setAndCenterSpritePositions(int index, int rows, int columns, float xSpriteSpacing, float ySpriteSpacing, sf::RenderWindow& window);
		void drawSprites(sf::RenderWindow& window);
		void updateIndividualTexture(int index, string newTexture);
		void checkForCompletion();
		bool getVectorComplete();

		string getLetter(int index, int itr);
		void setLetter(int index);

		long getLongValues(int index, int itr);
		void setLongValues(int index);

		void setStringValues(std::stringstream& stream);

		string getFullDataStrings(int index, int itr);
		void setFullDataStrings(std::ostringstream& out);

		void setSpriteToComplete(int index);
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
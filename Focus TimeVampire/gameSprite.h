#pragma once
//if something is broken is becuase sf::Sprite getSprite isnt const
class GameSprite {
	private:
		sf::Sprite sprite;
		sf::Texture texture;
		bool isVisible = true, isComplete = false, canMove = false;

		//FORCE
		float direction = 0;
		float calc_Dir_x = 0, calc_Dir_y = 0;
		int quadrant = 0;
		sf::Vector2f forceOnPlayer;
		float gravConst = 0.00000000006;
		float mass = 700000, distance = 0;
		float gravitationalForce = 0;
		float forceX = 0, forceY = 0;

		friend class DataSpriteVector;
	public:
		GameSprite(string spritePNG, float x, float y);
		void setNewTexture(string spritePNG); 
		sf::Sprite getSprite();
		void setRotation(float angle);
		void setPosition(sf::Vector2f newPosition);
		bool getIsVisible();
		void setVisibilty(bool visibility);
		bool getIsComplete();
		void setToComplete();
		bool getCanMove();
		void handleCanMove(sf::Event event,sf::Vector2f translatedMousePosition);

		float returnQuadrantDirectionTowardsPlayerInDegrees(sf::CircleShape circle);
		void setQuadrant(sf::CircleShape circle);
		sf::Vector2f getForceOnPlayer();
		void setForceOnPlayer(sf::CircleShape circle, float playerMass);

		void setForceMagnetude(float charge, float velo);
};

class DataSprite : public GameSprite{
	private: 
		string letter, valueAsString, fullDataString;
		long value;
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

class Player {
private:
	sf::CircleShape circle;
	sf::Texture texture;

	//Gravity
	float mass = 6000000;

	//MOVEMENT
	float rotationSpeed = 0, x = 0, y = 0;

	//SPEED
	sf::Clock clock;
	float xSpeed = 0, ySpeed = 0, playerSpeed = 0.1;
	float acceleration = 0;

	//VELOCITY
	float calc_Dir_x = 0, calc_Dir_y = 0;
	float direction = 0;
	int quadrant = 0;
	float velocity = 0;

	//COLLISION
	sf::Vector2f previousPosition;
	int spriteContactIndex = -1;
	friend class Wall;

public:
	Player(string newTexture, float speed, float rotationSpeed, float scale);
	sf::CircleShape getCircle();
	void setPlayerPosition(sf::Vector2f newPosition);
	void setPreviousPosition();
	void setPlayerSpeed(float newSpeed);

	int getSpriteContactIndex();
	void setSpriteContactIndex(int index);
	void handlePlayerMotion();

	//Player movement and screen bounds
	bool isAnyArrowKeyDown();
	void handleArrowKeyInput();
	void handleScreenBoundsCollision(sf::RenderWindow& window);
	void handlePlayerMovementWithinScreen(sf::RenderWindow& window, float deltaTime);

	//Vertex Array Collisions
	bool hasVertexArrayCollision(Wall testWall);
	void handleVertexArrayCollision(Wall testWall);

	//Sprite Collisions
	bool hasSpriteCollision(sf::Sprite sprite);

	//void handleAllCollisions(sf::RenderWindow& window, DataSpriteVector test, sf::Sprite acceptSprite);

	//Velocity & Gravity
	float getMass();

	//Direction
	void setQuadrant();
	void setDirectionInDegrees();

	bool hasRectangleCollision(sf::VertexArray vertexArray);
};
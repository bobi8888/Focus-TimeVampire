#pragma once
//if something is broken is becuase sf::Sprite getSprite isnt const
class GameSprite {
	private:
		sf::Sprite sprite;
		sf::Texture texture;
		int boundry = 40;
		//float xScale = 1, yScale = 1;
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

class Player {
private:
	sf::CircleShape circle;
	sf::Texture texture;
	sf::Clock clock;
	sf::Vector2f previousPosition;
	float movementSpeed = 0, rotationSpeed = 0;
	float direction = 0;
	float calc_Dir_x = 0, calc_Dir_y = 0;
	int spriteContactIndex = -1;
	int quadrant = 0;
	vector <sf::Vector2f> directionVector{ sf::Vector2f(0,0), sf::Vector2f(0,0) };

	float charge = 1;
	float velocity = 0;
	float E_electFieldStr = 2;
	float B_magFieldStr = 2;
	float theta_magFieldAngle = 90;
	float xForce = 0, yForce = 0;
	const double mu0 = 4 * 3.14 * 1e-7;
	double strength;

public:
	Player(string newTexture, float movementSpeed, float rotationSpeed, float scale);

	vector<double> calculateMagneticForce(Player magOne, Player magTwo);

	sf::CircleShape getCircle();
	void setPosition(sf::Vector2f newPosition);
	void setMovementSpeed(float movement);
	int getSpriteContactIndex();
	void setSpriteContactIndex(int index);
	float getPositiveCharge();
	float getNegativeCharge();
	void setCharge(float);
	sf::Vector2f getPreviousPosition();
	float getVelocity();
	void setVeloity(float);
	void calculateVelocity();
	int getQuadrant();
	void setQuadrant(const sf::Sprite& acceptSprite);
	float returnCalculatedDirection(const sf::Sprite& acceptSprite);
	//cirlceVector + newVector = new position
	void calculateDirectionVector();
	void spriteForce(float angle, float magnitude);

	bool isAnyArrowKeyDown();
	void handlePlayerInput(sf::RenderWindow& window);

	bool hasVertexArrayCollision(sf::VertexArray vertexArray);
	bool hasSpriteCollision(sf::Sprite sprite);
	void handleScreenBoundsCollision(sf::RenderWindow& window);
	void handleVertexArrayCollision(sf::VertexArray vertexArray);

	sf::Vector2f handleRepulsion(const sf::Sprite& acceptSprite);
	void handlePlayerMovement(sf::RenderWindow& window, DataSpriteVector test, sf::Sprite acceptSprite);

	sf::Vector2f applyForces(DataSpriteVector test);
	void setXForce(float newForce);
	void setYForce(float newForce);
};

//class PlayerSprite : public GameSprite {
//private:
//	int spriteContactIndex = -1;
//	float movementSpeed = 0, radius = 0;
//	bool hasContact = false, collision = false;
//	sf::CircleShape spriteRadiusCircle;
//	sf::CircleShape circle;
//	sf::Vector2f previousPosition = sf::Vector2f(250,250);
//public:
//	using GameSprite::GameSprite;
//	float getMovementSpeed();
//	void setMovementSpeed(float speed);
//	sf::Vector2f getPreviousPosition();
//	void setPreviousPosition(sf::Vector2f currentPosition);
//	float getRadius();
//	void setRadius(float newRadius);
//
//	sf::CircleShape getSpriteRadiusCircle();
//	void initializeSpriteRadiusCircle(size_t pointcount);
//	void setSpriteRadiusCirclePosition();
//
//	bool getCollision();
//	void setCollision(sf::VertexArray vertexArray);
//
//	sf::Sprite setMovement(sf::RenderWindow& window);
//
//	void handleCollision(sf::VertexArray vertexArray);
//
//	bool hasCircleContactWithSprite(const sf::Sprite& sprite, int boundry);
//	int getSpriteContactIndex();
//	void setSpriteContactIndex(int itr);
//	void handleSpriteContactIndex(DataSpriteVector dataSpriteVector, int boundry);
//};
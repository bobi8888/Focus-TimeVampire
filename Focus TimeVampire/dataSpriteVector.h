#pragma once
using std::vector;

class DataSprite;
class TransformableSprite;
class DataSpriteVector {
	private:
		vector <DataSprite> dataSpriteVector;
		bool vectorComplete = false;
		//friend class GameSprite;
		//friend class DataSprite;		
		//friend class TransformableSprite;
	public:
		DataSpriteVector(){};
		vector <DataSprite> getDataSpriteVector();
		void addSprite(DataSprite dataSprite, int qty);
		void setSpritePositions(int rows, int columns, float xSpriteSpacing, float ySpriteSpacing, float initialX, float initialY);
		void setAndCenterSpritePositions(int index, int rows, int columns, float xSpriteSpacing, float ySpriteSpacing, sf::RenderWindow &window);
		void drawSprites(sf::RenderWindow& window);

		void updateIndividualTexture(int indextPostition, string newTexture);
		void updateVectorComplete();
		bool getVectorComplete();
		void setSpriteToComplete(int index);
		bool isSpriteComplete(TransformableSprite player);

		string getLetter(int index, int itr);
		void setLetter(int numberNeeeded);

		long getLongValues(int index, int itr);
		void setLongValues(int numberNeeeded);

		void setStringValues(std::stringstream &out);

		string getFullDataStrings(int index, int itr);
		void setFullDataStrings(std::ostringstream& out);

};
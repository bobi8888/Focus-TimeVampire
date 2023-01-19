#pragma once

using std::string;

class GameSprite {
	private:
		sf::Sprite sprite;
		sf::Texture texture;
		float xScale = 1, yScale = 1, progression = 0;
		bool isVisible = true;
	public:
		GameSprite();
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
		float getProgress();
		void setProgress(float progress);
};
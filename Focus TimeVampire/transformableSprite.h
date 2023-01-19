#pragma once

class TransformableSprite : public GameSprite {
	private:
		int spriteContactIndex = -1;
		float movementSpeed, radius;
		bool hasContact = false;
		//friend class GameSprite;
		friend class DataSpriteVector;
	public:
		using GameSprite::GameSprite;
		TransformableSprite(float buildSpeed, float buildRadius);
		float getMovementSpeed();
		void setMovementSpeed(float speed);
		float getRadius();
		void setRadius(float newRadius);
		sf::Sprite setMovement(sf::RenderWindow &window);
		bool hasCircleContact(const sf::Sprite &sprite);
		int getSpriteContactIndex();
		void setSpriteContactIndex(int itr);
		void handleSpriteContactIndex(DataSpriteVector dataSprite);
};
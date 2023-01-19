#pragma once

class TransformableSprite : public GameSprite {
	private:
		int spriteContactIndex = -1;
		float movementSpeed, radius;
		bool hasContact = false;
	public:
		using GameSprite::GameSprite;
		TransformableSprite(float buildSpeed, float buildRadius);
		float getMovementSpeed();
		void setMovementSpeed(float speed);
		float getRadius();
		void setRadius(float newRadius);
		sf::Sprite setMovement(sf::RenderWindow &window);
		bool hasCircleContact(sf::Sprite sprite);
		int getSpriteContactIndex();
		void setSpriteContactIndex(int itr);
		void handleSpriteContactIndex(DataSpriteVector dataSpriteVector);
};
class GameScreen{
	private:
		vector <sf::Sprite> vectorOfSprites;
		GameText screenText;
	public:
		GameScreen(string string);
		void addSprite(const sf::Sprite &newSprite);
		vector <sf::Sprite> getScreenSprites();
		sf::Sprite getSpriteFromVector(int vectorPositon);
		sf::Text setAndCenterTitle(string newTitle);
		void drawScreen(sf::RenderWindow& window, const sf::Text& tooltipText);
		friend class GameText;
};

GameScreen::GameScreen(string string){
	screenText.setFont(font);
	screenText.getText().setFont(font);
	screenText.setCharSize(titleCharSize);
	screenText.setString(string);
	screenText.setOrigin(sf::Vector2f(screenText.getText().getGlobalBounds().width / 2, screenText.getText().getCharacterSize() / 2 
	+ ((screenText.getText().getCharacterSize() - screenText.getText().getGlobalBounds().height) / 2)));
	screenText.setPosition(sf::Vector2f(window.getSize().x / 2, titleSpaceFromTop));
}
void GameScreen::addSprite(const sf::Sprite &newSprite){
	vectorOfSprites.push_back(newSprite);
}
vector <sf::Sprite> GameScreen::getScreenSprites(){
	return vectorOfSprites;
}
sf::Sprite GameScreen::getSpriteFromVector(int vectorPosition){
	return getScreenSprites().at(vectorPosition);
}
sf::Text GameScreen::setAndCenterTitle(string newTitle){
	screenText.setStringAndCenterOrigin(newTitle);
	return screenText.getText();
}
void GameScreen::drawScreen(sf::RenderWindow &window, const sf::Text& tooltipText) {
	window.draw(tooltipText);
	window.draw(screenText.getText());
	for (int i = 0; i < vectorOfSprites.size(); i++) {
		window.draw(vectorOfSprites[i]);
	}
}
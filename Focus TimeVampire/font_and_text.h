using std::string;

sf::Font font;
int titleCharSize = 25;
float titleSpaceFromTop = 25;
bool loadFont(sf::Font& font) {
	if (!font.loadFromFile("RobotoCondensed-Regular.ttf")) {
		std::cout << "Error: Font not loaded." << printf("\n");
		return false;
	}
	return true;
}

class GameText{
	private:
		sf::Font gt_font;
		sf::Text text;
		int charSize = 10;

	public:
		GameText(){};
		GameText(int characterSize, string string, float spaceFromTop, sf::RenderWindow &window);
		void setString(string string);
		int getCharSize();
		void setCharSize(int charSize);
		sf::Vector2f getOrigin();
		void setOrigin(sf::Vector2f origin);
		sf::Vector2f getPosition();
		void setPosition(sf::Vector2f position);
		void centerOrigin();
		sf::Font getFont();
		void setFont(sf::Font &font);
		sf::Text& getText();
		sf::Text& setStringAndCenterOrigin(string string);
		friend class GameSceen;
};

GameText::GameText(int characterSize, string string, float spaceFromTop, sf::RenderWindow &window){
	text.setFont(font);
	text.setCharacterSize(characterSize);
	text.setString(string);
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2, characterSize / 2 + ((characterSize - text.getGlobalBounds().height) / 2)));
	text.setPosition(sf::Vector2f(window.getSize().x / 2, spaceFromTop));
}
void GameText::setString(string string){
	text.setString(string);
}
int GameText::getCharSize(){
	return text.getCharacterSize();
}
void GameText::setCharSize(int charSize){
	text.setCharacterSize(charSize);
}
sf::Vector2f GameText::getOrigin(){
	return text.getOrigin();
}
void GameText::setOrigin(sf::Vector2f origin){
	text.setOrigin(origin);
}
sf::Vector2f GameText::getPosition(){
	return text.getPosition();
}
void GameText::setPosition(sf::Vector2f position){
	text.setPosition(position);
}
void GameText::centerOrigin() {
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2, text.getCharacterSize() / 2 + ((text.getCharacterSize() - text.getGlobalBounds().height) / 2)));
}
sf::Font GameText::getFont(){
	return font;
}
void GameText::setFont(sf::Font& newFont){
	gt_font = newFont;
}
sf::Text& GameText::getText(){
	return text;
}
sf::Text& GameText::setStringAndCenterOrigin(string string) {
	text.setString(string);
	text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2, text.getCharacterSize() / 2 + ((text.getCharacterSize() - text.getGlobalBounds().height) / 2)));
	return text;
}
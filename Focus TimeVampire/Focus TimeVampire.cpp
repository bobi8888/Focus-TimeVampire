#include "utils.h"
#include "window.h"
#include "gameText.h"
#include "mouse.h"
#include "gameSprite.h"
#include "gameScreen.h"
#include "gameTimer.h"
#include "randomizedData.h"

//ISSUES
//reset random numbers each playthrough for Remember
//add reset button
//add X_out button
//switches are good for catching errors
//changing window size and player movement

int main() {	
	//WINDOW
	antialiasing.antialiasingLevel = 8;
	window.setVerticalSyncEnabled(true);
	window.setPosition(sf::Vector2i(1400, 400));
	window.setKeyRepeatEnabled(false);

	//TIME
	GameTimer gameTimer;
	sf::Clock timerClock;
	sf::Clock typingClock;
	sf::Time gameTime;
	std::ostringstream out;
	std::stringstream stream;
	srand(time(NULL));

	//FONT & TEXT
	sf::Font generalFont;
	loadFont(generalFont);
	//can playerInput be GameText obj?
	sf::String playerInput;

	GameText timerText(generalFont, 20, "", 20, window);
	timerText.setPosition(sf::Vector2f(5,30));
	GameText bannerText(generalFont, 20,"",0, window);
	bannerText.setFillColor(sf::Color::Black);
	GameText playerText(generalFont, 30, "", 400, window);
	playerText.setFillColor(sf::Color::White);	
	GameText tipText(generalFont, 25, "Enter the missing values!", 55, window);
	playerText.setFillColor(sf::Color::White);

	//GAME SPRITES
	GameSprite startButton("startSprite.png", 0.5, 0.5);
	startButton.setSpritePosition(getCenterOfWindow(window));
	GameSprite pauseButton("pauseSprite.png", 0.25, 0.25);
	pauseButton.setSpritePosition(sf::Vector2f(window.getSize().x - 35, 40));
	GameSprite resumeButton("resumeSprite.png", 0.5, 0.5);
	resumeButton.setSpritePosition(getCenterOfWindow(window));
	GameSprite bannerSprite("bannerSprite.png", 1, 1);
	bannerSprite.setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y - 50));
	bannerText.setPosition(sf::Vector2f(bannerSprite.getSprite().getPosition().x, bannerSprite.getSprite().getPosition().y - 20));
	GameSprite x_outButton("x_outSprite.png", 0.25, 0.25);
	x_outButton.setPosition(sf::Vector2f(bannerSprite.getSprite().getPosition().x + bannerSprite.getSprite().getGlobalBounds().width/2 - 15
	, bannerSprite.getSprite().getPosition().y - bannerSprite.getSprite().getGlobalBounds().height / 2 + 30));	
	GameSprite backButton("backSprite.png", 0.18, 0.18);
	backButton.setPosition(sf::Vector2f(window.getSize().x - 55, window.getSize().y - 30));
	 
	//TRANSFORMABLE SPRITES
	PlayerSprite player("playerSprite.png", 0.4, 0.4);
	player.setSpritePosition(getCenterOfWindow(window));
	player.setMovementSpeed(4);
	player.setRadius(player.getSprite().getGlobalBounds().height/2);

	//DATA SPRITES
	DataSprite minigameSprite("minigameSprite.png", 0.3, 0.3);
	DataSprite fullBubble("fullBubbleSprite.png", 1, 1);
	DataSprite emptyBubble("emptyBubbleSprite.png", 1, 1);

	//SPRITE VECTORS
	DataSpriteVector rememberFullBubbles(3,fullBubble);
	DataSpriteVector rememberEmptyBubbles(3, emptyBubble);
	rememberFullBubbles.setSpritePositions(3, 1, 1, 35, 100, 125);
	rememberEmptyBubbles.setSpritePositions(3, 1, 1, 35, 400, 125);
	rememberFullBubbles.setLetter(0);
	rememberFullBubbles.setLongValues(0);
	rememberFullBubbles.setStringValues(stream);
	rememberFullBubbles.setFullDataStrings(out);
	DataSpriteVector minigameSprites(9, minigameSprite);
	minigameSprites.setAndCenterSpritePositions(0, 3, 3, 1, 1, window);

	//MAIN GAME SCREENS
	GameScreen startScreen("FOCUS! Time Vampire", generalFont, 25, 25);
	startScreen.addSprite(startButton.getSprite());
	GameScreen gameScreen("FOCUS! Time Vampire", generalFont, 25, 25);
	GameScreen resumeScreen("FOCUS! Time Vampire", generalFont, 25, 25);
	resumeScreen.addSprite(resumeButton.getSprite());

	//MINIGAMES
	GameScreen remember("REMEMBER!", generalFont, 25, 25);
	bannerText.setStringAndCenterOrigin("Enter #", 0, 0);
	GameScreen count("COUNT!", generalFont, 25, 25);
	GameScreen assemble("ASSEMBLE!", generalFont, 25, 25);
	GameScreen discuss("DISCUSS!", generalFont, 25, 25);
	GameScreen ignore("IGNORE!", generalFont, 25, 25);
	GameScreen drive("DRIVE!", generalFont, 25, 25);
	GameScreen retain("RETAIN!", generalFont, 25, 25);
	GameScreen push("PUSH!", generalFont, 25, 25);
	GameScreen bonus("BONUS!", generalFont, 25, 25);

	bool deleteKeyWorkaround = false;//both needed for delete workaround
	bool acceptText = false;

	enum mainScreens { startMAIN, gameMAIN, resumeMAIN };
	enum gameScreens { rememberENUM, countENUM, assembleENUM, discussENUM, ignoreENUM, driveENUM, retainENUM, pushENUM, bonusENUM, mainENUM };
	mainScreens mainScreenENUM = startMAIN;
	gameScreens gameScreenENUM = mainENUM;

	//GAME LOOP: mainScreenENUM
	sf::Event event;
	while (window.isOpen()) {
		window.display();
		window.clear();
		translatedMousePosition = setMousePosition(window);

		while (window.pollEvent(event)) {//this includes the closed window event & entering text
			if (event.type == sf::Event::Closed)
				window.close();

			if (acceptText) {
				switch (event.key.code) {
					case sf::Keyboard::Delete://66
						if(!deleteKeyWorkaround){
							playerText.deleteLastChar(playerInput, out);
							playerText.setIsFull(false);
							deleteKeyWorkaround = true;
						}else{
							deleteKeyWorkaround = false;
						}
						break;
				}
			
				if (event.type == sf::Event::TextEntered) {
					string outString;
					switch (event.text.unicode){
						case 27://ESCAPE
							playerInput.clear();
							playerText.setString("");
							playerText.setIsFull(false);
							break;

						case 8://BACKSPACE
							playerText.deleteLastChar(playerInput,out);
							playerText.setIsFull(false);
							break;					
					}
			
					if(!playerText.getIsFull()){
						if (event.text.unicode <= 57 && event.text.unicode >= 48) {
							playerInput += event.text.unicode;//playerInput is sf::String, and the exact num of ints
							out.imbue(std::locale(""));
							out << std::put_money(playerInput);
							string outString = '$' + out.str();
							playerText.setStringAndCenterOrigin(outString, 0, -55);//playerText is GameText and its size includes put_money
							out.str("");
						}
					} else {
						playerInput = "";
					}
				}
			}
		
		}
		switch (mainScreenENUM){
			case startMAIN://START SCREEN
				startScreen.drawScreen(window, timerText.getText());
				//PRESS START TO BEGIN GAME
				if (event.type == sf::Event::EventType::MouseButtonPressed){
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && 
					startButton.getSprite().getGlobalBounds().contains(translatedMousePosition)) {
						timerClock.restart();
						mainScreenENUM = gameMAIN;
						event.type = sf::Event::MouseButtonReleased;
					}
				}
			break;	 

			case gameMAIN://GAME SCREEN
				window.draw(pauseButton.getSprite());
				if (gameTimer.getTimeRemaining() > 0) {
					timerText.setString(gameTimer.getString(out));
					gameTimer = gameTimer.manageGameTimer(timerClock, gameTimer);	
					
					//create function for the mouse click event?
					if (event.type == sf::Event::EventType::MouseButtonPressed) {
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && pauseButton.getSprite().getGlobalBounds().contains(translatedMousePosition)) {
							gameTimer = gameTimer.pause(timerClock, gameTimer);
							timerText.setString(("::Paused::"));
							mainScreenENUM = resumeMAIN;
						}
					}		

					if(gameScreenENUM != mainENUM){//BACK BUTTON
						window.draw(backButton.getSprite());
						if (event.type == sf::Event::EventType::MouseButtonPressed) {
							if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && backButton.getSprite().getGlobalBounds().contains(translatedMousePosition)) {
								gameScreenENUM = mainENUM;
							}
						}
					}

					switch(gameScreenENUM){
						case mainENUM:
							gameScreen.drawScreen(window, timerText.getText());
							minigameSprites.drawSprites(window);
							//SWITCH FOR WHICH MINIGAME IS SELECTED
							if (event.type == sf::Event::EventType::MouseButtonPressed) {
								for (int i = 0; i < minigameSprites.getDataSpriteVector().size(); i++) {
									if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && 
									minigameSprites.getSingleSprite(i).getSprite().getGlobalBounds().contains(translatedMousePosition)) {
										if (!minigameSprites.getSingleSprite(i).getIsComplete())
										gameScreenENUM = static_cast<gameScreens>(i);
									}
								}
							}
						break;
						case rememberENUM://REMEMBER
						//swapping can be used to randomize vectors to increase difficulty
							player.setMovement(window);
							window.draw(tipText.getText());
							window.draw(player.getSprite()); 
							rememberFullBubbles.drawSprites(window);
							rememberEmptyBubbles.drawSprites(window);
							remember.drawScreen(window, timerText.getText());

							for (int i = 0; i < rememberFullBubbles.getDataSpriteVector().size(); i++) {//contacting full sprites
								if (player.hasCircleContact(rememberFullBubbles.getDataSpriteVector()[i].getSprite()) == true){
									bannerText.setCharSize(25);
									bannerText.setStringAndCenterOrigin(rememberFullBubbles.getFullDataStrings(0,i), 0, - 15);
									window.draw(bannerSprite.getSprite());
									window.draw(bannerText.getText());
								}
							}		
							
							player.handleSpriteContactIndex(rememberEmptyBubbles);
							if (player.getSpriteContactIndex() >= 0) {
								if (rememberEmptyBubbles.getSingleSprite(player.getSpriteContactIndex()).getIsComplete()) {//checking if contacted sprite is complete
								} else {//sprite incomplete, check if text can be entered
									bannerText.enterLetterPrompt(23, rememberFullBubbles.getSingleSprite(player.getSpriteContactIndex()).getLetter());
									window.draw(bannerSprite.getSprite());
									window.draw(bannerText.getText());
									window.draw(playerText.getText());
									if (playerInput.getSize() <= rememberFullBubbles.getSingleSprite(player.getSpriteContactIndex()).getStringValue().size() - 1) {
										acceptText = true;
									} else {//no check for a match
										acceptText = false;
										if (playerInput.toAnsiString() == rememberFullBubbles.getSingleSprite(player.getSpriteContactIndex()).getStringValue()) {
											rememberEmptyBubbles.updateIndividualTexture(player.getSpriteContactIndex(), "okBubbleSprite.png");
											rememberEmptyBubbles.setSpriteToComplete(player.getSpriteContactIndex());
										} 
									}
								}
							} else {// no contact
								playerInput.clear();
								playerText.setString("");
								acceptText = false;
							}
							
							if (!rememberEmptyBubbles.getVectorComplete()) {
								rememberEmptyBubbles.checkForCompletion();
							} else {
								minigameSprites.updateIndividualTexture(rememberENUM, "completedMinigameSprite.png");
								minigameSprites.setSpriteToComplete(rememberENUM);
								gameScreenENUM = mainENUM;	
							}							
						break;
						case countENUM://COUNT
							count.drawScreen(window, timerText.getText());
						break;
						case assembleENUM://ASSEMBLE
							assemble.drawScreen(window, timerText.getText());
						break;
						case discussENUM://DISCUSS
							discuss.drawScreen(window, timerText.getText());
						break;
						case ignoreENUM://IGNORE
							ignore.drawScreen(window, timerText.getText());
						break;
						case driveENUM://DRIVE
							drive.drawScreen(window, timerText.getText());
						break;
						case retainENUM://RETAIN
							retain.drawScreen(window, timerText.getText());
						break;
						case pushENUM://PUSH
							push.drawScreen(window, timerText.getText());
						break;
						case bonusENUM://BONUS
							bonus.drawScreen(window, timerText.getText());
						break;
					}

				}else{//TIME IS UP
					gameTimer = gameTimer.timeUp(gameTimer);
					timerText.setString("Time Up!");
					startScreen.setAndCenterTitle("GAME OVER!");
					player.setPosition(getCenterOfWindow(window));
					mainScreenENUM = startMAIN;
					gameScreenENUM = mainENUM;
				}
			break;

			case resumeMAIN://RESUME			
				assert(gameTimer.getTimeRemaining() > 0);
				resumeScreen.drawScreen(window, timerText.getText());
				if (event.type == sf::Event::EventType::MouseButtonPressed) {
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && resumeButton.getSprite().getGlobalBounds().contains(translatedMousePosition)) {
						timerClock.restart();
						mainScreenENUM = gameMAIN;
						
					}
				}
				event.type = sf::Event::EventType::MouseButtonReleased;//this stops clicking through sprites
			break;
		}
		
	}
}
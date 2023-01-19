//#include <iostream>

//BUSTED

#include "utils.h"
#include "window.h"
#include "gameText.h"
#include "mouse.h"

#include "gameSprite.h"
#include "dataSprite.h"
#include "dataSpriteVector.h"
#include "transformableSprite.h"

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
	//GameText playerInput;

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
	TransformableSprite player("playerSprite.png", 0.4, 0.4);
	player.setSpritePosition(getCenterOfWindow(window));
	player.setMovementSpeed(4);
	player.setRadius(player.getSprite().getGlobalBounds().height/2);

	//DATA SPRITES
	DataSprite minigameSprite("minigameSprite.png", 0.2, 0.2);
	DataSprite fullBubble("fullBubbleSprite.png", 1, 1);
	DataSprite emptyBubble("emptyBubbleSprite.png", 1, 1);

	//SPRITE VECTORS
	DataSpriteVector rememberFullBubbles;
	DataSpriteVector rememberEmptyBubbles;
	rememberFullBubbles.addSprite(fullBubble, 3);
	rememberEmptyBubbles.addSprite(emptyBubble, 3);

	rememberFullBubbles.setSpritePositions(3, 1, 1, 35, 100, 125);
	rememberEmptyBubbles.setSpritePositions(3, 1, 1, 35, 400, 125);

	rememberFullBubbles.setLetter(0);
	rememberFullBubbles.setLongValues(0);
	rememberFullBubbles.setStringValues(stream);
	rememberFullBubbles.setFullDataStrings(out);

	DataSpriteVector minigameSprites;
	minigameSprites.addSprite(minigameSprite, 9);
	minigameSprites.setAndCenterSpritePositions(0, 3, 3, 1, 1, window);

	//MAIN GAME SCREENS
	GameScreen startScreen("FOCUS! Time Vampire", generalFont, 25, 25);
	startScreen.addSprite(startButton.getSprite());
	GameScreen gameScreen("FOCUS! Time Vampire", generalFont, 25, 25);
	GameScreen resumeScreen("FOCUS! Time Vampire", generalFont, 25, 25);
	resumeScreen.addSprite(resumeButton.getSprite());

	//MINIGAMES
	//GameScreen remember("REMEMBER!");

	////GameScreen count("COUNT!");
	//GameScreen assemble("ASSEMBLE!");
	//GameScreen discuss("DISCUSS!");
	//GameScreen ignore("IGNORE!");
	//GameScreen drive("DRIVE!");
	//GameScreen retain("RETAIN!");
	//GameScreen push("PUSH!");
	//GameScreen bonus("BONUS!");
	GameScreen remember("REMEMBER!", generalFont, 25, 25);
	bannerText.setStringAndCenterOrigin("Enter #", 0, 0);
	remember.addSprite(fullBubble.getSprite());
	remember.addSprite(emptyBubble.getSprite());
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
									minigameSprites.getDataSpriteVector()[i].getSprite().getGlobalBounds().contains(translatedMousePosition)) {
										gameScreenENUM = static_cast<gameScreens>(i);
									}
								}
							}
						break;
						case rememberENUM://REMEMBER
						// should not be able to input numbers if the playerSprite is not in contact with dataSprite
						//swapping can be used to randomize vectors to increase difficulty
							player.setMovement(window);
							window.draw(tipText.getText());
							window.draw(player.getSprite()); 
							rememberFullBubbles.drawSprites(window);
							rememberEmptyBubbles.drawSprites(window);
							remember.drawScreen(window, timerText.getText());

							for (int i = 0; i < rememberFullBubbles.getDataSpriteVector().size(); i++) {//full
								if (player.hasCircleContact(rememberFullBubbles.getDataSpriteVector()[i].getSprite()) == true){
									bannerText.setCharSize(25);
									bannerText.setStringAndCenterOrigin(rememberFullBubbles.getFullDataStrings(0,i), 0, - 15);
									window.draw(bannerSprite.getSprite());
									window.draw(bannerText.getText());
								}
							}			
							
							//Correctly handling the contact index
							player.handleSpriteContactIndex(rememberEmptyBubbles);

							//check if spriteContactIndex is > 0, that means that there has been contact
							//if (player.getSpriteContactIndex() > 0){
							//	//yes check if contacted sprite is complete
							//	std::cout << player.getSpriteContactIndex() << "\n";// used for debug
							//	if (rememberEmptyBubbles.isSpriteComplete(player)) {//yes
							//		acceptText = false;
							//		std::cout << "sprite is complete \n";// used for debug
							//	} else {//no check if text can be entered
							//		std::cout << "sprite is NOT complete \n";// used for debug
							//		acceptText = true;

							//		//func to handle setting the banner?
							//		bannerText.enterLetterPrompt(23, rememberFullBubbles, player);

							//		//bannerText.setCharSize(23);
							//		//string letter = rememberFullBubbles.getLetter(0, player.getSpriteContactIndex());
							//		//bannerText.setStringAndCenterOrigin("Enter " + letter, 0, 0);

							//		window.draw(bannerSprite.getSprite());//need to update the banner for entering text
							//		window.draw(bannerText.getText());
							//		window.draw(playerText.getText());

							//		//create bool for if text can be accepted
							//		if (~playerInput.getSize() > rememberFullBubbles.getDataSpriteVector()[player.getSpriteContactIndex()].getStringValue().size() - 1) {
							//			//yes text can be entered
							//		} else {//no check for a match
							//			acceptText = false;
							//			if (playerInput.toAnsiString() == rememberFullBubbles.getDataSpriteVector()[player.getSpriteContactIndex()].getStringValue()) {
							//				//yes a match, increment a value?
							//				playerInput.clear();
							//				rememberEmptyBubbles.updateIndividualTexture(player.getSpriteContactIndex(), "okBubbleSprite.png");
							//				rememberEmptyBubbles.setSpriteToComplete(player.getSpriteContactIndex());
							//				std::cout << "This should print once... \n";
							//			} else {//no
							//			}
							//		}
							//	}
							//	
							//} else {//no check if in contact with any sprites in vector
							//	player.setSpriteContactIndex(-1);
							//	acceptText = false;
							//	for (int i = 0; i < rememberEmptyBubbles.getDataSpriteVector().size(); i++) {//checking all sprites for contact
							//		if (player.hasCircleContact(rememberEmptyBubbles.getDataSpriteVector()[i].getSprite())) {
							//			//yes, set the sprite contact index
							//			player.handleSpriteContactIndex(rememberEmptyBubbles, i);
							//		} else {//no set contact index to -1
							//			player.setSpriteContactIndex(-1);
							//		}
							//	}
							//}
							

							if (rememberEmptyBubbles.getVectorComplete()) {
								std::cout << "Minigame complete! ";
								//update minigame texture to complete
								// block clicking on completed minigame
								//return to minigame screen
							}

							//if (player.getSpriteContactIndex() < 0) {//emptyBubbles 
							//	acceptText = false;
							//	for (int i = 0; i < rememberEmptyBubbles.getDataSpriteVector().size(); i++) {//checking all sprites for contact
							//		if (player.hasCircleContact(rememberEmptyBubbles.getDataSpriteVector()[i].getSprite())){
							//			player.handleSpriteContactIndex(rememberEmptyBubbles, i);
							//		}
							//	}
							//} else if (!rememberFullBubbles.getDataSpriteVector()[player.getSpriteContactIndex()].getIsComplete()){//checking if the sprite is complete
							//	//checking if still in contact with its one sprite
							//	if (player.hasCircleContact(rememberEmptyBubbles.getDataSpriteVector()[player.getSpriteContactIndex()].getSprite())) {
							//		acceptText = true;
							//		string letter = rememberFullBubbles.getLetter(0, player.getSpriteContactIndex());
							//		bannerText.setStringAndCenterOrigin("Enter " + letter, 0, 0);
							//		bannerText.setCharSize(23);
							//		window.draw(bannerSprite.getSprite());
							//		window.draw(bannerText.getText());
							//		window.draw(playerText.getText());
							//	}
							//	//checking if any more characters can be entered
							//	if (playerInput.getSize() > rememberFullBubbles.getDataSpriteVector()[player.getSpriteContactIndex()].getStringValue().size() - 1) {
							//		playerText.setIsFull(true);
							//		//checking if the strings match
							//		if (playerInput.toAnsiString() == rememberFullBubbles.getDataSpriteVector()[player.getSpriteContactIndex()].getStringValue()) {
							//			rememberEmptyBubbles.updateIndividualTexture(player.getSpriteContactIndex(),"okBubbleSprite.png");
							//			rememberEmptyBubbles.setSpriteToComplete(player.getSpriteContactIndex());
							//			std::cout << "THis should prtint once \n";
							//			std::cout << player.getSpriteContactIndex();
							//		}
							//	}
							//} else {
							//	player.setSpriteContactIndex(-1);
							//}
							
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
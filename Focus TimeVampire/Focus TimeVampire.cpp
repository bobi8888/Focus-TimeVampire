#include "utils.h"
#include "window.h"
#include "gameText.h"
#include "mouse.h"
#include "gameSprite.h"
#include "gameScreen.h"
#include "gameTimer.h"
#include "randomizedData.h"
#include "assembleUtils.h"

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
	GameText timerText(generalFont, 20, "", 20, window);
	timerText.getText().setPosition(sf::Vector2f(5,30));
	GameText bannerText(generalFont, 30,"",0, window);
	bannerText.getText().setFillColor(sf::Color::Black);
	GameText playerText(generalFont, 30, "", 400, window);
	playerText.getText().setFillColor(sf::Color::White);	
	GameText tipText(generalFont, 25, "Enter the missing values!", 55, window);
	playerText.getText().setFillColor(sf::Color::White);

	//GAME SPRITES
	GameSprite startButton("startSprite.png", 0.5, 0.5);
	startButton.setSpritePosition(getCenterOfWindow(window));
	GameSprite pauseButton("pauseSprite.png", 0.25, 0.25);
	pauseButton.setSpritePosition(sf::Vector2f(window.getSize().x - 35, 40));
	GameSprite resumeButton("resumeSprite.png", 0.5, 0.5);
	resumeButton.setSpritePosition(getCenterOfWindow(window));	
	GameSprite solutionButton("solutionSprite.png", 0.3, 0.3);
	solutionButton.setSpritePosition(sf::Vector2f(window.getSize().x/2, window.getSize().y - 50));
	GameSprite bannerSprite("bannerSprite.png", 1, 1);
	bannerSprite.setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y - 50));
	bannerText.getText().setPosition(sf::Vector2f(bannerSprite.getSprite().getPosition().x, bannerSprite.getSprite().getPosition().y - 20));
	GameSprite x_outButton("x_outSprite.png", 0.25, 0.25);
	x_outButton.setPosition(sf::Vector2f(bannerSprite.getSprite().getPosition().x + bannerSprite.getSprite().getGlobalBounds().width/2 - 15
	, bannerSprite.getSprite().getPosition().y - bannerSprite.getSprite().getGlobalBounds().height / 2 + 30));	
	GameSprite backButton("backSprite.png", 0.18, 0.18);
	backButton.setPosition(sf::Vector2f(window.getSize().x - 55, window.getSize().y - 30));
	GameSprite pcbSolvedSprite("pcbSolvedSprite.png", 0.75, 0.75);
	pcbSolvedSprite.setPosition(getCenterOfWindow(window));
		 
	//TRANSFORMABLE SPRITES
	PlayerSprite player("playerSprite.png", 0.4, 0.4);
	player.setSpritePosition(getCenterOfWindow(window));
	player.setMovementSpeed(4);
	player.setRadius(player.getSprite().getGlobalBounds().height/2);

	//DATA SPRITES
	DataSprite minigameSprite("minigameSprite.png", 0.3, 0.3);
	DataSprite fullBubble("fullBubbleSprite.png", 1, 1);
	DataSprite emptyBubble("emptyBubbleSprite.png", 1, 1);
	DataSprite countingSprite("countingSprite.png", 0.5, 0.5);
	
	//SPRITE VECTORS	
	DataSpriteVector minigameSprites(9, minigameSprite);
	minigameSprites.setPositions(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), 3, 3, 1, 1);
	int bubbleQTY = 3;
	DataSpriteVector rememberFullBubbles(bubbleQTY,fullBubble);
	rememberFullBubbles.setPositions(sf::Vector2f(80, 250), bubbleQTY, 1, 25, 0);

	DataSpriteVector rememberEmptyBubbles(bubbleQTY, emptyBubble);
	rememberEmptyBubbles.setPositions(sf::Vector2f(420, 250), bubbleQTY, 1, 25, 0);
	rememberFullBubbles.setLetters();
	rememberFullBubbles.setLongValues();
	rememberFullBubbles.setStringValues(stream);
	rememberFullBubbles.setFullDataStrings(out);

	int countingQTY = 13;
	DataSpriteVector countingSprites(countingQTY, countingSprite);
	countingSprites.setPositions(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), 1, countingQTY, 0, 4);



	//MAIN GAME SCREENS
	GameScreen startScreen("FOCUS! Time Vampire", generalFont, 25, 25);
	startScreen.addSprite(startButton.getSprite());
	GameScreen gameScreen("FOCUS! Time Vampire", generalFont, 25, 25);
	GameScreen resumeScreen("FOCUS! Time Vampire", generalFont, 25, 25);
	resumeScreen.addSprite(resumeButton.getSprite());

	//MINIGAMES
	GameScreen remember("REMEMBER!", generalFont, 25, 25);
	bannerText.setTextString("Enter #");
	bannerText.centerTextOriginOnSprite(bannerSprite.getSprite(),0,0);

	GameScreen count("COUNT!", generalFont, 25, 25);
	stream << countingQTY;
	string countingString = stream.str();

	//Assemble
	GameScreen assembleGameScreen("ASSEMBLE!", generalFont, 25, 25);
	assembleGameScreen.addSprite(solutionButton.getSprite());
	GameScreen assembleSolution("ASSEMBLE Solution", generalFont, 25, 25);
	assembleSolution.addSprite(pcbSolvedSprite.getSprite());

	for (int i = 0; i < 9; i++)
		assembleDataSpriteVector.addSprite(assemblePartsSpriteVector[i], 1);

	assembleDataSpriteVector.setPositions(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - 10), 3, 3, 90, 120);

	//Discuss
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

	assembleGoal.setOrigin(sf::Vector2f(assembleGoal.getGlobalBounds().width / 2, assembleGoal.getGlobalBounds().height / 2));
	for (int i = 0; i < assembleGoalPositions.size(); i++) {
		assembleGoal.setPosition(assembleGoalPositions[i]);
		assemblePartsGoals.push_back(assembleGoal);
	}

	//GAME LOOP: mainScreenENUM
	sf::Event event;
	while (window.isOpen()) {
		window.display();
		window.clear();
		translatedMousePosition = setMousePosition(window);

		while (window.pollEvent(event)) {//this includes the closed window event & entering text
			if (event.type == sf::Event::Closed)
				window.close();
		
			switch (event.key.code) {
				case sf::Keyboard::Delete://66
				if(!deleteKeyWorkaround){
					playerText.deleteLastChar();
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
					playerText.setTextString("");
					playerText.setIsFull(false);
					break;

					case 8://BACKSPACE
					playerText.deleteLastChar();
					playerText.setIsFull(false);
					break;					
				}			
			}

			if (acceptText) {
				if(!playerText.getIsFull()) {
					if (event.text.unicode <= 57 && event.text.unicode >= 48) {
						playerText.appendTextString(event.text.unicode);
					}
				} else {playerText.setTextString("");}
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
				timerText.getText().setString(gameTimer.getString(out));
				gameTimer = gameTimer.manageGameTimer(timerClock, gameTimer);	
					
				//create function for the mouse click event?
				if (event.type == sf::Event::EventType::MouseButtonPressed) {
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && pauseButton.getSprite().getGlobalBounds().contains(translatedMousePosition)) {
						gameTimer = gameTimer.pause(timerClock, gameTimer);
						timerText.getText().setString(("::Paused::"));
						mainScreenENUM = resumeMAIN;
					}
				}		

				if(gameScreenENUM != mainENUM){//BACK BUTTON
					window.draw(backButton.getSprite());
					if (event.type == sf::Event::EventType::MouseButtonPressed) {
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && backButton.getSprite().getGlobalBounds().contains(translatedMousePosition)) {
							gameScreenENUM = mainENUM;
							playerText.getText().setString("");
							acceptText = false;
						}
					}
				}

				switch(gameScreenENUM){
					case mainENUM:
					gameScreen.drawScreen(window, timerText.getText());
					minigameSprites.drawSprites(window, -1);
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
					case rememberENUM://REMEMBER swapping can be used to randomize vectors to increase difficulty
					player.setMovement(window);
					window.draw(tipText.getText());
					window.draw(player.getSprite()); 
					rememberFullBubbles.drawSprites(window, -1);
					rememberEmptyBubbles.drawSprites(window, -1);
					remember.drawScreen(window, timerText.getText());

					for (int i = 0; i < rememberFullBubbles.getDataSpriteVector().size(); i++) {//contacting full sprites
						if (player.hasCircleContact(rememberFullBubbles.getDataSpriteVector()[i].getSprite()) == true){
							bannerText.setTextString(rememberFullBubbles.getFullDataStrings(i));
							bannerText.centerTextOriginOnSprite(bannerSprite.getSprite(), 0, -5);
							window.draw(bannerSprite.getSprite());
							window.draw(bannerText.getText());
						}
					}		
							// need to set the positon of playerTExt
					player.handleSpriteContactIndex(rememberEmptyBubbles);
					if (player.getSpriteContactIndex() >= 0) {
						if (rememberEmptyBubbles.getSingleSprite(player.getSpriteContactIndex()).getIsComplete()) {//checking if contacted sprite is complete
						} else {//sprite incomplete, check if text can be entered			
							bannerText.setTextString("Enter " + rememberFullBubbles.getSingleSprite(player.getSpriteContactIndex()).getLetter());
							bannerText.centerTextOriginOnSprite(bannerSprite.getSprite(), 0, -20);
							playerText.setTextToMoney(out);
							playerText.centerTextOriginOnSprite(bannerSprite.getSprite(), 0, +5);
							window.draw(bannerSprite.getSprite());
							window.draw(bannerText.getText());
							window.draw(playerText.getText());
							if (playerText.getTextString().size() <= rememberFullBubbles.getSingleSprite(player.getSpriteContactIndex()).getStringValue().size() - 1) {
								acceptText = true;
							} else {//no check for a match
								acceptText = false;
								if (playerText.getTextString() == rememberFullBubbles.getSingleSprite(player.getSpriteContactIndex()).getStringValue()) {
									rememberEmptyBubbles.updateIndividualTexture(player.getSpriteContactIndex(), "okBubbleSprite.png");
									rememberEmptyBubbles.setSpriteToComplete(player.getSpriteContactIndex());
								} 
							}
						}
					} else {// no contact
						playerText.setTextString("");
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
						acceptText = true;
						count.drawScreen(window, timerText.getText());
						countingSprites.drawSprites(window, -1);							
						bannerText.setTextString("How Many?");
						bannerText.centerTextOriginOnSprite(bannerSprite.getSprite(), 0, -20);
						playerText.centerTextOriginOnSprite(bannerSprite.getSprite(), 0, +11);
						window.draw(bannerSprite.getSprite());
						window.draw(bannerText.getText());
						window.draw(playerText.getText());
						if (playerText.getTextString().size() < countingString.size()) {
							acceptText = true;
						} else {acceptText = false;}

						if (playerText.getText().getString() == countingString) {//success
							minigameSprites.updateIndividualTexture(countENUM, "completedMinigameSprite.png");
							minigameSprites.setSpriteToComplete(countENUM);
							gameScreenENUM = mainENUM;
						}
					break;
					case assembleENUM://ASSEMBLE dificulty scale should expidite timer and flip pcbSprite
						//should be able to click and hold and move mouse within button to see solution

						if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && solutionButton.getSprite().getGlobalBounds().contains(translatedMousePosition)) {
							if (event.type == sf::Event::EventType::MouseButtonPressed) {
								assembleScreen = 2;
							} else {assembleScreen = 1;}
						} else {assembleScreen = 1;}

						switch (assembleScreen) {
							case 1:
								assembleGameScreen.drawScreen(window, timerText.getText());
								for (int i = 0; i < assemblePartsSpriteVector.size(); i++) {
									if (i != 4) {//checks if sprites can move besides pcb
										assembleDataSpriteVector.setCanMove(i, event, translatedMousePosition);

										// when mouse enters the goal, it moves the sprite to 0,0?
										//consider removing the i != 4 workaround
										//while the part is moving, check if it has collided with the goal, 
										// if so, setCanMove to false

										if (assemblePartsGoals[i].getGlobalBounds().contains(translatedMousePosition)) {
											assembleDataSpriteVector.setSpritePosition(i, assemblePartsGoals[i].getOrigin());
										}
									}
									if (assembleDataSpriteVector.getSingleSprite(i).getCanMove()) {
										assembleDataSpriteVector.setSpritePosition(i, translatedMousePosition);
									}
								}
								assembleDataSpriteVector.drawSprites(window, 4);
								for (int i = 0; i < assembleGoalPositions.size(); i++) {
									window.draw(assemblePartsGoals[i]);
								}
								window.draw(assembleGoal);
							break;
							case 2:
								assembleSolution.drawScreen(window, timerText.getText());
							break;
						}

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
				timerText.getText().setString("Time Up!");
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
#include "utils.h"
#include "window.h"
#include "gameText.h"
#include "mouse.h"
#include "gameSprite.h"
#include "gameScreen.h"
#include "gameTimer.h"
#include "randomizedData.h"
#include "assembleUtils.h"
#include "discussUtils.h"
#include "gameScreen.h"
#include "ignoreUtils.h"


//ISSUES
//reset random numbers each playthrough for Remember
//add reset button
//add X_out button
//changing window size and player sprite going past the window
//sprite sizes should be relative the the window size at initialization

//					gameTimer = gameTimer.pause(gameTimerClock, gameTimer); so many game timers?


//5/4/2023 21232 bytes in stack
//5/10/23 21664 bytes in stack
int main() {	
	//WINDOW
	antialiasing.antialiasingLevel = 8;
	window.setVerticalSyncEnabled(true);
	window.setPosition(sf::Vector2i(1400, 400));
	window.setKeyRepeatEnabled(false);

	//TIME
	GameTimer gameTimer(100);
	sf::Clock gameTimerClock;

	GameTimer ignoreTimer(5);
	sf::Clock ignoreTimerClock;

	//STREAM
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
	GameText ignorePromptText(generalFont, 30, "",20, window);
	ignorePromptText.setTextPosition(sf::Vector2f(50, 125));

	//GAME SPRITES
	GameSprite startButton("startSprite.png", 0.5, 0.5);
	startButton.setPosition(getCenterOfWindow(window));	
	GameSprite questionButton("questionButton.png", 0.4, 0.4);
	questionButton.setPosition(sf::Vector2f(window.getSize().x/2, 300));	
	GameSprite gobackButton("gobackButton.png", 0.35, 0.35);
	gobackButton.setPosition(sf::Vector2f(window.getSize().x / 4, window.getSize().y - 100));	
	GameSprite skipButton("skipButton.png", 0.35, 0.35);
	skipButton.setPosition(sf::Vector2f(window.getSize().x / 4 * 3 , window.getSize().y - 100));
	GameSprite pauseButton("pauseSprite.png", 0.25, 0.25);
	pauseButton.setPosition(sf::Vector2f(window.getSize().x - 35, 40));
	GameSprite resumeButton("resumeSprite.png", 0.5, 0.5);
	resumeButton.setPosition(getCenterOfWindow(window));	
	GameSprite solutionButton("solutionSprite.png", 0.3, 0.3);
	solutionButton.setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y - 50));
	GameSprite bannerSprite("bannerSprite.png", 1, 1);
	bannerSprite.setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y - 50));
	bannerText.getText().setPosition(sf::Vector2f(bannerSprite.getSprite().getPosition().x, bannerSprite.getSprite().getPosition().y - 20));
	GameSprite x_outButton("x_outSprite.png", 0.25, 0.25);
	x_outButton.setPosition(sf::Vector2f(bannerSprite.getSprite().getPosition().x + bannerSprite.getSprite().getGlobalBounds().width/2 - 15
	, bannerSprite.getSprite().getPosition().y - bannerSprite.getSprite().getGlobalBounds().height / 2 + 30));	
	GameSprite backButton("backSprite.png", 0.18, 0.18);
	backButton.setPosition(sf::Vector2f(window.getSize().x - 55, window.getSize().y - 30));
		 
	//TRANSFORMABLE SPRITES
	PlayerSprite player("playerSprite.png", 0.4, 0.4);
	player.setPosition(getCenterOfWindow(window));
	player.setMovementSpeed(15);
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
	GameScreen startScreen("FOCUS! Time Vampire", generalFont, 25, 25, window);
	startScreen.addSprite(startButton.getSprite());
	GameScreen gameScreen("FOCUS! Time Vampire", generalFont, 25, 25, window);
	GameScreen resumeScreen("FOCUS! Time Vampire", generalFont, 25, 25, window);
	resumeScreen.addSprite(resumeButton.getSprite());

	//MINIGAMES
	//REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER
	GameScreen remember("REMEMBER!", generalFont, 25, 25, window);
	bannerText.setTextString("Enter #");
	bannerText.centerTextOriginOnSprite(bannerSprite.getSprite(),0,0);
	//COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT 
	GameScreen count("COUNT!", generalFont, 25, 25, window);
	stream << countingQTY;
	string countingString = stream.str();
	//ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE 
	GameScreen assembleGameScreen("ASSEMBLE!", generalFont, 25, 25, window);
	assembleGameScreen.addSprite(solutionButton.getSprite());
	GameScreen assembleSolution("ASSEMBLE Solution", generalFont, 25, 25, window);
	pcbSolvedSprite.setPosition(getCenterOfWindow(window));
	assembleSolution.addSprite(pcbSolvedSprite.getSprite());
	for (int i = 0; i < 9; i++) {assembleDataSpriteVector.addSprite(assemblePartsSpriteVector[i], 1);}
	assembleDataSpriteVector.setPositions(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - 10), 3, 3, 90, 120);
	assembleDataSpriteVector.setSpriteToComplete(4);	
	assembleGoal.setOrigin(sf::Vector2f(assembleGoal.getGlobalBounds().width / 2, assembleGoal.getGlobalBounds().height / 2));
	for (int i = 0; i < assembleGoalPositions.size(); i++) {
		assembleGoal.setPosition(assembleGoalPositions[i]);
		assemblePartsGoals.push_back(assembleGoal);
	}
	//DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS 
	GameScreen discuss("DISCUSS!", generalFont, 25, 25, window);
	DiscussText npcText(generalFont, 25, question1, questionY, window);
	npcText.setCharWidthsVector(question1);
	for (int i = 0; i < npcText.getTextString().size(); i++) {
		sf::RectangleShape textBlocker(sf::Vector2f(npcText.getCharWidthsVector()[i], npcText.getText().getCharacterSize() + 10));
		textBlocker.setOrigin(textBlocker.getSize().x/2, textBlocker.getSize().y/2);
		textBlocker.setPosition(sf::Vector2f(npcText.getText().findCharacterPos(i).x + textBlocker.getSize().x / 2, npcText.getText().findCharacterPos(i).y + textBlocker.getSize().y / 2));
		textBlocker.setFillColor(sf::Color::White);
		textBlocker.setOutlineColor(sf::Color::Cyan);
		textBlocker.setOutlineThickness(3);
		textBlockersVector.push_back(textBlocker);
	}
	GameSprite discussBannerSprite("bannerSprite.png", 1.3, 1.1);
	discussBannerSprite.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y - 150));

	GameText leftAnswer(generalFont, 32, response1A, 200, window);
	leftAnswer.getText().setFillColor(sf::Color::Black);
	leftAnswer.setTextPosition(sf::Vector2f(discussBannerSprite.getSprite().getPosition().x - discussBannerSprite.getSprite().getGlobalBounds().width * 0.25
		, discussBannerSprite.getSprite().getPosition().y));
	GameText rightAnswer(generalFont, 32, response1B, 200, window);

	rightAnswer.getText().setFillColor(sf::Color::Black);
	rightAnswer.setTextPosition(sf::Vector2f(discussBannerSprite.getSprite().getPosition().x + discussBannerSprite.getSprite().getGlobalBounds().width * 0.25
		, discussBannerSprite.getSprite().getPosition().y));
	//IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE 
	GameScreen ignorePromptScreen("IGNORE!", generalFont, 25, 25, window);
	ignorePromptScreen.addSprite(questionButton.getSprite());
	GameScreen ignoreQuestionScreen("IGNORE!", generalFont, 25, 25, window);
	ignoreQuestionScreen.addSprite(gobackButton.getSprite());
	ignoreQuestionScreen.addSprite(skipButton.getSprite());

	sf::Music dullBed;
	dullBed.setLoop(true);
	if (!dullBed.openFromFile("dullBed.wav")) std::cout << "Error loading dullBed.wav \n";	
	dullBed.setVolume(dullBedVolume);
	sf::Music convo;
	convo.setLoop(true);
	if (!convo.openFromFile("convo.wav")) std::cout << "Error loading convo.wav \n";
	convo.setVolume(convoVolume);
	sf::SoundBuffer ignoreSoundBuffer;
	if (!ignoreSoundBuffer.loadFromFile("beep.wav")) std::cout << "Error loading beep.wav \n";
	sf::Sound ignoreBeep;
	ignoreBeep.setBuffer(ignoreSoundBuffer);
	ignoreBeep.setVolume(beepVolume);

	beepCountdown = gameTimer.getTimeRemaining() - randomInt(5, 1);

	sf::Text tempText("", generalFont);
	int randomIgnore_Int = randomInt(2, 15);
	int ignoreKey_Int = randomIgnore_Int + 5;
	ignoreKeys[0] = std::to_string(ignoreKey_Int);
	string ignoreKey_String = std::to_string(ignoreKey_Int);
	string randomInt_String = std::to_string(randomIgnore_Int);

	ignorePromptText = loadPrompt(randomInt_String, tempText, ignorePromptVectors[currentPrompt], ignorePromptText, window);
	// DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE
	GameScreen drive("DRIVE!", generalFont, 25, 25, window);
	// RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN 
	GameScreen retain("RETAIN!", generalFont, 25, 25, window);
	// PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH
	GameScreen push("PUSH!", generalFont, 25, 25, window);
	// BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS
	GameScreen bonus("BONUS!", generalFont, 25, 25, window);

	bool deleteKeyWorkaround = false;//both needed for delete workaround
	bool acceptText = false;

	enum mainScreens { startMAIN, gameMAIN, resumeMAIN };
	enum gameScreens { rememberENUM, countENUM, assembleENUM, discussENUM, ignoreENUM, driveENUM, retainENUM, pushENUM, bonusENUM, mainENUM };
	mainScreens mainScreensENUM = startMAIN;
	gameScreens gameScreensENUM = mainENUM;

	//GAME LOOP: mainScreensENUM
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
				}else
					deleteKeyWorkaround = false;
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
					if (event.text.unicode < 58 && event.text.unicode >= 48 && event.type != sf::Event::MouseMoved)
						playerText.appendTextString(event.text.unicode);
				} else playerText.setTextString("");
			}		
		}

		switch (mainScreensENUM){
			case startMAIN://START SCREEN
			if (validSpriteClick(event, startButton.getSprite().getGlobalBounds(), translatedMousePosition) == true) {
				gameTimerClock.restart();
				mainScreensENUM = gameMAIN;
				event.type = sf::Event::MouseButtonReleased;
			} else startScreen.drawScreen(window, timerText.getText());
			break;	 

			case gameMAIN://GAME SCREEN
			window.draw(pauseButton.getSprite());
			if (gameTimer.getTimeRemaining() > 0) {//game timer
				timerText.getText().setString(gameTimer.getString(out));
				gameTimer = gameTimer.manageGameTimer(gameTimerClock, gameTimer);
					
				if (validSpriteClick(event, pauseButton.getSprite().getGlobalBounds(), translatedMousePosition) == true) {
					gameTimer = gameTimer.pause(gameTimerClock, gameTimer);
					ignoreTimer = ignoreTimer.pause(ignoreTimerClock, ignoreTimer);
					timerText.getText().setString(("::Paused::"));
					mainScreensENUM = resumeMAIN;					
				}		

				if(gameScreensENUM != mainENUM){//BACK BUTTON
					if (validSpriteClick (event, backButton.getSprite().getGlobalBounds(), translatedMousePosition) == true) {
						gameScreensENUM = mainENUM;
						playerText.getText().setString("");
						acceptText = false;						
					} else window.draw(backButton.getSprite());					
				}

				switch(gameScreensENUM){
					case mainENUM:
					gameScreen.drawScreen(window, timerText.getText());
					minigameSprites.drawSprites(window, -1);
					dullBed.pause();
					convo.pause();
					//SWITCH FOR WHICH MINIGAME IS SELECTED

					if (event.type == sf::Event::EventType::MouseButtonPressed) {
						for (int i = 0; i < minigameSprites.getDataSpriteVector().size(); i++) {
							if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && minigameSprites.getSingleSprite(i).getSprite().getGlobalBounds().contains(translatedMousePosition)) {
								if (!minigameSprites.getSingleSprite(i).getIsComplete()) { gameScreensENUM = static_cast<gameScreens>(i); }

								event.type = sf::Event::EventType::MouseButtonReleased;
								
								if (gameScreensENUM == ignoreENUM) {//excecute once when switching to ignorePrompt
									dullBed.play();
									convo.play();
									ignoreTimerClock.restart();
									bannerSprite.setPosition(getCenterOfWindow(window));
									acceptText = true;
								}

								if (gameScreensENUM == driveENUM) {	player.setMovementSpeed(1);	}

								if (gameScreensENUM == rememberENUM) { player.setMovementSpeed(15);	}
							}
						}
					}
					break;
					case rememberENUM://REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER 
					//swapping can be used to randomize vectors to increase difficulty
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
							} else {
								acceptText = false;
								if (playerText.getTextString() == rememberFullBubbles.getSingleSprite(player.getSpriteContactIndex()).getStringValue()) {
									rememberEmptyBubbles.updateIndividualTexture(player.getSpriteContactIndex(), "okBubbleSprite.png");
									rememberEmptyBubbles.setSpriteToComplete(player.getSpriteContactIndex());
								} 
							}
						}
					} else {
						playerText.setTextString("");
						acceptText = false;
					}
					//win condition		
					if (!rememberEmptyBubbles.getVectorComplete())
						rememberEmptyBubbles.checkForCompletion();
					else {
						playerText.setTextString("");
						minigameSprites.updateIndividualTexture(rememberENUM, "completedMinigameSprite.png");
						minigameSprites.setSpriteToComplete(rememberENUM);
						gameScreensENUM = mainENUM;	
					}							
					break;
					case countENUM://COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT 
					//acceptText = true;
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
					} else acceptText = false;

					if (playerText.getText().getString() == countingString) {
						playerText.setTextString("");
						minigameSprites.updateIndividualTexture(countENUM, "completedMinigameSprite.png");
						minigameSprites.setSpriteToComplete(countENUM);
						gameScreensENUM = mainENUM;
					}
					break;
					case assembleENUM://ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE 
					if (validSpriteClick(event, solutionButton.getSprite().getGlobalBounds(), translatedMousePosition) == true)
						validMouseClick = true;
					
					if (!solutionButton.getSprite().getGlobalBounds().contains(translatedMousePosition) || !sf::Mouse::isButtonPressed(sf::Mouse::Left))
						validMouseClick = false;
					if (validMouseClick) assembleScreen = 2;
					else assembleScreen = 1;

					switch (assembleScreen) {
						case 1:
						assembleGameScreen.drawScreen(window, timerText.getText());
						for (int i = 0; i < assemblePartsSpriteVector.size(); i++) {
							if (i != 4 && !assembleDataSpriteVector.getSingleSprite(i).getIsComplete()) {
								assembleDataSpriteVector.setCanMove(i, event, translatedMousePosition);
								if (assembleDataSpriteVector.getSingleSprite(i).getCanMove()) {
									assembleDataSpriteVector.setSpritePosition(i, translatedMousePosition);
									mouseContactIndex = i;
									if (assemblePartsGoals[i].getGlobalBounds().contains(translatedMousePosition)) {
										assembleDataSpriteVector.getSingleSprite(i).setToComplete();
										assembleDataSpriteVector.setSpritePosition(i,assembleGoalPositions[i]);
										assembleDataSpriteVector.setSpriteToComplete(i);
									}
								} else mouseContactIndex = -1;																				
							}
						}
						if (!assembleDataSpriteVector.getVectorComplete())
							assembleDataSpriteVector.checkForCompletion();
						else {
							minigameSprites.updateIndividualTexture(assembleENUM, "completedMinigameSprite.png");
							minigameSprites.setSpriteToComplete(assembleENUM);
							gameScreensENUM = mainENUM;
						}
						assembleDataSpriteVector.drawSprites(window, 4);
						break;
						case 2:
						assembleSolution.drawScreen(window, timerText.getText());
						break;
					}

					break;
					case discussENUM://DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS 

					//check that ignore timer is stoping, pausing, restarting etc

						if (discussTime == 0) discussTime = gameTimer.getTimeRemaining();
						npcText.charToShowIncrementor(discussTimePtr,gameTimer.getTimeRemaining(), discussSpeedPtr, textBlockersVector);
						if (gameTimer.handleMinigamePace(discussTime, *discussSpeedPtr)) {
							if (charToShow <= textBlockersVector.size()) discussTime = gameTimer.getTimeRemaining();
							else discussTime = 0;

							blockerFill = npcText.handleColor(blockerFill, redInc, blueInc, greenInc);
						}
						for (int i = 0; i < textBlockersVector.size(); i++){
							textBlockersVector[i].setOutlineColor(blockerFill);
						}

						discuss.drawScreen(window, timerText.getText());
						window.draw(npcText.getText());
						npcText.drawTextBlockers(textBlockersVector, window);
						window.draw(discussBannerSprite.getSprite());
						window.draw(leftAnswer.getText());
						window.draw(rightAnswer.getText());

						if (validSpriteClick(event, leftAnswer.getText().getGlobalBounds(), translatedMousePosition) == true 
							|| validSpriteClick(event, rightAnswer.getText().getGlobalBounds(), translatedMousePosition) == true) {
							questionNumber++;
							event.type = sf::Event::EventType::MouseButtonReleased;
							switch (questionNumber) {
								case 2:
									npcText.updateNextQuestion(question2, window, questionY);

									leftAnswer.setString_Origin_Position(response2A, sf::Vector2f(discussBannerSprite.getSprite().getPosition().x - discussBannerSprite.getSprite().getGlobalBounds().width * 0.25
										, discussBannerSprite.getSprite().getPosition().y));
									rightAnswer.setString_Origin_Position(response2B, sf::Vector2f(discussBannerSprite.getSprite().getPosition().x + discussBannerSprite.getSprite().getGlobalBounds().width * 0.25
										, discussBannerSprite.getSprite().getPosition().y));
									textBlockersVector = npcText.resetTextBlockers(textBlockersVector);
								break;
								case 3:
									npcText.updateNextQuestion(question3, window, questionY);
									leftAnswer.setString_Origin_Position(response3A, sf::Vector2f(discussBannerSprite.getSprite().getPosition().x - discussBannerSprite.getSprite().getGlobalBounds().width * 0.25
										, discussBannerSprite.getSprite().getPosition().y));
									rightAnswer.setString_Origin_Position(response3B, sf::Vector2f(discussBannerSprite.getSprite().getPosition().x + discussBannerSprite.getSprite().getGlobalBounds().width * 0.25
										, discussBannerSprite.getSprite().getPosition().y));
									textBlockersVector = npcText.resetTextBlockers(textBlockersVector);
								break;
								case 4:
									npcText.updateNextQuestion(question4, window, questionY);
									leftAnswer.setString_Origin_Position(response4A, sf::Vector2f(discussBannerSprite.getSprite().getPosition().x - discussBannerSprite.getSprite().getGlobalBounds().width * 0.25
										, discussBannerSprite.getSprite().getPosition().y));
									rightAnswer.setString_Origin_Position(response4B, sf::Vector2f(discussBannerSprite.getSprite().getPosition().x + discussBannerSprite.getSprite().getGlobalBounds().width * 0.25
										, discussBannerSprite.getSprite().getPosition().y));
									textBlockersVector = npcText.resetTextBlockers(textBlockersVector);
								break;
							}
						}
						
						if (questionNumber == 5) {
							minigameSprites.updateIndividualTexture(discussENUM, "completedMinigameSprite.png");
							minigameSprites.setSpriteToComplete(discussENUM);
							gameScreensENUM = mainENUM;
						}
					break;
					case ignoreENUM://IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE 
						if (beepCountdown > gameTimer.getTimeRemaining()) {
							ignoreBeep.play();
							beepCountdown = gameTimer.getTimeRemaining() - randomInt(1, 10);
						}

						//win condition and result
						if (currentPrompt == ignorePromptVectors.size() && currentQuestion >= ignoreQuestions.size()) {
							minigameSprites.updateIndividualTexture(ignoreENUM, "completedMinigameSprite.png");
							minigameSprites.setSpriteToComplete(ignoreENUM);
							gameScreensENUM = mainENUM;
							break;
						}

						switch (ignoreScreen) {
						case 1:
							//timer for the prompt screen
							if (ignoreTimer.getTimeRemaining() > 0.02) {
								tipText.setString_Origin_Position("Time Left: " + ignoreTimer.getString(out), sf::Vector2f(window.getSize().x / 2, 425));
								ignoreTimer = ignoreTimer.manageGameTimer(ignoreTimerClock, ignoreTimer);
							} else { 
								ignoreScreen = 2;
								tipText.setString_Origin_Position(ignoreQuestions[currentQuestion], sf::Vector2f(window.getSize().x / 2, 95));
							}

							if (validSpriteClick(event, questionButton.getSprite().getGlobalBounds(), translatedMousePosition) == true) {
								ignoreScreen = 2;
								tipText.setString_Origin_Position(ignoreQuestions[currentQuestion], sf::Vector2f(window.getSize().x / 2, 95));
								ignoreTimer = ignoreTimer.pause(ignoreTimerClock, ignoreTimer);
							}

							ignorePromptScreen.drawScreen(window, timerText.getText());
							window.draw(ignorePromptText.getText());
							window.draw(tipText.getText());
							event.type = sf::Event::EventType::MouseButtonReleased;
							break;
						case 2:		
							if (playerText.getTextString().size() <= ignoreKeys[currentKey].size() - 1) {
								acceptText = true;
							} else {
								acceptText = false;
							}
										
							if (validSpriteClick(event, skipButton.getSprite().getGlobalBounds(), translatedMousePosition) == true || playerText.getTextString() == ignoreKeys[currentKey]) {
								//for the last prompt,  should it progress even if the answer is wrong?
								ignoreScreen = 1;
								ignorePromptText.setTextString("");
								playerText.setTextString("");
								currentKey++;
								currentQuestion++;
								currentPrompt++;
								if (currentPrompt < ignorePromptVectors.size()) {
									ignorePromptText = loadPrompt("", tempText, ignorePromptVectors[currentPrompt], ignorePromptText, window);
								}
								ignoreTimer.resetTimer();
								ignoreTimerClock.restart();
							}

							if (validSpriteClick(event, gobackButton.getSprite().getGlobalBounds(), translatedMousePosition) == true && ignoreTimer.getTimeRemaining() > 0.02) {
								ignoreScreen = 1;
								ignoreTimerClock.restart();								
							}

							ignoreQuestionScreen.drawScreen(window, timerText.getText());
							window.draw(bannerSprite.getSprite());							
							playerText.centerTextOriginOnSprite(bannerSprite.getSprite(), 0, +5);//where can this be put so it isn't always being called
							window.draw(playerText.getText());
							window.draw(tipText.getText());
							event.type = sf::Event::EventType::MouseButtonReleased;
							break;
						}
					break;
					case driveENUM://DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE DRIVE 
						player.setMovement(window);
						window.draw(player.getSprite());

						drive.drawScreen(window, timerText.getText());
					break;
					case retainENUM://RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN 
						retain.drawScreen(window, timerText.getText());
					break;
					case pushENUM://PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH 
						push.drawScreen(window, timerText.getText());
					break;
					case bonusENUM://BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS 
						bonus.drawScreen(window, timerText.getText());
					break;
				}
			}else{//TIME IS UP
				gameTimer = gameTimer.timeUp(gameTimer);
				timerText.getText().setString("Time Up!");
				startScreen.setAndCenterTitle("GAME OVER!");
				player.setPosition(getCenterOfWindow(window));
				mainScreensENUM = startMAIN;
				gameScreensENUM = mainENUM;
			}
			break;

			case resumeMAIN://RESUME			
			assert(gameTimer.getTimeRemaining() > 0);			
			if (validSpriteClick(event, resumeButton.getSprite().getGlobalBounds(), translatedMousePosition) == true) {
				gameTimerClock.restart();
				ignoreTimerClock.restart();
				mainScreensENUM = gameMAIN;					
			} else resumeScreen.drawScreen(window, timerText.getText());
			event.type = sf::Event::EventType::MouseButtonReleased;//this stops clicking through sprites
			break;
		}		
	}
}
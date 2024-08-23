#include "utils.h"
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
#include "retainUtils.h"
#include "wall.h"
#include "window.h"

//ISSUES
//reset random numbers each playthrough for Remember
//add reset button
//add X_out button
//changing window size and player sprite going past the window
//sprite sizes should be relative the the window size at initialization

//gameTimer = gameTimer.pause(gameTimerClock, gameTimer); so many game timers?
//USE MULTI THREADING FOR MULTIPLE TIMERS?

int main() {	
	//WINDOW
	antialiasing.antialiasingLevel = 8;
	window.setVerticalSyncEnabled(true);
	window.setPosition(sf::Vector2i(600, 300));
	window.setKeyRepeatEnabled(false);

	//TIME
	GameTimer* gameTimerPtr = new GameTimer(100);
	sf::Clock gameTimerClock;
	GameTimer* ignoreTimerPtr = new GameTimer(5);
	sf::Clock ignoreTimerClock;

	//STREAM
	std::ostringstream out;
	std::stringstream stream;
	//srand(time(NULL));

	//FONT & TEXT
	sf::Font generalFont;
	loadFont(generalFont);
	sf::Color white(sf::Color::White);
	sf::Color black(sf::Color::Black);
	sf::Vector2f centerOfScreen(window.getSize().x / 2, window.getSize().y / 2);
	sf::Vector2f miniGameTitlePosition(window.getSize().x / 2, 40);
	sf::Vector2f discussQuesitonPosition(window.getSize().x / 2, 200);
	sf::Vector2f timerPosition(5, 30);
	sf::Vector2f ignorePromptPosition(50, 125);
	//string string, sf::Font &font, int characterSize, sf::Color &color, sf::Vector2f position
	GameText* timerTextPtr = new GameText("",generalFont, 20, white, timerPosition);
	GameText* bannerTextPtr = new GameText("", generalFont, 30, black, miniGameTitlePosition);
	GameText* playerTextPtr = new GameText("", generalFont, 30, white, miniGameTitlePosition);
	GameText* tipTextPtr = new GameText("Enter the missing values!", generalFont, 25, white, miniGameTitlePosition);
	GameText* ignorePromptTextPtr = new GameText("", generalFont, 30, white, ignorePromptPosition);

	//GAME SPRITES
	GameSprite* startButtonPtr = new GameSprite("startSprite.png", 0.5, 0.5, centerOfScreen);
	GameSprite* questionButtonPtr = new GameSprite("questionButton.png", 0.4, 0.4, sf::Vector2f(window.getSize().x / 2, 300));
	GameSprite* gobackButtonPtr = new GameSprite("gobackButton.png", 0.35, 0.35, sf::Vector2f(window.getSize().x / 4, window.getSize().y - 100));
	GameSprite* skipButtonPtr = new GameSprite ("skipButton.png", 0.35, 0.35, sf::Vector2f(window.getSize().x / 4 * 3, window.getSize().y - 100));
	GameSprite* pauseButtonPtr = new GameSprite("pauseSprite.png", 0.25, 0.25, sf::Vector2f(window.getSize().x - 35, 40));
	GameSprite* resumeButtonPtr = new GameSprite("resumeSprite.png", 0.5, 0.5, centerOfScreen);
	GameSprite* solutionButtonPtr = new GameSprite("solutionSprite.png", 0.3, 0.3, sf::Vector2f(window.getSize().x / 2, window.getSize().y - 50));
	GameSprite* bannerSpritePtr = new GameSprite("bannerSprite.png", 1, 1, sf::Vector2f(window.getSize().x / 2, window.getSize().y - 50));
	bannerTextPtr->getText().setPosition(sf::Vector2f(bannerSpritePtr->getSprite().getPosition().x, bannerSpritePtr->getSprite().getPosition().y - 20));
	GameSprite* backButtonPtr = new GameSprite("backSprite.png", 0.18, 0.18, sf::Vector2f(window.getSize().x - 55, window.getSize().y - 30));

	//TRANSFORMABLE SPRITES
	Player* playerCirclePtr = new Player("playerSprite.png",1, 7, 0.2);
	playerCirclePtr->setPlayerPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y / 2));

	//DATA SPRITES
	DataSprite* minigameSpritePtr = new DataSprite("minigameSprite.png", 0.3, 0.3, partStart);
	DataSprite* fullBubblePtr = new DataSprite("fullBubbleSprite.png", 1, 1, partStart);
	DataSprite* emptyBubblePtr = new DataSprite("emptyBubbleSprite.png", 1, 1, partStart);
	DataSprite* countingSpritePtr = new DataSprite("countingSprite.png", 0.5, 0.5, partStart);
	DataSprite* dataAcceptSpritePtr = new DataSprite("acceptSprite.png", 0.3, 0.3, partStart);

	//SPRITE VECTORS	
	DataSpriteVector minigameDataSpriteVector(9,*minigameSpritePtr);
	minigameDataSpriteVector.setPositions(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), 3, 3, 1, 1);

	int bubbleQTY = 3;
	DataSpriteVector rememberFullBubbles(bubbleQTY,*fullBubblePtr);
	rememberFullBubbles.setPositions(sf::Vector2f(80, 250), bubbleQTY, 1, 25, 0);

	DataSpriteVector rememberEmptyBubbles(bubbleQTY, *emptyBubblePtr);
	rememberEmptyBubbles.setPositions(sf::Vector2f(420, 250), bubbleQTY, 1, 25, 0);
	rememberFullBubbles.setLetters();
	rememberFullBubbles.setLongValues();
	rememberFullBubbles.setStringValues(stream);
	rememberFullBubbles.setFullDataStrings(out);

	int countingQTY = 13;
	DataSpriteVector countingSprites(countingQTY, *countingSpritePtr);
	countingSprites.setPositions(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2), 1, countingQTY, 0, 4);

	//MAIN GAME SCREENS
	GameScreen* startScreenPtr = new GameScreen("FOCUS! Time Vampire", generalFont, 25, 25, window);
	startScreenPtr->addSprite(startButtonPtr ->getSprite());
	GameScreen* gameScreenPtr = new GameScreen("FOCUS! Time Vampire", generalFont, 25, 25, window);
	GameScreen* resumeScreenPtr = new GameScreen("FOCUS! Time Vampire", generalFont, 25, 25, window);
	resumeScreenPtr->addSprite(resumeButtonPtr->getSprite());

	//MINIGAMES
	//REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER
	GameScreen* rememberGameScreenPtr = new GameScreen("REMEMBER!", generalFont, 25, 25, window);
	bannerTextPtr->setTextString("Enter #");
	bannerTextPtr->centerTextOriginOnSprite(bannerSpritePtr->getSprite(),0,0);
	//COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT 
	GameScreen* countGameScreenPtr = new GameScreen("COUNT!", generalFont, 25, 25, window);
	stream << countingQTY;
	string countingString = stream.str();
	//ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE 
	GameScreen* assembleGameScreenPtr = new GameScreen("ASSEMBLE!", generalFont, 25, 25, window);
	assembleGameScreenPtr->addSprite(solutionButtonPtr->getSprite());
	GameScreen* assembleSolutionGameScreenPtr = new GameScreen("ASSEMBLE Solution", generalFont, 25, 25, window);
	pcbSolvedSprite.setPosition(centerOfScreen);
	assembleSolutionGameScreenPtr->addSprite(pcbSolvedSprite.getSprite());
	for (int i = 0; i < 9; i++) {assembleDataSpriteVector.addSprite(assemblePartsSpriteVector.at(i), 1); }
	assembleDataSpriteVector.setPositions(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - 10), 3, 3, 90, 120);
	assembleDataSpriteVector.setSpriteToComplete(4);
	assembleGoal.setOrigin(sf::Vector2f(assembleGoal.getGlobalBounds().width / 2, assembleGoal.getGlobalBounds().height / 2));
	for (int i = 0; i < assembleGoalPositions.size(); i++) {
		assembleGoal.setPosition(assembleGoalPositions[i]);
		assemblePartsGoals.push_back(assembleGoal);
	}
	//DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS 
	GameScreen* discussGameScreenPtr = new GameScreen("DISCUSS!", generalFont, 25, 25, window);
	DiscussText* npcTextPtr = new DiscussText(question1, generalFont, 25, white, discussQuesitonPosition);
	npcTextPtr->setCharWidthsVector(question1);
	for (int i = 0; i < npcTextPtr->getTextString().size(); i++) {
		sf::RectangleShape textBlocker(sf::Vector2f(npcTextPtr->getCharWidthsVector()[i], npcTextPtr->getText().getCharacterSize() + 10));
		textBlocker.setOrigin(textBlocker.getSize().x/2, textBlocker.getSize().y/2);
		textBlocker.setPosition(sf::Vector2f(npcTextPtr->getText().findCharacterPos(i).x + textBlocker.getSize().x / 2, npcTextPtr->getText().findCharacterPos(i).y + textBlocker.getSize().y / 2));
		textBlocker.setFillColor(sf::Color::White);
		textBlocker.setOutlineColor(sf::Color::Cyan);
		textBlocker.setOutlineThickness(3);
		textBlockersVector.push_back(textBlocker);
	}
	GameSprite* discussBannerSpritePtr = new GameSprite("bannerSprite.png", 1.3, 1.1, partStart);
	discussBannerSpritePtr->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y - 150));
	discussLeftAnswerPosition = sf::Vector2f(discussBannerSpritePtr->getSprite().getPosition().x - discussBannerSpritePtr->getSprite().getGlobalBounds().width * 0.25, discussBannerSpritePtr->getSprite().getPosition().y);
	discussRightAnswerPosition = sf::Vector2f(discussBannerSpritePtr->getSprite().getPosition().x + discussBannerSpritePtr->getSprite().getGlobalBounds().width * 0.25, discussBannerSpritePtr->getSprite().getPosition().y);
	GameText* leftAnswerPtr = new GameText(response1A, generalFont, 32, black, discussLeftAnswerPosition);
	GameText* rightAnswerPtr = new GameText(response1B, generalFont, 32, black, discussRightAnswerPosition);
	rightAnswerPtr->getText().setFillColor(sf::Color::Black);

	//IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE 
	GameScreen* ignorePromptScreenPtr = new GameScreen("IGNORE!", generalFont, 25, 25, window);
	ignorePromptScreenPtr->addSprite(questionButtonPtr->getSprite());
	GameScreen* ignoreQuestionScreenPtr = new GameScreen("IGNORE!", generalFont, 25, 25, window);
	ignoreQuestionScreenPtr->addSprite(gobackButtonPtr->getSprite());
	ignoreQuestionScreenPtr->addSprite(skipButtonPtr->getSprite());

	sf::Music* dullBedPtr = new sf::Music;
	dullBedPtr->setLoop(true);
	if (!dullBedPtr->openFromFile("dullBed.wav")) std::cout << "Error loading dullBed.wav \n";
	dullBedPtr->setVolume(dullBedVolume);
	sf::Music* convoPtr = new sf::Music;
	convoPtr->setLoop(true);
	if (!convoPtr->openFromFile("convo.wav")) std::cout << "Error loading convo.wav \n";
	convoPtr->setVolume(convoVolume);
	sf::SoundBuffer ignoreSoundBuffer;
	if (!ignoreSoundBuffer.loadFromFile("beep.wav")) std::cout << "Error loading beep.wav \n";
	sf::Sound* ignoreBeepPtr = new sf::Sound;
	ignoreBeepPtr->setBuffer(ignoreSoundBuffer);
	ignoreBeepPtr->setVolume(beepVolume);

	beepCountdown = gameTimerPtr->getTimeRemaining() - randomInt(5, 1);

	sf::Text tempText("", generalFont);
	int randomIgnore_Int = randomInt(2, 15);
	int ignoreKey_Int = randomIgnore_Int + 5;
	ignoreKeys[0] = std::to_string(ignoreKey_Int);
	string ignoreKey_String = std::to_string(ignoreKey_Int);
	string randomInt_String = std::to_string(randomIgnore_Int);
	ignorePromptTextPtr = loadPrompt(randomInt_String, tempText, ignorePromptVectors[currentPrompt], ignorePromptTextPtr, window);

	//ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT 
	GameScreen* drivePtr = new GameScreen("ACCEPT!", generalFont, 25, 25, window);
	vector <Wall> AcceptWallsVector;
	//centerX, centerY, length(x), height(y), angle

	//Main Chute: Index 0 - 3
	Wall mainChuteLowerLeft(200, 370, 260, 10, 90, playerCirclePtr);
	AcceptWallsVector.push_back(mainChuteLowerLeft);
	Wall mainChuteUpperLeft(200, 40, 80, 10, 90, playerCirclePtr);
	AcceptWallsVector.push_back(mainChuteUpperLeft);
	Wall mainChutelowerRight(300, 470, 80, 10, 90, playerCirclePtr);
	AcceptWallsVector.push_back(mainChutelowerRight);
	Wall mainChuteUpperRight(300, 160, 310, 10, 90, playerCirclePtr);
	AcceptWallsVector.push_back(mainChuteUpperRight);
	//Right Chute: Index 4 - 5
	Wall rightChuteUpper(350, 290, 100, 10, 20, playerCirclePtr);
	AcceptWallsVector.push_back(rightChuteUpper);
	Wall rightChuteLower(400, 400, 200, 10, 20, playerCirclePtr);
	AcceptWallsVector.push_back(rightChuteLower);
	////Right Blocker: Index 6 - 7
	Wall rightBlockerVertical(440, 155, 30, 10, 90, playerCirclePtr);
	AcceptWallsVector.push_back(rightBlockerVertical);
	Wall rightBlockerHorizontal(480, 165, 60, 10, 0, playerCirclePtr);
	AcceptWallsVector.push_back(rightBlockerHorizontal);
	////Left Chute: Index 8 - 9
	Wall leftChuteUpper(157, 35, 120, 10, 135, playerCirclePtr);
	AcceptWallsVector.push_back(leftChuteUpper);
	Wall leftChuteLower(159, 205, 120, 10, 135, playerCirclePtr);
	AcceptWallsVector.push_back(leftChuteLower);
	////Left Blocker: Index 10 - 13 
	Wall leftBlockerRightAngle(100, 250, 50, 10, 120, playerCirclePtr);
	AcceptWallsVector.push_back(leftBlockerRightAngle);
	Wall leftBlockerLeftAngle(80, 250, 50, 10, 60, playerCirclePtr);
	AcceptWallsVector.push_back(leftBlockerLeftAngle);
	Wall leftBlockerRightVertical(70, 300, 70, 10, 90, playerCirclePtr);
	AcceptWallsVector.push_back(leftBlockerRightVertical);
	Wall leftBlockerLeftVertical(110, 300, 70, 10, 90, playerCirclePtr);
	AcceptWallsVector.push_back(leftBlockerLeftVertical);

	vector <GameSprite> acceptVector;
	//PUSHING: Index 0
	double pushingMass = 3500000;
	GameSprite* finalAcceptGoal = new GameSprite("acceptSprite.png", 0.2, 0.2, sf::Vector2f(250, 70));
	finalAcceptGoal->setMass(pushingMass * 2);//3 500 000 after right is collected
	acceptVector.push_back(*finalAcceptGoal);

	//PULLING
	double pullingMass = 700000;
	//Index 1
	GameSprite* leftAcceptGoal = new GameSprite("acceptSprite.png", 0.2, 0.2, sf::Vector2f(100, 450));
	leftAcceptGoal->setGravitationalPull(false);
	leftAcceptGoal ->setMass(pullingMass);//700 000
	acceptVector.push_back(*leftAcceptGoal);
	//Index 2
	GameSprite* rightAcceptGoal = new GameSprite("acceptSprite.png", 0.2, 0.2, sf::Vector2f(450, 110));
	rightAcceptGoal->setGravitationalPull(false);
	rightAcceptGoal->setMass(pullingMass);//700 000
	acceptVector.push_back(*rightAcceptGoal);

	// RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN 
	GameScreen* retainPtr = new GameScreen("RETAIN!", generalFont, 25, 25, window);
	GameText* fadeAlpha = new GameText("A long time ago...", generalFont, 32, white, miniGameTitlePosition);
	sf::Color nC(255, 75, 45,255);
	fadeAlpha->setColor(nC);

	//For_each needs to be of the same data type?
	std::for_each(retainStrings.begin(), retainStrings.end(), [](string x) {
		;});
	
	// PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH
	GameScreen* pushPtr  = new GameScreen("PUSH!", generalFont, 25, 25, window);
	// BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS
	GameScreen* bonusPtr = new GameScreen("BONUS!", generalFont, 25, 25, window);

	bool deleteKeyWorkaround = false;//both needed for delete workaround
	bool acceptTextInput = false;

	enum mainScreens { startMAIN, gameMAIN, resumeMAIN };
	enum gameScreens { rememberENUM, countENUM, assembleENUM, discussENUM, ignoreENUM, acceptENUM, retainENUM, pushENUM, bonusENUM, mainENUM };
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
					playerTextPtr->deleteLastChar();
					playerTextPtr->setIsFull(false);
					deleteKeyWorkaround = true;
				}else
					deleteKeyWorkaround = false;
				break;
			}
			if (event.type == sf::Event::TextEntered) {
				string outString;
				switch (event.text.unicode){
					case 27://ESCAPE
					playerTextPtr->setTextString("");
					playerTextPtr->setIsFull(false);
					break;
					case 8://BACKSPACE
					playerTextPtr->deleteLastChar();
					playerTextPtr->setIsFull(false);
					break;					
				}			
			}
			if (acceptTextInput) {//not sure where setIsFull(true) takes place...
				if(!playerTextPtr->getIsFull()) {
					if (event.text.unicode < 58 && event.text.unicode >= 48 && event.type != sf::Event::MouseMoved)
						playerTextPtr->appendTextString(event.text.unicode);
				} else playerTextPtr->setTextString("");
			}		
		}

		switch (mainScreensENUM){
			case startMAIN://START SCREEN
			if (validSpriteClick(event, startButtonPtr->getSprite().getGlobalBounds(), translatedMousePosition) == true) {
				gameTimerClock.restart();
				mainScreensENUM = gameMAIN;
				event.type = sf::Event::MouseButtonReleased;
			} else startScreenPtr->drawScreen(window, timerTextPtr->getText());
			break;	 

			case gameMAIN://GAME SCREEN
			window.draw(pauseButtonPtr->getSprite());
			if (gameTimerPtr->getTimeRemaining() > 0) {//game timer
				timerTextPtr->getText().setString(gameTimerPtr->getTimerString(out));
				gameTimerPtr = gameTimerPtr->manageGameTimer(gameTimerClock, gameTimerPtr);
				
				//PAUSE
				if (validSpriteClick(event, pauseButtonPtr->getSprite().getGlobalBounds(), translatedMousePosition) == true) {
					gameTimerPtr = gameTimerPtr->pause(gameTimerClock, gameTimerPtr);
					ignoreTimerPtr = ignoreTimerPtr->pause(ignoreTimerClock, ignoreTimerPtr);
					timerTextPtr->getText().setString(("::Paused::"));
					mainScreensENUM = resumeMAIN;					
				}		

				if(gameScreensENUM != mainENUM){//BACK BUTTON
					if (validSpriteClick (event, backButtonPtr->getSprite().getGlobalBounds(), translatedMousePosition) == true) {
						gameScreensENUM = mainENUM;
						playerTextPtr->getText().setString("");
						acceptTextInput = false;						
					} else window.draw(backButtonPtr->getSprite());
				}

				switch (gameScreensENUM) {
				case mainENUM:
					gameScreenPtr->drawScreen(window, timerTextPtr->getText());
					minigameDataSpriteVector.drawSprites(window, -1);
					dullBedPtr->pause();
					convoPtr->pause();
					//SWITCH FOR WHICH MINIGAME IS SELECTED

					if (event.type == sf::Event::EventType::MouseButtonPressed) {
						for (int i = 0; i < minigameDataSpriteVector.getDataSpriteVector().size(); i++) {
							if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && minigameDataSpriteVector.getSingleSprite(i).getSprite().getGlobalBounds().contains(translatedMousePosition)) {
								if (!minigameDataSpriteVector.getSingleSprite(i).getIsComplete()) gameScreensENUM = static_cast<gameScreens>(i);

								//REMEMBER
								if (gameScreensENUM == rememberENUM) { 
									//playerCirclePtr->setSpeed(5); 
									playerCirclePtr->setPlayerPosition(getCenterOfWindow(window));
								}
								//IGNORE 
								if (gameScreensENUM == ignoreENUM) {
									dullBedPtr->play();
									convoPtr->play();
									ignoreTimerClock.restart();
									bannerSpritePtr->setPosition(getCenterOfWindow(window));
									acceptTextInput = true;
								}
								//ACCEPT
								if (gameScreensENUM == acceptENUM) { 
									playerCirclePtr->setPlayerPosition(sf::Vector2f(250,500));
								}
								event.type = sf::Event::EventType::MouseButtonReleased;
							}
						}
					}
					break;
				case rememberENUM://REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER 
					//swapping can be used to randomize vectors to increase difficulty
					playerCirclePtr->handlePlayerMovementWithinScreen(window, false);
					window.draw(tipTextPtr->getText());
					window.draw(playerCirclePtr->getCircle());
					rememberFullBubbles.drawSprites(window, -1);
					rememberEmptyBubbles.drawSprites(window, -1);
					rememberGameScreenPtr->drawScreen(window, timerTextPtr->getText());

					for (int i = 0; i < rememberFullBubbles.getDataSpriteVector().size(); i++) {//contacting full sprites
						if (playerCirclePtr->hasSpriteCollision(rememberFullBubbles.getDataSpriteVector()[i].getSprite()) == true) {
							bannerTextPtr->setTextString(rememberFullBubbles.getFullDataStrings(i));
							bannerTextPtr->centerTextOriginOnSprite(bannerSpritePtr->getSprite(), 0, -5);
							window.draw(bannerSpritePtr->getSprite());
							window.draw(bannerTextPtr->getText());
						}
					}
					
					if (playerCirclePtr->getSpriteContactIndex() < 0) {
						for (int i = 0; i < rememberEmptyBubbles.getDataSpriteVector().size(); i++) {
							if (playerCirclePtr->hasSpriteCollision(rememberEmptyBubbles.getDataSpriteVector()[i].getSprite()) == true) {
								playerCirclePtr->setSpriteContactIndex(i);
								break;
							}
						}
					}
					else if (playerCirclePtr->hasSpriteCollision(rememberEmptyBubbles.getDataSpriteVector()[playerCirclePtr->getSpriteContactIndex()].getSprite()) == false) {
						playerCirclePtr->setSpriteContactIndex(-1);
						playerTextPtr->setTextString("");
						acceptTextInput = false;
						
					} else {	
						if (!rememberEmptyBubbles.getSingleSprite(playerCirclePtr->getSpriteContactIndex()).getIsComplete()) {
							bannerTextPtr->setTextString("Enter " + rememberFullBubbles.getSingleSprite(playerCirclePtr->getSpriteContactIndex()).getLetter());
							bannerTextPtr->centerTextOriginOnSprite(bannerSpritePtr->getSprite(), 0, -20);
							playerTextPtr->setTextToMoney(out);
							playerTextPtr->centerTextOriginOnSprite(bannerSpritePtr->getSprite(), 0, +5);
							window.draw(bannerSpritePtr->getSprite());
							window.draw(bannerTextPtr->getText());
							window.draw(playerTextPtr->getText());
							if (playerTextPtr->getTextString().size() <= rememberFullBubbles.getSingleSprite(playerCirclePtr->getSpriteContactIndex()).getStringValue().size() - 1) {
								acceptTextInput = true; 
							}
							else {
								acceptTextInput = false;
							}
						}
						if (playerTextPtr->getTextString() == rememberFullBubbles.getSingleSprite(playerCirclePtr->getSpriteContactIndex()).getStringValue()) {
							rememberEmptyBubbles.updateIndividualTexture(playerCirclePtr->getSpriteContactIndex(), "okBubbleSprite.png");
							rememberEmptyBubbles.setSpriteToComplete(playerCirclePtr->getSpriteContactIndex());
							rememberEmptyBubbles.checkForCompletion();
						} 
					}				
					//win condition		
					if (rememberEmptyBubbles.getVectorComplete()) {
						playerTextPtr->setTextString("");
						minigameDataSpriteVector.updateIndividualTexture(rememberENUM, "completedMinigameSprite.png");
						minigameDataSpriteVector.setSpriteToComplete(rememberENUM);
						gameScreensENUM = mainENUM;	
					}							
					break;
					case countENUM://COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT COUNT 
					//acceptTextInput = true;
					countGameScreenPtr->drawScreen(window, timerTextPtr->getText());
					countingSprites.drawSprites(window, -1);							
					bannerTextPtr->setTextString("How Many?");
					bannerTextPtr->centerTextOriginOnSprite(bannerSpritePtr->getSprite(), 0, -20);
					playerTextPtr->centerTextOriginOnSprite(bannerSpritePtr->getSprite(), 0, +11);
					window.draw(bannerSpritePtr->getSprite());
					window.draw(bannerTextPtr->getText());
					window.draw(playerTextPtr->getText());
					if (playerTextPtr->getTextString().size() < countingString.size()) {
						acceptTextInput = true;
					} else acceptTextInput = false;

					if (playerTextPtr->getText().getString() == countingString) {
						playerTextPtr->setTextString("");
						minigameDataSpriteVector.updateIndividualTexture(countENUM, "completedMinigameSprite.png");
						minigameDataSpriteVector.setSpriteToComplete(countENUM);
						gameScreensENUM = mainENUM;
					}
					break;
					case assembleENUM://ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE ASSEMBLE 
					if (validSpriteClick(event, solutionButtonPtr->getSprite().getGlobalBounds(), translatedMousePosition) == true)
						validMouseClick = true;
					
					if (!solutionButtonPtr->getSprite().getGlobalBounds().contains(translatedMousePosition) || !sf::Mouse::isButtonPressed(sf::Mouse::Left))
						validMouseClick = false;
					if (validMouseClick) assembleScreen = 2;
					else assembleScreen = 1;

					switch (assembleScreen) {
						case 1:
						assembleGameScreenPtr->drawScreen(window, timerTextPtr->getText());
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
							minigameDataSpriteVector.updateIndividualTexture(assembleENUM, "completedMinigameSprite.png");
							minigameDataSpriteVector.setSpriteToComplete(assembleENUM);
							gameScreensENUM = mainENUM;
						}
						assembleDataSpriteVector.drawSprites(window, 4);
						break;
						case 2:
						assembleSolutionGameScreenPtr->drawScreen(window, timerTextPtr->getText());
						break;
					}

					break;
					case discussENUM://DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS 

					//check that ignore timer is stoping, pausing, restarting etc

						if (discussTime == 0) discussTime = gameTimerPtr->getTimeRemaining();
						npcTextPtr->charToShowIncrementor(discussTimePtr,gameTimerPtr->getTimeRemaining(), discussSpeedPtr, textBlockersVector);
						if (gameTimerPtr->handleMinigamePace(discussTime, *discussSpeedPtr)) {
							if (charToShow <= textBlockersVector.size()) discussTime = gameTimerPtr->getTimeRemaining();
							else discussTime = 0;

							blockerFill = npcTextPtr->handleColor(blockerFill, redInc, blueInc, greenInc);
						}
						for (int i = 0; i < textBlockersVector.size(); i++){
							textBlockersVector[i].setOutlineColor(blockerFill);
						}

						discussGameScreenPtr->drawScreen(window, timerTextPtr->getText());
						window.draw(npcTextPtr->getText());
						npcTextPtr->drawTextBlockers(textBlockersVector, window);
						window.draw(discussBannerSpritePtr->getSprite());
						window.draw(leftAnswerPtr->getText());
						window.draw(rightAnswerPtr->getText());

						if (validSpriteClick(event, leftAnswerPtr->getText().getGlobalBounds(), translatedMousePosition) == true
							|| validSpriteClick(event, rightAnswerPtr->getText().getGlobalBounds(), translatedMousePosition) == true) {
							questionNumber++;
							event.type = sf::Event::EventType::MouseButtonReleased;
							switch (questionNumber) {
								case 2:
									npcTextPtr->updateNextQuestion(question2);
									leftAnswerPtr->setString_Origin_Position(response2A, sf::Vector2f(discussBannerSpritePtr->getSprite().getPosition().x - discussBannerSpritePtr->getSprite().getGlobalBounds().width * 0.25, discussBannerSpritePtr->getSprite().getPosition().y));
									rightAnswerPtr->setString_Origin_Position(response2B, sf::Vector2f(discussBannerSpritePtr->getSprite().getPosition().x + discussBannerSpritePtr->getSprite().getGlobalBounds().width * 0.25, discussBannerSpritePtr->getSprite().getPosition().y));
									textBlockersVector = npcTextPtr->resetTextBlockers(textBlockersVector);
								break;
								case 3:
									npcTextPtr->updateNextQuestion(question3);
									leftAnswerPtr->setString_Origin_Position(response3A, sf::Vector2f(discussBannerSpritePtr->getSprite().getPosition().x - discussBannerSpritePtr->getSprite().getGlobalBounds().width * 0.25
										, discussBannerSpritePtr->getSprite().getPosition().y));
									rightAnswerPtr->setString_Origin_Position(response3B, sf::Vector2f(discussBannerSpritePtr->getSprite().getPosition().x + discussBannerSpritePtr->getSprite().getGlobalBounds().width * 0.25
										, discussBannerSpritePtr->getSprite().getPosition().y));
									textBlockersVector = npcTextPtr->resetTextBlockers(textBlockersVector);
								break;
								case 4:
									npcTextPtr->updateNextQuestion(question4);
									leftAnswerPtr->setString_Origin_Position(response4A, sf::Vector2f(discussBannerSpritePtr->getSprite().getPosition().x - discussBannerSpritePtr->getSprite().getGlobalBounds().width * 0.25
										, discussBannerSpritePtr->getSprite().getPosition().y));
									rightAnswerPtr->setString_Origin_Position(response4B, sf::Vector2f(discussBannerSpritePtr->getSprite().getPosition().x + discussBannerSpritePtr->getSprite().getGlobalBounds().width * 0.25
										, discussBannerSpritePtr->getSprite().getPosition().y));
									textBlockersVector = npcTextPtr->resetTextBlockers(textBlockersVector);
								break;
							}
						}
						
						if (questionNumber == 5) {
							minigameDataSpriteVector.updateIndividualTexture(discussENUM, "completedMinigameSprite.png");
							minigameDataSpriteVector.setSpriteToComplete(discussENUM);
							gameScreensENUM = mainENUM;
						}
					break;
					case ignoreENUM://IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE IGNORE 
						//Sound not stopping when pressing pause
						if (beepCountdown > gameTimerPtr->getTimeRemaining()) {
							ignoreBeepPtr->play();
							beepCountdown = gameTimerPtr->getTimeRemaining() - randomInt(1, 10);
						}

						//win condition and result
						if (currentPrompt == ignorePromptVectors.size() && currentQuestion >= ignoreQuestions.size()) {
							minigameDataSpriteVector.updateIndividualTexture(ignoreENUM, "completedMinigameSprite.png");
							minigameDataSpriteVector.setSpriteToComplete(ignoreENUM);
							gameScreensENUM = mainENUM;
							break;
						}

						switch (ignoreScreen) {
						case 1:
							//timer for the prompt screen
							if (ignoreTimerPtr->getTimeRemaining() > 0.02) {
								tipTextPtr->setString_Origin_Position("Time Left: " + ignoreTimerPtr->getTimerString(out), sf::Vector2f(window.getSize().x / 2, 425));
								ignoreTimerPtr = ignoreTimerPtr->manageGameTimer(ignoreTimerClock, ignoreTimerPtr);
							} else { 
								ignoreScreen = 2;
								tipTextPtr->setString_Origin_Position(ignoreQuestions[currentQuestion], sf::Vector2f(window.getSize().x / 2, 95));
							}

							if (validSpriteClick(event, questionButtonPtr->getSprite().getGlobalBounds(), translatedMousePosition) == true) {
								ignoreScreen = 2;
								tipTextPtr->setString_Origin_Position(ignoreQuestions[currentQuestion], sf::Vector2f(window.getSize().x / 2, 95));
								ignoreTimerPtr = ignoreTimerPtr->pause(ignoreTimerClock, ignoreTimerPtr);
							}

							ignorePromptScreenPtr->drawScreen(window, timerTextPtr->getText());
							window.draw(ignorePromptTextPtr->getText());
							window.draw(tipTextPtr->getText());
							event.type = sf::Event::EventType::MouseButtonReleased;
							break;
						case 2:		
							if (playerTextPtr->getTextString().size() <= ignoreKeys[currentKey].size() - 1) {
								acceptTextInput = true;
							} else {
								acceptTextInput = false;
							}
										
							if (validSpriteClick(event, skipButtonPtr->getSprite().getGlobalBounds(), translatedMousePosition) == true || playerTextPtr->getTextString() == ignoreKeys[currentKey]) {
								//for the last prompt, should it progress even if the answer is wrong?
								ignoreScreen = 1;
								ignorePromptTextPtr->setTextString("");
								playerTextPtr->setTextString("");
								currentKey++;
								currentQuestion++;
								currentPrompt++;
								if (currentPrompt < ignorePromptVectors.size()) {
									ignorePromptTextPtr = loadPrompt("", tempText, ignorePromptVectors[currentPrompt], ignorePromptTextPtr, window);
								}
								ignoreTimerPtr->resetTimer();
								ignoreTimerClock.restart();
							}

							if (validSpriteClick(event, gobackButtonPtr->getSprite().getGlobalBounds(), translatedMousePosition) == true && ignoreTimerPtr->getTimeRemaining() > 0.02) {
								ignoreScreen = 1;
								ignoreTimerClock.restart();								
							}

							ignoreQuestionScreenPtr->drawScreen(window, timerTextPtr->getText());
							window.draw(bannerSpritePtr->getSprite());
							playerTextPtr->centerTextOriginOnSprite(bannerSpritePtr->getSprite(), 0, +5);//where can this be put so it isn't always being called
							window.draw(playerTextPtr->getText());
							window.draw(tipTextPtr->getText());
							event.type = sf::Event::EventType::MouseButtonReleased;
							break;
						}
					break;
					case acceptENUM://ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT
						for (int i = 0; i < AcceptWallsVector.size(); i++) {
							window.draw(AcceptWallsVector.at(i).getVertexArray());
							if (AcceptWallsVector.at(i).playerIsInBoundingBox(playerCirclePtr)) {
								AcceptWallsVector.at(i).setPlayerRelativeMinMaxXY(playerCirclePtr);
								playerCirclePtr->handleWallCollision(AcceptWallsVector.at(i).hasSATCollision(playerCirclePtr));
							}
						}
						playerCirclePtr->handlePlayerMovementWithinScreen(window, false);
						for (int i = 0; i < acceptVector.size(); i++) {
							if (!acceptVector.at(0).getIsVisible()) {
								minigameDataSpriteVector.updateIndividualTexture(acceptENUM, "completedMinigameSprite.png");
								minigameDataSpriteVector.setSpriteToComplete(acceptENUM);
								gameScreensENUM = mainENUM;
							}
							if(acceptVector.at(i).getIsVisible()) window.draw(acceptVector.at(i).getSprite());

							window.draw(acceptVector.at(i).getOverlap());
							acceptVector.at(i).setQuadrant(playerCirclePtr->getCircle());
							acceptVector.at(i).setForceOnPlayer(playerCirclePtr->getCircle(), playerCirclePtr->getMass());
							playerCirclePtr->setPlayerPosition(acceptVector.at(i).getForceOnPlayer());	

							if (acceptVector.at(2).getSprite().getGlobalBounds().contains(playerCirclePtr->getCircle().getPosition())) {
								if (acceptVector.at(2).getOverlap().getGlobalBounds().contains(playerCirclePtr->getCircle().getPosition())) {
									acceptVector.at(2).setVisibilty(false);
									acceptVector.at(2).setCanMovePlayer(false);
									acceptVector.at(1).setMass(pullingMass * 2);
									acceptVector.at(1).setMass(pullingMass * 2);
									acceptVector.at(0).setMass(pushingMass / 2);
									AcceptWallsVector.at(4).clearVertexArray();
									AcceptWallsVector.at(6).clearVertexArray();
									AcceptWallsVector.at(7).clearVertexArray();
								}
							}
							if (acceptVector.at(1).getSprite().getGlobalBounds().contains(playerCirclePtr->getCircle().getPosition())) {
								if (acceptVector.at(1).getOverlap().getGlobalBounds().contains(playerCirclePtr->getCircle().getPosition())) {
									acceptVector.at(1).setVisibilty(false);
									acceptVector.at(1).setCanMovePlayer(false);	
									acceptVector.at(0).setMass(-500000);
									AcceptWallsVector.at(10).clearVertexArray();
									AcceptWallsVector.at(11).clearVertexArray();
									AcceptWallsVector.at(12).clearVertexArray();
									AcceptWallsVector.at(13).clearVertexArray();
								}
							}
							if (acceptVector.at(0).getSprite().getGlobalBounds().contains(playerCirclePtr->getCircle().getPosition())) {
								if (acceptVector.at(0).getOverlap().getGlobalBounds().contains(playerCirclePtr->getCircle().getPosition())) {
									acceptVector.at(0).setVisibilty(false);
									acceptVector.at(0).setCanMovePlayer(false);
								}
							}
						}
						window.draw(playerCirclePtr->getCircle());
						drivePtr->drawScreen(window, timerTextPtr->getText());
					break;
					case retainENUM://RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN 
						retainPtr->drawScreen(window, timerTextPtr->getText());

						//for_each(retainStrings.begin(), retainStrings.end(), void());
						//std::for_each(retainStrings.begin(), retainStrings.end(), fadeAlpha->handleFallingText(translatedMousePosition));
						for (int i = 0; i < retainStrings.size(); i++) {
							fadeAlpha->handleFallingText(translatedMousePosition);
							window.draw(fadeAlpha->getText());
						}


					break;
					case pushENUM://PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH 
						pushPtr->drawScreen(window, timerTextPtr->getText());
					break;
					case bonusENUM://BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS 
						bonusPtr->drawScreen(window, timerTextPtr->getText());
					break;
				}
			}else{//TIME IS UP
				gameTimerPtr = gameTimerPtr->timeUp(gameTimerPtr);
				timerTextPtr->getText().setString("Time Up!");
				startScreenPtr->setAndCenterTitle("GAME OVER!");
				playerCirclePtr->setPlayerPosition(getCenterOfWindow(window));
				mainScreensENUM = startMAIN;
				gameScreensENUM = mainENUM;
			}
			break;

			case resumeMAIN://RESUME			
			assert(gameTimerPtr->getTimeRemaining() > 0);
			if (validSpriteClick(event, resumeButtonPtr->getSprite().getGlobalBounds(), translatedMousePosition) == true) {
				gameTimerClock.restart();
				ignoreTimerClock.restart();
				mainScreensENUM = gameMAIN;					
			} else resumeScreenPtr->drawScreen(window, timerTextPtr->getText());
			event.type = sf::Event::EventType::MouseButtonReleased;//this stops clicking through sprites
			break;
		}	

	}
}
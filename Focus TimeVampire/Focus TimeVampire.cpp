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
#include "acceptUtils.h"
#include "circle.h"


//ISSUES
//reset random numbers each playthrough for Remember
//add reset button
//add X_out button
//changing window size and player sprite going past the window
//sprite sizes should be relative the the window size at initialization

//gameTimer = gameTimer.pause(gameTimerClock, gameTimer); so many game timers?

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
	srand(time(NULL));

	//FONT & TEXT
	sf::Font generalFont;
	loadFont(generalFont);

	GameText* timerTextPtr = new GameText(generalFont, 20, "", 20, window);
	timerTextPtr->getText().setPosition(sf::Vector2f(5,30));
	GameText* bannerTextPtr = new GameText(generalFont, 30,"",0, window);
	bannerTextPtr->getText().setFillColor(sf::Color::Black);
	GameText* playerTextPtr = new GameText(generalFont, 30, "", 400, window);
	playerTextPtr->getText().setFillColor(sf::Color::White);
	GameText* tipTextPtr = new GameText(generalFont, 25, "Enter the missing values!", 55, window);
	playerTextPtr->getText().setFillColor(sf::Color::White);
	GameText* ignorePromptTextPtr = new GameText(generalFont, 30, "",20, window);
	ignorePromptTextPtr->setTextPosition(sf::Vector2f(50, 125));

	//GAME SPRITES

	GameSprite* startButtonPtr = new GameSprite("startSprite.png", 0.5, 0.5);
	startButtonPtr->setPosition(getCenterOfWindow(window));
	GameSprite* questionButtonPtr = new GameSprite("questionButton.png", 0.4, 0.4);
	questionButtonPtr ->setPosition(sf::Vector2f(window.getSize().x/2, 300));
	GameSprite* gobackButtonPtr = new GameSprite("gobackButton.png", 0.35, 0.35);
	gobackButtonPtr->setPosition(sf::Vector2f(window.getSize().x / 4, window.getSize().y - 100));
	GameSprite* skipButtonPtr = new GameSprite ("skipButton.png", 0.35, 0.35);
	skipButtonPtr->setPosition(sf::Vector2f(window.getSize().x / 4 * 3 , window.getSize().y - 100));
	GameSprite* pauseButtonPtr = new GameSprite("pauseSprite.png", 0.25, 0.25);
	pauseButtonPtr->setPosition(sf::Vector2f(window.getSize().x - 35, 40));
	GameSprite* resumeButtonPtr = new GameSprite("resumeSprite.png", 0.5, 0.5);
	resumeButtonPtr->setPosition(getCenterOfWindow(window));
	GameSprite* solutionButtonPtr = new GameSprite("solutionSprite.png", 0.3, 0.3);
	solutionButtonPtr->setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y - 50));
	GameSprite* bannerSpritePtr = new GameSprite("bannerSprite.png", 1, 1);
	bannerSpritePtr->setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y - 50));
	bannerTextPtr->getText().setPosition(sf::Vector2f(bannerSpritePtr->getSprite().getPosition().x, bannerSpritePtr->getSprite().getPosition().y - 20));
	GameSprite* backButtonPtr = new GameSprite("backSprite.png", 0.18, 0.18);
	backButtonPtr->setPosition(sf::Vector2f(window.getSize().x - 55, window.getSize().y - 30));
	GameSprite* acceptSpritePtr = new GameSprite("acceptSprite.png", 0.3, 0.3);
	acceptSpritePtr->setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y/2));

	//GameSprite* x_outButtonPtr = new GameSprite("x_outSprite.png", 0.25, 0.25);
//x_outButtonPtr->setPosition(sf::Vector2f(bannerSpritePtr->getSprite().getPosition().x + bannerSpritePtr->getSprite().getGlobalBounds().width/2 - 15
//, bannerSpritePtr->getSprite().getPosition().y - bannerSpritePtr->getSprite().getGlobalBounds().height / 2 + 30));

	//TRANSFORMABLE SPRITES
	//FIGURE OUT WHY THE SCALE MESSES UP THE CONTACT CIRCLE
	Circle* playerCirclePtr = new Circle("playerSprite.png", 10, 7, 1, 1);
	playerCirclePtr->setPosition(sf::Vector2f(window.getSize().x/2, window.getSize().y / 2));

	//DATA SPRITES
	DataSprite* minigameSpritePtr = new DataSprite("minigameSprite.png", 0.3, 0.3);
	DataSprite* fullBubblePtr = new DataSprite("fullBubbleSprite.png", 1, 1);
	DataSprite* emptyBubblePtr = new DataSprite("emptyBubbleSprite.png", 1, 1);
	DataSprite* countingSpritePtr = new DataSprite("countingSprite.png", 0.5, 0.5);
	
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
	pcbSolvedSprite.setPosition(getCenterOfWindow(window));
	assembleSolutionGameScreenPtr->addSprite(pcbSolvedSprite.getSprite());
	for (int i = 0; i < 9; i++) {assembleDataSpriteVector.addSprite( assemblePartsSpriteVector.at(i), 1); }
	assembleDataSpriteVector.setPositions(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2 - 10), 3, 3, 90, 120);
	assembleDataSpriteVector.setSpriteToComplete(4);
	assembleGoal.setOrigin(sf::Vector2f(assembleGoal.getGlobalBounds().width / 2, assembleGoal.getGlobalBounds().height / 2));
	for (int i = 0; i < assembleGoalPositions.size(); i++) {
		assembleGoal.setPosition(assembleGoalPositions[i]);
		assemblePartsGoals.push_back(assembleGoal);
	}
	//DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS DISCUSS 
	GameScreen* discussGameScreenPtr = new GameScreen("DISCUSS!", generalFont, 25, 25, window);
	DiscussText* npcTextPtr = new DiscussText(generalFont, 25, question1, questionY, window);
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
	GameSprite* discussBannerSpritePtr = new GameSprite("bannerSprite.png", 1.3, 1.1);
	discussBannerSpritePtr->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y - 150));

	GameText* leftAnswerPtr = new GameText(generalFont, 32, response1A, 200, window);
	leftAnswerPtr->getText().setFillColor(sf::Color::Black);
	leftAnswerPtr->setTextPosition(sf::Vector2f(discussBannerSpritePtr->getSprite().getPosition().x - discussBannerSpritePtr->getSprite().getGlobalBounds().width * 0.25
		, discussBannerSpritePtr->getSprite().getPosition().y));

	GameText* rightAnswerPtr = new GameText(generalFont, 32, response1B, 200, window);
	rightAnswerPtr->getText().setFillColor(sf::Color::Black);
	rightAnswerPtr->setTextPosition(sf::Vector2f(discussBannerSpritePtr->getSprite().getPosition().x + discussBannerSpritePtr->getSprite().getGlobalBounds().width * 0.25
		, discussBannerSpritePtr->getSprite().getPosition().y));
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
	// ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT 
	GameScreen* drivePtr = new GameScreen("ACCEPT!", generalFont, 25, 25, window);
	// RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN 
	GameScreen* retainPtr = new GameScreen("RETAIN!", generalFont, 25, 25, window);
	// PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH PUSH
	GameScreen* pushPtr  = new GameScreen("PUSH!", generalFont, 25, 25, window);
	// BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS BONUS
	GameScreen* bonusPtr = new GameScreen("BONUS!", generalFont, 25, 25, window);

	bool deleteKeyWorkaround = false;//both needed for delete workaround
	bool acceptText = false;

	enum mainScreens { startMAIN, gameMAIN, resumeMAIN };
	enum gameScreens { rememberENUM, countENUM, assembleENUM, discussENUM, ignoreENUM, acceptENUM, retainENUM, pushENUM, bonusENUM, mainENUM };
	mainScreens mainScreensENUM = startMAIN;
	gameScreens gameScreensENUM = mainENUM;

	sf::VertexArray testQuads(sf::Quads,5);
	testQuads[0].position = sf::Vector2f(200, 200);
	testQuads[1].position = sf::Vector2f(300, 200);
	testQuads[2].position = sf::Vector2f(300, 300);
	testQuads[3].position = sf::Vector2f(200, 300);
	testQuads[4].position = sf::Vector2f(200, 200);

	testQuads[0].color = sf::Color::Black;
	testQuads[1].color = sf::Color::Magenta;
	testQuads[2].color = sf::Color::Cyan;
	testQuads[3].color = sf::Color::Blue;

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
			if (acceptText) {
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
				timerTextPtr->getText().setString(gameTimerPtr->getString(out));
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
						acceptText = false;						
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
								if (!minigameDataSpriteVector.getSingleSprite(i).getIsComplete()) { gameScreensENUM = static_cast<gameScreens>(i); }

								event.type = sf::Event::EventType::MouseButtonReleased;

								//REMEMBER
								if (gameScreensENUM == rememberENUM) { 
									playerCirclePtr->setMovementSpeed(10); 
									playerCirclePtr->setPosition(getCenterOfWindow(window));
									//playerCirclePtr->setSpriteContactIndex(-1);
								}

								//IGNORE 
								if (gameScreensENUM == ignoreENUM) {
									dullBedPtr->play();
									convoPtr->play();
									ignoreTimerClock.restart();
									bannerSpritePtr->setPosition(getCenterOfWindow(window));
									acceptText = true;
								}

								//ACCEPT
								if (gameScreensENUM == acceptENUM) { 
									playerCirclePtr->setMovementSpeed(10); 
									playerCirclePtr->setPosition(sf::Vector2f(playerCirclePtr->getCircle().getRadius(), window.getSize().y - playerCirclePtr->getCircle().getRadius()));
								}
							}
						}
					}
					break;
				case rememberENUM://REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER REMEMBER 
					//swapping can be used to randomize vectors to increase difficulty
					playerCirclePtr->handlePlayerInput(window);
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
						acceptText = false;
						
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
								acceptText = true; 
							}
							else {
								acceptText = false;
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
					//acceptText = true;
					countGameScreenPtr->drawScreen(window, timerTextPtr->getText());
					countingSprites.drawSprites(window, -1);							
					bannerTextPtr->setTextString("How Many?");
					bannerTextPtr->centerTextOriginOnSprite(bannerSpritePtr->getSprite(), 0, -20);
					playerTextPtr->centerTextOriginOnSprite(bannerSpritePtr->getSprite(), 0, +11);
					window.draw(bannerSpritePtr->getSprite());
					window.draw(bannerTextPtr->getText());
					window.draw(playerTextPtr->getText());
					if (playerTextPtr->getTextString().size() < countingString.size()) {
						acceptText = true;
					} else acceptText = false;

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
									npcTextPtr->updateNextQuestion(question2, window, questionY);

									leftAnswerPtr->setString_Origin_Position(response2A, sf::Vector2f(discussBannerSpritePtr->getSprite().getPosition().x - discussBannerSpritePtr->getSprite().getGlobalBounds().width * 0.25
										, discussBannerSpritePtr->getSprite().getPosition().y));
									rightAnswerPtr->setString_Origin_Position(response2B, sf::Vector2f(discussBannerSpritePtr->getSprite().getPosition().x + discussBannerSpritePtr->getSprite().getGlobalBounds().width * 0.25
										, discussBannerSpritePtr->getSprite().getPosition().y));
									textBlockersVector = npcTextPtr->resetTextBlockers(textBlockersVector);
								break;
								case 3:
									npcTextPtr->updateNextQuestion(question3, window, questionY);
									leftAnswerPtr->setString_Origin_Position(response3A, sf::Vector2f(discussBannerSpritePtr->getSprite().getPosition().x - discussBannerSpritePtr->getSprite().getGlobalBounds().width * 0.25
										, discussBannerSpritePtr->getSprite().getPosition().y));
									rightAnswerPtr->setString_Origin_Position(response3B, sf::Vector2f(discussBannerSpritePtr->getSprite().getPosition().x + discussBannerSpritePtr->getSprite().getGlobalBounds().width * 0.25
										, discussBannerSpritePtr->getSprite().getPosition().y));
									textBlockersVector = npcTextPtr->resetTextBlockers(textBlockersVector);
								break;
								case 4:
									npcTextPtr->updateNextQuestion(question4, window, questionY);
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
								tipTextPtr->setString_Origin_Position("Time Left: " + ignoreTimerPtr->getString(out), sf::Vector2f(window.getSize().x / 2, 425));
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
								acceptText = true;
							} else {
								acceptText = false;
							}
										
							if (validSpriteClick(event, skipButtonPtr->getSprite().getGlobalBounds(), translatedMousePosition) == true || playerTextPtr->getTextString() == ignoreKeys[currentKey]) {
								//for the last prompt,  should it progress even if the answer is wrong?
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
					case acceptENUM://ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT ACCEPT
						//need to make a spriteVector for the acceptSprites
						//broad and narrow collision detection: only check for detection if actually close enough

						//need to create a vector of VertexArray for the walls
						//check for a collision only if the player is in the area
						
						playerCirclePtr->handlePlayerInput(window);//moves the player
						playerCirclePtr->handlePlayerCollision(testQuads);//Check for collision
						window.draw(playerCirclePtr->getCircle());
						window.draw(testQuads);

						drivePtr->drawScreen(window, timerTextPtr->getText());
					break;
					case retainENUM://RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN RETAIN 
						retainPtr->drawScreen(window, timerTextPtr->getText());
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
				playerCirclePtr->setPosition(getCenterOfWindow(window));
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
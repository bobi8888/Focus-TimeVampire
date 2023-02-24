#pragma once
int assembleScreen = 1;

sf::Vector2f resistorGoal (295, 313);
sf::Vector2f capacitorGoal (340, 235);
sf::Vector2f microchipGoal (264, 264);
sf::Vector2f diodeGoal (256, 313);
sf::Vector2f pcbGoal (-50,-50);
sf::Vector2f heatsinkGoal (307, 202);
sf::Vector2f usbPortGoal (194, 321);
sf::Vector2f relayGoal (240, 196);
sf::Vector2f jackGoal (146, 214);
vector <sf::Vector2f> assembleGoalPositions {resistorGoal, capacitorGoal, microchipGoal, diodeGoal, pcbGoal, heatsinkGoal, usbPortGoal, relayGoal, jackGoal};

sf::RectangleShape assembleGoal(sf::Vector2f(20, 20));
vector <sf::RectangleShape> assemblePartsGoals;

DataSprite resistorSprite("resistorSprite.png", 0.045, 0.045);
DataSprite capacitorSprite("capacitorSprite.png", 0.02, 0.02);
DataSprite microchipSprite("microchipSprite.png", 0.03, 0.03);
DataSprite diodeSprite("diodeSprite.png", 0.05, 0.05);
DataSprite pcbSprite("pcbSprite.png", 1, 1);
DataSprite heatsinkSprite("heatsinkSprite.png", 0.02, 0.02);
DataSprite usbPortSprite("usbPortSprite.png", 0.15, 0.15);
DataSprite relaySprite("relaySprite.png", 0.02, 0.02);
DataSprite jackSprite("jackSprite.png", 0.1, 0.1);
vector <DataSprite> assemblePartsSpriteVector{ resistorSprite, capacitorSprite, microchipSprite, diodeSprite, pcbSprite, heatsinkSprite, usbPortSprite, relaySprite, jackSprite };

DataSpriteVector assembleDataSpriteVector;
GameSprite pcbSolvedSprite("pcbSolvedSprite.png", 0.75, 0.75);
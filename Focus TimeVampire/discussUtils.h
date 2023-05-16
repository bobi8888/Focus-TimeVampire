#pragma once

sf::Color blockerFill(0,0,0);
sf::Color blockerBorder(0,0,0);
vector <sf::RectangleShape> textBlockersVector; 
float discussTime = 0;
float* discussTimePtr = &discussTime;

float discussSpeed = 0.02;
float* discussSpeedPtr = &discussSpeed;

float questionY = 200;
float* questionYPtr = &questionY;

int charToShow = 0;
int* charToShowPtr = &charToShow;

//int red = 0, blue = 0, green = 0;
//int* redPtr = &red;
//int* bluePtr = &blue;
//int* greenPtr = &green;

int redInc = 1, blueInc = 5, greenInc = 3;
int* redIncPtr = &redInc;
int questionNumber = 1;
string question1 = "How many minigames are there?", response1A = "9", response1B = "8";
string question2 = "Are they too easy?", response2A = "Yes", response2B = "No";
string question3 = "What is the wrong answer to my 1st question?", response3A = "8", response3B = "8.0";
string question4 = "I hope you find the secret ending…", response4A = "Walk away", response4B = "Steal key";

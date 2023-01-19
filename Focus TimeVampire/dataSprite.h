#pragma once

class DataSprite : public GameSprite {
	private:
		string letter = (1,""), valueAsString = (1, ""), fullDataString = (1, "");
		long value = 0;
		bool isComplete = false;
	public:
		using GameSprite::GameSprite;
		string getLetter();
		void setLetter(string letter);

		long getLongValue();
		void setLongValue(long currentLong);

		string getStringValue();
		void setStringValue(string string);

		string getFullDataString();
		void setFullDataString(string string);

		bool getIsComplete();
		void setIsComplete(bool complete);
};
#pragma once
#include <sstream>
#include "AIE.h"
#include <cstring>

//origin = Mr.Marco

class Textbox
{
	char input[64];			// the input that we're getting in
	int len;				// how many characters in the input
	float x, y;				// location to draw the textbox
	bool result;			// whether the textbox has received and 'enter' command
	bool key_cache[350];	// the state of all the keys on the keyboard

public:
	Textbox(float a_x, float a_y) : x(a_x), y(a_y)
	{
		clear();
	} 

	void update(float dt)
	{
		if (result) return;			// If this textbox is done, we don't need to update it

		for (int i = 31; i < 349; ++i) // Loop through every possible key
		{
			if (!key_cache[i] && IsKeyDown(i)) // Detecting a change in the key state - key pressed
			{							 
				 switch (i)
				 {
				 case 259: if(len > 0) input[--len]  = '\0'; break;
				 case 257: result = true; break;


				 default: if (i> 31 && i < 127 && len < 63)
					 
					 input[len++] = !IsKeyDown(340) && !IsKeyDown(344) ? tolower(i) : i;			 					 
					 break;
				 }
			}
			key_cache[i] = IsKeyDown(i); // updating the state of the key
		}
	}

	bool isDone() { return result; }
	std::string getString() { return input; }

	void draw()
	{
		// checks to see if the player's name is "Richard"
		try
		{			
			if (strcmp(input,"Richard") == 0)
				throw 0;
		}
		//if it is, a voice greets the player with "Ah, the Lionheart!"
		catch (...)
		{
			DrawString("Ah, the Lionheart!", g_screenW / 3.1, g_screenH / 1.5 - 4 * 40, SColour(255, 201, 14, 150));
		}
		DrawString(input, x, y);
	}

	void clear()
	{
		len = 0;
		result = false;
		memset(key_cache, 0, sizeof(bool) * 350);	//clear out the key cache- setting all keys to 'up'
		memset(input, '\0', sizeof(char) * 64);		//clear out all the text in our input array
	}
};
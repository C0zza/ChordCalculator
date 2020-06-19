#pragma once

#include <Windows.h>
#include <string>
#include <vector>

class Console
{
private:
	HANDLE outputHandle;
	COORD cursorPosition{ 0,0 }; // position of the cursor within the console
	CONSOLE_SCREEN_BUFFER_INFO m_info; // Screen buffer info
	CONSOLE_CURSOR_INFO m_cursorInfo;  // cursor info

public:
	Console(HANDLE hndle);
	Console();

	void setCursorPosition(int x, int y); // Set cursor position (x,y)
	void setCursorPosition(COORD thisCoordinate); // Set cursor position (coord)
	void setCharacterAttribute(int fgColour, int bgColour); // Set foreground and background colour of text
	void setCharacterAttribute(int fgColour);				// Set foreground colour of text.
	void setCursorVisibility(bool status);					// Set whether the blinking cursor is visible.

	CONSOLE_SCREEN_BUFFER_INFO getInfo();		// Get screen buffer info
	COORD GetCursorPosition(void);				// Get position of cursor position
	COORD getMousePosition();					// Get mouse position
	bool mouseClick();							// Return true/false value based on whether a click was made
	char GetInput();							// Wait for input
	void Clear();								// Clear the entire console
	void clearThis(std::string text, COORD anchor); // Clear the given element, string with position of a coord
	void clearThis(std::string text, int x, int y); //							       with position of x, y in ints
	void clearThis(std::vector<std::string> vec, COORD anchor); // Clear the given element, vector of strings with position of a coord
	void clearThis(std::vector<std::string> vec, int x, int y);											//    with position of x, y in ints
};


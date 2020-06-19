#include "Console.h"
#include <conio.h>
#include <vector>

Console::Console(HANDLE hndle)
	: outputHandle{ hndle }
{
	GetConsoleScreenBufferInfo(outputHandle, &m_info); // Retrieve the console screen buffer info so it can be manipulated
	setCursorVisibility(false); // Can no longer see blinking console cursor.
}

Console::Console()
	: outputHandle{ GetStdHandle(STD_OUTPUT_HANDLE) }
{
	GetConsoleScreenBufferInfo(outputHandle, &m_info);
	setCursorVisibility(false);
}


CONSOLE_SCREEN_BUFFER_INFO Console::getInfo()
{
	return m_info;
}

COORD Console::GetCursorPosition(void)
{
	return m_info.dwCursorPosition;
}

COORD Console::getMousePosition()
{
	POINT mousePOS;
	GetCursorPos(&mousePOS);
	ScreenToClient(GetConsoleWindow(), &mousePOS);

	HWND hWnd = GetConsoleWindow();
	RECT rcClient{ 0 };
	GetClientRect(hWnd, &rcClient);

	const SMALL_RECT& smRect = getInfo().srWindow;
	int x = smRect.Left + (mousePOS.x * (smRect.Right - smRect.Left))
		/ (rcClient.right - rcClient.left);
	int y = smRect.Top + (mousePOS.y * (smRect.Bottom - smRect.Top))
		/ (rcClient.bottom - rcClient.top);

	COORD mouseCoord;
	mouseCoord.X = x;
	mouseCoord.Y = y;

	return mouseCoord;
}

bool Console::mouseClick()
{
	if (GetAsyncKeyState(VK_LBUTTON)) {
		return true;
	}
	else {
		return false;
	}
}

void Console::setCursorPosition(int x, int y)
{
	COORD tempCoord{ x,y };
	SetConsoleCursorPosition(outputHandle, tempCoord);
	cursorPosition.X = x;
	cursorPosition.Y = y;
}

void Console::setCursorPosition(COORD thisCoordinate)
{
	COORD tempCoord{ thisCoordinate.X, thisCoordinate.Y };
	SetConsoleCursorPosition(outputHandle, tempCoord);
	cursorPosition = thisCoordinate;
}


void Console::setCharacterAttribute(int fgColour, int bgColour) {
	SetConsoleTextAttribute(outputHandle, (fgColour + (bgColour * 16)));
}

void Console::setCharacterAttribute(int fgColour)
{
	SetConsoleTextAttribute(outputHandle, fgColour);
}

void Console::setCursorVisibility(bool status)
{
	GetConsoleCursorInfo(outputHandle, &m_cursorInfo);
	m_cursorInfo.dwSize = 100;
	m_cursorInfo.bVisible = status;
	SetConsoleCursorInfo(outputHandle, &m_cursorInfo);
}

char Console::GetInput() {
	char tempChar = _getch();
	return tempChar;
}

void Console::Clear()
{
	DWORD dwBufferLen = m_info.dwSize.X * m_info.dwSize.Y;
	const COORD coordWriteStart = { 0,0 };
	DWORD dwWritten;

	const char fillChar = ' ';
	FillConsoleOutputAttribute(outputHandle, m_info.wAttributes, dwBufferLen, coordWriteStart, &dwWritten);
	FillConsoleOutputCharacter(outputHandle, fillChar, dwBufferLen, coordWriteStart, &dwWritten);
	SetConsoleCursorPosition(outputHandle, coordWriteStart);
}

void Console::clearThis(std::string text, COORD anchor)
{
	DWORD dwBufferLen = text.length();
	const COORD coordWriteStart = { anchor.X ,anchor.Y };
	DWORD dwWritten;

	const char fillChar = ' ';
	FillConsoleOutputAttribute(outputHandle, m_info.wAttributes, dwBufferLen, coordWriteStart, &dwWritten);
	FillConsoleOutputCharacter(outputHandle, fillChar, dwBufferLen, coordWriteStart, &dwWritten);
	SetConsoleCursorPosition(outputHandle, coordWriteStart);
}

void Console::clearThis(std::string text, int x, int y)
{
	DWORD dwBufferLen = text.length();
	const COORD coordWriteStart = { x ,y };
	DWORD dwWritten;

	const char fillChar = ' ';
	FillConsoleOutputAttribute(outputHandle, m_info.wAttributes, dwBufferLen, coordWriteStart, &dwWritten);
	FillConsoleOutputCharacter(outputHandle, fillChar, dwBufferLen, coordWriteStart, &dwWritten);
	//SetConsoleCursorPosition(outputHandle, coordWriteStart);
}

void Console::clearThis(std::vector<std::string> vec, COORD anchor)
{
	for (unsigned int i = 0; i < vec.size(); i++) {
		DWORD dwBufferLen = vec[i].size();
		const COORD coordWriteStart = { anchor.X, anchor.Y + i };
		DWORD dwWritten;

		const char fillChar = ' ';
		FillConsoleOutputAttribute(outputHandle, m_info.wAttributes, dwBufferLen, coordWriteStart, &dwWritten);
		FillConsoleOutputCharacter(outputHandle, fillChar, dwBufferLen, coordWriteStart, &dwWritten);
	}
	SetConsoleCursorPosition(outputHandle, anchor);
}

void Console::clearThis(std::vector<std::string> vec, int x, int y)
{
	for (unsigned int i = 0; i < vec.size(); i++) {
		DWORD dwBufferLen = vec[i].size();
		const COORD coordWriteStart = { x, y };
		DWORD dwWritten;

		const char fillChar = ' ';
		FillConsoleOutputAttribute(outputHandle, m_info.wAttributes, dwBufferLen, coordWriteStart, &dwWritten);
		FillConsoleOutputCharacter(outputHandle, fillChar, dwBufferLen, coordWriteStart, &dwWritten);
	}
	COORD tempCoord{ x,y };
	SetConsoleCursorPosition(outputHandle, tempCoord);
}

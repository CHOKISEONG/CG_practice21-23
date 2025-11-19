#pragma once

#include "header.h"

enum Mouse {
	LEFT,
	RIGHT
};

struct KeyState
{
	// 알파벳 대소문자 구별 안함
	std::array<bool, 26> alphabets{};
	std::array<bool, 10> numbers{};
	std::array<bool, 2> mouse{};

	void keyDown(const char ch)
	{
		if (ch >= 'a' && ch <= 'z')
		{
			alphabets[ch - 'a'] = true;
		}
		else if (ch >= 'A' && ch <= 'A')
		{
			alphabets[ch - 'A'] = true;
		}
		else if (ch >= '0' && ch <= '9')
		{
			numbers[ch - '0'] = true;
		}
	}
	void keyUp(const char ch)
	{
		if (ch >= 'a' && ch <= 'z')
		{
			alphabets[ch - 'a'] = false;
		}
		else if (ch >= 'A' && ch <= 'A')
		{
			alphabets[ch - 'A'] = false;
		}
		else if (ch >= '0' && ch <= '9')
		{
			numbers[ch - '0'] = false;
		}
	}

	// 아직 쓸 일이 없음
	void toggleMouse(Mouse _mouse)
	{
		if (_mouse == LEFT)
			mouse[LEFT] = !mouse[LEFT];
		else if (_mouse == RIGHT)
			mouse[RIGHT] = !mouse[RIGHT];
	}
};

// 편하게 쓸려고 struct에다가 전역에 둠
KeyState keyState;
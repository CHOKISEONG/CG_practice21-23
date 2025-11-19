#pragma once

#include "header.h"

enum Mouse {
	LEFT,
	RIGHT
};

enum Alphabets
{
	a, b, c, d, e, f, g, 
	h, i, j, k, l, m, n, o, p, 
	q, r, s, t, u, v, w, x, y, z,
	A, B, C, D, E, F, G, 
	H, I, J, K, L, M, N, O, P,
	Q, R, S, T, U, V, W, X, Y, Z
};

struct KeyState
{
	// 0~25 소문자, 26~51 대문자
	std::array<bool, 52> alphabets{};
	std::array<bool, 10> numbers{};
	std::array<bool, 2> mouse{};

	void keyDown(const char ch)
	{
		if (ch >= 'a' && ch <= 'z')
		{
			alphabets[ch - 'a'] = true;
		}
		else if (ch >= 'A' && ch <= 'Z')
		{
			alphabets[ch - 'A' + 26] = true;
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
			alphabets[ch - 'A' + 26] = false;
		}
		else if (ch >= '0' && ch <= '9')
		{
			numbers[ch - '0'] = false;
		}
	}
	void keyClear()
	{
		alphabets = std::array<bool, 52>{};
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
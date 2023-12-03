#pragma once
#include <SFML/Graphics.hpp>

class WindowManager
{
public:

	static void Init();
	inline static int GetFps() { return fps; }
	inline static int GetMaxFps() { return maxFps; }
	inline static int GetMinFps() { return minFps; }
	inline static void SetFps(int _fps) { fps = _fps; }
	inline static void SetMinFps(int& _minFps) { minFps = _minFps; }
	inline static void SetMaxFps(int& _maxFps) { maxFps = _maxFps; }

	inline static sf::RenderWindow* GetWindow() { return window; }
	inline static void SetWindow(sf::RenderWindow* _window) { window = _window; }
	inline static int GetWindowWidth() { return window->getSize().x; }
	inline static float GetFloatWindowWidth() { return (float) window->getSize().x; }
	inline static int GetWindowHeight() { return window->getSize().y; }
	inline static float GetFloatWindowHeight() { return (float) window->getSize().y; }

	inline static void Clear() { window->clear(sf::Color::Black); }
	inline static void Display() { window->display(); }

private:
	static sf::RenderWindow* window;
	static int fps;
	static int minFps;
	static int maxFps; 
};


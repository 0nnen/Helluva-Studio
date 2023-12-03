#pragma once
class Engine
{
public:
	static Engine* GetInstance();

	void Init() const;
	void Run() const;
	void Quit() { shouldQuit = true; }

private:
	static Engine* instance;

	bool shouldQuit = false;
};


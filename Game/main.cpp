#include "Engine.h"
int main()
{
	const Engine* engine = Engine::GetInstance();

	engine->Init();

	engine->Run();

	return 0;
}

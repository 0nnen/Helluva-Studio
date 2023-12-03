#include "Command.h"

Command::Command() 
{
	this->entity = nullptr;
}

Command::Command(GameObject* _entity) 
{
	this->entity = _entity;
}
Command::~Command(){}

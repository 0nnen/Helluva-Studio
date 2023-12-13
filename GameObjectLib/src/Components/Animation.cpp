#include "Components/Animation.h"
#include <iostream>

void Animation::Play()
{
	if (!isPlaying) {
		sprite = GetOwner()->GetComponentsByType<Sprite>()[0];
		sprite->SetActiveAndVisible(true);
		sprite->SetTexture(spriteSheet, totalFrame);
		isPlaying = true;
	}
	
}

void Animation::Play(const std::string& _nameSprite)
{
	if (!isPlaying) {
		for (Sprite* _sprite : GetOwner()->GetComponentsByType<Sprite>())
		{
			if (_sprite->GetName() == _nameSprite)
			{
				sprite = _sprite;
				sprite->SetActiveAndVisible(true);
				sprite->SetTexture(spriteSheet, totalFrame);
				isPlaying = true;
			}
		}
	}
}

void Animation::Update(const float& _delta)
{
	Component::Update(_delta);
	if (isPlaying)
	{
		if (actualLoop != totalLoop)
		{
			if (sprite) {
				if (totalFrame > actualFrame + 1)
				{
					if (actualTime > animationTime / totalFrame)
					{

						actualTime = 0.f;
						actualFrame++;
						sprite->SetRecTexture(actualFrame, width / totalFrame, height);
					}
					actualTime += _delta;
				}
				else
				{
					actualLoop++;
					actualFrame = 0;
					actualTime = 0.f;
					sprite->SetRecTexture(actualFrame, width / totalFrame, height);
				}
			}
		}
		else
		{
			actualLoop = 0;
			this->Stop();
		}

	}

}

void Animation::SetSpriteSheet(sf::Texture* _spriteSheet)
{
	spriteSheet = _spriteSheet;
	width = spriteSheet->getSize().x;
	height = spriteSheet->getSize().y;
}

void Animation::SetLoop(const int& _loop)
{
	if (_loop < -1)
	{
		totalLoop = -1;
	}
	else
	{
		totalLoop = _loop;
	}
}
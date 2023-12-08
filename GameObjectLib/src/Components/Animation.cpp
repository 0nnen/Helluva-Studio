#include "Components/Animation.h""

void Animation::Play()
{
	for (Component* component : GetOwner()->GetComponents())
	{
		Animation* animation = static_cast<Animation*>(component);
		if (animation && animation != this)
		{
			animation->Stop();
		}
	}
	Sprite* sprite = GetOwner()->GetComponent<Sprite>();
	sprite->SetTexture(spriteSheet, totalFrame);
	isPlaying = true;
}
void Animation::Update(const float& _delta)
{
	Component::Update(_delta);
	if (isPlaying)
	{
		if (actualLoop != totalLoop)
		{
			Sprite* sprite = GetOwner()->GetComponent<Sprite>();
			if (totalFrame > actualFrame + 1)
			{
				if (actualTime > animationTime / totalFrame)
				{
			
					actualTime = 0.f;
					actualFrame++;
					sprite->SetRecTexture(actualFrame, totalFrame, width / totalFrame, height);
				}
				actualTime += _delta;
			}
			else
			{
				actualLoop++;
				actualFrame = 0;
				actualTime = 0.f;
				sprite->SetRecTexture(actualFrame, totalFrame, width / totalFrame, height);
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
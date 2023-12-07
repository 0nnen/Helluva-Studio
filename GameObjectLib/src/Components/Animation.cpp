#include "Components/Animation.h""

Animation::Animation()
{
	sprite = GetOwner()->GetComponent<Sprite>();
}

void Animation::Play()
{
	for (Component* component : GetOwner()->GetComponents())
	{
		if (Animation* animation = static_cast<Animation*>(component))
		{
			animation->Stop();
		}
	}
	isPlaying = true;
}
void Animation::Update(const float& _delta)
{
	Component::Update(_delta);
	if (isPlaying)
	{
		if (actualLoop != totalLoop)
		{
			if (totalFrame > actualFrame + 1)
			{
				if (actualTime > animationTime / (totalFrame + 1))
				{
					actualTime = 0.f;
					actualFrame++;
					sprite->SetRecTexture(actualFrame, totalFrame);
				}
				actualTime += _delta;
			}
			else
			{
				actualLoop++;
				actualFrame = 0;
				actualTime = 0.f;
				sprite->SetRecTexture(actualFrame, totalFrame);
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
	sprite->SetTexture(spriteSheet);
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
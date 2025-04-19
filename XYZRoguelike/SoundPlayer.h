#pragma once
#include "SoundPlayer.h"

#include <GameObject.h>
#include <GameWorld.h>
#include <SoundComponent.h>
#include <ResourceSystem.h>

class SoundPlayer
{
public:
	SoundPlayer(const std::string& soundName);
private:
	XYZEngine::GameObject* gameObject;
};

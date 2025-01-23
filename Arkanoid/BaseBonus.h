#pragma once
#include "SpriteObject.h"
#include "Resources.h"
namespace Arkanoid 
{
	class BaseBonus : public SpriteObject
	{
	private:
		bool isDestroy = false;
	public:
		enum class TypeBonus
		{
			FireBall = 0, 
			GlassBrick,
			IncreasingPlatform
		};
		virtual void Initialization(GameResources& resources) = 0;
		virtual void Update(float& deltaTime);
		virtual TypeBonus GetTypeBonus();
		void DestroyBonus();
		bool isDestroyed();
	protected:
		TypeBonus typeBonus;
	};
}


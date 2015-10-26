#pragma once

#ifndef PAWNSPAWNER_H
#define PAWNSPAWNER_H

#include "ISpawner.h"

namespace Framework
{
	class PawnSpawner :public ISpawner
	{
	public:
		Framework::GameObject*  Spawn()							override;
		void					Activate()						override;
		void					Deactivate()					override;
		void					ResetObject(GameObject* object) override;
		bool					IsActive()				  const override;
	};
}

#endif // PAWNSPAWNER_H
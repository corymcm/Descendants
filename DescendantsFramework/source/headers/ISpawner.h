#pragma once

#ifndef ISPAWNER_H
#define ISPAWNER_H

#include "GameObject.h"


namespace Framework
{
	class DESCENDANT_EXPORT ISpawner
	{
	public:
		virtual Framework::GameObject*	Spawn()							= 0;
		virtual void					ResetObject(GameObject* object) = 0;
		virtual bool					IsActive() const				= 0;
		virtual void					Activate()						= 0;
		virtual void					Deactivate() 					= 0;

			private:
		friend class boost::serialization::access;
		template<class Archive> inline void serialize(Archive & ar, const unsigned int version)
		{
			DESCENDANT_UNUSED(version);
			DESCENDANT_UNUSED(ar);
		}
	};
}

#endif // ISPAWNER_H
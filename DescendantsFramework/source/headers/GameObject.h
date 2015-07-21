#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

// include headers that implement a archive in simple text format
#include <Boost/archive/text_oarchive.hpp>
#include <Boost/archive/text_iarchive.hpp>

namespace GameObject
{
	class GameObject
	{
		friend class boost::serialization::access;

	private:
		SDL_Texture* _texture;
		std::string _textureName;

		DESCENDANT_EXPORT SDL_Surface* LoadBitmap(const char* path);

		template<class Archive>
		inline void serialize(Archive & ar, const unsigned int version)
		{
			DESCENDANT_UNUSED(version);

			ar & _textureName;
			ar & src_x;
			ar & src_y;
			ar & src_w;
			ar & src_h;

			ar & dest_x;
			ar & dest_y;
			ar & dest_w;
			ar & dest_h;
		}

	protected:
		int src_x = 0;
		int src_y = 0;
		int src_w = 0;
		int src_h = 0;

		int dest_x = 0;
		int dest_y = 0;
		int dest_w = 0;
		int dest_h = 0;

		DESCENDANT_EXPORT SDL_Texture* LoadTexture(std::string texturePath, SDL_Renderer* renderer);

		DESCENDANT_EXPORT SDL_Rect* GetDestination()
		{
			if (dest_x == 0 && dest_y == 0 && dest_w == 0 && dest_h == 0)
				return nullptr;
			return new SDL_Rect{ dest_x, dest_y, dest_w, dest_h };
		};

		DESCENDANT_EXPORT SDL_Rect* GetPosition()
		{ 
			if (src_x == 0 && src_y == 0 && src_w == 0 && src_h == 0)
				return nullptr;
			return new SDL_Rect{ src_x, src_y, src_w, src_h };
		};

	public:
		bool RequiresLoad = true;

		DESCENDANT_EXPORT GameObject(std::string textureName, SDL_Renderer* renderer, SDL_Rect* source, SDL_Rect* destination);
		DESCENDANT_EXPORT GameObject();

		virtual DESCENDANT_EXPORT ~GameObject();

		DESCENDANT_EXPORT void SetTexture(std::string texturePath, SDL_Renderer* renderer);

		virtual void DESCENDANT_EXPORT Update(SDL_Event* e);
		virtual void DESCENDANT_EXPORT Render(SDL_Renderer* renderer);
	};
}

#endif // GAMEOBJECT_H
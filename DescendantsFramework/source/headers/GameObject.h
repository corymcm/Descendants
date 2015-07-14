#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

// include headers that implement a archive in simple text format
#include <Boost/archive/text_oarchive.hpp>
#include <Boost/archive/text_iarchive.hpp>
#include <Boost/serialization/split_member.hpp>

namespace GameObject
{
	class GameObject
	{
		friend class boost::serialization::access;

	private:
		DESCENDANT_EXPORT SDL_Surface* LoadBitmap(const char* path);

		template<class Archive>
		void save(Archive & ar, const unsigned int version) const
		{
			DESCENDANT_UNUSED(version);

			ar & _texturePath;
			ar & src_x;
			ar & src_y;
			ar & src_w;
			ar & src_h;

			ar & dest_x;
			ar & dest_y;
			ar & dest_w;
			ar & dest_h;
		}

		template<class Archive>
		void load(Archive & ar, const unsigned int version)
		{
			DESCENDANT_UNUSED(version);

			ar & _texturePath;
			ar & src_x;
			ar & src_y;
			ar & src_w;
			ar & src_h;

			ar & dest_x;
			ar & dest_y;
			ar & dest_w;
			ar & dest_h;
		}

		BOOST_SERIALIZATION_SPLIT_MEMBER()

	protected:
		int src_x = 0;
		int src_y = 0;
		int src_w = 0;
		int src_h = 0;

		int dest_x = 0;
		int dest_y = 0;
		int dest_w = 0;
		int dest_h = 0;

		SDL_Texture* _texture;
		bool _requiresLoad = true;
		std::string _texturePath;

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
		DESCENDANT_EXPORT GameObject(std::string texturePath, SDL_Renderer* renderer, SDL_Rect* source, SDL_Rect* destination);
		DESCENDANT_EXPORT GameObject();

		virtual DESCENDANT_EXPORT ~GameObject();

		virtual void DESCENDANT_EXPORT Update(SDL_Event* e);
		virtual void DESCENDANT_EXPORT Render(SDL_Renderer* renderer);
	};
}

#endif // GAMEOBJECT_H
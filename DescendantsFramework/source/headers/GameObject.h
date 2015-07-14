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
			ar & pos_x;
			ar & pos_y;
			ar & pos_w;
			ar & pos_h;
		}

		template<class Archive>
		void load(Archive & ar, const unsigned int version)
		{
			DESCENDANT_UNUSED(version);

			ar & _texturePath;
			ar & pos_x;
			ar & pos_y;
			ar & pos_w;
			ar & pos_h;
		}

		BOOST_SERIALIZATION_SPLIT_MEMBER()

	protected:
		SDL_Texture* _texture;
		bool _requiresLoad = true;
		std::string _texturePath;

		DESCENDANT_EXPORT SDL_Texture* LoadTexture(std::string texturePath, SDL_Renderer* renderer);

		int pos_x = 0;
		int pos_y = 0;
		int pos_w = 0;
		int pos_h = 0;

		DESCENDANT_EXPORT SDL_Rect* GetPosition()
		{ 
			if (pos_x == 0 && pos_y == 0 && pos_w == 0 && pos_h == 0)
				return nullptr;
			return new SDL_Rect{ pos_x, pos_y, pos_w, pos_h }; 
		};

	public:
		DESCENDANT_EXPORT GameObject(std::string texturePath, SDL_Renderer* renderer, int posx, int posy, int width, int height);
		DESCENDANT_EXPORT GameObject(std::string texturePath, SDL_Renderer* renderer, SDL_Rect* position);
		DESCENDANT_EXPORT GameObject();

		virtual DESCENDANT_EXPORT ~GameObject();

		virtual void DESCENDANT_EXPORT Update(SDL_Event* e);
		virtual void DESCENDANT_EXPORT Render(SDL_Renderer* renderer);
	};
}

#endif // GAMEOBJECT_H
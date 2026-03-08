#pragma once

#include <SDL3/SDL.h>
#include "Math.hpp"

struct Sprite
{
	Sprite()
	:name(""),
	texture(NULL),
	flip(SDL_FLIP_NONE),
	color(255, 255, 255), alpha(255),
	origin(0.f, 0.f), frameSize(0, 0),
	z(1.f), layer(1.f),
	camera(true)
	{}
	std::string name;
	SDL_Texture* texture;
	SDL_FlipMode flip;
	Vec3 color;
	float alpha;

	Vec2 origin;
	Vec2i frameSize;

	float z;
	float layer;

	bool camera;
};
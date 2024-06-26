#pragma once
#include <gl2d/gl2d.h>

struct TiledRenderer {
	float backgroundSize = 3000;
	gl2d::Texture texture;

	float parallaxStrength = 1;

	void render(gl2d::Renderer2D& renderer);
};
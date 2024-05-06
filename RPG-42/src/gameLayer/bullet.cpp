#include <bullet.h>

void Bullet::render(gl2d::Renderer2D &renderer, gl2d::Texture bulletTex, gl2d::TextureAtlasPadding bulletsAtlas) {
	float bulletAngle = atan2(fireDir.y, -fireDir.x);
	bulletAngle = glm::degrees(bulletAngle) + 90.f;
	renderer.renderRectangle({ position - glm::vec2(25,25), 50, 50 }, bulletTex, Colors_White, {}, bulletAngle, bulletsAtlas.get(1,1));
}

void Bullet::update(float deltaTime) {
	position += fireDir * deltaTime * 1500.f;
}
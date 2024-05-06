#define GLM_ENABLE_EXPERIMENTAL
#include "gameLayer.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "platformInput.h"
#include "imgui.h"
#include <iostream>
#include <sstream>
#include <vector>
#include "imfilebrowser.h"
#include <gl2d/gl2d.h>
#include <platformTools.h>
#include <tiledRenderer.h>
#include <bullet.h>


//FULL DISCLOSURE, I USED A SECONDARY LIBRARY AND HELP TO MAKE THIS, I JUST USED MY RESOURCES AT HAND
//UNFINISHED, THE GAME HAS ONLY THE BASIC FUNCTIONS OF A TOPDOWN SHOOTER (NO MAPS, DOES NOT FOLLOW THE STORY THAT HAS BEEN SET UP


struct Gameplay_Data {
	glm::vec2 playerPos = { 100, 100 };
	std::vector<Bullet> proj;
};

Gameplay_Data data;

gl2d::Renderer2D renderer;

constexpr int BACKGROUNDS = 3;

gl2d::Texture playerTexR;
gl2d::Texture playerTexL;
gl2d::Texture bulletTex;
gl2d::TextureAtlasPadding bulletsAtlas;
gl2d::Texture enemyTex;
gl2d::Texture backgroundTex[BACKGROUNDS];

TiledRenderer tiledRenderer[BACKGROUNDS];

void restartGame() {
	data = {};
}

bool initGame()
{
	//initializing stuff for the renderer
	gl2d::init();
	renderer.create();

	playerTexR.loadFromFile(RESOURCES_PATH "Bot Wheel/no_move.png", true);
	playerTexL.loadFromFile(RESOURCES_PATH "Bot Wheel/no_move_left.png", true);

	bulletTex.loadFromFileWithPixelPadding(RESOURCES_PATH "Bot Wheel/energy_bull.png", 100, true);
	bulletsAtlas = gl2d::TextureAtlasPadding(5, 2, bulletTex.GetSize().x, bulletTex.GetSize().y);

	enemyTex.loadFromFile(RESOURCES_PATH "Shock Sweeper/no_move.png", true);
	backgroundTex[0].loadFromFile(RESOURCES_PATH "space/backback.png", true);
	backgroundTex[1].loadFromFile(RESOURCES_PATH "space/backover.png", true);
	backgroundTex[2].loadFromFile(RESOURCES_PATH "space/backback2.png", true);
	//backgroundTex[3].loadFromFile(RESOURCES_PATH "space/shiptex.png", true);

	tiledRenderer[0].texture = backgroundTex[0];
	tiledRenderer[1].texture = backgroundTex[1];
	tiledRenderer[2].texture = backgroundTex[2];
	//tiledRenderer[3].texture = backgroundTex[3];

	tiledRenderer[0].parallaxStrength = 0.0;
	tiledRenderer[1].parallaxStrength = 0.5;
	tiledRenderer[2].parallaxStrength = 0.7;
	//tiledRenderer[3].parallaxStrength = 0.0;



	return true;
}



bool gameLogic(float deltaTime)
{
#pragma region init stuff
	int w = 0; int h = 0;
	w = platform::getFrameBufferSizeX(); //window w
	h = platform::getFrameBufferSizeY(); //window h

	glViewport(0, 0, w, h);
	glClear(GL_COLOR_BUFFER_BIT); //clear screen

	renderer.updateWindowMetrics(w, h);
#pragma endregion

#pragma region movement
	glm::vec2 movement = {};

	if (platform::isButtonHeld(platform::Button::W)) { movement.y = -1; }
	if (platform::isButtonHeld(platform::Button::S)) { movement.y = 1; }
	if (platform::isButtonHeld(platform::Button::A)) { movement.x = -1; }
	if (platform::isButtonHeld(platform::Button::D)) { movement.x = 1; }

	if (movement.x != 0 || movement.y != 0) {
		movement = glm::normalize(movement);
		movement *= deltaTime * 500; //200 Pixels per second
		data.playerPos += movement;
	}

#pragma endregion

#pragma region follow
	renderer.currentCamera.follow(data.playerPos, deltaTime * 150, 10, 200, w, h);
#pragma endregion

#pragma region background rendering
	//renderer.currentCamera.zoom = 0.5;

	for (int i = 0; i < BACKGROUNDS; i++) {
		tiledRenderer[i].render(renderer);
	}

#pragma endregion

#pragma region mouse pos
	glm::vec2 mousePos = platform::getRelMousePosition();
	glm::vec2 screenCenter(w / 2.f, h / 2.f);

	glm::vec2 mouseDirection = mousePos - screenCenter;

	if (glm::length(mouseDirection) == 0.f) {
		mouseDirection = { 1,0 };
	}
	else {
		mouseDirection = normalize(mouseDirection);
	}
	//To Determine the angle for projectiles or display
	float playerAngle = atan2(mouseDirection.y, -mouseDirection.x);

	//Texture Exclusive Angle
	float playerAngleF = atan2(mouseDirection.y, mouseDirection.x);

#pragma endregion

#pragma region bullet math

	if (platform::isLMousePressed()) {
		Bullet ex;
		ex.position = data.playerPos;
		ex.fireDir = mouseDirection;
		data.proj.push_back(ex);
	}

	for (int i = 0; i < data.proj.size(); i++) {
		if (glm::distance(data.proj[i].position, data.playerPos) > 5'000) {
			data.proj.erase(data.proj.begin() + i);
			i--;
			continue;
		}
		data.proj[i].update(deltaTime);
	}

	for (auto &ex : data.proj) {
		ex.render(renderer, bulletTex, bulletsAtlas);
	}
	for (auto& ex : data.proj) {
		ex.update(deltaTime);
	}

#pragma endregion

#pragma region render player
	//all floats, {x,y, w,h (size of rectangle) }
	//renderer.renderRectangle({ data.playerPos, 100, 100 }, playerTexL, Colors_White, {}, glm::degrees(playerAngle) + 90.f);
	
	//Calcs which texture to render based on which way the mouse is pointing
	constexpr float playerSize = 100.f;
	float playerAngleF2 = glm::degrees(playerAngleF);
	if (playerAngleF2 < -90.f || playerAngleF2 > 90.f ) {
		renderer.renderRectangle({ data.playerPos - glm::vec2(playerSize/2,playerSize/2), 100, 100}, playerTexL);
	}
	else {
		renderer.renderRectangle({ data.playerPos - glm::vec2(playerSize / 2,playerSize / 2), 100, 100 }, playerTexR);
	}

#pragma endregion

	renderer.flush();

	//ImGui::ShowDemoWindow();

	//OnScreenData showing ingame statistics
	ImGui::Begin("OnScreenStats");
	ImGui::Text("Bullets count: %d", (int)data.proj.size());
	if (ImGui::Button("Restart Game")) { restartGame(); }
	ImGui::End();

	return true;
#pragma endregion

}

//This function might not be be called if the program is forced closed
void closeGame()
{



}

#include "gametime.h"

float GameTime::s_last_time = 0;
float GameTime::s_last_last_time = 0;

void GameTime::Init() {

}

void GameTime::Update() {
	s_last_last_time = s_last_time;
	s_last_time = glfwGetTime();
}
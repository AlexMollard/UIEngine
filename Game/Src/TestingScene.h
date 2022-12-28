#pragma once
#include "Scene.h"
#include <string_view>
#include "glm/glm.hpp"
class TestingScene : public Scene
{
public:
	explicit TestingScene(std::string_view inName) { name = inName; };

	void OnCreate() override{ /*To Be Impelmented*/ };
	void Enter() override;

	void Exit() override;
	void OnDestroy() override{ /*To Be Impelmented*/ };

	void Update(float deltaTime) override;
	void Draw() override;

private:
	std::string name;

	glm::vec3 direction = glm::vec3(0.2f, 0.2f, 0.0f);
};

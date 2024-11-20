#include "stdafx.h"
#include "StartButton.h"
#include "Scene.h"

StartButton::StartButton(const std::string& textId, const std::string& name, unsigned int textSize, sf::Color textColor)
	: UIButtonObject(textId, name, textSize, textColor)
{
}

void StartButton::OnCollisionEnter(Collider* target)
{
}

void StartButton::OnCollisionStay(Collider* target)
{
	if (InputManager::GetInstance().GetKeyUp(sf::Mouse::Left))
	{
		SceneManager::GetInstance().ChangeScene(SceneIds::SceneDev1);
	}
}
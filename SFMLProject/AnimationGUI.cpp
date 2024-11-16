#include "stdafx.h"
#include "AnimationGUI.h"
#include "imgui.h"

AnimationGUI::AnimationGUI()
	: ComponentGUI(ComponentGUIType::Animator)
	, animator(nullptr)
	// , useAnimationTool(true)
{
	// animationTool = new AnimationToolGUI;
}

AnimationGUI::~AnimationGUI()
{
	// delete animationTool;
}

void AnimationGUI::Update()
{
	if (animator == nullptr)
		return;
	ImGui::Text("Animation"); ImGui::SameLine();
	ImGui::BeginChild("##Animation");

	/*if (useAnimationTool)
		animationTool->Update();*/

	ImGui::EndChild();
}

void AnimationGUI::SetObject(GameObject* object)
{
	target = object;

	if (target == nullptr || target->GetAnimator() == nullptr)
	{
		animator = nullptr;
		return;
	}

	animator = target->GetAnimator();
	

}
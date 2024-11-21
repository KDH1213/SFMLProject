#include "stdafx.h"
#include "UICoinObject.h"
#include "Animator.h"

UICoinObject::UICoinObject(const std::string& name)
	: UIAnimationObject(name)
{
	animator->LoadCsv("animators/coin.csv");
}

void UICoinObject::Start()
{
	UIAnimationObject::Start();

	animator->ChangeAnimation("coinIdle", true);
}

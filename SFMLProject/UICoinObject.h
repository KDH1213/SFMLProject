#pragma once
#include "UIAnimationObject.h"
class UICoinObject : public UIAnimationObject
{
public:
	void Start() override;

public:
	UICoinObject(const std::string& name);
	virtual ~UICoinObject() = default;
	UICoinObject& operator= (const UICoinObject& other) = delete;
};


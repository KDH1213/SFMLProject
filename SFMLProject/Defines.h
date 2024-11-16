#pragma once

struct DefaultStatus
{
	int			maxHp;
	int			hp;
	float		speed;
	float		jumpPower;
	float		maxJumpPower;

	DefaultStatus() {}
	DefaultStatus(int hp, float speed, float jumpPower, float maxJumpPower)
		: hp(hp), maxHp(hp), speed(speed), jumpPower(jumpPower), maxJumpPower(maxJumpPower) {}
};
#pragma once
class BurgerTimeScene
{
public:
	BurgerTimeScene();
	~BurgerTimeScene() = default;
	BurgerTimeScene(const BurgerTimeScene& other) = delete;
	BurgerTimeScene(BurgerTimeScene&& other) noexcept = delete;
	BurgerTimeScene& operator=(const BurgerTimeScene& other) = delete;
	BurgerTimeScene& operator=(BurgerTimeScene&& other) noexcept = delete;

private:
};

#pragma once
#include "BaseComponent.h"
class MenuComponent :public BaseComponent

{
public:
	void Initialize(dae::GameObject* owner) override;
	void Render() override;
	void Update() override;

private:
	void ComposeWindow();
};

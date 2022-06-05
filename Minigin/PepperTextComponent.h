#pragma once
#include "BaseComponent.h"
class PepperTextComponent :
	public BaseComponent, public Observer
{
public:
	void Update() override;
	void Render() override;
	void Notify(const dae::GameObject& actor, Event event) override;
	void Refresh(const dae::GameObject& actor);
private:
	void ChangeText(const dae::GameObject& actor);
};

#pragma once
#include "BaseComponent.h"

class ScoreComponent : public BaseComponent, public Observer
{
public:
	void Notify(const dae::GameObject& actor, Event event) override;
	void Update() override;
	void Render() override;

private:
	void ChangeText(const dae::GameObject& object);
};

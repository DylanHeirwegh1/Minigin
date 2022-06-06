#pragma once
#include "BaseComponent.h"
class LivesComponent :
	public BaseComponent, public Observer
{
public:
	void Notify(const dae::GameObject& actor, Event event) override;
	void Update() override;
	void Render() override;
	void Refresh(const dae::GameObject& actor);
private:
	void ChangeText(const dae::GameObject&);
};

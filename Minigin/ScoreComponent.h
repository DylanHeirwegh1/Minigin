#pragma once
#include "BaseComponent.h"

class ScoreComponent : public BaseComponent, public Observer
{
public:

	ScoreComponent();
	~ScoreComponent() = default;
	ScoreComponent(const ScoreComponent& other) = delete;
	ScoreComponent(ScoreComponent&& other) noexcept = delete;
	ScoreComponent& operator=(const ScoreComponent& other) = delete;
	ScoreComponent& operator=(ScoreComponent&& other) noexcept = delete;
	void Render() override;
	void Update() override;

	void Notify(const dae::GameObject& actor, Event event) override;

};


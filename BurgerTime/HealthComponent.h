#pragma once
#include "BaseComponent.h"

class HealthComponent : public BaseComponent, public Observer
{
public:
	HealthComponent();
	~HealthComponent() = default;
	HealthComponent(const HealthComponent& other) = delete;
	HealthComponent(HealthComponent&& other) noexcept = delete;
	HealthComponent& operator=(const HealthComponent& other) = delete;
	HealthComponent& operator=(HealthComponent&& other) noexcept = delete;

	void Render() override;
	void Update() override;

	void Notify(const dae::GameObject& actor, Event event) override;

};


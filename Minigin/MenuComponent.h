#pragma once
#include "BaseComponent.h"
class MenuComponent :public BaseComponent

{
public:
	void Initialize(dae::GameObject* owner) override;
	void Render() override;
	void Update() override;
	Subject* GetSubject() const { return m_Subject.get(); };

private:
	void ComposeWindow();
	std::unique_ptr<Subject> m_Subject{ std::make_unique<Subject>() };
};

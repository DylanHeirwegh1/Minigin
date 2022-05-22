#pragma once

#include "BaseComponent.h"

class IngredientComponent :
	public BaseComponent
{
public:
	void Render() override;
	void Update() override;
};

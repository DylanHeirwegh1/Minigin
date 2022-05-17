#pragma once
#include "BaseComponent.h"
#include "imgui_plot.h"

namespace dae
{
	class Minigin;
}


class PlotComponent : public BaseComponent
{
public:
	void Update() override;
	void Render()override;
	void AddGraph(std::pair<const char*, ImGui::PlotConfig> graphData);
	void AddGraph(const char* name);
	void UpdateGraph(int idx, ImGui::PlotConfig graphData);
	void SetEngine(dae::Minigin* min);
	void SetWindowName(const char* name);


private:
	bool m_PressedButton{ false };

	const char* m_WindowName{ "testwindow" };
	std::vector<bool>m_DisplayGraphs;
	int m_Samples;
	dae::Minigin* m_Engine{ nullptr };

	std::vector<std::pair<const char*, ImGui::PlotConfig>> m_Graphs;
};


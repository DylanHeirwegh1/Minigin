#include "MiniginPCH.h"
#include "PlotComponent.h"

#include "Minigin.h"

void PlotComponent::Update()
{


}

void PlotComponent::Render()
{
	ImGui::Begin(m_WindowName, nullptr, ImGuiWindowFlags_AlwaysAutoResize);



	for (size_t i = 0; i < m_Graphs.size(); i++)
	{
		ImGui::InputInt("# samples ", &m_Samples);
		if (ImGui::Button("Trash the cache"))
		{
			m_DisplayGraphs[i] = true;
			std::cout << m_Samples;


		}


		ImGui::Plot(m_Graphs[i].first, m_Graphs[i].second);
	}



	ImGui::End();
}
void PlotComponent::AddGraph(std::pair<const char*, ImGui::PlotConfig> graphData)
{
	m_Graphs.push_back(graphData); // make config here
	m_DisplayGraphs.push_back(false);

}
void PlotComponent::AddGraph(const char* name)
{
	auto p = std::make_pair(name, ImGui::PlotConfig());
	m_Graphs.push_back(p);
	m_DisplayGraphs.push_back(false);

}
void PlotComponent::UpdateGraph(int idx, ImGui::PlotConfig graphData)
{
	m_Graphs.at(idx).second = graphData;
}
void PlotComponent::SetEngine(dae::Minigin* min)
{
	m_Engine = min;
}
void PlotComponent::SetWindowName(const char* name)
{
	m_WindowName = name;
}


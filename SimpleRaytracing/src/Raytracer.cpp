#include "RayTracer.h"

void ExampleLayer::OnUIRender()
{
	ImGui::Begin("Settings");
	ImGui::Text("Last Render: %0.3fms", m_lastRenderTime);
	ImGui::End();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
	ImGui::Begin("Viewport");

	m_viewportWidth = ImGui::GetContentRegionAvail().x;
	m_viewportHeight = ImGui::GetContentRegionAvail().y;

	auto image = m_renderer.GetFinalImage();
	if (image)
	{
		ImGui::Image(image->GetDescriptorSet(), { (float)image->GetWidth(), (float)image->GetHeight() },
			ImVec2(0, 1), ImVec2(1 ,0));
	}

	ImGui::End();
	ImGui::PopStyleVar();

	Render();
}

void ExampleLayer::Render()
{
	Walnut::Timer timer;

	m_renderer.OnResize(m_viewportWidth, m_viewportHeight);
	m_renderer.Render();

	m_lastRenderTime = timer.ElapsedMillis();
}

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Simple Raytracer";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))
				{
					app->Close();
				}
				ImGui::EndMenu();
			}
		});
	return app;
}

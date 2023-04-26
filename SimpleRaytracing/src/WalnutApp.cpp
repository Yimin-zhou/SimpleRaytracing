#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"

using namespace Walnut;

class ExampleLayer : public Walnut::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Settings");
		if (ImGui::Button("Render"))
		{
			Render();
		}
		ImGui::End();

		ImGui::Begin("Viewport");

		m_viewportWidth = ImGui::GetContentRegionAvail().x;
		m_viewportHeight = ImGui::GetContentRegionAvail().y;

		ImGui::ShowDemoWindow();
	}

	void Render()
	{
		if (!m_image || m_viewportWidth != m_image->GetWidth() 
			|| m_viewportHeight != m_image->GetHeight())
		{
			m_image = std::make_shared<Image>(m_viewportWidth, m_viewportHeight, ImageFormat::RGBA);
			delete[] m_imageData;

			for (uint32_t i = 0; i < m_viewportWidth * m_viewportHeight; i++)
			{
				m_imageData[i] = 0xFF0000FF;
			}

		}
	}

private: 
	std::shared_ptr<Image> m_image;
	uint32_t* m_imageData = nullptr;

	uint32_t m_viewportWidth;
	uint32_t m_viewportHeight;
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Walnut Example";

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
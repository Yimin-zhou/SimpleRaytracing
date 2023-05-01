#include "Renderer.h"

Renderer::~Renderer()
{

}


Renderer::Renderer()
{

}


void Renderer::OnResize(uint32_t width, uint32_t height)
{
	if (m_finalImage)
	{
		if (m_finalImage->GetWidth() == width && m_finalImage->GetHeight() == height) return;
		m_finalImage->Resize(width, height);
	}
	else
	{
		m_finalImage = std::make_shared<Walnut::Image>(width, height, Walnut::ImageFormat::RGBA);
	}

	delete[] m_imageData;
	m_imageData = new uint32_t[width * height];
}

void Renderer::Render()
{
	for (uint32_t i = 0; i < m_finalImage->GetWidth() * m_finalImage->GetHeight(); i++)
	{
		m_imageData[i] = Walnut::Random::UInt(); // abgr
		m_imageData[i] |= 0xff000000;
	}
	m_finalImage->SetData(m_imageData);
}
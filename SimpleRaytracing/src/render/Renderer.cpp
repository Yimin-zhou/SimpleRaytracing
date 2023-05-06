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
	for (uint32_t y = 0; y < m_finalImage->GetHeight(); y++)
	{
		for (uint32_t x = 0; x < m_finalImage->GetWidth(); x++)
		{
			glm::vec2 coord = { (float)x / m_finalImage->GetWidth(), (float)y / m_finalImage->GetHeight() };
			coord = coord * 2.0f - 1.0f;
			m_imageData[x + y * m_finalImage->GetWidth()] = perPixel(coord);; // abgr
		}
	}
	m_finalImage->SetData(m_imageData);
}

uint32_t Renderer::perPixel(glm::vec2 coord)
{
	glm::vec3 ratOrigin = glm::vec3(0.0f, 0.0f, 2.0f); // a
	glm::vec3 rayDirection = glm::normalize(glm::vec3(coord.x, coord.y, -1.0f)); // b
	float radius = 0.5f; // r

	// for a 2d circle
	// A = ray origin
	// B = ray direction
	// r = radius
	// t = hit distance
	// (B.x^2 + B.y^2 + B.z^2)t^2 + 2(A.xB.x + A.yB.y + A.zB.z)t + (A.x^2 + A.y^2 + A.z^2 - r^2) = 0

	float a = glm::dot(rayDirection, rayDirection);
	float b = 2.0f * glm::dot(rayDirection, ratOrigin);
	float c = glm::dot(ratOrigin, ratOrigin) - radius * radius;

	// solve quadratic equation
	// (-b +- sqrt(b^2 - 4ac)) / 2a

	float discriminant = b * b - 4.0f * a * c;

	if (discriminant >= 0.0f)
	{
		return 0xffff00ff;
	}

	return 0xff000000;
}

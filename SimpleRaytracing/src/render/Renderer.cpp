#include "Renderer.h"

namespace Utils
{
	static uint32_t ConvertToRGBA(const glm::vec4& color)
	{
		glm::vec4 clampedColor = glm::clamp(color, 0.0f, 1.0f);
		uint8_t r = (uint8_t)(clampedColor.r * 255.0f);
		uint8_t g = (uint8_t)(clampedColor.g * 255.0f);
		uint8_t b = (uint8_t)(clampedColor.b * 255.0f);
		uint8_t a = (uint8_t)(clampedColor.a * 255.0f);
		return (uint32_t)((a << 24) | (b << 16) | (g << 8) | r); // abgr, little endian, convert to bits
	}
}

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
			m_imageData[x + y * m_finalImage->GetWidth()] = Utils::ConvertToRGBA(perPixel(coord)); // abgr
		}
	}
	m_finalImage->SetData(m_imageData);
}

glm::vec4 Renderer::perPixel(glm::vec2 coord)
{
	float aspectRatio = (float)m_finalImage->GetWidth() / m_finalImage->GetHeight();
	coord.x *= aspectRatio;

	glm::vec3 rayOrigin = glm::vec3(0.0f, 0.0f, 2.0f); // a
	glm::vec3 rayDirection = glm::vec3(coord.x, coord.y, -1.0f); // b
	float radius = 0.5f; // r

	// for a 2d circle
	// A = ray origin
	// B = ray direction
	// r = radius
	// t = hit distance
	// (B.x^2 + B.y^2 + B.z^2)t^2 + 2(A.xB.x + A.yB.y + A.zB.z)t + (A.x^2 + A.y^2 + A.z^2 - r^2) = 0

	float a = glm::dot(rayDirection, rayDirection);
	float b = 2.0f * glm::dot(rayDirection, rayOrigin);
	float c = glm::dot(rayOrigin, rayOrigin) - radius * radius;

	// solve quadratic equation and discriminant
	// (-b +- sqrt(b^2 - 4ac)) / 2a

	float discriminant = b * b - 4.0f * a * c;
	if (discriminant <  0.0f)
	{
		return glm::vec4(0, 0, 0, 1);
	}

	// solve for t0,1 (hit distance)
	float t0 = (-b - sqrt(discriminant)) / (2.0f * a);
	float t1 = (-b + sqrt(discriminant)) / (2.0f * a);

	// closest hit point, a is definately positive, so t0 is always the closest hit point
	glm::vec3 hitPoint = rayOrigin + rayDirection * t0;
	glm::vec3 normal = glm::normalize(hitPoint) * 0.5f + 0.5f;

	glm::vec3 lightDir = glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f));

	glm::vec4 sphereColor = glm::vec4(0.3f, 0.3f, 1.0f, 1.0f);

	glm::vec3 diffuse = sphereColor * glm::max(glm::dot(normal, lightDir), 0.0f);

	sphereColor = glm::pow(glm::vec4(diffuse, 1.0f), glm::vec4(1.0f/2.2f));

	return sphereColor;
}

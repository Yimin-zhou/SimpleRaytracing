#pragma once

#include "Walnut/Image.h"
#include "Walnut/Random.h"

#include <memory>

class Renderer
{
public:
	Renderer();
	~Renderer();

	void OnResize(uint32_t width, uint32_t height);
	void Render();

	std::shared_ptr<Walnut::Image> GetFinalImage() const { return m_finalImage; }

private:
	glm::vec4 perPixel(glm::vec2 coord);

private:
	std::shared_ptr<Walnut::Image> m_finalImage;
	uint32_t* m_imageData = nullptr;
};
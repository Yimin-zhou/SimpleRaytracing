#pragma once

#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"
#include "Walnut/Timer.h"

#include "render/Renderer.h"

class ExampleLayer : public Walnut::Layer
{
public:
	virtual void OnUIRender() override;

	void Render();

private:
	Renderer m_renderer;
	uint32_t* m_imageData = nullptr;

	uint32_t m_viewportWidth;
	uint32_t m_viewportHeight;

	float m_lastRenderTime = 0.0f;
};
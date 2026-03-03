#include "TextComponent.h"
#include "Renderer.h"
#include <SDL3_ttf/SDL_ttf.h>

dae::TextComponent::TextComponent(GameObject* pOwner)
	: BaseComponent(pOwner)
{
}

dae::TextComponent::~TextComponent() = default;

void dae::TextComponent::Update(float) {}

void dae::TextComponent::FixedUpdate(float) {}

void dae::TextComponent::Render()
{
	if (m_NeedsUpdate && m_Font != nullptr)
	{
		const SDL_Color color = { 255, 255, 255, 255 }; 
		auto surface = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), 0, color);

		if (surface)
		{
			auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surface);
			SDL_DestroySurface(surface);

			if (texture)
			{
				m_pTextTexture = std::make_unique<Texture2D>(texture);
			}
		}
		m_NeedsUpdate = false;
	}

	if (m_pTextTexture)
	{
		const auto& pos = m_pOwner->GetTransform().GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTextTexture, pos.x, pos.y);
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	if (m_Text != text)
	{
		m_Text = text;
		m_NeedsUpdate = true;
	}
}

void dae::TextComponent::SetFont(std::shared_ptr<Font> pFont)
{
	m_Font = pFont;
}

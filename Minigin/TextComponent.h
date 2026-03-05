#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "Font.h"
#include <memory>
#include "Texture2D.h"

namespace dae
{
	class GameObject;
	class TextComponent final : public BaseComponent
	{
	public:

		TextComponent(GameObject* pOwner);
		virtual ~TextComponent();
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		virtual void Update(float elapsedSec);
		virtual void FixedUpdate(float elapsedSec);
		virtual void Render();

		void SetText(const std::string& text);
		void SetFont(std::shared_ptr<Font> pFont);

	private:

		std::string m_Text;
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<Texture2D> m_pTextTexture;
		bool m_NeedsUpdate{ true };
	};
}
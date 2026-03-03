#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include <memory>

namespace dae
{
	class GameObject;
	class FPSComponent final : public BaseComponent
	{
	public:

		FPSComponent(GameObject* pOwner);
		virtual ~FPSComponent();
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		virtual void Update(float elapsedSec);
		virtual void FixedUpdate(float elapsedSec);
		virtual void Render();

	private:
		float m_Interval{ 0.5f };
		float m_AccuTime{ 0.f };
		int m_FrameCount{ 0 };
	};
}
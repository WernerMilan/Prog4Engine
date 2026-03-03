#pragma once
#include "GameObject.h"
#include <memory>

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:

		BaseComponent(GameObject* pOwner);
		virtual ~BaseComponent();
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Update(float elapsedSec);
		virtual void FixedUpdate(float elapsedSec);
		virtual void Render();

		bool m_IsMarkedForRemoval;

	protected:

		std::unique_ptr<GameObject> m_pOwner;
	};
}
#pragma once
#include <string>
#include <memory>
#include <algorithm>
#include "Transform.h"
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class BaseComponent;
	class GameObject 
	{
		std::vector<std::unique_ptr<BaseComponent>> m_pComponents{};
		Transform m_transform{};
		std::shared_ptr<Texture2D> m_texture{};

	public:
		virtual void AddComponent(std::unique_ptr<BaseComponent> pComponent);
		virtual void RemoveComponent(const BaseComponent& component);
		template <typename ComponentType>
		ComponentType* GetComponent();

		template <typename ComponentType>
		bool HasComponent() const;

		virtual void Update(float deltaTime);
		virtual void FixedUpdate(float deltaTime);
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		const Transform& GetTransform() const;

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	};

	template<typename ComponentType>
	inline ComponentType* GameObject::GetComponent()
	{
		for (const auto& component : m_pComponents)
		{
			ComponentType* result = dynamic_cast<ComponentType*>(component.get());
			if (result != nullptr)
			{
				return result;
			}
		}
		return nullptr;
	}

	template<typename ComponentType>
	inline bool GameObject::HasComponent() const
	{
		return std::any_of(m_pComponents.begin(), m_pComponents.end(),
			[](const std::unique_ptr<BaseComponent>& ptr) {
				return dynamic_cast<ComponentType*>(ptr.get()) != nullptr;
			});
	}
}

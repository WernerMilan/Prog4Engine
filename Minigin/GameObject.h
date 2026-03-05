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
		Transform m_Transform{};
		std::shared_ptr<Texture2D> m_texture{};
		bool m_MarkedForDeletion{};
		GameObject* m_Parent{};
		bool m_PositionIsDirty{false};
		glm::vec3 m_LocalPosition{};
		glm::vec3 m_WorldPosition{};

	public:
		virtual void AddComponent(std::unique_ptr<BaseComponent> pComponent);
		virtual void RemoveComponent(const BaseComponent& component);
		template <typename ComponentType>
		ComponentType* GetComponent();
		template <typename ComponentType>
		bool HasComponent() const;

		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);

		bool IsChild(GameObject* parent);
		void SetPositionDirty();

		void SetParent(GameObject* parent, bool keepWorldPosition);
		void SetLocalPosition(const glm::vec3& pos);

		const glm::vec3& GetWorldPosition();
		void UpdateWorldPosition();

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

		bool IsMarkedForDeletion() const;
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

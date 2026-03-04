#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <algorithm>

dae::GameObject::~GameObject() = default;

bool dae::GameObject::IsMarkedForDeletion() const
{
	return m_MarkedForDeletion;
}

void dae::GameObject::AddComponent(std::unique_ptr<BaseComponent> pComponent)
{
	m_pComponents.emplace_back(std::move(pComponent));
}

void dae::GameObject::RemoveComponent(const BaseComponent& component)
{
	m_pComponents.erase(
		std::remove_if(m_pComponents.begin(),
			m_pComponents.end(),
			[&component](const auto& ptr)
			{
				return ptr.get() == &component;
			}),
		m_pComponents.end());
}

void dae::GameObject::Update(float deltaTime)
{
	for (auto& component : m_pComponents)
	{
		component->Update(deltaTime);
	}
}

void dae::GameObject::FixedUpdate(float deltaTime)
{
	for (auto& component : m_pComponents)
	{
		component->FixedUpdate(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	const auto& pos = m_transform.GetPosition();

	if (m_texture)
	{
		Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
	}

	for (const auto& component : m_pComponents)
	{
		component->Render();
	}
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

const dae::Transform& dae::GameObject::GetTransform() const
{
	return m_transform;
}

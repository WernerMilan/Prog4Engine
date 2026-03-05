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

void dae::GameObject::AddChild(GameObject*)
{
}

void dae::GameObject::RemoveChild(GameObject*)
{
}

bool dae::GameObject::IsChild(GameObject* parent)
{
	if(parent == nullptr)
	{
		return false;
	}
	return true;
}

void dae::GameObject::SetPositionDirty()
{
	m_PositionIsDirty = true;
}

void dae::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	if (IsChild(parent) || parent == this || m_Parent == parent)
	{
		return;
	}
	if (parent == nullptr)
	{
		SetLocalPosition(GetWorldPosition());
	}
	else
	{
		if (keepWorldPosition)
			SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
		SetPositionDirty();
	}
	if (m_Parent) m_Parent->RemoveChild(this);
	m_Parent = parent;
	if (m_Parent) m_Parent->AddChild(this);
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPosition = pos;
	SetPositionDirty();
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	if (m_PositionIsDirty)
		UpdateWorldPosition();
	return m_WorldPosition;
}
void dae::GameObject::UpdateWorldPosition()
{
	if (m_PositionIsDirty)
	{
		if (m_Parent == nullptr)
			m_WorldPosition = m_LocalPosition;
		else
			m_WorldPosition = m_Parent->GetWorldPosition() + m_LocalPosition;
	}
	m_PositionIsDirty = false;
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
	const auto& pos = m_Transform.GetPosition();

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
	m_Transform.SetPosition(x, y, 0.0f);
}

const dae::Transform& dae::GameObject::GetTransform() const
{
	return m_Transform;
}

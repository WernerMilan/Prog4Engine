#include "BaseComponent.h"

dae::BaseComponent::BaseComponent(GameObject* pOwner)
	: m_pOwner{ pOwner }
	, m_IsMarkedForRemoval{false}
{
}

dae::BaseComponent::~BaseComponent() = default;

void dae::BaseComponent::Update(float){}

void dae::BaseComponent::FixedUpdate(float){}

void dae::BaseComponent::Render(){}

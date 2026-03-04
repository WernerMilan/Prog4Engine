#include <algorithm>
#include "Scene.h"

using namespace dae;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	assert(object != nullptr && "Cannot add a null GameObject to the scene.");
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(const GameObject& object)
{
	m_objects.erase(
		std::remove_if(
			m_objects.begin(),
			m_objects.end(),
			[&object](const auto& ptr) { return ptr.get() == &object; }
		),
		m_objects.end()
	);
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update(float deltaTime)
{
	for (auto& object : m_objects)
	{
		object->Update(deltaTime);
	}

	CleanUpMarkedObjects();
}

void dae::Scene::FixedUpdate(float deltaTime)
{
	for (auto& object : m_objects)
	{
		object->FixedUpdate(deltaTime);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void dae::Scene::CleanUpMarkedObjects()
{
	for (int objIdx; objIdx < m_objects.size(); ++objIdx)
	{
		if (m_objects[objIdx]->IsMarkedForDeletion())
		{
			m_objects.erase(m_objects.begin() + objIdx);
		}
	}
}


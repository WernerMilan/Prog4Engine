#include "FPSComponent.h"
#include "TextComponent.h"
#include <iomanip>
#include <sstream>

dae::FPSComponent::FPSComponent(GameObject* pOwner)
    : BaseComponent(pOwner)
{
}

dae::FPSComponent::~FPSComponent() = default;

void dae::FPSComponent::Update(float deltaTime)
{
    m_AccuTime += deltaTime;
    m_FrameCount++;

    if (m_AccuTime >= m_Interval) {
        const float fps = static_cast<float>(m_FrameCount) / m_AccuTime;

        auto textComp = m_pOwner->GetComponent<TextComponent>();
        if (textComp) {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(1) << fps << " FPS";
            textComp->SetText(ss.str());
        }

        m_FrameCount = 0;
        m_AccuTime -= m_Interval;
    }
}

void dae::FPSComponent::FixedUpdate(float) {}

void dae::FPSComponent::Render() {}

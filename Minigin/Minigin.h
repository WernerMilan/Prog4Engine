#pragma once
#include <string>
#include <functional>
#include <filesystem>

namespace dae
{
	class Minigin final
	{
	private:

		bool m_Quit{};
		std::chrono::steady_clock::time_point m_LastTime{ std::chrono::high_resolution_clock::now() };
		const float m_FixedTimeStep{ 1.0f / 30.0f };
		const int m_MsPerFrame{ 1000 / 144};
		float m_Lag{ 0.0f };

	public:

		explicit Minigin(const std::filesystem::path& dataPath);
		~Minigin();
		void Run(const std::function<void()>& load);
		void RunOneFrame();

		Minigin(const Minigin& other) = delete;
		Minigin(Minigin&& other) = delete;
		Minigin& operator=(const Minigin& other) = delete;
		Minigin& operator=(Minigin&& other) = delete;

	};
}
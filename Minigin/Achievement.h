#pragma once
class Achievement
{
public:
	Achievement() = default;
	~Achievement() = default;
	Achievement(const Achievement& other) = delete;
	Achievement(Achievement&& other) noexcept = delete;
	Achievement& operator=(const Achievement& other) = delete;
	Achievement& operator=(Achievement&& other) noexcept = delete;

	const bool IsUnlocked() { return m_Unlocked; }
	void Unlock() { m_Unlocked = true; }
private:
	bool m_Unlocked;
};
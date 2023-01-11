#pragma once
#include <memory>

namespace ActionGame
{
	/*
	* @brief	�N���A�����ɕK�v�ȃp�����[�^��񋟂���
	*/
	class ClearTermProvider
	{
	private:
		float m_DivisionCurrentTime;
		size_t m_EnemyCount;
		size_t m_EnemyMaxCount;
		size_t m_BossCount;
		size_t m_BossMaxCount;
	public:

		ClearTermProvider():
			m_DivisionCurrentTime(0.0f),
			m_EnemyCount(0),
			m_EnemyMaxCount(0),
			m_BossCount(0),
			m_BossMaxCount(0)
		{
			
		}
		~ClearTermProvider() {
		}

		/**
		 * @brief		���ݎ��Ԏ擾
		 */
		float GetDivisionTime() const noexcept 
		{
			return m_DivisionCurrentTime;
		}

		/**
		 * @brief		���ݎ��Ԑݒ�
		 */
		void SetDivisionTime(float time) noexcept
		{
			m_DivisionCurrentTime = time;
		}

		void SetEnemyCount(size_t count) noexcept
		{
			m_EnemyCount = count;
		}

		void SetBossCount(size_t count) noexcept
		{
			m_BossCount = count;
		}

		void SetEnemyMaxCount(size_t count) noexcept
		{
			m_EnemyMaxCount = count;
		}

		void SetBossMaxCount(size_t count) noexcept
		{
			m_BossMaxCount = count;
		}

		/**
		 * @brief		�G���擾
		 */
		size_t GetEnemyCount() const noexcept
		{
			return m_EnemyCount;
		}

		/**
		 * @brief		�G�ő吔�擾
		 */
		size_t GetEnemyMaxCount() const noexcept
		{
			return m_EnemyMaxCount;
		}

		/**
		 * @brief		�{�X���擾
		 */
		size_t GetBossCount() const noexcept
		{
			return m_EnemyMaxCount;
		}

		/**
		 * @brief		�{�X�ő吔�擾
		 */
		size_t GetBossMaxCount() const noexcept
		{
			return m_EnemyMaxCount;
		}
		
	};

	using ClearTermProviderPtr = std::shared_ptr<ClearTermProvider>;
}
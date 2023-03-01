#pragma once
#include <memory>

namespace ClearTerm
{
	/*
	* @brief	�N���A�����ɕK�v�ȃp�����[�^��񋟂���
	*/
	class CProvider
	{
	private:
		float divisionCurrentTime_;
		size_t enemyCount_;
		size_t enemyMaxCount_;
		size_t bossCount_;
		size_t bossMaxCount_;
	public:

		CProvider():
			divisionCurrentTime_(0.0f),
			enemyCount_(0),
			enemyMaxCount_(0),
			bossCount_(0),
			bossMaxCount_(0)
		{
			
		}
		~CProvider() {
		}

		/**
		 * @brief		���ݎ��Ԏ擾
		 */
		float GetDivisionTime() const noexcept 
		{
			return divisionCurrentTime_;
		}

		/**
		 * @brief		���ݎ��Ԑݒ�
		 */
		void SetDivisionTime(float time) noexcept
		{
			divisionCurrentTime_ = time;
		}

		void SetEnemyCount(size_t count) noexcept
		{
			enemyCount_ = count;
		}

		void SetBossCount(size_t count) noexcept
		{
			bossCount_ = count;
		}

		void SetEnemyMaxCount(size_t count) noexcept
		{
			enemyMaxCount_ = count;
		}

		void SetBossMaxCount(size_t count) noexcept
		{
			bossMaxCount_ = count;
		}

		/**
		 * @brief		�G���擾
		 */
		size_t GetEnemyCount() const noexcept
		{
			return enemyCount_;
		}

		/**
		 * @brief		�G�ő吔�擾
		 */
		size_t GetEnemyMaxCount() const noexcept
		{
			return enemyMaxCount_;
		}

		/**
		 * @brief		�{�X���擾
		 */
		size_t GetBossCount() const noexcept
		{
			return bossCount_;
		}

		/**
		 * @brief		�{�X�ő吔�擾
		 */
		size_t GetBossMaxCount() const noexcept
		{
			return bossMaxCount_;
		}
		
	};

	using ProviderPtr = std::shared_ptr<CProvider>;
}
#pragma once

#include "GameDefine.h"
#include "ResourceManager.h"

namespace Sample
{
	/**
	 * @brief		�v���C���[CTUI
	 */
	class SkillUIRender
	{
	private:

		std::shared_ptr<CTexture>			m_pSKillFrame;
		std::shared_ptr<CTexture>			m_pUsedSKillFrame;

		float								m_CT;
		float								m_MaxCT;

		Vector2								m_Offset;
		Vector2								m_Size;
		Vector2								m_Position;

		CShader								m_Shader;
		CShaderBind_SpriteBase				m_ShaderBind;

	public:
		/**
		 * @brief		�R���X�g���N�^
		 */
		SkillUIRender()
			: m_CT(0.0f)
			, m_MaxCT(0.0f)
			, m_Offset(0,0)
			, m_Size(0, 0)
			, m_Position(0, 0)
		{

		}

		/**
		 * @brief		�f�X�g���N�^
		 */
		~SkillUIRender() {
		}


		void Initialize(std::string key)
		{
			m_pSKillFrame = Sample::ResourceManager<CTexture>::GetInstance().GetResource(key);
			m_pUsedSKillFrame = Sample::ResourceManager<CTexture>::GetInstance().GetResource(key);

			m_Offset = Vector2(0, 0);
			m_Size = Vector2(1, 1);
			m_Shader.Load("UI/Shader.hlsl");
			m_ShaderBind.Create(&m_Shader);
			CGraphicsUtilities::SetScreenSize(g_pGraphics->GetTargetWidth(), g_pGraphics->GetTargetHeight(), &m_ShaderBind);
		}


		void SetCT(float  ct)
		{
			m_CT = ct;
		}

		void SetMaxCT(float ct)
		{
			m_MaxCT = ct;
		}

		/**
		 * @brief		�Ǘ�HP������
		 */
		void Reset() noexcept {

		}

		/**
		 * @brief		�Ǘ��X�R�A������
		 */
		void Render(float x) {

			float percent = m_CT / m_MaxCT;
			//�`�悵���^�[�Q�b�g���e�N�X�`���Ƃ��ĉ�ʂɕ`�悷��
			CTexture* tex = m_pUsedSKillFrame.get();
			CGraphicsUtilities::RenderTexture(20, 20, tex, &m_Shader, &m_ShaderBind);

			m_pUsedSKillFrame->Render(g_pGraphics->GetTargetWidth() * 0.4f + x, g_pGraphics->GetTargetHeight() * 0.9f, MOF_ARGB(255, 10, 10, 10), TEXALIGN_BOTTOMCENTER);

			CRectangle rect(0, m_pUsedSKillFrame->GetHeight() * percent, m_pUsedSKillFrame->GetWidth(), m_pUsedSKillFrame->GetHeight());
			m_pSKillFrame->Render(g_pGraphics->GetTargetWidth() * 0.4f + x, g_pGraphics->GetTargetHeight() * 0.9f, rect, TEXALIGN_BOTTOMCENTER);

			if (m_CT > 0.0f)
			{
				if (m_CT > 1.0f)
				{
					CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() * 0.4f - 5 + x, g_pGraphics->GetTargetHeight() * 0.9f - m_pUsedSKillFrame->GetHeight() * 0.5f, "%.0f", m_CT);
				}
				else
				{
					CGraphicsUtilities::RenderString(g_pGraphics->GetTargetWidth() * 0.4f - 5 + x, g_pGraphics->GetTargetHeight() * 0.9f - m_pUsedSKillFrame->GetHeight() * 0.5f, "%.1f", m_CT);
				}
			}
			
		}

		void Release(void) {
			m_pSKillFrame.reset();
			m_Shader.Release();
			m_ShaderBind.Release();
		}
	};
	
	using SkillUIRenderPtr = std::shared_ptr<SkillUIRender>;
}

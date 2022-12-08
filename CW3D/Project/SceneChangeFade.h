#pragma once
#include "SceneChangeEffect.h"
#include "Common.h"

namespace ActionGame
{
    class SceneChangeFade : public ISceneChangeEffect
    {
    private:
        float   m_CurrentTime;
        float   m_EndTime;
        int     m_Alpha;
    public:
        SceneChangeFade(float endTime);
        virtual ~SceneChangeFade() = default;
        /**
         * @brief		�V�[���ύX���ʍX�V
         */
        void Update() override;
        /**
         * @brief		�V�[���ύX���ʕ`��
         */
        void Render(ScenePtr& prev,ScenePtr& current) override;

        /**
         * @brief		�V�[���ύX���ʏI������
         */
        virtual bool IsEnd() const noexcept;
    };    
}



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
        float   m_StartTime;
        float   m_DurationTime;
        float   m_AllTime;
        int     m_Alpha;
        bool    m_HalfPointFlg;
    public:
        /*
        * @brief    �R���X�g���N�^
        */
        SceneChangeFade(float startTime,float durationTime,float endTime);
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
        virtual bool IsEnd() const noexcept override;

        /**
         * @brief		���Ԃ܂Ői�񂾂��H
         */
        virtual bool IsHalfPoint() const noexcept override;
    };    
}



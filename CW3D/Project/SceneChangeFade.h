#pragma once
#include "SceneChangeEffect.h"
#include "Common.h"

namespace Scene
{
    class SceneChangeFade : public ISceneChangeEffect
    {
    private:
        float   currentTime_;
        float   endTime_;
        float   startTime_;
        float   durationTime_;
        float   totalTime_;
        int     alpha_;
        bool    isHalfPoint_;
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
        void Render(const ScenePtr& prev,const ScenePtr& current) override;

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



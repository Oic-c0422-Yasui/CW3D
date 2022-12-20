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
        * @brief    コンストラクタ
        */
        SceneChangeFade(float startTime,float durationTime,float endTime);
        virtual ~SceneChangeFade() = default;
        /**
         * @brief		シーン変更効果更新
         */
        void Update() override;
        /**
         * @brief		シーン変更効果描画
         */
        void Render(ScenePtr& prev,ScenePtr& current) override;

        /**
         * @brief		シーン変更効果終了判定
         */
        virtual bool IsEnd() const noexcept override;

        /**
         * @brief		中間まで進んだか？
         */
        virtual bool IsHalfPoint() const noexcept override;
    };    
}



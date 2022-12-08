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
        virtual bool IsEnd() const noexcept;
    };    
}



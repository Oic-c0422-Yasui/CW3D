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
        void Render(const ScenePtr& prev,const ScenePtr& current) override;

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



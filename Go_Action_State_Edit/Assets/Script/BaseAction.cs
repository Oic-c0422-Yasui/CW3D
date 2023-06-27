
using UnityEngine;

public class BaseAction : ScriptableObject
{
    //アニメーションパラメータ
    [System.Serializable]
    public class AnimParam
    {
        public string name;
        public float startTime;
        public float speed;
        public float tTime;
        public bool isLoop;
    };

    //基底パラメータ
    [System.Serializable]
    public class BaseParam
    {
        public AnimParam anim;

    };
   
}

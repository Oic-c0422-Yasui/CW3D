
using UnityEngine;

public class BaseAction : ScriptableObject
{
    //�A�j���[�V�����p�����[�^
    [System.Serializable]
    public class AnimParam
    {
        public string name;
        public float startTime;
        public float speed;
        public float tTime;
        public bool isLoop;
    };

    //���p�����[�^
    [System.Serializable]
    public class BaseParam
    {
        public AnimParam anim;

    };
   
}

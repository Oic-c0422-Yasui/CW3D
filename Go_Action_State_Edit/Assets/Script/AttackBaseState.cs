
using UnityEngine;

public class AttackBaseState : ScriptableObject
{

    //�G�t�F�N�g�p�����[�^
    [System.Serializable]
    public class EffectParam
    {
        public string name;
        public Vector3 offset;
        public Vector3 scale;
        public Vector3 rotate;
        public float speed;
    };

    //�d�̓p�����[�^
    [System.Serializable]
    public class GravityScale
    {
        public bool isEnable;
        public float time;
        public float startScale;
        public float endScale;
    };

    //��ꓖ���蔻��p�����[�^
    [System.Serializable]
    public class ColliderBase
    {
        public Vector3 offset;
        public float nextHitTime;
        public uint damage;
        public Vector3 knockBack;
        public bool isEnableCollider;
        [Range(0, 10)]
        public int armorBreakLevel;
        public float recieveUltGauge;
        public EffectParam damageEffect;
        public GravityScale gravityScale;
    };

    //AABB�����蔻��p�����[�^
    [System.Serializable]
    public class ColliderAABB : ColliderBase
    {
        public Vector3 size;
    };

    //OBB�����蔻��p�����[�^
    [System.Serializable]
    public class ColliderOBB : ColliderAABB
    {
        public Vector3 angle;
    };

    //���̓����蔻��p�����[�^
    [System.Serializable]
    public class ColliderSphere
    {
        public float radius;
    };

   
}

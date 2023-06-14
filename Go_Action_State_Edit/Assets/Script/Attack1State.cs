using UnityEngine;
using System.IO;

[CreateAssetMenu(fileName = "Attack1", menuName = "State/Attack1")]
public class Attack1State : AttackBaseState, IJsonWriter
{
    [System.Serializable]
    public struct Parameter
    {
        [Range(0, 10)]
        public uint            armorLevel;
        public uint            colliderStartFrameTime;
        public uint            colliderEndFrameTime;
        public float           nextInputFrameTime;
        public ColliderAABB    colliderParam;
        public EffectParam     effectParam;
    }

    public Parameter param;
    public void SaveJson()
    {
        SaveJsonUtil.SaveJson(OutPutType.State, this.name, param);
    }
}

using UnityEngine;

[CreateAssetMenu(fileName = "Attack1", menuName = "Action/Attack1")]
public class Attack1Action : BaseAction, IJsonWriter
{
    [System.Serializable]
    public struct Parameter
    {
        public Vector3 decelerate;
        public Vector3 velocity;
        public AnimParam anim;
    }

    public Parameter param;
    public void SaveJson()
    {
        SaveJsonUtil.SaveJson(OutPutType.Action, this.name, param);
    }
}

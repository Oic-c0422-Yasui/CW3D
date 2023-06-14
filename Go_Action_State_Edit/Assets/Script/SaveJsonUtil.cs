using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

public class SaveJsonUtil
{
    //Json‚É‘‚«o‚µ
    public static void SaveJson(in OutPutType type,
                                in string fileName,
                                in object param)
    {
        var dataPath = Application.dataPath + "/Json/" + type.ToString() + "/" + fileName + ".json";

        Debug.Log("•Û‘¶æF" + dataPath);

        //Json‘‚«o‚µ
        var writer = new StreamWriter(dataPath, false);
        var str = JsonUtility.ToJson(param);
        writer.WriteLine(str);
        writer.Flush();
        writer.Close();
    }
}

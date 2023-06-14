using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;

public class SaveJsonUtil
{
    //Jsonに書き出し
    public static void SaveJson(in OutPutType type,
                                in string fileName,
                                in object param)
    {
        var dataPath = Application.dataPath + "/Json/" + type.ToString() + "/" + fileName + ".json";

        Debug.Log("保存先：" + dataPath);

        //Json書き出し
        var writer = new StreamWriter(dataPath, false);
        var str = JsonUtility.ToJson(param);
        writer.WriteLine(str);
        writer.Flush();
        writer.Close();
    }
}

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using System.IO;

public class WriteMenu : MonoBehaviour
{

    [MenuItem("Creator/State/Json書き出し", false, 1)]
    static void OutputState()
    {

        //指定したディレクトリ内のすべてのファイル名を取得する
        const string directoryPath = "Assets/Parameters/State";

        OutPut(directoryPath);

    }

    [MenuItem("Creator/Action/Json書き出し", false, 1)]
    static void OutputAction()
    {

        //指定したディレクトリ内のすべてのファイル名を取得する
        const string directoryPath = "Assets/Parameters/Action";

        OutPut(directoryPath);

    }

    static private void OutPut(in string directoryPath)
    {

        var filePathArray = Directory.GetFiles(directoryPath, "*", SearchOption.AllDirectories);
        //IJsonWriterを継承しているスクリプタブルオブジェクトを取得し、
        //Jsonで保存する
        foreach (string filePath in filePathArray)
        {
            var asset = AssetDatabase.LoadAssetAtPath<ScriptableObject>(filePath) as IJsonWriter;
            if (asset != null)
            {
                asset.SaveJson();
            }
        }
    }


}

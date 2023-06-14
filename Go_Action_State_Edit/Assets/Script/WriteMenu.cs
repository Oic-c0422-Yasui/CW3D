using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;
using System.IO;

public class WriteMenu : MonoBehaviour
{

    [MenuItem("StateCreator/Json�����o��", false, 1)]
    static void OutputState()
    {

        //�w�肵���f�B���N�g�����̂��ׂẴt�@�C�������擾����
        const string directoryPath = "Assets/Parameters";
        var filePathArray = Directory.GetFiles (directoryPath, "*", SearchOption.AllDirectories);


        //IJsonWriter���p�����Ă���X�N���v�^�u���I�u�W�F�N�g���擾���A
        //Json�ŕۑ�����
        foreach(string filePath in filePathArray)
        {
            var asset = AssetDatabase.LoadAssetAtPath<ScriptableObject>(filePath) as IJsonWriter;
            if(asset != null)
            {
                asset.SaveJson();
            }
        }
        
    }


}

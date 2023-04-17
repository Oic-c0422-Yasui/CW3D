#pragma once

//メッセンジャーで送るメッセージ
enum GameMessageType
{
    UI_Visible,     //UI表示
    UI_Disable,     //UI非表示

    ChangeDevice_KeyBoard,      //デバイスをキーボードへ変更
    ChangeDevice_Controller,    //デバイスをコントローラーへ変更


    MessageCount
};
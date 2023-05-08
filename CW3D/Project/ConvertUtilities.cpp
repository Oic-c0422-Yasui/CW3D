#include "ConvertUtilities.h"


std::string MyUtil::UTF8toShiftJIS(const std::string& utf8)
{

	//Unicode�֕ϊ���̕����񒷂𓾂�
	int lenghtUnicode = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.size() + 1, NULL, 0);

	//�K�v�ȕ�����Unicode������̃o�b�t�@���m��
	wchar_t* bufUnicode = new wchar_t[lenghtUnicode];

	//UTF8����Unicode�֕ϊ�
	MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.size() + 1, bufUnicode, lenghtUnicode);

	//ShiftJIS�֕ϊ���̕����񒷂𓾂�
	int lengthSJis = WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, -1, NULL, 0, NULL, NULL);

	//�K�v�ȕ�����ShiftJIS������̃o�b�t�@���m��
	char* bufShiftJis = new char[lengthSJis];

	//Unicode����ShiftJIS�֕ϊ�
	WideCharToMultiByte(CP_THREAD_ACP, 0, bufUnicode, lenghtUnicode + 1, bufShiftJis, lengthSJis, NULL, NULL);

	std::string strSJis(bufShiftJis);

	delete bufUnicode;
	delete bufShiftJis;

	return strSJis;

}



std::u16string MyUtil::ConvertUTF8ToUTF16(const std::string& utf8)
{
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
	return convert.from_bytes(utf8);
}
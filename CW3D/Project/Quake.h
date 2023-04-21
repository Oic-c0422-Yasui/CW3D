#pragma once
#include "Common.h"

namespace ActionGame
{
	/*
	* @brief	—h‚ç‚·²
	*/
	enum class QaukeAxis
	{
		X,
		Y,
		XY
	};

	/*
	* @brief	U“®ƒpƒ‰ƒ[ƒ^
	*/
	struct QuakeParam
	{
		float power;	//—h‚ê•
		float frequent;	//—h‚êŠÔŠu
		float time;		//—h‚êŠÔ
	};
	/*
	* @brief	UI‚È‚Ç‚ğ—h‚ç‚·‚½‚ß‚ÌƒIƒtƒZƒbƒg‚ğì¬‚·‚é
	*/
	class CQuake
	{
	private:
		Vector2		offset_;
		QuakeParam	param_;
		float		currentTime_;
		bool		isQuake_;
	private:
		/*
		* @brief	U“®’l‚ğŒˆ‚ß‚é
		* @param	power —h‚ê•
		* @param	frequent —h‚êŠÔŠu
		* @param	time —h‚êŠÔ
		*/
		void Quake(float power, float frequent, float time) noexcept;
	public:
		CQuake();
		~CQuake();
		/*
		* @brief	‰Šú‰»
		* @param	power —h‚ê•
		* @param	frequent —h‚êŠÔŠu
		* @param	time —h‚êŠÔ
		*/
		void Initialize(float power, float frequent, float time);
		/*
		* @brief	—h‚êŠJn
		*/
		void StartQuake();
		
		/*
		* @brief	U“®’l‚ğ“K—p‚·‚é
		* @param	axis —h‚ç‚·²
		*/
		void EnableQuake(QaukeAxis axis);

		/*
		* @brief	—h‚êÀ•WƒIƒtƒZƒbƒg
		*/
		const Vector2& GetOffset() const noexcept;
	};
}



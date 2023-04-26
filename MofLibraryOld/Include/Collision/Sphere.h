/*************************************************************************//*!
					
					@file	Sphere.h
					@brief	球演算関連

															@author	CDW
															@date	2014.05.14
*//**************************************************************************/

//ONCE
#ifndef		__SPHERE__H__

#define		__SPHERE__H__

//INCLUDE
#include	"CollisionCommon.h"

namespace Mof {

	/*******************************//*!
	@brief	3D球構造体

			3D球を扱うための構造体。

	@author	CDW
	*//********************************/
	typedef struct MOFLIBRARY_API Sphere {
		union {
			struct {
				MofFloat		x;						//!<X位置
				MofFloat		y;						//!<Y位置
				MofFloat		z;						//!<Z位置
			};
			struct {
				Vector3Impl		Position;				//!<位置
			};
		};
		MofFloat			r;							//!<半径
		
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		Sphere();
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param[in]		cx			Ｘ座標
				@param[in]		cy			Ｙ座標
				@param[in]		cz			Ｚ座標
				@param[in]		cr			半径

				@return			None
		*//**************************************************************************/
		Sphere(MofFloat cx,MofFloat cy,MofFloat cz,MofFloat cr);
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param[in]		pos			座標
				@param[in]		r			半径

				@return			None
		*//**************************************************************************/
		Sphere(const Vector3& pos,MofFloat cr);
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param[in]		pv			座標

				@return			None
		*//**************************************************************************/
		Sphere(LPMofFloat pv);
		/*************************************************************************//*!
				@brief			コピーコンストラクタ
				@param[in]		pObj		コピー球

				@return			None
		*//**************************************************************************/
		Sphere(const Sphere& pObj);
		
		//----------------------------------------------------------------------------
		////Operator
		//----------------------------------------------------------------------------

		/*************************************************************************//*!
				@brief			floatキャスト<br>
								内部の座標をfloatポインタとしてそのまま返す。
		*//**************************************************************************/
		operator LPMofFloat ();
		/*************************************************************************//*!
				@brief			+=演算
		*//**************************************************************************/
		Sphere& operator += ( const Vector3& v );
		/*************************************************************************//*!
				@brief			+=演算
		*//**************************************************************************/
		Sphere& operator += ( const Sphere& v );
		/*************************************************************************//*!
				@brief			-=演算
		*//**************************************************************************/
		Sphere& operator -= ( const Vector3& v );
		/*************************************************************************//*!
				@brief			-=演算
		*//**************************************************************************/
		Sphere& operator -= ( const Sphere& v );
		/*************************************************************************//*!
				@brief			floatとの*=演算
		*//**************************************************************************/
		Sphere& operator *= ( const MofFloat v );
		/*************************************************************************//*!
				@brief			Vector3との*=演算
		*//**************************************************************************/
		Sphere& operator *= ( const Vector3& v );
		/*************************************************************************//*!
				@brief			Sphereとの*=演算
		*//**************************************************************************/
		Sphere& operator *= ( const Sphere& v );
		/*************************************************************************//*!
				@brief			Sphereとの*=演算
		*//**************************************************************************/
		Sphere& operator *= ( const Matrix44& v );
		/*************************************************************************//*!
				@brief			floatとの/=演算
		*//**************************************************************************/
		Sphere& operator /= ( const MofFloat v );
		/*************************************************************************//*!
				@brief			Vector3との/=演算
		*//**************************************************************************/
		Sphere& operator /= ( const Vector3& v );
		/*************************************************************************//*!
				@brief			Sphereとの/=演算
		*//**************************************************************************/
		Sphere& operator /= ( const Sphere& v );
		/*************************************************************************//*!
				@brief			Vector3との+演算
		*//**************************************************************************/
		Sphere operator + ( const Vector3& v ) const;
		/*************************************************************************//*!
				@brief			Sphereとの+演算
		*//**************************************************************************/
		Sphere operator + ( const Sphere& v ) const;
		/*************************************************************************//*!
				@brief			Vector3との+演算
		*//**************************************************************************/
		Sphere operator - ( const Vector3& v ) const;
		/*************************************************************************//*!
				@brief			Sphereとの-演算
		*//**************************************************************************/
		Sphere operator - ( const Sphere& v ) const;
		/*************************************************************************//*!
				@brief			floatとの*演算
		*//**************************************************************************/
		Sphere operator * ( const MofFloat v ) const;
		/*************************************************************************//*!
				@brief			Vector3との*演算
		*//**************************************************************************/
		Sphere operator * ( const Vector3& v ) const;
		/*************************************************************************//*!
				@brief			Matrix44との*演算
		*//**************************************************************************/
		Sphere operator * ( const Matrix44& v ) const;
		/*************************************************************************//*!
				@brief			Sphereとの*演算
		*//**************************************************************************/
		Sphere operator * ( const Sphere& v ) const;
		/*************************************************************************//*!
				@brief			floatとの/演算
		*//**************************************************************************/
		Sphere operator / ( const MofFloat v ) const;
		/*************************************************************************//*!
				@brief			Vector3との/演算
		*//**************************************************************************/
		Sphere operator / ( const Vector3& v ) const;
		/*************************************************************************//*!
				@brief			Sphereとの/演算
		*//**************************************************************************/
		Sphere operator / ( const Sphere& v ) const;
		/*************************************************************************//*!
				@brief			配列指定によるSphereメンバへのアクセス
		*//**************************************************************************/
		MofFloat& operator [] ( int i );
		/*************************************************************************//*!
				@brief			配列指定によるSphereメンバへのアクセス
		*//**************************************************************************/
		const MofFloat& operator [] ( int i ) const;
		/*************************************************************************//*!
				@brief			==判断
		*//**************************************************************************/
		bool operator == ( const Sphere& v ) const;
		/*************************************************************************//*!
				@brief			!=判断
		*//**************************************************************************/
		bool operator != ( const Sphere& v ) const;
		
	}Sphere;
	
	/*******************************//*!
	@brief	3D球演算クラス

			Sphere構造体を扱うためのスタティッククラス。

	@author	CDW
	*//********************************/
	class MOFLIBRARY_API CSphereUtilities {
	public:
		/*************************************************************************//*!
				@brief			あたり判定<br>
								指定したVector3（ポイント）が球の中に入っているかを判定する
				@param[in]		r			判定球
				@param[in]		px			判定X位置
				@param[in]		py			判定Y位置
				@param[in]		pz			判定Z位置

				@return			TRUE		球の中に点がある
								FALSE		球の範囲外
		*//**************************************************************************/
		static MofBool CollisionPoint(const Sphere& r,const MofFloat px,const MofFloat py,const MofFloat pz);
		/*************************************************************************//*!
				@brief			あたり判定<br>
								指定したVector3（ポイント）が球の中に入っているかを判定する
				@param[in]		r			判定球
				@param[in]		p			判定位置

				@return			TRUE		球の中に点がある
								FALSE		球の範囲外
		*//**************************************************************************/
		static MofBool CollisionPoint(const Sphere& r,const Vector3& p);
		/*************************************************************************//*!
				@brief			あたり判定<br>
								指定した二つのSphere（球）が接触しているかを判定する
				@param[in]		r1			判定球
				@param[in]		r2			判定球
				
				@return			TRUE		接触
								FALSE		範囲外
		*//**************************************************************************/
		static MofBool CollisionSphere(const Sphere& r1,const Sphere& r2);

	private:
		//作成を禁止する
		CSphereUtilities() = delete;
		CSphereUtilities(const CSphereUtilities& pObj) = delete;
	};


	/*******************************//*!
	@brief	3D球クラス

			3D球を扱うためのクラス。

	@author	CDW
	*//********************************/
	class MOFLIBRARY_API CSphere : public Sphere , public IMofBase {
	public:
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param			None

				@return			None
		*//**************************************************************************/
		CSphere();
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param[in]		cx			Ｘ座標
				@param[in]		cy			Ｙ座標
				@param[in]		cz			Ｚ座標
				@param[in]		cr			半径

				@return			None
		*//**************************************************************************/
		CSphere(MofFloat cx,MofFloat cy,MofFloat cz,MofFloat cr);
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param[in]		pos			座標
				@param[in]		cr			半径

				@return			None
		*//**************************************************************************/
		CSphere(const Vector3& pos,MofFloat cr);
		/*************************************************************************//*!
				@brief			コンストラクタ
				@param[in]		pv			座標

				@return			None
		*//**************************************************************************/
		CSphere(LPMofFloat pv);
		/*************************************************************************//*!
				@brief			コピーコンストラクタ
				@param[in]		pObj		コピー球

				@return			None
		*//**************************************************************************/
		CSphere(const Sphere& pObj);
		/*************************************************************************//*!
				@brief			コピーコンストラクタ
				@param[in]		pObj		コピー球

				@return			None
		*//**************************************************************************/
		CSphere(const CSphere& pObj);
		
		/*************************************************************************//*!
				@brief			移動<br>
								m移動する。
				@param[in]		m			移動量
				
				@return			None
		*//**************************************************************************/
		void Translation(const Vector3& m);
		/*************************************************************************//*!
				@brief			移動<br>
								posの位置に移動する。
				@param[in]		pos			位置
				
				@return			None
		*//**************************************************************************/
		void SetPosition(const Vector3& pos);

		/*************************************************************************//*!
				@brief			あたり判定<br>
								指定したVector3（ポイント）が球の中に入っているかを判定する
				@param[in]		px			判定X位置
				@param[in]		py			判定Y位置
				@param[in]		pz			判定Z位置

				@return			TRUE		球の中に点がある
								FALSE		球の範囲外
		*//**************************************************************************/
		MofBool CollisionPoint(const MofFloat px,const MofFloat py,const MofFloat pz) const;
		/*************************************************************************//*!
				@brief			あたり判定<br>
								指定したVector3（ポイント）が球の中に入っているかを判定する
				@param[in]		p			判定位置

				@return			TRUE		球の中に点がある
								FALSE		球の範囲外
		*//**************************************************************************/
		MofBool CollisionPoint(const Vector3& p) const;
		/*************************************************************************//*!
				@brief			あたり判定<br>
								指定したSphere（球）が接触しているかを判定する
				@param[in]		cx			判定Ｘ位置
				@param[in]		cy			判定Ｙ位置
				@param[in]		cz			判定Ｚ位置
				@param[in]		cr			判定半径
				
				@return			TRUE		接触
								FALSE		範囲外
		*//**************************************************************************/
		MofBool CollisionSphere(const MofFloat cx,const MofFloat cy,const MofFloat cz,const MofFloat cr) const;
		/*************************************************************************//*!
				@brief			あたり判定<br>
								指定したSphere（球）が接触しているかを判定する
				@param[in]		c			判定球
				
				@return			TRUE		接触
								FALSE		範囲外
		*//**************************************************************************/
		MofBool CollisionSphere(const Sphere& c) const;
		
		/*************************************************************************//*!
				@brief			あたり判定<br>
								指定したジオメトリと交差するかを判定する。
				@param[in]		pGeom		判定ジオメトリ

				@return			TRUE		接触あり
								FALSE		接触なし
		*//**************************************************************************/
		MofBool CollisionGeometry(LPGeometry pGeom) const;
		/*************************************************************************//*!
				@brief			あたり判定<br>
								指定したジオメトリと交差するかを判定する。<br>
								交差する場合、接触ポリゴンの情報をoutに格納する
				@param[in]		pGeom		判定ジオメトリ
				@param[out]		out			出力接触ポリゴン情報

				@return			TRUE		接触あり
								FALSE		接触なし
		*//**************************************************************************/
		MofBool CollisionGeometry(LPGeometry pGeom, COLLISIONOUTGEOMETRY& out) const;

		/*************************************************************************//*!
				@brief			あたり判定<br>
								指定したメッシュと交差するかを判定する。
				@param[in]		pGeom		判定メッシュ

				@return			TRUE		接触あり
								FALSE		接触なし
		*//**************************************************************************/
		MofBool CollisionMesh(LPMesh pMesh) const;
		/*************************************************************************//*!
				@brief			あたり判定<br>
								指定したメッシュと交差するかを判定する。<br>
								交差する場合、接触ジオメトリの情報をoutに格納する
				@param[in]		pGeom		判定メッシュ
				@param[out]		out			出力接触ポリゴン情報

				@return			TRUE		接触あり
								FALSE		接触なし
		*//**************************************************************************/
		MofBool CollisionMesh(LPMesh pMesh, COLLISIONOUTMESH& out) const;

		/*************************************************************************//*!
				@brief			あたり判定<br>
								指定したメッシュと交差するかを判定する。
				@param[in]		pGeom		判定メッシュ

				@return			TRUE		接触あり
								FALSE		接触なし
		*//**************************************************************************/
		MofBool CollisionMesh(LPMeshContainer pMesh) const;
		/*************************************************************************//*!
				@brief			あたり判定<br>
								指定したメッシュと交差するかを判定する。<br>
								交差する場合、接触ジオメトリの情報をoutに格納する
				@param[in]		pGeom		判定メッシュ
				@param[out]		out			出力接触ポリゴン情報

				@return			TRUE		接触あり
								FALSE		接触なし
		*//**************************************************************************/
		MofBool CollisionMesh(LPMeshContainer pMesh, COLLISIONOUTGEOMETRY& out) const;
		/*************************************************************************//*!
				@brief			あたり判定<br>
								指定したメッシュと交差するかを判定する。<br>
								交差する場合、接触ジオメトリの情報をoutに格納する
				@param[in]		pGeom		判定メッシュ
				@param[out]		out			出力接触ポリゴン情報

				@return			TRUE		接触あり
								FALSE		接触なし
		*//**************************************************************************/
		MofBool CollisionMesh(LPMeshContainer pMesh, COLLISIONOUTMESHCONTAINER& out) const;

		/*************************************************************************//*!
				@brief			数値の設定
				@param[in]		cx			Ｘ座標
				@param[in]		cy			Ｙ座標
				@param[in]		cz			Ｚ座標
				@param[in]		cr			半径

				@return			None
		*//**************************************************************************/
		void SetValue(MofFloat cx,MofFloat cy,MofFloat cz,MofFloat cr);

		//----------------------------------------------------------------------------
		////Get
		//----------------------------------------------------------------------------
		
		//----------------------------------------------------------------------------
		////Operator
		//----------------------------------------------------------------------------

		/*************************************************************************//*!
				@brief			代入
		*//**************************************************************************/
		CSphere& operator = ( const Sphere& v );

		//クラス基本定義
		MOF_LIBRARYCLASS_NOTEQUAL(CSphere,MOF_SPHERECLASS_ID);
	};

	//ポインタ置き換え
	typedef CSphere*			LPSphere;

	//INLINE INCLUDE
	#include	"Sphere.inl"

}

#endif

//[EOF]
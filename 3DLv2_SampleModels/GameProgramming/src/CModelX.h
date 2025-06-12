#ifndef CMODELX_H	//インクルードガード
#define CMODELX_H
#include <string>
#include <algorithm>	//toupper
#include <memory>		//smart pointer
#include <vector>		//vectorクラスのインクルード（動的配列）
#include "CMatrix.h"	//マトリクスクラスのインクルード
#include "CVector.h"
#include "CMyShader.h" //シェーダーのインクルード

using namespace std;

class CModelX;			// CModelXクラスの宣言
class CModelXFrame;		// CModelXFrameクラスの宣言
class CMesh;			// CMeshクラスの宣言
class CMaterial;		//マテリアルの宣言
class CSkinWeights;		//スキンウェイトクラス
class CAnimationSet;	//アニメーションセットクラス
class CAnimation;		//アニメーションクラス
class CAnimationKey;  //アニメーションキークラス

//配列のサイズ取得をマクロ化
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

/*
 CAnimationKey
 アニメーションキークラス
*/
class CAnimationKey {
	friend CAnimation;
	friend CAnimationSet;
	friend CModelX;
private:
	//時間
	float mTime;
	//行列
	CMatrix mMatrix;
};


/*
 CAnimation
 アニメーションクラス
*/
class CAnimation {
	friend CAnimationSet;
	friend CModelX;
public:
	CAnimation(CModelX* model);
	CAnimation()
		: mKeyNum(0)
		, mFrameIndex(0)
	{}

	~CAnimation();
private:
	int mKeyNum;	//キー数（時間数）
	//CAnimationKey* mpKey;	//キーの配列
	vector<CAnimationKey> mKeys;	//キーの配列
	string mFrameName;//フレーム名
	int mFrameIndex;	//フレーム番号
};

/*
 CAnimationSet
 アニメーションセット
*/
class CAnimationSet {
	friend CModelX;
public:
	float Time();
	float MaxTime();
	void AnimateMatrix(CModelX* model);
	vector<shared_ptr<CAnimation>>& Animations();

	void Time(float time);  //時間の設定
	void Weight(float weight);  //重みの設定

	CAnimationSet(CModelX* model);
	~CAnimationSet();
	CAnimationSet()
		: mTime(0.0f)
		, mWeight(0.0f)
		, mMaxTime(0.0f)
	{}

private:
	float mTime;	//現在時間
	float mWeight;	//重み
	float mMaxTime;	//最大時間

	//アニメーション
	vector<shared_ptr<CAnimation>> mAnimations;

	//アニメーションセット名
	string mName;
};

/*
 CSkinWeights
 スキンウェイトクラス
*/
class CSkinWeights {
	friend CModelX;
	friend CMesh;
	friend CMyShader;
public:
	CSkinWeights(CModelX* model);
	~CSkinWeights();
	const int& FrameIndex();
	const CMatrix& Offset();
private:
	string mFrameName;	//フレーム名
	int mFrameIndex;	//フレーム番号
	int mIndexNum;	//頂点番号数
	int* mpIndex;	//頂点番号配列
	float* mpWeight;	//頂点ウェイト配列
	CMatrix mOffset;	//オフセットマトリックス
};


//#define MODEL_FILE "res\\sample.blend.x"	//入力ファイル名 \は￥
#define MODEL_FILE "res\\ラグナ.x"	//入力ファイル名

//CMeshクラスの定義
class CMesh {
	friend CMyShader;
public:
	//頂点バッファの作成
	void CreateVertexBuffer();

	void AnimateVertex(CMatrix*);
	//頂点にアニメーション適用
	void AnimateVertex(CModelX* model);
	//スキンウェイトにフレーム番号を設定する
	void SetSkinWeightFrameIndex(CModelX* model);

	void Render();
	//コンストラクタ
	CMesh();
	//デストラクタ
	~CMesh();
	//読み込み処理
	void Init(CModelX* model);
private:
protected:
	//マテリアル毎の面数
	std::vector<int> mMaterialVertexCount;
	//頂点バッファ識別子
	GLuint	  mMyVertexBufferId;

	//テクスチャ座標データ
	float* mpTextureCoords;

	CVector* mpAnimateVertex;  //アニメーション用頂点
	CVector* mpAnimateNormal;  //アニメーション用法線
	//スキンウェイト
	std::vector<shared_ptr<CSkinWeights>> mSkinWeights;
	int mMaterialNum;	//マテリアル数
	int mMaterialIndexNum;//マテリアル番号数（面数）
	int* mpMaterialIndex;	  //マテリアル番号
	std::vector<shared_ptr<CMaterial>> mMaterials;//マテリアルデータ

	int mNormalNum;	//法線数
	CVector* mpNormal;//法線ベクトル

	int mFaceNum;	//面数
	int* mpVertexIndex;	//面を構成する頂点インデックス
	int mVertexNum;	//頂点数
	CVector* mpVertex;	//頂点データ
};

//CModelXFrameクラスの定義
class CModelXFrame {
	friend CModelX;
	friend CAnimation;
	friend CAnimationSet;
	friend CMyShader;
public:
	const string& Name() { return mName; }
	CModelXFrame();
	const CMatrix& CombinedMatrix();
	//合成行列の作成
	void AnimateCombined(CMatrix* parent);
	int Index();
	void Render();
	//コンストラクタ
	CModelXFrame(CModelX* model);
	//デストラクタ
	~CModelXFrame();
private:
	CMatrix mCombinedMatrix;	//合成行列

	CMesh* mpMesh;	//Meshデータ
	std::vector<shared_ptr<CModelXFrame>> mChildren;  //子フレームの配列
//	std::vector<CModelXFrame*> mChild;  //子フレームの配列
	CMatrix mTransformMatrix;  //変換行列
	string mName;   //フレーム名前
	int mIndex;  //フレーム番号
};


//領域解放をマクロ化
#define SAFE_DELETE_ARRAY(a) { if(a) delete[] a; a = nullptr;}
/*
 CModelX
 Xファイル形式の3Dモデルデータをプログラムで認識する
*/
class CModelX {
	friend CAnimationSet;
	friend CModelXFrame;
	friend CAnimation;
	friend CMyShader;
public:
	void AddFrame(shared_ptr<CModelXFrame>& frame);
	//シェーダーを使った描画
	void RenderShader(CMatrix* m);

	//アニメーションセットの追加
	size_t AddAnimationSet(const char* file);

	bool IsLoaded();
	/*
	アニメーションを抜き出す
	idx:分割したいアニメーションセットの番号
	start:分割したいアニメーションの開始時間
	end:分割したいアニメーションの終了時間
	name:追加するアニメーションセットの名前
	*/
	void CModelX::SeparateAnimationSet(
		int idx, int start, int end, char* name);

	void AnimateVertex(CMatrix*);
	//マテリアル配列の取得
	std::vector<shared_ptr<CMaterial>>& Materials();
	//マテリアルの検索
	shared_ptr<CMaterial> FindMaterial(char* name);

	//頂点にアニメーションを適用
	void AnimateVertex();
	//スキンウェイトのフレーム番号設定
	void SetSkinWeightFrameIndex();

	std::vector<shared_ptr<CModelXFrame>>& Frames();
	void AnimateFrame();
	std::vector<CAnimationSet*>& AnimationSet();
	//フレーム名に該当するフレームのアドレスを返す
	shared_ptr<CModelXFrame> FindFrame(const string& name);

	bool EOT(); // トークンが無くなったらtrue
	void Render();
	char* Token();

	~CModelX();
	//ノードの読み飛ばし
	void SkipNode();

	//単語の取り出し
	char* GetToken();

	CModelX();
	CModelX(const char* base);
	//ファイル読み込み
	void Load(const char* file);
	string& BaseDir()
	{
		return mBaseDir;
	}

	void BaseDir(string base)
	{
		std::transform(base.begin(), base.end(), base.begin(), ::toupper);
		mBaseDir = base;
	}
private:
	string mBaseDir;

	//シェーダー用スキンマトリックス
	CMatrix* mpSkinningMatrix;
	CMyShader mShader; //シェーダーのインスタンス

	bool mLoaded;
	std::vector<shared_ptr<CMaterial>> mMaterials;  //マテリアル配列
	//アニメーションセットの配列
	std::vector<CAnimationSet*> mAnimationSet;
	std::vector<shared_ptr<CModelXFrame>> mFrames;  //フレームの配列
	//cが区切り文字ならtrueを返す
	bool IsDelimiter(char c);

	char* mpPointer;	//読み込み位置
	char mToken[1024];	//取り出した単語の領域
};

#endif

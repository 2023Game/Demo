#ifndef CMODEL_H
#define CMODEL_H
//vectorのインクルード
#include <vector>
#include "CTriangle.h"
#include "CMaterial.h"
#include "CVertex.h"
#include "CModelX.h"

/*
モデルクラス
モデルデータの入力や表示
*/
class CModel //: public CMesh 
{
	//シェーダークラスをフレンドにする
	friend CMyShader;

public:
	//頂点バッファ識別子
	GLuint	  mMyVertexBufferId;

	//std::vector<CTriangle> Triangles() const;
	const std::vector<CTriangle>& Triangles() const;

	//モデルファイルの入力
	//Load(モデルファイル名, マテリアルファイル名)
	void Load(char* obj, char* mtl);
	//描画
	void Render();
	~CModel();
	//描画
	//Render(行列)
	void Render(const CMatrix& m);
	CMatrix mDummySkinningMatrix;
private:
	CMyShader mShader;
	//マテリアルポインタの可変長配列
	std::vector<CMaterial*> mpMaterials;
	//三角形の可変長配列
	std::vector<CTriangle> mTriangles;
	//頂点の配列
	CVertex* mpVertexes;
	void CreateVertexBuffer();
};

#include "CVertex.h"
#include <vector>

class CModelTest
{
public:
	CModelTest();
	void Render();

	CVertex mVertex[6];
	std::vector<CVertex> mVector;

};

#endif

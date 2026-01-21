#include "CCollider.h"
#include "CCollisionManager.h"
#include "CColliderLine.h"

bool CollisionTriangleLine2(const CVector& v0, const CVector& v1, const CVector& v2, const CVector& sv, const CVector& ev, CVector* adjust)
{
	//面の法線を、外積を正規化して求める
	CVector normal = (v1 - v0).Cross(v2 - v0).Normalize();
	//三角の頂点から線分始点へのベクトルを求める
	CVector v0sv = sv - v0;
	//三角の頂点から線分終点へのベクトルを求める
	CVector v0ev = ev - v0;
	//線分が面と交差しているか内積で確認する
	float dots = v0sv.Dot(normal);
	float dote = v0ev.Dot(normal);
	//プラスは交差してない
	if (dots * dote >= 0.0f) {
		//衝突してない（調整不要）
		*adjust = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}

	//線分は面と交差している
	//面と線分の交点を求める
	//交点の計算
	float per = (abs(dots) / (abs(dots) + abs(dote)));
	CVector cross = sv + (ev - sv) * per;

	//交点が三角形内なら衝突している
	//頂点1頂点2ベクトルと頂点1交点ベクトルとの外積を求め、
	//法線との内積がマイナスなら、三角形の外
	if ((v1 - v0).Cross(cross - v0).Dot(normal) < 0.0f) {
		//衝突してない
		*adjust = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//頂点2頂点3ベクトルと頂点2交点ベクトルとの外積を求め、
	//法線との内積がマイナスなら、三角形の外
	if ((v2 - v1).Cross(cross - v1).Dot(normal) < 0.0f) {
		//衝突してない
		*adjust = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//頂点3頂点1ベクトルと頂点3交点ベクトルとの外積を求め、
	//法線との内積がマイナスなら、三角形の外
	if ((v0 - v2).Cross(cross - v2).Dot(normal) < 0.0f) {
		//衝突してない
		*adjust = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}

	//調整値計算（衝突しない位置まで戻す）
	if (dots < 0.0f) {
		//始点が裏面
		//*adjust = normal * -dots;
		*adjust = (ev - sv) * per;
	}
	else {
		//終点が裏面
		//*adjust = normal * -dote;
		*adjust = (sv - ev) * (1.0f - per);
	}
	return true;
}


void CCollider::ChangePriority(int priority)
{
	mPriority = priority;
	CCollisionManager::Instance()->Remove(this); //一旦削除
	CCollisionManager::Instance()->Add(this); //追加
}

bool CCollider::CollisionTriangleSphere(CCollider* t, CCollider* s, CVector* a)
{
	CVector v[3], sv, ev;
	//各コライダの頂点をワールド座標へ変換
	v[0] = t->mV[0];// **t->mpMatrix;
	v[1] = t->mV[1];// **t->mpMatrix;
	v[2] = t->mV[2];// **t->mpMatrix;
	//面の法線を、外積を正規化して求める
	CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	//線コライダをワールド座標で作成
	sv = s->mPosition * *s->mpMatrix + normal * s->mRadius;
	ev = s->mPosition * *s->mpMatrix - normal * s->mRadius;
	return CollisionTriangleLine2(v[0], v[1], v[2], sv, ev, a);
}

CCollider::CCollider()
	: mpParent(nullptr)
	, mpMatrix(&mMatrix)
	, mType(EType::ESPHERE)
	, mRadius(0)
	, mTag(ETag::ENONE)
{
	//コリジョンマネージャに追加
	CCollisionManager::Instance()->Add(this);
}

//衝突判定
//Collision(コライダ1, コライダ2)
//retrun:true（衝突している）false(衝突していない)
bool CCollider::Collision(CCollider* m, CCollider* o) {
	//各コライダの中心座標を求める
	//原点×コライダの変換行列×親の変換行列
	CVector mpos = m->mPosition * *m->mpMatrix;
	CVector opos = o->mPosition * *o->mpMatrix;
	//中心から中心へのベクトルを求める
	mpos = mpos - opos;
	//中心の距離が半径の合計より小さいと衝突
	if (m->mRadius + o->mRadius > mpos.Length()) {
		//衝突している
		return  true;
	}
	//衝突していない
	return false;
}

CCollider::~CCollider() {
	//コリジョンリストから削除
	CCollisionManager::Instance()->Remove(this);
}

CCollider::CCollider(CCharacter3* parent, CMatrix* matrix,
	const CVector& position, float radius, ETag tag)
	: CCollider() 
{
	mTag = tag;//タグの設定
	//親設定
	mpParent = parent;
	//親行列設定
	if (matrix)
		mpMatrix = matrix;
	else
		mpMatrix = &mMatrix;
	//CTransform設定
	mPosition = position; //位置
	//半径設定
	mRadius = radius;
	//コリジョンマネージャyに追加
	//CCollisionManager::Instance()->Add(this);
}

CCharacter3* CCollider::Parent()
{
	return mpParent;
}

void CCollider::Render() {
	glPushMatrix();
	//コライダの中心座標を計算
	//自分の座標×親の変換行列を掛ける
	CVector pos = mPosition * *mpMatrix;
	//中心座標へ移動
	glMultMatrixf(CMatrix().Translate(pos.X(), pos.Y(), pos.Z()).M());
	//DIFFUSE赤色設定
	float c[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	//球描画
	glutWireSphere(mRadius, 16, 16);
	glPopMatrix();
}

void CCollider::Update()
{
	CCollider::mV[0] = mV[0] * *mpMatrix;
	CCollider::mV[1] = mV[1] * *mpMatrix;
	ChangePriority();
}

CCollider::EType CCollider::Type()
{
	return mType;
}

bool CCollider::CollisionTriangleLine(CCollider* t, CCollider* l, CVector* a) {
	CVector v[3], sv, ev;
	//各コライダの頂点をワールド座標へ変換
	v[0] = t->mV[0];// **t->mpMatrix;
	v[1] = t->mV[1];// **t->mpMatrix;
	v[2] = t->mV[2];// **t->mpMatrix;
	sv = l->mV[0];// **l->mpMatrix;
	ev = l->mV[1];// **l->mpMatrix;

	return CollisionTriangleLine2(v[0], v[1], v[2], sv, ev, a);

	//面の法線を、外積を正規化して求める
	CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	//三角の頂点から線分始点へのベクトルを求める
	CVector v0sv = sv - v[0];
	//三角の頂点から線分終点へのベクトルを求める
	CVector v0ev = ev - v[0];
	//線分が面と交差しているか内積で確認する
	float dots = v0sv.Dot(normal);
	float dote = v0ev.Dot(normal);
	//プラスは交差してない
	if (dots * dote >= 0.0f) {
		//衝突してない（調整不要）
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}

	//線分は面と交差している
	//面と線分の交点を求める
	//交点の計算
	CVector cross = sv + (ev - sv) * (abs(dots) / (abs(dots) + abs(dote)));

	//交点が三角形内なら衝突している
	//頂点1頂点2ベクトルと頂点1交点ベクトルとの外積を求め、
	//法線との内積がマイナスなら、三角形の外
	if ((v[1] - v[0]).Cross(cross - v[0]).Dot(normal) < 0.0f) {
		//衝突してない
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//頂点2頂点3ベクトルと頂点2交点ベクトルとの外積を求め、
	//法線との内積がマイナスなら、三角形の外
	if ((v[2] - v[1]).Cross(cross - v[1]).Dot(normal) < 0.0f) {
		//衝突してない
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//課題３２
	//頂点3頂点1ベクトルと頂点3交点ベクトルとの外積を求め、
	//法線との内積がマイナスなら、三角形の外
	if ((v[0] - v[2]).Cross(cross - v[2]).Dot(normal) < 0.0f) {
		//衝突してない
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}

	//調整値計算（衝突しない位置まで戻す）
	if (dots < 0.0f) {
		//始点が裏面
		*a = normal * -dots;
	}
	else {
		//終点が裏面
		*a = normal * -dote;
	}
	return true;
}

//優先度の変更
void CCollider::ChangePriority()
{
	//自分の座標×親の変換行列を掛けてワールド座標を求める
	CVector pos = mPosition * *mpMatrix;
	//ベクトルの長さが優先度
	ChangePriority(pos.Length());
	//mPriority = pos.Length();
	//CCollisionManager::Instance()->Remove(this); //一旦削除
	//CCollisionManager::Instance()->Add(this); //追加
}

CCollider::ETag CCollider::Tag()
{
	return mTag;
}

CCharacter3::ETag CCollider::ParentTag()
{
	return mpParent->Tag();
}

CCharacter3::EState CCollider::ParentState()
{
	return mpParent->State();
}

void CCollider::Matrix(CMatrix* m)
{
	mpMatrix = m;
}


//CalcCalcPointLineDist(点, 始点, 終点, 線上の最短点, 割合)
//点と線（始点、終点を通る直線）の最短距離を求める
float CalcPointLineDist(const CVector& p, const CVector& s, const CVector& e, CVector* mp, float* t)
{
	*t = 0.0f; //割合の初期化
	CVector v = e - s; //始点から終点へのベクトルを求める
	float dvv = v.Dot(v); //ベクトルの長さの2乗を求める
	if (dvv > 0.0f) {
		*t = v.Dot(p - s) / dvv; //線上の垂線となる点の割合を求める
		// 上の式の説明
		// dot(v, p-sp) は |v||p-sp|cosΘ
		// dvvは|v|の２乗
		// 上の計算で、tは |p-sp|cosΘ / |v|となる。
		// つまりtは「dotで投影した長さ÷vの長さ」という割合になる
	}
	*mp = s + v * *t; //線上の垂線となる点を求める
	return (p - *mp).Length(); //垂線の長さを返す
}


//CalcLineLineDist(始点1, 終点1, 始点2, 終点2, 交点1, 交点2, 比率1, 比率2)
//2線間の最短距離を返す
float CalcLineLineDist(
	const CVector& s1, //始点1
	const CVector& e1, //終点1
	const CVector& s2, //始点2
	const CVector& e2, //終点2
	CVector* mp1, //交点1
	CVector* mp2, //交点2
	float* t1, //比率1
	float* t2  //比率2
)
{
	CVector v1 = e1 - s1;
	CVector v2 = e2 - s2;
	//2直線が平行
	if (v1.Cross(v2).Length() < 0.000001f) {
		//線分1の始点から直線2までの最短距離問題に帰着する
		*t1 = 0.0f;
		*mp1 = s1;
		float dist = CalcPointLineDist(*mp1, s2, e2, mp2, t2);
		return dist;
	}
	//2直線が平行でない
	float dv1v2 = v1.Dot(v2);
	float dv1v1 = v1.Dot(v1);
	float dv2v2 = v2.Dot(v2);
	CVector vs2s1 = s1 - s2;
	//比率1を求める
	*t1 = (dv1v2 * v2.Dot(vs2s1) - dv2v2 * v1.Dot(vs2s1))
		/ (dv1v1 * dv2v2 - dv1v2 * dv1v2);
	//交点1を求める
	*mp1 = s1 + v1 * *t1;
	//比率2を求める
	*t2 = v2.Dot(*mp1 - s2) / dv2v2;
	//交点2を求める
	*mp2 = s2 + v2 * *t2;
	//最短距離を返す
	return (*mp2 - *mp1).Length();
}


//0～1の間にクランプ(値を強制的にある範囲内にすること)
void clamp0to1(float& v) {
	if (v < 0.0f)  v = 0.0f;
	else if (v > 1.0f)  v = 1.0f;
}
//2線分間の最短距離
float CalcSegmentSegmentDist
(
	const CVector& s1, const CVector& e1, //線分1
	const CVector& s2, const CVector& e2, //線分2
	CVector* mp1, //最短線の端点1(始点や終点になることもある)
	CVector* mp2 //最短線の端点2(始点や終点になることもある)
)
{
	float dist = 0, t1, t2;
	//----------------------------------------------------------------
	//とりあえず2直線間の最短距離,mp1,mp2,t1,t2を求めてみる
	dist = CalcLineLineDist(s1, e1, s2, e2, mp1, mp2, &t1, &t2);
	if (0.0f <= t1 && t1 <= 1.0f &&
		0.0f <= t2 && t2 <= 1.0f) {
		//mp1,mp2が両方とも線分内にあった
		return dist;
	}
	//mp1,mp2の両方、またはどちらかが線分内になかったので次へ
		//mp1,t1を求め直す ⇒ 
	//t2を0～1にクランプしてmp2からs1.vに垂線を降ろしてみる
	clamp0to1(t2);
	*mp2 = s2 + (e2 - s2) * t2;
	dist = CalcPointLineDist(*mp2, s1, e1, mp1, &t1);
	if (0.0f <= t1 && t1 <= 1.0f) {
		//mp1が線分内にあった
		return dist;
	}
	//mp1が線分内になかったので次へ

	//mp2,t2を求め直す ⇒ 
	//t1を0～1にクランプしてmp1からs2.vに垂線を降ろしてみる
	clamp0to1(t1);
	*mp1 = s1 + (e1 - s1) * t1;
	dist = CalcPointLineDist(*mp1, s2, e2, mp2, &t2);
	if (0.0f <= t2 && t2 <= 1.0f) {
		//mp2が線分内にあった
		return dist;
	}
	//mp2が線分内になかったので次へ

	//t2をクランプしてmp2を再計算すると、mp1からmp2までが最短
	clamp0to1(t2);
	*mp2 = s2 + (e2 - s2) * t2;
	return (*mp2 - *mp1).Length();
}

bool CCollider::CollisionCapsuleTriangle(CCollider* m, CCollider* t, CVector* a)
{
	CVector v[3], sv, ev;
	bool ret = false;
	//各コライダの頂点をワールド座標へ変換
	//v[0] = t->mV[0];// **t->mpMatrix;
	//v[1] = t->mV[1];// **t->mpMatrix;
	//v[2] = t->mV[2];// **t->mpMatrix;
	//面の法線を、外積を正規化して求める
	//CVector normal = (v[1] - v[0]).Cross(v[2] - v[0]).Normalize();
	//CVector r = ((m->V(0) - m->V(1)).Normalize()) * m->mRadius;
	//sv = m->V(0) + r;
	//ev = m->V(1) - r;

	//if (CollisionTriangleLine2(t->mV[0], t->mV[1], t->mV[2], sv, ev, a))
	//{
	//	return true;
	//}

	//線コライダをワールド座標で作成
	sv = m->V(0) + t->mV[3] * m->mRadius;
	ev = m->V(0) - t->mV[3] * m->mRadius;
	if (CollisionTriangleLine2(t->mV[0], t->mV[1], t->mV[2], sv, ev, a))
	{
		return true;
	}

	sv = m->V(1) + t->mV[3] * m->mRadius;
	ev = m->V(1) - t->mV[3] * m->mRadius;
	if (CollisionTriangleLine2(t->mV[0], t->mV[1], t->mV[2], sv, ev, a))
	{
		return true;
	}

	CVector r = ((m->V(0) - m->V(1)).Normalize()) * m->mRadius;
	sv = m->V(0) + r;
	ev = m->V(1) - r;

	if (CollisionTriangleLine2(t->mV[0], t->mV[1], t->mV[2], sv, ev, a))
	{
		return true;
	}

	return false;
}

bool CCollider::CollisionCapsuleCapsule(CCollider* m, CCollider* o, CVector* adjust)
{
	CVector mp1, mp2;
	float radius = m->mRadius + o->mRadius;

	*adjust = CVector();
	if (CalcSegmentSegmentDist(m->V(0), m->V(1), o->V(0), o->V(1), &mp1, &mp2) < radius)
	{
		*adjust = mp1 - mp2;
		float len = radius - adjust->Length();
		*adjust = adjust->Normalize() * len;
		return true;
	}
	return false;
}

/// code by Copilot ///

// v を [0,1] にクランプ
inline float Clamp01(float v)
{
	if (v < 0.0f) return 0.0f;
	if (v > 1.0f) return 1.0f;
	return v;
}

// 線分 P1Q1 と P2Q2 の最近接点を求める（完全版）
// 戻り値: 最近接点間の距離
// outS, outT: 各線分上のパラメータ（0〜1）
float SegmentSegmentClosestPoints(
	const CVector& p1, const CVector& q1,
	const CVector& p2, const CVector& q2,
	CVector& outC1, CVector& outC2,
	float* outS = nullptr, float* outT = nullptr)
{
	const float EPS = 1e-6f;

	CVector d1 = q1 - p1;  // 線分1 方向
	CVector d2 = q2 - p2;  // 線分2 方向
	CVector r = p1 - p2;

	float a = d1.Dot(d1);  // |d1|^2
	float e = d2.Dot(d2);  // |d2|^2
	float f = d2.Dot(r);

	float s, t;

	// 両方ほぼ点
	if (a < EPS && e < EPS) {
		outC1 = p1;
		outC2 = p2;
		if (outS) *outS = 0.0f;
		if (outT) *outT = 0.0f;
		return (outC1 - outC2).Length();
	}

	// 線分1 がほぼ点
	if (a < EPS) {
		s = 0.0f;
		t = Clamp01(f / e);
	}
	else {
		float c = d1.Dot(r);
		// 線分2 がほぼ点
		if (e < EPS) {
			t = 0.0f;
			s = Clamp01(-c / a);
		}
		else {
			float b = d1.Dot(d2);
			float denom = a * e - b * b;

			// 無限直線同士の最適 s
			if (denom != 0.0f)
				s = Clamp01((b * f - c * e) / denom);
			else
				s = 0.0f; // ほぼ平行

			// その s に対する最適 t（まだクランプ前）
			t = (b * s + f) / e;

			// t を [0,1] に押し込む → それに応じて s を取り直す
			if (t < 0.0f) {
				t = 0.0f;
				s = Clamp01(-c / a);
			}
			else if (t > 1.0f) {
				t = 1.0f;
				s = Clamp01((b - c) / a);
			}
		}
	}

	outC1 = p1 + d1 * s;
	outC2 = p2 + d2 * t;

	if (outS) *outS = s;
	if (outT) *outT = t;

	return (outC1 - outC2).Length();
}

// 線分同士の最短距離だけ欲しいとき
float SegmentSegmentDistance(
	const CVector& p1, const CVector& q1,
	const CVector& p2, const CVector& q2)
{
	CVector c1, c2;
	return SegmentSegmentClosestPoints(p1, q1, p2, q2, c1, c2, nullptr, nullptr);
}

//カプセル vs 三角形（or エッジ）
bool IntersectCapsuleSegment(
	const CVector& capA, const CVector& capB, float radius,
	const CVector& s, const CVector& e,
	CVector* outPointOnCapsule = nullptr,
	CVector* outPointOnEdge = nullptr,
	CVector* outNormal = nullptr)
{
	CVector c1, c2;
	float dist = SegmentSegmentClosestPoints(capA, capB, s, e, c1, c2);

	if (dist > radius) {
		return false;
	}

	if (outPointOnCapsule) *outPointOnCapsule = c1;
	if (outPointOnEdge)    *outPointOnEdge = c2;

	if (outNormal) {
		CVector n = c1 - c2;
		float len2 = n.Dot(n);
		if (len2 > 1e-12f) {
			*outNormal = n * (1.0f / std::sqrt(len2));
		}
		else {
			// ほぼ同一点・退化ケース用のフォールバック
			*outNormal = CVector(0, 1, 0); // 適当なデフォルト
		}
	}

	return true;
}

//点と三角形の面への射影（内部判定つき）
inline bool ProjectPointOnTriangle(
	const CVector& p,
	const CVector& a, const CVector& b, const CVector& c,
	CVector& outProj)
{
	CVector ab = b - a;
	CVector ac = c - a;
	CVector ap = p - a;

	float d00 = ab.Dot(ab);
	float d01 = ab.Dot(ac);
	float d11 = ac.Dot(ac);
	float d20 = ap.Dot(ab);
	float d21 = ap.Dot(ac);

	float denom = d00 * d11 - d01 * d01;
	if (denom == 0.0f) return false; // 退化三角形

	float v = (d11 * d20 - d01 * d21) / denom;
	float w = (d00 * d21 - d01 * d20) / denom;
	float u = 1.0f - v - w;

	if (u >= 0 && v >= 0 && w >= 0) {
		outProj = a * u + b * v + c * w;
		return true;
	}
	return false;
}

//線分 vs 三角形（面距離）
inline float SegmentTriangleDistanceSq(
	const CVector& p0, const CVector& p1,
	const CVector& a, const CVector& b, const CVector& c,
	CVector& outSegPoint,
	CVector& outTriPoint)
{
	CVector segDir = p1 - p0;

	// 1. 線分を無限直線として三角形面と交差するか
	CVector n = (b - a).Cross(c - a);
	float denom = n.Dot(segDir);

	if (fabsf(denom) > 1e-6f) {
		float t = n.Dot(a - p0) / denom;
		if (t >= 0.0f && t <= 1.0f) {
			CVector p = p0 + segDir * t;

			CVector proj;
			if (ProjectPointOnTriangle(p, a, b, c, proj)) {
				outSegPoint = p;
				outTriPoint = proj;
				return (p - proj).LengthSq();
			}
		}
	}

	// 2. 面内に落ちない → エッジ距離で決まる
	float best = FLT_MAX;

	auto testEdge = [&](const CVector& e0, const CVector& e1) {
		CVector s, t;
		float d = SegmentSegmentClosestPoints(p0, p1, e0, e1, s, t);
		float dsq = (s - t).LengthSq();
		if (dsq < best) {
			best = dsq;
			outSegPoint = s;
			outTriPoint = t;
		}
		};

	testEdge(a, b);
	testEdge(b, c);
	testEdge(c, a);

	return best;
}

//カプセル vs 三角形（完成版）
bool CapsuleTriangleIntersect(
	const CVector& capA,
	const CVector& capB,
	float radius,
	const CVector& A,
	const CVector& B,
	const CVector& C,
	CVector* outPointCapsule = nullptr,
	CVector* outPointTriangle = nullptr,
	CVector* outNormal = nullptr)
{
	CVector pCaps, pTri;

	float distSq = SegmentTriangleDistanceSq(
		capA, capB,
		A, B, C,
		pCaps, pTri
	);

	float rSq = radius * radius;

	if (distSq > rSq)
		return false;

	if (outPointCapsule)  *outPointCapsule = pCaps;
	if (outPointTriangle) *outPointTriangle = pTri;

	if (outNormal) {
		CVector n = pCaps - pTri;
		float lenSq = n.Dot(n);
		if (lenSq > 1e-12f)
			*outNormal = n * (1.0f / sqrtf(lenSq));
		else
			*outNormal = CVector(0, 1, 0); // fallback
	}

	return true;
}

#include <Novice.h>

#include "Math/Quaternion.h"

const char kWindowTitle[] = "LE2A_16_ハマヤ_タイセイ";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

void PrintMatrix4x4(int x, int y, const Matrix4x4& matrix) {
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "% 4.3f", matrix[row][column]);
		}
	}
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Quaternion quaternion0 = Quaternion::FromToRotation(CVector3::BASIS_X, -CVector3::BASIS_X);
	Vector3 from1 = Vector3{ 1.0f, 0.7f, 0.5f }.normalize();
	Vector3 to1 = -from1;
	Quaternion quaternion1 = Quaternion::FromToRotation(from1, to1);
	Vector3 from2 = Vector3{ -0.6f, 0.9f, 0.2f }.normalize();
	Vector3 to2 = Vector3{ 0.4f, 0.7f, -0.5f }.normalize();
	Quaternion quaternion2 = Quaternion::FromToRotation(from2, to2);

	Matrix4x4 fromToMatrix0 = quaternion0.to_matrix();
	Matrix4x4 fromToMatrix1 = quaternion1.to_matrix();
	Matrix4x4 fromToMatrix2 = quaternion2.to_matrix();

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		PrintMatrix4x4(0, 0, fromToMatrix0);
		PrintMatrix4x4(0, kRowHeight * 5, fromToMatrix1);
		PrintMatrix4x4(0, kRowHeight * 10, fromToMatrix2);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

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


void PrintQuaternion(int x, int y, const Quaternion& quat) {
	const Vector3& vec = quat.vector();
	Novice::ScreenPrintf(x, y, "%4.3f %4.3f %4.3f %4.3f", vec.x, vec.y, vec.z, quat.real());
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Quaternion quat1{ 2.0f, 3.0f, 4.0f, 1.0f };
	Quaternion quat2{ 1.0f, 3.0f, 5.0f, 2.0f };

	Quaternion identity = CQuaternion::IDENTITY;
	Quaternion conj = quat1.conjugate();
	Quaternion inverse = quat1.inverse();
	Quaternion normalize = quat1.normalize();
	Quaternion mul1 = quat1 * quat2;
	Quaternion mul2 = quat2 * quat1;
	float norm = quat1.norm();

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

		PrintQuaternion(0, 0, identity);
		PrintQuaternion(0, 20, conj);
		PrintQuaternion(0, 40, inverse);
		PrintQuaternion(0, 60, normalize);
		PrintQuaternion(0, 80, mul1);
		PrintQuaternion(0, 100, mul2);
		Novice::ScreenPrintf(0, 120, "%4.3f", norm);

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

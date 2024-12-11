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

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	float w = vector.x * matrix[0][3] + vector.y * matrix[1][3] + vector.z * matrix[2][3] + 1.0f * matrix[3][3];
	return {
		(vector.x * matrix[0][0] + vector.y * matrix[1][0] + vector.z * matrix[2][0] + 1.0f * matrix[3][0]) / w,
		(vector.x * matrix[0][1] + vector.y * matrix[1][1] + vector.z * matrix[2][1] + 1.0f * matrix[3][1]) / w,
		(vector.x * matrix[0][2] + vector.y * matrix[1][2] + vector.z * matrix[2][2] + 1.0f * matrix[3][2]) / w
	};
}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Quaternion from = Quaternion::AngleAxis({ 0.71f, 0.71f, 0.0f }, 0.3f);
	Quaternion to = { -from.vector(), -from.real() };

	Quaternion interpolate0 = Quaternion::Slerp(from, to, 0.0f);
	Quaternion interpolate1 = Quaternion::Slerp(from, to, 0.3f);
	Quaternion interpolate2 = Quaternion::Slerp(from, to, 0.5f);
	Quaternion interpolate3 = Quaternion::Slerp(from, to, 0.7f);
	Quaternion interpolate4 = Quaternion::Slerp(from, to, 1.0f);

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

		PrintQuaternion(0, 0, interpolate0);
		PrintQuaternion(0, 20, interpolate1);
		PrintQuaternion(0, 40, interpolate2);
		PrintQuaternion(0, 60, interpolate3);
		PrintQuaternion(0, 80, interpolate4);

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

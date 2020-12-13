/*
InitSound関数をLoadTexture関数より後に呼び出すとエラー
※内部でCOMオブジェクトを利用するため

リスナー
音を聞くための「耳」に相当。3Dサウンドで必要。
ソース
音を発する「音源」に相当。スピーカー。XAudio2ではVoiceと呼ばれる。
バッファ
音データを格納しておくバッファ。WAVファイル、OGGファイルなどからロード。
 */
#ifndef __SOUND_H__
#define __SOUND_H__

#include <xaudio2.h>

#pragma comment(lib, "xaudio2.lib")

//----------
// プロトタイプ宣言
//----------
class CSound
{
public:
	CSound();
	~CSound();

	// 初期化
	static HRESULT InitSound(void);
	// 終了処理
	static void UninitSound(void);

	// サウンドとソースの作成
	void Load(const char *file, bool loop = false);
	// サウンドとソースの破棄
	//void Destroy();

	// サウンドの再生 (各設定を引数で)
	void Play(float fVolume = 1.0f, float = 0.0f);

	// サウンドの停止
	void Stop();
	
private:
	XAUDIO2_BUFFER* m_pSound;
	IXAudio2SourceVoice* m_pSource;

	// サウンドの読み込み
	static XAUDIO2_BUFFER* CreateSound(const char *file, bool loop = false);
	// サウンドの再生
	static IXAudio2SourceVoice* PlaySound(XAUDIO2_BUFFER* pSound);
};


#endif // __SOUND_H__
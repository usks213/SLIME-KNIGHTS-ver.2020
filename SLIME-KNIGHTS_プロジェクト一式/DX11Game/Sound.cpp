#include "Sound.h"

#include <mmsystem.h>
#include <mmreg.h>
#include <MSAcm.h>
#include <Shlwapi.h>
#include <vector>
#include <map>
#include <string>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msacm32.lib")
#pragma comment(lib, "shlwapi.lib")

//----------
// 構造体
//----------
struct SoundData
{
	WAVEFORMATEX		format;		// WAVフォーマット
	BYTE				*pBuffer;	// サウンドデータ
	DWORD				bufSize;	// データサイズ
	XAUDIO2_BUFFER		sound;		// サウンドバッファ
};
struct MP3FormatInfo
{
	DWORD offset;
	DWORD dataSize;
};
struct MP3FrameInfo
{
	BYTE channel;
	BYTE padding;
	DWORD sampleRate;
	DWORD bitRate;
	DWORD frameSize;
};

//----------
// プロトタイプ宣言
//----------
HRESULT LoadWav(const char *file, SoundData *pData);
HRESULT LoadMP3(const char *file, SoundData *pData);
DWORD ReadMP3Format(HANDLE hFile, MP3FormatInfo *pFormat);
DWORD ReadMP3FrameHeader(HANDLE hFile, DWORD seek, MP3FrameInfo *pFrame);
DWORD ReadMP3Data(HANDLE hFile, DWORD seek, DWORD size, MP3FrameInfo *pFrame, SoundData *pData);

//----------
// 定数定義
//----------
const BYTE CMP_MATCH = 0;

//----------
// グローバル変数
//----------
typedef std::pair<std::string, SoundData> SoundKey;
typedef std::map<std::string, SoundData> SoundList;
typedef std::vector<IXAudio2SourceVoice*> SourceList;

IXAudio2 *g_pXAudio;
IXAudio2MasteringVoice *g_pMasterVoice;
SoundList g_soundList;
SourceList g_sourceList;

/**
 * @brief 初期化
 * @return 処理結果
 */
HRESULT CSound::InitSound(void)
{
	HRESULT hr = E_FAIL;

	// COMオブジェクト初期化
	//hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	//if (FAILED(hr))
	//{
	//	return hr;
	//}

	// XAUDIO2初期化
	hr = XAudio2Create(&g_pXAudio);
	if (FAILED(hr))
	{
		return hr;
	}

	// マスターボイス(ソース)作成
	hr = g_pXAudio->CreateMasteringVoice(&g_pMasterVoice);

	return hr;
}

/**
 * @brief 終了処理
 */
void CSound::UninitSound(void)
{
	SourceList::iterator sourceIt = g_sourceList.begin();
	while (sourceIt != g_sourceList.end())
	{
		(*sourceIt)->DestroyVoice();
		++sourceIt;
	}
	SoundList::iterator soundIt = g_soundList.begin();
	while (soundIt != g_soundList.end())
	{
		delete[] soundIt->second.pBuffer;
		++soundIt;
	}

	if (g_pMasterVoice != NULL)
	{
		g_pMasterVoice->DestroyVoice();
		g_pMasterVoice = NULL;
	}
	if (g_pXAudio != NULL)
	{
		g_pXAudio->Release();
		g_pXAudio = NULL;
	}
}

/**
 * @brief サウンド作成
 * @param[in] file 読み込むファイル
 * @param[in] loop 繰り返し再生
 * @return サウンドバッファ
 */
XAUDIO2_BUFFER* CSound::CreateSound(const char *file, bool loop)
{
	SoundData data;

	SoundList::iterator it = g_soundList.find(file);
	if (it != g_soundList.end())
	{
		// すでに読み込んだサウンドファイルがある
		return &it->second.sound;
	}


	// 拡張子ごとに読み込み処理実行
	HRESULT hr = E_FAIL;
	LPSTR ext = PathFindExtensionA(file);
	if (ext != NULL) {
		if (memcmp(ext, ".wav", 4) == 0) {
			hr = LoadWav(file, &data);
		}
		else if (memcmp(ext, ".mp3", 4) == 0) {
			hr = LoadMP3(file, &data);
		}
	}
	if (FAILED(hr)) {
		return NULL;
	}

	//--- バッファー作成
	ZeroMemory(&data.sound, sizeof(data.sound));
	// サウンドデータのバイト数
	data.sound.AudioBytes = data.bufSize;
	// サウンドデータの先頭アドレス
	data.sound.pAudioData = data.pBuffer;
	// ループ指定
	if (loop)
	{
		data.sound.LoopCount = XAUDIO2_LOOP_INFINITE;
	}
	data.sound.Flags = XAUDIO2_END_OF_STREAM;

	// 登録
	g_soundList.insert(SoundKey(file, data));
	it = g_soundList.find(file);

	return &it->second.sound;
}

/**
 * @brief サウンド再生
 * @param[in] pSound サウンドバッファ
 */
IXAudio2SourceVoice* CSound::PlaySound(XAUDIO2_BUFFER* pSound)
{
	HRESULT hr;
	IXAudio2SourceVoice* pSource;

	// 再生するデータを探索
	SoundList::iterator soundIt = g_soundList.begin();
	while (soundIt != g_soundList.end())
	{
		if (&soundIt->second.sound == pSound)
		{
			break;
		}
		++soundIt;
	}
	if (soundIt == g_soundList.end())
	{
		// 該当のデータなし
		return NULL;
	}

	// 未使用のソースを探索
	XAUDIO2_VOICE_STATE state;
	SourceList::iterator sourceIt = g_sourceList.begin();
	while (sourceIt != g_sourceList.end())
	{
		(*sourceIt)->GetState(&state);
		if (state.BuffersQueued == 0)
		{
			break;
		}
		++sourceIt;
	}
	if (sourceIt != g_sourceList.end())
	{
		// 既存ソースを使用
		pSource = *sourceIt;
		pSource->SetVolume(1.0f);
	}
	else
	{

		// フォーマットを指定してソースを作成
		/*----------
		* WAVEFORMATEX
		* wFormatTag
		*  フォーマット
		* nChannels
		*  チャンネル数
		*  1... モノラル
		*  2... ステレオ
		* wBitsPerSample
		*  1サンプルあたりのビット数
		*  8...128を無音とする0~255
		*  16...0を無音とする-32768~32767
		* nSamplesPerSec
		*  サンプリングレート
		*  (1秒あたりのサンプル数
		*  単位はHz(ヘルツ
		*----------*/
		hr = g_pXAudio->CreateSourceVoice(&pSource, &soundIt->second.format);
		if (FAILED(hr)) {
			return NULL;
		}
		// ソースをリストに追加
		g_sourceList.push_back(pSource);
	}

	pSource->SubmitSourceBuffer(pSound);

	// 再生
	//pSource->Start();


	return pSource;
}


//================================================================================================================
// 自前の関数

/**
 * @brief コンストラクタ
 */
CSound::CSound()
{
	m_pSound = nullptr;
	m_pSource = nullptr;
}

/**
 * @brief デストラクタ
 */
CSound::~CSound()
{
	//// ソース
	//if (m_pSource)
	//{
	//	// サウンドソースの解放
	//	SourceList::iterator sourceIt = g_sourceList.begin();
	//	while (sourceIt != g_sourceList.end())
	//	{
	//		if (*sourceIt == m_pSource)
	//		{
	//			// 解放
	//			m_pSource->DestroyVoice();
	//			m_pSource = nullptr;

	//			break;
	//		}
	//		++sourceIt;
	//	}
	//}

	//// サウンド
	//if (m_pSound)
	//{
	//	// サウンドデータの解放
	//	SoundList::iterator soundIt = g_soundList.begin();
	//	while (soundIt != g_soundList.end())
	//	{
	//		if (&soundIt->second.sound == m_pSound)
	//		{
	//			// 解放
	//			delete[] soundIt->second.pBuffer;
	//			m_pSound = nullptr;

	//			break;
	//		}
	//		++soundIt;
	//	}
	//}

}

/**
 * @brief サウンドとソースの作成
 * @param[in] file 読み込むファイル
 * @param[in] loop 繰り返し再生
 * @return サウンドクラス
 */
void CSound::Load(const char *file, bool loop)
{
	// サウンドの読み込み、作成
	m_pSound = CreateSound(file, loop);

	// サウンドソースの作成
	//m_pSource = PlaySound(m_pSound);
}

/**
 * @brief サウンドの再生
 * @param[in] fVolume	ボリューム					( 0.0f～1.0f)
 * @param[in] fChannel	LRのチャンネルボリューム	(-1.0f～1.0f)
 * @return なし
 */
void CSound::Play(float fVolume, float fChannel)
{
	if (!m_pSound) return;

	// 各設定
	m_pSource = PlaySound(m_pSound);

	// ボリューム設定
	m_pSource->SetVolume(fVolume);

	// チャンネル設定
	float fChan[2];
	if (fChannel == 0.0f)
	{
		// L
		fChan[0] = 1.0f;
		// R
		fChan[1] = 1.0f;
	}
	else if (fChannel < 0)
	{
		// L
		fChan[0] = -fChannel;
		// R
		fChan[1] = 1.0f + fChannel;
	}
	else
	{
		// L
		fChan[0] = 1.0f - fChannel;
		// R
		fChan[1] = fChannel;
	}
	// セット
	m_pSource->SetChannelVolumes(2, fChan);


	// 再生
	m_pSource->Start();

}

/**
 * @brief サウンドの停止
 * @return なし
 */
void CSound::Stop()
{
	if (!m_pSound || !m_pSource) return;

	// 停止
	m_pSource->Stop();

}

//================================================================================================================


/**
 * @brief wavファイル読み込み
 * @param[in] file 読み込むファイル
 * @param[out] pData サウンドデータ
 * @return 処理結果
 */
HRESULT LoadWav(const char *file, SoundData *pData)
{
	HMMIO hMmio = NULL;
	MMIOINFO mmioInfo;
	MMRESULT mmRes;

	// WAVEファイルオープン
	memset(&mmioInfo, 0, sizeof(MMIOINFO));
	hMmio = mmioOpenA(const_cast<char*>(file), &mmioInfo, MMIO_READ);
	if (hMmio == NULL) {
		return E_FAIL;
	}

	// RIFFチャンク検索
	MMCKINFO riffChunk;
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);
	if (mmRes != MMSYSERR_NOERROR) {
		mmioClose(hMmio, 0);
		return E_FAIL;
	}

	// フォーマットチャンク検索
	MMCKINFO formatChunk;
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);
	if (mmRes != MMSYSERR_NOERROR) {
		mmioClose(hMmio, 0);
		return E_FAIL;
	}

	// フォーマット取得
	DWORD formatSize = formatChunk.cksize;
	DWORD size = mmioRead(hMmio, reinterpret_cast<HPSTR>(&pData->format), formatSize);
	if (size != formatSize) {
		mmioClose(hMmio, 0);
		return E_FAIL;
	}
	
	// RIFFチャンクに移動
	mmioAscend(hMmio, &formatChunk, 0);


	// データチャンク検索
	MMCKINFO dataChunk;
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);
	if (mmRes != MMSYSERR_NOERROR) {
		mmioClose(hMmio, 0);
		return E_FAIL;
	}

	// データ取得
	pData->bufSize = dataChunk.cksize;
	pData->pBuffer = new BYTE[pData->bufSize];
	size = mmioRead(hMmio, reinterpret_cast<HPSTR>(pData->pBuffer), pData->bufSize);
	if (size != dataChunk.cksize) {
		pData->bufSize = 0;
		if (pData->pBuffer != NULL)
		{
			delete[] pData->pBuffer;
			pData->pBuffer;
		}
		return E_FAIL;
	}

	mmioClose(hMmio, 0);
	return S_OK;
}

/**
 * @brief mp3ファイル読み込み
 * @param[in] file 読み込むファイル
 * @param[out] pData サウンドデータ
 * @return 処理結果
 */
HRESULT LoadMP3(const char *file, SoundData *pData)
{
	HANDLE hFile; // ファイルポインタ
	DWORD readSize; // 読み込みサイズ

	// 読み込み
	hFile = CreateFileA(
		file, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL
	);
	if (hFile == INVALID_HANDLE_VALUE) {
		return E_FAIL;
	}

	// ファイルフォーマット読み込み
	MP3FormatInfo format;
	readSize = ReadMP3Format(hFile, &format);
	if(readSize == 0) {
		return E_FAIL;
	}

	// サウンドフレームヘッダ読み込み
	MP3FrameInfo frame;
	readSize = ReadMP3FrameHeader(hFile, format.offset, &frame);
	if(readSize == 0) {
		return E_FAIL;
	}

	// サウンドデータ読み込み
	readSize = ReadMP3Data(hFile, format.offset, format.dataSize, &frame, pData);
	if (readSize == 0) {
		return E_FAIL;
	}

	return S_OK;
}
/**
 * @brief MP3フォーマットチェック
 * @param[in] hFile ファイルポインタ
 * @param[out] pFormat ファイルフォーマット
 * @return データサイズ
 */
DWORD ReadMP3Format(HANDLE hFile, MP3FormatInfo *pFormat)
{
	DWORD readSize;

	// MP3ファイルサイズ
	DWORD fileSize = GetFileSize(hFile, NULL);

	// ①ヘッダー/フッターの有無を調べる
	/*----------
	* ID3v1
	*  -末尾にタグがあるorタグなし
	*  [MP3データ]
	*		or
	*	[MP3データ]["TAG"(3byte)][タグ情報(125byte)]
	* ID3v2
	*  -先頭にタグがある
	*	["ID3"(3byte)][バージョン(2byte)][フラグ(1byte)][タグサイズ(4byte)][拡張ヘッダ][MP3データ]
	*----------*/
	const BYTE ID3V2_HEADER_SIZE = 10;
	BYTE header[ID3V2_HEADER_SIZE];	// ヘッダー情報
	ReadFile(hFile, header, sizeof(header), &readSize, NULL);

	// タグをチェックし、MP3データの位置、サイズを計算
	const char *ID3V1_TAG = "TAG";
	const char *ID3V2_TAG = "ID3";
	const BYTE MP3_TAG_SIZE = 3;
	if (memcmp(header, ID3V2_TAG, MP3_TAG_SIZE) == CMP_MATCH)
	{
		// ID3v2ヘッダー情報解析
		/*----------
		* [拡張ヘッダ]のデータサイズについて
		*  [タグサイズ]のデータ構造
		*	 [0AAAAAAA][0BBBBBBB][0CCCCCCC][0DDDDDDD]
		*	実際のデータサイズ
		*	 0x0000AAAAAAABBBBBBBCCCCCCCDDDDDDD
		*
		* - データの最上位ビットは必ず0
		*	 実際のサイズは、0を省いて詰めたもの
		*----------*/
		DWORD exHeaderSize =
			(header[6] << 21) |
			(header[7] << 14) |
			(header[8] << 7) |
			(header[9]);
		pFormat->offset = exHeaderSize + ID3V2_HEADER_SIZE;
		pFormat->dataSize = fileSize - pFormat->offset;
	}
	else
	{
		// ID3v1フッター情報解析
		const BYTE ID3V1_FOOTER_SIZE = 128;
		BYTE tag[MP3_TAG_SIZE];
		SetFilePointer(hFile, fileSize - ID3V1_FOOTER_SIZE, NULL, FILE_BEGIN);
		ReadFile(hFile, tag, MP3_TAG_SIZE, &readSize, NULL);
		pFormat->offset = 0;
		if (memcmp(tag, ID3V1_TAG, MP3_TAG_SIZE) == CMP_MATCH)
		{
			pFormat->dataSize = fileSize - 128;
		}
		else
		{
			pFormat->dataSize = fileSize;
		}
	}
	return pFormat->dataSize;
}


/** 
 * @brief MP3サウンドフレームヘッダ読み込み
 * @param[in] hFile ファイルポインタ
 * @param[in] seek フレーム読み込み位置
 * @param[out] pFrame フレーム情報
 * @return 読み込みサイズ
 */ 
DWORD ReadMP3FrameHeader(HANDLE hFile, DWORD seek, MP3FrameInfo *pFrame)
{
	DWORD readSize;

	// ①フレームヘッダから情報を取得
	/*----------
	 * MP3データの構造
	 *	[フレームヘッダ(4byte)][データ]
	 *	[フレームヘッダ(4byte)][データ]
	 *	[フレームヘッダ(4byte)][データ]
	 *	...(繰り返し
	 *----------*/
	// MP3データ位置へ移動
	SetFilePointer(hFile, seek, NULL, FILE_BEGIN);

	/*----------
	 * フレームヘッダ情報
	 * http://www.cactussoft.co.jp/Sarbo/divMPeg3UnmanageHeader.html
	 *	[AAAAAAAA][AAABBCCD][EEEEFFGH][IIJJKLMM]
	 *	 A - 同期ビット(必ず１)
	 *	 B - MP3のバージョン
	 *		00 - MPEG2.5
	 *		01 - 予約
	 *		10 - MPEG2
	 *		11 - MPEG1
	 *	 C - レイヤー
	 *		00 - 予約
	 *		01 - Layer3
	 *		10 - Layer2
	 *		11 - Layer1
	 *	 D - CRC誤り検出の有無
	 *	 E - ビットレート
	 *	 F - サンプリング周波数
	 *	 G - パディング(フレームの最後のデータが0xFFだった場合、
	 *		 次のフレームの頭とつながるため、フレームの最後にNULLが挿入される
	 *		 実際にデータが挿入されたかどうかの情報をもつ
	 *	 H - 拡張(未使用
	 *	 I - チャンネルモード
	 *	 J - 拡張
	 *	 K - 著作権の有無
	 *	 L - オリジナル(コピーorオリジナル
	 *	 M - 強調
	 *
	 *	- 最低限必要な情報はB,C,E,F,G,I
	 *----------*/
	const BYTE FRAME_HEADER_SIZE = 4;
	BYTE frameHeader[FRAME_HEADER_SIZE];
	ReadFile(hFile, frameHeader, FRAME_HEADER_SIZE, &readSize, NULL);

	// 同期ビットチェック
	if (!(frameHeader[0] == 0xFF && (frameHeader[1] & 0xE0) == 0xE0)) {
		return 0;
	}

	// バージョン
	BYTE version = (frameHeader[1] >> 3) & 0b11;

	// レイヤー
	BYTE layer = (frameHeader[1] >> 1) & 0b11;

	// ビットレート(単位はkbit/sec
	const int bitRateTable[][16] = {
		// MPEG1, Layer1
		{ 0, 32, 64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448, -1 },
		// MPEG1, Layer2
		{ 0, 32, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, 384, -1 },
		// MPEG1, Layer3
		{ 0, 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, -1 },
		// MPEG2, Layer1
		{ 0, 32, 48, 56, 64, 80, 96, 112, 128, 144, 160, 176, 192, 224, 256, -1 },
		// MPEG2/2.5, Layer2,3
		{ 0, 8, 16, 24, 32, 40, 48, 56, 64, 80, 96, 112, 128, 144, 160, -1 }
	};
	BYTE bitRateTableIndex;
	if (version == 0b11) {
		bitRateTableIndex = 0b11 - layer;
	}
	else if (version == 0b10 && layer == 0b11) {
		bitRateTableIndex = 3;
	}
	else {
		bitRateTableIndex = 4;
	}
	WORD bitRate = bitRateTable[bitRateTableIndex][frameHeader[2] >> 4];

	// サンプリングレート
	const int sampleRateTable[][4] = {
		// MPEG1
		{ 44100, 48000, 32000, -1 },
		// MPEG2
		{ 22050, 24000, 16000, -1 },
		// MPEG2.5
		{ 11025, 12000, 8000, -1 },
	};
	BYTE sampleRateTableIndex;
	switch (version) {
	case 0b00: sampleRateTableIndex = 2; break;
	case 0b10: sampleRateTableIndex = 1; break;
	case 0b11: sampleRateTableIndex = 0; break;
	default: return E_FAIL;
	}
	WORD sampleRate = sampleRateTable[sampleRateTableIndex][(frameHeader[2] >> 2) & 0b11];

	// パディング
	BYTE padding = (frameHeader[2] >> 1) & 0b01;

	// チャンネル
	BYTE channel = frameHeader[3] >> 6;


	// フレームサイズ
	// ビットレートはkbit/secなのでbit/secに変換するために1000倍する
	const int samplePerFrame[][4] = {
		// layer1
		{ 384, 384, 384, -1 },
		// layer2
		{ 1152, 1152, 1152, -1 },
		// layer3
		{ 1152, 576, 576, -1 }
	};
	WORD frameBlockSize = ((samplePerFrame[0b11 - layer][sampleRateTableIndex] * bitRate * 1000 / 8) / sampleRate) + padding;

	// ②取得した情報をもとにMEPGLAYER3WAVEFORMATにデータ設定
	/*----------
	 *	MPEGLAYER3WAVEFORMAT
	 *	http://www.cactussoft.co.jp/Sarbo/divMPeg3UnmanageStruct.html
	 *	 - mpegオーディオレイヤー3(mp3)を扱うために拡張されたWAVEFORMAT構造体
	 *	.wfx.cbSize				- 構造体の拡張サイズ、MPEGLAYER3_WFX_EXTRA_BYTESを指定
	 *	.wfx.nChannels			- チャンネル数、モノラル＝１、ステレオ＝２
	 *	.wfx.wFormatTag			- mp3を表す、WAVE_FORMAT_MPEGLAYER3を指定
	 *	.wfx.nBlockAlign		- 1を指定
	 *	.wfx.wBitsPerSample		- 0を指定
	 *	.wfx.nSamplesPerSec		- サンプリング周波数
	 *	.wfx.nAvgBytesPerSec	- 1秒間に必要なデータサイズ
	 *	wID						- MPEGLAYER3_ID_MPEGを指定
	 *	fdwFlags				- パディングの挿入があれば指定
	 *	nFramesPerBlock			- 1つのブロックに配置するフレーム数
	 *	nBlockSize				- ブロックサイズ(フレームサイズ * フレーム数)
	 *	nCodecDelay				- 1393(0x571)を指定
	 *----------*/

	// channel
	// sample
	// bitRate
	// padding
	pFrame->channel = channel == 0x11 ? 1 : 2;
	pFrame->sampleRate = sampleRate;
	pFrame->bitRate = bitRate;
	pFrame->padding = padding;
	pFrame->frameSize = frameBlockSize;

	return pFrame->frameSize;
}

/**
 * @brief MP3サウンドデータ読み込み
 * @param[in] hFile ファイルポインタ
 * @param[in] seek フレーム読み込み位置
 * @param[in] size 読み込みデータ量
 * @param[in] pFrame フレーム情報
 * @param[out] pData サウンドデータ
 * @return 読み込みサイズ
 */
DWORD ReadMP3Data(HANDLE hFile, DWORD seek, DWORD size, MP3FrameInfo *pFrame, SoundData *pData)
{
	// 変換フォーマット作成
	MPEGLAYER3WAVEFORMAT mp3WavFormat;
	mp3WavFormat.wfx.cbSize = MPEGLAYER3_WFX_EXTRA_BYTES;
	mp3WavFormat.wfx.nChannels = pFrame->channel;
	mp3WavFormat.wfx.wFormatTag = WAVE_FORMAT_MPEGLAYER3;
	mp3WavFormat.wfx.nBlockAlign = 1;
	mp3WavFormat.wfx.wBitsPerSample = 0;
	mp3WavFormat.wfx.nSamplesPerSec = pFrame->sampleRate;
	mp3WavFormat.wfx.nAvgBytesPerSec = (pFrame->bitRate * 1000) / 8;

	mp3WavFormat.wID = MPEGLAYER3_ID_MPEG;
	mp3WavFormat.fdwFlags = pFrame->padding ? MPEGLAYER3_FLAG_PADDING_ON : MPEGLAYER3_FLAG_PADDING_OFF;
	mp3WavFormat.nFramesPerBlock = 1;
	mp3WavFormat.nBlockSize = static_cast<WORD>(pFrame->frameSize * mp3WavFormat.nFramesPerBlock);
	mp3WavFormat.nCodecDelay = 0x571;

	// mp3をwavへ変換可能か
	// 変換可能であれば,wavFormatへデータを設定
	WAVEFORMATEX wavFormat;
	wavFormat.wFormatTag = WAVE_FORMAT_PCM;
	MMRESULT mmr;
	mmr = acmFormatSuggest(NULL, &mp3WavFormat.wfx, &wavFormat, sizeof(WAVEFORMATEX), ACM_FORMATSUGGESTF_WFORMATTAG);
	if (mmr != MMSYSERR_NOERROR) {
		return 0;
	}

	// ACMストリームオープン
	// mp3からwavへフォーマット変換
	HACMSTREAM has;
	mmr = acmStreamOpen(&has, NULL, &mp3WavFormat.wfx, &wavFormat, NULL, NULL, NULL, 0);

	// MP3のブロックサイズからWAVE形式へデコード後のサイズを取得
	DWORD waveBlockSize;
	acmStreamSize(has, size, &waveBlockSize, ACM_STREAMSIZEF_SOURCE);

	// 変換データセット
	ACMSTREAMHEADER ash = { 0 };
	ash.cbStruct = sizeof(ACMSTREAMHEADER);
	ash.cbSrcLength = size;
	ash.pbSrc = new BYTE[ash.cbSrcLength];
	ash.cbDstLength = waveBlockSize;
	ash.pbDst = new BYTE[ash.cbDstLength];

	// デコード
	acmStreamPrepareHeader(has, &ash, 0);
	DWORD readSize;
	SetFilePointer(hFile, seek, NULL, FILE_BEGIN);
	ReadFile(hFile, ash.pbSrc, ash.cbSrcLength, &readSize, NULL);
	mmr = acmStreamConvert(has, &ash, 0);
	acmStreamUnprepareHeader(has, &ash, 0);
	acmStreamClose(has, 0);

	// wavデータコピー
	if (ash.cbDstLengthUsed > 0) {
		pData->bufSize = ash.cbDstLengthUsed;
		pData->pBuffer = new BYTE[pData->bufSize];
		pData->format = wavFormat;
		memcpy_s(pData->pBuffer, pData->bufSize,
			ash.pbDst, ash.cbDstLengthUsed);
	}

	delete[] ash.pbSrc;
	delete[] ash.pbDst;

	CloseHandle(hFile);

	return ash.cbSrcLengthUsed;
}



// EOF
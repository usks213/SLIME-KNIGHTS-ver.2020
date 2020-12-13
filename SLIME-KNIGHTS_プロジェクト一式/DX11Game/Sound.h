/*
InitSound�֐���LoadTexture�֐�����ɌĂяo���ƃG���[
��������COM�I�u�W�F�N�g�𗘗p���邽��

���X�i�[
���𕷂����߂́u���v�ɑ����B3D�T�E���h�ŕK�v�B
�\�[�X
���𔭂���u�����v�ɑ����B�X�s�[�J�[�BXAudio2�ł�Voice�ƌĂ΂��B
�o�b�t�@
���f�[�^���i�[���Ă����o�b�t�@�BWAV�t�@�C���AOGG�t�@�C���Ȃǂ��烍�[�h�B
 */
#ifndef __SOUND_H__
#define __SOUND_H__

#include <xaudio2.h>

#pragma comment(lib, "xaudio2.lib")

//----------
// �v���g�^�C�v�錾
//----------
class CSound
{
public:
	CSound();
	~CSound();

	// ������
	static HRESULT InitSound(void);
	// �I������
	static void UninitSound(void);

	// �T�E���h�ƃ\�[�X�̍쐬
	void Load(const char *file, bool loop = false);
	// �T�E���h�ƃ\�[�X�̔j��
	//void Destroy();

	// �T�E���h�̍Đ� (�e�ݒ��������)
	void Play(float fVolume = 1.0f, float = 0.0f);

	// �T�E���h�̒�~
	void Stop();
	
private:
	XAUDIO2_BUFFER* m_pSound;
	IXAudio2SourceVoice* m_pSource;

	// �T�E���h�̓ǂݍ���
	static XAUDIO2_BUFFER* CreateSound(const char *file, bool loop = false);
	// �T�E���h�̍Đ�
	static IXAudio2SourceVoice* PlaySound(XAUDIO2_BUFFER* pSound);
};


#endif // __SOUND_H__
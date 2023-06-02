#include "DxLib.h"

// �v���O�����̍ŏ���WinMain�Ŏn�߂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    //##### �����ݒ� #####//
    // �E�B���h�E���[�h�ݒ�
    ChangeWindowMode(TRUE);

    // ��ʃT�C�Y�ݒ�
    int width = 1920;
    int height = 1080;
    SetGraphMode(width, height, 32);

    // DX���C�u��������������
    if (DxLib_Init() == -1) {
        return -1; // �G���[���N�����璼���ɏI��
    }



    //## ���ɉ����Đݒ�
    // �ړ����̂̔��T�C�Y
    int size = 60;

    // �����l
    // ���t���̃t���[�����[�g�ɂ���ĕω����邱�Ƃ��킩���Ă��邽��
    // ��������������ꍇ�₨��������ꍇ�͂��̐��l�𒲐����邱�ƁB
    float decay = 0.97; // 60=0.97 300=0.9925 or 0.99

    // �L�[���͎��̈ړ����x
    int moveSpeed = 15;

    // ���@���l
    // ���t���̃t���[�����[�g�ɂ���ĕω����邱�Ƃ��킩���Ă��邽��
    // ��������������ꍇ�₨��������ꍇ�͂��̐��l�𒲐����邱�ƁB
    float divisor = 0.25; // 60=0.25 300=0.01



    //## �ŗL�̐ݒ�
    // ���̃T�C�Y�̔������v�Z
    int sizeCenter = size / 2;

    // �F�̐ݒ�
    unsigned int mainColor = GetColor(0, 0, 255);
    unsigned int subColor = GetColor(255, 0, 0);

    // �ړ����̏������W�ݒ�
    int x = width / 2;
    int y = height / 2;

    // �������̏������W�ݒ�
    int centerX = width / 2;
    int centerY = height / 2;

    // �}�E�X���W�擾
    int mouseX = 0;
    int mouseY = 0;

    // �^���x�N�^�n���i�[
    int RelativeX = 0;
    int RelativeY = 0;
    float MotionX = 0;
    float MotionY = 0;

    // �����蔻��������I�u�W�F�N�g�̊i�[
    bool obj = false;
    int objX = 100;
    int objY = 400;



    // ���C�����[�v�i�`�揈���j
    while (ProcessMessage() == 0) {
        // ��ʂ̍X�V
        ClearDrawScreen();



        //##### �������� �ړ����̂̏���
        // ���S�Ƃ̑��΃x�N�^�[�̎擾
        RelativeX = centerX - x;
        RelativeY = centerY - y;

        // �����������^���x�N�^�ɗݐω��Z
        MotionX += RelativeX * divisor;
        MotionY += RelativeY * divisor;

        // �^���x�N�^���g���Ĉړ�
        x += MotionX;
        y += MotionY;

        // �{�[���̉^���x�N�^������������
        MotionX *= decay;
        MotionY *= decay;



        //##### �������� �������̂̏���
        // �}�E�X���W�̎擾
        GetMousePoint(&mouseX, &mouseY);

        // �}�E�X�N���b�N�Œ��S���̂̍��W�ƐF��ύX
        if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
            subColor = GetColor(0, 255, 0);
            centerX = mouseX - sizeCenter; // �}�E�X���W�͍��オ���_�Ȃ̂ŁA���S���W�ɍ��킹�邽�߂ɐ}�`��2����1��������
            centerY = mouseY - sizeCenter;
        }
        else {
            subColor = GetColor(255, 0, 0);
        }

        // �L�[�ňړ�������
        int input = GetJoypadInputState(DX_INPUT_KEY_PAD1);
        if (input & PAD_INPUT_RIGHT) {
            centerX += moveSpeed;
        }
        if (input & PAD_INPUT_LEFT) {
            centerX -= moveSpeed;
        }
        if (input & PAD_INPUT_UP) {
            centerY -= moveSpeed;
        }
        if (input & PAD_INPUT_DOWN) {
            centerY += moveSpeed;
        }

        // ���S���͉̂𑜓x�O�ɏo���Ȃ�
        if (centerX < 0) {
            centerX = 0;
        }
        if (centerX > width - size) {
            centerX = width - size;
        }
        if (centerY < 0) {
            centerY = 0;
        }
        if (centerY > height - size) {
            centerY = height - size;
        }



        //##### �������� �`�揈��
        // �l�p��`�� DrawBox(����X���W, ����Y���W, �E��X���W, �E��Y���W, �F, �h��Ԃ��t���O)

        // �j��\�ȃI�u�W�F�N�g���܂�1�����p�ӁB
        // �ړ����̂Ɠ���̈ʒu�ɐݒu���ꂽ�I�u�W�F�N�g���G�ꂽ��F��ς���
        if (x + size > objX && x < objX + (size * 3) && y + size > objY && y < objY + (size * 3)) obj = true;
        if (!obj) DrawBox(objX, objY, objX + (size * 3), objY + (size * 3), GetColor(255, 255, 255), TRUE);

        // ���S���̕`��
        DrawBox(centerX, centerY, centerX + size, centerY + size, subColor, TRUE);
        // �ړ����̕`��
        DrawBox(x, y, x + size, y + size, mainColor, TRUE);
        // ���̂̒��S�ƒ��S����Ō���
        DrawLine(x + sizeCenter, y + sizeCenter, centerX + sizeCenter, centerY + sizeCenter, GetColor(255, 255, 255));

        // �f�o�b�O�p
        printfDx("x:%d y:%d\n", x, y);
        printfDx("centerX:%d centerY:%d\n", centerX, centerY);
        printfDx("RelativeX:%d RelativeY:%d\n", RelativeX, RelativeY);
        printfDx("MotionX:%f MotionY:%f\n", MotionX, MotionY);

        // ��ʂ̍X�V�i�K�{�j
        ScreenFlip();
        clsDx(); // �f�o�b�O���O��ʂ��N���A���鏈��
    }

    DxLib_End(); // DX Library�̎g�p���I�����鏈��
    return 0;    // �\�t�g�𐳏�I��
}
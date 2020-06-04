#ifndef INIT_H
#define INIT_H

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BLOCKSIZE 1024 // ���̿��С��һ��Ϊ512B��2^n�α�
#define BLOCKNUM 1000 // ���̿�����
#define SIZE BLOCKNUM*BLOCKSIZE // ���̿ռ��С
#define END 65535 // FAT���ļ�������־
#define FREE 0 // FAT���̿���б�־
#define ROOTBLOCKNUM 2 // ��Ŀ¼��ʼ��ռ�̿��С
#define MAXOPENFILE 10 // ͬʱ������ļ���
#define MAX_TEXT_SIZE 10000 // �����ı���������С

// �ļ����ƿ�
typedef struct FCB {
    char filename[8]; // �ļ���
    char exname[3]; // �ļ���չ��
    unsigned char attribute; // 0: Ŀ¼�ļ�, 1: �����ļ�
    unsigned short time; // ����ʱ��
    unsigned short date; // ��������
    unsigned short first; // �ļ���ʼ�̿��
    unsigned short length; // �ļ����ȣ��ֽ�����
    char free; // 0: �� 1: �ѷ���
} fcb;

/**
 * ��¼ÿ���ļ���ռ�ݴ��̿�Ŀ��
 * ��¼��Щ�鱻�ֳ�ȥ
 * ֵΪFREE��ʾ���У�ֵΪEND��ʾ�ļ����һ�����̺�
*/
typedef struct FAT {
    unsigned short id;
} fat;

/**
 * �û����ļ���
*/
typedef struct USEROPEN {
    char filename[8]; // �ļ���
    char exname[3]; // ��չ��
    unsigned char attribute; //���� 0:Ŀ¼�ļ� 1:�����ļ�
    unsigned short time; // ����ʱ��
    unsigned short date; // ��������
    unsigned short first; // �ļ���ʼ�̿��
    unsigned short length; // �ļ����� (�ֽ���)
    char free;

    //������FCB����Ϣ

    int dirno; // ��Ŀ¼�ļ���ʼ�̿��
    int diroff; // ���ļ���Ӧ�� fcb �ڸ�Ŀ¼�е��߼����
    char dir[100]; // ȫ·����Ϣ
    int count; // ��дָ��λ��
    char fcbstate; // �Ƿ��޸� 1�� 0��
    char topenfile; // �򿪱� 0: �� �����ʾռ��
} useropen;

// ������
typedef struct BLOCK {
    char information[200]; // ������Ϣ ���̿��С ���̿�����
    unsigned short root; // ��Ŀ¼��ʼ�̿��
    unsigned char* startblock; // ��������ʼλ��
} block0;

// ȫ�ֱ���

unsigned char* myvhard; // ָ��������̵���ʼ��ַ
useropen openfilelist[MAXOPENFILE]; // �û����ļ�������
int currfd; // ��ǰĿ¼���ļ�������fd
unsigned char* startp; // ��������ʼ��λ��
char* copytextbuf; // copy������

/* ϵͳ��Ҫ������� */
void startsys(); // �����ļ�ϵͳ
void my_format(); // ��������̽��г�ʼ��
void my_cd(char* dirname); // ���ĵ�ǰĿ¼
int do_read(int fd, int len, char* text);
int do_write(int fd, char* text, int len, char wstyle);
int my_read(int fd);
int my_write(int fd);

void exitsys();
void my_cd(char* dirname);
int my_open(char* filename);
int my_close(int fd);
void my_mkdir(char* dirname);
void my_rmdir(char* dirname);
int my_create(char* fullname);
void my_rm(char* filename); // ɾ���ļ�
void my_ls(); // ��ʾĿ¼����
void help(); // ������Ϣ
void my_search(char* fullname); // ����

int get_free_openfilelist();
unsigned short int get_free_block();
void set_create_time(unsigned short* create_date, unsigned short* create_time);

void get_name(char* name, int size, char* rawname); //���û��'\0'������

#endif

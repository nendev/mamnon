#ifndef LOPHOC_H
#define LOPHOC_H

#define TABLE_SIZE 10 // Kích thước bảng băm
struct LopHoc {
    char maLop[10];
    char tenHocPhan[50];
    char tenGiaoVien[50];
    struct LopHoc* next;
};

struct SListLopHoc {
    struct LopHoc* Head;
    struct LopHoc* Tail;
};

void initHashTable(struct SListLopHoc* table);
int hashFunction(const char* maLop);
void insertLopHoc(struct SListLopHoc* table, struct LopHoc* newNode);
void docDuLieuLopHocTuFile(struct SListLopHoc* table, const char* tenFile);
void inHashTable(struct SListLopHoc* table);

#endif

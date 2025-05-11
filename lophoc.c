#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lophoc.h"

void initHashTable(struct SListLopHoc* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i].Head = NULL;
        table[i].Tail = NULL;
    }
}

int hashFunction(const char* maLop) {
    int sum = 0;
    for (int i = 0; maLop[i] != '\0'; i++) {
        sum += maLop[i];
    }
    return sum % TABLE_SIZE;
}

void insertLopHoc(struct SListLopHoc* table, struct LopHoc* newNode) {
    int index = hashFunction(newNode->maLop);

    newNode->next = NULL;
    if (table[index].Head == NULL) {
        table[index].Head = table[index].Tail = newNode;
    } else {
        table[index].Tail->next = newNode;
        table[index].Tail = newNode;
    }
}

void docDuLieuLopHocTuFile(struct SListLopHoc* table, const char* tenFile) {
    FILE* f = fopen(tenFile, "r");
    if (f == NULL) {
        printf("Khong the mo file %s\n", tenFile);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        struct LopHoc* newNode = (struct LopHoc*)malloc(sizeof(struct LopHoc));
        if (!newNode) continue;

        // Loại bỏ ký tự newline ở cuối dòng nếu có
        line[strcspn(line, "\n")] = '\0';

        char* token = strtok(line, "|");
        if (token) strncpy(newNode->maLop, token, sizeof(newNode->maLop));

        token = strtok(NULL, "|");
        if (token) strncpy(newNode->tenHocPhan, token, sizeof(newNode->tenHocPhan));

        token = strtok(NULL, "|");
        if (token) strncpy(newNode->tenGiaoVien, token, sizeof(newNode->tenGiaoVien));

        // Xóa khoảng trắng thừa 2 đầu
        for (char* s = newNode->maLop; *s == ' '; s++) memmove(newNode->maLop, s, strlen(s) + 1);
        for (char* s = newNode->tenHocPhan; *s == ' '; s++) memmove(newNode->tenHocPhan, s, strlen(s) + 1);
        for (char* s = newNode->tenGiaoVien; *s == ' '; s++) memmove(newNode->tenGiaoVien, s, strlen(s) + 1);

        insertLopHoc(table, newNode);
    }

    fclose(f);
}


void inHashTable(struct SListLopHoc* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Bucket %d:\n", i);
        struct LopHoc* p = table[i].Head;
        while (p != NULL) {
            printf("Ma lop:%s | Ten Hoc Phan: %s | Giao Vien: %s\n",
                   p->maLop, p->tenHocPhan, p->tenGiaoVien);
            p = p->next;
        }
    }
}

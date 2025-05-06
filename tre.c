#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tre.h"

void initHashTableTre(struct SListTre* hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i].Head = NULL;
        hashTable[i].Tail = NULL;
    }
}

int hashFunctionTre(const char* maTre) {
    int sum = 0;
    for (int i = 0; maTre[i] != '\0'; i++) {
        sum += maTre[i];
    }
    return sum % TABLE_SIZE;
}

void insertTre(struct SListTre* hashTable, struct Tre* newNode) {
    int index = hashFunctionTre(newNode->maTre);

    newNode->next = NULL;
    if (hashTable[index].Head == NULL) {
        hashTable[index].Head = hashTable[index].Tail = newNode;
    } else {
        hashTable[index].Tail->next = newNode;
        hashTable[index].Tail = newNode;
    }
}

void docDuLieuTreTuFile(struct SListTre* hashTable, const char* tenFile) {
    FILE* f = fopen(tenFile, "r");
    if (f == NULL) {
        printf("Khong the mo file %s\n", tenFile);
        return;
    }

    char line[512];
    while (fgets(line, sizeof(line), f)) {
        struct Tre* newNode = (struct Tre*)malloc(sizeof(struct Tre));
        if (!newNode) continue;

        line[strcspn(line, "\n")] = '\0';

        // Dữ liệu trong file: maTre | hoLot | ten | ngay/thang/nam | hoPhuHuynh | soDienThoai | moiQuanHe | maLop
        char ngaySinhStr[15];
        char* token = strtok(line, "|");
        if (token) strncpy(newNode->maTre, token, sizeof(newNode->maTre));

        token = strtok(NULL, "|");
        if (token) strncpy(newNode->hoLot, token, sizeof(newNode->hoLot));

        token = strtok(NULL, "|");
        if (token) strncpy(newNode->ten, token, sizeof(newNode->ten));

        token = strtok(NULL, "|");
        if (token) {
            strncpy(ngaySinhStr, token, sizeof(ngaySinhStr));
            sscanf(ngaySinhStr, "%d/%d/%d", &newNode->ngay, &newNode->thang, &newNode->nam);
        }

        token = strtok(NULL, "|");
        if (token) strncpy(newNode->hoPhuHuynh, token, sizeof(newNode->hoPhuHuynh));

        token = strtok(NULL, "|");
        if (token) strncpy(newNode->soDienThoai, token, sizeof(newNode->soDienThoai));

        token = strtok(NULL, "|");
        if (token) strncpy(newNode->moiQuanHe, token, sizeof(newNode->moiQuanHe));

        token = strtok(NULL, "|");
        if (token) strncpy(newNode->maLop, token, sizeof(newNode->maLop));

        insertTre(hashTable, newNode);
    }

    fclose(f);
}

void inHashTableTre(struct SListTre* hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Bucket %d:\n", i);
        struct Tre* p = hashTable[i].Head;
        while (p != NULL) {
            printf("  Ma Tre: %s | Họ: %s | Tên: %s | Ngày Sinh: %02d/%02d/%04d | Phụ huynh: %s | Sđt: %s | Mối quan hệ: %s | Mã lớp: %s\n",
                   p->maTre, p->hoLot, p->ten, p->ngay, p->thang, p->nam,
                   p->hoPhuHuynh, p->soDienThoai, p->moiQuanHe, p->maLop);
            p = p->next;
        }
    }
}
void themMotTre(struct SListTre* hashTable, const char* tenFile) {
    struct Tre newTre;
    printf("Nhap ma tre: ");
    fgets(newTre.maTre, sizeof(newTre.maTre), stdin);
    newTre.maTre[strcspn(newTre.maTre, "\n")] = '\0';

    printf("Nhap ho lot: ");
    fgets(newTre.hoLot, sizeof(newTre.hoLot), stdin);
    newTre.hoLot[strcspn(newTre.hoLot, "\n")] = '\0';

    printf("Nhap ten: ");
    fgets(newTre.ten, sizeof(newTre.ten), stdin);
    newTre.ten[strcspn(newTre.ten, "\n")] = '\0';

    printf("Nhap ngay sinh (dd): ");
    scanf("%d", &newTre.ngay);
    printf("Nhap thang sinh (mm): ");
    scanf("%d", &newTre.thang);
    printf("Nhap nam sinh (yyyy): ");
    scanf("%d", &newTre.nam);
    getchar(); // bỏ newline

    printf("Nhap ho phu huynh: ");
    fgets(newTre.hoPhuHuynh, sizeof(newTre.hoPhuHuynh), stdin);
    newTre.hoPhuHuynh[strcspn(newTre.hoPhuHuynh, "\n")] = '\0';

    printf("Nhap so dien thoai: ");
    fgets(newTre.soDienThoai, sizeof(newTre.soDienThoai), stdin);
    newTre.soDienThoai[strcspn(newTre.soDienThoai, "\n")] = '\0';

    printf("Nhap moi quan he: ");
    fgets(newTre.moiQuanHe, sizeof(newTre.moiQuanHe), stdin);
    newTre.moiQuanHe[strcspn(newTre.moiQuanHe, "\n")] = '\0';

    printf("Nhap ma lop: ");
    fgets(newTre.maLop, sizeof(newTre.maLop), stdin);
    newTre.maLop[strcspn(newTre.maLop, "\n")] = '\0';

    // Ghi thêm vào file
    FILE* f = fopen(tenFile, "a");
    if (f == NULL) {
        printf("Khong mo duoc file %s de ghi.\n", tenFile);
        return;
    }
    fprintf(f, "%s | %s | %s | %02d/%02d/%04d | %s | %s | %s | %s\n",
            newTre.maTre, newTre.hoLot, newTre.ten, newTre.ngay, newTre.thang, newTre.nam,
            newTre.hoPhuHuynh, newTre.soDienThoai, newTre.moiQuanHe, newTre.maLop);
    fclose(f);

    // Xóa bảng băm cũ
    initHashTableTre(hashTable);

    // Đọc lại toàn bộ từ file
    docDuLieuTreTuFile(hashTable, tenFile);

    printf("Da them tre moi va cap nhat danh sach!\n");
}

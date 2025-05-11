#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tre.h"
#include "lophoc.h"

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
void trim(char* s) {
    // Trim đầu
    while (*s == ' ') memmove(s, s + 1, strlen(s));

    // Trim cuối
    size_t len = strlen(s);
    while (len > 0 && s[len - 1] == ' ') {
        s[len - 1] = '\0';
        len--;
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
        if (token) 
        {
            strncpy(newNode->maTre, token, sizeof(newNode->maTre));
        }

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

        for (char* s = newNode->maTre; *s == ' '; s++) memmove(newNode->maTre, s, strlen(s) + 1);
        insertTre(hashTable, newNode);
    }

    fclose(f);
}

void inHashTableTre(struct SListTre* hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Bucket %d:\n", i);
        struct Tre* p = hashTable[i].Head;
        while (p != NULL) {
            printf("Ma Tre:%s | Họ: %s | Tên: %s | Ngày Sinh: %02d/%02d/%04d | Phụ huynh: %s | Sđt: %s | Mối quan hệ: %s | Mã lớp: %s\n",
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

// Cau 4: Tim kiem tre theo tieu chi: ho ten giao vien or ma tre or ten lop - Ngo Gia Bao
void timKiemTre(struct SListTre* hashTre, struct SListLopHoc* hashLop) {
    int luaChon;
    char tuKhoa[100];

    printf("=== TIM KIEM TRE ===\n");
    printf("1. Tim theo ho ten giao vien\n");
    printf("2. Tim theo ma tre\n");
    printf("3. Tim theo ten lop\n");
    printf("Nhap lua chon (1-3): ");
    scanf("%d", &luaChon);
    getchar(); // Xóa ký tự '\n' dư

    printf("Nhap tu khoa can tim: ");
    fgets(tuKhoa, sizeof(tuKhoa), stdin);
    tuKhoa[strcspn(tuKhoa, "\n")] = '\0';

    int timThay = 0;

    switch (luaChon)
    {
    case 1:
        // Tìm kiếm theo tên họ tên giáo viên
        for (int i = 0; i < TABLE_SIZE; i++) {
            for (struct LopHoc* lop = hashLop[i].Head; lop != NULL; lop = lop->next) {
                if (strcmp(lop->tenGiaoVien, tuKhoa) == 0) {
                    // Tìm trẻ học lớp có giáo viên đó
                    for (int j = 0; j < TABLE_SIZE; j++) {
                        for (struct Tre* tre = hashTre[j].Head; tre != NULL; tre = tre->next) {
                            if (strcmp(tre->maLop, lop->maLop) == 0) {
                                printf("Ma Tre: %s | Ho ten: %s %s | Ngay sinh: %02d%02d%04d | Lop: %s\n",
                                    tre->maTre, tre->hoLot, tre->ten, tre->ngay, tre->thang, tre->nam, tre->maLop);
                                timThay = 1;
                            }
                        }
                    }
                }
            }
        }
        break;
    case 2:
        // Tìm theo mã trẻ
        for (int i = 0; i < TABLE_SIZE; i++) {
            for (struct Tre* tre = hashTre[i].Head; tre != NULL; tre = tre->next) {
                if (strcmp(tre->maTre, tuKhoa) == 0) {
                    printf("Ma Tre: %s | Ho ten: %s %s | Ngay sinh: %02d%02d%04d | Lop: %s\n",
                           tre->maTre, tre->hoLot, tre->ten, tre->ngay, tre->thang, tre->nam, tre->maLop);
                    timThay = 1;
                }
            }
        }
        break;
    case 3:
        // Tìm theo tên lớp
        for (int i = 0; i < TABLE_SIZE; i++) {
            for (struct LopHoc* lop = hashLop[i].Head; lop != NULL; lop = lop->next) {
                if (strcmp(lop->tenHocPhan, tuKhoa) == 0) {
                    // Tìm trẻ có mã lớp trùng với lop->maLop
                    for (int j = 0; j < TABLE_SIZE; j++) {
                        for (struct Tre* tre = hashTre[j].Head; tre != NULL; tre = tre->next) {
                            
                            if (strcmp(tre->maLop, lop->maLop) == 0) {
                                printf("Ma tre: %s | Ho ten: %s %s | Ngay sinh: %02d%02d%04d | Lop: %s\n",
                                    tre->maTre, tre->hoLot, tre->ten, tre->ngay, tre->thang, tre->nam, tre->maLop);
                                timThay = 1;
                            }
                        }
                    }
                }
            }
        }
        break;
    default:
        printf("Lua chon khong hop le!\n");
        break;
    }

    if (!timThay)
        printf("Khong tim thay tre nao phu hop.\n");
}

// Câu 5: Tìm lớp học có số lượng trẻ theo học nhiều nhất - Ngo Gia Bao
int demTreTheoMaLop(struct SListTre* hashTre, char* maLop) { // Hàm đếm số lượng trẻ trong từng lớp
    int count = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        for (struct Tre* tre = hashTre[i].Head; tre != NULL; tre = tre->next) {
            if (strcmp(tre->maLop, maLop) == 0) {
                count++;
            }
        }
    }
    return count;
}

void timLopDongNhat(struct SListTre* hashTre, struct SListLopHoc* hashLop) { // Hàm tìm lớp có số lượng trẻ theo học nhiều nhất
    char maLopMax[20] = "";
    char tenGVMax[50] = "";
    int maxCount = 0;

    for (int i = 0; i < TABLE_SIZE; i++) {
        for (struct LopHoc* lop = hashLop[i].Head; lop != NULL; lop = lop->next) {
            int soTre = demTreTheoMaLop(hashTre, lop->maLop);
            if (soTre > maxCount) {
                maxCount = soTre;
                strcpy(maLopMax, lop->maLop);
                strcpy(tenGVMax, lop->tenGiaoVien);
            }
        }
    }

    if (maxCount > 0) {
        printf("Lop co nhieu tre nhat: %s (GV: %s) - So luong tre: %d\n", maLopMax, tenGVMax, maxCount);
    } else {
        printf("Khong co lop nao co tre.\n");
    }
}

// Câu 6: Sắp xếp danh sách trẻ theo tên lớp học, những trẻ học cùng một lớp sắp xếp theo tên trẻ tăng dần - Ngo Gia Bao
int soSanhTre(const void* a, const void* b) {
    struct Tre* t1 = *(struct Tre**)a;
    struct Tre* t2 = *(struct Tre**)b;

    int cmpLop = strcmp(t1->maLop, t2->maLop);
    if (cmpLop != 0)
        return cmpLop;
    
    return strcmp(t1->ten, t2->ten);
}

void sapXepTreTheoLopVaTen(struct SListTre* hashTre) {
    struct Tre* ds[1000];
    int count = 0;

    
    for (int i = 0; i < TABLE_SIZE; i++) {
        for (struct Tre* p = hashTre[i].Head; p != NULL; p = p->next) {
            ds[count++] = p;
        }
    }

    qsort(ds, count, sizeof(struct Tre*), soSanhTre);

    printf("Danh sach tre sau khi sap xep theo lop va ten tre:\n");
    for (int i = 0; i < count; i++) {
        printf("Ma lop: %s | Ten tre: %s %s | Ma tre: %s | Ngay sinh: %02d%02d%04d\n",
            ds[i]->maLop,
            ds[i]->hoLot,
            ds[i]->ten,
            ds[i]->maTre,
            ds[i]->ngay,
            ds[i]->thang,
            ds[i]->nam);
    }
}

// Câu 7: In ra thông tin của trẻ theo học lớp do giáo viên có họ Trần giảng dạy - Ngo Gia Bao
void inTreTheoGV(struct SListTre* hashTre, struct SListLopHoc* hashLop) {
    // Duyệt qua tất cả các bucket trong bảng băm của lớp
    for(int i = 0; i < TABLE_SIZE; i++){
        for (struct LopHoc* lop = hashLop[i].Head; lop != NULL; lop = lop->next) {
            // Kiểm tra họ giáo viên bắt đầu bằng "Trần"
            if (strncmp(lop->tenGiaoVien, "Tran", 4) == 0) {
                printf("-> Lớp %s do GV %s giảng dạy:\n", lop->maLop, lop->tenGiaoVien);

                // Duyệt qua tất cả các trẻ để tìm trẻ thuộc lớp này
                for (int j = 0; j < TABLE_SIZE; j++) {
                    for (struct Tre* tre = hashTre[j].Head; tre != NULL; tre = tre->next) {
                        if (strcmp(tre->maLop, lop->maLop) == 0) {
                            // In thông tin trẻ
                            printf("- Mã trẻ: %s, Họ tên: %s %s, Ngày sinh: %02d%02d%04d, Họ tên phụ huynh: %s, SDT: %s, MQH: %s\n",
                                tre->maTre, tre->hoLot, tre->ten, tre->ngay, tre->thang, tre->nam,
                                tre->hoPhuHuynh, tre->soDienThoai, tre->moiQuanHe);
                        }
                    }
                }
            }
        }
    }
}
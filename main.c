#include <stdio.h>
#include "lophoc.h"
#include "tre.h"
#include <windows.h>
void hienThiMenu() {
    printf("=============================================\n");
    printf("        QUAN LY LOP HOC & TRE EM\n");
    printf("=============================================\n");
    printf("1. In danh sach lop hoc (bang bam)\n");
    printf("2. In danh sach tre (bang bam)\n");
    printf("3. Them mot tre moi\n");
    printf("0. Thoat\n");
    printf("=============================================\n");
    printf("Chon chuc nang: ");
}
int main() {
    SetConsoleOutputCP(65001);
    struct SListLopHoc lopHocTable[TABLE_SIZE];
    struct SListTre treTable[TABLE_SIZE];

    initHashTable(lopHocTable);
    initHashTableTre(treTable);

    docDuLieuLopHocTuFile(lopHocTable, "lophoc.txt");
    printf("Da doc du lieu lop hoc!\n");
    docDuLieuTreTuFile(treTable, "tre.txt");
    printf("Da doc du lieu tre!\n");

    int luaChon;
    do {
        hienThiMenu();
        scanf("%d", &luaChon);
        getchar(); // Đọc bỏ ký tự newline

        switch (luaChon) {
            case 1:
                printf("===== DANH SACH LOP HOC (BANG BAM) =====\n");
                inHashTable(lopHocTable);
                break;

            case 2:
                printf("===== DANH SACH TRE EM (BANG BAM) =====\n");
                inHashTableTre(treTable);
                break;

            case 3:
                themMotTre(treTable, "tre.txt");
                break;

            case 0:
                printf("Dang thoat chuong trinh...\n");
                break;

            default:
                printf("Lua chon khong hop le. Vui long thu lai!\n");
                break;
        }

        printf("\nNhan phim Enter de tiep tuc...");
        getchar(); 
        system("clear"); // Linux/macOS; nếu dùng Windows thì thay bằng system("cls");
    } while (luaChon != 0);



    return 0;
}

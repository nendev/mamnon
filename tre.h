#ifndef TRE_H
#define TRE_H
#define TABLE_SIZE 10 
struct Tre {
    char maTre[10];
    char hoLot[30];
    char ten[30];
    int ngay;
    int thang;
    int nam;
    char hoPhuHuynh[30];
    char soDienThoai[15];
    char moiQuanHe[20];
    char maLop[10];
    struct Tre* next;
};

struct SListTre {
    struct Tre* Head;
    struct Tre* Tail;
};

void initHashTableTre(struct SListTre* hashTable);
int hashFunctionTre(const char* maTre);
void insertTre(struct SListTre* hashTable, struct Tre* newNode);
void docDuLieuTreTuFile(struct SListTre* hashTable, const char* tenFile);
void inHashTableTre(struct SListTre* hashTable);
void themMotTre(struct SListTre* hashTable,const char* tenFile);
#endif

#include <iostream>
#include <cstring>

using namespace std;

const int MAX_SIZE_DAUSACH = 100;
const int MAX_SIZE_SACH = 1000;

struct Sach{
    char masach[21];
    int trangthai;
};

struct DauSach{
    char ISBN[14];
    char tensach[41];
    char tacgia[21];
    char theloai[21];
    int sotrang;
    Sach *dsSach[MAX_SIZE_SACH];
    int sosach = 0;
};

struct DS_DauSach{
    int n = 0;
    DauSach *nodes[MAX_SIZE_DAUSACH];
};

void InsertDauSach(DS_DauSach &dsds, DauSach *dausach, int pos){
    for(int i=dsds.n-1; i>=pos; i--)
        dsds.nodes[i+1] = dsds.nodes[i];
    dsds.nodes[pos] = dausach;
    dsds.n++;
}

void ThemDauSach(DS_DauSach &dsds, DauSach *dausach){
    if(dsds.n > MAX_SIZE_DAUSACH)
        cout << "DSDS day \n";
    else{
        int i;
        for(i=0; i<dsds.n; i++){
            if(strcmp(dausach->theloai, dsds.nodes[i]->theloai) < 0){
                InsertDauSach(dsds, dausach, i);
                return;
            }
            else if(strcmp(dausach->theloai, dsds.nodes[i]->theloai) == 0){
                if(strcmp(dausach->tensach, dsds.nodes[i]->tensach) <= 0){
                    InsertDauSach(dsds, dausach, i);
                    return;
                }
            }
        }
        dsds.nodes[i] = dausach;
        dsds.n++;
    }
}

DauSach *TimDauSach(DS_DauSach dsds, char *ISBN){
    for(int i=0; i<dsds.n; i++){
        if(strcmp(dsds.nodes[i]->ISBN, ISBN) == 0){
            return dsds.nodes[i];
        }
    }
    return NULL;
}

bool XoaSach(DauSach *dausach, char *masach){
    for(int i=0; i<dausach->sosach; i++){
        if(strcmp(dausach->dsSach[i]->masach, masach) == 0){
            if(dausach->dsSach[i]->trangthai == 1){
                cout << "Khong the xoa sach nay vi sach dang duoc muon\n";
                return false;
            }
            else{
                for(int j=i; j<dausach->sosach-1; j++){
                    dausach->dsSach[j] = dausach->dsSach[j+1];
                }
                dausach->sosach--;
                cout << "Xoa sach thanh


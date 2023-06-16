// #ifndef _STRUCTDAUSACH_H // Nếu chưa định nghĩa _STRUCTDAUSACH_H
// #define _STRUCTDAUSACH_H // thì định nghĩa _STRUCTDAUSACH_H
// #include "StructDanhMucSach.h"
#define MAX_SIZE_LIST_DAU_SACH 100
#define MAX_SIZE_LIST_DMS 100

struct DauSach
{
    char ISBN[30], TenSach[30], TacGia[30], TheLoai[30];
    int SoTrang, NXB;
    DM_Sach *DS_Sach;
    int TongSoLuong;
    int TongSoLuotMuon = 0;
    // constructor
    DauSach() {}
    DauSach(char isbn[], char tensach[], char tacgia[], char theloai[], int sotrang, int nxb)
    {
        strcpy(ISBN, isbn);
        strcpy(TenSach, tensach);
        strcpy(TacGia, tacgia);
        strcpy(TheLoai, theloai);
        SoTrang = sotrang;
        NXB = nxb;
        TongSoLuong = 0;
    }
    void Init(char isbn[], char tensach[], char tacgia[], char theloai[], int sotrang, int nxb)
    {
        strcpy(ISBN, isbn);
        strcpy(TenSach, tensach);
        strcpy(TacGia, tacgia);
        strcpy(TheLoai, theloai);
        SoTrang = sotrang;
        NXB = nxb;
    }
    void TongSLM()
    {
        int sum=0;
        while(DS_Sach)
        {
            sum+=DS_Sach->sach->SoLuotMuon;
            DS_Sach = DS_Sach->next;
        }   
        TongSoLuotMuon = sum;
    }
    bool ThuocDauSach(char* c)
    {
        for(int i = 0; i < strlen(ISBN); i++)
        {
            if (c[i] != ISBN[i])
            return false;
        }
        return true;
    }
    // destructor
    ~DauSach(){};
};
struct DS_DauSach
{
    int n;
    DauSach *nodes[MAX_SIZE_LIST_DAU_SACH];
    DS_DauSach()
    {
        n = 0;
    }
    ~DS_DauSach() {}
};

// su dung khi doc file
void InsertLastDauSach(DS_DauSach &DSDS, DauSach *dausach)
{
    if (DSDS.n > MAX_SIZE_LIST_DAU_SACH)
        printf("DSDS day \n");
    else
    {
        DSDS.nodes[DSDS.n] = dausach;
        DSDS.n++;
    }
}

void InsertDauSach(DS_DauSach &DSDS, DauSach *dausach, int pos)
{
    for (int i = DSDS.n - 1; i >= pos; i--)
        DSDS.nodes[i + 1] = DSDS.nodes[i];
    DSDS.nodes[pos] = dausach;
    DSDS.n++;
}

void ThemDauSach(DS_DauSach &DSDS, DauSach *dausach)
{
    if (DSDS.n > MAX_SIZE_LIST_DAU_SACH)
        std::cout << "DSDS day \n";
    else
    {
        int i;
        for (i = 0; i < DSDS.n; i++)
        {
            if (strcmp(dausach->TheLoai, DSDS.nodes[i]->TheLoai) < 0)
            {
                InsertDauSach(DSDS, dausach, i);
                return;
            }
            else if (strcmp(dausach->TheLoai, DSDS.nodes[i]->TheLoai) == 0)
            {
                if (strcmp(dausach->TenSach, DSDS.nodes[i]->TenSach) <= 0)
                {
                    InsertDauSach(DSDS, dausach, i);
                    return;
                }
            }
        }
        DSDS.nodes[i] = dausach;
        DSDS.n++;
    }
}

void DeleteDauSach(DS_DauSach &DSDS, int pos)
{
    for (int i = pos; i < DSDS.n - 1; ++i)
        DSDS.nodes[i] = DSDS.nodes[i + 1];
    DSDS.nodes[DSDS.n - 1] = nullptr;
    DSDS.n--;
}

DauSach *TimDauSach(DS_DauSach DSDS, char ISBN[])
{
    for (int i = 0; i < DSDS.n; i++)
    {
        if (strcmp(DSDS.nodes[i]->ISBN, ISBN) == 0)
        {
            return DSDS.nodes[i];
        }
    }
    return nullptr;
}
int TimPosDauSach(DS_DauSach DSDS, char ISBN[])
{
    for (int i = 0; i < DSDS.n; i++)
    {
        if (strcmp(DSDS.nodes[i]->ISBN, ISBN) == 0)
        {
            return i;
        }
    }
    return -1;
}

struct DS_DMS
{
    int n = 0;
    Sach *nodes[MAX_SIZE_LIST_DMS];
    void InsertLastDMS(DS_DMS &DSDMS, Sach *sach)
    {
        if (DSDMS.n > MAX_SIZE_LIST_DMS)
            printf("DSDMS day \n");
        else
        {
            DSDMS.nodes[DSDMS.n] = sach;
            DSDMS.n++;
        }
    }
};

void GetDMS(DS_DMS &DSDMS, DauSach *dauSach)
{
    DSDMS.n = 0;
    if (dauSach->TongSoLuong == 0)
        return;
    DM_Sach *temp = dauSach->DS_Sach;
    for (temp; temp != nullptr; temp = temp->next)
        DSDMS.InsertLastDMS(DSDMS, temp->sach);
}

void InsertAfter_DM_Sach(DauSach *&node, Sach *sach)
{
    node->TongSoLuong++;
    if (node->DS_Sach == nullptr)
        InsertFirst_DM_Sach(node->DS_Sach, sach);
    else
    {
        DM_Sach *find = node->DS_Sach;
        for (int i = 0; i < sach->id - 1; i++)
            find = find->next;
        InsertAfter_DM_Sach(find, sach);
    }
}

char *CreateMaSach(DauSach *&ds)
{
    DM_Sach *node = ds->DS_Sach;
    char *ms = new char;
    strcpy(ms, ds->ISBN);
    char cid[3];
    // TH chua co sach
    if (node == nullptr)
    {
        strcat(ms, "-00");
        return ms;
    }
    else
        // TH id khong lien mach
        for (node; node->next != nullptr; node = node->next)
        {
            if (node->next->sach->id - node->sach->id != 1)
            {
                int id = node->sach->id + 1;
                itoa(id, cid, 10);
                if (id < 10)
                {
                    ms = strcat(ms, "-0");
                    strcat(ms, cid);
                    return ms;
                }
                else
                {
                    ms = strcat(ms, "-");
                    strcat(ms, cid);
                    return ms;
                }
            }
        }
    // TH them sach vao id ke tiep
    int id = node->sach->id + 1;
    itoa(id, cid, 10);
    if (id < 10)
    {
        ms = strcat(ms, "-0");
        strcat(ms, cid);
        return ms;
    }
    else
    {
        ms = strcat(ms, "-");
        strcat(ms, cid);
        return ms;
    }
}
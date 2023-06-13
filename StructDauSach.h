// #ifndef _STRUCTDAUSACH_H // Nếu chưa định nghĩa _STRUCTDAUSACH_H
// #define _STRUCTDAUSACH_H // thì định nghĩa _STRUCTDAUSACH_H
// #include "StructDanhMucSach.h"
#define MAX_SIZE_LIST_DAU_SACH 100

struct DauSach
{
    char ISBN[30], TenSach[30], TacGia[30], TheLoai[30];
    int SoTrang, NXB;
    DM_Sach *DS_Sach;
    int TongSoLuong;

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
// #endif
DM_Sach *CreateMaSach(DauSach *&ds, Sach *sach)
{
    DM_Sach *node = ds->DS_Sach;
    // TH chua co sach
    if (node == nullptr)
    {
        node = CreateDM_Sach(sach);
        node->sach->id = 1;
        char *ms = ds->ISBN;
        strcat(ms, "-01");
        strcpy(node->sach->MaSach, ms);
        return node;
    }
    else
        // TH id khong lien mach
        while (node->next != nullptr)
        {
            if (node->next->sach->id - node->sach->id != 1)
            {
                DM_Sach *newnode = CreateDM_Sach(sach);
                newnode->next = node->next;
                node->next = newnode;
                newnode->sach->id = node->sach->id + 1;
                char *ms = ds->ISBN;
                char *cid;
                if (newnode->sach->id < 10)
                {
                    ms = strcat(ms, "-0");
                    itoa(newnode->sach->id, cid, 10);
                    strcat(ms, cid);
                    strcpy(node->sach->MaSach, ms);
                    return newnode;
                }
                else
                {
                    ms = strcat(ms, "-");
                    itoa(newnode->sach->id, cid, 10);
                    strcat(ms, cid);
                    strcpy(node->sach->MaSach, ms);
                    return newnode;
                }
            }
            node = node->next;
        }
    // TH them sach vao id ke tiep
    DM_Sach *newnode = node->next;
    newnode = CreateDM_Sach(sach);
    newnode->sach->id = node->sach->id + 1;
    char *ms = ds->ISBN;
    char *cid;
    if (newnode->sach->id < 10)
    {
        ms = strcat(ms, "-0");
        itoa(newnode->sach->id, cid, 10);
        strcat(ms, cid);
        strcpy(node->sach->MaSach, ms);
        return newnode;
    }
    else
    {
        ms = strcat(ms, "-");
        itoa(newnode->sach->id, cid, 10);
        strcat(ms, cid);
        strcpy(node->sach->MaSach, ms);
        return newnode;
    }
}
//
void InsertSach(DauSach *&ds, int addval)
{
    while (addval > 0)
    {
        // show bang nhap tt,vt
        // dung CreateMaSach de lay masach
        // neu huy bo nhap thi DeleteDM_Sach(ds->DS_Sach, DM_Sach->Sach->MaSach) vua tao
    }
}
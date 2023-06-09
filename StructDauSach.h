#define MAX_SIZE_LIST_DAU_SACH 100

struct DauSach
{
    char ISBN[30], TenSach[30], TacGia[30], TheLoai[30];
    int SoTrang, NXB;
    DM_Sach *DS_Sach;
    int soluong;

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
        soluong = 0;
    }
    void Init(char isbn[], char tensach[], char tacgia[], char theloai[], int sotrang, int nxb)
    {
        strcpy(ISBN, isbn);
        strcpy(TenSach, tensach);
        strcpy(TacGia, tacgia);
        strcpy(TheLoai, theloai);
        SoTrang = sotrang;
        NXB = nxb;
        soluong = 0;
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

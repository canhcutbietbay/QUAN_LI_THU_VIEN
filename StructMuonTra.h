struct DateTime
{
    int Year, Month, Day;
    char res[15];
    DateTime(){};
    DateTime(int year, int month, int day)
    {
        Year = year;
        Month = month;
        Day = day;
    }
    void GetRes()
    {
        if (Day)
        {
            char temp[10];
            itoa(Day, temp, 10);
            if (Day < 10)
                strcat(this->res, "0");
            strcat(this->res, temp);
            strcat(this->res, "/");
            if (Month < 10)
                strcat(this->res, "0");
            itoa(Month, temp, 10);
            strcat(this->res, temp);
            strcat(this->res, "/");
            itoa(Year, temp, 10);
            strcat(this->res, temp);
        }
        else
            strcpy(res, "");
    }
    void GetTimeNow()
    {
        time_t CurrentTime = time(0);
        tm *Time = localtime(&CurrentTime);
        Year = Time->tm_year + 1900;
        Month = Time->tm_mon + 1;
        Day = Time->tm_mday;
    }

    unsigned long long GetSoNgayMuon()
    {
        time_t CurrentTime;
        DateTime Now;
        time(&CurrentTime);
        tm *End, *Start;
        Start = localtime(&CurrentTime);
        Start->tm_year = Year - 1900;
        Start->tm_mon = Month - 1;
        Start->tm_mday = Day;
        unsigned long long Seconds = difftime(CurrentTime, mktime(Start));
        int SoNgayMuon = Seconds / 86400;
        return SoNgayMuon;
    }
};
//
struct MuonTra
{
    char MaSach[15];
    int TrangThai;
    DateTime NgayMuon, NgayTra;
    /*
     * 0: Dang muon
     * 1: Da tra
     * 2: Lam mat sach
     */
};
struct NodeMuonTra
{
    MuonTra *value;
    NodeMuonTra *Left = nullptr;
    NodeMuonTra *Right = nullptr;
};
struct DS_MuonTra
{
    NodeMuonTra *First = nullptr;
    NodeMuonTra *Last = nullptr;
};

NodeMuonTra *CreateNodeMuonTra(MuonTra *muonTra)
{
    NodeMuonTra *NewNode = new NodeMuonTra;
    NewNode->value = muonTra;
    NewNode->Left = NewNode->Right = nullptr;
    return NewNode;
}

void InsertFirst_DM_MuonTra(DS_MuonTra *&DSMT, MuonTra *muonTra)
{
    NodeMuonTra *NewNode = CreateNodeMuonTra(muonTra);
    if (!DSMT->First)
        DSMT->First = DSMT->Last = NewNode;
    else
    {
        NewNode->Right = DSMT->First;
        DSMT->First->Left = NewNode;
        DSMT->First = NewNode;
    }
}
void InsertLast_DM_MuonTra(DS_MuonTra *&DSMT, MuonTra *muonTra)
{
    NodeMuonTra *NewNode = CreateNodeMuonTra(muonTra);
    if (!DSMT->First)
        DSMT->First = DSMT->Last = NewNode;
    else
    {
        NewNode->Left = DSMT->Last;
        DSMT->Last->Right = NewNode;
        DSMT->Last = NewNode;
    }
}

void InsertAfter(DS_MuonTra *&DSMT, NodeMuonTra *node, NodeMuonTra *after)
{
    if (after)
    {
        node->Left = after;
        node->Right = after->Right;
        after->Right = node;
        if (DSMT->First != after)
            after->Right->Left = node;
        if (DSMT->Last == after)
            DSMT->Last = after;
    }
    else
        InsertFirst_DM_MuonTra(DSMT, node->value);
}

void InsertBefore(DS_MuonTra *&DSMT, NodeMuonTra *node, NodeMuonTra *before)
{
    if (before)
    {
        node->Right = before;
        node->Left = before->Left;
        if (DSMT->First != before)
            before->Left->Right = node;
        if (DSMT->First == before)
            DSMT->First = before;
    }
    else
        InsertLast_DM_MuonTra(DSMT, node->value);
}
char *TBMuon(DS_MuonTra *firstnode);
int DK_MuonSach(NodeMuonTra *check);
bool MuonQuaHan(DateTime *NgayMuon, DateTime *NgayTra);
// bool CungDauSach(DS_MuonTra *firstnode, char *ms);

// void InSachMuon(NodeTheDocGia *TheDocGia, int MaThe)
// {
// }
//
bool MuonQuaHan(DateTime *NgayMuon, DateTime *NgayTra)
{
    if (NgayTra->Day != 0)
        return false;
    else if (NgayMuon->GetSoNgayMuon() > 7)
        return true;
    else
        return false;
}
//
// bool CungDauSach(NodeMuonTra *firstnode, char *ms)
// {
//     if (firstnode == nullptr)
//         return false;
//     else
//     {
//         NodeMuonTra *node = firstnode;
//         for (node->Right != nullptr, node = node->Right)
//         {
//             if (node->value->TrangThai == 0)
//                 while (1)
//                 {
//                     int k = 0;
//                     if (ms[k] == node->value->MaSach[k])
//                         if (ms[k] == '-')
//                             return true;
//                         else
//                             k++;
//                     else
//                         break;
//                 }
//         }
//         return false;
//     }
// }
//

// int TTSach(DS_DauSach ds, char* masach)
// {
//     for (int i=0; i < ds.n; i++)
//     {
//         if (inside(masach, ds.nodes[i]->isbn))
//         return checknodeSach(ds.nodes[i]->DS_Sach, masach);
//     }
// }
/*
    0- co the muon sach
    1- muon 3 sach
    2- muon 1 sach qua 7 ngay
    3- chung 1 dau sach
    4- sach da cho muon
    5- sach da thanh li
    6- khong co masach nay
*/

// int DK_MuonSach(NodeMuonTra *firstnode, char* ms, DS_DauSach DSDS)
// {
//     if (firstnode == nullptr)
//     {
//         int tt = TTSach(DSDS, masach);
//         return (tt == 0) ? 0 : (tt+3);
//     }
//     else
//     {
//         NodeMuonTra *node = new NodeMuonTra;
//         node = firstnode;
//         int DangMuon = 0;
//         for (;node != nullptr; node = node->Right)
//         {
//             if (node->value->TrangThai == 0)
//             {
//                 DangMuon++;
//                 if (inside(ms, node->value->MaSach))
//                     return 3;
//                 if (MuonQuaHan(&(node->value->NgayMuon), &(node->value->NgayTra)))
//                 return 2;
//             }
//         }
//         if (DangMuon == 3)
//             return 1;
//         int tt = TTSach(DSDS, masach);
//         return (tt == 0) ? 0 : (tt+3);
//     }
// }

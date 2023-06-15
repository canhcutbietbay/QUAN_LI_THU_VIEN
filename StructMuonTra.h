struct DateTime
{
    int Year, Month, Day;
    char res[15];
    void GetRes()
    {
        strcpy(res, "");
        if (Day)
        {
            char temp[10];
            strcpy(temp, "");
            if (Day < 10)
                strcat(this->res, "0");
            itoa(Day, temp, 10);
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
    }
    void GetTimeNow()
    {
        time_t CurrentTime = time(0);
        tm *Time = localtime(&CurrentTime);
        this->Year = Time->tm_year + 1900;
        this->Month = Time->tm_mon + 1;
        this->Day = Time->tm_mday;
    }

    unsigned long long GetSoNgayMuon()
    {
        time_t CurrentTime;
        time(&CurrentTime);
        tm *Start;
        Start = localtime(&CurrentTime);
        Start->tm_year = Year - 1900;
        Start->tm_mon = Month - 1;
        Start->tm_mday = Day;
        unsigned long long Seconds = difftime(CurrentTime, mktime(Start));
        unsigned long long SoNgayMuon = Seconds / 86400;
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
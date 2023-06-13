struct Date
{
    char Ngay[3], Thang[3], Nam[5];
};

struct MuonTra
{
    char MaSach[15];
    int TrangThai;
    Date NgayMuon, NgayTra;
    /*
     * 0: Dang muon
     * 1: Da tra
     * 2: Lam mat sach
     */
};
struct NodeMuonTra
{
    MuonTra *value;
    NodeMuonTra *Left;
    NodeMuonTra *Right;
};
struct DS_MuonTra
{
    NodeMuonTra *First = nullptr;
    NodeMuonTra *Last = nullptr;
};

NodeMuonTra *CreateNodeMuonTra(MuonTra *muonTra)
{
    NodeMuonTra *NewNode;
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
      if (DSMT->Last == after) DSMT->Last = after;
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
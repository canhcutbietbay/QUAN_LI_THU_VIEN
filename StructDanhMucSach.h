struct Sach
{
  int id = 0;
  char MaSach[15];
  int TrangThai;
  char ViTri[30];
  int SoLuotMuon = 0;
  // construction
  Sach() {}
  Sach(char maSach[15], int trangThai, char viTri[30])
  {
    strcpy(MaSach, maSach);
    TrangThai = trangThai;
    strcpy(ViTri, viTri);
  }
};
// lien ket don
struct DM_Sach
{
  Sach *sach;
  DM_Sach *next;
  ~DM_Sach() {}
};
/*
 */
// lenh khoi tao node
void InsertFirst_DM_Sach(DM_Sach *&First, Sach *sach);
void InsertAfter_DM_Sach(DM_Sach *&node, Sach *sach);
void InsertLast_DM_Sach(DM_Sach *&First, Sach *sach);

// new DM_Sach;
DM_Sach *CreateDM_Sach(Sach *sach)
{
  DM_Sach *node = new DM_Sach;
  node->next = nullptr;
  node->sach = sach;
  return node;
}

// them DM_Sach o dau
void InsertFirst_DM_Sach(DM_Sach *&First, Sach *sach)
{
  DM_Sach *newSach = CreateDM_Sach(sach);
  First = newSach;

}
void AddFirst_DM_Sach(DM_Sach *&First, Sach *sach)
{
  DM_Sach *newSach = CreateDM_Sach(sach), *temp;
  temp = First ;
  newSach->next = temp;
  First = newSach;
}


// them DM_Sach o vi tri
void InsertAfter_DM_Sach(DM_Sach *&node, Sach *sach)
{
  DM_Sach *newSach = CreateDM_Sach(sach);
  newSach->next = node->next;
  node->next = newSach;
}

// them NodeSach o cuoi
void InsertLast_DM_Sach(DM_Sach *&First, Sach *sach)
{
  if (First == nullptr)
    InsertFirst_DM_Sach(First, sach);
  else
  {
    DM_Sach *last;
    for (last = First; last->next != nullptr; last = last->next)
      ;
    InsertAfter_DM_Sach(last, sach);
  }
}

// lay node sach voi masach
DM_Sach *GetDM_Sach(DM_Sach *First, char *masach)
{
  DM_Sach *node = First;
  while (node) // ds tinh tu 1
    if (!strcmp(masach, node->sach->MaSach))
      return node;
    else
      node = node->next;
  return node;
}

int DeleteAfterDM_Sach(DM_Sach *node)
{
  DM_Sach *temp;
  // nếu node là NULL hoặc sau node không có nút
  if ((node == nullptr) || (node->next == nullptr))
    return 0;
  temp = node->next; // node la nut can xoa
  node->next = temp->next;
  delete temp;
  return 1;
}

DM_Sach *DeleteFirstDM_Sach(DM_Sach *node)
{
  if (node == nullptr)
    return nullptr; // Khong co gi de xoa het
  else
  {
    DM_Sach *newHead = node->next;
    delete (node);
    return newHead;
  }
}

int DeleteSach(DM_Sach *&First, char maSach[])
{
  if (strcmp(First->sach->MaSach, maSach) == 0)
  {
    First = DeleteFirstDM_Sach(First);
    if (First != nullptr)
      return 1;
    else
      return 0;
  }
  else
  {
    DM_Sach *node = First;
    for (node; node->next != nullptr; node = node->next)
    {
      if (strcmp(node->next->sach->MaSach, maSach) == 0)
      {
        int code = DeleteAfterDM_Sach(node);
        return code;
      }
    }
  }
  return 0;
}

int UpdateSach(DM_Sach *&First, Sach sach)
{
  DM_Sach *node = GetDM_Sach(First, sach.MaSach);
  if (node == nullptr)
  {
    return 0;
  }
  else
  {
    node->sach->TrangThai = sach.TrangThai;
    strcpy(node->sach->ViTri, sach.ViTri);
    return 1;
  }
}
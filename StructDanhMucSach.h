
struct Sach
{
  int id = 0;
  char MaSach[15];
  int TrangThai;
  char ViTri[15];
  // construction
  Sach(){};
  Sach(char ms[], int tt, char vt[])
  {
    strcpy(MaSach, ms);
    TrangThai = tt;
    strcpy(ViTri, vt);
  }

  ~Sach() {}
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
void InsertFirst_DM_Sach(DM_Sach *&First, Sach &sach);
void InsertLast_DM_Sach(DM_Sach *First, Sach &sach);
void InsertAfter_DM_Sach(DM_Sach *&node, Sach &sach);
// lenh truy xuat
DM_Sach *GetDM_Sach(DM_Sach *First, int pos);
DM_Sach *GetDM_Sach(DM_Sach *First, char *masach);
Sach *GetSach(DM_Sach *First, char *masach);
// lenh cap nhat sach cua node
void DeleteDM_Sach(DM_Sach *First, char *masach);
DM_Sach *MaSach(DM_Sach dms, int addval);
/*
 */

// new DM_Sach;
DM_Sach *CreateDM_Sach()
{
  DM_Sach *node = new DM_Sach;
  node->next = nullptr;
  return node;
}

// them DM_Sach o dau
void InsertFirst_DM_Sach(DM_Sach *&First, Sach &sach)
{
  DM_Sach *newSach = CreateDM_Sach();
  newSach->next = First;
  First = newSach;
}

// them DM_Sach o vi tri
void InsertAfter_DM_Sach(DM_Sach *&node, Sach &sach)
{
  DM_Sach *newSach = CreateDM_Sach();
  newSach->next = node->next;
  node->next = newSach;
}

// them DM_Sach o cuoi
void InsertLast_DM_Sach(DM_Sach *First, Sach &sach)
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

// lay node sach o vi tri pos
DM_Sach *GetDM_Sach(DM_Sach *First, int id)
{
  DM_Sach *node = First;
  while (node->sach->id < id) // ds tinh tu 1
    if (node->next == nullptr)
      return nullptr;
    else
      node = node->next;
  return node;
}

// lay node sach theo ma sach
DM_Sach *GetDM_Sach(DM_Sach *First, char *masach)
{
  for (DM_Sach *node = First; node != nullptr; node = node->next)
  {
    if (strcmp(node->sach.MaSach, masach) == 0)
      return node;
  }
  return nullptr;
}

// lay sach theo ma sach
Sach *GetSach(DM_Sach *First, char *masach)
{
  DM_Sach *node = GetDM_Sach(First, masach);
  if (node)
    return node->sach;
  else
    return nullptr;
}

// xoa sach theo ma sach
void DeleteDM_Sach(DM_Sach *First, char *masach)
{
}
void DeleteDM_Sach(DM_Sach *&node)
{
  delete node;
}
// tao MaSach tu dong
// DM_Sach *CreateMaSach(DauSach &ds, int &addval)
// {
//   DauSach *node = ds;
//   // TH dausach chua co sach
//   if (node->soluong == 0)
//   {
//     node->DS_Sach = CreateDM_Sach();
//     node->DS_Sach->sach.id = 1;
//     // them 0 khi id be hon 10
//     if (node->DS_Sach->sach.id < 10)
//     {
//       char *s;
//       itoa(node->DS_Sach->sach.id, s);
//       s = "0" + s;
//       node->DS_Sach->sach.MaSach = node->ISBN + s;
//     }
//     else
//     {
//       char *s;
//       itoa(node->DS_Sach->sach.id, s);
//       node->DS_Sach->sach.MaSach = node->ISBN + s;
//     }
//     addval--;
//     node->soluong = 1;
//     return node->DS_Sach;
//   }
//   // TH them o cuoi
//   else if (node->DS_Sach->next == nullptr)
//   {
//     node->DS_Sach->next = CreateDM_Sach();
//     node->DS_Sach->next->sach.id = node->DS_Sach->sach.id + 1;
//     //
//     if (node->DS_Sach->sach.id < 9)
//     {
//       char *s;
//       itoa(node->DS_Sach->next->sach.id, s);
//       s = "0" + s;
//       node->DS_Sach->next->sach.MaSach = node->ISBN + s;
//     }
//     else
//     {
//       char *s;
//       itoa(node->DS_Sach->next->sach.id, s);
//       node->DS_Sach->next->sach.MaSach = node->ISBN + s;
//     }
//     addval--;
//     return node->DS_Sach->next;
//   }
//   // TH khuyet id vi bi xoa tu truoc
//   else if (node->DS_Sach->next->sach.id - node->DS_Sach->sach.id != 1)
//   {
//     DM_Sach *newnode = CreateDM_Sach();
//     newnode->next = node->DS_Sach->next;
//     node->DS_Sach->next = newnode;
//     newnode->sach.id = node->DS_Sach->sach.id + 1;
//     //
//     if (newnode->sach.id < 9)
//     {
//       char *s;
//       itoa(node->DS_Sach->next->sach.id, s);
//       s = "0" + s;
//       node->DS_Sach->next->sach.MaSach = node->ISBN + s;
//     }
//     else
//     {
//       char *s;
//       itoa(node->DS_Sach->next->sach.id, s);
//       node->DS_Sach->next->sach.MaSach = node->ISBN + s;
//     }
//     addval--;
//     return node->DS_Sach->next;
//   }
// }

// // Nhap thong tin sach theo so luong sach nhap vao dau sach
// void NhapSach(DauSach &ds, int &addval)
// {
//   DM_Sach *node = ds.DM_Sach;
//   while (addval > 0)
//   {
//     node = CreateMaSach(ds, addval);
//     /*
//     Them vao trang thai va vi tri
//     TH nguoi dung nhan HUY o MaSach nao thi xoa MS do roi dung lai
//     */
//   }
// }
//
struct Sach
{
  char MaSach[15];
  int TrangThai;
  char ViTri[15];
  // // construction
  // Sach(){};
  // Sach(char ms[], int tt, char vt[])
  // {
  //   strcpy(MaSach, ms);
  //   TrangThai = tt;
  //   strcpy(ViTri, vt);
  // }

  // ~Sach() {}
};
// lien ket don
struct DM_Sach
{
  Sach sach;
  int count;
  DM_Sach *next;
};
/*
 */
// lenh khoi tao node
void InsertFirst_NodeSach(DM_Sach *&First, Sach &sach);
void InsertLast_NodeSach(DM_Sach *First, Sach &sach);
void InsertAfter_NodeSach(DM_Sach *&node, Sach &sach);
// lenh truy xuat
DM_Sach *GetNodeSach(DM_Sach *First, int pos);
DM_Sach *GetNodeSach(DM_Sach *First, char *masach);
Sach *GetSach(DM_Sach *First, char *masach);
// lenh cap nhat sach cua node
void UpdateNodeSach(DM_Sach *&node, Sach *sach);
// lenh xoa sach
void DeleteNodeSach(DM_Sach *First, char *masach);
/*
 */
char *CreateMaSach(DauSach ds)
{
  char *ms;
  char *s;
  strcpy(ms, ds.ISBN);
  strcat(ms, "-");
  itoa(ds.DS_Sach->count + 1, s, 10);
  strcat(ms, s);
  return ms;
}
// new DM_Sach;
DM_Sach *CreateNodeSach(DauSach ds, int trangthai, char *vitri)
{
  DM_Sach *node = new DM_Sach;
  strcpy(node->sach.MaSach, CreateMaSach(ds));
  node->sach.TrangThai = trangthai;
  strcpy(node->sach.ViTri, vitri);
  node->next = NULL;
  (node->count)++;
  return node;
}

void InsertSach(DauSach &ds, int soluong)
{
  if (soluong >= 1)
    for (int i = 1; i <= soluong; i++)
      ds.DS_Sach = CreateNodeSach();
  // Chua xong ham nha
};
// them DM_Sach o dau
// void InsertFirst_NodeSach(DM_Sach *&First, Sach &sach)
// {
//   DM_Sach *newSach = CreateNodeSach();
//   newSach->next = First;
//   First = newSach;
// }

// // them DM_Sach o vi tri
// void InsertAfter_NodeSach(DM_Sach *&node, Sach &sach)
// {
//   DM_Sach *newSach = CreateNodeSach();
//   newSach->next = node->next;
//   node->next = newSach;
// }

// // them DM_Sach o cuoi
// void InsertLast_NodeSach(DM_Sach *First, Sach &sach)
// {
//   if (First == NULL)
//     InsertFirst_NodeSach(First, sach);
//   else
//   {
//     DM_Sach *last;
//     for (last = First; last->next != NULL; last = last->next)
//       ;
//     InsertAfter_NodeSach(last, sach);
//   }
// }

// // lay node sach o vi tri pos
// DM_Sach *GetNodeSach(DM_Sach *First, int pos)
// {
//   DM_Sach *node = First;
//   for (int i = 1; i != pos; i++) // ds tinh tu 1
//     if (node->next == NULL)
//       return NULL;
//     else
//       node = node->next;
//   return node;
// }

// lay node sach theo ma sach
DM_Sach *GetNodeSach(DM_Sach *First, char *masach)
{
  for (DM_Sach *node = First; node != NULL; node = node->next)
  {
    if (strcmp(node->sach.MaSach, masach) == 0)
      return node;
  }
  return NULL;
}

// lay sach theo ma sach
Sach *GetSach(DM_Sach *First, char *masach)
{
  DM_Sach *node = GetNodeSach(First, masach);
  if (node)
    return &node->sach;
  else
    return NULL;
}

// xoa sach theo ma sach
void DeleteNodeSach(DM_Sach *First, char *masach)
{
}
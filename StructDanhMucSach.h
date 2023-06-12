// #ifndef _STRUCTDANHMUCSACH_H // Nếu chưa định nghĩa _STRUCTDANHMUCSACH_H
// #define _STRUCTDANHMUCSACH_H // thì định nghĩa _STRUCTDANHMUCSACH_H
// #include "StructDauSach.h"
#define MAX_SIZE_LIST_DMS 100
struct Sach
{
  int id = 0;
  char MaSach[15];
  int TrangThai;
  char ViTri[30];
  // construction
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
// lenh truy xuat
// DM_Sach *GetDM_Sach(DM_Sach *First, int pos);
// DM_Sach *GetDM_Sach(DM_Sach *First, char *masach);
Sach *GetSach(DM_Sach *First, char *masach);
// lenh cap nhat sach cua node
void DeleteDM_Sach(DM_Sach *First, char *masach);
DM_Sach *MaSach(DM_Sach dms, int addval);
/*
 */

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
// DM_Sach *GetDM_Sach(DM_Sach *First, char *masach)
// {
//   for (DM_Sach *node = First; node != nullptr; node = node->next)
//   {
//     if (strcmp(node->sach.MaSach, masach) == 0)
//       return node;
//   }
//   return nullptr;
// }

// lay sach theo ma sach
// Sach *GetSach(DM_Sach *First, char *masach)
//{
//  DM_Sach *node = GetDM_Sach(First, masach);
//  if (node)
//    return node->sach;
//  else
//    return nullptr;
//}

// xoa sach theo ma sach
void DeleteDM_Sach(DM_Sach *&First, char *masach)
{
  DM_Sach *node = First;
  if (strcmp(First->sach->id, masach) == 0)
  {
    First = nullptr;
    delete node;
  }
  else
    for (node->next != nullptr, node = node->next)
    {
      if (strcmp(node->next->sach->id, masach) == 0)
      {
        DM_Sach *nodedel = node->next;
        node->next = node->next->next;
        delete nodedel;
      }
    }
}

// #endif
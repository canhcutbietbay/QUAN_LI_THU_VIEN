//
struct Sach
{
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
};
// lien ket don
struct NodeSach
{
  Sach sach;
  NodeSach *next;
};
/*

*/
// lenh khoi tao node
void InsertFirst_NodeSach(NodeSach *&First, Sach &sach);
void InsertLast_NodeSach(NodeSach *First, Sach &sach);
void InsertAfter_NodeSach(NodeSach *&node, Sach &sach);
// lenh truy xuat
NodeSach *GetNodeSach(NodeSach *First, int pos);
NodeSach *GetNodeSach(NodeSach *First, char *masach);
Sach *GetSach(NodeSach *First, char *masach);
// lenh cap nhat sach cua node
void UpdateNodeSach(NodeSach *&node, Sach *sach);
// lenh xoa sach
void DeleteNodeSach(NodeSach *First, char *masach);
/*

*/

// new NodeSach;
NodeSach *CreateNodeSach(Sach &sach)
{
  NodeSach *node = new NodeSach;
  node->sach = sach;
  node->next = nullptr;
  return node;
}

// them NodeSach o dau
void InsertFirst_NodeSach(NodeSach *&First, Sach &sach)
{
  NodeSach *newSach = CreateNodeSach(sach);
  newSach->next = First;
  First = newSach;
}

// them NodeSach o vi tri
void InsertAfter_NodeSach(NodeSach *&node, Sach &sach)
{
  NodeSach *newSach = CreateNodeSach(sach);
  newSach->next = node->next;
  node->next = newSach;
}

// them NodeSach o cuoi
void InsertLast_NodeSach(NodeSach *First, Sach &sach)
{
  if (First == nullptr)
    InsertFirst_NodeSach(First, sach);
  else
  {
    NodeSach *last;
    for (last = First; last->next != nullptr; last = last->next)
      ;
    InsertAfter_NodeSach(last, sach);
  }
}

// lay node sach o vi tri pos
NodeSach *GetNodeSach(NodeSach *First, int pos)
{
  NodeSach *node = First;
  for (int i = 1; i != pos; i++) // ds tinh tu 1
    if (node->next == nullptr)
      return nullptr;
    else
      node = node->next;
  return node;
}

// lay node sach theo ma sach
NodeSach *GetNodeSach(NodeSach *First, char *masach)
{
  for (NodeSach *node = First; node != nullptr; node = node->next)
  {
    if (strcmp(node->sach.MaSach, masach) == 0)
      return node;
  }
  return nullptr;
}

// lay sach theo ma sach
Sach *GetSach(NodeSach *First, char *masach)
{
  NodeSach *node = GetNodeSach(First, masach);
  if (node)
    return &node->sach;
  else
    return nullptr;
}

// cap nhat lai sach cua node
void UpdateNodeSach(NodeSach *&node, Sach *sach)
{
  // if (sach != nullptr)
  //   node->sach = *sach;
  // else
  //   printf("Khong co thong tin");
}

// xoa sach theo ma sach
void DeleteNodeSach(NodeSach *First, char *masach)
{
}
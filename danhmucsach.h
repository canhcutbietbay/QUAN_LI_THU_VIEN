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
// lenh khoi tao node
void InsertFirst_NodeSach(NodeSach *First, Sach &sach);
void InsertLast_NodeSach(NodeSach *Last, Sach &sach);
void InsertAfter_NodeSach(NodeSach *node, Sach &sach);
// new NodeSach;
NodeSach *CreateNodeSach(Sach &sach)
{
  NodeSach *node = new NodeSach;
  node->sach = sach;
  return node;
}
// them NodeSach o dau
void InsertFirst_NodeSach(NodeSach *First, Sach &sach)
{
  NodeSach *newSach = CreateNodeSach(sach);
  newSach->next = First;
  First = newSach;
}
// them NodeSach o vi tri
void InsertAfter_NodeSach(NodeSach *node, Sach &sach)
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
    last->next = CreateNodeSach(sach);
  }
}
//

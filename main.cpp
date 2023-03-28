#include <string.h>
#include <iostream>

using namespace std;

const int MAX_SIZE_LIST_DAU_SACH = 100;


struct DauSach
{
    char ISBN[15], TenSach[25], TacGia[25], TheLoai[25];
    int SoTrang, NXB;
	// NodeSach* First = nullptr;

	//constructor
	DauSach() {}
    DauSach (char isbn[], char tensach[], char tacgia[], char theloai[], int sotrang, int nxb ) {
        strcpy(ISBN, isbn);
        strcpy(TenSach, tensach);
        strcpy(TacGia, tacgia);
        strcpy(TheLoai, theloai);
        SoTrang = sotrang;
        NXB = nxb;
    }

	//destructor
    ~DauSach(){};
};
struct ListDauSach{
	int n;
	DauSach *nodes[MAX_SIZE_LIST_DAU_SACH];
	ListDauSach(){
		n = 0;
	}
	~ListDauSach(){}
};

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
void InsertFirst_NodeSach(NodeSach *&First, Sach &sach);
void InsertLast_NodeSach(NodeSach *First, Sach &sach);
void InsertAfter_NodeSach(NodeSach *&node, Sach &sach);
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

struct DocGia{
	int MaThe;
	char Ho[20];
	char Ten[11];
	int Phai;
		/*
		 * 0: Nam
		 * 1: Nu
		 */
	int TrangThai;
		/*
		 * 0: Khoa
		 * 1: Hoat dong
		 */
	
	//constructor
	DocGia(){}
	DocGia(int mathe, char ho[20], char ten[11], int phai, int trangthai){
		MaThe = mathe;
		strcpy(Ho, ho);
		strcpy(Ten, ten);
		Phai = phai;
		TrangThai = trangthai;
	}
};


struct TreeDocGia{
	DocGia docgia;
	TreeDocGia *Left = NULL;
	TreeDocGia *Right = NULL;
};

void printList(NodeSach *l){
	NodeSach *p = l;
	while (p != NULL){
		cout << p->sach.MaSach << " " << p->sach.TrangThai << " "<< p->sach.ViTri << endl;
    cout << p->next << endl;
		p = p->next;
	}
}


using namespace std;

int main () {
    // DauSach test("abc", "xyz","a1b2","asd", 15, 2013);
    // cout << test.ISBN << endl;
    // cout << test.TenSach << endl;
    // cout << test.TacGia << endl;
    // cout << test.TheLoai << endl;
    // cout << test.NXB << endl;
    // cout << test.SoTrang << endl;
    // DocGia test2 (123,"Huynh", "Tan", 0, 1);
    // cout << test2.MaThe << endl;
    // cout << test2.Ho << endl;
    // cout << test2.Ten << endl;
    // cout << test2.Phai << endl;
    // cout << test2.TrangThai << endl;

	Sach sach("1", 2, "3");
	NodeSach *l = CreateNodeSach(sach);
	// printList(l);
	Sach sach2("4", 5, "6");
	InsertLast_NodeSach(l, sach2);
	// printList(l);
	Sach sach3("7", 8, "9");
	InsertAfter_NodeSach(l, sach3);
	Sach sach4("10", 11, "12");
  InsertFirst_NodeSach (l, sach4);
	printList(l);
}

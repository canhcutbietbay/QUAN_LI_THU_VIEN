#define MAX_SIZE_LIST_DOC_GIA 90000
#define MAX_SIZE_LIST_MT 100

struct ArrRanMT
{
	bool used[90000];
	int k = 0;
	ArrRanMT()
	{
		for (int i = 10000; i < 100000; i++)
		{
			used[i - 10000] = false;
		}
	}
	int RanMT()
	{
		int ma;
		srand(time(0));
		ma = rand() % (89999 - k) + 1;
		return ma;
	}
} mathe = ArrRanMT();
void ArrMTfromFile(ArrRanMT &mathe, int ma)
{
	mathe.used[ma - 10000] = true;
	(mathe.k)++;
}
int RanNewMT(ArrRanMT &mathe)
{
	int r = mathe.RanMT();
	int i = 0;
	while (r != 0)
	{
		if (mathe.used[i] == false)
		{
			r--;
			i++;
		}
		else
			i++;
	}
	mathe.used[--i] = true;
	(mathe.k)++;
	return (i + 9999);
}
struct TheDocGia
{
	int MaThe;
	char Ho[30];
	char Ten[30];
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
	int TongSoLuong;
	DS_MuonTra *DS_MT;
	// constructor
	TheDocGia() {}
	TheDocGia(int mathe, char ho[], char ten[], int phai, int trangthai, DS_MuonTra *DSMT = nullptr, int tongsoluong = 0)
	{
		// random MaThe...
		MaThe = mathe;
		strcpy(Ho, ho);
		strcpy(Ten, ten);
		Phai = phai;
		TrangThai = trangthai;
		DS_MT = DSMT;
		TongSoLuong = tongsoluong;
	}
};
struct NodeTheDocGia
{
	TheDocGia DocGia;
	NodeTheDocGia *left = NULL;
	NodeTheDocGia *right = NULL;
	int height = 0;
};
/*

*/
struct DS_MT
{
	int n = 0;
	MuonTra *nodes[MAX_SIZE_LIST_MT];
	// su dung de tao danh sach muon tra => output ra man hinh
	void InsertLastDSMT(DS_MT &DSMT, MuonTra *muonTra)
	{
		if (DSMT.n > MAX_SIZE_LIST_MT)
			printf("DSMT day \n");
		else
		{
			DSMT.nodes[DSMT.n] = muonTra;
			DSMT.n++;
		}
	}
};
void GetMT(DS_MT &DSMT, TheDocGia *theDocGia)
{
	DSMT.n = 0;
	if (theDocGia->TongSoLuong == 0)
		return;
	NodeMuonTra *temp = theDocGia->DS_MT->First;
	for (temp; temp != nullptr; temp = temp->Right)
		DSMT.InsertLastDSMT(DSMT, temp->value);
}
/*

*/
struct DS_DocGia
{
	int n = 0;
	TheDocGia *nodes[MAX_SIZE_LIST_DOC_GIA];
	void InsertLastDocGia(DS_DocGia &DSDG, TheDocGia *theDocGia)
	{
		if (DSDG.n > MAX_SIZE_LIST_DOC_GIA)
			printf("DSDS day \n");
		else
		{
			DSDG.nodes[DSDG.n] = theDocGia;
			DSDG.n++;
		}
	}
	int CompareDG(TheDocGia *a, TheDocGia *b, int mode)
	{
		// mode 0: MaThe, mode 1: HoTen
		switch (mode)
		{
		case 0:
			return a->MaThe - b->MaThe;
			break;
		case 1:
			if (strcmp(a->Ten, b->Ten) == 0)
			{
				return strcmp(a->Ho, b->Ho);
			}
			else
			{
				return strcmp(a->Ten, b->Ten);
			}
			break;
		}

		return 0;
	}
	void SortDocGia(int l, int r, int mode = 0) // Quick Sort
	{
		// mode 0: MaThe, mode 1: HoTen
		int i = l, j = r;
		TheDocGia *pivot = nodes[(l + r) / 2];
		TheDocGia *temp;
		do
		{
			while (CompareDG(nodes[i], pivot, mode) < 0)
				i++;
			while (CompareDG(nodes[j], pivot, mode) > 0)
				j--;
			if (i <= j)
			{
				temp = nodes[i];
				nodes[i] = nodes[j];
				nodes[j] = temp;
				i++;
				j--;
			}
		} while (i <= j);

		if (l < j)
			SortDocGia(l, j, mode);
		if (i < r)
			SortDocGia(i, r, mode);
	}
};
/*

*/

int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int getHeight(NodeTheDocGia *root)
{
	if (root == NULL)
		return 0;
	// return 1 + max(getHeight(root->left), getHeight(root->right));
	return root->height;
}

NodeTheDocGia *rightRotate(NodeTheDocGia *root)
{
	NodeTheDocGia *x = root->left;

	// Bắt đầu quay phải
	root->left = x->right;
	x->right = root;

	// Thiết lập chiều cao
	root->height = 1 + max(getHeight(root->left), getHeight(root->right));
	x->height = 1 + max(getHeight(x->left), getHeight(x->right));

	// Return x - trả về root mới
	return x;
}

NodeTheDocGia *leftRotate(NodeTheDocGia *root)
{
	NodeTheDocGia *y = root->right;

	// Bắt đầu quay trái
	root->right = y->left;
	y->left = root;

	// Thiết lập chiều cao
	root->height = 1 + max(getHeight(root->left), getHeight(root->right));
	y->height = 1 + max(getHeight(y->left), getHeight(y->right));

	// Return y - trả về root mới
	return y;
}
// Insertion - AVL Tree
NodeTheDocGia *InsertDocGia(NodeTheDocGia *root, TheDocGia DocGia)
{
	// 1. Insert
	if (root == NULL)
		return new NodeTheDocGia{DocGia, NULL, NULL, 1}; // Trả về NodeTheDocGia có height = 1
	if (DocGia.MaThe > root->DocGia.MaThe)
		root->right = InsertDocGia(root->right, DocGia);
	else if (DocGia.MaThe < root->DocGia.MaThe)
		root->left = InsertDocGia(root->left, DocGia);
	else
		return root; // Neu bang thi khong them

	// 2. Set height
	root->height = 1 + max(getHeight(root->left), getHeight(root->right));

	// 3. Rotate
	int valBalance = getHeight(root->left) - getHeight(root->right);

	// Kiểm tra 4 TH xảy ra:
	// 4.1. Left left
	if (valBalance > 1 && DocGia.MaThe < root->left->DocGia.MaThe)
		return rightRotate(root);

	// 4.2. Right Right
	if (valBalance < -1 && DocGia.MaThe > root->right->DocGia.MaThe)
		return leftRotate(root);

	// 4.3. Left Right
	if (valBalance > 1 && DocGia.MaThe > root->left->DocGia.MaThe)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// 4.4. Right Left
	if (valBalance < -1 && DocGia.MaThe < root->right->DocGia.MaThe)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}
// Giá trị cân bằng - Balance
int Balance(NodeTheDocGia *root)
{
	if (root == NULL)
		return 0;
	return getHeight(root->left) - getHeight(root->right);
}

NodeTheDocGia *maxMaThe(NodeTheDocGia *root)
{
	NodeTheDocGia *current = root;

	// Tìm kiếm NodeTheDocGia có mã thẻ lớn nhất
	while (current->right != NULL)
		current = current->right;

	return current;
}
// Find Node
NodeTheDocGia *findNode(NodeTheDocGia *root, int MaThe)
{
	if (MaThe < root->DocGia.MaThe)
		return findNode(root->left, MaThe);
	else if (MaThe > root->DocGia.MaThe)
		return findNode(root->right, MaThe);
	else
		return root;
}

// Update Node
void updateNode(NodeTheDocGia *root, TheDocGia DocGia)
{
	NodeTheDocGia *temp = new NodeTheDocGia;
	temp = findNode(root, DocGia.MaThe);
	temp->DocGia = DocGia;
}
// Deletion - AVL Tree
NodeTheDocGia *deleteNode(NodeTheDocGia *root, int MaThe)
{
	// 1. XÓA NODE - DELETE
	if (root == NULL)
		return root;

	if (MaThe > root->DocGia.MaThe)
		root->right = deleteNode(root->right, MaThe);
	else if (MaThe < root->DocGia.MaThe)
		root->left = deleteNode(root->left, MaThe);

	// Nếu MaThe có giá trị bằng với root->DocGia.MaThe
	// Thì đây chính là NodeTheDocGia cần xóa
	else
	{
		// Trường hợp 0 con hoặc 1 con
		if (root->left == NULL || root->right == NULL)
		{
			// Sử dụng NodeTheDocGia temp để kiểm tra
			NodeTheDocGia *temp = root->left;
			if (root->right != NULL)
				temp = root->right;

			// TH: 0 con - No child case
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
				delete temp;
			}
			// TH: 1 con - One child case
			else
			{
				// Gán tất cả các giá trị (bao gồm left, right, height) của temp vào root
				*root = *temp;
				delete temp;
			}
		}
		// Trường hợp 2 con - Two child case
		else
		{
			// Tìm NodeTheDocGia lớn nhất bên trái (nhỏ nhất bên phải)
			// successor - biggest in the left subtree
			NodeTheDocGia *temp = maxMaThe(root->left);

			// Đưa DocGia của temp vào root
			root->DocGia = temp->DocGia;

			// Xóa temp như 2 TH trên - Delete the inorder successor
			root->left = deleteNode(root->left, temp->DocGia.MaThe);
		}
	}

	// Nếu không còn gì thì trả về luôn !!
	if (root == NULL)
		return root;

	// 2. CẬP NHẬT CHIỀU CAO - UPDATE HEIGHT OF THE CURRENT NODE
	root->height = 1 + max(getHeight(root->left), getHeight(root->right));

	// 3. CÂN BẰNG CÂY - GET THE BALANCE FACTOR
	int valBalance = Balance(root);

	// Kiểm tra 4 TH xảy ra - There are 4 cases

	// Case 1: Left left - Trái trái
	if (valBalance > 1 && Balance(root->left) >= 0)
		return rightRotate(root);

	// Case 2: Right right - Phải phải
	if (valBalance < -1 && Balance(root->right) <= 0)
		return leftRotate(root);

	// Case 3: Left right - Trái phải
	if (valBalance > 1 && Balance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// Case 4: Right left - Phải trái
	if (valBalance < -1 && Balance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}
/*
HIEU CHINH THONG TIN DOC GIA
*/
void InDocGiaTheoMaDocGia(NodeTheDocGia *&TreeAVLDocGia) // Inorder
{
	if (TreeAVLDocGia != nullptr)
	{
		InDocGiaTheoMaDocGia(TreeAVLDocGia->left);
		std::cout << TreeAVLDocGia->DocGia.MaThe << "||" << TreeAVLDocGia->DocGia.Ho << "||" << TreeAVLDocGia->DocGia.Ten << "||" << TreeAVLDocGia->DocGia.Phai << "||" << TreeAVLDocGia->DocGia.TrangThai << std::endl;
		InDocGiaTheoMaDocGia(TreeAVLDocGia->right);
	}
}
//
void GetFromTree(NodeTheDocGia *root, DS_DocGia &DSDG)
{
	if (root == NULL)
		return;
	GetFromTree(root->left, DSDG);
	DSDG.InsertLastDocGia(DSDG, &root->DocGia);
	GetFromTree(root->right, DSDG);
}
// xet nodesach
int checknodeSach(DM_Sach *dms, char *masach)
{
	DM_Sach *temp = dms;
	while (temp)
	{
		if (!strcmp(masach, temp->sach->MaSach))
			return temp->sach->TrangThai;
		temp = temp->next;
	}
	return 3; // khong ton tai ma sach nay`
}

// // Muon Qua Han
bool MuonQuaHan(DateTime *NgayMuon, DateTime *NgayTra)
{
	if (NgayTra->Day != 0)
		return false;
	else if (NgayMuon->GetSoNgayMuon() > 7)
		return true;
	else
		return false;
}
// check
bool inside(char *S, char *s)
{
	int k = 0;
	while (S[k] == s[k])
		if (S[k + 1] == '-')
			return true;
		else
			k++;
	return false;
}
// Trang thai sach
int TTSach(DS_DauSach ds, char *masach)
{
	for (int i = 0; i < ds.n; i++)
	{
		if (inside(masach, ds.nodes[i]->ISBN))
			return checknodeSach(ds.nodes[i]->DS_Sach, masach);
	}
	return 3;
}
// // lay dau sach tu masach
DM_Sach *GetSach(DS_DauSach ds, char *masach)
{
	for (int i = 0; i < ds.n; i++)
	{
		if (inside(masach, ds.nodes[i]->ISBN))
			return GetDM_Sach(ds.nodes[i]->DS_Sach, masach);
	}
	return nullptr;
}
/*
	0- Muon sach thanh cong
	1- muon 3 sach
	2- muon 1 sach qua 7 ngay
	3- chung 1 dau sach
	4- sach da cho muon
	5- sach da thanh li
	6- khong co ma sach nay
	7- The da bi khoa
*/

int DK_MuonSach(NodeMuonTra *firstnode, char *ms, DS_DauSach DSDS)
{
	if (firstnode == nullptr)
	{
		int tt = TTSach(DSDS, ms);
		return (tt == 0) ? 0 : (tt + 3);
	}
	else
	{
		NodeMuonTra *node = new NodeMuonTra;
		node = firstnode;
		int DangMuon = 0;
		for (; node != nullptr; node = node->Right)
		{
			if (node->value->TrangThai == 0)
			{
				DangMuon++;
				if (inside(ms, node->value->MaSach))
					return 3;
				if (MuonQuaHan(&(node->value->NgayMuon), &(node->value->NgayTra)))
					return 2;
			}
		}
		if (DangMuon == 3)
			return 1;
		int tt = TTSach(DSDS, ms);
		return (tt == 0) ? 0 : (tt + 3);
	}
}

// MUONSACH
int MuonSach(TheDocGia *thedocgia, char *masach, DS_DauSach &DSDS)
{
	if (thedocgia->TrangThai == 0)
		return 7; // THE BI KHOA
	int TH = DK_MuonSach(thedocgia->DS_MT->First, masach, DSDS);
	if (TH == 0)
	{
		// lay sach muon
		DM_Sach *SachMuon = GetSach(DSDS, masach);
		// doi trang thai sach thanh DA DUOC MUON
		SachMuon->sach->TrangThai = 1;
		SachMuon->sach->SoLuotMuon++;
		// thiet lap muon tra
		MuonTra *newnode = new MuonTra;
		newnode->NgayMuon.GetTimeNow();
		newnode->NgayMuon.GetRes();
		newnode->NgayTra.Day = newnode->NgayTra.Month = newnode->NgayTra.Year = 0;
		newnode->NgayTra.GetRes();
		strcpy(newnode->MaSach, masach);
		newnode->TrangThai = 0;
		// them vao DSMT
		thedocgia->TongSoLuong++;
		InsertLast_DM_MuonTra(thedocgia->DS_MT, newnode);
		return 0;
	}
	else
		return TH;
}
// TRASACH
int TraSach(TheDocGia *thedocgia, char *masach, DS_DauSach &DSDS)
{
	NodeMuonTra *find = thedocgia->DS_MT->First;
	// tim sach da muon
	while (find)
		if (!strcmp(masach, find->value->MaSach))
		{
			// chinh sua DSMT & Muon cua DocGia
			find->value->TrangThai = 1;
			find->value->NgayTra.GetTimeNow();
			find->value->NgayTra.GetRes();
			// tra sach ve trang thai co the muon
			DM_Sach *SachTra = GetSach(DSDS, masach);
			SachTra->sach->TrangThai = 0;
			return 1;
		}
		else
			find = find->Right;
	return 0;
};
struct QuaHan
{
	int MaThe;
	char HoTen[51];
	char MaSach[15];
	char TenSach[30];
	DateTime NgayMuon;
	int SoNgayQuaHan;
	//
	QuaHan() {}
	QuaHan(int mathe, char hoten[51], char masach[15], char tensach[30], DateTime ngaymuon, int songayquahan)
	{
		MaThe = mathe;
		strcpy(HoTen, hoten);
		strcpy(MaSach, masach);
		strcpy(TenSach, tensach);
		NgayMuon = ngaymuon;
		SoNgayQuaHan = songayquahan;
	}
	~QuaHan() {}
	//
};
struct DS_QuaHan
{
	int n;
	QuaHan *nodes[MAX_SIZE_DAUSACH];
	void InsertQuaHan(DS_QuaHan &DSQH, QuaHan *quahan)
	{
		if (DSQH.n > MAX_SIZE_DAUSACH)
			std::cout << "Loi" << std::endl;
		else
		{
			int pos = DSQH.n;
			while (pos)
			{
				if (quahan->SoNgayQuaHan > DSQH.nodes[pos - 1]->SoNgayQuaHan)
					pos--;
				else
					break;
			}
			DSQH.n++;
			for (int i = DSQH.n; i >= pos; --i)
				DSQH.nodes[i] = DSQH.nodes[i - 1];
			DSQH.nodes[pos] = quahan;
		}
	}
};

void GetFromTree(NodeTheDocGia *root, DS_QuaHan &DSQH, DS_DauSach &DSDS)
{
	if (root == NULL)
		return;
	GetFromTree(root->left, DSQH, DSDS);
	NodeMuonTra *node = root->DocGia.DS_MT->First;
	while (node)
	{
		if (node->value->TrangThai == 0)
		{
			QuaHan *newnode = new QuaHan;
			char temp[51];
			newnode->MaThe = root->DocGia.MaThe;
			strcat(strcpy(temp, root->DocGia.Ho), " ");
			strcpy(newnode->HoTen, strcat(temp, root->DocGia.Ten));
			strcpy(newnode->MaSach, node->value->MaSach);
			for (int i = 0; i < DSDS.n; i++)
			{
				if (inside(newnode->MaSach, DSDS.nodes[i]->ISBN))
				{
					strcpy(newnode->TenSach, DSDS.nodes[i]->TenSach);
					break;
				}
			}
			newnode->NgayMuon.Day = node->value->NgayMuon.Day;
			newnode->NgayMuon.Month = node->value->NgayMuon.Month;
			newnode->NgayMuon.Year = node->value->NgayMuon.Year;
			newnode->NgayMuon.GetRes();
			newnode->SoNgayQuaHan = newnode->NgayMuon.GetSoNgayMuon();
			if (newnode->SoNgayQuaHan > 7){
				newnode->SoNgayQuaHan -= 7;
				DSQH.InsertQuaHan(DSQH, newnode);
			}
		}
		node = node->Right;
	}
	GetFromTree(root->right, DSQH, DSDS);
}

//	FREE MEMORY
// void FreeTreeAVLDocGia(NodeTheDocGia *&TreeAVLDocGia)
// {
// 	if (TreeAVLDocGia == NULL)
// 		return;
// 	FreeTreeAVLDocGia(TreeAVLDocGia->left);
// 	delete TreeAVLDocGia;
// 	FreeTreeAVLDocGia(TreeAVLDocGia->right);
// }
// void FreeDSDG(DS_DocGia &DSDG)
// {
// 	int k = MAX_SIZE_LIST_DOC_GIA;
// 	while (k--)
// 	{
// 		delete DSDG.nodes[k];
// 	}
// }
// void FreeDSMT(DS_MT &DSMT)
// {
// 	int k = MAX_SIZE_LIST_MT;
// 	while (k--)
// 	{
// 		delete DSMT.nodes[k];
// 	}
// }
// void FreeTopList(TopList &toplist)
// {
// 	int k = 10;
// 	while (k--)
// 	{
// 		delete toplist.nodes[k];
// 	}
// }
// void FreeDSQH(DS_QuaHan &DSQH)
// {
// 	int k = MAX_SIZE_DAUSACH;
// 	while (k--)
// 	{
// 		delete DSQH.nodes[k];
// 	}
// }
// void FreeMemory_DG_MT(NodeTheDocGia *&TreeAVLDocGia, DS_DocGia &DSDG, DS_MT &DSMT, TopList &toplist, DS_QuaHan &quahan)
// {
// 	FreeTreeAVLDocGia(NodeTheDocGia *TreeAVLDocGia);
// 	FreeDSDG(DS_DocGia DSDG);
// 	FreeDSMT(DS_MT DSMT);
// 	FreeTopList(TopList toplist);
// 	FreeDSQH(DS_QuaHan DSQH);
// }
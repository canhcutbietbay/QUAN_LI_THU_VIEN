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
	TheDocGia(int mathe, char ho[], char ten[], int phai, int trangthai)
	{
		// random MaThe...
		MaThe = mathe;
		strcpy(Ho, ho);
		strcpy(Ten, ten);
		Phai = phai;
		TrangThai = trangthai;
		DS_MT = NULL;
	}
};

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
struct NodeTheDocGia
{
	TheDocGia DocGia;
	NodeTheDocGia *left = NULL;
	NodeTheDocGia *right = NULL;
	int height = 0;
};
/*

*/
struct DS_QuaHan
{
	int MaThe;
	char HoTen[51];
	char MaSach[15];
	char TenSach[30];
	DateTime NgayMuon;
	int SoNgayQuaHan;
	DS_QuaHan *next;
	//
	DS_QuaHan() {}
	DS_QuaHan(int mathe, char hoten[51], char masach[15], char tensach[30], DateTime ngaymuon, int songayquahan)
	{
		MaThe = mathe;
		strcpy(HoTen, hoten);
		strcpy(MaSach, masach);
		strcpy(TenSach, tensach);
		NgayMuon = ngaymuon;
		SoNgayQuaHan = songayquahan;
	}
	~DS_QuaHan() {}
	//
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
/*

*/
// void GetDSMuon(NodeTheDocGia *node)
// {
// 	if (node == nullptr)
// 		return;
// 	else
// 	{
// 		NodeMuonTra *check = node->DocGia.DS_MT->First;
// 		while (check)
// 		{
// 			if (check->value->TrangThai == 0)
// 			{
// 				InsertLastDSMT(node->DocGia.Muon, check->value);
// 				check = check->Right;
// 			}
// 		}
// 	}
// }
// DS_MuonTra *GetDSMuon(NodeTheDocGia *node)
// {
// 	if (node == nullptr)
// 		return;
// 	else
// 	{
// 		NodeMuonTra *check = node->DocGia.DS_MT->First;
// 		int k = 0;
// 		while (check != nullptr)
// 		{
// 			if (check->value->TrangThai == 0)
// 			{
// 				node->DocGia.DS_Muon[k] = check->value;
// 				k++;
// 				if (k == 3)
// 					break;
// 			}
// 			check = check->Right;
// 		}
// 		return node->DocGia.DS_Muon;
// 	}
// }
//
//xet nodesach
// int checknodeSach(DM_Sach *dms, char* masach)
// {
//   DM_Sach *temp = dms;
//   while (temp)
//   {
//     if (!strcmp(masach, temp->sach->MaSach))
//       return temp->sach->TrangThai;
//     temp = temp->next;
//   }
//   return 3;
// }

// // Muon Qua Han
// bool MuonQuaHan(DateTime *NgayMuon, DateTime *NgayTra)
// {
//     if (NgayTra->Day != 0)
//         return false;
//     else if (NgayMuon->GetSoNgayMuon() > 7)
//         return true;
//     else
//         return false;
// }
// // check
// bool inside(char* S, char* s)
// {
//     int k=0;
//     while (S[k] == s[k])
//         if (S[k+1] == '-')
//             return true;
//         else k++;
//     return false;
// }
// int TTSach(DS_DauSach ds, char* masach)
// {
//     for (int i=0; i < ds.n; i++)
//     {
//         if (inside(masach, ds.nodes[i]->isbn))
//         return checknodeSach(ds.nodes[i]->DS_Sach, masach);
//     }
// }
// // lay dau sach tu masach
// DM_Sach *GetSach(DS_DauSach ds, char* masach)
// {
//     for (int i=0; i < ds.n; i++)
//     {
//         if (inside(masach, ds.nodes[i]->isbn))
//         	return GetDM_Sach(ds.nodes[i]->DS_Sach, masach);
//     }
// 	return nullptr;
// }
// /*
//     0- co the muon sach
//     1- muon 3 sach
//     2- muon 1 sach qua 7 ngay
//     3- chung 1 dau sach
//     4- sach da cho muon
//     5- sach da thanh li
//     6- khong co masach nay
// */

// int DK_MuonSach(NodeMuonTra *firstnode, char* ms, DS_DauSach DSDS)
// {
//     if (firstnode == nullptr)
//     {
//         int tt = TTSach(DSDS, masach);
//         return (tt == 0) ? 0 : (tt+3);
//     }
//     else
//     {
//         NodeMuonTra *node = new NodeMuonTra;
//         node = firstnode;
//         int DangMuon = 0;
//         for (;node != nullptr; node = node->Right)
//         {
//             if (node->value->TrangThai == 0)
//             {
//                 DangMuon++;
//                 if (inside(ms, node->value->MaSach))
//                     return 3;
//                 if (MuonQuaHan(&(node->value->NgayMuon), &(node->value->NgayTra)))
//                 return 2;
//             }
//         }
//         if (DangMuon == 3)
//             return 1;
//         int tt = TTSach(DSDS, masach);
//         return (tt == 0) ? 0 : (tt+3); 
//     }
// }
// /*
// -----------
// DANH SACH QUA HAN
// -----------
// */
// DS_QuaHan *CreateDSQH()
// {
//   DS_QuaHan *node = new DS_QuaHan;
//   node->next = nullptr;
//   return node;
// }
// DS_QuaHan *CreateDS_QuaHan(DS_DauSach &DSDS, DS_DocGia &DSDG)
// {
// 	DS_QuaHan *first, *insert, *bf;
// 	first = insert = bf = nullptr;
// 	// Nhap tat ca sach dang muon
// 	for (int i=0; i< DSDG.n; i++)
// 	{
// 		for (int j=0; j < DSDG.nodes[i]->Muon->n; j++)
// 		{
// 			DS_QuaHan *node = CreateDS_QuaHan();
// 			int k=0;
// 			while (!inside(DSDG.nodes[i]->Muon->nodes[j]->MaSach, DSDS.nodes[k]->ISBN))
// 				k++;
// 			node->MaThe = DSDG.nodes[i]->MaThe;
// 			char temp[51];
// 			strcat(strcpy(temp, DSDG.nodes[i]->Ho), " ");
// 			strcpy(node->HoTen, strcat(temp, DSDG.nodes[i]->Ten));
// 			strcpy(node->MaSach, DSDG.nodes[i]->Muon->nodes[j]->MaSach);
// 			strcpy(node->TenSach, DSDS.nodes[k]->TenSach);
// 			node->NgayMuon = DSDG.nodes[i]->Muon->nodes[j]->NgayMuon;
// 			node->SoNgayQuaHan = DSDG.nodes[i]->Muon->nodes[j]->NgayMuon.GetSoNgayMuon();
// 			node->next = nullptr;
// 			// sort & insert
// 			*bf = nullptr;
// 			insert = first;
// 			if (first)
// 			{
// 				while (1)
// 				{
// 					if (!bf) 
// 					{
// 						if (node->SoNgayQuaHan > insert->SoNgayQuaHan)
// 						{
// 							node->next = insert;
// 							bf->next = node;
// 							break;
// 						}
// 						bf = insert;
// 						insert = insert->next;
// 						if (!insert)
// 						{
// 							node->next = insert;
// 							bf->next = node;
// 							break;
// 						}
// 					}
// 					else 
// 					{
// 						if (node->SoNgayQuaHan > insert->SoNgayQuaHan)
// 						{
// 							node->next = insert;
// 							first = node;
// 							break;
// 						}
// 						bf = insert;
// 						insert = insert->next;
// 						if (!insert)
// 						{
// 							node->next = insert;
// 							first->next = node;
// 							break;
// 						}
// 					}
// 				}
// 			}
// 			else first = node;
// 		}
// 	}
// 	return first;
// }
// void UpdateDS_QuaHan_KhiMuon(DS_QuaHan *&first, DS_DauSach &DSDS, TheDocGia *thedocgia, char* masach)
// {
// 	DS_QuaHan *insert;
// 	if (!first)
// 	{
// 		first = CreateDSQH();
// 		insert = first;
// 	}
// 	else
// 	{ 
// 		insert = first; 
// 		while (insert->next)
// 		{
// 			insert->SoNgayQuaHan = insert->NgayMuon.GetSoNgayMuon();
// 			insert = insert->next;
// 		}
// 		insert->next = CreateDSQH();
// 		insert = insert->next;
// 	}
// 	char temp[51];
// 	insert->MaThe = thedocgia->MaThe;
// 	strcat(strcpy(temp, thedocgia->Ho), " ");
// 	strcpy(insert->HoTen, strcat(temp, thedocgia->Ten));
// 	strcpy(insert->MaSach, masach);
// 	for (int i=0; i < DSDS.n; i++)
// 		if(inside(masach,DSDS.nodes[i]->ISBN))
// 		{
// 			strcpy(insert->TenSach, DSDS.nodes[i]->TenSach);
// 			break;
// 		}
// 	insert->NgayMuon.GetTimeNow();
// 	insert->SoNgayQuaHan = insert->NgayMuon.GetSoNgayMuon();
// 	insert->next=nullptr;
// }
// void *UpdateDS_QuaHan_KhiTra(DS_QuaHan *&first, DS_DauSach &DSDS, TheDocGia *thedocgia, char* masach)
// {
// 	if (first)
// 	{
// 		DS_QuaHan *del = first, *bf = nullptr;
// 		while (strcmp(del->MaSach, masach))
// 		{
// 			del->SoNgayQuaHan = del->NgayMuon.GetSoNgayMuon();
// 			bf = del;
// 			del = del->next;
// 		}
// 		if (del == first)
// 			first = del->next;
// 		else 
// 		{
// 			bf = del->next;
// 			delete del;
// 		}
// 	}
// }
// /*
// ------------------
// MUON & TRA SACH
// ------------------
// */
// // MUONSACH
// int MuonSach(TheDocGia *thedocgia, char* masach, DS_DauSach &DSDS)
// {
// 	if (thedocgia->TrangThai == 0)
// 		return;// THE BI KHOA
// 	int TH = DK_MuonSach(thedocgia->DS_MT->First, masach, DSDS);
// 	if (TH == 0)
// 	{
// 		//lay sach muon
// 		DM_Sach *SachMuon = GetSach(DSDS, masach);
// 		//doi trang thai sach thanh DA DUOC MUON
// 		SachMuon->sach->TrangThai = 1;
// 		//thiet lap muon tra 
// 		MuonTra *newnode = new MuonTra;
// 		newnode->MaSach = masach;
// 		newnode->TrangThai = 0;
// 		newnode->NgayMuon.GetTimeNow();
// 		newnode->NgayTra.Day = newnode->NgayTra.Month = newnode->NgayTra.Year = 0;
// 		//them vao DSMT
// 		InsertLast_DM_MuonTra(thedocgia->DS_MT, newnode);
// 		//them vao DSMUON
// 		thedocgia->Muon->nodes[thedocgia->Muon->n] = newnode;
// 		thedocgia->Muon->n++;
// 	}
// 	else return TH;
// }
// // TRASACH
// int TraSach(TheDocGia *thedocgia, char* masach, DS_DauSach &DSDS)
// {
// 	NodeMuonTra *find = thedocgia->DS_MT->First;
// 	// tim sach da muon
// 	while (find)
// 		if (!strcmp(masach, find->value->MaSach))
// 		{
// 			// chinh sua DSMT & Muon cua DocGia
// 			find->value->TrangThai = 1;
// 			find->value->NgayTra.GetTimeNow();
// 			thedocgia->Muon->nodes[thedocgia->Muon->n - 1] = nullptr;
// 			thedocgia->Muon->n--;
// 			// tra sach ve trang thai co the muon
// 			DM_Sach *SachTra = GetSach(DSDS, masach);
// 			SachTra->sach->TrangThai = 0;
// 			return 1;
// 		}
// 		else find = find->Right;
// 	return 0;
// }

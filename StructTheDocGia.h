#define MAX_SIZE_LIST_DOC_GIA 90000
/*

*/
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
//
struct DSMT
{
	int n;
	MuonTra *nodes[3];
	DSMT()
	{
		n = 0;
	}
	~DSMT() {}
};

// su dung khi doc file
void InsertLastDSMT(DSMT *DSMuon, MuonTra *muontra)
{
	if (DSMT->n > 3)
		printf("DSMuon day \n");
	else
	{
		DSMT->nodes[DSMT->n] = muontra;
		(DSMT->n)++;
	}
}
//
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
	DS_MuonTra *DS_MT;
	DSMT *Muon;
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
//
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

void GetFromTree(NodeTheDocGia *root, DS_DocGia &DSDG)
{
	if (root == NULL)
		return;
	GetFromTree(root->left, DSDG);
	DSDG.InsertLastDocGia(DSDG, &root->DocGia);
	GetFromTree(root->right, DSDG);
}

// void GetDSMuon(NodeTheDocGia *node)
// {
// 	if (node == nullptr)
// 		return;
// 	else
// 	{
// 		NodeMuonTra *check = node->DocGia.DS_MT->First;
// 		while (check != nullptr)
// 		{
// 			if (check->value->TrangThai == 0)
// 			{
// 				InsertLastDSMT(node->DocGia.Muon, check->value);
// 			}
// 			check = check->Right;
// 		}
// 	}
// }

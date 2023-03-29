struct TheDocGia
{
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
	DS_MuonTra *DS_MT;

	// constructor
	TheDocGia() {}
	TheDocGia(int mathe, char ho[20], char ten[11], int phai, int trangthai)
	{
		MaThe = mathe;
		strcpy(Ho, ho);
		strcpy(Ten, ten);
		Phai = phai;
		TrangThai = trangthai;
	}
};

// Cay AVL
struct NodeTheDocGia
{
	// key = DocGia.MaThe
	TheDocGia DocGia;
	int bf;
	NodeTheDocGia *left = nullptr;
	NodeTheDocGia *right = nullptr;
};
/*

*/
// ham cua Cay AVL
NodeTheDocGia Rotate_Left(NodeTheDocGia root)
{
	NodeTheDocGia p;
	if (root != nullptr)
		if (root.right != nullptr)
		{
			p = root.right;
			root.right = p.left;
			p.left = root;
		}
	return p;
}
NodeTheDocGia Rotate_Right(NodeTheDocGia root)
{
	NodeTheDocGia p;
	if (root != nullptr)
		if (root.left != nullptr)
		{
			p = root.left;
			root.left = p.right;
			p.right = root;
		}
	return p;
}
/*
Them vao cay
*/
void Insert(NodeTheDocGia &pavltree, int x)
{
	NodeTheDocGia fp, p, q, fya, ya, s;
	int imbal;
	fp = nullptr;
	p = pavltree;
	fya = nullptr;
	ya = p;
	// tim nut fp, ya va fya, nut moi them vao la nut la con cua nut fp
	while (p != nullptr)
	{
		if (x == p.DocGia.MaThe) // bi trung khoa
			return;
		if (x < p.DocGia.MaThe)
			q = p.left;
		else
			q = p.right;
		if (q != nullptr)
			if (q.bf != 0) // truong hop chi so can bang cua q la 1 hay -1
			{
				fya = p;
				ya = q;
			}
		fp = p;
		p = q;
	}
	// Thêm nút mới (nut la) la con cua nut fp
	q = new NodeTheDocGia; // cấp phát vùng nhớ
	q.DocGia.MaThe = x;
	q.bf = 0;
	q.left = nullptr;
	q.right = nullptr;
	if (x < fp.DocGia.MaThe)
		fp.left = q;
	else
		fp.right = q;

	/*Hieu chinh chi so can bang cua tat ca cac nut giua ya va q, neu bi lech
		 ve phia trai thi chi so can bang cua tat ca cac nut giua ya va q deu la
		 1, neu bi lech ve phia phai thi chi so can bang cua tat ca cac nut giua
		 ya va q deu la -1 */
	if (x < ya.DocGia.MaThe)
		p = ya.left;
	else
		p = ya.right;
	s = p; // s là con của nút ya
	while (p != q)
	{
		if (x < p.DocGia.MaThe)
		{
			p.bf = 1;
			p = p.left;
		}
		else
		{
			p.bf = -1;
			p = p.right;
		}
	}
	// xac dinh huong lech
	if (x < ya.DocGia.MaThe)
		imbal = 1;
	else
		imbal = -1;

	if (ya.bf == 0)
	{
		ya.bf = imbal;
		return;
	}
	if (ya.bf != imbal)
	{
		ya.bf = 0;
		return;
	}
	// cây mất cân bằng
	if (s.bf == imbal) // Truong hop xoay don
	{
		if (imbal == 1) // xoay phai
			p = Rotate_Right(ya);
		else // xoay trai
			p = Rotate_Left(ya);
		ya.bf = 0;
		s.bf = 0;
	}
	else // Truong hop xoay kep
	{
		if (imbal == 1) // xoay kep trai-phai
		{
			ya.left = Rotate_Left(s);
			p = Rotate_Right(ya);
		}
		else // xoay kep phai-trai -
		{
			ya.right = Rotate_Right(s);
			p = Rotate_Left(ya);
		}
		if (p.bf == 0) // truong hop p la nut moi them vao
		{
			ya.bf = 0;
			s.bf = 0;
		}
		else if (p.bf == imbal)
		{
			ya.bf = -imbal;
			s.bf = 0;
		}
		else
		{
			ya.bf = 0;
			s.bf = imbal;
		}
		p.bf = 0;
	}
	if (fya == nullptr)
		pavltree = p;
	else if (ya == fya.right)
		fya.right = p;
	else
		fya.left = p;
}
/*
TAO CAY TIM KIEM AVL
*/
void Create_AVLTree(NodeTheDocGia &root)
{
	int mathe;
	char ho[20];
	char ten[11];
	int phai;
	/*
	 * 0: Nam
	 * 1: Nu
	 */
	int trangthai;
	/*
	 * 0: Khoa
	 * 1: Hoat dong
	 */
	DS_MuonTra *ds_mt;
	//
	NodeTheDocGia p;
	do
	{
		//...
		if (mathe != 0)
		{
			//...
			if (root == nullptr)
			{
				// p = New_Node();...//
				// p.DocGia.MaThe = mathe;
				// p.bf = 0;
				// p.left = nullptr;
				// p.right = nullptr;
				// root = p;
			}
			else
				Insert(root, mathe);
		}
	} while (mathe != 0); // khóa =0 thì dừng nhập
}

int MT[90000];

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
	TheDocGia(char ho[20], char ten[11], int phai, int trangthai)
	{
		// random MaThe...
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
	int bf = 0;
	NodeTheDocGia *left = nullptr;
	NodeTheDocGia *right = nullptr;
};
//
// ham cua Cay AVL
NodeTheDocGia *Rotate_Left(NodeTheDocGia *root)
{
	NodeTheDocGia *p;
	if (root != nullptr)
		if (root->right != nullptr)
		{
			p = root->right;
			root->right = p->left;
			p->left = root;
		}
	return p;
}
NodeTheDocGia *Rotate_Right(NodeTheDocGia *root)
{
	NodeTheDocGia *p;
	if (root != nullptr)
		if (root->left != nullptr)
		{
			p = root->left;
			root->left = p->right;
			p->right = root;
		}
	return p;
}
/*
Them vao cay
*/
void InsertDocGia(NodeTheDocGia *TreeAVLDocGia, TheDocGia *docgia)
{
	NodeTheDocGia *fp, *p, *q, *fya, *ya, *s;
	int imbal;
	fp = nullptr;
	p = TreeAVLDocGia;
	fya = nullptr;
	ya = p;

	while (p != nullptr)
	{
		if (docgia->MaThe == p->DocGia.MaThe) // bi trung khoa
			return;
		if (docgia->MaThe < p->DocGia.MaThe)
			q = p->left;
		else
			q = p->right;
		if (q != nullptr)
			if (q->bf != 0) // truong hop chi so can bang cua q la 1 hay -1
			{
				fya = p;
				ya = q;
			}
		fp = p;
		p = q;
	}
	// Thêm nút mới (nut la) la con cua nut fp
	q = new NodeTheDocGia;
	q->DocGia.MaThe = docgia->MaThe;
	strcpy(q->DocGia.Ho, docgia->Ho);
	strcpy(q->DocGia.Ten, docgia->Ten);
	q->DocGia.Phai = docgia->Phai;
	q->DocGia.TrangThai = docgia->TrangThai;
	q->DocGia.DS_MT = nullptr;
	// q->bf = 0;
	// q->left = nullptr;
	// q->right = nullptr;
	if (docgia->MaThe < fp->DocGia.MaThe)
		fp->left = q;
	else
		fp->right = q;

	/*Hieu chinh chi so can bang cua tat ca cac nut giua ya va q, neu bi lech
		 ve phia trai thi chi so can bang cua tat ca cac nut giua ya va q deu la
		 1, neu bi lech ve phia phai thi chi so can bang cua tat ca cac nut giua
		 ya va q deu la -1 */
	if (docgia->MaThe < ya->DocGia.MaThe)
		p = ya->left;
	else
		p = ya->right;
	s = p; // s là con của nút ya
	while (p != q)
	{
		if (docgia->MaThe < p->DocGia.MaThe)
		{
			p->bf = 1;
			p = p->left;
		}
		else
		{
			p->bf = -1;
			p = p->right;
		}
	}
	// xac dinh huong lech
	if (docgia->MaThe < ya->DocGia.MaThe)
		imbal = 1;
	else
		imbal = -1;
	// cay vua lech
	if (ya->bf == 0)
	{
		ya->bf = imbal;
		return;
	}
	// cay het lech
	if (ya->bf != imbal)
	{
		ya->bf = 0;
		return;
	}
	// cây mất cân bằng
	if (s->bf == imbal) // Truong hop xoay don
	{
		if (imbal == 1) // xoay phai
			p = Rotate_Right(ya);
		else // xoay trai
			p = Rotate_Left(ya);
		ya->bf = 0;
		s->bf = 0;
	}
	else // Truong hop xoay kep
	{
		if (imbal == 1) // xoay kep trai-phai
		{
			ya->left = Rotate_Left(s);
			p = Rotate_Right(ya);
		}
		else // xoay kep phai-trai -
		{
			ya->right = Rotate_Right(s);
			p = Rotate_Left(ya);
		}
		if (p->bf == 0) // truong hop p la nut moi them vao
		{
			ya->bf = 0;
			s->bf = 0;
		}
		else if (p->bf == imbal)
		{
			ya->bf = -imbal;
			s->bf = 0;
		}
		else
		{
			ya->bf = 0;
			s->bf = imbal;
		}
		p->bf = 0;
	}
	if (fya == nullptr)
		TreeAVLDocGia = p;
	else if (ya == fya->right)
		fya->right = p;
	else
		fya->left = p;
}
/*
TAO CAY TIM KIEM AVL
*/
NodeTheDocGia *Create_AVLTree(TheDocGia *root) // tao cay khi nhap data tu file
{
	NodeTheDocGia *fr = new NodeTheDocGia;
	//...
	if (root != nullptr)
	{
		fr->DocGia.MaThe = root->MaThe;
		strcpy(fr->DocGia.Ho, root->Ho);
		strcpy(fr->DocGia.Ten, root->Ten);
		fr->DocGia.Phai = root->Phai;
		fr->DocGia.TrangThai = root->TrangThai;
		fr->DocGia.DS_MT = nullptr;
		// fr->bf = 0;
		// fr->left = nullptr;
		// fr->right = nullptr;
		return fr;
	}
	else
		return;
}
/*
XOA NUT CAY AVL
*/
void RemoveDocGia(NodeTheDocGia *TreeAVLDocGia, int mathe)
{
}
/*
HIEU CHINH THONG TIN DOC GIA
*/

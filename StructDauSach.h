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
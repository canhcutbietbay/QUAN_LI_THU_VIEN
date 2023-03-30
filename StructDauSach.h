#define MAX_SIZE_LIST_DAU_SACH 100

struct DauSach
{
    char ISBN[15], TenSach[25], TacGia[25], TheLoai[25];
    int SoTrang, NXB;
    NodeSach *DS_Sach;

    // constructor
    DauSach() {}
    DauSach(char isbn[], char tensach[], char tacgia[], char theloai[], int sotrang, int nxb)
    {
        strcpy(ISBN, isbn);
        strcpy(TenSach, tensach);
        strcpy(TacGia, tacgia);
        strcpy(TheLoai, theloai);
        SoTrang = sotrang;
        NXB = nxb;
    }

    // destructor
    ~DauSach(){};
};
struct DS_DauSach
{
    int n;
    DauSach *nodes[MAX_SIZE_LIST_DAU_SACH];
    DS_DauSach()
    {
        n = 0;
    }
    ~DS_DauSach() {}
};

	// su dung khi doc file
void InsertLastDauSach(DS_DauSach &DSDS, DauSach *dausach){
	if(DSDS.n > MAX_SIZE_LIST_DAU_SACH)
		printf("DSDS day \n");
	else{
		DSDS.nodes[DSDS.n] = dausach;
        DSDS.n++;
	}
}
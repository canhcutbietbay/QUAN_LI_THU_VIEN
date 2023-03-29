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

struct TreeTheDocGia
{
	// key info.MaThe
	TheDocGia info;
	int bf;
	TreeTheDocGia *Left = nullptr;
	TreeTheDocGia *Right = nullptr;
};

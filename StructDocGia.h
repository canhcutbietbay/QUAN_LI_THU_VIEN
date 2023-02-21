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

const int X_DS = w / 10, Y_DS = h / 7;
const int XDS[] = {10, X_DS * 1.5, X_DS * 4, X_DS * 7, X_DS * 8.5, X_DS * 9.5, X_DS * 10 - 10};
const int XDMS[] = {10, X_DS * 4, X_DS * 7, X_DS * 10 - 10};
const int XDG[] = {10, X_DS * 2, X_DS * 4, X_DS * 6, X_DS * 8, X_DS * 10 - 10};
const int XXDG[] = {10, X_DS * 2, X_DS * 4.5, X_DS * 7, X_DS * 8.5, X_DS * 10 - 10};
const int XQH[] = {10, X_DS * 1.5, X_DS * 3.5, X_DS * 5, X_DS * 7.5, X_DS * 9, X_DS * 10 - 10};
const int XT10[] = {10, X_DS * 1, X_DS * 3.5, X_DS * 6, X_DS * 7.5, X_DS * 8.5, X_DS * 9, X_DS * 10 - 10};
const int ContentHeight = (Y_DS * 5 - Y_DS - 50) / 10;
int CurrentMenuId = 0, LastCurrenMenuID = 0;
int mouseX = 0, mouseY = 0;
bool isExit = 0;

int CurrentItem = -1, SubCurrentItem = -1, CurrentAddDMS = -1, TotalAddDMS = -1;
// Button
int ButtonHeight = 60, ButtonWidth = 300, ButtonSpace = 80, ButtonY = 200;
Button ButtonDauSach(100, w / 2 - ButtonWidth / 2, ButtonY + ButtonSpace, ButtonWidth, ButtonHeight, "QUAN LY DAU SACH", 0);
Button ButtonDocGia(200, w / 2 - ButtonWidth / 2, ButtonY + 2 * ButtonSpace, ButtonWidth, ButtonHeight, "QUAN LY DOC GIA", 0);
Button ButtonThongKe(300, w / 2 - ButtonWidth / 2, ButtonY + 3 * ButtonSpace, ButtonWidth, ButtonHeight, "THONG KE", 0);
Button ButtonThongTin(400, w / 2 - ButtonWidth / 2, ButtonY + 4 * ButtonSpace, ButtonWidth, ButtonHeight, "THONG TIN", 0);
Button ButtonThoat(500, w / 2 - ButtonWidth / 2, ButtonY + 5 * ButtonSpace, ButtonWidth, ButtonHeight, "THOAT", 0);

int DefaultButtonHeight = 50, DefaultButtonWidth = 100;
EditButton *ButtonTemp = nullptr;
Button ButtonBack(0, 10, 10, DefaultButtonWidth, DefaultButtonHeight, "BACK", 0);
Button ButtonOKThongBao;
Button ButtonPrev(0, XDS[0], Y_DS * 5 + 10, DefaultButtonWidth, DefaultButtonHeight, "Prev", 0);
Button ButtonNext(0, XDS[6] - 100, Y_DS * 5 + 10, DefaultButtonWidth, DefaultButtonHeight, "Next", 0);
Button ButtonThem(0, w / 3 + w / 9 - DefaultButtonWidth / 2, h / 2 - h / 4 + 200 + DefaultButtonHeight * 6, DefaultButtonWidth, DefaultButtonHeight, "THEM", 0);
Button ButtonClearData(0, w / 3 + w / 6 + DefaultButtonWidth / 2, h / 2 - h / 4 + 200 + DefaultButtonHeight * 6, DefaultButtonWidth, DefaultButtonHeight, "CLEAR", 0);
Button ButtonDongY;
Button ButtonHuyBo;

// Dau Sach
EditButton ButtonSearchDauSach(101, w / 2 - w / 6, 50, w / 3, 50, "TIM DAU SACH", "", "NHAP TEN DAU SACH");
Button ButtonXemDauSach(102, (w / 4) * 1 - DefaultButtonWidth / 2 - w / 8, Y_DS * 6 - 10 - DefaultButtonHeight, DefaultButtonWidth, DefaultButtonHeight, "XEM", 0);
Button ButtonThemDauSach(103, (w / 4) * 2 - DefaultButtonWidth / 2 - w / 8, Y_DS * 6 - 10 - DefaultButtonHeight, DefaultButtonWidth, DefaultButtonHeight, "THEM", 0);
Button ButtonXoaDauSach(104, (w / 4) * 3 - DefaultButtonWidth / 2 - w / 8, Y_DS * 6 - 10 - DefaultButtonHeight, DefaultButtonWidth, DefaultButtonHeight, "XOA", 0);
Button ButtonSuaDauSach(105, (w / 4) * 4 - DefaultButtonWidth / 2 - w / 8, Y_DS * 6 - 10 - DefaultButtonHeight, DefaultButtonWidth, DefaultButtonHeight, "SUA", 0);
Button ButtonClearSearchDauSach(106, w / 2 + w / 6 + 20, 50, DefaultButtonWidth, DefaultButtonHeight, "CLEAR", 0);
EditButton ButtonThemISBN(107, w / 2 - w / 6 + 10, h / 2 - h / 4 + 50, w / 3 - 20, DefaultButtonHeight, "ISBN", "", "NHAP VAO ISBN");
EditButton ButtonThemTenSach(108, w / 2 - w / 6 + 10, h / 2 - h / 4 + 60 + DefaultButtonHeight, w / 3 - 20, DefaultButtonHeight, "TEN SACH", "", "NHAP VAO TEN SACH");
EditButton ButtonThemSoTrang(109, w / 2 - w / 6 + 10, h / 2 - h / 4 + 70 + DefaultButtonHeight * 2, w / 3 - 20, DefaultButtonHeight, "SO TRANG", "", "NHAP VAO SO TRANG");
EditButton ButtonThemTacGia(110, w / 2 - w / 6 + 10, h / 2 - h / 4 + 80 + DefaultButtonHeight * 3, w / 3 - 20, DefaultButtonHeight, "TAC GIA", "", "NHAP VAO TAC GIA");
EditButton ButtonThemNXB(111, w / 2 - w / 6 + 10, h / 2 - h / 4 + 90 + DefaultButtonHeight * 4, w / 3 - 20, DefaultButtonHeight, "NXB", "", "NHAP VAO NAM XUAT BAN");
EditButton ButtonThemTheLoai(112, w / 2 - w / 6 + 10, h / 2 - h / 4 + 100 + DefaultButtonHeight * 5, w / 3 - 20, DefaultButtonHeight, "THE LOAI", "", "NHAP VAO THEO LOAI");
EditButton ButtonSuaISBN(113, w / 2 - w / 6 + 10, h / 2 - h / 4 + 50, w / 3 - 20, DefaultButtonHeight, "ISBN", "", "NHAP VAO ISBN");
EditButton ButtonSuaTenSach(114, w / 2 - w / 6 + 10, h / 2 - h / 4 + 60 + DefaultButtonHeight, w / 3 - 20, DefaultButtonHeight, "TEN SACH", "", "NHAP VAO TEN SACH");
EditButton ButtonSuaSoTrang(115, w / 2 - w / 6 + 10, h / 2 - h / 4 + 70 + DefaultButtonHeight * 2, w / 3 - 20, DefaultButtonHeight, "SO TRANG", "", "NHAP VAO SO TRANG");
EditButton ButtonSuaTacGia(126, w / 2 - w / 6 + 10, h / 2 - h / 4 + 80 + DefaultButtonHeight * 3, w / 3 - 20, DefaultButtonHeight, "TAC GIA", "", "NHAP VAO TAC GIA");
EditButton ButtonSuaNXB(127, w / 2 - w / 6 + 10, h / 2 - h / 4 + 90 + DefaultButtonHeight * 4, w / 3 - 20, DefaultButtonHeight, "NXB", "", "NHAP VAO NAM XUAT BAN");
EditButton ButtonSuaTheLoai(128, w / 2 - w / 6 + 10, h / 2 - h / 4 + 100 + DefaultButtonHeight * 5, w / 3 - 20, DefaultButtonHeight, "THE LOAI", "", "NHAP VAO THEO LOAI");
Button ButtonThemDMS(129, (w / 3) * 1 - DefaultButtonWidth / 2 - w / 6, Y_DS * 6 - 10 - DefaultButtonHeight, DefaultButtonWidth, DefaultButtonHeight, "THEM", 0);
Button ButtonXoaDMS(130, (w / 3) * 2 - DefaultButtonWidth / 2 - w / 6, Y_DS * 6 - 10 - DefaultButtonHeight, DefaultButtonWidth, DefaultButtonHeight, "XOA", 0);
Button ButtonSuaDMS(131, (w / 3) * 3 - DefaultButtonWidth / 2 - w / 6, Y_DS * 6 - 10 - DefaultButtonHeight, DefaultButtonWidth, DefaultButtonHeight, "SUA", 0);
EditButton ButtonThemSoLuong(132, w / 2 - w / 6 + 10, h / 2 - DefaultButtonHeight / 2, w / 3 - 20, DefaultButtonHeight, "SO LUONG", "", "NHAP VAO SO LUONG");
EditButton ButtonThemMaSach(133, w / 2 - w / 6 + 10, h / 3 + 30 + DefaultButtonHeight * 1, w / 3 - 20, DefaultButtonHeight, "MA SACH", "", "NHAP VAO MA SACH");
EditButton ButtonThemTrangThaiSach(134, w / 2 - w / 6 + 10, h / 3 + 40 + DefaultButtonHeight * 2, w / 3 - 20, DefaultButtonHeight, "TRANG THAI", "", "NHAP VAO TRANG THAI");
EditButton ButtonThemViTriSach(135, w / 2 - w / 6 + 10, h / 3 + 50 + DefaultButtonHeight * 3, w / 3 - 20, DefaultButtonHeight, "VI TRI", "", "NHAP VAO VI TRI");
EditButton ButtonSuaMaSach(136, w / 2 - w / 6 + 10, h / 3 + 30 + DefaultButtonHeight * 1, w / 3 - 20, DefaultButtonHeight, "MA SACH", "", "NHAP VAO MA SACH");
EditButton ButtonSuaTrangThaiSach(137, w / 2 - w / 6 + 10, h / 3 + 40 + DefaultButtonHeight * 2, w / 3 - 20, DefaultButtonHeight, "TRANG THAI", "", "NHAP VAO TRANG THAI");
EditButton ButtonSuaViTriSach(138, w / 2 - w / 6 + 10, h / 3 + 50 + DefaultButtonHeight * 3, w / 3 - 20, DefaultButtonHeight, "VI TRI", "", "NHAP VAO VI TRI");
// Doc Gia
Button ButtonDocGiaMaThe(201, w / 2 - DefaultButtonWidth - 10, Y_DS - 75, DefaultButtonWidth, DefaultButtonHeight, "MA THE", 0);
Button ButtonDocGiaHoTen(202, w / 2 + 10, Y_DS - 75, DefaultButtonWidth, DefaultButtonHeight, "HO TEN", 0);
Button ButtonXemDocGia(203, (w / 4) * 1 - DefaultButtonWidth / 2 - w / 8, Y_DS * 6 - 10 - DefaultButtonHeight, DefaultButtonWidth, DefaultButtonHeight, "XEM", 0);
Button ButtonThemDocGia(204, (w / 4) * 2 - DefaultButtonWidth / 2 - w / 8, Y_DS * 6 - 10 - DefaultButtonHeight, DefaultButtonWidth, DefaultButtonHeight, "THEM", 0);
Button ButtonXoaDocGia(205, (w / 4) * 3 - DefaultButtonWidth / 2 - w / 8, Y_DS * 6 - 10 - DefaultButtonHeight, DefaultButtonWidth, DefaultButtonHeight, "XOA", 0);
Button ButtonSuaDocGia(206, (w / 4) * 4 - DefaultButtonWidth / 2 - w / 8, Y_DS * 6 - 10 - DefaultButtonHeight, DefaultButtonWidth, DefaultButtonHeight, "SUA", 0);
EditButton ButtonThemMaThe(207, w / 2 - w / 6 + 10, h / 2 - h / 4 + 80, w / 3 - 20, DefaultButtonHeight, "MA THE", "", "NHAP VAO MA THE");
EditButton ButtonThemHo(208, w / 2 - w / 6 + 10, h / 2 - h / 4 + 90 + DefaultButtonHeight, w / 3 - 20, DefaultButtonHeight, "HO", "", "NHAP VAO HO");
EditButton ButtonThemTen(209, w / 2 - w / 6 + 10, h / 2 - h / 4 + 100 + DefaultButtonHeight * 2, w / 3 - 20, DefaultButtonHeight, "TEN", "", "NHAP VAO TEN");
EditButton ButtonThemPhai(2010, w / 2 - w / 6 + 10, h / 2 - h / 4 + 110 + DefaultButtonHeight * 3, w / 3 - 20, DefaultButtonHeight, "PHAI", "", "0: NAM - 1: NU");
EditButton ButtonThemTrangThai(211, w / 2 - w / 6 + 10, h / 2 - h / 4 + 120 + DefaultButtonHeight * 4, w / 3 - 20, DefaultButtonHeight, "TRANG THAI", "", "0: KHOA - 1:HOAT DONG");
EditButton ButtonSuaMaThe(212, w / 2 - w / 6 + 10, h / 2 - h / 4 + 80, w / 3 - 20, DefaultButtonHeight, "MA THE", "", "NHAP VAO MA THE");
EditButton ButtonSuaHo(213, w / 2 - w / 6 + 10, h / 2 - h / 4 + 90 + DefaultButtonHeight, w / 3 - 20, DefaultButtonHeight, "HO", "", "NHAP VAO HO");
EditButton ButtonSuaTen(214, w / 2 - w / 6 + 10, h / 2 - h / 4 + 100 + DefaultButtonHeight * 2, w / 3 - 20, DefaultButtonHeight, "TEN", "", "NHAP VAO TEN");
EditButton ButtonSuaPhai(215, w / 2 - w / 6 + 10, h / 2 - h / 4 + 110 + DefaultButtonHeight * 3, w / 3 - 20, DefaultButtonHeight, "PHAI", "", "0: NAM - 1: NU");
EditButton ButtonSuaTrangThai(216, w / 2 - w / 6 + 10, h / 2 - h / 4 + 120 + DefaultButtonHeight * 4, w / 3 - 20, DefaultButtonHeight, "TRANG THAI", "", "0: KHOA - 1:HOAT DONG");
Button ButtonMuonSach(216, (w / 2) * 1 - DefaultButtonWidth / 2 - w / 4, Y_DS * 6 - 10 - DefaultButtonHeight, DefaultButtonWidth, DefaultButtonHeight, "MUON", 0);
Button ButtonTraSach(217, (w / 2) * 2 - DefaultButtonWidth / 2 - w / 4, Y_DS * 6 - 10 - DefaultButtonHeight, DefaultButtonWidth, DefaultButtonHeight, "TRA", 0);
EditButton ButtonNhapMaSach(218, w / 2 - w / 6 + 10, h / 2 - DefaultButtonHeight / 2, w / 3 - 20, DefaultButtonHeight, "MA SACH", "", "NHAP MA SACH");
// Thong ke
Button ButtonThongKeQuaHan(301, w / 2 - DefaultButtonWidth - 10 - 25, Y_DS - 75, DefaultButtonWidth + 25, DefaultButtonHeight, "QUA HAN", 0);
Button ButtonThongKeTop10(302, w / 2 + 10, Y_DS - 75, DefaultButtonWidth + 25, DefaultButtonHeight, "TOP 10", 0);

// global
DS_DauSach DSDS; 
DS_DauSach ListSearchDauSach;
DS_DMS DSDMS;

DS_MT DSMT;
DS_QuaHan DSQH;
TopList DS10;
NodeTheDocGia *TreeAVLDocGia, *SubTree;
DS_DocGia DSDG;


char AppTitle[50] = "QUAN LY THU VIEN";
char NumOfPage[10] = "";
int CurrentPage = 1, TotalPage = 0;
int SubCurrentPage = 1;

char MuonSachCode[][25] = {"MUON SACH THANH CONG", // 0
                           "DA MUON 3 SACH", //1
                           "MUON 1 SACH QUA 7 NGAY",//2
                           "MUON CUNG 1 DAU SACH",//3
                           "SACH DA CHO MUON",//4
                           "SACH DA THANH LY",//5
                           "MA SACH KHONG TON TAI",//6
                           "THE DA BI KHOA"};//7
char XoaSachCode [][25] = {"XOA THAT BAI", "XOA THANH CONG"};
char SuaSachCode [][25] = {"SUA THAT BAI", "SUA THANH CONG"};

// ---------------------------------------------------- //
//help
void InDanhSachDauSach(DS_DauSach &DSDS);
void InDMS();
void InMuonTra(NodeTheDocGia *&TreeAVLDocGia);
void InTop10();
std::string GetNumberFromMaSach(std::string MaSach);
int FindPosBookName(char maSach[15]);
void ClearScreen();
void ClearScreenXY(int x, int y, int z, int t);
void ThongBao(char Data[], int width, int height, int NextMenu);
void GetCurrentItem(int mouseY);
void ClearEditButtonData(EditButton &Button);
void CLearLastCharInput();
void ThongBaoEvent();
void MoveToNextEditTextButton();
boolean CheckInput(char c);
void KeyBoardEvent();
void ButtonEffect(Button &Button);
void SetMenuSelect(int MenuID);


// Menu
void DrawMenu();

//Dau Sach
void SearchDauSach(char TenSach[]);
void RunDauSach();
void DrawItemDauSach(DS_DauSach DSDS);
void DrawSelecteItemDauSach(DS_DauSach DSDS);
void RunXemDauSach();
void DrawItemDMS(DS_DMS &DSDMS);
void DrawSelectedItemDMS(DS_DMS &DSDMS);
void RunThemDMS();
void RunThemSach();
void RunXoaDMS();
void RunSuaDMS();
void RunThemDauSach();
void RunXoaDauSach();
void RunSuaDauSach();

// Doc Gia
void RunDocGia();
void DrawItemDocGia(DS_DocGia DSDG);
void DrawSelecteItemDocGia(DS_DocGia DSDG);
void RunXemDocGia();
void DrawItemMuonTra(DS_MT DSMT);
void DrawSelectedItemMuonTra(DS_MT DSMT);
void RunMuonSach();
void RunThemDocGia();
void RunXoaDocGia();
void RunSuaDocGia();

// Thong Ke
void RunThongKe();
void RunQuaHan();
void DrawItemQuaHan(DS_QuaHan DSQH);
void RunTop10();
void DrawItemTop10(TopList &DS10);

// Thong Tin
void RunThongTin();

// In-Out

void GetDataDauSachFromFile(DS_DauSach &DSDS);
void GetDataDocGiaFromFile(NodeTheDocGia *&TreeAVLDocGia);
void GetDataDocGiaFromFile(NodeTheDocGia *&TreeAVLDocGia);

void WriteDataDauSachToFile(DS_DauSach DSDS);
void WriteDSMuonTra(std::fstream &FileMuonTra, NodeTheDocGia *thedocgia);
void WriteDG(std::fstream &FileDocGia, std::fstream &FileMuonTra, NodeTheDocGia *&TreeAVLDocGia);
void WriteDataDocGiaToFile(NodeTheDocGia *&TreeAVLDocGia);

// -------------------- Event ----------------- //
//Menu
void MenuEvent();
//Dau Sach
void SearchDauSachEvent();
void DauSachEvent();
void XemDauSachEvent();
void ThemDMSEvent();
void ThemSachEvent();
void XoaDMSEvent();
void SuaDMSEvent();
void ThemDauSachEvent();
void XoaDauSachEvent();
void SuaDauSachEvent();
//Doc Gia
void DocGiaEvent();
void XemDocGiaEvent();
void MuonSachEvent();
void ThemDocGiaEvent();
void XoaDocGiaEvent();
void SuaDocGiaEvent();
//Thong Ke
void ThongKeEvent();
// Thong Tin
void ThongTinEvent();

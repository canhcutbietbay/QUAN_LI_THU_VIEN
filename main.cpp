#include <graphics.h>
#include "Define.h"
#include "Button.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include "time.h"
#include "StructDanhMucSach.h"
#include "StructDauSach.h"
#include "StructMuonTra.h"
#include "StructTheDocGia.h"

using namespace std;
/* MenuId
	99 - Them Sach
*/
int CurrentMenuId = 0, LastCurrenMenuID = 0;
const int X_DS = w / 10, Y_DS = h / 7;
const int XDS[7] = {10, X_DS * 1.5, X_DS * 4, X_DS * 7, X_DS * 8.5, X_DS * 9.5, X_DS * 10 - 10};
const int XDMS[] = {10, X_DS * 4, X_DS * 7, X_DS * 10 - 10};
const int XDG[] = {10, X_DS * 2, X_DS * 4, X_DS * 6, X_DS * 8, X_DS * 10 - 10};
const int XXDG[] = {10, X_DS * 2, X_DS * 4.5, X_DS * 7, X_DS * 8.5, X_DS * 10 - 10};
const int XQH[] = {10, X_DS * 1.5, X_DS * 3.5, X_DS * 5, X_DS * 7.5, X_DS * 9, X_DS * 10 - 10};
const int XT10[] = {10, X_DS * 4, X_DS * 7, X_DS * 10 - 10};

int mouseX = 0, mouseY = 0;
bool isExit = 0;

const int ContentHeight = (Y_DS * 5 - Y_DS - 50) / 10;
int CurrentItem = -1, SubCurrentItem = -1, CurrentAddDMS = -1, TotalAddDMS = -1;

int ButtonHeight = 60, ButtonWidth = 300, ButtonSpace = 80, ButtonY = 200;
Button ButtonDauSach(100, w / 2 - ButtonWidth / 2, ButtonY + ButtonSpace, ButtonWidth, ButtonHeight, "QUAN LY DAU SACH", 0);
Button ButtonDocGia(200, w / 2 - ButtonWidth / 2, ButtonY + 2 * ButtonSpace, ButtonWidth, ButtonHeight, "QUAN LY DOC GIA", 0);
Button ButtonThongKe(300, w / 2 - ButtonWidth / 2, ButtonY + 3 * ButtonSpace, ButtonWidth, ButtonHeight, "THONG KE", 0);
Button ButtonThongTin(400, w / 2 - ButtonWidth / 2, ButtonY + 4 * ButtonSpace, ButtonWidth, ButtonHeight, "THONG TIN", 0);
Button ButtonThoat(500, w / 2 - ButtonWidth / 2, ButtonY + 5 * ButtonSpace, ButtonWidth, ButtonHeight, "THOAT", 0);

int DefaultButtonHeight = 50, DefaultButtonWidth = 100;
DM_Sach *SachTemp;
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
EditButton ButtonThemSoLuong(132, w / 2 - w / 6 + 10, h / 2 - 100, w / 3 - 20, DefaultButtonHeight, "SO LUONG", "", "NHAP VAO SO LUONG");
EditButton ButtonThemMaSach(133, w / 2 - w / 6 + 10, h / 3 + 30 + DefaultButtonHeight * 1, w / 3 - 20, DefaultButtonHeight, "MA SACH", "", "NHAP VAO MA SACH");
EditButton ButtonThemTrangThaiSach(134, w / 2 - w / 6 + 10, h / 3 + 40 + DefaultButtonHeight * 2, w / 3 - 20, DefaultButtonHeight, "TRANG THAI", "", "NHAP VAO TRANG THAI");
EditButton ButtonThemViTriSach(135, w / 2 - w / 6 + 10, h / 3 + 50 + DefaultButtonHeight * 3, w / 3 - 20, DefaultButtonHeight, "VI TRI", "", "NHAP VAO VI TRI");

// Button ButtonDongYSua(123, w / 3 + w / 9 - DefaultButtonWidth / 2, h / 2 - h / 4 + 200 + DefaultButtonHeight * 6, DefaultButtonWidth, DefaultButtonHeight, "DONG Y", 0);
// Button ButtonHuyBoSua(124, w / 3 + w / 6 + DefaultButtonWidth / 2, h / 2 - h / 4 + 200 + DefaultButtonHeight * 6, DefaultButtonWidth, DefaultButtonHeight, "HUY BO", 0);

DS_DauSach DSDS; // global
DS_DauSach ListSearchDauSach;
DS_DMS DSDMS;
DS_MT DSMT;
DS_QuaHan DSQH;
// Doc Gia
Button ButtonDocGiaHoTen(201, w / 2 - DefaultButtonWidth - 10, Y_DS - 75, DefaultButtonWidth, DefaultButtonHeight, "HO TEN", 0);
Button ButtonDocGiaMaThe(202, w / 2 + 10, Y_DS - 75, DefaultButtonWidth, DefaultButtonHeight, "MA THE", 0);
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
void InDanhSachDauSach(DS_DauSach &DSDS);
void InDMS();
void InMuonTra(NodeTheDocGia *&TreeAVLDocGia);

string GetNumberFromMaSach(string MaSach)
{

	string res = MaSach.substr(MaSach.length() - 2, 2);
	return res;
}

int FindPosBookName(char maSach[15])
{
	for (int i = 0; i < DSDS.n; ++i)
	{
		int k = 0;
		while (maSach[k] == DSDS.nodes[i]->ISBN[k])
			if (maSach[k + 1] == '-')
				return i;
			else
				k++;
	}
	return false;
}

void GetDataDauSachFromFile(DS_DauSach &DSDS)
{
	fstream FileDauSach, FileDanhMucSach;
	FileDauSach.open("data_dausach.txt", ios::in);
	FileDanhMucSach.open("data_danhmucsach.txt", ios::in);
	if (!FileDauSach.is_open())
	{
		printf("Loi mo File de doc \n");
		return;
	}
	string data;
	int n;
	FileDauSach >> n;
	FileDauSach.ignore();
	for (int i = 0; i < n; i++)
	{
		DauSach *dauSach = new DauSach;
		getline(FileDauSach, data);
		strcpy(dauSach->ISBN, data.c_str());
		getline(FileDauSach, data);
		strcpy(dauSach->TenSach, data.c_str());
		getline(FileDauSach, data);
		dauSach->SoTrang = atoi(data.c_str());
		getline(FileDauSach, data);
		strcpy(dauSach->TacGia, data.c_str());
		getline(FileDauSach, data);
		dauSach->NXB = atoi(data.c_str());
		getline(FileDauSach, data);
		strcpy(dauSach->TheLoai, data.c_str());
		FileDanhMucSach >> dauSach->TongSoLuong;
		FileDanhMucSach.ignore();
		DM_Sach *DMS = nullptr;
		for (int j = 0; j < dauSach->TongSoLuong; ++j)
		{
			Sach *sach = new Sach;
			getline(FileDanhMucSach, data);
			sach->id = atoi(GetNumberFromMaSach(data).c_str());
			strcpy(sach->MaSach, data.c_str());
			getline(FileDanhMucSach, data);
			sach->TrangThai = atoi(data.c_str());
			getline(FileDanhMucSach, data);
			strcpy(sach->ViTri, data.c_str());
			InsertLast_DM_Sach(DMS, sach);
		}
		dauSach->DS_Sach = DMS;
		InsertLastDauSach(DSDS, dauSach);
	}
	FileDauSach.close();
	FileDanhMucSach.close();
}

NodeTheDocGia *TreeAVLDocGia;
DS_DocGia DSDG;
void GetDataDocGiaFromFile(NodeTheDocGia *&TreeAVLDocGia)
{
	fstream FileDocGia, FileMuonTra;
	FileDocGia.open("data_docgia.txt", ios::in);
	if (!FileDocGia.is_open())
	{
		printf("Loi mo File de doc \n");
		return;
	}
	FileMuonTra.open("data_muontra.txt", ios::in);
	if (!FileMuonTra.is_open())
	{
		printf("Loi mo File de doc \n");
		return;
	}
	string data;
	int n, temp;
	FileDocGia >> n;
	FileDocGia.ignore();
	for (int i = 0; i < n; i++)
	{
		TheDocGia theDocGia;
		getline(FileDocGia, data);
		theDocGia.MaThe = atoi(data.c_str());
		ArrMTfromFile(mathe, theDocGia.MaThe);
		getline(FileDocGia, data);
		strcpy(theDocGia.Ho, data.c_str());
		getline(FileDocGia, data);
		strcpy(theDocGia.Ten, data.c_str());
		getline(FileDocGia, data);
		theDocGia.Phai = atoi(data.c_str());
		getline(FileDocGia, data);
		theDocGia.TrangThai = atoi(data.c_str());
		FileMuonTra >> theDocGia.TongSoLuong;
		FileMuonTra.ignore();
		DS_MuonTra *DSMT = new DS_MuonTra;
		for (int j = 0; j < theDocGia.TongSoLuong; ++j)
		{
			MuonTra *node = new MuonTra;
			getline(FileMuonTra, data);
			strcpy(node->MaSach, data.c_str());
			getline(FileMuonTra, data);
			node->TrangThai = atoi(data.c_str());
			getline(FileMuonTra, data);
			node->NgayMuon.Day = atoi(data.substr(0, 2).c_str());
			node->NgayMuon.Month = atoi(data.substr(3, 2).c_str());
			node->NgayMuon.Year = atoi(data.substr(6, 4).c_str());
			getline(FileMuonTra, data);
			if (data != "0")
			{
				node->NgayTra.Day = atoi(data.substr(0, 2).c_str());
				node->NgayTra.Month = atoi(data.substr(3, 2).c_str());
				node->NgayTra.Year = atoi(data.substr(6, 4).c_str());
			}
			else
			{
				node->NgayTra.Day = 0;
				node->NgayTra.Month = 0;
				node->NgayTra.Year = 0;
			}
			node->NgayMuon.GetRes();
			node->NgayTra.GetRes();
			InsertLast_DM_MuonTra(DSMT, node);
		}
		theDocGia.DS_MT = DSMT;
		TreeAVLDocGia = InsertDocGia(TreeAVLDocGia, theDocGia);
	}
	FileDocGia.close();
	FileMuonTra.close();
}
void GetDataFromFile()
{
	GetDataDauSachFromFile(DSDS);
	GetDataDocGiaFromFile(TreeAVLDocGia);
}

void ButtonEffect(Button &Button)
{
	if (Button.isMouseHover(mousex(), mousey()))
	{
		if (Button.IsHover == false)
		{
			Button.IsHover = true;
			Button.draw();
		}
	}
	else
	{
		if (Button.IsHover == true)
		{
			Button.IsHover = false;
			Button.draw();
		}
	}
}

void ClearScreen()
{
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(0, 0, w, h);
}

void ClearScreenXY(int x, int y, int z, int t)
{
	setfillstyle(SOLID_FILL, BG_COLOR);
	bar(x, y, z, t);
}

void ThongBao(char Data[], int width = 400, int height = 150, int NextMenu = -1)
{
	ClearScreenXY(w / 2 - width / 2, h / 2 - height / 2, w / 2 + width / 2, h / 2 + height / 2);
	setcolor(YELLOW);
	rectangle(w / 2 - width / 2, h / 2 - height / 2, w / 2 + width / 2, h / 2 + height / 2);
	outtextxy(w / 2 - textwidth("THONG BAO") / 2, h / 2 - height / 2 + 10, "THONG BAO");
	setcolor(WHITE);
	outtextxy(w / 2 - textwidth(Data) / 2, h / 2 - height / 2 + 20 + textheight("A"), Data);
	ButtonOKThongBao.Init(999, w / 2 - DefaultButtonWidth / 2, h / 2 + height / 2 - DefaultButtonHeight - 10, DefaultButtonWidth, DefaultButtonHeight, "OK", 0);
	ButtonOKThongBao.draw();
	LastCurrenMenuID = (NextMenu == -1) ? CurrentMenuId : NextMenu;
	// LastCurrenMenuID = CurrentMenuId;
	CurrentMenuId = ButtonOKThongBao.ID;
}

char AppTitle[50] = "QUAN LY THU VIEN";
char NumOfPage[10] = "";
int CurrentPage = 1, TotalPage = 0;
int SubCurrentPage = 1;
void DrawMenu()
{
	ClearScreen();
	CurrentItem = -1;
	CurrentPage = 1;
	settextstyle(BOLD_FONT, HORIZ_DIR, 7);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy(w / 2 - textwidth(AppTitle) / 2, 100, AppTitle);
	ButtonDauSach.draw();
	ButtonDocGia.draw();
	ButtonThongKe.draw();
	ButtonThongTin.draw();
	ButtonThoat.draw();
}
void RunDauSach();
void RunThemDauSach();
void RunXemDauSach();
void RunXoaDauSach();
void RunSuaDauSach();
void RunDocGia();
void RunXemDocGia();
void RunMuonSach();
void RunThemDMS();
void RunThemSach();
void RunThemDocGia();
void RunXoaDocGia();
void RunSuaDocGia();
void RunThongKe();
void RunQuaHan();
void RunTop10();
void RunThongTin();
void SetMenuSelect(int MenuID)
{
	if (CurrentMenuId != MenuID)
		CurrentMenuId = MenuID;
	if (CurrentMenuId == 0)
		DrawMenu();
	else if (MenuID == ButtonDauSach.ID)
		RunDauSach();
	else if (MenuID == ButtonThemDauSach.ID)
		RunThemDauSach();
	else if (MenuID == ButtonXemDauSach.ID)
		RunXemDauSach();
	else if (MenuID == 99)
		RunThemSach();
	else if (MenuID == ButtonThemDMS.ID)
		RunThemDMS();
	else if (MenuID == ButtonXoaDauSach.ID)
		RunXoaDauSach();
	else if (MenuID == ButtonSuaDauSach.ID)
		RunSuaDauSach();
	else if (MenuID == ButtonDocGia.ID)
		RunDocGia();
	else if (MenuID == ButtonXemDocGia.ID)
		RunXemDocGia();
	else if (MenuID == ButtonMuonSach.ID)
		RunMuonSach();
	else if (MenuID == ButtonThemDocGia.ID)
		RunThemDocGia();
	else if (MenuID == ButtonXoaDocGia.ID)
		RunXoaDocGia();
	else if (MenuID == ButtonSuaDocGia.ID)
		RunSuaDocGia();
	else if (MenuID == ButtonThongKe.ID)
		RunThongKe();
	else if (MenuID == ButtonThongTin.ID)
		RunThongTin();
}

void DrawSelecteItemDauSach(DS_DauSach DSDS)
{
	if (CurrentItem > 0 && (ceil(CurrentItem * 1.0 / 10) == CurrentPage))
	{
		char data[15];
		// Clear text
		ClearScreenXY(XDS[0] + 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2) - 10, XDS[1] - 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 + textheight("A") / 2) + 10);
		ClearScreenXY(XDS[1] + 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2) - 10, XDS[2] - 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 + textheight("A") / 2) + 10);
		ClearScreenXY(XDS[2] + 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2) - 10, XDS[3] - 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 + textheight("A") / 2) + 10);
		ClearScreenXY(XDS[3] + 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2) - 10, XDS[4] - 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 + textheight("A") / 2) + 10);
		ClearScreenXY(XDS[4] + 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2) - 10, XDS[5] - 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 + textheight("A") / 2) + 10);
		ClearScreenXY(XDS[5] + 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2) - 10, XDS[6] - 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 + textheight("A") / 2) + 10);
		// Fill with color
		setfillstyle(SOLID_FILL, BG_BUTTON_SELECT);
		floodfill(XDS[0] + 1, Y_DS + 50 + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)), WHITE);
		floodfill(XDS[1] + 1, Y_DS + 50 + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)), WHITE);
		floodfill(XDS[2] + 1, Y_DS + 50 + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)), WHITE);
		floodfill(XDS[3] + 1, Y_DS + 50 + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)), WHITE);
		floodfill(XDS[4] + 1, Y_DS + 50 + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)), WHITE);
		floodfill(XDS[5] + 1, Y_DS + 50 + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)), WHITE);
		// Draw selected item
		setbkcolor(BG_BUTTON_SELECT);
		outtextxy(XDS[0] + 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSDS.nodes[CurrentItem - 1]->ISBN);
		outtextxy(XDS[1] + 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSDS.nodes[CurrentItem - 1]->TenSach);
		outtextxy(XDS[2] + 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSDS.nodes[CurrentItem - 1]->TacGia);
		outtextxy(XDS[3] + 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSDS.nodes[CurrentItem - 1]->TheLoai);
		itoa(DSDS.nodes[CurrentItem - 1]->SoTrang, data, 10);
		outtextxy(XDS[4] + (XDS[5] - XDS[4]) / 2 - textwidth(data) / 2, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), data);
		itoa(DSDS.nodes[CurrentItem - 1]->NXB, data, 10);
		outtextxy(XDS[5] + (XDS[6] - XDS[5]) / 2 - textwidth(data) / 2, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), data);
	}
}

void DrawItemDauSach(DS_DauSach DSDS)
{
	char data[15];
	if (DSDS.n == 0)
		return;
	for (int i = 1 + 10 * (CurrentPage - 1); i <= 10 + 10 * (CurrentPage - 1); i++)
	{
		if (i > DSDS.n)
			break;
		line(XDS[0], (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1) + 1)), XDS[6], (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1) + 1)));
		outtextxy(XDS[0] + 10, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSDS.nodes[i - 1]->ISBN);
		outtextxy(XDS[1] + 10, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSDS.nodes[i - 1]->TenSach);
		outtextxy(XDS[2] + 10, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSDS.nodes[i - 1]->TacGia);
		outtextxy(XDS[3] + 10, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSDS.nodes[i - 1]->TheLoai);
		itoa(DSDS.nodes[i - 1]->SoTrang, data, 10);
		outtextxy(XDS[4] + (XDS[5] - XDS[4]) / 2 - textwidth(data) / 2, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), data);
		itoa(DSDS.nodes[i - 1]->NXB, data, 10);
		outtextxy(XDS[5] + (XDS[6] - XDS[5]) / 2 - textwidth(data) / 2, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), data);
	}
	memset(NumOfPage, 0, sizeof NumOfPage);
	string temp;
	TotalPage = ceil(DSDS.n * 1.0 / 10);
	if (TotalPage == 0)
		TotalPage = 1;
	temp = to_string(CurrentPage);
	strcat(NumOfPage, temp.c_str());
	strcat(NumOfPage, "/");
	temp = to_string(TotalPage);
	strcat(NumOfPage, temp.c_str());
	outtextxy(w / 2 - textwidth(NumOfPage) / 2, Y_DS * 5 + 10, NumOfPage);
}

void SearchDauSach(char TenSach[])
{
	ListSearchDauSach.n = 0;
	CurrentItem = -1;
	string temp;
	for (int i = 0; i < DSDS.n; ++i)
	{
		temp = DSDS.nodes[i]->TenSach;
		if (temp.find(TenSach) != string::npos)
			ThemDauSach(ListSearchDauSach, DSDS.nodes[i]);
	}
}

void DrawItemQuaHan(DS_QuaHan DSQH)
{
	char data[15];
	if (DSQH.n == 0)
		return;
	for (int i = 1 + 10 * (CurrentPage - 1); i <= 10 + 10 * (CurrentPage - 1); i++)
	{
		if (i > DSQH.n)
			break;
		line(XQH[0], (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1) + 1)), XQH[6], (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1) + 1)));
		itoa(DSQH.nodes[i - 1]->MaThe, data, 10);
		outtextxy(XQH[0] + (XQH[1] - XQH[0]) / 2 - textwidth(data) / 2, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), data);
		outtextxy(XQH[1] + 10, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSQH.nodes[i - 1]->HoTen);
		outtextxy(XQH[2] + 10, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSQH.nodes[i - 1]->MaSach);
		outtextxy(XQH[3] + 10, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSQH.nodes[i - 1]->TenSach);
		outtextxy(XQH[4] + (XQH[5] - XQH[4]) / 2 - textwidth(DSQH.nodes[i - 1]->NgayMuon.res) / 2, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSQH.nodes[i - 1]->NgayMuon.res);
		itoa(DSQH.nodes[i - 1]->SoNgayQuaHan, data, 10);
		outtextxy(XQH[5] + (XQH[6] - XQH[5]) / 2 - textwidth(data) / 2, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), data);
	}
}

void RunQuaHan()
{
	ClearScreen();
	ButtonBack.draw();
	ButtonPrev.draw();
	ButtonNext.draw();
	ButtonThongKeQuaHan.draw();
	ButtonThongKeTop10.draw();
	char Title[][25] = {"MA THE", "HO TEN", "MA SACH", "TEN SACH", "NGAY MUON", "SO NGAY QH"};
	setcolor(WHITE);
	// Ve khung + title
	char title[] = "THONG KE";
	outtextxy(w / 2 - textwidth(title) / 2, textheight("A") - 10, title);
	rectangle(XQH[0], Y_DS, XQH[6], Y_DS * 5);
	line(XQH[0], Y_DS + 50, XQH[6], Y_DS + 50);
	for (int i = 0; i < 6; i++)
	{
		line(XQH[i + 1], Y_DS, XQH[i + 1], Y_DS * 5);
		outtextxy(XQH[i] + ((XQH[i + 1] - XQH[i]) / 2 - textwidth(Title[i]) / 2), (Y_DS + 25) - textheight("A") / 2, Title[i]);
	}
	DSQH.n = 0;
	GetFromTree(TreeAVLDocGia, DSQH, DSDS);
	DrawItemQuaHan(DSQH);
	memset(NumOfPage, 0, sizeof NumOfPage);
	string temp;
	TotalPage = ceil(DSQH.n * 1.0 / 10);
	if (TotalPage == 0)
		TotalPage = 1;
	temp = to_string(CurrentPage);
	strcat(NumOfPage, temp.c_str());
	strcat(NumOfPage, "/");
	temp = to_string(TotalPage);
	strcat(NumOfPage, temp.c_str());
	outtextxy(w / 2 - textwidth(NumOfPage) / 2, Y_DS * 5 + 10, NumOfPage);
}
void RunTop10()
{
	ClearScreen();
	ButtonBack.draw();
	ButtonPrev.draw();
	ButtonNext.draw();
	ButtonThongKeQuaHan.draw();
	ButtonThongKeTop10.draw();
	char Title[][25] = {"ISBN", "TEN SACH", "SO LUOT MUON"};
	setcolor(WHITE);
	// Ve khung + title
	char title[] = "THONG KE";
	outtextxy(w / 2 - textwidth(title) / 2, textheight("A") - 10, title);
	rectangle(XT10[0], Y_DS, XT10[3], Y_DS * 5);
	line(XT10[0], Y_DS + 50, XT10[3], Y_DS + 50);
	for (int i = 0; i < 3; i++)
	{
		line(XT10[i + 1], Y_DS, XT10[i + 1], Y_DS * 5);
		outtextxy(XT10[i] + ((XT10[i + 1] - XT10[i]) / 2 - textwidth(Title[i]) / 2), (Y_DS + 25) - textheight("A") / 2, Title[i]);
	}
}
void RunThongKe()
{
	if (ButtonThongKeTop10.IsHover == 0)
	{
		ButtonThongKeQuaHan.IsHover = true;
		ButtonThongKeQuaHan.IsChoose = 1;
		ButtonThongKeTop10.IsChoose = 0;
	}
	else
	{
		ButtonThongKeQuaHan.IsHover = false;
		ButtonThongKeQuaHan.IsChoose = 0;
		ButtonThongKeTop10.IsChoose = 1;
	}
	if (ButtonThongKeQuaHan.IsChoose)
		RunQuaHan();
	else
		RunTop10();
}
void RunThongTin()
{
	ClearScreen();
	ButtonBack.draw();
		// ve giao dien
	setcolor(YELLOW);	// chon mau chu
	settextstyle(BOLD_FONT, HORIZ_DIR, 3);		// chon font chu, huong ve chu (direction), size chu
	
	char uni[] = "Hoc vien Cong nghe Buu Chinh Vien Thong - TPHCM";
	char nam[] = "-- 2023 --";
	char title[] = "* Mon hoc : ";
	char title2[] = "Cau Truc Du Lieu & Giai Thuat";
	char gv[] = "* Giang vien : ";
	char gv2[] = "Luu Nguyen Ky Thu";
	char doan[] = "* Do An : ";
	char doan2[] = "Quan Ly Thu Vien";
	char sv[] = "* Sinh vien :";
	char author1[] = "1. Nguyen Tan Loc - N21DCCN049 - D21CQCN01-N";
	char author2[] = "2. Huynh Ngoc Tan - N21DCCN074 - D21CQCN01-N";
	
	settextstyle(BOLD_FONT, HORIZ_DIR, 5);
	outtextxy(w/2-textwidth(uni)/2, 50, uni);
	outtextxy(w/2-textwidth(nam)/2, h-250, nam);
	
	settextstyle(BOLD_FONT, HORIZ_DIR, 3);
	outtextxy(w/2-500, 200, title);
	outtextxy(w/2-500, 280, gv);
	outtextxy(w/2-500, 360, doan);
	outtextxy(w/2-500, 440, sv);
	
	outtextxy(w/2-250, 200, title2);
	outtextxy(w/2-250, 280, gv2);
	outtextxy(w/2-250, 360, doan2);
	
	outtextxy(w/2-250, 440, author1);
	outtextxy(w/2-250, 520, author2);
}
void RunDauSach()
{
	ClearScreen();
	ButtonBack.draw();
	ButtonPrev.draw();
	ButtonNext.draw();
	ButtonXemDauSach.draw();
	ButtonThemDauSach.draw();
	ButtonXoaDauSach.draw();
	ButtonSuaDauSach.draw();
	ButtonSearchDauSach.draw();
	ButtonClearSearchDauSach.draw();
	char Title[][25] = {"ISBN", "TEN SACH", "TAC GIA", "THE LOAI", "SO TRANG", "NXB"};
	setcolor(WHITE);
	// Ve khung + title
	outtextxy(w / 2 - textwidth("DAU SACH") / 2, textheight("A") - 10, "DAU SACH");
	rectangle(XDS[0], Y_DS, XDS[6], Y_DS * 5);
	line(XDS[0], Y_DS + 50, XDS[6], Y_DS + 50);
	for (int i = 0; i < 6; i++)
	{
		line(XDS[i + 1], Y_DS, XDS[i + 1], Y_DS * 5);
		outtextxy(XDS[i] + ((XDS[i + 1] - XDS[i]) / 2 - textwidth(Title[i]) / 2), (Y_DS + 25) - textheight("A") / 2, Title[i]);
	}
	if (strlen(ButtonSearchDauSach.UserInput) != 0)
	{
		DrawItemDauSach(ListSearchDauSach);
		DrawSelecteItemDauSach(ListSearchDauSach);
	}
	else
	{
		DrawItemDauSach(DSDS);
		DrawSelecteItemDauSach(DSDS);
	}
}
void RunThemDMS()
{
	CurrentAddDMS = 1;
	TotalAddDMS = -1;
	const int width = w / 3, height = h / 8;
	char Title[50] = "THEM SACH";
	ClearScreenXY(w / 2 - width / 2, h / 3 - height / 2, w / 2 + width / 2, h * 2 / 3 + height / 2);
	setcolor(WHITE);
	rectangle(w / 2 - width / 2, h / 3 - height / 2, w / 2 + width / 2, h * 2 / 3 + height / 2);
	settextstyle(BOLD_FONT, HORIZ_DIR, 5);
	setcolor(TEXT_TITLE_COLOR);
	// outtextxy(w / 2 - width / 2 + textwidth(Title) / 4, h / 3 - height / 2 + 10, Title);
	outtextxy(w / 2 - textwidth(Title) / 2, h / 3 - height / 2 + 10, Title);
	ButtonThemSoLuong.draw();
	ButtonDongY.Init(0, w / 3 + w / 9 - DefaultButtonWidth / 2, h / 2 - h / 4 + 160 + DefaultButtonHeight * 6, DefaultButtonWidth, DefaultButtonHeight, "DONG Y", 0);
	ButtonHuyBo.Init(0, w / 3 + w / 6 + DefaultButtonWidth / 2, h / 2 - h / 4 + 160 + DefaultButtonHeight * 6, DefaultButtonWidth, DefaultButtonHeight, "HUY BO", 0);
	ButtonDongY.draw();
	ButtonHuyBo.draw();
}

void RunThemSach()
{
	const int width = w / 3, height = h / 8;
	char Title[50] = "THEM SACH";
	ClearScreenXY(w / 2 - width / 2, h / 3 - height / 2, w / 2 + width / 2, h * 2 / 3 + height / 2);
	setcolor(WHITE);
	rectangle(w / 2 - width / 2, h / 3 - height / 2, w / 2 + width / 2, h * 2 / 3 + height / 2);
	settextstyle(BOLD_FONT, HORIZ_DIR, 5);
	setcolor(TEXT_TITLE_COLOR);
	char NumPerTotal[10], data[10];
	memset(NumPerTotal, 0, sizeof NumPerTotal);
	char *maSach = CreateMaSach(DSDS.nodes[CurrentItem - 1]);
	itoa(CurrentAddDMS, data, 10);
	strcat(NumPerTotal, data);
	strcat(NumPerTotal, "/");
	itoa(TotalAddDMS, data, 10);
	strcat(NumPerTotal, data);
	outtextxy(w / 2 - textwidth(Title) / 2, h / 3 - height / 2 + 10, Title);
	outtextxy(w / 2 - textwidth(NumPerTotal) / 2, h / 2 - h / 4 + 100 + DefaultButtonHeight * 6, NumPerTotal);
	strcpy(ButtonThemMaSach.UserInput, maSach);
	strcpy(ButtonThemTrangThaiSach.UserInput, "CHO MUON DUOC");
	ButtonThemMaSach.draw();
	ButtonThemTrangThaiSach.draw();
	ButtonThemViTriSach.draw();
	ButtonDongY.Init(0, w / 3 + w / 9 - DefaultButtonWidth / 2, h / 2 - h / 4 + 160 + DefaultButtonHeight * 6, DefaultButtonWidth, DefaultButtonHeight, "DONG Y", 0);
	ButtonHuyBo.Init(0, w / 3 + w / 6 + DefaultButtonWidth / 2, h / 2 - h / 4 + 160 + DefaultButtonHeight * 6, DefaultButtonWidth, DefaultButtonHeight, "HUY BO", 0);
	ButtonDongY.draw();
	ButtonHuyBo.draw();
}
void DrawSelecteItemDocGia(DS_DocGia DSDG)
{
	if (CurrentItem > 0 && (ceil(CurrentItem * 1.0 / 10) == CurrentPage))
	{
		char data[15];
		char Phai[][15] = {"NAM", "NU"};
		char TrangThai[][15] = {"KHOA", "HOAT DONG"};
		// Clear text
		ClearScreenXY(XDG[0] + 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2) - 10, XDG[1] - 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 + textheight("A") / 2) + 10);
		ClearScreenXY(XDG[1] + 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2) - 10, XDG[2] - 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 + textheight("A") / 2) + 10);
		ClearScreenXY(XDG[2] + 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2) - 10, XDG[3] - 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 + textheight("A") / 2) + 10);
		ClearScreenXY(XDG[3] + 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2) - 10, XDG[4] - 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 + textheight("A") / 2) + 10);
		ClearScreenXY(XDG[4] + 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2) - 10, XDG[5] - 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 + textheight("A") / 2) + 10);
		// Fill with color
		setfillstyle(SOLID_FILL, BG_BUTTON_SELECT);
		floodfill(XDG[0] + 1, Y_DS + 50 + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)), WHITE);
		floodfill(XDG[1] + 1, Y_DS + 50 + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)), WHITE);
		floodfill(XDG[2] + 1, Y_DS + 50 + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)), WHITE);
		floodfill(XDG[3] + 1, Y_DS + 50 + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)), WHITE);
		floodfill(XDG[4] + 1, Y_DS + 50 + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)), WHITE);
		// Draw selected item
		setbkcolor(BG_BUTTON_SELECT);
		itoa(DSDG.nodes[CurrentItem - 1]->MaThe, data, 10);
		outtextxy(XDG[0] + (XDG[1] - XDG[0]) / 2 - textwidth(data) / 2, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), data);
		outtextxy(XDG[1] + 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSDG.nodes[CurrentItem - 1]->Ho);
		outtextxy(XDG[2] + 10, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSDG.nodes[CurrentItem - 1]->Ten);
		outtextxy(XDG[3] + (XDG[4] - XDG[3]) / 2 - textwidth(Phai[DSDG.nodes[CurrentItem - 1]->Phai]) / 2, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), Phai[DSDG.nodes[CurrentItem - 1]->Phai]);
		outtextxy(XDG[4] + (XDG[5] - XDG[4]) / 2 - textwidth(TrangThai[DSDG.nodes[CurrentItem - 1]->TrangThai]) / 2, (Y_DS + ContentHeight * (CurrentItem - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), TrangThai[DSDG.nodes[CurrentItem - 1]->TrangThai]);
	}
}

void DrawItemDocGia(DS_DocGia DSDG)
{
	char data[15];
	char Phai[][15] = {"NAM", "NU"};
	char TrangThai[][15] = {"KHOA", "HOAT DONG"};
	if (DSDG.n == 0)
		return;
	for (int i = 1 + 10 * (CurrentPage - 1); i <= 10 + 10 * (CurrentPage - 1); i++)
	{
		if (i > DSDG.n)
			break;
		line(XDG[0], (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1) + 1)), XDG[5], (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1) + 1)));
		itoa(DSDG.nodes[i - 1]->MaThe, data, 10);
		outtextxy(XDG[0] + (XDG[1] - XDG[0]) / 2 - textwidth(data) / 2, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), data);
		outtextxy(XDG[1] + 10, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSDG.nodes[i - 1]->Ho);
		outtextxy(XDG[2] + 10, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSDG.nodes[i - 1]->Ten);
		outtextxy(XDG[3] + (XDG[4] - XDG[3]) / 2 - textwidth(Phai[DSDG.nodes[i - 1]->Phai]) / 2, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), Phai[DSDG.nodes[i - 1]->Phai]);
		outtextxy(XDG[4] + (XDG[5] - XDG[4]) / 2 - textwidth(TrangThai[DSDG.nodes[i - 1]->TrangThai]) / 2, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), TrangThai[DSDG.nodes[i - 1]->TrangThai]);
	}
	memset(NumOfPage, 0, sizeof NumOfPage);
	string temp;
	TotalPage = ceil(DSDG.n * 1.0 / 10);
	if (TotalPage == 0)
		TotalPage = 1;
	temp = to_string(CurrentPage);
	strcat(NumOfPage, temp.c_str());
	strcat(NumOfPage, "/");
	temp = to_string(TotalPage);
	strcat(NumOfPage, temp.c_str());
	outtextxy(w / 2 - textwidth(NumOfPage) / 2, Y_DS * 5 + 10, NumOfPage);
	// if (CurrentPage > TotalPage)
	// {
	// 	while (CurrentPage > TotalPage)
	// 		CurrentPage--;
	// 	RunDocGia();
	// }
}
void RunDocGia()
{
	ClearScreen();
	if (ButtonDocGiaHoTen.IsHover == 0)
	{
		ButtonDocGiaMaThe.IsHover = true;
		ButtonDocGiaMaThe.IsChoose = 1;
		ButtonDocGiaHoTen.IsChoose = 0;
	}
	else
	{
		ButtonDocGiaMaThe.IsHover = false;
		ButtonDocGiaMaThe.IsChoose = 0;
		ButtonDocGiaHoTen.IsChoose = 1;
	}
	DSDG.n = 0;
	GetFromTree(TreeAVLDocGia, DSDG);
	ButtonDocGiaHoTen.draw();
	ButtonDocGiaMaThe.draw();
	ButtonBack.draw();
	ButtonPrev.draw();
	ButtonNext.draw();
	ButtonXemDocGia.draw();
	ButtonThemDocGia.draw();
	ButtonXoaDocGia.draw();
	ButtonSuaDocGia.draw();
	//	ButtonSearchDocGia.draw();
	char Title[][25] = {"MA THE", "HO", "TEN", "PHAI", "TRANG THAI"};
	setcolor(WHITE);
	// Ve khung + title
	outtextxy(w / 2 - textwidth("DANH SACH DOC GIA") / 2, textheight("A") - 10, "DANH SACH DOC GIA");
	rectangle(XDG[0], Y_DS, XDG[5], Y_DS * 5);
	line(XDG[0], Y_DS + 50, XDG[5], Y_DS + 50);
	for (int i = 0; i < 5; i++)
	{
		line(XDG[i + 1], Y_DS, XDG[i + 1], Y_DS * 5);
		outtextxy(XDG[i] + ((XDG[i + 1] - XDG[i]) / 2 - textwidth(Title[i]) / 2), (Y_DS + 25) - textheight("A") / 2, Title[i]);
	}
	if (ButtonDocGiaHoTen.IsChoose)
		DSDG.SortDocGia(0, DSDG.n - 1, 1);
	else
		DSDG.SortDocGia(0, DSDG.n - 1);
	DrawItemDocGia(DSDG);		 // Ve item
	DrawSelecteItemDocGia(DSDG); // Ve selected item
}

void DrawItemMuonTra(DS_MT DSMT)
{
	char TrangThai[][25] = {"DANG MUON", "DA TRA", "LAM MAT SACH"};
	if (DSMT.n == 0)
		return;
	for (int i = 1 + 10 * (SubCurrentPage - 1); i <= 10 + 10 * (SubCurrentPage - 1); i++)
	{
		if (i > DSMT.n)
			break;
		line(XXDG[0], (Y_DS + ContentHeight * (i - 10 * (SubCurrentPage - 1) + 1)), XXDG[5], (Y_DS + ContentHeight * (i - 10 * (SubCurrentPage - 1) + 1)));
		outtextxy(XXDG[0] + (XXDG[1] - XXDG[0]) / 2 - textwidth(DSMT.nodes[i - 1]->MaSach) / 2, (Y_DS + ContentHeight * (i - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSMT.nodes[i - 1]->MaSach);
		outtextxy(XXDG[1] + 10, (Y_DS + ContentHeight * (i - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSDS.nodes[FindPosBookName(DSMT.nodes[i - 1]->MaSach)]->TenSach);
		outtextxy(XXDG[2] + (XXDG[3] - XXDG[2]) / 2 - textwidth(TrangThai[DSMT.nodes[i - 1]->TrangThai]) / 2, (Y_DS + ContentHeight * (i - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), TrangThai[DSMT.nodes[i - 1]->TrangThai]);
		outtextxy(XXDG[3] + (XXDG[4] - XXDG[3]) / 2 - textwidth(DSMT.nodes[i - 1]->NgayMuon.res) / 2, (Y_DS + ContentHeight * (i - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSMT.nodes[i - 1]->NgayMuon.res);
		outtextxy(XXDG[4] + (XXDG[5] - XXDG[4]) / 2 - textwidth(DSMT.nodes[i - 1]->NgayTra.res) / 2, (Y_DS + ContentHeight * (i - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSMT.nodes[i - 1]->NgayTra.res);
	}
}
void DrawSelectedItemMuonTra(DS_MT DSMT)
{
	if (SubCurrentItem > 0 && (ceil(SubCurrentItem * 1.0 / 10) == SubCurrentPage))
	{
		char TrangThai[][25] = {"DANG MUON", "DA TRA", "LAM MAT SACH"};
		// Clear text
		ClearScreenXY(XXDG[0] + 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2) - 10, XXDG[1] - 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 + textheight("A") / 2) + 10);
		ClearScreenXY(XXDG[1] + 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2) - 10, XXDG[2] - 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 + textheight("A") / 2) + 10);
		ClearScreenXY(XXDG[2] + 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2) - 10, XXDG[3] - 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 + textheight("A") / 2) + 10);
		ClearScreenXY(XXDG[3] + 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2) - 10, XXDG[3] - 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 + textheight("A") / 2) + 10);
		ClearScreenXY(XXDG[4] + 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2) - 10, XXDG[3] - 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 + textheight("A") / 2) + 10);
		// Fill with color
		setfillstyle(SOLID_FILL, BG_BUTTON_SELECT);
		floodfill(XXDG[0] + 1, Y_DS + 50 + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)), WHITE);
		floodfill(XXDG[1] + 1, Y_DS + 50 + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)), WHITE);
		floodfill(XXDG[2] + 1, Y_DS + 50 + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)), WHITE);
		floodfill(XXDG[3] + 1, Y_DS + 50 + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)), WHITE);
		floodfill(XXDG[4] + 1, Y_DS + 50 + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)), WHITE);
		// Draw selected item
		setbkcolor(BG_BUTTON_SELECT);
		outtextxy(XXDG[0] + (XXDG[1] - XXDG[0]) / 2 - textwidth(DSMT.nodes[SubCurrentItem - 1]->MaSach) / 2, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSMT.nodes[SubCurrentItem - 1]->MaSach);
		outtextxy(XXDG[1] + 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSDS.nodes[FindPosBookName(DSMT.nodes[SubCurrentItem - 1]->MaSach)]->TenSach);
		outtextxy(XXDG[2] + (XXDG[3] - XXDG[2]) / 2 - textwidth(TrangThai[DSMT.nodes[SubCurrentItem - 1]->TrangThai]) / 2, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), TrangThai[DSMT.nodes[SubCurrentItem - 1]->TrangThai]);
		outtextxy(XXDG[3] + (XXDG[4] - XXDG[3]) / 2 - textwidth(DSMT.nodes[SubCurrentItem - 1]->NgayMuon.res) / 2, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSMT.nodes[SubCurrentItem - 1]->NgayMuon.res);
		outtextxy(XXDG[4] + (XXDG[5] - XXDG[4]) / 2 - textwidth(DSMT.nodes[SubCurrentItem - 1]->NgayTra.res) / 2, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSMT.nodes[SubCurrentItem - 1]->NgayTra.res);
	}
}
void RunXemDocGia()
{
	ClearScreen();
	ButtonBack.draw();
	ButtonPrev.draw();
	ButtonNext.draw();
	ButtonMuonSach.draw();
	ButtonTraSach.draw();
	char Title[][25] = {"MA SACH", "TEN SACH", "TRANG THAI", "NGAY MUON", "NGAY TRA"};
	setcolor(WHITE);
	rectangle(XXDG[0], Y_DS, XXDG[5], Y_DS * 5);
	line(XXDG[0], Y_DS + 50, XXDG[5], Y_DS + 50);
	for (int i = 0; i < 5; i++)
	{
		line(XXDG[i + 1], Y_DS, XXDG[i + 1], Y_DS * 5);
		outtextxy(XXDG[i] + ((XXDG[i + 1] - XXDG[i]) / 2 - textwidth(Title[i]) / 2), (Y_DS + 25) - textheight("A") / 2, Title[i]);
	}
	char title[] = {"DOC GIA"}, MaThe[10];
	strcat(title, ": ");
	itoa(DSDG.nodes[CurrentItem - 1]->MaThe, MaThe, 10);
	strcat(title, MaThe);
	outtextxy(w / 2 - textwidth(title) / 2, textheight("A") - 10, title);
	GetMT(DSMT, DSDG.nodes[CurrentItem - 1]);
	memset(NumOfPage, 0, sizeof NumOfPage);
	string temp;
	TotalPage = ceil(DSMT.n * 1.0 / 10);
	if (TotalPage == 0)
		TotalPage = 1;
	temp = to_string(SubCurrentPage);
	strcat(NumOfPage, temp.c_str());
	strcat(NumOfPage, "/");
	temp = to_string(TotalPage);
	strcat(NumOfPage, temp.c_str());
	outtextxy(w / 2 - textwidth(NumOfPage) / 2, Y_DS * 5 + 10, NumOfPage);
	DrawItemMuonTra(DSMT);
	DrawSelectedItemMuonTra(DSMT);
}
void RunMuonSach()
{
	const int width = w / 3, height = 300;
	char Title[50] = "MUON SACH";
	ClearScreenXY(w / 2 - width / 2, h / 2 - height / 2, w / 2 + width / 2, h / 2 + height / 2);
	setcolor(WHITE);
	rectangle(w / 2 - width / 2, h / 2 - height / 2, w / 2 + width / 2, h / 2 + height / 2);
	settextstyle(BOLD_FONT, HORIZ_DIR, 5);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy(w / 2 - textwidth(Title) / 2, h / 2 - height / 2 + 10, Title);
	ButtonNhapMaSach.draw();
	ButtonDongY.Init(0, w / 2 - DefaultButtonWidth / 2 - w / 12, h / 2 + height / 2 - DefaultButtonHeight - 10, DefaultButtonWidth, DefaultButtonHeight, "DONG Y", 0);
	ButtonHuyBo.Init(0, w / 2 - DefaultButtonWidth / 2 + w / 12, h / 2 + height / 2 - DefaultButtonHeight - 10, DefaultButtonWidth, DefaultButtonHeight, "HUY BO", 0);
	ButtonDongY.draw();
	ButtonHuyBo.draw();
}
void RunThemDocGia()
{
	const int width = w / 3, height = h / 4;
	char Title[50] = "THEM DOC GIA";
	ClearScreenXY(w / 2 - width / 2, h / 3 - height / 2, w / 2 + width / 2, h * 2 / 3 + height / 2);
	setcolor(WHITE);
	rectangle(w / 2 - width / 2, h / 3 - height / 2, w / 2 + width / 2, h * 2 / 3 + height / 2);
	settextstyle(BOLD_FONT, HORIZ_DIR, 5);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy(w / 2 - textwidth(Title) / 2, h / 3 - height / 2 + 10, Title);
	// outtextxy(w / 2 - width / 2 , h / 3 - height / 2 + 10, Title);
	char MaThe[10];
	itoa(RanNewMT(mathe), MaThe, 10);
	strcpy(ButtonThemMaThe.UserInput, MaThe);
	ButtonThemMaThe.draw();
	ButtonThemHo.draw();
	ButtonThemTen.draw();
	ButtonThemPhai.draw();
	ButtonThemTrangThai.draw();
	ButtonThem.draw();
	ButtonClearData.draw();
}
void DrawItemDMS(DS_DMS &DSDMS)
{
	// Content
	char TrangThai[][20] = {"CHO MUON DUOC", "DA CO NGUOI MUON", "DA THANH LY"};
	if (DSDMS.n)
	{
		for (int i = 1 + 10 * (SubCurrentPage - 1); i <= 10 + 10 * (SubCurrentPage - 1); i++)
		{
			if (i > DSDMS.n)
				break;
			line(XDMS[0], (Y_DS + ContentHeight * (i - 10 * (SubCurrentPage - 1) + 1)), XDMS[3], (Y_DS + ContentHeight * (i - 10 * (SubCurrentPage - 1) + 1)));
			outtextxy(XDMS[0] + 10, (Y_DS + ContentHeight * (i - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSDMS.nodes[i - 1]->MaSach);
			outtextxy(XDMS[1] + 10, (Y_DS + ContentHeight * (i - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), TrangThai[DSDMS.nodes[i - 1]->TrangThai]);
			outtextxy(XDMS[2] + 10, (Y_DS + ContentHeight * (i - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSDMS.nodes[i - 1]->ViTri);
		}
	}
}
void DrawSelectedItemDMS(DS_DMS &DSDMS)
{
	if (SubCurrentItem > 0 && (ceil(SubCurrentItem * 1.0 / 10) == SubCurrentPage))
	{
		char TrangThai[][20] = {"CHO MUON DUOC", "DA CO NGUOI MUON", "DA THANH LY"};
		// Clear text
		ClearScreenXY(XDMS[0] + 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2) - 10, XDMS[1] - 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 + textheight("A") / 2) + 10);
		ClearScreenXY(XDMS[1] + 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2) - 10, XDMS[2] - 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 + textheight("A") / 2) + 10);
		ClearScreenXY(XDMS[2] + 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2) - 10, XDMS[3] - 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 + textheight("A") / 2) + 10);
		// Fill with color
		setfillstyle(SOLID_FILL, BG_BUTTON_SELECT);
		floodfill(XDMS[0] + 1, Y_DS + 50 + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)), WHITE);
		floodfill(XDMS[1] + 1, Y_DS + 50 + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)), WHITE);
		floodfill(XDMS[2] + 1, Y_DS + 50 + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)), WHITE);
		// Draw selected item
		setbkcolor(BG_BUTTON_SELECT);
		outtextxy(XDMS[0] + 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSDMS.nodes[SubCurrentItem - 1]->MaSach);
		outtextxy(XDMS[1] + 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), TrangThai[DSDMS.nodes[SubCurrentItem - 1]->TrangThai]);
		outtextxy(XDMS[2] + 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSDMS.nodes[SubCurrentItem - 1]->ViTri);
	}
}

void RunXemDauSach()
{
	DauSach *dauSach;
	if (strlen(ButtonSearchDauSach.UserInput) != 0)
		dauSach = ListSearchDauSach.nodes[CurrentItem - 1];
	else
		dauSach = DSDS.nodes[CurrentItem - 1];
	ClearScreen();
	ButtonBack.draw();
	ButtonPrev.draw();
	ButtonNext.draw();
	ButtonThemDMS.draw();
	ButtonXoaDMS.draw();
	ButtonSuaDMS.draw();
	char Title[][25] = {"TEN SACH", "TRANG THAI", "VI TRI"};
	setcolor(WHITE);
	rectangle(XDMS[0], Y_DS, XDMS[3], Y_DS * 5);
	line(XDMS[0], Y_DS + 50, XDMS[3], Y_DS + 50);
	// Ve Khung
	for (int i = 0; i < 3; i++)
	{
		line(XDMS[i + 1], Y_DS, XDMS[i + 1], Y_DS * 5);
		outtextxy(XDMS[i] + ((XDMS[i + 1] - XDMS[i]) / 2 - textwidth(Title[i]) / 2), (Y_DS + 25) - textheight("A") / 2, Title[i]);
	}
	// Title
	char title[] = {"DANH MUC SACH"};
	strcat(title, ": ");
	strcat(title, dauSach->TenSach);
	outtextxy(w / 2 - textwidth(title) / 2, textheight("A") - 10, title);
	GetDMS(DSDMS, dauSach); // Get DMS cua Dau Sach hien tai
	memset(NumOfPage, 0, sizeof NumOfPage);
	string temp;
	TotalPage = ceil(dauSach->TongSoLuong * 1.0 / 10);
	if (TotalPage == 0)
		TotalPage = 1;
	temp = to_string(SubCurrentPage);
	strcat(NumOfPage, temp.c_str());
	strcat(NumOfPage, "/");
	temp = to_string(TotalPage);
	strcat(NumOfPage, temp.c_str());
	outtextxy(w / 2 - textwidth(NumOfPage) / 2, Y_DS * 5 + 10, NumOfPage);
	DrawItemDMS(DSDMS);
	DrawSelectedItemDMS(DSDMS);
	// if (SubCurrentPage > TotalPage)
	// {
	// 	while (SubCurrentPage > TotalPage)
	// 		SubCurrentPage--;
	// 	RunXemDauSach();
	// }
}

void RunXoaDauSach()
{
	const int width = 500, height = 150;
	char Data[] = "DAU SACH SE DUOC XOA";
	ClearScreenXY(w / 2 - width / 2, h / 2 - height / 2, w / 2 + width / 2, h / 2 + height / 2);
	setcolor(YELLOW);
	rectangle(w / 2 - width / 2, h / 2 - height / 2, w / 2 + width / 2, h / 2 + height / 2);
	outtextxy(w / 2 - textwidth("THONG BAO") / 2, h / 2 - height / 2 + 10, "THONG BAO");
	setcolor(WHITE);
	outtextxy(w / 2 - textwidth(Data) / 2, h / 2 - height / 2 + 20 + textheight("A"), Data);
	ButtonDongY.Init(0, w / 2 - DefaultButtonWidth / 2 - DefaultButtonWidth, h / 2 + height / 2 - DefaultButtonHeight - 10, DefaultButtonWidth, DefaultButtonHeight, "DONG Y", 0);
	ButtonHuyBo.Init(0, w / 2 - DefaultButtonWidth / 2 + DefaultButtonWidth, h / 2 + height / 2 - DefaultButtonHeight - 10, DefaultButtonWidth, DefaultButtonHeight, "HUY BO", 0);
	ButtonDongY.draw();
	ButtonHuyBo.draw();
}

void RunXoaDocGia()
{
	const int width = 500, height = 150;
	char Data[] = "DOC GIA SE DUOC XOA";
	ClearScreenXY(w / 2 - width / 2, h / 2 - height / 2, w / 2 + width / 2, h / 2 + height / 2);
	setcolor(YELLOW);
	rectangle(w / 2 - width / 2, h / 2 - height / 2, w / 2 + width / 2, h / 2 + height / 2);
	outtextxy(w / 2 - textwidth("THONG BAO") / 2, h / 2 - height / 2 + 10, "THONG BAO");
	setcolor(WHITE);
	outtextxy(w / 2 - textwidth(Data) / 2, h / 2 - height / 2 + 20 + textheight("A"), Data);
	ButtonDongY.Init(0, w / 2 - DefaultButtonWidth / 2 - DefaultButtonWidth, h / 2 + height / 2 - DefaultButtonHeight - 10, DefaultButtonWidth, DefaultButtonHeight, "DONG Y", 0);
	ButtonHuyBo.Init(0, w / 2 - DefaultButtonWidth / 2 + DefaultButtonWidth, h / 2 + height / 2 - DefaultButtonHeight - 10, DefaultButtonWidth, DefaultButtonHeight, "HUY BO", 0);
	ButtonDongY.draw();
	ButtonHuyBo.draw();
}

void GetCurrentItem(int mouseY)
{
	int temp = (mouseY - Y_DS) / ContentHeight;
	if (CurrentMenuId == ButtonDauSach.ID)
	{
		if (strlen(ButtonSearchDauSach.UserInput) == 0)
		{
			if ((temp > 0) && (temp < 11) && (CurrentItem = temp + (CurrentPage - 1) * 10) <= DSDS.n)
				CurrentItem = temp + (CurrentPage - 1) * 10;
			else
				CurrentItem = -1;
		}
		else
		{
			if ((temp > 0) && (temp < 11) && (CurrentItem = temp + (CurrentPage - 1) * 10) <= ListSearchDauSach.n)
				CurrentItem = temp + (CurrentPage - 1) * 10;
			else
				CurrentItem = -1;
		}
	}
	else if (CurrentMenuId == ButtonDocGia.ID)
	{
		if ((temp > 0) && (temp < 11) && (CurrentItem = temp + (CurrentPage - 1) * 10) <= DSDG.n)
			CurrentItem = temp + (CurrentPage - 1) * 10;
		else
			CurrentItem = -1;
	}
	else if (CurrentMenuId == ButtonXemDauSach.ID)
	{
		if ((temp > 0) && (temp < 11) && (SubCurrentItem = temp + (SubCurrentPage - 1) * 10) <= DSDMS.n)
			SubCurrentItem = temp + (SubCurrentPage - 1) * 10;
		else
			SubCurrentItem = -1;
	}
	else if (CurrentMenuId == ButtonXemDocGia.ID)
	{
		if ((temp > 0) && (temp < 11) && (SubCurrentItem = temp + (SubCurrentPage - 1) * 10) <= DSMT.n)
			SubCurrentItem = temp + (SubCurrentPage - 1) * 10;
		else
			SubCurrentItem = -1;
	}
}

void RunThemDauSach()
{
	const int width = w / 3, height = h / 4;
	char Title[50] = "THEM DAU SACH";
	ClearScreenXY(w / 2 - width / 2, h / 3 - height / 2, w / 2 + width / 2, h * 2 / 3 + height / 2);
	setfillstyle(SOLID_FILL, BLUE);
	rectangle(w / 2 - width / 2, h / 3 - height / 2, w / 2 + width / 2, h * 2 / 3 + height / 2);
	settextstyle(BOLD_FONT, HORIZ_DIR, 5);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy(w / 2 - textwidth(Title) / 2, h / 3 - height / 2 + 10, Title);
	ButtonThemISBN.draw();
	ButtonThemTenSach.draw();
	ButtonThemSoTrang.draw();
	ButtonThemTacGia.draw();
	ButtonThemNXB.draw();
	ButtonThemTheLoai.draw();
	ButtonThem.draw();
	ButtonClearData.draw();
}

void RunSuaDauSach()
{
	const int width = w / 3, height = h / 4;
	char Title[50] = "SUA DAU SACH";
	ClearScreenXY(w / 2 - width / 2, h / 3 - height / 2, w / 2 + width / 2, h * 2 / 3 + height / 2);
	setfillstyle(SOLID_FILL, BLUE);
	rectangle(w / 2 - width / 2, h / 3 - height / 2, w / 2 + width / 2, h * 2 / 3 + height / 2);
	settextstyle(BOLD_FONT, HORIZ_DIR, 5);
	setcolor(TEXT_TITLE_COLOR);
	// outtextxy(w / 2 - width / 2 + textwidth(Title) / 4, h / 3 - height / 2 + 10, Title);
	outtextxy(w / 2 - textwidth(Title) / 2, h / 3 - height / 2 + 10, Title);
	char temp[10];
	if (strlen(ButtonSearchDauSach.UserInput) == 0)
	{
		strcpy(ButtonSuaISBN.UserInput, DSDS.nodes[CurrentItem - 1]->ISBN);
		ButtonSuaISBN.draw();
		strcpy(ButtonSuaTenSach.UserInput, DSDS.nodes[CurrentItem - 1]->TenSach);
		ButtonSuaTenSach.draw();
		itoa(DSDS.nodes[CurrentItem - 1]->SoTrang, temp, 10);
		strcpy(ButtonSuaSoTrang.UserInput, temp);
		ButtonSuaSoTrang.draw();
		strcpy(ButtonSuaTacGia.UserInput, DSDS.nodes[CurrentItem - 1]->TacGia);
		ButtonSuaTacGia.draw();
		itoa(DSDS.nodes[CurrentItem - 1]->NXB, temp, 10);
		strcpy(ButtonSuaNXB.UserInput, temp);
		ButtonSuaNXB.draw();
		strcpy(ButtonSuaTheLoai.UserInput, DSDS.nodes[CurrentItem - 1]->TheLoai);
	}
	else
	{
		strcpy(ButtonSuaISBN.UserInput, ListSearchDauSach.nodes[CurrentItem - 1]->ISBN);
		ButtonSuaISBN.draw();
		strcpy(ButtonSuaTenSach.UserInput, ListSearchDauSach.nodes[CurrentItem - 1]->TenSach);
		ButtonSuaTenSach.draw();
		itoa(ListSearchDauSach.nodes[CurrentItem - 1]->SoTrang, temp, 10);
		strcpy(ButtonSuaSoTrang.UserInput, temp);
		ButtonSuaSoTrang.draw();
		strcpy(ButtonSuaTacGia.UserInput, ListSearchDauSach.nodes[CurrentItem - 1]->TacGia);
		ButtonSuaTacGia.draw();
		itoa(ListSearchDauSach.nodes[CurrentItem - 1]->NXB, temp, 10);
		strcpy(ButtonSuaNXB.UserInput, temp);
		ButtonSuaNXB.draw();
		strcpy(ButtonSuaTheLoai.UserInput, ListSearchDauSach.nodes[CurrentItem - 1]->TheLoai);
		ButtonSuaTheLoai.draw();
	}
	ButtonDongY.Init(0, w / 3 + w / 9 - DefaultButtonWidth / 2, h / 2 - h / 4 + 200 + DefaultButtonHeight * 6, DefaultButtonWidth, DefaultButtonHeight, "DONG Y", 0);
	ButtonHuyBo.Init(0, w / 3 + w / 6 + DefaultButtonWidth / 2, h / 2 - h / 4 + 200 + DefaultButtonHeight * 6, DefaultButtonWidth, DefaultButtonHeight, "HUY BO", 0);
	ButtonDongY.draw();
	ButtonHuyBo.draw();
}
void RunSuaDocGia()
{
	const int width = w / 3, height = h / 4;
	char Title[50] = "SUA DOC GIA";
	ClearScreenXY(w / 2 - width / 2, h / 3 - height / 2, w / 2 + width / 2, h * 2 / 3 + height / 2);
	setfillstyle(SOLID_FILL, BLUE);
	rectangle(w / 2 - width / 2, h / 3 - height / 2, w / 2 + width / 2, h * 2 / 3 + height / 2);
	settextstyle(BOLD_FONT, HORIZ_DIR, 5);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy(w / 2 - textwidth(Title) / 2, h / 3 - height / 2 + 10, Title);
	char temp[10];
	itoa(DSDG.nodes[CurrentItem - 1]->MaThe, temp, 10);
	strcpy(ButtonSuaMaThe.UserInput, temp);
	ButtonSuaMaThe.draw();
	strcpy(ButtonSuaHo.UserInput, DSDG.nodes[CurrentItem - 1]->Ho);
	ButtonSuaHo.draw();
	strcpy(ButtonSuaTen.UserInput, DSDG.nodes[CurrentItem - 1]->Ten);
	ButtonSuaTen.draw();
	itoa(DSDG.nodes[CurrentItem - 1]->Phai, temp, 10);
	strcpy(ButtonSuaPhai.UserInput, temp);
	ButtonSuaPhai.draw();
	itoa(DSDG.nodes[CurrentItem - 1]->TrangThai, temp, 10);
	strcpy(ButtonSuaTrangThai.UserInput, temp);
	ButtonSuaTrangThai.draw();
	ButtonDongY.Init(0, w / 3 + w / 9 - DefaultButtonWidth / 2, h / 2 - h / 4 + 200 + DefaultButtonHeight * 6, DefaultButtonWidth, DefaultButtonHeight, "DONG Y", 0);
	ButtonHuyBo.Init(0, w / 3 + w / 6 + DefaultButtonWidth / 2, h / 2 - h / 4 + 200 + DefaultButtonHeight * 6, DefaultButtonWidth, DefaultButtonHeight, "HUY BO", 0);
	ButtonDongY.draw();
	ButtonHuyBo.draw();
}

void ClearEditButtonData(EditButton &Button)
{
	memset(Button.UserInput, 0, sizeof Button.UserInput);
	Button.draw();
}

void SearchDauSachEvent()
{
	ButtonEffect(ButtonClearSearchDauSach);
	ButtonTemp = &ButtonSearchDauSach;
	if (GetAsyncKeyState(VK_LBUTTON) && ButtonSearchDauSach.isMouseHover(mouseX, mouseY) == false)
	{
		SetMenuSelect(ButtonDauSach.ID);
		ButtonTemp = nullptr;
	}
}

void DauSachEvent()
{
	ButtonEffect(ButtonBack);
	ButtonEffect(ButtonPrev);
	ButtonEffect(ButtonNext);
	ButtonEffect(ButtonXemDauSach);
	ButtonEffect(ButtonThemDauSach);
	ButtonEffect(ButtonXoaDauSach);
	ButtonEffect(ButtonSuaDauSach);
	ButtonEffect(ButtonClearSearchDauSach);

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (ButtonBack.isMouseHover(mouseX, mouseY))
			SetMenuSelect(0);
		else if (ButtonThemDauSach.isMouseHover(mouseX, mouseY))
			SetMenuSelect(ButtonThemDauSach.ID);
		else if (ButtonNext.isMouseHover(mouseX, mouseY))
		{
			if (CurrentPage < TotalPage)
				CurrentPage++;
			RunDauSach();
		}
		else if (ButtonPrev.isMouseHover(mouseX, mouseY))
		{
			if (CurrentPage > 1)
				CurrentPage--;
			RunDauSach();
		}
		else if (ButtonSearchDauSach.isMouseHover(mouseX, mouseY))
			SetMenuSelect(ButtonSearchDauSach.ID);
		else if (ButtonClearSearchDauSach.isMouseHover(mouseX, mouseY))
		{
			ClearEditButtonData(ButtonSearchDauSach);
			RunDauSach();
		}
		else if (ButtonXemDauSach.isMouseHover(mouseX, mouseY))
		{
			if (CurrentItem == -1)
			{
				ThongBao("HAY CHON 1 DAU SACH");
			}
			else
			{
				SubCurrentItem = -1;
				SubCurrentPage = 1;
				SetMenuSelect(ButtonXemDauSach.ID);
			}
		}
		else if (ButtonXoaDauSach.isMouseHover(mouseX, mouseY))
		{
			if (CurrentItem == -1)
			{
				ThongBao("HAY CHON 1 DAU SACH");
			}
			else
				SetMenuSelect(ButtonXoaDauSach.ID);
		}
		else if (ButtonSuaDauSach.isMouseHover(mouseX, mouseY))
		{
			if (CurrentItem == -1)
			{
				ThongBao("HAY CHON 1 DAU SACH");
			}
			else
				SetMenuSelect(ButtonSuaDauSach.ID);
		}
		else
		{
			GetCurrentItem(mouseY);
			RunDauSach();
		}
	}
}

void DocGiaEvent()
{
	ButtonEffect(ButtonBack);
	ButtonEffect(ButtonPrev);
	ButtonEffect(ButtonNext);
	ButtonEffect(ButtonXemDocGia);
	ButtonEffect(ButtonThemDocGia);
	ButtonEffect(ButtonXoaDocGia);
	ButtonEffect(ButtonSuaDocGia);
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (ButtonBack.isMouseHover(mouseX, mouseY))
			SetMenuSelect(0);
		else if (ButtonDocGiaHoTen.isMouseHover(mouseX, mouseY))
		{
			ButtonDocGiaHoTen.IsHover = 1;
			SetMenuSelect(ButtonDocGia.ID);
		}
		else if (ButtonDocGiaMaThe.isMouseHover(mouseX, mouseY))
		{
			ButtonDocGiaHoTen.IsHover = 0;
			SetMenuSelect(ButtonDocGia.ID);
		}
		else if (ButtonXemDocGia.isMouseHover(mouseX, mouseY))
		{
			if (CurrentItem == -1)
			{
				ThongBao("HAY CHON 1 DOC GIA");
			}
			else
			{
				SubCurrentItem = -1;
				SubCurrentPage = 1;
				SetMenuSelect(ButtonXemDocGia.ID);
			}
		}
		else if (ButtonThemDocGia.isMouseHover(mouseX, mouseY))
			SetMenuSelect(ButtonThemDocGia.ID);
		else if (ButtonXoaDocGia.isMouseHover(mouseX, mouseY))
		{
			if (CurrentItem == -1)
			{
				ThongBao("HAY CHON 1 DOC GIA");
			}
			else
				SetMenuSelect(ButtonXoaDocGia.ID);
		}
		else if (ButtonSuaDocGia.isMouseHover(mouseX, mouseY))
		{
			if (CurrentItem == -1)
			{
				ThongBao("HAY CHON 1 DOC GIA");
			}
			else
				SetMenuSelect(ButtonSuaDocGia.ID);
		}
		else if (ButtonNext.isMouseHover(mouseX, mouseY))
		{
			if (CurrentPage < TotalPage)
				CurrentPage++;
			RunDocGia();
		}
		else if (ButtonPrev.isMouseHover(mouseX, mouseY))
		{
			if (CurrentPage > 1)
				CurrentPage--;
			RunDocGia();
		}
		else
		{
			GetCurrentItem(mouseY);
			RunDocGia();
		}
	}
}

void CLearLastCharInput()
{
	if (ButtonTemp != nullptr)
	{
		ButtonTemp->UserInput[strlen(ButtonTemp->UserInput)] = '\0';
		ButtonTemp->draw();
	}
}

void ThemDauSachEvent()
{
	ButtonEffect(ButtonBack);
	ButtonEffect(ButtonThem);
	ButtonEffect(ButtonClearData);
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (ButtonBack.isMouseHover(mouseX, mouseY))
		{
			SetMenuSelect(ButtonDauSach.ID);
			ButtonTemp = nullptr;
		}
		else if (ButtonThemISBN.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonThemISBN;
		}
		else if (ButtonThemTenSach.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonThemTenSach;
		}
		else if (ButtonThemSoTrang.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonThemSoTrang;
		}
		else if (ButtonThemTacGia.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonThemTacGia;
		}
		else if (ButtonThemNXB.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonThemNXB;
		}
		else if (ButtonThemTheLoai.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonThemTheLoai;
		}
		else if (ButtonThem.isMouseHover(mouseX, mouseY))
		{
			// Them Dau Sach moi
			DauSach *dausach = new DauSach(ButtonThemISBN.UserInput, ButtonThemTenSach.UserInput, ButtonThemTacGia.UserInput, ButtonThemTheLoai.UserInput, atoi(ButtonThemSoTrang.UserInput), atoi(ButtonThemNXB.UserInput));
			ThemDauSach(DSDS, dausach);
			ClearEditButtonData(ButtonThemISBN);
			ClearEditButtonData(ButtonThemTenSach);
			ClearEditButtonData(ButtonThemSoTrang);
			ClearEditButtonData(ButtonThemTacGia);
			ClearEditButtonData(ButtonThemNXB);
			ClearEditButtonData(ButtonThemTheLoai);
			ButtonTemp = nullptr;
			ThongBao("THEM DAU SACH THANH CONG");
			SearchDauSach(ButtonSearchDauSach.UserInput);
		}
		else if (ButtonClearData.isMouseHover(mouseX, mouseY))
		{
			ClearEditButtonData(ButtonThemISBN);
			ClearEditButtonData(ButtonThemTenSach);
			ClearEditButtonData(ButtonThemSoTrang);
			ClearEditButtonData(ButtonThemTacGia);
			ClearEditButtonData(ButtonThemNXB);
			ClearEditButtonData(ButtonThemTheLoai);
			ButtonTemp = nullptr;
		}
	}
}
void XemDauSachEvent()
{
	ButtonEffect(ButtonBack);
	ButtonEffect(ButtonPrev);
	ButtonEffect(ButtonNext);
	ButtonEffect(ButtonThemDMS);
	ButtonEffect(ButtonXoaDMS);
	ButtonEffect(ButtonSuaDMS);
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (ButtonBack.isMouseHover(mouseX, mouseY))
			SetMenuSelect(ButtonDauSach.ID);
		else if (ButtonNext.isMouseHover(mouseX, mouseY))
		{
			if (SubCurrentPage < TotalPage)
				SubCurrentPage++;
			RunXemDauSach();
		}
		else if (ButtonPrev.isMouseHover(mouseX, mouseY))
		{
			if (SubCurrentPage > 1)
				SubCurrentPage--;
			RunXemDauSach();
		}
		else if (ButtonThemDMS.isMouseHover(mouseX, mouseY))
			SetMenuSelect(ButtonThemDMS.ID);
		else
		{
			GetCurrentItem(mouseY);
			RunXemDauSach();
		}
	}
}
void ThemDMSEvent()
{
	ButtonEffect(ButtonDongY);
	ButtonEffect(ButtonHuyBo);
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (ButtonHuyBo.isMouseHover(mouseX, mouseY))
		{
			ButtonTemp = nullptr;
			ClearEditButtonData(ButtonThemSoLuong);
			SetMenuSelect(ButtonXemDauSach.ID);
		}
		else if (ButtonDongY.isMouseHover(mouseX, mouseY))
		{
			if (strlen(ButtonThemSoLuong.UserInput) != 0)
			{
				ButtonTemp = nullptr;
				TotalAddDMS = atoi(ButtonThemSoLuong.UserInput);
				ClearEditButtonData(ButtonThemSoLuong);
				if (!TotalAddDMS)
					ThongBao("SO LUONG PHAI > 0");
				else
					SetMenuSelect(99);
			}
			else
				ThongBao("NHAP SO LUONG SACH");
		}
		else if (ButtonThemSoLuong.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonThemSoLuong;
		}
	}
}
void ThemSachEvent()
{
	ButtonEffect(ButtonDongY);
	ButtonEffect(ButtonHuyBo);
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (ButtonHuyBo.isMouseHover(mouseX, mouseY))
		{
			ButtonTemp = nullptr;
			SetMenuSelect(ButtonXemDauSach.ID);
		}
		else if (ButtonDongY.isMouseHover(mouseX, mouseY))
		{
			ClearEditButtonData(ButtonThemViTriSach);
			ButtonTemp = nullptr;
			Sach *sach = new Sach;
			strcpy(sach->MaSach, ButtonThemMaSach.UserInput);
			sach->TrangThai = atoi(ButtonThemTrangThaiSach.UserInput);
			strcpy(sach->ViTri, ButtonThemViTriSach.UserInput);
			string str(sach->MaSach);
			sach->id = atoi(GetNumberFromMaSach(str).c_str());
			// cout << sach->id << " " << sach->MaSach << " " << sach->TrangThai << " " << sach->ViTri << endl;
			InsertAfter_DM_Sach(DSDS.nodes[CurrentItem - 1], sach);
			if (CurrentAddDMS < TotalAddDMS)
			{
				CurrentAddDMS++;
				ThongBao("THEM THANH CONG", 400, 150, 99);
			}
			else
			{
				ThongBao("THEM THANH CONG", 400, 150, ButtonXemDauSach.ID);
			}
		}
		else if (ButtonThemViTriSach.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonThemViTriSach;
		}
	}
}
void XemDocGiaEvent()
{
	ButtonEffect(ButtonBack);
	ButtonEffect(ButtonPrev);
	ButtonEffect(ButtonNext);
	ButtonEffect(ButtonMuonSach);
	ButtonEffect(ButtonTraSach);
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (ButtonBack.isMouseHover(mouseX, mouseY))
			SetMenuSelect(ButtonDocGia.ID);
		else if (ButtonNext.isMouseHover(mouseX, mouseY))
		{
			if (SubCurrentPage < TotalPage)
				SubCurrentPage++;
			RunXemDocGia();
		}
		else if (ButtonPrev.isMouseHover(mouseX, mouseY))
		{
			if (SubCurrentPage > 1)
				SubCurrentPage--;
			RunXemDocGia();
		}
		else if (ButtonMuonSach.isMouseHover(mouseX, mouseY))
			SetMenuSelect(ButtonMuonSach.ID);
		else if (ButtonTraSach.isMouseHover(mouseX, mouseY))
		{
			if (SubCurrentItem == -1)
			{
				ThongBao("CHON 1 MA SACH");
			}
			else if (DSMT.nodes[SubCurrentItem - 1]->TrangThai != 0)
				ThongBao("KHONG THE TRA");
			else
			{
				int code = TraSach(DSDG.nodes[CurrentItem - 1], DSMT.nodes[SubCurrentItem - 1]->MaSach, DSDS);
				if (code == 1)
					ThongBao("TRA SACH THANH CONG");
				else
					ThongBao("LOI");
			}
		}
		else
		{
			GetCurrentItem(mouseY);
			RunXemDocGia();
		}
	}
}
void MuonSachEvent()
{
	ButtonEffect(ButtonDongY);
	ButtonEffect(ButtonHuyBo);
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (ButtonHuyBo.isMouseHover(mouseX, mouseY))
		{
			ClearEditButtonData(ButtonNhapMaSach);
			ButtonTemp = nullptr;
			SetMenuSelect(ButtonXemDocGia.ID);
		}
		else if (ButtonDongY.isMouseHover(mouseX, mouseY))
		{
			if (strlen(ButtonNhapMaSach.UserInput) == 0)
				ThongBao("HAY NHAP MA SACH");
			else
			{
				int code = MuonSach(DSDG.nodes[CurrentItem - 1], ButtonNhapMaSach.UserInput, DSDS);
				ButtonTemp = nullptr;
				ClearEditButtonData(ButtonNhapMaSach);
				if (code != 0)
					ThongBao(MuonSachCode[code]);
				else
					ThongBao(MuonSachCode[code], 400, 150, ButtonXemDocGia.ID);
			}
		}
		else if (ButtonNhapMaSach.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonNhapMaSach;
		}
	}
}
void XoaDauSachEvent()
{
	ButtonEffect(ButtonDongY);
	ButtonEffect(ButtonHuyBo);
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (ButtonDongY.isMouseHover(mouseX, mouseY))
		{
			if (strlen(ButtonSearchDauSach.UserInput) != 0)
			{
				DeleteDauSach(DSDS, TimPosDauSach(DSDS, ListSearchDauSach.nodes[CurrentItem - 1]->ISBN));
				DeleteDauSach(ListSearchDauSach, CurrentItem - 1);
			}
			else
				DeleteDauSach(DSDS, CurrentItem - 1);
			CurrentItem = -1;
			ThongBao("XOA THANH CONG", 400, 150, ButtonDauSach.ID);
		}
		else if (ButtonHuyBo.isMouseHover(mouseX, mouseY))
			SetMenuSelect(ButtonDauSach.ID);
	}
}
void XoaDocGiaEvent()
{
	ButtonEffect(ButtonDongY);
	ButtonEffect(ButtonHuyBo);
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (ButtonDongY.isMouseHover(mouseX, mouseY))
		{
			TreeAVLDocGia = deleteNode(TreeAVLDocGia, DSDG.nodes[CurrentItem - 1]->MaThe);
			CurrentItem = -1;
			ThongBao("XOA THANH CONG", 400, 150, ButtonDocGia.ID);
		}
		else if (ButtonHuyBo.isMouseHover(mouseX, mouseY))
			SetMenuSelect(ButtonDocGia.ID);
	}
}

void SuaDauSachEvent()
{
	ButtonEffect(ButtonDongY);
	ButtonEffect(ButtonHuyBo);
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (ButtonHuyBo.isMouseHover(mouseX, mouseY))
		{
			ClearEditButtonData(ButtonSuaISBN);
			ClearEditButtonData(ButtonSuaTenSach);
			ClearEditButtonData(ButtonSuaSoTrang);
			ClearEditButtonData(ButtonSuaTacGia);
			ClearEditButtonData(ButtonSuaNXB);
			ClearEditButtonData(ButtonSuaTheLoai);
			SetMenuSelect(ButtonDauSach.ID);
			ButtonTemp = nullptr;
		}
		else if (ButtonSuaISBN.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonSuaISBN;
		}
		else if (ButtonSuaTenSach.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonSuaTenSach;
		}
		else if (ButtonSuaSoTrang.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonSuaSoTrang;
		}
		else if (ButtonSuaTacGia.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonSuaTacGia;
		}
		else if (ButtonSuaNXB.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonSuaNXB;
		}
		else if (ButtonSuaTheLoai.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonSuaTheLoai;
		}
		else if (ButtonDongY.isMouseHover(mouseX, mouseY))
		{
			if (strlen(ButtonSearchDauSach.UserInput) == 0)
			{
				DSDS.nodes[CurrentItem - 1]->Init(ButtonSuaISBN.UserInput, ButtonSuaTenSach.UserInput, ButtonSuaTacGia.UserInput, ButtonSuaTheLoai.UserInput, atoi(ButtonSuaSoTrang.UserInput), atoi(ButtonSuaNXB.UserInput));
			}
			else
			{
				ListSearchDauSach.nodes[CurrentItem - 1]->Init(ButtonSuaISBN.UserInput, ButtonSuaTenSach.UserInput, ButtonSuaTacGia.UserInput, ButtonSuaTheLoai.UserInput, atoi(ButtonSuaSoTrang.UserInput), atoi(ButtonSuaNXB.UserInput));
				DSDS.nodes[TimPosDauSach(DSDS, ListSearchDauSach.nodes[CurrentItem - 1]->ISBN)]->Init(ButtonSuaISBN.UserInput, ButtonSuaTenSach.UserInput, ButtonSuaTacGia.UserInput, ButtonSuaTheLoai.UserInput, atoi(ButtonSuaSoTrang.UserInput), atoi(ButtonSuaNXB.UserInput));
			}
			ThongBao("SUA THANH CONG", 400, 150, ButtonDauSach.ID);
			ButtonTemp = nullptr;
		}
	}
}
void ThongKeEvent()
{
	ButtonEffect(ButtonBack);
	ButtonEffect(ButtonPrev);
	ButtonEffect(ButtonNext);
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (ButtonBack.isMouseHover(mouseX, mouseY))
			SetMenuSelect(0);
		else if (ButtonThongKeTop10.isMouseHover(mouseX, mouseY))
		{
			ButtonThongKeTop10.IsHover = 1;
			SetMenuSelect(ButtonThongKe.ID);
		}
		else if (ButtonThongKeQuaHan.isMouseHover(mouseX, mouseY))
		{
			CurrentPage = 1;
			ButtonThongKeTop10.IsHover = 0;
			SetMenuSelect(ButtonThongKe.ID);
		}
		else if (ButtonNext.isMouseHover(mouseX, mouseY))
		{
			if (CurrentPage < TotalPage)
				CurrentPage++;
			RunThongKe();
		}
		else if (ButtonPrev.isMouseHover(mouseX, mouseY))
		{
			if (CurrentPage > 1)
				CurrentPage--;
			RunThongKe();
		}
	}
}
void ThongTinEvent()
{
	ButtonEffect(ButtonBack);
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (ButtonBack.isMouseHover(mouseX, mouseY))
			SetMenuSelect(0);
	}
}
void SuaDocGiaEvent()
{
	ButtonEffect(ButtonDongY);
	ButtonEffect(ButtonHuyBo);
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (ButtonHuyBo.isMouseHover(mouseX, mouseY))
		{
			ClearEditButtonData(ButtonSuaMaThe);
			ClearEditButtonData(ButtonSuaHo);
			ClearEditButtonData(ButtonSuaTen);
			ClearEditButtonData(ButtonSuaPhai);
			ClearEditButtonData(ButtonSuaTrangThai);
			SetMenuSelect(ButtonDocGia.ID);
			ButtonTemp = nullptr;
		}
		else if (ButtonSuaHo.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonSuaHo;
		}
		else if (ButtonSuaTen.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonSuaTen;
		}
		else if (ButtonSuaPhai.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonSuaPhai;
		}
		else if (ButtonSuaTrangThai.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonSuaTrangThai;
		}
		else if (ButtonDongY.isMouseHover(mouseX, mouseY))
		{
			TheDocGia DocGia(atoi(ButtonSuaMaThe.UserInput), ButtonSuaHo.UserInput, ButtonSuaTen.UserInput, atoi(ButtonSuaPhai.UserInput), atoi(ButtonSuaTrangThai.UserInput), DSDG.nodes[CurrentItem - 1]->DS_MT, DSDG.nodes[CurrentItem - 1]->TongSoLuong);
			updateNode(TreeAVLDocGia, DocGia);
			ThongBao("SUA THANH CONG", 400, 150, ButtonDocGia.ID);
			ButtonTemp = nullptr;
		}
	}
}

void ThemDocGiaEvent()
{
	ButtonEffect(ButtonBack);
	ButtonEffect(ButtonThem);
	ButtonEffect(ButtonClearData);
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (ButtonBack.isMouseHover(mouseX, mouseY))
		{
			SetMenuSelect(ButtonDocGia.ID);
			ButtonTemp = nullptr;
		}
		else if (ButtonThemHo.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonThemHo;
		}
		else if (ButtonThemTen.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonThemTen;
		}
		else if (ButtonThemPhai.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonThemPhai;
		}
		else if (ButtonThemTrangThai.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonThemTrangThai;
		}
		else if (ButtonThem.isMouseHover(mouseX, mouseY))
		{
			// Them Doc Gia moi
			TheDocGia theDocGia(atoi(ButtonThemMaThe.UserInput), ButtonThemHo.UserInput, ButtonThemTen.UserInput, atoi(ButtonThemPhai.UserInput), atoi(ButtonThemTrangThai.UserInput));
			TreeAVLDocGia = InsertDocGia(TreeAVLDocGia, theDocGia);
			ClearEditButtonData(ButtonThemMaThe);
			ClearEditButtonData(ButtonThemHo);
			ClearEditButtonData(ButtonThemTen);
			ClearEditButtonData(ButtonThemPhai);
			ClearEditButtonData(ButtonThemTrangThai);
			ButtonTemp = nullptr;
			ThongBao("THEM DOC GIA THANH CONG");
		}
		else if (ButtonClearData.isMouseHover(mouseX, mouseY))
		{
			// ClearEditButtonData(ButtonThemMaThe);
			ClearEditButtonData(ButtonThemHo);
			ClearEditButtonData(ButtonThemTen);
			ClearEditButtonData(ButtonThemPhai);
			ClearEditButtonData(ButtonThemTrangThai);
			ButtonTemp = nullptr;
		}
	}
}

void ThongBaoEvent()
{
	ButtonEffect(ButtonOKThongBao);
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (ButtonOKThongBao.isMouseHover(mouseX, mouseY))
			SetMenuSelect(LastCurrenMenuID);
	}
}

void MenuEvent()
{
	ButtonEffect(ButtonDauSach);
	ButtonEffect(ButtonDocGia);
	ButtonEffect(ButtonThongKe);
	ButtonEffect(ButtonThongTin);
	ButtonEffect(ButtonThoat);
	// Menu Click Event
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (ButtonDauSach.isMouseHover(mouseX, mouseY))
		{
			SetMenuSelect(ButtonDauSach.ID);
		}
		if (ButtonDocGia.isMouseHover(mouseX, mouseY))
		{
			SetMenuSelect(ButtonDocGia.ID);
		}
		if (ButtonThongKe.isMouseHover(mouseX, mouseY))
		{
			SetMenuSelect(ButtonThongKe.ID);
		}
		if (ButtonThongTin.isMouseHover(mouseX, mouseY))
		{
			SetMenuSelect(ButtonThongTin.ID);
		}
		else if (ButtonThoat.isMouseHover(mouseX, mouseY))
		{
			isExit = 1;
		}
	}
}

void MoveToNextEditTextButton()
{
	CLearLastCharInput();
	if (ButtonTemp->ID == ButtonThemISBN.ID)
	{
		ButtonTemp = &ButtonThemTenSach;
	}
	else if (ButtonTemp->ID == ButtonThemTenSach.ID)
	{
		ButtonTemp = &ButtonThemSoTrang;
	}
	else if (ButtonTemp->ID == ButtonThemSoTrang.ID)
	{
		ButtonTemp = &ButtonThemTacGia;
	}
	else if (ButtonTemp->ID == ButtonThemTacGia.ID)
	{
		ButtonTemp = &ButtonThemNXB;
	}
	else if (ButtonTemp->ID == ButtonThemNXB.ID)
	{
		ButtonTemp = &ButtonThemTheLoai;
	}
}

boolean CheckInput(char c)
{
	if (CurrentMenuId == ButtonSearchDauSach.ID)
	{
		if (ButtonTemp->ID == ButtonSearchDauSach.ID)
			return true;
	}
	else if (CurrentMenuId == ButtonThemDMS.ID)
	{
		if (ButtonTemp->ID == ButtonThemSoLuong.ID)
		{
			if (c >= 48 && c <= 57)
				return true;
		}
	}
	else if (CurrentMenuId == ButtonThemDauSach.ID)
	{
		if (ButtonTemp->ID == ButtonThemISBN.ID)
			return true;
		else if (ButtonTemp->ID == ButtonThemTenSach.ID)
			return true;
		else if (ButtonTemp->ID == ButtonThemSoTrang.ID)
		{
			if (c >= 48 && c <= 57)
				return true;
		}
		else if (ButtonTemp->ID == ButtonThemTacGia.ID)
			return true;
		else if (ButtonTemp->ID == ButtonThemNXB.ID)
		{
			if (c >= 48 && c <= 57)
				return true;
		}
		else if (ButtonTemp->ID == ButtonThemTheLoai.ID)
			return true;
	}
	else if (CurrentMenuId == ButtonSuaDauSach.ID)
	{
		if (ButtonTemp->ID == ButtonSuaISBN.ID)
			return true;
		else if (ButtonTemp->ID == ButtonSuaTenSach.ID)
			return true;
		else if (ButtonTemp->ID == ButtonSuaSoTrang.ID)
		{
			if (c >= 48 && c <= 57)
				return true;
		}
		else if (ButtonTemp->ID == ButtonSuaTacGia.ID)
			return true;
		else if (ButtonTemp->ID == ButtonSuaNXB.ID)
		{
			if (c >= 48 && c <= 57)
				return true;
		}
		else if (ButtonTemp->ID == ButtonSuaTheLoai.ID)
			return true;
	}
	else if (CurrentMenuId == ButtonMuonSach.ID)
	{
		return true;
	}
	else if (CurrentMenuId == ButtonThemDocGia.ID)
	{
		if (ButtonTemp->ID == ButtonThemHo.ID)
			return true;
		else if (ButtonTemp->ID == ButtonThemTen.ID)
			return true;
		else if (ButtonTemp->ID == ButtonThemPhai.ID)
		{
			if (c >= 48 && c <= 49 && strlen(ButtonTemp->UserInput) < 1)
				return true;
		}
		else if (ButtonTemp->ID == ButtonThemTrangThai.ID)
		{
			if (c >= 48 && c <= 49 && strlen(ButtonTemp->UserInput) < 1)
				return true;
		}
	}
	else if (CurrentMenuId == ButtonSuaDocGia.ID)
	{
		if (ButtonTemp->ID == ButtonSuaHo.ID)
			return true;
		else if (ButtonTemp->ID == ButtonSuaTen.ID)
			return true;
		else if (ButtonTemp->ID == ButtonSuaPhai.ID)
		{
			if (c >= 48 && c <= 49 && strlen(ButtonTemp->UserInput) < 1)
				return true;
		}
		else if (ButtonTemp->ID == ButtonSuaTrangThai.ID)
		{
			if (c >= 48 && c <= 49 && strlen(ButtonTemp->UserInput) < 1)
				return true;
		}
	}
	return false;
}

void KeyBoardEvent()
{
	int n = 0;
	char c;
	if (ButtonTemp != nullptr)
	{
		n = strlen(ButtonTemp->UserInput);
		ButtonTemp->UserInput[n] = '_';
		ButtonTemp->draw();
		ButtonTemp->UserInput[n] = '\0';
		while (kbhit())
		{
			c = getch();
			c = toupper(c);
			if (c == BACKSPACE)
			{
				ButtonTemp->UserInput[n - 1] = '\0';
			}
			else if (c == ENTER)
				MoveToNextEditTextButton();
			else if (CheckInput(c) && n < 28)
			{
				ButtonTemp->UserInput[n] = c;
				n++;
			};
			if (ButtonTemp->ID == ButtonSearchDauSach.ID)
			{
				SearchDauSach(ButtonSearchDauSach.UserInput);
				RunDauSach();
			}
		}
	}
}

void InDanhSachDauSach(DS_DauSach &DSDS)
{
	for (int i = 0; i < DSDS.n; i++)
	{
		cout << DSDS.nodes[i]->ISBN << "||" << DSDS.nodes[i]->TenSach << "||" << DSDS.nodes[i]->SoTrang << "||" << DSDS.nodes[i]->TacGia << "||" << DSDS.nodes[i]->NXB << "||" << DSDS.nodes[i]->TheLoai << endl;
	}
}

void Event()
{
	KeyBoardEvent();
	mouseX = mousex();
	mouseY = mousey();
	if (CurrentMenuId == 0)
		MenuEvent();
	else if (CurrentMenuId == ButtonOKThongBao.ID)
		ThongBaoEvent();
	else if (CurrentMenuId == ButtonDauSach.ID)
		DauSachEvent();
	else if (CurrentMenuId == ButtonThemDauSach.ID)
		ThemDauSachEvent();
	else if (CurrentMenuId == ButtonSearchDauSach.ID)
		SearchDauSachEvent();
	else if (CurrentMenuId == ButtonXemDauSach.ID)
		XemDauSachEvent();
	else if (CurrentMenuId == ButtonThemDMS.ID)
		ThemDMSEvent();
	else if (CurrentMenuId == 99)
		ThemSachEvent();
	else if (CurrentMenuId == ButtonXoaDauSach.ID)
		XoaDauSachEvent();
	else if (CurrentMenuId == ButtonSuaDauSach.ID)
		SuaDauSachEvent();
	else if (CurrentMenuId == ButtonDocGia.ID)
		DocGiaEvent();
	else if (CurrentMenuId == ButtonXemDocGia.ID)
		XemDocGiaEvent();
	else if (CurrentMenuId == ButtonMuonSach.ID)
		MuonSachEvent();
	else if (CurrentMenuId == ButtonThemDocGia.ID)
		ThemDocGiaEvent();
	else if (CurrentMenuId == ButtonXoaDocGia.ID)
		XoaDocGiaEvent();
	else if (CurrentMenuId == ButtonSuaDocGia.ID)
		SuaDocGiaEvent();
	else if (CurrentMenuId == ButtonThongKe.ID)
		ThongKeEvent();
	else if (CurrentMenuId == ButtonThongTin.ID)
		ThongTinEvent();
}
void InDMS()
{
	// NodeSach *node = new NodeSach;
	for (int i = 0; i < DSDS.n; i++)
	{
		cout << DSDS.nodes[i]->TenSach << endl;
		DM_Sach *temp = DSDS.nodes[i]->DS_Sach;
		for (temp; temp != nullptr; temp = temp->next)
		{
			cout << temp->sach->id << " " << temp->sach->MaSach << " " << temp->sach->TrangThai << " " << temp->sach->ViTri << endl;
		}
		cout << "-------------------" << endl;
	}
}
void InMuonTra(NodeTheDocGia *&TreeAVLDocGia) // Inorder
{
	if (TreeAVLDocGia != nullptr)
	{
		InMuonTra(TreeAVLDocGia->left);
		NodeMuonTra *node = TreeAVLDocGia->DocGia.DS_MT->First;
		cout << TreeAVLDocGia->DocGia.Ten << endl;
		for (node; node != nullptr; node = node->Right)
		{
			cout << node->value->MaSach << " " << node->value->TrangThai << endl;
		}
		cout << "--------------------" << endl;
		InMuonTra(TreeAVLDocGia->right);
	}
}
void InQuaHan()
{
	DSQH.n = 0;
	GetFromTree(TreeAVLDocGia, DSQH, DSDS);
	for (int i = 0; i < DSQH.n; ++i)
	{
		cout << DSQH.nodes[i]->MaSach << " " << DSQH.nodes[i]->SoNgayQuaHan << endl;
	}
}
int main()
{
	initwindow(w, h, AppTitle);
	DrawMenu();
	GetDataFromFile();
	// InDMS();
	// InMuonTra(TreeAVLDocGia);
	// InQuaHan();
	while (1)
	{
		Event();
		if (isExit)
			break;
		delay(50);
	}
	closegraph();
	return 0;
}

// Thu vien C++
#include <graphics.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <windows.h>
#include <math.h>
#include "time.h"

// File ngoai
#include "Define.h"
#include "StructDanhMucSach.h"
#include "StructDauSach.h"
#include "StructMuonTra.h"
#include "StructTheDocGia.h"

#include "Button.h"
#include "global.h"

#include "help.h"
#include "DrawMenu.h"
#include "DrawDauSach.h"
#include "DrawDocGia.h"
#include "DrawThongKe.h"
#include "DrawThongTin.h"

using namespace std;
/* MenuId
	99 - Them Sach
*/

void GetDataDauSachFromFile(DS_DauSach &DSDS)
{
	std::fstream FileDauSach, FileDanhMucSach;
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
			sach->SoLuotMuon = atoi(data.c_str());
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

// -------------------------------- Write-------------------------//
void WriteDataDauSachToFile(DS_DauSach DSDS)
{
	fstream FileDauSach, FileDanhMucSach;
	FileDauSach.open("data_dausach.txt", ios::out);
	if (!FileDauSach.is_open())
	{
		printf("Loi mo FileDauSach de ghi \n");
		return;
	}

	FileDanhMucSach.open("data_danhmucsach.txt", ios::out);
	if (!FileDanhMucSach.is_open())
	{
		printf("Loi mo FileDanhMucSach de ghi \n");
		return;
	}

	FileDauSach << DSDS.n << std::endl;
	for (int i = 0; i < DSDS.n; ++i)
	{
		FileDauSach << DSDS.nodes[i]->ISBN << std::endl;
		FileDauSach << DSDS.nodes[i]->TenSach << std::endl;
		FileDauSach << DSDS.nodes[i]->SoTrang << std::endl;
		FileDauSach << DSDS.nodes[i]->TacGia << std::endl;
		FileDauSach << DSDS.nodes[i]->NXB << std::endl;
		FileDauSach << DSDS.nodes[i]->TheLoai << std::endl;
		FileDanhMucSach << DSDS.nodes[i]->TongSoLuong << std::endl;
		if (DSDS.nodes[i]->TongSoLuong > 0)
			for (DM_Sach *node = DSDS.nodes[i]->DS_Sach; node != NULL; node = node->next)
			{
				FileDanhMucSach << node->sach->MaSach << std::endl;
				FileDanhMucSach << node->sach->SoLuotMuon << std::endl;
				FileDanhMucSach << node->sach->TrangThai << std::endl;
				FileDanhMucSach << node->sach->ViTri << std::endl;
			}
	}
	FileDauSach.close();
	FileDanhMucSach.close();
}

void WriteDSMuonTra(fstream &FileMuonTra, NodeTheDocGia *thedocgia)
{
	FileMuonTra << thedocgia->DocGia.TongSoLuong << std::endl;
	if (thedocgia->DocGia.TongSoLuong > 0)
		for (NodeMuonTra *node = thedocgia->DocGia.DS_MT->First; node != NULL; node = node->Right)
		{
			FileMuonTra << node->value->MaSach << std::endl;
			FileMuonTra << node->value->TrangThai << std::endl;
			FileMuonTra << node->value->NgayMuon.res << std::endl;
			if (node->value->TrangThai == 0)
				FileMuonTra << "0" << std::endl;
			else
				FileMuonTra << node->value->NgayTra.res << std::endl;
		}
}

void WriteDG(fstream &FileDocGia, fstream &FileMuonTra, NodeTheDocGia *&TreeAVLDocGia)
{
	if (TreeAVLDocGia != nullptr)
	{
		FileDocGia << TreeAVLDocGia->DocGia.MaThe << std::endl;
		FileDocGia << TreeAVLDocGia->DocGia.Ho << std::endl;
		FileDocGia << TreeAVLDocGia->DocGia.Ten << std::endl;
		FileDocGia << TreeAVLDocGia->DocGia.Phai << std::endl;
		FileDocGia << TreeAVLDocGia->DocGia.TrangThai << std::endl;
		WriteDSMuonTra(FileMuonTra, TreeAVLDocGia);
		if (TreeAVLDocGia->left != nullptr)
			WriteDG(FileDocGia, FileMuonTra, TreeAVLDocGia->left);
		if (TreeAVLDocGia->right != nullptr)
			WriteDG(FileDocGia, FileMuonTra, TreeAVLDocGia->right);
	}
}

void WriteDataDocGiaToFile(NodeTheDocGia *&TreeAVLDocGia)
{
	DSDG.n = 0;
	GetFromTree(TreeAVLDocGia, DSDG);
	fstream FileDocGia, FileMuonTra;
	FileDocGia.open("data_docgia.txt", ios::out);
	if (!FileDocGia.is_open())
	{
		printf("Loi mo FileDocGia de ghi \n");
		return;
	}

	FileMuonTra.open("data_muontra.txt", ios::out);
	if (!FileMuonTra.is_open())
	{
		printf("Loi mo FileMuonTra de ghi \n");
		return;
	}
	FileDocGia << DSDG.n << std::endl;
	WriteDG(FileDocGia, FileMuonTra, TreeAVLDocGia);
}

void WriteDataToFile()
{
	WriteDataDauSachToFile(DSDS);
	WriteDataDocGiaToFile(TreeAVLDocGia);
	std::cout << "Write Data Successfull!" << std::endl;
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

void XoaDocGiaEvent()
{
	ButtonEffect(ButtonDongY);
	ButtonEffect(ButtonHuyBo);
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (ButtonDongY.isMouseHover(mouseX, mouseY))
		{
			if (DSDG.nodes[CurrentItem - 1]->DS_MT->First != nullptr)
				ThongBao("KHONG THE XOA", 400, 150, ButtonDocGia.ID);
			else
			{
				TreeAVLDocGia = deleteNode(TreeAVLDocGia, DSDG.nodes[CurrentItem - 1]->MaThe);
				CurrentItem = -1;
				ThongBao("XOA THANH CONG", 400, 150, ButtonDocGia.ID);
			}
		}
		else if (ButtonHuyBo.isMouseHover(mouseX, mouseY))
			SetMenuSelect(ButtonDocGia.ID);
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
			CurrentPage = 1;
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
			ButtonTemp = nullptr;
			if (strlen(ButtonSuaMaThe.UserInput) == 0 ||
				strlen(ButtonSuaHo.UserInput) == 0 ||
				strlen(ButtonSuaTen.UserInput) == 0 ||
				strlen(ButtonSuaPhai.UserInput) == 0 ||
				strlen(ButtonSuaTrangThai.UserInput) == 0)
				ThongBao("KHONG DUOC DE TRONG");
			else
			{
				TheDocGia DocGia(atoi(ButtonSuaMaThe.UserInput), ButtonSuaHo.UserInput, ButtonSuaTen.UserInput, atoi(ButtonSuaPhai.UserInput), atoi(ButtonSuaTrangThai.UserInput), DSDG.nodes[CurrentItem - 1]->DS_MT, DSDG.nodes[CurrentItem - 1]->TongSoLuong);
				updateNode(TreeAVLDocGia, DocGia);
				ThongBao("SUA THANH CONG", 400, 150, ButtonDocGia.ID);
			}
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
			if (strlen(ButtonThemMaThe.UserInput) == 0 ||
				strlen(ButtonThemHo.UserInput) == 0 ||
				strlen(ButtonThemTen.UserInput) == 0 ||
				strlen(ButtonThemPhai.UserInput) == 0 ||
				strlen(ButtonThemTrangThai.UserInput) == 0)
				ThongBao("KHONG DUOC DE TRONG");
			else if (DSDG.n == MAX_SIZE_LIST_DOC_GIA)
				ThongBao("DOC GIA DA DAT DEN GIOI HAN");
			else
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
	else if (CurrentMenuId == ButtonXoaDMS.ID)
		XoaDMSEvent();
	else if (CurrentMenuId == ButtonSuaDMS.ID)
		SuaDMSEvent();
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

void FreeMemory(){
	FreeMemory_DS_DMS(DSDS, ListSearchDauSach, DSDMS);
	FreeMemory_DG_MT(TreeAVLDocGia, DSDG, DSMT, DS10, DSQH);
}



int main()
{
	initwindow(w, h, AppTitle);
	DrawMenu();
	GetDataFromFile();
	while (1)
	{
		Event();
		if (isExit)
			break;
		delay(50);
	}
	// WriteDataToFile();
	// FreeMemory();
	closegraph();
	return 0;
}

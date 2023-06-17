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
void FreeMemory()
{
	FreeMemory_DS_DMS(DSDS, ListSearchDauSach, DSDMS);
	FreeMemory_DG_MT(TreeAVLDocGia, DSDG, DSMT, DS10, DSQH);
	cout << "FreeMemory" << endl;
}

int main()
{
	initwindow(w, h, AppTitle);
	DrawMenu();
	GetDataFromFile();
	// InDMS();
	while (1)
	{
		Event();
		if (isExit)
			break;
		delay(50);
	}
	WriteDataToFile();
	FreeMemory();
	closegraph();
	return 0;
}

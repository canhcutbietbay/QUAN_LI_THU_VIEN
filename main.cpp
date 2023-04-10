#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include "time.h"
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include "StructDanhMucSach.h"
#include "StructDauSach.h"
#include "StructMuonTra.h"
#include "StructTheDocGia.h"
//
using namespace std;
//
#define getch() _getch()
void clrscr()
{
  system("cls");
}
//
DS_DauSach DSDS; // global
void GetDataDauSachFromFile(DS_DauSach &DSDS)
{
  fstream FileDauSach;
  FileDauSach.open("data_dausach.txt", ios::in);
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
    InsertLastDauSach(DSDS, dauSach);
  }
  FileDauSach.close();
}
//
void InDocGiaTheoMaDocGia(NodeTheDocGia *&TreeAVLDocGia);

NodeTheDocGia *TreeAVLDocGia;
DSDocGia DSDG;
void GetDataDocGiaFromFile(NodeTheDocGia *&TreeAVLDocGia)
{
  fstream FileDocGia;
  FileDocGia.open("data_docgia.txt", ios::in);
  if (!FileDocGia.is_open())
  {
    printf("Loi mo File de doc \n");
    return;
  }
  string data;
  int n;
  FileDocGia >> n;
  FileDocGia.ignore();
  for (int i = 0; i < n; i++)
  {
    TheDocGia *theDocGia = new TheDocGia;
    getline(FileDocGia, data);
    theDocGia->MaThe = atoi(data.c_str());
    ArrMTfromFile(mathe, theDocGia->MaThe);
    getline(FileDocGia, data);
    strcpy(theDocGia->Ho, data.c_str());
    getline(FileDocGia, data);
    strcpy(theDocGia->Ten, data.c_str());
    getline(FileDocGia, data);
    theDocGia->Phai = atoi(data.c_str());
    getline(FileDocGia, data);
    theDocGia->TrangThai = atoi(data.c_str());
    DSDG.InsertLastDocGia(DSDG, theDocGia);
    if (i == 0)
    {
      TreeAVLDocGia = Create_AVLTree(theDocGia);
      continue;
    }
    InsertDocGia(TreeAVLDocGia, theDocGia);
  }
  FileDocGia.close();
}
//
void GetDataFromFile()
{
  GetDataDauSachFromFile(DSDS);
  GetDataDocGiaFromFile(TreeAVLDocGia);
}

void WriteData(fstream &FileDocGia, NodeTheDocGia *&TreeAVLDocGia)
{
  if (TreeAVLDocGia != nullptr)
  {
    FileDocGia << TreeAVLDocGia->DocGia.MaThe << endl;
    FileDocGia << TreeAVLDocGia->DocGia.Ho << endl;
    FileDocGia << TreeAVLDocGia->DocGia.Ten << endl;
    FileDocGia << TreeAVLDocGia->DocGia.Phai << endl;
    FileDocGia << TreeAVLDocGia->DocGia.TrangThai << endl;
    if (TreeAVLDocGia->left != nullptr)
      WriteData(FileDocGia, TreeAVLDocGia->left);
    if (TreeAVLDocGia->right != nullptr)
      WriteData(FileDocGia, TreeAVLDocGia->right);
  }
}

void WriteDataDocGiaToFile(NodeTheDocGia *&TreeAVLDocGia)
{
  fstream FileDocGia;
  FileDocGia.open("data_docgia.txt", ios::out);
  if (!FileDocGia.is_open())
  {
    printf("Loi mo File de doc \n");
    return;
  }
  FileDocGia << DSDG.n << endl;
  WriteData(FileDocGia, TreeAVLDocGia);
  FileDocGia.close();
}

void WriteDataDauSachToFile(DS_DauSach DSDS)
{
  fstream FileDauSach;
  FileDauSach.open("data_dausach.txt", ios::out);
  if (!FileDauSach.is_open())
  {
    printf("Loi mo File de doc \n");
    return;
  }
  FileDauSach << DSDS.n << endl;
  for (int i = 0; i < DSDS.n; ++i){
    FileDauSach << DSDS.nodes[i] ->ISBN << endl;
    FileDauSach << DSDS.nodes[i] ->TenSach << endl;
    FileDauSach << DSDS.nodes[i] ->SoTrang << endl;
    FileDauSach << DSDS.nodes[i] ->TacGia << endl;
    FileDauSach << DSDS.nodes[i] ->NXB << endl;
    FileDauSach << DSDS.nodes[i] ->TenSach << endl;
  }
  FileDauSach.close();
}

void WriteDataToFile()
{
  WriteDataDocGiaToFile(TreeAVLDocGia);
  WriteDataDauSachToFile(DSDS);
}
//
void Menu()
{
  cout << "1. Them doc gia" << endl;
  cout << "2. Xoa doc gia" << endl;
  cout << "3. Hieu chinh doc gia" << endl;
  cout << "4. In doc gia ten-ho" << endl;
  cout << "5. In doc gia theo ma doc gia" << endl;
  cout << "6. Them dau sach moi" << endl;
  cout << "7. In danh sach dau sach" << endl;
  cout << "99. Thoat" << endl;
}
//
int ChonMenu()
{
  int n = 0;
  cout << "\n\nMoi chon menu: ";
  cin >> n;
  if (n > 0 || n < 99)
    return n;
  else
    return ChonMenu();
}
//
void InDanhSachDauSach(DS_DauSach &DSDS)
{
  for (int i = 0; i < DSDS.n; i++)
  {
    cout << DSDS.nodes[i]->ISBN << "||" << DSDS.nodes[i]->TenSach << "||" << DSDS.nodes[i]->SoTrang << "||" << DSDS.nodes[i]->TacGia << "||" << DSDS.nodes[i]->NXB << "||" << DSDS.nodes[i]->TheLoai << endl;
  }
}

void ThemDauSachMoi(DS_DauSach &DSDS)
{
  char ISBN[15], TenSach[25], TacGia[25], TheLoai[25];
  int SoTrang, NXB;
  cin.ignore();
  cout << "Nhap ISBN:";
  cin.getline(ISBN, 15);
  while (TimDauSach(DSDS, ISBN) != nullptr)
  {
    cout << "ISBN da ton tai" << endl;
    cout << "Nhap ISBN:";
    cin.getline(ISBN, 15);
  }
  cout << "Nhap ten sach:";
  cin.getline(TenSach, 25);
  cout << "Nhap tac gia:";
  cin.getline(TacGia, 25);
  cout << "Nhap the loai:";
  cin.getline(TheLoai, 25);
  cout << "Nhap so trang:";
  cin >> SoTrang;
  cout << "Nhap nha xuat ban:";
  cin >> NXB;
  DauSach *dausach = new DauSach(ISBN, TenSach, TacGia, TheLoai, SoTrang, NXB);
  ThemDauSach(DSDS, dausach);
  cout << "Them dau sach thanh cong" << endl;
}

void InDocGiaTheoMaDocGia(NodeTheDocGia *&TreeAVLDocGia) // Inorder
{
  if (TreeAVLDocGia != NULL)
  {
    InDocGiaTheoMaDocGia(TreeAVLDocGia->left);
    cout << TreeAVLDocGia->DocGia.MaThe << "||" << TreeAVLDocGia->DocGia.Ho << "||" << TreeAVLDocGia->DocGia.Ten << "||" << TreeAVLDocGia->DocGia.Phai << "||" << TreeAVLDocGia->DocGia.TrangThai << endl;
    InDocGiaTheoMaDocGia(TreeAVLDocGia->right);
  }
}

void InDocGiaTheoTenDocGia(DSDocGia &DSDG)
{
  for (int i = 0; i < DSDG.n; ++i)
  {
    cout << DSDG.nodes[i]->MaThe << "||" << DSDG.nodes[i]->Ho << "||" << DSDG.nodes[i]->Ten << "||" << DSDG.nodes[i]->Phai << "||" << DSDG.nodes[i]->TrangThai << endl;
  }
}

void ThemDocGiaMoi()
{
  char ho[25], ten[11];
  int phai = 0, trang_thai = 0;
  cin.ignore();
  cout << "Nhap ho va ten den:";
  cin.getline(ho, 20);
  cout << "Nhap ten:";
  cin.getline(ten, 11);
  cout << "Phai (0-Nam, 1 - Nu):";
  cin >> phai;
  cout << "Trang thai (0-Khoa, 1-Hoat dong): ";
  cin >> trang_thai;
  TheDocGia *theDocGia = new TheDocGia(ho, ten, phai, trang_thai);
  InsertDocGia(TreeAVLDocGia, theDocGia);
  DSDG.InsertLastDocGia(DSDG, theDocGia);
  cout << "Them thanh cong" << endl;
}
//
void XuLyMenu();
void BackToMenu()
{
  Sleep(1000);
  char c;
  cout << "Nhan Enter de tro ve menu chinh!" << endl;
  c = getch();
  if (c == 13)
  {
    clrscr();
    Menu();
    XuLyMenu();
  }
  else
  {
    clrscr();
    BackToMenu();
  }
}

void XuLyMenu()
{
  int input = ChonMenu();
  switch (input)
  {
  case 1:
    clrscr();
    ThemDocGiaMoi();
    BackToMenu();
    break;
  case 2:
    clrscr();
    cout << "2" << endl;
    break;
  case 3:
    clrscr();
    cout << "3" << endl;
    break;
  case 4:
    clrscr();
    DSDG.SortDocGiaTheoTen(0, DSDG.n - 1);
    InDocGiaTheoTenDocGia(DSDG);
    BackToMenu();
    break;
  case 5:
    clrscr();
    InDocGiaTheoMaDocGia(TreeAVLDocGia);
    BackToMenu();
    break;
  case 6:
    clrscr();
    ThemDauSachMoi(DSDS);
    BackToMenu();
    break;
  case 7:
    clrscr();
    InDanhSachDauSach(DSDS);
    BackToMenu();
    break;
  case 99:
    WriteDataToFile();
    cout << "Write data successfully!" << endl;
    cout << "Thoat!!!\n";
    exit(1);
    break;
  }
}
// MAIN
int main()
{
  GetDataFromFile();
  Menu();
  XuLyMenu();
  return 0;
}
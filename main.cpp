#include <iostream>
#include <fstream>
#include <string.h>
#include "StructDanhMucSach.h"
#include "StructDauSach.h"
#include "StructTheDocGia.h"
#include "StructMuonTra.h"
#include <iomanip>
//
using namespace std;
//
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
NodeTheDocGia TreeAVLDocGia;
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
  TheDocGia *theDocGia = new TheDocGia;
  for (int i = 0; i < n; i++)
  {
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
  // GetDataDocGiaFromFile();
}
//
void Menu()
{
  cout << "1. Them doc gia" << endl;
  cout << "2. Xoa doc gia" << endl;
  cout << "3. Hieu chinh doc gia" << endl;
  cout << "4. In doc gia ten-ho" << endl;
  cout << "5. In doc gia theo ma doc gia" << endl;
  cout << "6. Nhap thong tin dau sach" << endl;
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
//
void XuLyMenu()
{
  int input = ChonMenu();
  switch (input)
  {
  case 1:
    clrscr();
    cout << "1" << endl;
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
    cout << "4" << endl;
    break;
  case 5:
    clrscr();
    cout << "5" << endl;
    break;
  case 6:
    clrscr();
    cout << "6" << endl;
    break;
  case 7:
    clrscr();
    InDanhSachDauSach(DSDS);
    break;
  case 99:
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
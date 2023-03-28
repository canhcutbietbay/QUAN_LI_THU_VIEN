#include <iostream>

using namespace std;

void clrscr()
{
  system("cls");
}

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
    cout << "7" << endl;
    break;
  case 99:
    cout << "Thoat!!!\n";
    exit(1);
    break;
  }
}
int main()
{
  Menu();
  XuLyMenu();
  return 0;
}
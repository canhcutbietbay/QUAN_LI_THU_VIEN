std::string GetNumberFromMaSach(std::string MaSach)
{

	std::string res = MaSach.substr(MaSach.length() - 2, 2);
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

void InDanhSachDauSach(DS_DauSach &DSDS)
{
	for (int i = 0; i < DSDS.n; i++)
	{
		std::cout << DSDS.nodes[i]->ISBN << "||" << DSDS.nodes[i]->TenSach << "||" << DSDS.nodes[i]->SoTrang << "||" << DSDS.nodes[i]->TacGia << "||" << DSDS.nodes[i]->NXB << "||" << DSDS.nodes[i]->TheLoai << std::endl;
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
	CurrentMenuId = ButtonOKThongBao.ID;
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

void ClearEditButtonData(EditButton &Button)
{
	memset(Button.UserInput, 0, sizeof Button.UserInput);
	Button.draw();
}

void CLearLastCharInput()
{
	if (ButtonTemp != nullptr)
	{
		ButtonTemp->UserInput[strlen(ButtonTemp->UserInput)] = '\0';
		ButtonTemp->draw();
	}
}

void MoveToNextEditTextButton()
{
	CLearLastCharInput();
	if (CurrentMenuId == ButtonThemDauSach.ID)
	{
		if (ButtonTemp->ID == ButtonThemISBN.ID)
			ButtonTemp = &ButtonThemTenSach;
		else if (ButtonTemp->ID == ButtonThemTenSach.ID)
			ButtonTemp = &ButtonThemSoTrang;
		else if (ButtonTemp->ID == ButtonThemSoTrang.ID)
			ButtonTemp = &ButtonThemTacGia;
		else if (ButtonTemp->ID == ButtonThemTacGia.ID)
			ButtonTemp = &ButtonThemNXB;
		else if (ButtonTemp->ID == ButtonThemNXB.ID)
			ButtonTemp = &ButtonThemTheLoai;
	}
	else if (CurrentMenuId == ButtonSuaDMS.ID)
	{
		if (ButtonTemp->ID == ButtonSuaTrangThaiSach.ID)
			ButtonTemp = &ButtonSuaViTriSach;
	}
	else if (CurrentMenuId == ButtonSuaDauSach.ID)
	{
		if (ButtonTemp->ID == ButtonSuaTenSach.ID)
			ButtonTemp = &ButtonSuaSoTrang;
		else if (ButtonTemp->ID == ButtonSuaSoTrang.ID)
			ButtonTemp = &ButtonSuaTacGia;
		else if (ButtonTemp->ID == ButtonSuaTacGia.ID)
			ButtonTemp = &ButtonSuaNXB;
		else if (ButtonTemp->ID == ButtonSuaNXB.ID)
			ButtonTemp = &ButtonSuaTheLoai;
	}
	else if (CurrentMenuId == ButtonThemDocGia.ID)
	{
		if (ButtonTemp->ID == ButtonThemHo.ID)
			ButtonTemp = &ButtonThemTen;
		else if (ButtonTemp->ID == ButtonThemTen.ID)
			ButtonTemp = &ButtonThemPhai;
		else if (ButtonTemp->ID == ButtonThemPhai.ID)
			ButtonTemp = &ButtonThemTrangThai;
	}
	else if (CurrentMenuId == ButtonSuaDocGia.ID)
	{
		if (ButtonTemp->ID == ButtonSuaHo.ID)
			ButtonTemp = &ButtonSuaTen;
		else if (ButtonTemp->ID == ButtonSuaTen.ID)
			ButtonTemp = &ButtonSuaPhai;
		else if (ButtonTemp->ID == ButtonSuaPhai.ID)
			ButtonTemp = &ButtonSuaTrangThai;
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
	else if (CurrentMenuId == 99)
	{
		if (ButtonTemp->ID == ButtonThemViTriSach.ID)
			return true;
	}
	else if (CurrentMenuId == ButtonSuaDMS.ID)
	{
		if (ButtonTemp->ID == ButtonSuaTrangThaiSach.ID)
		{
			if (c >= 48 && c <= 50 && strlen(ButtonTemp->UserInput) < 1)
				return true;
		}
		else if (ButtonTemp->ID == ButtonSuaViTriSach.ID)
			return true;
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
		if (ButtonTemp->ID == ButtonSuaTenSach.ID)
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

void InDMS()
{
	for (int i = 0; i < DSDS.n; i++)
	{
		std::cout << DSDS.nodes[i]->TenSach << std::endl;
		DM_Sach *temp = DSDS.nodes[i]->DS_Sach;
		for (temp; temp != nullptr; temp = temp->next)
		{
			std::cout << temp->sach->id << " " << temp->sach->MaSach << " " << temp->sach->TrangThai << " " << temp->sach->ViTri << std::endl;
		}
		std::cout << "-------------------" << std::endl;
	}
}

void InMuonTra(NodeTheDocGia *&TreeAVLDocGia) // Inorder
{
	if (TreeAVLDocGia != nullptr)
	{
		InMuonTra(TreeAVLDocGia->left);
		NodeMuonTra *node = TreeAVLDocGia->DocGia.DS_MT->First;
		std::cout << TreeAVLDocGia->DocGia.Ten << std::endl;
		for (node; node != nullptr; node = node->Right)
		{
			std::cout << node->value->MaSach << " " << node->value->TrangThai << std::endl;
		}
		std::cout << "--------------------" << std::endl;
		InMuonTra(TreeAVLDocGia->right);
	}
}

void InQuaHan()
{
	DSQH.n = 0;
	GetFromTree(TreeAVLDocGia, DSQH, DSDS);
	for (int i = 0; i < DSQH.n; ++i)
	{
		std::cout << DSQH.nodes[i]->MaSach << " " << DSQH.nodes[i]->SoNgayQuaHan << std::endl;
	}
}

void InTop10()
{
	DS10.n = 0;
	GetTop10(DSDS, DS10);
	for (int i = 0; i < DS10.n; ++i)
	{
		std::cout << DS10.nodes[i]->ISBN << " " << DS10.nodes[i]->SoLuotMuon << std::endl;
	}
}

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
	else if (MenuID == ButtonXoaDMS.ID)
		RunXoaDMS();
	else if (MenuID == ButtonSuaDMS.ID)
		RunSuaDMS();
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
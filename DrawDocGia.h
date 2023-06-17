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
	std::string temp;
	TotalPage = ceil(DSDG.n * 1.0 / 10);
	if (TotalPage == 0)
		TotalPage = 1;
	temp = std::to_string(CurrentPage);
	strcat(NumOfPage, temp.c_str());
	strcat(NumOfPage, "/");
	temp = std::to_string(TotalPage);
	strcat(NumOfPage, temp.c_str());
	outtextxy(w / 2 - textwidth(NumOfPage) / 2, Y_DS * 5 + 10, NumOfPage);
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
	std::string temp;
	TotalPage = ceil(DSMT.n * 1.0 / 10);
	if (TotalPage == 0)
		TotalPage = 1;
	temp = std::to_string(SubCurrentPage);
	strcat(NumOfPage, temp.c_str());
	strcat(NumOfPage, "/");
	temp = std::to_string(TotalPage);
	strcat(NumOfPage, temp.c_str());
	outtextxy(w / 2 - textwidth(NumOfPage) / 2, Y_DS * 5 + 10, NumOfPage);
	DrawItemMuonTra(DSMT);
	DrawSelectedItemMuonTra(DSMT);
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
		ClearScreenXY(XXDG[3] + 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2) - 10, XXDG[4] - 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 + textheight("A") / 2) + 10);
		ClearScreenXY(XXDG[4] + 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2) - 10, XXDG[5] - 10, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 + textheight("A") / 2) + 10);
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
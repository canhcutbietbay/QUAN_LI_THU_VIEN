void SearchDauSach(char TenSach[])
{
	ListSearchDauSach.n = 0;
	CurrentItem = -1;
	std::string temp;
	for (int i = 0; i < DSDS.n; ++i)
	{
		temp = DSDS.nodes[i]->TenSach;
		if (temp.find(TenSach) != std::string::npos)
			ThemDauSach(ListSearchDauSach, DSDS.nodes[i]);
	}
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
	std::string temp;
	TotalPage = ceil(DSDS.n * 1.0 / 10);
	if (TotalPage == 0)
		TotalPage = 1;
	temp = std::to_string(CurrentPage);
	strcat(NumOfPage, temp.c_str());
	strcat(NumOfPage, "/");
	temp = std::to_string(TotalPage);
	strcat(NumOfPage, temp.c_str());
	outtextxy(w / 2 - textwidth(NumOfPage) / 2, Y_DS * 5 + 10, NumOfPage);
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
	char Title[][25] = {"MA SACH", "TRANG THAI", "VI TRI"};
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
	std::string temp;
	TotalPage = ceil(dauSach->TongSoLuong * 1.0 / 10);
	if (TotalPage == 0)
		TotalPage = 1;
	temp = std::to_string(SubCurrentPage);
	strcat(NumOfPage, temp.c_str());
	strcat(NumOfPage, "/");
	temp = std::to_string(TotalPage);
	strcat(NumOfPage, temp.c_str());
	outtextxy(w / 2 - textwidth(NumOfPage) / 2, Y_DS * 5 + 10, NumOfPage);
	DrawItemDMS(DSDMS);
	DrawSelectedItemDMS(DSDMS);
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
			outtextxy(XDMS[0] + (XDMS[1] - XDMS[0]) / 2 - textwidth(DSDMS.nodes[i - 1]->MaSach) / 2, (Y_DS + ContentHeight * (i - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSDMS.nodes[i - 1]->MaSach);
			outtextxy(XDMS[1] + (XDMS[2] - XDMS[1]) / 2 - textwidth(TrangThai[DSDMS.nodes[i - 1]->TrangThai]) / 2, (Y_DS + ContentHeight * (i - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), TrangThai[DSDMS.nodes[i - 1]->TrangThai]);
			outtextxy(XDMS[2] + (XDMS[3] - XDMS[2]) / 2 - textwidth(DSDMS.nodes[i - 1]->ViTri) / 2, (Y_DS + ContentHeight * (i - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSDMS.nodes[i - 1]->ViTri);
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
		outtextxy(XDMS[0] + (XDMS[1] - XDMS[0]) / 2 - textwidth(DSDMS.nodes[SubCurrentItem - 1]->MaSach) / 2, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSDMS.nodes[SubCurrentItem - 1]->MaSach);
		outtextxy(XDMS[1] + (XDMS[2] - XDMS[1]) / 2 - textwidth(TrangThai[DSDMS.nodes[SubCurrentItem - 1]->TrangThai]) / 2, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), TrangThai[DSDMS.nodes[SubCurrentItem - 1]->TrangThai]);
		outtextxy(XDMS[2] + (XDMS[3] - XDMS[2]) / 2 - textwidth(DSDMS.nodes[SubCurrentItem - 1]->ViTri) / 2, (Y_DS + ContentHeight * (SubCurrentItem - 10 * (SubCurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DSDMS.nodes[SubCurrentItem - 1]->ViTri);
	}
}

void RunThemDMS()
{
	CurrentAddDMS = 1;
	TotalAddDMS = -1;
	const int width = w / 3, height = 300;
	char Title[50] = "THEM SACH";
	ClearScreenXY(w / 2 - width / 2, h / 2 - height / 2, w / 2 + width / 2, h / 2 + height / 2);
	setcolor(WHITE);
	rectangle(w / 2 - width / 2, h / 2 - height / 2, w / 2 + width / 2, h / 2 + height / 2);
	settextstyle(BOLD_FONT, HORIZ_DIR, 5);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy(w / 2 - textwidth(Title) / 2, h / 2 - height / 2 + 10, Title);
	ButtonThemSoLuong.draw();
	ButtonDongY.Init(0, w / 2 - DefaultButtonWidth / 2 - w / 12, h / 2 + height / 2 - DefaultButtonHeight - 10, DefaultButtonWidth, DefaultButtonHeight, "DONG Y", 0);
	ButtonHuyBo.Init(0, w / 2 - DefaultButtonWidth / 2 + w / 12, h / 2 + height / 2 - DefaultButtonHeight - 10, DefaultButtonWidth, DefaultButtonHeight, "HUY BO", 0);
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

void RunXoaDMS()
{
	const int width = 500, height = 150;
	char Data[] = "SACH SE DUOC XOA";
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

void RunSuaDMS()
{
	const int width = w / 3, height = h / 8;
	char Title[50] = "SUA SACH";
	ClearScreenXY(w / 2 - width / 2, h / 3 - height / 2, w / 2 + width / 2, h * 2 / 3 + height / 2);
	setcolor(WHITE);
	rectangle(w / 2 - width / 2, h / 3 - height / 2, w / 2 + width / 2, h * 2 / 3 + height / 2);
	settextstyle(BOLD_FONT, HORIZ_DIR, 5);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy(w / 2 - textwidth(Title) / 2, h / 3 - height / 2 + 10, Title);
	char temp[10];
	strcpy(ButtonSuaMaSach.UserInput, DSDMS.nodes[SubCurrentItem - 1]->MaSach);
	ButtonSuaMaSach.draw();
	itoa(DSDMS.nodes[SubCurrentItem - 1]->TrangThai, temp, 10);
	strcpy(ButtonSuaTrangThaiSach.UserInput, temp);
	ButtonSuaTrangThaiSach.draw();
	strcpy(ButtonSuaViTriSach.UserInput, DSDMS.nodes[SubCurrentItem - 1]->ViTri);
	ButtonSuaViTriSach.draw();
	ButtonDongY.Init(0, w / 3 + w / 9 - DefaultButtonWidth / 2, h / 2 - h / 4 + 160 + DefaultButtonHeight * 6, DefaultButtonWidth, DefaultButtonHeight, "DONG Y", 0);
	ButtonHuyBo.Init(0, w / 3 + w / 6 + DefaultButtonWidth / 2, h / 2 - h / 4 + 160 + DefaultButtonHeight * 6, DefaultButtonWidth, DefaultButtonHeight, "HUY BO", 0);
	ButtonDongY.draw();
	ButtonHuyBo.draw();
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

void RunSuaDauSach()
{
	const int width = w / 3, height = h / 4;
	char Title[50] = "SUA DAU SACH";
	ClearScreenXY(w / 2 - width / 2, h / 3 - height / 2, w / 2 + width / 2, h * 2 / 3 + height / 2);
	setfillstyle(SOLID_FILL, BLUE);
	rectangle(w / 2 - width / 2, h / 3 - height / 2, w / 2 + width / 2, h * 2 / 3 + height / 2);
	settextstyle(BOLD_FONT, HORIZ_DIR, 5);
	setcolor(TEXT_TITLE_COLOR);
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
		ButtonSuaTheLoai.draw();
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

// -------------------Event----------------//

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
		else if (ButtonXoaDMS.isMouseHover(mouseX, mouseY))
		{
			if (SubCurrentItem == -1)
				ThongBao("CHON 1 QUYEN SACH");
			else
				SetMenuSelect(ButtonXoaDMS.ID);
		}
		else if (ButtonSuaDMS.isMouseHover(mouseX, mouseY))
		{
			if (SubCurrentItem == -1)
				ThongBao("CHON 1 QUYEN SACH");
			else
				SetMenuSelect(ButtonSuaDMS.ID);
		}
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
				else if (TotalAddDMS > MAX_SIZE_LIST_DMS - DSDMS.n)
				{
					char ConLai[5], mess[] = "CHI CON LAI: ";
					itoa(MAX_SIZE_LIST_DMS - DSDMS.n, ConLai, 10);
					strcat(mess, ConLai);
					strcat(mess, " VI TRI");
					ThongBao(mess);
				}
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
			if (strlen(ButtonThemViTriSach.UserInput) != 0)
			{

				Sach *sach = new Sach;
				strcpy(sach->MaSach, ButtonThemMaSach.UserInput);
				sach->TrangThai = atoi(ButtonThemTrangThaiSach.UserInput);
				strcpy(sach->ViTri, ButtonThemViTriSach.UserInput);
				std::string str(sach->MaSach);
				sach->id = atoi(GetNumberFromMaSach(str).c_str());
				sach->SoLuotMuon = 0;
				ClearEditButtonData(ButtonThemViTriSach);
				ButtonTemp = nullptr;
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
			else
				ThongBao("KHONG DUOC DE TRONG");
		}
		else if (ButtonThemViTriSach.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonThemViTriSach;
		}
	}
}

void XoaDMSEvent()
{
	ButtonEffect(ButtonDongY);
	ButtonEffect(ButtonHuyBo);
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		if (ButtonDongY.isMouseHover(mouseX, mouseY))
		{
			if (DSDMS.nodes[SubCurrentItem - 1]->SoLuotMuon == 0)
			{
				int code;
				if (strlen(ButtonSearchDauSach.UserInput) == 0)
					code = DeleteSach(DSDS.nodes[CurrentItem - 1]->DS_Sach, DSDMS.nodes[SubCurrentItem - 1]->MaSach);
				else
					code = DeleteSach(DSDS.nodes[TimPosDauSach(DSDS, ListSearchDauSach.nodes[CurrentItem - 1]->ISBN)]->DS_Sach, DSDMS.nodes[SubCurrentItem - 1]->MaSach);
				if (code == 1)
				{
					DSDS.nodes[CurrentItem - 1]->TongSoLuong--;
					SubCurrentItem = -1;
				}
				ThongBao(XoaSachCode[code], 400, 150, ButtonXemDauSach.ID);
			}
			else
				ThongBao("KHONG THE XOA", 400, 150, ButtonXemDauSach.ID);
		}
		else if (ButtonHuyBo.isMouseHover(mouseX, mouseY))
			SetMenuSelect(ButtonXemDauSach.ID);
	}
}

void SuaDMSEvent()
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
		else if (ButtonSuaTrangThaiSach.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonSuaTrangThaiSach;
		}
		else if (ButtonSuaViTriSach.isMouseHover(mouseX, mouseY))
		{
			CLearLastCharInput();
			ButtonTemp = &ButtonSuaViTriSach;
		}
		else if (ButtonDongY.isMouseHover(mouseX, mouseY))
		{
			ButtonTemp = nullptr;
			if (strlen(ButtonSuaTrangThaiSach.UserInput) == 0 || strlen(ButtonSuaViTriSach.UserInput) == 0)
				ThongBao("KHONG DUOC DE TRONG");
			else if (DSDMS.nodes[SubCurrentItem - 1]->TrangThai == 1)
				ThongBao("KHONG THE SUA TRANG THAI CUA SACH", 600, 150, -1);
			else if (DSDMS.nodes[SubCurrentItem - 1]->TrangThai == 0)
			{
				int temp = atoi(ButtonSuaTrangThaiSach.UserInput);
				if (temp == 1)
					ThongBao("CHI CO THE SUA TU 0:CO THE CHO MUON -> 2: SACH DA THANH LY", 700, 150, -1);
				else
				{
					Sach sach(ButtonSuaMaSach.UserInput, temp, ButtonSuaViTriSach.UserInput);
					int code = 0;
					if (strlen(ButtonSearchDauSach.UserInput) == 0)
						code = UpdateSach(DSDS.nodes[CurrentItem - 1]->DS_Sach, sach);
					else
						code = UpdateSach(ListSearchDauSach.nodes[CurrentItem - 1]->DS_Sach, sach);
					ThongBao(SuaSachCode[code], 400, 150, ButtonXemDauSach.ID);
				}
			}
		}
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
			ButtonTemp = nullptr;
			// Them Dau Sach moi
			if (strlen(ButtonThemISBN.UserInput) == 0 ||
				strlen(ButtonThemTenSach.UserInput) == 0 ||
				strlen(ButtonThemTacGia.UserInput) == 0 ||
				strlen(ButtonThemTheLoai.UserInput) == 0 ||
				strlen(ButtonThemSoTrang.UserInput) == 0 ||
				strlen(ButtonThemNXB.UserInput) == 0)
				ThongBao("KHONG DUOC DE TRONG");
			else if (DSDS.n == MAX_SIZE_LIST_DAU_SACH)
				ThongBao("DAU SACH DA DAT DEN GIOI HAN");
			else if (TimDauSach(DSDS, ButtonThemISBN.UserInput) == nullptr)
			{
				DauSach *dausach = new DauSach(ButtonThemISBN.UserInput, ButtonThemTenSach.UserInput, ButtonThemTacGia.UserInput, ButtonThemTheLoai.UserInput, atoi(ButtonThemSoTrang.UserInput), atoi(ButtonThemNXB.UserInput));
				ThemDauSach(DSDS, dausach);
				ClearEditButtonData(ButtonThemISBN);
				ClearEditButtonData(ButtonThemTenSach);
				ClearEditButtonData(ButtonThemSoTrang);
				ClearEditButtonData(ButtonThemTacGia);
				ClearEditButtonData(ButtonThemNXB);
				ClearEditButtonData(ButtonThemTheLoai);
				ThongBao("THEM DAU SACH THANH CONG");
				SearchDauSach(ButtonSearchDauSach.UserInput);
			}
			else
				ThongBao("TRUNG ISBN");
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
				if (ListSearchDauSach.nodes[CurrentItem - 1]->DS_Sach == nullptr)
				{
					DeleteDauSach(DSDS, TimPosDauSach(DSDS, ListSearchDauSach.nodes[CurrentItem - 1]->ISBN));
					DeleteDauSach(ListSearchDauSach, CurrentItem - 1);
					CurrentItem = -1;
					ThongBao("XOA THANH CONG", 400, 150, ButtonDauSach.ID);
				}
				else
					ThongBao("KHONG THE XOA", 400, 150, ButtonDauSach.ID);
			}
			else
			{
				if (DSDS.nodes[CurrentItem - 1]->DS_Sach == nullptr)
				{
					DeleteDauSach(DSDS, CurrentItem - 1);
					CurrentItem = -1;
					ThongBao("XOA THANH CONG", 400, 150, ButtonDauSach.ID);
				}
				else
					ThongBao("KHONG THE XOA", 400, 150, ButtonDauSach.ID);
			}
		}
		else if (ButtonHuyBo.isMouseHover(mouseX, mouseY))
			SetMenuSelect(ButtonDauSach.ID);
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
			ButtonTemp = nullptr;
			if (strlen(ButtonSuaISBN.UserInput) == 0 ||
				strlen(ButtonSuaTenSach.UserInput) == 0 ||
				strlen(ButtonSuaTacGia.UserInput) == 0 ||
				strlen(ButtonSuaTheLoai.UserInput) == 0 ||
				strlen(ButtonSuaSoTrang.UserInput) == 0 ||
				strlen(ButtonSuaNXB.UserInput) == 0)
				ThongBao("KHONG DUOC DE TRONG");
			else
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
			}
		}
	}
}

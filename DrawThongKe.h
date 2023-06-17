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
	std::string temp;
	TotalPage = ceil(DSQH.n * 1.0 / 10);
	if (TotalPage == 0)
		TotalPage = 1;
	temp = std::to_string(CurrentPage);
	strcat(NumOfPage, temp.c_str());
	strcat(NumOfPage, "/");
	temp = std::to_string(TotalPage);
	strcat(NumOfPage, temp.c_str());
	outtextxy(w / 2 - textwidth(NumOfPage) / 2, Y_DS * 5 + 10, NumOfPage);
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

void RunTop10()
{
	ClearScreen();
	ButtonBack.draw();
	ButtonThongKeQuaHan.draw();
	ButtonThongKeTop10.draw();
	char Title[][25] = {"ISBN", "TEN SACH", "TAC GIA", "THE LOAI", "SO TRANG", "NXB", "LUOT MUON"};
	setcolor(WHITE);
	// Ve khung + title
	char title[] = "THONG KE";
	outtextxy(w / 2 - textwidth(title) / 2, textheight("A") - 10, title);
	rectangle(XT10[0], Y_DS, XT10[7], Y_DS * 5);
	line(XT10[0], Y_DS + 50, XT10[7], Y_DS + 50);
	for (int i = 0; i < 7; i++)
	{
		line(XT10[i + 1], Y_DS, XT10[i + 1], Y_DS * 5);
		outtextxy(XT10[i] + ((XT10[i + 1] - XT10[i]) / 2 - textwidth(Title[i]) / 2), (Y_DS + 25) - textheight("A") / 2, Title[i]);
	}
	DS10.n = 0;
	GetTop10(DSDS, DS10);
	DrawItemTop10(DS10);
}

void DrawItemTop10(TopList &DS10)
{
	char data[15];
	if (DS10.n == 0)
		return;
	for (int i = 1 + 10 * (CurrentPage - 1); i <= 10 + 10 * (CurrentPage - 1); i++)
	{
		if (i > DS10.n)
			break;
		line(XT10[0], (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1) + 1)), XT10[7], (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1) + 1)));
		outtextxy(XT10[0] + (XT10[1] - XT10[0]) / 2 - textwidth(DS10.nodes[i - 1]->ISBN) / 2, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DS10.nodes[i - 1]->ISBN);
		outtextxy(XT10[1] + 10, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DS10.nodes[i - 1]->TenSach);
		outtextxy(XT10[2] + 10, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DS10.nodes[i - 1]->TacGia);
		outtextxy(XT10[3] + 10, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), DS10.nodes[i - 1]->TheLoai);
		itoa(DS10.nodes[i - 1]->SoTrang, data, 10);
		outtextxy(XT10[4] + (XT10[5] - XT10[4]) / 2 - textwidth(data) / 2, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), data);
		itoa(DS10.nodes[i - 1]->NXB, data, 10);
		outtextxy(XT10[5] + (XT10[6] - XT10[5]) / 2 - textwidth(data) / 2, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), data);
		itoa(DS10.nodes[i - 1]->SoLuotMuon, data, 10);
		outtextxy(XT10[6] + (XT10[7] - XT10[6]) / 2 - textwidth(data) / 2, (Y_DS + ContentHeight * (i - 10 * (CurrentPage - 1)) + ContentHeight / 2 - textheight("A") / 2), data);
	}
}
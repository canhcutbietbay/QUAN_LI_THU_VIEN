void DrawMenu()
{
	ClearScreen();
	settextstyle(BOLD_FONT, HORIZ_DIR, 7);
	setcolor(TEXT_TITLE_COLOR);
	outtextxy(w / 2 - textwidth(AppTitle) / 2, 100, AppTitle);
	ButtonDauSach.draw();
	ButtonDocGia.draw();
	ButtonThongKe.draw();
	ButtonThongTin.draw();
	ButtonThoat.draw();
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
			CurrentItem = -1;
			CurrentPage = 1;
			SetMenuSelect(ButtonDauSach.ID);
		}
		if (ButtonDocGia.isMouseHover(mouseX, mouseY))
		{
			CurrentItem = -1;
			CurrentPage = 1;
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
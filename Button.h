struct Button
{
	int ID, xPos, yPos, Width, Height, Align;
	/* Align value
	-1: Left
	0: center
	1: right
	*/
	char Title[50];
	bool IsHover, IsChoose;
	Button() {}

	Button(int id, int x, int y, int width, int height, char title[30], int align)
	{
		ID = id;
		xPos = x;
		yPos = y;
		Width = width;
		Height = height;
		strcpy(Title, title);
		Align = align;
	}
	void Init(int id, int x, int y, int width, int height, char title[30], int align)
	{
		ID = id;
		xPos = x;
		yPos = y;
		Width = width;
		Height = height;
		strcpy(Title, title);
		Align = align;
	}
	void draw()
	{
		setfillstyle(SOLID_FILL, IsHover ? BG_BUTTON_SELECT : BG_BUTTON_DEFAULT);
		bar(xPos, yPos, xPos + Width, yPos + Height);
		settextstyle(BOLD_FONT, HORIZ_DIR, 2);
		setbkcolor(IsHover ? BG_BUTTON_SELECT : BG_BUTTON_DEFAULT);
		setcolor(IsHover ? TEXT_BUTTON_SELECT : TEXT_BUTTON_DEFAULT);
		switch (Align)
		{
		case -1:
			outtextxy(xPos + 10, yPos + (Height - textheight(Title)) / 2, Title);
			break;
		case 0:
			outtextxy(xPos + Width / 2 - textwidth(Title) / 2, yPos + (Height - textheight(Title)) / 2, Title);
			break;
		case 1:
			outtextxy(xPos + Width - textwidth(Title) - 10, yPos + (Height - textheight(Title)) / 2, Title);
			break;
		default:
			break;
		}

		setbkcolor(BG_COLOR);
	}

	bool isMouseHover(int mouseX, int mouseY)
	{
		if (mouseX >= xPos && mouseX <= xPos + Width && mouseY >= yPos && mouseY <= yPos + Height)
		{
			return true;
		}
		return false;
	}
};

// Edit Button
struct EditButton{
	int ID, xPos, yPos, Width, Height;
	char Title[30], UserInput[30], Hint[30];
	bool IsHover, IsChoose;
	
	EditButton(int id, int x, int y, int width, int height, char title[50], char userInput[50], char hint[50]){
		xPos = x; yPos = y; 
		ID = id;
		Width = width; Height = height;
		strcpy(Title, title);
		strcpy(UserInput, userInput);
		strcpy(Hint, hint);
		IsHover = false;
		IsChoose = false;
	}
	
	void draw(){
		setbkcolor(BG_COLOR);

		// Ve tieu de
		settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
		setcolor(TEXT_EDIITEXT_TITLE_COLOR);
		outtextxy(xPos, yPos+(Height-textheight("TD"))/2, Title);
		
		// Ve background 
		setfillstyle(SOLID_FILL, BG_EDITTEXT_COLOR);
		bar(xPos+150, yPos, xPos+Width, yPos+Height);

		if(strlen(UserInput) == 0){
			// Ve hint 
			setcolor(TEXT_EDIITEXT_HINT_COLOR);
			setbkcolor(BG_EDITTEXT_COLOR);
			outtextxy(xPos + 160, yPos+(Height-textheight("H"))/2, Hint);
		} else {
			// Ve noi dung nguoi dung nhap vao
			setcolor(TEXT_EDITTEXT_COLOR);
			setbkcolor(BG_EDITTEXT_COLOR);
			outtextxy(xPos + 160, yPos+(Height-textheight("C"))/2, UserInput);
			
			// if(dataFill != NULL){
			// 	int pos = toInt();
			// 	if(pos != -1) outtextxy(x+width - textwidth(dataFill[pos]) -20, y+(height-textheight("C"))/2, dataFill[pos]);
			// }
		}
		
		setbkcolor(BG_COLOR);
	}
	
	bool isMouseHover(int mouseX, int mouseY)
	{
		if (mouseX >= xPos && mouseX <= xPos + Width && mouseY >= yPos && mouseY <= yPos + Height)
		{
			return true;
		}
		return false;
	}
};
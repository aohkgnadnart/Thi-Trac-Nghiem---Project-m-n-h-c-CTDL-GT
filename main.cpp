#include <graphics.h>
#include "listMonHoc.h"
//#include <bits/stdc++.h>
const int BACKSPACE=8;
using namespace std;

//CAC HAM THIET KE GIAO DIEN//////////////////////////////////////////////////////////////////////////////////////////////////
void outtextXY(int x, int y, const string &str){
	char * cstr = new char [(int)str.length()+1];
  	std::strcpy (cstr, str.c_str());
  	outtextxy(x,y,cstr);
  	delete[] cstr;
}
void hinhChuNhatDac(int left, int top, int right, int bottom, int color){
	setfillstyle(SOLID_FILL, color);//chon mau to cho hinh chu nhat dac
	bar(left,top,right,bottom);//ve hinh chu nhat dac	
} 
void hinhChuNhatRong(int left, int top, int right, int bottom, int color){
	setcolor(color);//chon mau to cho hinh chu nhat rong
	rectangle(left,top,right,bottom);//ve hinh chu nhat dac
}
void vanBan(int x, int y,const string &text, int color, int bkcolor, int font, int charsize, int horiz, int vert){
	//horiz=0, 1, 2 hieu la van ban xuat hien ben phai, tam, trai con chay
	//vert=0, 1, 2 hieu la van ban xuat hien tren, giua, duoi con chay
	setcolor(color);//chon mau cho van ban
	setbkcolor(bkcolor);//chon mau nen cho van ban
	//chon kieu chu, co chu, HORIZ_DIR(nam ngang) trong chuong trinh nay khong co van ban nam doc
	settextstyle(font, HORIZ_DIR, charsize);
	settextjustify(horiz, vert);//vi tri hien thi cua van ban
	outtextXY(x,y,text);
}
void khungNhap(int x, int y, string &text, int font, int charsize, int horiz, int vert, int limit){
	static int temp=0;//bien co chuc nang trong viec tao dau nhap nhay
	temp=(temp+1)%20;
	if(kbhit()){
		char u=getch();
		int v=u;
		if(v==BACKSPACE && text.length()>0){
			text.push_back(u);
			vanBan(x,y, text, WHITE, WHITE, 8, 2, 0, 1);
			text.pop_back();
			text.pop_back();
			vanBan(x,y, text, BLACK, WHITE, 8, 2, 0, 1);
		}
		else if(limit==5){
			if(text.length()<5 && u>='0' && u<='9'){
				text.push_back(u);
				vanBan(x,y, text, BLACK, WHITE, 8, 2, 0, 1);
			}
		}
		else if(limit>25){
			if(text.length()<min(68, limit) && u>=32 && u<127){
				text.push_back(u);
				vanBan(x,y, text, BLACK, WHITE, 8, 2, 0, 1);
			}
		}
		else if(text.length()<min(68, limit) && ((u>='A' && u<='Z') || u=='_' || u=='-' || (u>='0' && u<='9'))){
			text.push_back(u);
			vanBan(x,y, text, BLACK, WHITE, 8, 2, 0, 1);
		}
	}
	else{
		if(temp<=10){
			text.push_back('|');
			vanBan(x,y,text,BLACK,WHITE,8,2,0,1);
			text.pop_back();
		}
		else{
			text.push_back(' ');
			vanBan(x,y,text,BLACK,WHITE,8,2,0,1);
			text.pop_back();
			vanBan(x,y,text,BLACK,WHITE,8,2,0,1);
		}
		delay(1);
	}
}
void thoatKhungNhap(int x, int y, string &text, int font, int charsize, int horiz, int vert){
	text.push_back(' ');
	vanBan(x,y,text,WHITE,WHITE,8,2,0,1);
	text.pop_back();
	vanBan(x,y,text,BLACK,WHITE,8,2,0,1);
}

//CAC SLIDE DUOC SU DUNG////////////////////////////////////////////////////////////////////////////////////////////////////////
void manHinhDangNhap();
void slideDanhSach();
void slideLopHoc();
void slideThemLop();
void slideXoaLop();
void slideSuaLop();
void slideInLop();
void slideSinhVien();
void slideTruocThemSV();
void slideThemSV(int pos_lop);
void slideXoaSV();
void slideSuaSV();
void slideXemBaiThisv();
void slideMonHoc();
void slideThemMH();
void slideXoaMH();
void slideSuaMH();
void slideCauHoi();
void slideTruocThemCH();
void slideThemCH(const string &mmh);
void slideXoaCH();
void slideTruocSuaCH();
void slideSuaCH(int id);
void slideSETUPbaithi(pSinhVien temp);
void slideTHITRACNGHIEM(pSinhVien temp,int thoigian);
void slideSauXemBaiThiSV(pDiemThi temp1);
//Cac bien toan cuc////////////////////////////////////////////////////////////////////////////////////////////////////////////
AVLtree dscauhoi;
listLop dslop;
listMH dsmonhoc;
int IDpossible=1;
//Docfile, ghi file /////////////////////////////////////////////////////////////////////////////
void write_IDpossible(){
	ofstream myfile ("IDpossible.txt");
	if (myfile.is_open()){
		myfile << IDpossible;
		myfile.close();
	}
}
void read_IDpossible(){
		ifstream myfile ("IDpossible.txt");
		if (myfile.is_open()){
			string line;
			getline(myfile,line);
			IDpossible=toNumber(line);
			myfile.close();
		}
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void manHinhDangNhap(){
	hinhChuNhatDac(0,0,1024,768,WHITE);
	vanBan(240,100, " THI  TRAC  NGHIEM ", WHITE, RED, 8, 5, 0, 1);
	vanBan(240,100, " THI  TRAC ", WHITE, BLUE, 8, 5, 0, 1);
	vanBan(240,100, " THI ", WHITE, YELLOW, 8, 5, 0, 1);
	vanBan(290,720, "Chuong trinh duoc thuc hien boi Tran Dang Khoa N18DCCN101 D18CQCN02-N Hoc Vien Cong Nghe Buu Chinh Vien Thong co so TP.HCM", LIGHTGRAY, WHITE, 2, 5, 0,1);
	hinhChuNhatRong(190,190,760,520,DARKGRAY);
	vanBan(300,295,"Ten tai khoan",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260,720,310,DARKGRAY);
	vanBan(300,385,"Mat khau",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260+90,720,310+90,DARKGRAY);
	hinhChuNhatDac(420,455,550,500,LIGHTBLUE);
	vanBan(485,485,"Dang nhap", WHITE, LIGHTBLUE, 8,2,1,1);
	hinhChuNhatDac(960,10,1024,40,LIGHTRED);
	vanBan(987,33,"X", WHITE, LIGHTRED, 8,3,1,1);
	int x, y;
	int nutdangnhap=0, thanhtaikhoan=0, thanhmatkhau=0, thoat=0;
	string tk="", mk="";
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			nutdangnhap=((x>=420 && x<=550 && y>=455 && y<=500)? 1: 0);
			
			thoat=((x>=960 && x<=1024 && y>=10 && y<=40)? 1: 0);
		}
		if(nutdangnhap){
			hinhChuNhatDac(420,455,550,500,BLUE);
			vanBan(485,485,"Dang nhap", WHITE, BLUE, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(420,455,550,500,LIGHTBLUE);
			vanBan(485,485,"Dang nhap", WHITE, LIGHTBLUE, 8,2,1,1);
		}
		if(thoat==1){
			hinhChuNhatDac(960,10,1024,40,RED);
			vanBan(987,33,"X", WHITE, RED, 8,3,1,1);
		}
		else{
			hinhChuNhatDac(960,10,1024,40,LIGHTRED);
			vanBan(987,33,"X", WHITE, LIGHTRED, 8,3,1,1);
		}
		
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			thanhtaikhoan=((x>=390 && x<=720 && y>=260 && y<=310)? 1: 0);
			thanhmatkhau=((x>=390 && x<=720 && y>=260+90 && y<=310+90)? 1: 0);	
			
			nutdangnhap=((x>=420 && x<=550 && y>=455 && y<=500)? 2: 0);		
			
			thoat=((x>=960 && x<=1024 && y>=10 && y<=40)? 2: 0);										
        }
        if(thanhtaikhoan){
        	//chuyen thanh mat khau ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90,720,310+90, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1,720-1,310+90-1, WHITE);
        	thoatKhungNhap(395,385,mk,8,2,0,1);
        	//chuyen thanh tai khoan sang trai thai nhap van ban
        	hinhChuNhatRong(390,260,720,310, BLUE);
        	hinhChuNhatRong(390+1,260+1,720-1,310-1, BLUE);
        	khungNhap(395,295,tk,8,2,0,1,25);
		}
		else if(thanhmatkhau){
			//chuyen thanh tai khoan ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260,720,310, DARKGRAY);
			hinhChuNhatRong(390+1,260+1,720-1,310-1, WHITE);
			thoatKhungNhap(395,295,tk,8,2,0,1);
        	//chuyen thanh mat khau sang trang thai nhap van ban
        	hinhChuNhatRong(390,260+90,720,310+90, BLUE);
        	hinhChuNhatRong(390+1,260+90+1,720-1,310+90-1, BLUE);
			khungNhap(395,385,mk,8,2,0,1,25);
		}
		else if(kbhit()) getch();
		else{
			//chuyen thanh tai khoan ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260,720,310, DARKGRAY);
			hinhChuNhatRong(390+1,260+1,720-1,310-1, WHITE);
			thoatKhungNhap(395,295,tk,8,2,0,1);
        	//chuyen thanh mat khau va trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90,720,310+90, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1,720-1,310+90-1, WHITE);
        	thoatKhungNhap(395,385,mk,8,2,0,1);
		}
		
		if(nutdangnhap==2){
			nutdangnhap=0;
			if(tk.length()==0 || mk.length()==0){
				vanBan(485,485+80,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,485+80,"Thong bao: Khong duoc de trong", MAGENTA, WHITE, 8,1,1,1);
			}
			else{
				if(tk=="GV" && mk=="GV") slideDanhSach();
				pSinhVien temp=dslop.svThi(tk,mk);
				if(temp!=NULL) slideSETUPbaithi(temp);
				else{
					vanBan(485,485+80,STRDEL, WHITE, WHITE, 8,1,1,1);
					vanBan(485,485+80,"Thong bao: Tai Khoan hoac Mat Khau sai", MAGENTA, WHITE, 8,1,1,1);
				}
			}
			
		} 
		else if(thoat==2){
			dscauhoi.writeFile();
			dslop.writeFile();
			dsmonhoc.writeFile();
			write_IDpossible();
			exit(0);
		}
	}
}
void slideDanhSach(){
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
	hinhChuNhatDac(340,160,650,220,LIGHTGREEN);
	hinhChuNhatDac(340,230,650,290,LIGHTGREEN);
	hinhChuNhatDac(340,300,650,360,LIGHTGREEN);
	hinhChuNhatDac(340,370,650,430,LIGHTGREEN);
	vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
	vanBan(490, 55, "Danh Sach", GREEN, WHITE, 8, 5, 1, 1);
	vanBan(490, 200, "Lop Hoc", WHITE, LIGHTGREEN, 8, 4, 1, 1);
	vanBan(490, 270, "Sinh Vien", WHITE, LIGHTGREEN, 8, 4, 1, 1);
	vanBan(490, 340, "Mon Hoc", WHITE, LIGHTGREEN, 8, 4, 1, 1);
	vanBan(490, 410, "Cau Hoi", WHITE, LIGHTGREEN, 8, 4, 1, 1);
	int x, y;
	int trolai=0, lophoc=0, sinhvien=0, monhoc=0, cauhoi=0;
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 1: 0);
			lophoc=((x>=340 && x<=650 && y>=160 && y<=220)? 1: 0);
			sinhvien=((x>=340 && x<=650 && y>=230 && y<=290)? 1: 0);
			monhoc=((x>=340 && x<=650 && y>=300 && y<=360)? 1: 0);
			cauhoi=((x>=340 && x<=650 && y>=370 && y<=430)? 1: 0);
		}
		if(trolai==1){
			hinhChuNhatDac(30,30,120,65,MAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, MAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		if(lophoc==1){
			hinhChuNhatDac(340,160,650,220,GREEN);
			vanBan(490, 200, "Lop Hoc", WHITE, GREEN, 8, 4, 1, 1);
		}
		else{
			hinhChuNhatDac(340,160,650,220,LIGHTGREEN);
			vanBan(490, 200, "Lop Hoc", WHITE, LIGHTGREEN, 8, 4, 1, 1);
		}
		if(sinhvien==1){
			hinhChuNhatDac(340,230,650,290,GREEN);
			vanBan(490, 270, "Sinh Vien", WHITE, GREEN, 8, 4, 1, 1);
		}
		else{
			hinhChuNhatDac(340,230,650,290,LIGHTGREEN);
			vanBan(490, 270, "Sinh Vien", WHITE, LIGHTGREEN, 8, 4, 1, 1);
		}
		if(monhoc==1){
			hinhChuNhatDac(340,300,650,360,GREEN);
			vanBan(490, 340, "Mon Hoc", WHITE, GREEN, 8, 4, 1, 1);
		}
		else{
			hinhChuNhatDac(340,300,650,360,LIGHTGREEN);
			vanBan(490, 340, "Mon Hoc", WHITE, LIGHTGREEN, 8, 4, 1, 1);
		}
		if(cauhoi==1){
			hinhChuNhatDac(340,370,650,430,GREEN);
			vanBan(490, 410, "Cau Hoi", WHITE, GREEN, 8, 4, 1, 1);
		}
		else{
			hinhChuNhatDac(340,370,650,430,LIGHTGREEN);
			vanBan(490, 410, "Cau Hoi", WHITE, LIGHTGREEN, 8, 4, 1, 1);
		}
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 2: 0);
			lophoc=((x>=340 && x<=650 && y>=160 && y<=220)? 2: 0);
			sinhvien=((x>=340 && x<=650 && y>=230 && y<=290)? 2: 0);
			monhoc=((x>=340 && x<=650 && y>=300 && y<=360)? 2: 0);
			cauhoi=((x>=340 && x<=650 && y>=370 && y<=430)? 2: 0);													
        }
        //doan code nay chua chen lien ket
        if(trolai==2) manHinhDangNhap();
        else if(lophoc==2) slideLopHoc();
        else if(sinhvien==2) slideSinhVien();
        else if(monhoc==2) slideMonHoc();
        else if(cauhoi==2) slideCauHoi();
	}
}
void slideLopHoc(){
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
	hinhChuNhatDac(290,160,700,220,LIGHTRED);
	hinhChuNhatDac(290,230,700,290,LIGHTRED);
	hinhChuNhatDac(290,300,700,360,LIGHTRED);
	hinhChuNhatDac(290,370,700,430,LIGHTRED);
	vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
	vanBan(490, 55, "Lop Hoc", RED, WHITE, 8, 5, 1, 1);
	vanBan(490, 200, "Them Lop Hoc", WHITE, LIGHTRED, 8, 4, 1, 1);
	vanBan(490, 270, "Xoa Lop Hoc", WHITE, LIGHTRED, 8, 4, 1, 1);
	vanBan(490, 340, "Sua Thong Tin Lop", WHITE, LIGHTRED, 8, 4, 1, 1);
	vanBan(490, 410, "In Danh Sach Lop Hoc", WHITE, LIGHTRED, 8, 4, 1, 1);
	int x, y;
	int trolai=0, themlop=0, xoalop=0, sualop=0, inlop=0;
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 1: 0);
			themlop=((x>=290 && x<=700 && y>=160 && y<=220)? 1: 0);
			xoalop=((x>=290 && x<=700 && y>=230 && y<=290)? 1: 0);
			sualop=((x>=290 && x<=700 && y>=300 && y<=360)? 1: 0);
			inlop=((x>=290 && x<=700 && y>=370 && y<=430)? 1: 0);
		}
		if(trolai==1){
			hinhChuNhatDac(30,30,120,65,MAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, MAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		if(themlop==1){
			hinhChuNhatDac(290,160,700,220,RED);
			vanBan(490, 200, "Them Lop Hoc", WHITE, RED, 8, 4, 1, 1);
		}
		else{
			hinhChuNhatDac(290,160,700,220,LIGHTRED);
			vanBan(490, 200, "Them Lop Hoc", WHITE, LIGHTRED, 8, 4, 1, 1);
		}
		if(xoalop==1){
			hinhChuNhatDac(290,230,700,290,RED);
			vanBan(490, 270, "Xoa Lop Hoc", WHITE, RED, 8, 4, 1, 1);
		}
		else{
			hinhChuNhatDac(290,230,700,290,LIGHTRED);
			vanBan(490, 270, "Xoa Lop Hoc", WHITE, LIGHTRED, 8, 4, 1, 1);
		}
		if(sualop==1){
			hinhChuNhatDac(290,300,700,360,RED);
			vanBan(490, 340, "Sua Thong Tin Lop", WHITE, RED, 8, 4, 1, 1);
		}
		else{
			hinhChuNhatDac(290,300,700,360,LIGHTRED);
			vanBan(490, 340, "Sua Thong Tin Lop", WHITE, LIGHTRED, 8, 4, 1, 1);
		}
		if(inlop==1){
			hinhChuNhatDac(290,370,700,430,RED);
			vanBan(490, 410, "In Danh Sach Lop Hoc", WHITE, RED, 8, 4, 1, 1);
		}
		else{
			hinhChuNhatDac(290,370,700,430,LIGHTRED);
			vanBan(490, 410, "In Danh Sach Lop Hoc", WHITE, LIGHTRED, 8, 4, 1, 1);
		}
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 2: 0);
			themlop=((x>=340 && x<=650 && y>=160 && y<=220)? 2: 0);
			xoalop=((x>=340 && x<=650 && y>=230 && y<=290)? 2: 0);
			sualop=((x>=340 && x<=650 && y>=300 && y<=360)? 2: 0);
			inlop=((x>=340 && x<=650 && y>=370 && y<=430)? 2: 0);													
        }
        //doan code nay chua chen lien ket
        if(trolai==2) slideDanhSach();
        else if(themlop==2) slideThemLop();
        else if(xoalop==2) slideXoaLop();
        else if(sualop==2) slideSuaLop();
        else if(inlop==2) slideInLop();
	}
}
void slideThemLop(){
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
	vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
	vanBan(490, 55, "Them Lop Hoc", BLUE, WHITE, 8, 5, 1, 1);
	
	vanBan(300,295-150,"Ma Lop",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260-150,720,310-150,DARKGRAY);
	vanBan(300,385-150,"Ten Lop",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260+90-150,720,310+90-150,DARKGRAY);
	hinhChuNhatDac(420,455-150,550,500-150,LIGHTBLUE);
	vanBan(485,485-150,"Them", WHITE, LIGHTBLUE, 8,2,1,1);
	
	int x, y;
	int trolai=0, them=0, thanhmalop=0, thanhtenlop=0;
	string malop="", tenlop="";
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 1: 0);
			them=((x>=420 && x<=550 && y>=455-150 && y<=500-150)? 1: 0);
		}
		if(them==1){
			hinhChuNhatDac(420,455-150,550,500-150,BLUE);
			vanBan(485,485-150,"Them", WHITE, BLUE, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(420,455-150,550,500-150,LIGHTBLUE);
			vanBan(485,485-150,"Them", WHITE, LIGHTBLUE, 8,2,1,1);
		}
		if(trolai==1){
			hinhChuNhatDac(30,30,120,65,MAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, MAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			thanhmalop=((x>=390 && x<=720 && y>=260-150 && y<=310-150)? 1: 0);
			thanhtenlop=((x>=390 && x<=720 && y>=260+90-150 && y<=310+90-150)? 1: 0);
			
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 2: 0);
			them=((x>=420 && x<=550 && y>=455-150 && y<=500-150)? 2: 0);												
        }
        if(thanhmalop){
        	//chuyen thanh tenlop ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,385-150,tenlop,8,2,0,1);
        	//chuyen thanh malop sang trai thai nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, BLUE);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, BLUE);
        	khungNhap(395,295-150,malop,8,2,0,1,25);
		}
		else if(thanhtenlop){
			//chuyen thanhmalop ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
			hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
			thoatKhungNhap(395,295-150,malop,8,2,0,1);
        	//chuyen thanhtenlop sang trang thai nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, BLUE);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, BLUE);
			khungNhap(395,385-150,tenlop,8,2,0,1,25);
		}
		else if(kbhit()) getch();
		else{
			//chuyen thanhmalop ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
			hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
			thoatKhungNhap(395,295-150,malop,8,2,0,1);
			//chuyen thanh tenlop ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,385-150,tenlop,8,2,0,1);
		}
		if(trolai==2) slideLopHoc();
		else if(them==2){
			if(malop.length()==0 || tenlop.length()==0){
				vanBan(485,520-150,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,520-150,"Thong bao: khong duoc de trong", MAGENTA, WHITE, 8,1,1,1);
			} 
			else{
				dslop.append(malop, tenlop);
				vanBan(485,520-150,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,520-150,"Thong bao: "+thongbao, MAGENTA, WHITE, 8,1,1,1);
				if(thongbao==CONGRATULATION){
					delay(1500);
					slideThemLop();
				} 
			}
		}
	}
}
void slideXoaLop(){
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
	vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
	vanBan(490, 55, "Xoa Lop Hoc", RED, WHITE, 8, 5, 1, 1);
	
	vanBan(300,295-150,"Ma Lop",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260-150,720,310-150,DARKGRAY);

	hinhChuNhatDac(420,455-150-100,550,500-150-100,LIGHTRED);
	vanBan(485,485-150-100,"Xoa", WHITE, LIGHTRED, 8,2,1,1);
	
	int x, y;
	int trolai=0, xoa=0, thanhmalop=0;
	string malop="";
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 1: 0);
			xoa=((x>=420 && x<=550 && y>=455-150-100 && y<=500-150-100)? 1: 0);
		}
		if(xoa==1){
			hinhChuNhatDac(420,455-150-100,550,500-150-100,RED);
			vanBan(485,485-150-100,"Xoa", WHITE, RED, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(420,455-150-100,550,500-150-100,LIGHTRED);
			vanBan(485,485-150-100,"Xoa", WHITE, LIGHTRED, 8,2,1,1);
		}
		if(trolai==1){
			hinhChuNhatDac(30,30,120,65,MAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, MAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			thanhmalop=((x>=390 && x<=720 && y>=260-150 && y<=310-150)? 1: 0);
			
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 2: 0);
			xoa=((x>=420 && x<=550 && y>=455-150-100 && y<=500-150-100)? 2: 0);												
        }
        if(thanhmalop){
        	//chuyen thanh malop sang trai thai nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, BLUE);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, BLUE);
        	khungNhap(395,295-150,malop,8,2,0,1,25);
		}
		else if(kbhit()) getch();
		else{
			//chuyen thanhmalop ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
			hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
			thoatKhungNhap(395,295-150,malop,8,2,0,1);
		}
		if(trolai==2) slideLopHoc();
		else if(xoa==2){
			if(malop.length()==0){
				vanBan(485,420-150,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,420-150,"Thong bao: khong duoc de trong", MAGENTA, WHITE, 8,1,1,1);
			} 
			else{
				dslop.deleteLop(malop, dscauhoi);
				vanBan(485,420-150,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,420-150,"Thong bao: "+thongbao, MAGENTA, WHITE, 8,1,1,1);
				if(thongbao==CONGRATULATION){
					delay(1500);
					slideXoaLop();
				} 
			}
		}
	}
}
void slideSuaLop(){
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
	vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
	vanBan(490, 55, "Sua Thong Tin Lop Hoc", BLUE, WHITE, 8, 5, 1, 1);
	vanBan(490, 90, "Luu y: De trong Neu khong muon thay doi no.", LIGHTBLUE, WHITE, 8, 1, 1, 1);
	
	vanBan(300,295-150,"Ma Lop Cu",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260-150,720,310-150,DARKGRAY);
	vanBan(300,385-150,"Ma Lop Moi",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260+90-150,720,310+90-150,DARKGRAY);
	vanBan(300,475-150,"Ten Lop Moi",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,350+90-150,720,400+90-150,DARKGRAY);
	hinhChuNhatDac(420,405,550,450,LIGHTBLUE);
	vanBan(485,485-50,"Sua", WHITE, LIGHTBLUE, 8,2,1,1);
	
	int x, y;
	int trolai=0, sua=0, thanhmalopcu=0, thanhmalopmoi=0, thanhtenlopmoi=0;
	string malopcu="", malopmoi="", tenlopmoi="";
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 1: 0);
			sua=((x>=420 && x<=550 && y>=405 && y<=450)? 1: 0);
		}
		if(sua==1){
			hinhChuNhatDac(420,405,550,450,BLUE);
			vanBan(485,485-50,"Sua", WHITE, BLUE, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(420,405,550,450,LIGHTBLUE);
			vanBan(485,485-50,"Sua", WHITE, LIGHTBLUE, 8,2,1,1);
		}
		if(trolai==1){
			hinhChuNhatDac(30,30,120,65,MAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, MAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
	
			thanhmalopcu=((x>=390 && x<=720 && y>=260-150 && y<=310-150)? 1: 0);
			thanhmalopmoi=((x>=390 && x<=720 && y>=260+90-150 && y<=310+90-150)? 1: 0);
			thanhtenlopmoi=((x>=390 && x<=720 && y>=350+90-150 && y<=400+90-150)? 1: 0);
			
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 2: 0);
			sua=((x>=420 && x<=550 && y>=405 && y<=450)? 2: 0);												
        }
        if(thanhmalopcu){
        	//chuyen thanh malopmoi ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,385-150,malopmoi,8,2,0,1);
        	//chuyen thanh tenlopmoi ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,350+90-150,720,400+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,350+90+1-150,720-1,400+90-1-150, WHITE);
        	thoatKhungNhap(395,385+90-150,tenlopmoi,8,2,0,1);
        	//chuyen thanh malopcu sang trai thai nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, BLUE);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, BLUE);
        	khungNhap(395,295-150,malopcu,8,2,0,1,25);
		}
		else if(thanhmalopmoi){
			//chuyen thanhmalopcu ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
			hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
			thoatKhungNhap(395,295-150,malopcu,8,2,0,1);
			//chuyen thanh tenlopmoi ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,350+90-150,720,400+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,350+90+1-150,720-1,400+90-1-150, WHITE);
        	thoatKhungNhap(395,385+90-150,tenlopmoi,8,2,0,1);
        	//chuyen thanhmalopmoi sang trang thai nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, BLUE);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, BLUE);
			khungNhap(395,385-150,malopmoi,8,2,0,1,25);
		}
		else if(thanhtenlopmoi){
			//chuyen thanhmalopcu ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
			hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
			thoatKhungNhap(395,295-150,malopcu,8,2,0,1);
			//chuyen thanh malopmoi ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,385-150,malopmoi,8,2,0,1);
        	//chuyen thanh tenlopmoi ve trang thai nhap van ban
        	hinhChuNhatRong(390,350+90-150,720,400+90-150, BLUE);
        	hinhChuNhatRong(390+1,350+90+1-150,720-1,400+90-1-150, BLUE);
        	khungNhap(395,385+90-150,tenlopmoi,8,2,0,1,25);
		}
		else if(kbhit()) getch();
		else{
			//chuyen thanhmalopcu ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
			hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
			thoatKhungNhap(395,295-150,malopcu,8,2,0,1);
			//chuyen thanh malopmoi ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,385-150,malopmoi,8,2,0,1);
        	//chuyen thanh tenlopmoi ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,350+90-150,720,400+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,350+90+1-150,720-1,400+90-1-150, WHITE);
        	thoatKhungNhap(395,385+90-150,tenlopmoi,8,2,0,1);
        	
		}
		if(trolai==2) slideLopHoc();
		else if(sua==2){
			if(malopcu.length()==0){
				vanBan(485,480,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,480,"Thong bao: ma lop cu khong duoc de trong", MAGENTA, WHITE, 8,1,1,1);
			} 
			else{
				dslop.change(malopcu, malopmoi, tenlopmoi);
				vanBan(485,480,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,480,"Thong bao: "+thongbao, MAGENTA, WHITE, 8,1,1,1);
				if(thongbao==CONGRATULATION){
					delay(1500);
					slideSuaLop();
				} 
			}
		}
	}
}
void slideInLop(){
	int sotrang=(dslop.size()+9)/10;//lam tron len
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
	vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
	vanBan(490, 55, "In Danh Sach Lop", RED, WHITE, 8, 5, 1, 1);
	hinhChuNhatDac(200,80,500,130,LIGHTBLUE);
	vanBan(350, 115, "Ma Lop", WHITE, LIGHTBLUE, 8, 3, 1, 1);
	hinhChuNhatDac(501,80,801,130,LIGHTBLUE);
	vanBan(660, 115, "Ten Lop", WHITE, LIGHTBLUE, 8, 3, 1, 1);
	hinhChuNhatDac(30,640,70,680,LIGHTMAGENTA);
	vanBan(47, 662, "<", WHITE, LIGHTMAGENTA, 8, 3, 1, 1);
	hinhChuNhatDac(920,640,960,680,LIGHTMAGENTA);
	vanBan(937, 662, ">", WHITE, LIGHTMAGENTA, 8, 3, 1, 1);
	
	int trolai=0, truoc=0, sau=0, trangnow=(sotrang>0?1:0);
	for(int i=1; i<=10; i++){
		hinhChuNhatDac(501,80+51*i,801,130+51*i,LIGHTGRAY);
		hinhChuNhatDac(200,80+51*i,500,130+51*i,LIGHTGRAY);
	}
	for(int i=0, j=1; i<min(10, dslop.size()); i++, j++){
		vanBan(350, 110+51*j,dslop.malop_at(i), WHITE, LIGHTGRAY, 8,1,1,1);
		vanBan(650, 110+51*j,dslop.tenlop_at(i), WHITE, LIGHTGRAY, 8,1,1,1);
	}
	vanBan(480, 675, "Trang "+to_string(trangnow), BLACK, WHITE, 8, 2, 1, 1);
	vanBan(550, 675, "/ "+to_string(sotrang), BLACK, WHITE, 8, 2, 1, 1);
	int x, y;
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 1: 0);
			truoc=((x>=30 && x<=70 && y>=640 && y<=680)? 1: 0);
			sau=((x>=920 && x<=960 && y>=640 && y<=680)? 1: 0);	
		}
		if(trolai==1){
			hinhChuNhatDac(30,30,120,65,MAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, MAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		if(truoc==1){
			hinhChuNhatDac(30,640,70,680,MAGENTA);
			vanBan(47, 662, "<", WHITE, MAGENTA, 8, 3, 1, 1);
		}
		else{
			hinhChuNhatDac(30,640,70,680,LIGHTMAGENTA);
			vanBan(47, 662, "<", WHITE, LIGHTMAGENTA, 8, 3, 1, 1);
		}
		if(sau==1){
			hinhChuNhatDac(920,640,960,680,MAGENTA);
			vanBan(937, 662, ">", WHITE, MAGENTA, 8, 3, 1, 1);
		}
		else{
			hinhChuNhatDac(920,640,960,680,LIGHTMAGENTA);
			vanBan(937, 662, ">", WHITE, LIGHTMAGENTA, 8, 3, 1, 1);
		}
		
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 2: 0);
			truoc=((x>=30 && x<=70 && y>=640 && y<=680)? 2: 0);
			sau=((x>=920 && x<=960 && y>=640 && y<=680)? 2: 0);												
        }
        //doan code nay chua chen lien ket
        if(trolai==2) slideLopHoc();
        else if(sotrang>0){
        	if(truoc==2 && trangnow>1){
	        	trangnow--;
	        	for(int i=1; i<=10; i++){
					hinhChuNhatDac(501,80+51*i,801,130+51*i,LIGHTGRAY);
					hinhChuNhatDac(200,80+51*i,500,130+51*i,LIGHTGRAY);
				}
	        	for(int i=(trangnow-1)*10, j=1; i<min(trangnow*10, dslop.size()); i++, j++){
	        		vanBan(350, 110+51*j,dslop.malop_at(i), WHITE, LIGHTGRAY, 8,1,1,1);
	        		vanBan(650, 110+51*j,dslop.tenlop_at(i), WHITE, LIGHTGRAY, 8,1,1,1);
				}
				vanBan(480, 675, "Trang "+to_string(trangnow), BLACK, WHITE, 8, 1, 1, 1);
				truoc=0;
			}
			if(sau==2 && trangnow<sotrang){
	        	trangnow++;
	        	for(int i=1; i<=10; i++){
					hinhChuNhatDac(501,80+51*i,801,130+51*i,LIGHTGRAY);
					hinhChuNhatDac(200,80+51*i,500,130+51*i,LIGHTGRAY);
				}
	        	for(int i=(trangnow-1)*10, j=1; i<min(trangnow*10, dslop.size()); i++, j++){
	        		vanBan(350, 110+51*j,dslop.malop_at(i), WHITE, LIGHTGRAY, 8,1,1,1);
	        		vanBan(650, 110+51*j,dslop.tenlop_at(i), WHITE, LIGHTGRAY, 8,1,1,1);
				}
				vanBan(480, 675, "Trang "+to_string(trangnow), BLACK, WHITE, 8, 1, 1, 1);
				sau=0;
			}
		}
	}
}
void slideSinhVien(){
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
	hinhChuNhatDac(290,160,700,220,LIGHTRED);
	hinhChuNhatDac(290,230,700,290,LIGHTRED);
	hinhChuNhatDac(290,300,700,360,LIGHTRED);
	hinhChuNhatDac(290,370,700,430,LIGHTRED);
	vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
	vanBan(490, 55, "Sinh Vien", RED, WHITE, 8, 5, 1, 1);
	vanBan(490, 200, "Them Sinh Vien", WHITE, LIGHTRED, 8, 4, 1, 1);
	vanBan(490, 270, "Xoa Sinh Vien", WHITE, LIGHTRED, 8, 4, 1, 1);
	vanBan(490, 340, "Sua Thong Tin SV", WHITE, LIGHTRED, 8, 4, 1, 1);
	vanBan(490, 410, "Xem Bai Thi Cua SV", WHITE, LIGHTRED, 8, 4, 1, 1);
	int x, y;
	int trolai=0, themsv=0, xoasv=0, suasv=0, xemsv=0;
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 1: 0);
			themsv=((x>=290 && x<=700 && y>=160 && y<=220)? 1: 0);
			xoasv=((x>=290 && x<=700 && y>=230 && y<=290)? 1: 0);
			suasv=((x>=290 && x<=700 && y>=300 && y<=360)? 1: 0);
			xemsv=((x>=290 && x<=700 && y>=370 && y<=430)? 1: 0);
		}
		if(trolai==1){
			hinhChuNhatDac(30,30,120,65,MAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, MAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		if(themsv==1){
			hinhChuNhatDac(290,160,700,220,RED);
			vanBan(490, 200, "Them Sinh Vien", WHITE, RED, 8, 4, 1, 1);
		}
		else{
			hinhChuNhatDac(290,160,700,220,LIGHTRED);
			vanBan(490, 200, "Them Sinh Vien", WHITE, LIGHTRED, 8, 4, 1, 1);
		}
		if(xoasv==1){
			hinhChuNhatDac(290,230,700,290,RED);
			vanBan(490, 270, "Xoa Sinh Vien", WHITE, RED, 8, 4, 1, 1);
		}
		else{
			hinhChuNhatDac(290,230,700,290,LIGHTRED);
			vanBan(490, 270, "Xoa Sinh Vien", WHITE, LIGHTRED, 8, 4, 1, 1);
		}
		if(suasv==1){
			hinhChuNhatDac(290,300,700,360,RED);
			vanBan(490, 340, "Sua Thong Tin SV", WHITE, RED, 8, 4, 1, 1);
		}
		else{
			hinhChuNhatDac(290,300,700,360,LIGHTRED);
			vanBan(490, 340, "Sua Thong Tin SV", WHITE, LIGHTRED, 8, 4, 1, 1);
		}
		if(xemsv==1){
			hinhChuNhatDac(290,370,700,430,RED);
			vanBan(490, 410, "Xem Bai Thi Cua SV", WHITE, RED, 8, 4, 1, 1);
		}
		else{
			hinhChuNhatDac(290,370,700,430,LIGHTRED);
			vanBan(490, 410, "Xem Bai Thi Cua SV", WHITE, LIGHTRED, 8, 4, 1, 1);
		}
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 2: 0);
			themsv=((x>=340 && x<=650 && y>=160 && y<=220)? 2: 0);
			xoasv=((x>=340 && x<=650 && y>=230 && y<=290)? 2: 0);
			suasv=((x>=340 && x<=650 && y>=300 && y<=360)? 2: 0);
			xemsv=((x>=340 && x<=650 && y>=370 && y<=430)? 2: 0);													
        }
        //doan code nay chua chen lien ket
        if(trolai==2) slideDanhSach();
        else if(themsv==2) slideTruocThemSV();
        else if(xoasv==2) slideXoaSV();
        else if(suasv==2) slideSuaSV();
        else if(xemsv==2) slideXemBaiThisv();
	}
}
void slideTruocThemSV(){//slide nhap vao ma lop can them sinh vien
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
	vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
	vanBan(490, 55, "Lop Hoc Can Them Sinh Vien", RED, WHITE, 8, 5, 1, 1);
	
	vanBan(300,295-150,"Ma Lop",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260-150,720,310-150,DARKGRAY);

	hinhChuNhatDac(420,455-150-100,550,500-150-100,LIGHTRED);
	vanBan(485,485-150-100,"Chon", WHITE, LIGHTRED, 8,2,1,1);
	
	int x, y;
	int trolai=0, chon=0, thanhmalop=0;
	string malop="";
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 1: 0);
			chon=((x>=420 && x<=550 && y>=455-150-100 && y<=500-150-100)? 1: 0);
		}
		if(chon==1){
			hinhChuNhatDac(420,455-150-100,550,500-150-100,RED);
			vanBan(485,485-150-100,"Chon", WHITE, RED, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(420,455-150-100,550,500-150-100,LIGHTRED);
			vanBan(485,485-150-100,"Chon", WHITE, LIGHTRED, 8,2,1,1);
		}
		if(trolai==1){
			hinhChuNhatDac(30,30,120,65,MAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, MAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			thanhmalop=((x>=390 && x<=720 && y>=260-150 && y<=310-150)? 1: 0);
			
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 2: 0);
			chon=((x>=420 && x<=550 && y>=455-150-100 && y<=500-150-100)? 2: 0);												
        }
        if(thanhmalop){
        	//chuyen thanh malop sang trai thai nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, BLUE);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, BLUE);
        	khungNhap(395,295-150,malop,8,2,0,1,25);
		}
		else if(kbhit()) getch();
		else{
			//chuyen thanhmalop ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
			hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
			thoatKhungNhap(395,295-150,malop,8,2,0,1);
		}
		if(trolai==2) slideSinhVien();
		else if(chon==2){
			chon=0;
			if(malop.length()==0){
				vanBan(485,485-150-100+40,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,485-150-100+40,"Thong bao: Khong duoc de trong", MAGENTA, WHITE, 8,1,1,1);
			}
			else{
				int ok=dslop.find(malop);
				if(ok==-1){
					vanBan(485,485-150-100+40,STRDEL, WHITE, WHITE, 8,1,1,1);
					vanBan(485,485-150-100+40,"Thong bao: Khong tim thay ma lop", MAGENTA, WHITE, 8,1,1,1);
				} 
				else{
					slideThemSV(ok);
				}
			}
			
		} 
	}
}
void slideThemSV(int pos_lop){ 
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
	vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
	vanBan(490, 55, "Them SV vao lop "+dslop.malop_at(pos_lop), BLUE, WHITE, 8, 5, 1, 1);
	
	vanBan(300,295-150,"Ma Sinh Vien",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260-150,720,310-150,DARKGRAY);
	vanBan(300,385-150,"Ho",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260+90-150,720,310+90-150,DARKGRAY);
	vanBan(300,385+90-150,"Ten",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260+180-150,720,310+180-150,DARKGRAY);
	
	vanBan(300,385+180-150,"Gioi Tinh",BLACK,WHITE,8,2,1,1);
	hinhChuNhatDac(390,260+270-150,720,310+270-150,CYAN);
	vanBan(485+50,385+180-150,"NAM", WHITE, CYAN, 8,2,1,1);
	
	vanBan(300,385+270-150,"Password",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260+360-150,720,310+360-150,DARKGRAY);
	
	hinhChuNhatDac(420,260+450-150,550,310+450-150,LIGHTBLUE);
	vanBan(485,385+360-150,"Them", WHITE, LIGHTBLUE, 8,2,1,1);
	
	int x, y;
	int trolai=0, them=0, thanhmasv=0, thanhho=0, thanhten=0, thanhgioitinh=0, thanhpassword=0;
	string masv="", ho="", ten="", password="";
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 1: 0);
			them=((x>=420 && x<=550 && y>=260+450-150 && y<=310+450-150)? 1: 0);
		}
		if(them==1){
			hinhChuNhatDac(420,260+450-150,550,310+450-150,BLUE);
			vanBan(485,385+360-150,"Them", WHITE, BLUE, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(420,260+450-150,550,310+450-150,LIGHTBLUE);
			vanBan(485,385+360-150,"Them", WHITE, LIGHTBLUE, 8,2,1,1);
		}
		if(trolai==1){
			hinhChuNhatDac(30,30,120,65,MAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, MAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			thanhmasv=((x>=390 && x<=720 && y>=260-150 && y<=310-150)? 1: 0);
			thanhho=((x>=390 && x<=720 && y>=260+90-150 && y<=310+90-150)? 1: 0);
			thanhten=((x>=390 && x<=720 && y>=260+180-150 && y<=310+180-150)? 1: 0);
			thanhgioitinh=((x>=390 && x<=720 && y>=260+270-150 && y<=310+270-150)? !thanhgioitinh: thanhgioitinh);
			thanhpassword=((x>=390 && x<=720 && y>=260+360-150 && y<=310+360-150)? 1: 0);
			
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 2: 0);
			them=((x>=420 && x<=550 && y>=260+450-150 && y<=310+450-150)? 2: 0);												
        }
        if(thanhmasv){
        	//chuyen thanh ho ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,295+90-150,ho,8,2,0,1);
        	//chuyen thanh ten sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260+180-150,720,310+180-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+180+1-150,720-1,310+180-1-150, WHITE);
        	thoatKhungNhap(395,295+180-150,ten,8,2,0,1);
        	//chuyen thanh password sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260+360-150,720,310+360-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+360+1-150,720-1,310+360-1-150, WHITE);
        	thoatKhungNhap(395,295+360-150,password,8,2,0,1);
        	//chuyen thanh masv sang trai thai nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, BLUE);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, BLUE);
        	khungNhap(395,295-150,masv,8,2,0,1,25);
        	
		}
		else if(thanhho){
        	//chuyen thanh ten sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260+180-150,720,310+180-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+180+1-150,720-1,310+180-1-150, WHITE);
        	thoatKhungNhap(395,295+180-150,ten,8,2,0,1);
        	//chuyen thanh password sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260+360-150,720,310+360-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+360+1-150,720-1,310+360-1-150, WHITE);
        	thoatKhungNhap(395,295+360-150,password,8,2,0,1);
        	//chuyen thanh masv sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
        	thoatKhungNhap(395,295-150,masv,8,2,0,1);
        	//chuyen thanh ho ve trang thai nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, BLUE);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, BLUE);
        	khungNhap(395,295+90-150,ho,8,2,0,1,25);
		}
		else if(thanhten){
        	//chuyen thanh password sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260+360-150,720,310+360-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+360+1-150,720-1,310+360-1-150, WHITE);
        	thoatKhungNhap(395,295+360-150,password,8,2,0,1);
        	//chuyen thanh masv sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
        	thoatKhungNhap(395,295-150,masv,8,2,0,1);
        	//chuyen thanh ho ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,295+90-150,ho,8,2,0,1);
        	//chuyen thanh ten sang trai thai nhap van ban
        	hinhChuNhatRong(390,260+180-150,720,310+180-150, BLUE);
        	hinhChuNhatRong(390+1,260+180+1-150,720-1,310+180-1-150, BLUE);
        	khungNhap(395,295+180-150,ten,8,2,0,1,25);
		}
		else if(thanhpassword){
        	//chuyen thanh masv sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
        	thoatKhungNhap(395,295-150,masv,8,2,0,1);
        	//chuyen thanh ho ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,295+90-150,ho,8,2,0,1);
        	//chuyen thanh ten sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260+180-150,720,310+180-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+180+1-150,720-1,310+180-1-150, WHITE);
        	thoatKhungNhap(395,295+180-150,ten,8,2,0,1);
        	//chuyen thanh password sang trai thai nhap van ban
        	hinhChuNhatRong(390,260+360-150,720,310+360-150, BLUE);
        	hinhChuNhatRong(390+1,260+360+1-150,720-1,310+360-1-150, BLUE);
        	khungNhap(395,295+360-150,password,8,2,0,1,25);
		}
		else if(kbhit()) getch();
		else{
			//chuyen thanh masv sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
        	thoatKhungNhap(395,295-150,masv,8,2,0,1);
        	//chuyen thanh ho ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,295+90-150,ho,8,2,0,1);
        	//chuyen thanh ten sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260+180-150,720,310+180-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+180+1-150,720-1,310+180-1-150, WHITE);
        	thoatKhungNhap(395,295+180-150,ten,8,2,0,1);
        	//chuyen thanh password sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260+360-150,720,310+360-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+360+1-150,720-1,310+360-1-150, WHITE);
        	thoatKhungNhap(395,295+360-150,password,8,2,0,1);
		}
		if(thanhgioitinh){
			hinhChuNhatDac(390,260+270-150,720,310+270-150,LIGHTMAGENTA);
			vanBan(485+50,385+180-150,"NU", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(390,260+270-150,720,310+270-150,CYAN);
			vanBan(485+50,385+180-150,"NAM", WHITE, CYAN, 8,2,1,1);
		}
		
		if(trolai==2) slideTruocThemSV();
		else if(them==2){
			them=0;
			if(masv.length()==0 || ho.length()==0 || ten.length()==0 || password.length()==0){
				vanBan(485,385+360+40-150,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,385+360+40-150,"Thong bao: Khong duoc de trong", MAGENTA, WHITE, 8,1,1,1);
			}
			else{
				pSinhVien temp=new SinhVien;
				temp->masv=masv;
				temp->ho=ho;
				temp->ten=ten;
				temp->password=password;
				temp->phai=thanhgioitinh;
				temp->next=NULL;
				dslop.addSVvaoLop(pos_lop, temp);
				vanBan(485,385+360+40-150,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,385+360+40-150,"Thong bao: "+thongbao, MAGENTA, WHITE, 8,1,1,1);
				if(thongbao==CONGRATULATION){
					delay(1500);
					slideThemSV(pos_lop);
				}
			}
		}
	}
}
void slideXoaSV(){
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
	vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
	vanBan(490, 55, "Xoa Sinh Vien", RED, WHITE, 8, 5, 1, 1);
	
	vanBan(300,295-150,"Ma Sinh Vien",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260-150,720,310-150,DARKGRAY);

	hinhChuNhatDac(420,455-150-100,550,500-150-100,LIGHTRED);
	vanBan(485,485-150-100,"Xoa", WHITE, LIGHTRED, 8,2,1,1);
	
	int x, y;
	int trolai=0, xoa=0, thanhmasv=0;
	string masv="";
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 1: 0);
			xoa=((x>=420 && x<=550 && y>=455-150-100 && y<=500-150-100)? 1: 0);
		}
		if(xoa==1){
			hinhChuNhatDac(420,455-150-100,550,500-150-100,RED);
			vanBan(485,485-150-100,"Xoa", WHITE, RED, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(420,455-150-100,550,500-150-100,LIGHTRED);
			vanBan(485,485-150-100,"Xoa", WHITE, LIGHTRED, 8,2,1,1);
		}
		if(trolai==1){
			hinhChuNhatDac(30,30,120,65,MAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, MAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			thanhmasv=((x>=390 && x<=720 && y>=260-150 && y<=310-150)? 1: 0);
			
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 2: 0);
			xoa=((x>=420 && x<=550 && y>=455-150-100 && y<=500-150-100)? 2: 0);												
        }
        if(thanhmasv){
        	//chuyen thanh masv sang trai thai nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, BLUE);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, BLUE);
        	khungNhap(395,295-150,masv,8,2,0,1,25);
		}
		else if(kbhit()) getch();
		else{
			//chuyen thanhmasv ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
			hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
			thoatKhungNhap(395,295-150,masv,8,2,0,1);
		}
		if(trolai==2) slideSinhVien();
		else if(xoa==2){
			xoa=0;
			if(masv.length()==0){
				vanBan(485,485-150-100+40,STRDEL, WHITE, WHITE, 8,2,1,1);
				vanBan(485,485-150-100+40,"Thong bao: Khong duoc de trong", MAGENTA, WHITE, 8,1,1,1);
			}
			else{
				dslop.xoaSVkhoiLop(masv, dscauhoi);
				vanBan(485,485-150-100+40,STRDEL, WHITE, WHITE, 8,2,1,1);
				vanBan(485,485-150-100+40,"Thong bao: "+thongbao, MAGENTA, WHITE, 8,1,1,1);
				if(thongbao==CONGRATULATION){
					delay(1500);
					slideXoaSV();
				}
			}
		}
	}
}
void slideSuaSV(){
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
	vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
	vanBan(490, 55, "Sua Thong Tin Sinh Vien", BLUE, WHITE, 8, 5, 1, 1);
	vanBan(490, 90, "Luu y: De trong Neu khong muon thay doi no.", LIGHTBLUE, WHITE, 8, 1, 1, 1);
	
	vanBan(300,295-150,"Ma SV Cu",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260-150,720,310-150,DARKGRAY);
	vanBan(300,385-150,"Ma SV Moi",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260+90-150,720,310+90-150,DARKGRAY);
	vanBan(300,385+90-150,"Ho moi",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260+180-150,720,310+180-150,DARKGRAY);
	vanBan(300,385+90+90-150,"Ten moi",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260+180+90-150,720,310+180+90-150,DARKGRAY);
	
	vanBan(300,385+180+90-150,"Gioi Tinh Moi",BLACK,WHITE,8,2,1,1);
	hinhChuNhatDac(390,260+270+90-150,720,310+270+90-150,CYAN);
	vanBan(485+50,385+180+90-150,"NAM", WHITE, CYAN, 8,2,1,1);
	
	vanBan(300,385+270+90-150,"Password Moi",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260+360+90-150,720,310+360+90-150,DARKGRAY);
	
	hinhChuNhatDac(420,260+450+90-150,550,310+450+90-150,LIGHTBLUE);
	vanBan(485,385+360+90-150,"Sua", WHITE, LIGHTBLUE, 8,2,1,1);
	
	int x, y;
	int trolai=0, sua=0, thanhmasvcu=0, thanhmasvmoi=0, thanhhomoi=0, thanhtenmoi=0, thanhgioitinhmoi=0, thanhpasswordmoi=0;
	string masvcu="", masvmoi="", homoi="", tenmoi="", passwordmoi="";
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 1: 0);
			sua=((x>=420 && x<=550 && y>=260+450+90-150 && y<=310+450+90-150)? 1: 0);
		}
		if(sua==1){
			hinhChuNhatDac(420,260+450+90-150,550,310+450+90-150,BLUE);
			vanBan(485,385+360+90-150,"Sua", WHITE, BLUE, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(420,260+450+90-150,550,310+450+90-150,LIGHTBLUE);
			vanBan(485,385+360+90-150,"Sua", WHITE, LIGHTBLUE, 8,2,1,1);
		}
		if(trolai==1){
			hinhChuNhatDac(30,30,120,65,MAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, MAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			thanhmasvcu=((x>=390 && x<=720 && y>=260-150 && y<=310-150)? 1: 0);
			thanhmasvmoi=((x>=390 && x<=720 && y>=260+90-150 && y<=310+90-150)? 1: 0);
			thanhhomoi=((x>=390 && x<=720 && y>=260+180-150 && y<=310+180-150)? 1: 0);
			thanhtenmoi=((x>=390 && x<=720 && y>=260+180+90-150 && y<=310+180+90-150)? 1: 0);
			thanhgioitinhmoi=((x>=390 && x<=720 && y>=260+270+90-150 && y<=310+270+90-150)? !thanhgioitinhmoi: thanhgioitinhmoi);
			thanhpasswordmoi=((x>=390 && x<=720 && y>=260+360+90-150 && y<=310+360+90-150)? 1: 0);
			
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 2: 0);
			sua=((x>=420 && x<=550 && y>=260+450+90-150 && y<=310+450+90-150)? 2: 0);												
        }
        if(thanhmasvcu){
        	//chuyen thanh masvmoi ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,295+90-150,masvmoi,8,2,0,1);
        	//chuyen thanh homoi sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260+180-150,720,310+180-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+180+1-150,720-1,310+180-1-150, WHITE);
        	thoatKhungNhap(395,295+180-150,homoi,8,2,0,1);
        	//chuyen thanh tenmoi sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260+270-150,720,310+270-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+1+270-150,720-1,310-1+270-150, WHITE);
        	thoatKhungNhap(395,295+270-150,tenmoi,8,2,0,1);
        	//chuyen thanh passwordmoi sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260+360+90-150,720,310+360+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+360+90+1-150,720-1,310+360+90-1-150, WHITE);
        	thoatKhungNhap(395,295+360+90-150,passwordmoi,8,2,0,1);
        	//chuyen thanh masvcu sang trai thai nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, BLUE);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, BLUE);
        	khungNhap(395,295-150,masvcu,8,2,0,1,25);
		}
		else if(thanhmasvmoi){
        	//chuyen thanh homoi sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260+180-150,720,310+180-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+180+1-150,720-1,310+180-1-150, WHITE);
        	thoatKhungNhap(395,295+180-150,homoi,8,2,0,1);
        	//chuyen thanh tenmoi sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260+270-150,720,310+270-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+270+1-150,720-1,310+270-1-150, WHITE);
        	thoatKhungNhap(395,295+270-150,tenmoi,8,2,0,1);
        	//chuyen thanh passwordmoi sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260+360+90-150,720,310+360+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+360+90+1-150,720-1,310+360+90-1-150, WHITE);
        	thoatKhungNhap(395,295+360+90-150,passwordmoi,8,2,0,1);
        	//chuyen thanh masvcu sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
        	thoatKhungNhap(395,295-150,masvcu,8,2,0,1);
        	//chuyen thanh masvmoi ve trang thai nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, BLUE);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, BLUE);
        	khungNhap(395,295+90-150,masvmoi,8,2,0,1,25);
		}
		else if(thanhhomoi){
        	//chuyen thanh tenmoi sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260+270-150,720,310+270-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+270+1-150,720-1,310+270-1-150, WHITE);
        	thoatKhungNhap(395,295+270-150,tenmoi,8,2,0,1);
        	//chuyen thanh passwordmoi sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260+360+90-150,720,310+360+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+360+90+1-150,720-1,310+360+90-1-150, WHITE);
        	thoatKhungNhap(395,295+360+90-150,passwordmoi,8,2,0,1);
        	//chuyen thanh masvcu sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
        	thoatKhungNhap(395,295-150,masvcu,8,2,0,1);
        	//chuyen thanh masvmoi ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,295+90-150,masvmoi,8,2,0,1);
        	//chuyen thanh homoi sang trai thai nhap van ban
        	hinhChuNhatRong(390,260+180-150,720,310+180-150, BLUE);
        	hinhChuNhatRong(390+1,260+180+1-150,720-1,310+180-1-150, BLUE);
        	khungNhap(395,295+180-150,homoi,8,2,0,1,25);
		}
		else if(thanhtenmoi){
        	//chuyen thanh passwordmoi sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260+360+90-150,720,310+360+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+360+90+1-150,720-1,310+360+90-1-150, WHITE);
        	thoatKhungNhap(395,295+360+90-150,passwordmoi,8,2,0,1);
        	//chuyen thanh masvcu sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
        	thoatKhungNhap(395,295-150,masvcu,8,2,0,1);
        	//chuyen thanh masvmoi ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,295+90-150,masvmoi,8,2,0,1);
        	//chuyen thanh homoi sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260+180-150,720,310+180-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+180+1-150,720-1,310+180-1-150, WHITE);
        	thoatKhungNhap(395,295+180-150,homoi,8,2,0,1);
        	//chuyen thanh tenmoi sang trai thai nhap van ban
        	hinhChuNhatRong(390,260+270-150,720,310+270-150, BLUE);
        	hinhChuNhatRong(390+1,260+270+1-150,720-1,310+270-1-150, BLUE);
        	khungNhap(395,295+270-150,tenmoi,8,2,0,1,25);
		}
		else if(thanhpasswordmoi){
        	//chuyen thanh masvcu sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
        	thoatKhungNhap(395,295-150,masvcu,8,2,0,1);
        	//chuyen thanh masvmoi ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,295+90-150,masvmoi,8,2,0,1);
        	//chuyen thanh homoi sang trai thai nhap van ban
        	hinhChuNhatRong(390,260+180-150,720,310+180-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+180+1-150,720-1,310+180-1-150, WHITE);
        	thoatKhungNhap(395,295+180-150,homoi,8,2,0,1);
        	//chuyen thanh tenmoi sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260+270-150,720,310+270-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+270+1-150,720-1,310+270-1-150, WHITE);
        	thoatKhungNhap(395,295+270-150,tenmoi,8,2,0,1);
        	//chuyen thanh passwordmoi sang trai thai nhap van ban
        	hinhChuNhatRong(390,260+360+90-150,720,310+360+90-150, BLUE);
        	hinhChuNhatRong(390+1,260+360+90+1-150,720-1,310+360+90-1-150, BLUE);
        	khungNhap(395,295+360+90-150,passwordmoi,8,2,0,1,25);
		}
		else if(kbhit()) getch();
		else{
			//chuyen thanh masvcu sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
        	thoatKhungNhap(395,295-150,masvcu,8,2,0,1);
        	//chuyen thanh masvmoi ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,295+90-150,masvmoi,8,2,0,1);
        	//chuyen thanh homoi sang trai thai nhap khong van ban
        	hinhChuNhatRong(390,260+180-150,720,310+180-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+180+1-150,720-1,310+180-1-150, WHITE);
        	thoatKhungNhap(395,295+180-150,homoi,8,2,0,1);
        	//chuyen thanh tenmoi sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260+270-150,720,310+270-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+270+1-150,720-1,310+270-1-150, WHITE);
        	thoatKhungNhap(395,295+270-150,tenmoi,8,2,0,1);
        	//chuyen thanh passwordmoi sang trai thai khong nhap van ban
        	hinhChuNhatRong(390,260+360+90-150,720,310+360+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+360+90+1-150,720-1,310+360+90-1-150, WHITE);
        	thoatKhungNhap(395,295+360+90-150,passwordmoi,8,2,0,1);
		}
		if(thanhgioitinhmoi){
			hinhChuNhatDac(390,260+270+90-150,720,310+270+90-150,LIGHTMAGENTA);
			vanBan(485+50,385+180+90-150,"NU", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(390,260+270+90-150,720,310+270+90-150,CYAN);
			vanBan(485+50,385+180+90-150,"NAM", WHITE, CYAN, 8,2,1,1);
		}
		
		if(trolai==2) slideSinhVien();
		else if(sua==2){
			sua=0;
			if(masvcu.length()==0){
				vanBan(485,385+360+90-150+40,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,385+360+90-150+40,"Thong bao: Khong duoc de trong ma sv cu", MAGENTA, WHITE, 8,1,1,1);
			}
			else{
				dslop.suaSV(masvcu, masvmoi, homoi, tenmoi, passwordmoi, thanhgioitinhmoi);
				vanBan(485,385+360+90-150+40,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,385+360+90-150+40,"Thong bao: "+thongbao, MAGENTA, WHITE, 8,1,1,1);
				if(thongbao==CONGRATULATION){
					delay(1500);
					slideSuaSV();
				}
			}
			
		}
	}
}
void slideXemBaiThisv(){
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
	vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
	vanBan(490, 55, "Xem Bai Thi Cua Sinh Vien", BLUE, WHITE, 8, 5, 1, 1);
	
	vanBan(300,295-150,"Ma Sinh Vien",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260-150,720,310-150,DARKGRAY);
	vanBan(300,385-150,"Ma Mon Hoc",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260+90-150,720,310+90-150,DARKGRAY);
	hinhChuNhatDac(410,455-150,560,500-150,LIGHTBLUE);
	vanBan(485,485-150,"Xem Bai Thi", WHITE, LIGHTBLUE, 8,2,1,1);
	
	int x, y;
	int trolai=0, xem=0, thanhmasv=0, thanhmamh=0;
	string masv="", mamh="";
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 1: 0);
			xem=((x>=410 && x<=560 && y>=455-150 && y<=500-150)? 1: 0);
		}
		if(xem==1){
			hinhChuNhatDac(410,455-150,560,500-150,BLUE);
			vanBan(485,485-150,"Xem Bai Thi", WHITE, BLUE, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(410,455-150,560,500-150,LIGHTBLUE);
			vanBan(485,485-150,"Xem Bai Thi", WHITE, LIGHTBLUE, 8,2,1,1);
		}
		if(trolai==1){
			hinhChuNhatDac(30,30,120,65,MAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, MAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			thanhmasv=((x>=390 && x<=720 && y>=260-150 && y<=310-150)? 1: 0);
			thanhmamh=((x>=390 && x<=720 && y>=260+90-150 && y<=310+90-150)? 1: 0);
			
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 2: 0);
			xem=((x>=410 && x<=560 && y>=455-150 && y<=500-150)? 2: 0);												
        }
        if(thanhmasv){
        	//chuyen thanh mamh ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,385-150,mamh,8,2,0,1);
        	//chuyen thanh masv sang trai thai nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, BLUE);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, BLUE);
        	khungNhap(395,295-150,masv,8,2,0,1,25);
		}
		else if(thanhmamh){
			//chuyen thanh masv ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
			hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
			thoatKhungNhap(395,295-150,masv,8,2,0,1);
        	//chuyen thanh mamh sang trang thai nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, BLUE);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, BLUE);
			khungNhap(395,385-150,mamh,8,2,0,1,25);
		}
		else if(kbhit()) getch();
		else{
			//chuyen thanh masv ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
			hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
			thoatKhungNhap(395,295-150,masv,8,2,0,1);
			//chuyen thanh mamh ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,385-150,mamh,8,2,0,1);
		}
		if(trolai==2) slideSinhVien();
		else if(xem==2){
			xem=0;
			pSinhVien tam=dslop.xemSV(masv);
			if(masv.length()==0 || mamh.length()==0){
				vanBan(485,485-150+40,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,485-150+40,"Thong bao: khong duoc de trong" , MAGENTA, WHITE, 8,1,1,1);
			}
			else if(tam==NULL){
				vanBan(485,485-150+40,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,485-150+40,"Thong bao: khong tim thay masv nay" , MAGENTA, WHITE, 8,1,1,1);
			}
			else{
				pDiemThi tam1=tam->ketqua;
				pCauDaLam tam2=NULL;
				while(tam1!=NULL){
					if(tam1->mmh==mamh){
						tam2=tam1->baiLam;
						break;
					}
				}
				if(tam2==NULL){
					vanBan(485,485-150+40,STRDEL, WHITE, WHITE, 8,1,1,1);
					vanBan(485,485-150+40,"Thong bao: khong tim thay mamh nay" , MAGENTA, WHITE, 8,1,1,1);
				}
				else{
					slideSauXemBaiThiSV(tam1);
				}
			}
		}
	}
}
void slideSauXemBaiThiSV(pDiemThi temp1){
	int socau=temp1->soCau;
	pCauDaLam temp2=temp1->baiLam;
	int caunow=1;
	pNodeQuestion cauchitiet=dscauhoi.timCauHoi(temp2->id);
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,260-150,990,310-150,DARKGRAY);
	hinhChuNhatDac(30,260+90-150,990,310+90-150,DARKGRAY);
	hinhChuNhatDac(30,260+180-150,990,310+180-150,DARKGRAY);
	hinhChuNhatDac(30,260+270-150,990,310+270-150,DARKGRAY);
	hinhChuNhatDac(30,260+360-150,990,310+360-150,DARKGRAY);
	
	vanBan(40,295-150,"Noi Dung: "+cauchitiet->noiDung,WHITE,DARKGRAY,8,2,0,1);
	vanBan(40,295+90-150,"A. "+cauchitiet->cauA,WHITE,DARKGRAY,8,2,0,1);
	vanBan(40,295+180-150,"B. "+cauchitiet->cauB,WHITE,DARKGRAY,8,2,0,1);
	vanBan(40,295+270-150,"C. "+cauchitiet->cauC,WHITE,DARKGRAY,8,2,0,1);
	vanBan(40,295+360-150,"D. "+cauchitiet->cauD,WHITE,DARKGRAY,8,2,0,1);
	
	hinhChuNhatDac(920,640,960,680,LIGHTMAGENTA);
	vanBan(937, 662, ">", WHITE, LIGHTMAGENTA, 8, 3, 1, 1);
	
	vanBan(480, 675, "Cau "+to_string(caunow), BLACK, WHITE, 8, 2, 1, 1);
	vanBan(550, 675, "/ "+to_string(socau), BLACK, WHITE, 8, 2, 1, 1);
	string dapan, luachon;
	int x, y;
	int tiep=0;
	while(1){
		delay(35);
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			tiep=((x>=920 && x<=960 && y>=640 && y<=680)? 2: 0);												
        }
		if(cauchitiet->dapAn==0) dapan="A";
		else if(cauchitiet->dapAn==1) dapan="B";
		else if(cauchitiet->dapAn==2) dapan="C";
		else dapan="D";
		if(temp2->luaChon==-1) luachon="Chua chon";
		else if(temp2->luaChon==0) luachon="A";
		else if(temp2->luaChon==1) luachon="B";
		else if(temp2->luaChon==2) luachon="C";
		else luachon="D";
		
		hinhChuNhatDac(140,260+450-150,300,310+450-150,DARKGRAY);
		vanBan(80,295+450-150,"Dap an",BLACK,WHITE,8,2,1,1);
		vanBan(220,295+450-150,dapan, WHITE, DARKGRAY, 8,2,1,1);
		
		hinhChuNhatDac(140+300,260+450-150,300+300,310+450-150,DARKGRAY);
		vanBan(80+300,295+450-150,"Lua chon",BLACK,WHITE,8,2,1,1);
		vanBan(220+300,295+450-150,luachon, WHITE, DARKGRAY, 8,2,1,1);
		
		if(tiep==2){
			tiep=0;
			temp2=temp2->next;
			caunow++;
			if(caunow>socau){
				slideXemBaiThisv();
			}
			else{
				cauchitiet=dscauhoi.timCauHoi(temp2->id);
				hinhChuNhatDac(30,260-150,990,310-150,DARKGRAY);
				hinhChuNhatDac(30,260+90-150,990,310+90-150,DARKGRAY);
				hinhChuNhatDac(30,260+180-150,990,310+180-150,DARKGRAY);
				hinhChuNhatDac(30,260+270-150,990,310+270-150,DARKGRAY);
				hinhChuNhatDac(30,260+360-150,990,310+360-150,DARKGRAY);
				
				vanBan(40,295-150,"Noi Dung: "+cauchitiet->noiDung,WHITE,DARKGRAY,8,2,0,1);
				vanBan(40,295+90-150,"A. "+cauchitiet->cauA,WHITE,DARKGRAY,8,2,0,1);
				vanBan(40,295+180-150,"B. "+cauchitiet->cauB,WHITE,DARKGRAY,8,2,0,1);
				vanBan(40,295+270-150,"C. "+cauchitiet->cauC,WHITE,DARKGRAY,8,2,0,1);
				vanBan(40,295+360-150,"D. "+cauchitiet->cauD,WHITE,DARKGRAY,8,2,0,1);
				vanBan(480, 675, "Cau "+to_string(caunow), BLACK, WHITE, 8, 2, 1, 1);
				vanBan(550, 675, "/ "+to_string(socau), BLACK, WHITE, 8, 2, 1, 1);
				
				if(cauchitiet->dapAn==0) dapan="A";
				else if(cauchitiet->dapAn==1) dapan="B";
				else if(cauchitiet->dapAn==2) dapan="C";
				else dapan="D";
				if(temp2->luaChon==-1) luachon="Chua chon";
				else if(temp2->luaChon==0) luachon="A";
				else if(temp2->luaChon==1) luachon="B";
				else if(temp2->luaChon==2) luachon="C";
				else luachon="D";
				
				hinhChuNhatDac(140,260+450-150,300,310+450-150,DARKGRAY);
				vanBan(80,295+450-150,"Dap an",BLACK,WHITE,8,2,1,1);
				vanBan(220,295+450-150,dapan, WHITE, DARKGRAY, 8,2,1,1);
				
				hinhChuNhatDac(140+300,260+450-150,300+300,310+450-150,DARKGRAY);
				vanBan(80+300,295+450-150,"Lua chon",BLACK,WHITE,8,2,1,1);
				vanBan(220+300,295+450-150,luachon, WHITE, DARKGRAY, 8,2,1,1);
			}
		}
		
	}
}
void slideMonHoc(){
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
	hinhChuNhatDac(280,160,710,220,LIGHTRED);
	hinhChuNhatDac(280,230,710,290,LIGHTRED);
	hinhChuNhatDac(280,300,710,360,LIGHTRED);
	vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
	vanBan(490, 55, "Mon Hoc", RED, WHITE, 8, 5, 1, 1);
	vanBan(490, 200, "Them Mon Hoc", WHITE, LIGHTRED, 8, 4, 1, 1);
	vanBan(490, 270, "Xoa Mon Hoc", WHITE, LIGHTRED, 8, 4, 1, 1);
	vanBan(490, 340, "Sua Thong Tin Mon Hoc", WHITE, LIGHTRED, 8, 4, 1, 1);
	int x, y;
	int trolai=0, themmh=0, xoamh=0, suamh=0;
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 1: 0);
			themmh=((x>=280 && x<=710 && y>=160 && y<=220)? 1: 0);
			xoamh=((x>=280 && x<=710 && y>=230 && y<=290)? 1: 0);
			suamh=((x>=280 && x<=710 && y>=300 && y<=360)? 1: 0);
		}
		if(trolai==1){
			hinhChuNhatDac(30,30,120,65,MAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, MAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		if(themmh==1){
			hinhChuNhatDac(280,160,710,220,RED);
			vanBan(490, 200, "Them Mon Hoc", WHITE, RED, 8, 4, 1, 1);
		}
		else{
			hinhChuNhatDac(280,160,710,220,LIGHTRED);
			vanBan(490, 200, "Them Mon Hoc", WHITE, LIGHTRED, 8, 4, 1, 1);
		}
		if(xoamh==1){
			hinhChuNhatDac(280,230,710,290,RED);
			vanBan(490, 270, "Xoa Mon Hoc", WHITE, RED, 8, 4, 1, 1);
		}
		else{
			hinhChuNhatDac(280,230,710,290,LIGHTRED);
			vanBan(490, 270, "Xoa Mon Hoc", WHITE, LIGHTRED, 8, 4, 1, 1);
		}
		if(suamh==1){
			hinhChuNhatDac(280,300,710,360,RED);
			vanBan(490, 340, "Sua Thong Tin Mon Hoc", WHITE, RED, 8, 4, 1, 1);
		}
		else{
			hinhChuNhatDac(280,300,710,360,LIGHTRED);
			vanBan(490, 340, "Sua Thong Tin Mon Hoc", WHITE, LIGHTRED, 8, 4, 1, 1);
		}
		
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 2: 0);
			themmh=((x>=280 && x<=710 && y>=160 && y<=220)? 2: 0);
			xoamh=((x>=280 && x<=710 && y>=230 && y<=290)? 2: 0);
			suamh=((x>=280 && x<=710 && y>=300 && y<=360)? 2: 0);											
        }
        //doan code nay chua chen lien ket
        if(trolai==2) slideDanhSach();
        else if(themmh==2) slideThemMH();
        else if(xoamh==2) slideXoaMH();
        else if(suamh==2) slideSuaMH();
	}
}
void slideThemMH(){
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
	vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
	vanBan(490, 55, "Them Mon Hoc", BLUE, WHITE, 8, 5, 1, 1);
	
	vanBan(300,295-150,"Ma Mon Hoc",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260-150,720,310-150,DARKGRAY);
	vanBan(300,385-150,"Ten Mon Hoc",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260+90-150,720,310+90-150,DARKGRAY);
	hinhChuNhatDac(420,455-150,550,500-150,LIGHTBLUE);
	vanBan(485,485-150,"Them", WHITE, LIGHTBLUE, 8,2,1,1);
	
	int x, y;
	int trolai=0, them=0, thanhmamh=0, thanhtenmh=0;
	string mamh="", tenmh="";
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 1: 0);
			them=((x>=420 && x<=550 && y>=455-150 && y<=500-150)? 1: 0);
		}
		if(them==1){
			hinhChuNhatDac(420,455-150,550,500-150,BLUE);
			vanBan(485,485-150,"Them", WHITE, BLUE, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(420,455-150,550,500-150,LIGHTBLUE);
			vanBan(485,485-150,"Them", WHITE, LIGHTBLUE, 8,2,1,1);
		}
		if(trolai==1){
			hinhChuNhatDac(30,30,120,65,MAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, MAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			thanhmamh=((x>=390 && x<=720 && y>=260-150 && y<=310-150)? 1: 0);
			thanhtenmh=((x>=390 && x<=720 && y>=260+90-150 && y<=310+90-150)? 1: 0);
			
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 2: 0);
			them=((x>=420 && x<=550 && y>=455-150 && y<=500-150)? 2: 0);												
        }
        if(thanhmamh){
        	//chuyen thanh tenmh ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,385-150,tenmh,8,2,0,1);
        	//chuyen thanh mamh sang trai thai nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, BLUE);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, BLUE);
        	khungNhap(395,295-150,mamh,8,2,0,1,25);
		}
		else if(thanhtenmh){
			//chuyen thanh mamh ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
			hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
			thoatKhungNhap(395,295-150,mamh,8,2,0,1);
        	//chuyen thanh tenmh sang trang thai nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, BLUE);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, BLUE);
			khungNhap(395,385-150,tenmh,8,2,0,1,25);
		}
		else if(kbhit()) getch();
		else{
			//chuyen thanh mamh ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
			hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
			thoatKhungNhap(395,295-150,mamh,8,2,0,1);
			//chuyen thanh tenmh ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,385-150,tenmh,8,2,0,1);
		}
		if(trolai==2) slideMonHoc();
		else if(them==2){
			them=0;
			if(mamh.length()==0 || tenmh.length()==0){
				vanBan(485,485-150+40,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,485-150+40,"Thong bao: khong duoc de trong", MAGENTA, WHITE, 8,1,1,1);
			}
			else{
				dsmonhoc.append(mamh,tenmh);
				vanBan(485,485-150+40,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,485-150+40,"Thong bao: "+thongbao, MAGENTA, WHITE, 8,1,1,1);
				if(thongbao==CONGRATULATION){
					delay(1500);
					slideThemMH();
				}
			}
		}
	}
}
void slideXoaMH(){
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
	vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
	vanBan(490, 55, "Xoa Mon Hoc", RED, WHITE, 8, 5, 1, 1);
	vanBan(490, 90, "Luu y: Xoa Mon Hoc se xoa tat ca cac cau hoi, bai thi, diem thi co lien quan.", RED, WHITE, 8, 1, 1, 1);
	
	vanBan(300,295-150,"Ma Mon Hoc",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260-150,720,310-150,DARKGRAY);

	hinhChuNhatDac(420,455-150-100,550,500-150-100,LIGHTRED);
	vanBan(485,485-150-100,"Xoa", WHITE, LIGHTRED, 8,2,1,1);
	
	int x, y;
	int trolai=0, xoa=0, thanhmamh=0;
	string mamh="";
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 1: 0);
			xoa=((x>=420 && x<=550 && y>=455-150-100 && y<=500-150-100)? 1: 0);
		}
		if(xoa==1){
			hinhChuNhatDac(420,455-150-100,550,500-150-100,RED);
			vanBan(485,485-150-100,"Xoa", WHITE, RED, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(420,455-150-100,550,500-150-100,LIGHTRED);
			vanBan(485,485-150-100,"Xoa", WHITE, LIGHTRED, 8,2,1,1);
		}
		if(trolai==1){
			hinhChuNhatDac(30,30,120,65,MAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, MAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			thanhmamh=((x>=390 && x<=720 && y>=260-150 && y<=310-150)? 1: 0);
			
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 2: 0);
			xoa=((x>=420 && x<=550 && y>=455-150-100 && y<=500-150-100)? 2: 0);												
        }
        if(thanhmamh){
        	//chuyen thanh mamh sang trai thai nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, BLUE);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, BLUE);
        	khungNhap(395,295-150,mamh,8,2,0,1,25);
		}
		else if(kbhit()) getch();
		else{
			//chuyen thanh mamh ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
			hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
			thoatKhungNhap(395,295-150,mamh,8,2,0,1);
		}
		if(trolai==2) slideMonHoc();
		else if(xoa==2){
			xoa=0;
			if(mamh.length()==0){
				vanBan(485,485-150-100+40,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,485-150-100+40,"Thong bao: khong duoc de trong", MAGENTA, WHITE, 8,1,1,1);
			}
			else{
				dsmonhoc.deleteMH(mamh, dslop, dscauhoi);
				vanBan(485,485-150-100+40,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,485-150-100+40,"Thong bao: "+thongbao, MAGENTA, WHITE, 8,1,1,1);
				if(thongbao==CONGRATULATION){
					delay(1500);
					slideXoaMH();
				}
			}
		}
	}
}
void slideSuaMH(){
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
	vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
	vanBan(490, 55, "Sua Thong Tin Mon Hoc", BLUE, WHITE, 8, 5, 1, 1);
	vanBan(490, 90, "Luu y: De trong Neu khong muon thay doi no.", LIGHTBLUE, WHITE, 8, 1, 1, 1);
	
	vanBan(300,295-150,"Ma Mon Hoc Cu",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260-150,720,310-150,DARKGRAY);
	vanBan(300,385-150,"Ma Mon Hoc Moi",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260+90-150,720,310+90-150,DARKGRAY);
	vanBan(300,475-150,"Ten Mon Hoc Moi",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,350+90-150,720,400+90-150,DARKGRAY);
	hinhChuNhatDac(420,405,550,450,LIGHTBLUE);
	vanBan(485,485-50,"Sua", WHITE, LIGHTBLUE, 8,2,1,1);
	
	int x, y;
	int trolai=0, sua=0, thanhmamhcu=0, thanhmamhmoi=0, thanhtenmhmoi=0;
	string mamhcu="", mamhmoi="", tenmhmoi="";
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 1: 0);
			sua=((x>=420 && x<=550 && y>=405 && y<=450)? 1: 0);
		}
		if(sua==1){
			hinhChuNhatDac(420,405,550,450,BLUE);
			vanBan(485,485-50,"Sua", WHITE, BLUE, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(420,405,550,450,LIGHTBLUE);
			vanBan(485,485-50,"Sua", WHITE, LIGHTBLUE, 8,2,1,1);
		}
		if(trolai==1){
			hinhChuNhatDac(30,30,120,65,MAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, MAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
	
			thanhmamhcu=((x>=390 && x<=720 && y>=260-150 && y<=310-150)? 1: 0);
			thanhmamhmoi=((x>=390 && x<=720 && y>=260+90-150 && y<=310+90-150)? 1: 0);
			thanhtenmhmoi=((x>=390 && x<=720 && y>=350+90-150 && y<=400+90-150)? 1: 0);
			
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 2: 0);
			sua=((x>=420 && x<=550 && y>=405 && y<=450)? 2: 0);												
        }
        if(thanhmamhcu){
        	//chuyen thanh mamhmoi ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,385-150,mamhmoi,8,2,0,1);
        	//chuyen thanh tenmhmoi ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,350+90-150,720,400+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,350+90+1-150,720-1,400+90-1-150, WHITE);
        	thoatKhungNhap(395,385+90-150,tenmhmoi,8,2,0,1);
        	//chuyen thanh mamhcu sang trai thai nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, BLUE);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, BLUE);
        	khungNhap(395,295-150,mamhcu,8,2,0,1,25);
		}
		else if(thanhmamhmoi){
			//chuyen thanh mamhcu ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
			hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
			thoatKhungNhap(395,295-150,mamhcu,8,2,0,1);
			//chuyen thanh tenmhmoi ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,350+90-150,720,400+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,350+90+1-150,720-1,400+90-1-150, WHITE);
        	thoatKhungNhap(395,385+90-150,tenmhmoi,8,2,0,1);
        	//chuyen thanh mamhmoi sang trang thai nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, BLUE);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, BLUE);
			khungNhap(395,385-150,mamhmoi,8,2,0,1,25);
		}
		else if(thanhtenmhmoi){
			//chuyen thanh mamhcu ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
			hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
			thoatKhungNhap(395,295-150,mamhcu,8,2,0,1);
			//chuyen thanh mamhmoi ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,385-150,mamhmoi,8,2,0,1);
        	//chuyen thanh tenmhmoi ve trang thai nhap van ban
        	hinhChuNhatRong(390,350+90-150,720,400+90-150, BLUE);
        	hinhChuNhatRong(390+1,350+90+1-150,720-1,400+90-1-150, BLUE);
        	khungNhap(395,385+90-150,tenmhmoi,8,2,0,1,25);
		}
		else if(kbhit()) getch();
		else{
			//chuyen thanh mamhcu ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
			hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
			thoatKhungNhap(395,295-150,mamhcu,8,2,0,1);
			//chuyen thanh mamhmoi ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,385-150,mamhmoi,8,2,0,1);
        	//chuyen thanh tenmhmoi ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,350+90-150,720,400+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,350+90+1-150,720-1,400+90-1-150, WHITE);
        	thoatKhungNhap(395,385+90-150,tenmhmoi,8,2,0,1);
        	
		}
		if(trolai==2) slideMonHoc();
		else if(sua==2){
			sua=0;
			if(mamhcu.length()==0){
				vanBan(485,485-50+40,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,485-50+40,"Thong bao: ma mon hoc cu khong duoc de trong", MAGENTA, WHITE, 8,1,1,1);
			}
			else{
				dsmonhoc.changeMH(mamhcu, mamhmoi, tenmhmoi, dslop, dscauhoi);
				vanBan(485,485-50+40,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,485-50+40,thongbao, MAGENTA, WHITE, 8,1,1,1);
				if(thongbao==CONGRATULATION){
					delay(1500);
					slideSuaMH();
				}
			}	
		}
	}
}
void slideCauHoi(){
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
	hinhChuNhatDac(280,160,710,220,LIGHTRED);
	hinhChuNhatDac(280,230,710,290,LIGHTRED);
	hinhChuNhatDac(280,300,710,360,LIGHTRED);
	vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
	vanBan(490, 55, "Cau Hoi", RED, WHITE, 8, 5, 1, 1);
	vanBan(490, 200, "Them Cau Hoi", WHITE, LIGHTRED, 8, 4, 1, 1);
	vanBan(490, 270, "Xoa Cau Hoi", WHITE, LIGHTRED, 8, 4, 1, 1);
	vanBan(490, 340, "Chinh Sua Cau Hoi", WHITE, LIGHTRED, 8, 4, 1, 1);
	int x, y;
	int trolai=0, themch=0, xoach=0, suach=0;
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 1: 0);
			themch=((x>=280 && x<=710 && y>=160 && y<=220)? 1: 0);
			xoach=((x>=280 && x<=710 && y>=230 && y<=290)? 1: 0);
			suach=((x>=280 && x<=710 && y>=300 && y<=360)? 1: 0);
		}
		if(trolai==1){
			hinhChuNhatDac(30,30,120,65,MAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, MAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		if(themch==1){
			hinhChuNhatDac(280,160,710,220,RED);
			vanBan(490, 200, "Them Cau Hoi", WHITE, RED, 8, 4, 1, 1);
		}
		else{
			hinhChuNhatDac(280,160,710,220,LIGHTRED);
			vanBan(490, 200, "Them Cau Hoi", WHITE, LIGHTRED, 8, 4, 1, 1);
		}
		if(xoach==1){
			hinhChuNhatDac(280,230,710,290,RED);
			vanBan(490, 270, "Xoa Cau Hoi", WHITE, RED, 8, 4, 1, 1);
		}
		else{
			hinhChuNhatDac(280,230,710,290,LIGHTRED);
			vanBan(490, 270, "Xoa Cau Hoi", WHITE, LIGHTRED, 8, 4, 1, 1);
		}
		if(suach==1){
			hinhChuNhatDac(280,300,710,360,RED);
			vanBan(490, 340, "Chinh Sua Cau Hoi", WHITE, RED, 8, 4, 1, 1);
		}
		else{
			hinhChuNhatDac(280,300,710,360,LIGHTRED);
			vanBan(490, 340, "Chinh Sua Cau Hoi", WHITE, LIGHTRED, 8, 4, 1, 1);
		}
		
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 2: 0);
			themch=((x>=280 && x<=710 && y>=160 && y<=220)? 2: 0);
			xoach=((x>=280 && x<=710 && y>=230 && y<=290)? 2: 0);
			suach=((x>=280 && x<=710 && y>=300 && y<=360)? 2: 0);											
        }
        //doan code nay chua chen lien ket
        if(trolai==2) slideDanhSach();
        else if(themch==2) slideTruocThemCH();
        else if(xoach==2) slideXoaCH();
        else if(suach==2) slideTruocSuaCH();
	}
}
void slideTruocThemCH(){
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
	vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
	vanBan(490, 55, "Ma Mon Hoc Can Them Cau Hoi", RED, WHITE, 8, 5, 1, 1);
	
	vanBan(300,295-150,"Ma Mon Hoc",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260-150,720,310-150,DARKGRAY);

	hinhChuNhatDac(420,455-150-100,550,500-150-100,LIGHTRED);
	vanBan(485,485-150-100,"Chon", WHITE, LIGHTRED, 8,2,1,1);
	
	int x, y;
	int trolai=0, chon=0, thanhmamh=0;
	string mamh="";
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 1: 0);
			chon=((x>=420 && x<=550 && y>=455-150-100 && y<=500-150-100)? 1: 0);
		}
		if(chon==1){
			hinhChuNhatDac(420,455-150-100,550,500-150-100,RED);
			vanBan(485,485-150-100,"Chon", WHITE, RED, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(420,455-150-100,550,500-150-100,LIGHTRED);
			vanBan(485,485-150-100,"Chon", WHITE, LIGHTRED, 8,2,1,1);
		}
		if(trolai==1){
			hinhChuNhatDac(30,30,120,65,MAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, MAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			thanhmamh=((x>=390 && x<=720 && y>=260-150 && y<=310-150)? 1: 0);
			
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 2: 0);
			chon=((x>=420 && x<=550 && y>=455-150-100 && y<=500-150-100)? 2: 0);												
        }
        if(thanhmamh){
        	//chuyen thanh mamh sang trai thai nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, BLUE);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, BLUE);
        	khungNhap(395,295-150,mamh,8,2,0,1,25);
		}
		else if(kbhit()) getch();
		else{
			//chuyen thanh mamh ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
			hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
			thoatKhungNhap(395,295-150,mamh,8,2,0,1);
		}
		if(trolai==2) slideCauHoi();
		else if(chon==2){
			chon=0;
			if(mamh.length()==0){
				vanBan(485,485-150-100+40,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,485-150-100+40,"Thong bao: khong duoc de trong", MAGENTA, WHITE, 8,1,1,1);
			}
			else{
				bool ok=dsmonhoc.find(mamh);
				if(ok) slideThemCH(mamh);
				else{
					vanBan(485,485-150-100+40,STRDEL, WHITE, WHITE, 8,1,1,1);
					vanBan(485,485-150-100+40,"Thong bao: ma mon hoc khong tim thay", MAGENTA, WHITE, 8,1,1,1);
				}
			}
		}
	}
}
void slideThemCH(const string &mmh){
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
	vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
	vanBan(490, 55, "Them Cau Hoi co ID: "+to_string(IDpossible), BLUE, WHITE, 8, 5, 1, 1);
	
	vanBan(80,295-150,"Noi Dung",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(140,260-150,990,310-150,DARKGRAY);
	vanBan(80,295+90-150,"A",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(140,260+90-150,990,310+90-150,DARKGRAY);
	vanBan(80,295+180-150,"B",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(140,260+180-150,990,310+180-150,DARKGRAY);
	
	vanBan(80,295+270-150,"C",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(140,260+270-150,990,310+270-150,DARKGRAY);
	
	vanBan(80,295+360-150,"D",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(140,260+360-150,990,310+360-150,DARKGRAY);
	
	hinhChuNhatDac(140,260+450-150,300,310+450-150,DARKGRAY);
	vanBan(80,295+450-150,"Dap An",BLACK,WHITE,8,2,1,1);
	
	hinhChuNhatDac(420,260+540-150,550,310+540-150,LIGHTBLUE);
	vanBan(485,295+540-150,"Them", WHITE, LIGHTBLUE, 8,2,1,1);
	
	int x, y;
	int trolai=0, them=0, thanhnd=0, thanha=0, thanhb=0, thanhc=0, thanhd=0, thanhdapan=0;
	string nd="", a="", b="", c="", d="";
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 1: 0);
			them=((x>=420 && x<=550 && y>=260+540-150 && y<=310+540-150)? 1: 0);
		}
		
		
		if(them==1){
			hinhChuNhatDac(420,260+540-150,550,310+540-150,BLUE);
			vanBan(485,295+540-150,"Them", WHITE, BLUE, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(420,260+540-150,550,310+540-150,LIGHTBLUE);
			vanBan(485,295+540-150,"Them", WHITE, LIGHTBLUE, 8,2,1,1);
		}
		if(trolai==1){
			hinhChuNhatDac(30,30,120,65,MAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, MAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			thanhnd=((x>=140 && x<=990 && y>=260-150 && y<=310-150)? 1: 0);
			thanha=((x>=140 && x<=990 && y>=260+90-150 && y<=310+90-150)? 1: 0);
			thanhb=((x>=140 && x<=990 && y>=260+180-150 && y<=310+180-150)? 1: 0);
			thanhc=((x>=140 && x<=990 && y>=260+270-150 && y<=310+270-150)? 1: 0);
			thanhd=((x>=140 && x<=990 && y>=260+360-150 && y<=310+360-150)? 1: 0);
			thanhdapan=((x>=140 && x<=300 && y>=260+450-150 && y<=310+450-150)? (thanhdapan+1)%4: thanhdapan);
			
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 2: 0);
			them=((x>=420 && x<=550 && y>=260+540-150 && y<=310+540-150)? 2: 0);												
        }
		
		hinhChuNhatDac(140,260+450-150,300,310+450-150,1+thanhdapan);
		string dapan;
		if(thanhdapan==0) dapan="A";
		else if(thanhdapan==1) dapan="B";
		else if(thanhdapan==2) dapan="C";
		else dapan="D";
		vanBan(220,295+450-150,dapan, WHITE, 1+thanhdapan, 8,2,1,1);
		
        if(thanhnd){
        	//chuyen thanh a ve trang thai khong nhap van ban
        	hinhChuNhatRong(140,260+90-150,990,310+90-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+90+1-150,990-1,310+90-1-150, WHITE);
        	thoatKhungNhap(150,295+90-150,a,8,2,0,1);
        	//chuyen thanh b sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+180-150,990,310+180-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+180+1-150,990-1,310+180-1-150, WHITE);
        	thoatKhungNhap(150,295+180-150,b,8,2,0,1);
        	//chuyen thanh c sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+270-150,990,310+270-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+270+1-150,990-1,310+270-1-150, WHITE);
        	thoatKhungNhap(150,295+270-150,c,8,2,0,1);
        	//chuyen thanh d sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+360-150,990,310+360-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+360+1-150,990-1,310+360-1-150, WHITE);
        	thoatKhungNhap(150,295+360-150,d,8,2,0,1);
        	//chuyen thanh nd sang trai thai nhap van ban
        	hinhChuNhatRong(140,260-150,990,310-150, BLUE);
        	hinhChuNhatRong(140+1,260+1-150,990-1,310-1-150, BLUE);
        	khungNhap(150,295-150,nd,8,2,0,1,100);
		}
		else if(thanha){
        	//chuyen thanh b sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+180-150,990,310+180-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+180+1-150,990-1,310+180-1-150, WHITE);
        	thoatKhungNhap(150,295+180-150,b,8,2,0,1);
        	//chuyen thanh c sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+270-150,990,310+270-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+270+1-150,990-1,310+270-1-150, WHITE);
        	thoatKhungNhap(150,295+270-150,c,8,2,0,1);
        	//chuyen thanh d sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+360-150,990,310+360-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+360+1-150,990-1,310+360-1-150, WHITE);
        	thoatKhungNhap(150,295+360-150,d,8,2,0,1);
        	//chuyen thanh nd sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260-150,990,310-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+1-150,990-1,310-1-150, WHITE);
        	thoatKhungNhap(150,295-150,nd,8,2,0,1);
        	//chuyen thanh a ve trang thai nhap van ban
        	hinhChuNhatRong(140,260+90-150,990,310+90-150, BLUE);
        	hinhChuNhatRong(140+1,260+90+1-150,990-1,310+90-1-150, BLUE);
        	khungNhap(150,295+90-150,a,8,2,0,1,100);
		}
		else if(thanhb){
        	//chuyen thanh c sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+270-150,990,310+270-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+270+1-150,990-1,310+270-1-150, WHITE);
        	thoatKhungNhap(150,295+270-150,c,8,2,0,1);
        	//chuyen thanh d sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+360-150,990,310+360-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+360+1-150,990-1,310+360-1-150, WHITE);
        	thoatKhungNhap(150,295+360-150,d,8,2,0,1);
        	//chuyen thanh nd sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260-150,990,310-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+1-150,990-1,310-1-150, WHITE);
        	thoatKhungNhap(150,295-150,nd,8,2,0,1);
        	//chuyen thanh a ve trang thai khong nhap van ban
        	hinhChuNhatRong(140,260+90-150,990,310+90-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+90+1-150,990-1,310+90-1-150, WHITE);
        	thoatKhungNhap(150,295+90-150,a,8,2,0,1);
        	//chuyen thanh b sang trai thai nhap van ban
        	hinhChuNhatRong(140,260+180-150,990,310+180-150, BLUE);
        	hinhChuNhatRong(140+1,260+180+1-150,990-1,310+180-1-150, BLUE);
        	khungNhap(150,295+180-150,b,8,2,0,1,100);
		}
		else if(thanhc){
        	//chuyen thanh d sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+360-150,990,310+360-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+360+1-150,990-1,310+360-1-150, WHITE);
        	thoatKhungNhap(150,295+360-150,d,8,2,0,1);
        	//chuyen thanh nd sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260-150,990,310-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+1-150,990-1,310-1-150, WHITE);
        	thoatKhungNhap(150,295-150,nd,8,2,0,1);
        	//chuyen thanh a ve trang thai khong nhap van ban
        	hinhChuNhatRong(140,260+90-150,990,310+90-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+90+1-150,990-1,310+90-1-150, WHITE);
        	thoatKhungNhap(150,295+90-150,a,8,2,0,1);
        	//chuyen thanh b sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+180-150,990,310+180-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+180+1-150,990-1,310+180-1-150, WHITE);
        	thoatKhungNhap(150,295+180-150,b,8,2,0,1);
        	//chuyen thanh c sang trai thai nhap van ban
        	hinhChuNhatRong(140,260+270-150,990,310+270-150, BLUE);
        	hinhChuNhatRong(140+1,260+270+1-150,990-1,310+270-1-150, BLUE);
        	khungNhap(150,295+270-150,c,8,2,0,1,100);
		}
		else if(thanhd){
        	//chuyen thanh nd sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260-150,990,310-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+1-150,990-1,310-1-150, WHITE);
        	thoatKhungNhap(150,295-150,nd,8,2,0,1);
        	//chuyen thanh a ve trang thai khong nhap van ban
        	hinhChuNhatRong(140,260+90-150,990,310+90-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+90+1-150,990-1,310+90-1-150, WHITE);
        	thoatKhungNhap(150,295+90-150,a,8,2,0,1);
        	//chuyen thanh b sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+180-150,990,310+180-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+180+1-150,990-1,310+180-1-150, WHITE);
        	thoatKhungNhap(150,295+180-150,b,8,2,0,1);
        	//chuyen thanh c sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+270-150,990,310+270-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+270+1-150,990-1,310+270-1-150, WHITE);
        	thoatKhungNhap(150,295+270-150,c,8,2,0,1);
        	//chuyen thanh d sang trai thai nhap van ban
        	hinhChuNhatRong(140,260+360-150,990,310+360-150, BLUE);
        	hinhChuNhatRong(140+1,260+360+1-150,990-1,310+360-1-150, BLUE);
        	khungNhap(150,295+360-150,d,8,2,0,1,100);
		}
		else if(kbhit()) getch();
		else{
			//chuyen thanh nd sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260-150,990,310-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+1-150,990-1,310-1-150, WHITE);
        	thoatKhungNhap(150,295-150,nd,8,2,0,1);
        	//chuyen thanh a ve trang thai khong nhap van ban
        	hinhChuNhatRong(140,260+90-150,990,310+90-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+90+1-150,990-1,310+90-1-150, WHITE);
        	thoatKhungNhap(150,295+90-150,a,8,2,0,1);
        	//chuyen thanh b sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+180-150,990,310+180-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+180+1-150,990-1,310+180-1-150, WHITE);
        	thoatKhungNhap(150,295+180-150,b,8,2,0,1);
        	//chuyen thanh c sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+270-150,990,310+270-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+270+1-150,990-1,310+270-1-150, WHITE);
        	thoatKhungNhap(150,295+270-150,c,8,2,0,1);
        	//chuyen thanh d sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+360-150,990,310+360-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+360+1-150,990-1,310+360-1-150, WHITE);
        	thoatKhungNhap(150,295+360-150,d,8,2,0,1);
		}
		
		if(trolai==2) slideCauHoi();
		else if(them==2){
			them=0;
			if(nd.length()==0 || a.length()==0 || b.length()==0 || c.length()==0 || d.length()==0){
				vanBan(485,295+540-150+40,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,295+540-150+40,"Thong bao: Khong duoc de trong", MAGENTA, WHITE, 8,1,1,1);
			}
			else{
				dscauhoi.chen(IDpossible, mmh, nd, a,b,c,d, thanhdapan);
				vanBan(485,295+540-150+40,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,295+540-150+40,"Thong bao: "+CONGRATULATION, MAGENTA, WHITE, 8,1,1,1);
				delay(1500);
				IDpossible++;
				slideThemCH(mmh);
			}
		}
	}
}
void slideXoaCH(){
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
	vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
	vanBan(490, 55, "Xoa Cau Hoi", RED, WHITE, 8, 5, 1, 1);
	vanBan(490, 90, "Luu y: Chuong trinh Tu dong khong xoa cau da duoc dung de thi", RED, WHITE, 8, 1, 1, 1);
	
	vanBan(300,295-150,"ID",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260-150,720,310-150,DARKGRAY);

	hinhChuNhatDac(420,455-150-100,550,500-150-100,LIGHTRED);
	vanBan(485,485-150-100,"Xoa", WHITE, LIGHTRED, 8,2,1,1);
	
	int x, y;
	int trolai=0, xoa=0, thanhid=0;
	string id="";
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 1: 0);
			xoa=((x>=420 && x<=550 && y>=455-150-100 && y<=500-150-100)? 1: 0);
		}
		if(xoa==1){
			hinhChuNhatDac(420,455-150-100,550,500-150-100,RED);
			vanBan(485,485-150-100,"Xoa", WHITE, RED, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(420,455-150-100,550,500-150-100,LIGHTRED);
			vanBan(485,485-150-100,"Xoa", WHITE, LIGHTRED, 8,2,1,1);
		}
		if(trolai==1){
			hinhChuNhatDac(30,30,120,65,MAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, MAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			thanhid=((x>=390 && x<=720 && y>=260-150 && y<=310-150)? 1: 0);
			
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 2: 0);
			xoa=((x>=420 && x<=550 && y>=455-150-100 && y<=500-150-100)? 2: 0);												
        }
        if(thanhid){
        	//chuyen thanh mamh sang trai thai nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, BLUE);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, BLUE);
        	khungNhap(395,295-150,id,8,2,0,1,25);
		}
		else if(kbhit()) getch();
		else{
			//chuyen thanh mamh ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
			hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
			thoatKhungNhap(395,295-150,id,8,2,0,1);
		}
		if(trolai==2) slideCauHoi();
		else if(xoa==2){
			xoa=0;
			if(id.length()==0){
				vanBan(485,485-150-100+40,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,485-150-100+40,"Thong bao: khong duoc de trong", MAGENTA, WHITE, 8,1,1,1);
				
				
			}
			else{
				int id_int=0;
				for(int i=0; i<id.length(); i++){
					id_int=id_int*10+(id[i]-'0');
				}
				dscauhoi.xoa(id_int);
				vanBan(485,485-150-100+40,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,485-150-100+40,"Thong bao: "+CONGRATULATION, MAGENTA, WHITE, 8,1,1,1);
				delay(1500);
				slideXoaCH();
			}
		}
	}
}
void slideTruocSuaCH(){
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
	vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
	vanBan(490, 55, "Nhap ID Cau Hoi can sua", RED, WHITE, 8, 5, 1, 1);
	vanBan(490, 90, "Luu y: Khong the xoa cau hoi da duoc dung de thi.", RED, WHITE, 8, 1, 1, 1);
	
	vanBan(300,295-150,"ID",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260-150,720,310-150,DARKGRAY);

	hinhChuNhatDac(420,455-150-100,550,500-150-100,LIGHTRED);
	vanBan(485,485-150-100,"Chon", WHITE, LIGHTRED, 8,2,1,1);
	
	int x, y;
	int trolai=0, chon=0, thanhid=0;
	string id="";
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 1: 0);
			chon=((x>=420 && x<=550 && y>=455-150-100 && y<=500-150-100)? 1: 0);
		}
		if(chon==1){
			hinhChuNhatDac(420,455-150-100,550,500-150-100,RED);
			vanBan(485,485-150-100,"Chon", WHITE, RED, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(420,455-150-100,550,500-150-100,LIGHTRED);
			vanBan(485,485-150-100,"Chon", WHITE, LIGHTRED, 8,2,1,1);
		}
		if(trolai==1){
			hinhChuNhatDac(30,30,120,65,MAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, MAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			thanhid=((x>=390 && x<=720 && y>=260-150 && y<=310-150)? 1: 0);
			
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 2: 0);
			chon=((x>=420 && x<=550 && y>=455-150-100 && y<=500-150-100)? 2: 0);												
        }
        if(thanhid){
        	//chuyen thanh mamh sang trai thai nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, BLUE);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, BLUE);
        	khungNhap(395,295-150,id,8,2,0,1,25);
		}
		else if(kbhit()) getch();
		else{
			//chuyen thanh mamh ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
			hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
			thoatKhungNhap(395,295-150,id,8,2,0,1);
		}
		if(trolai==2) slideCauHoi();
		else if(chon==2){
			chon=0;
			int id_int=0;
			for(int i=0; i<id.length(); i++){
				id_int=id_int*10+(id[i]-'0');
			}
			dscauhoi.timID(id_int);
			if(thongbao!=CONGRATULATION){
				vanBan(485,485-150-100+40,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,485-150-100+40,thongbao, MAGENTA, WHITE, 8,1,1,1);
			}
			else slideSuaCH(id_int);
		}
	}
}
void slideSuaCH(int id){
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
	vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
	vanBan(490, 55, "Sua Cau Hoi Co ID "+to_string(id), BLUE, WHITE, 8, 5, 1, 1);
	vanBan(490, 90, "Luu y: De trong Neu khong muon thay doi no.", LIGHTBLUE, WHITE, 8, 1, 1, 1);
	
	vanBan(80,295-150,"Noi Dung",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(140,260-150,990,310-150,DARKGRAY);
	vanBan(80,295+90-150,"A",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(140,260+90-150,990,310+90-150,DARKGRAY);
	vanBan(80,295+180-150,"B",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(140,260+180-150,990,310+180-150,DARKGRAY);
	
	vanBan(80,295+270-150,"C",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(140,260+270-150,990,310+270-150,DARKGRAY);
	
	vanBan(80,295+360-150,"D",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(140,260+360-150,990,310+360-150,DARKGRAY);
	
	hinhChuNhatDac(140,260+450-150,300,310+450-150,DARKGRAY);
	vanBan(80,295+450-150,"Dap An",BLACK,WHITE,8,2,1,1);
	
	hinhChuNhatDac(420,260+540-150,550,310+540-150,LIGHTBLUE);
	vanBan(485,295+540-150,"Sua", WHITE, LIGHTBLUE, 8,2,1,1);
	
	int x, y;
	int trolai=0, sua=0, thanhnd=0, thanha=0, thanhb=0, thanhc=0, thanhd=0, thanhdapan=0;
	string nd="", a="", b="", c="", d="";
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 1: 0);
			sua=((x>=420 && x<=550 && y>=260+540-150 && y<=310+540-150)? 1: 0);
		}
		
		
		if(sua==1){
			hinhChuNhatDac(420,260+540-150,550,310+540-150,BLUE);
			vanBan(485,295+540-150,"Sua", WHITE, BLUE, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(420,260+540-150,550,310+540-150,LIGHTBLUE);
			vanBan(485,295+540-150,"Sua", WHITE, LIGHTBLUE, 8,2,1,1);
		}
		if(trolai==1){
			hinhChuNhatDac(30,30,120,65,MAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, MAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			thanhnd=((x>=140 && x<=990 && y>=260-150 && y<=310-150)? 1: 0);
			thanha=((x>=140 && x<=990 && y>=260+90-150 && y<=310+90-150)? 1: 0);
			thanhb=((x>=140 && x<=990 && y>=260+180-150 && y<=310+180-150)? 1: 0);
			thanhc=((x>=140 && x<=990 && y>=260+270-150 && y<=310+270-150)? 1: 0);
			thanhd=((x>=140 && x<=990 && y>=260+360-150 && y<=310+360-150)? 1: 0);
			thanhdapan=((x>=140 && x<=300 && y>=260+450-150 && y<=310+450-150)? (thanhdapan+1)%4: thanhdapan);
			
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 2: 0);
			sua=((x>=420 && x<=550 && y>=260+540-150 && y<=310+540-150)? 2: 0);												
        }
        
        hinhChuNhatDac(140,260+450-150,300,310+450-150,1+thanhdapan);
		string dapan;
		if(thanhdapan==0) dapan="A";
		else if(thanhdapan==1) dapan="B";
		else if(thanhdapan==2) dapan="C";
		else dapan="D";
		vanBan(220,295+450-150,dapan, WHITE, 1+thanhdapan, 8,2,1,1);
		
        if(thanhnd){
        	//chuyen thanh a ve trang thai khong nhap van ban
        	hinhChuNhatRong(140,260+90-150,990,310+90-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+90+1-150,990-1,310+90-1-150, WHITE);
        	thoatKhungNhap(150,295+90-150,a,8,2,0,1);
        	//chuyen thanh b sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+180-150,990,310+180-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+180+1-150,990-1,310+180-1-150, WHITE);
        	thoatKhungNhap(150,295+180-150,b,8,2,0,1);
        	//chuyen thanh c sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+270-150,990,310+270-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+270+1-150,990-1,310+270-1-150, WHITE);
        	thoatKhungNhap(150,295+270-150,c,8,2,0,1);
        	//chuyen thanh d sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+360-150,990,310+360-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+360+1-150,990-1,310+360-1-150, WHITE);
        	thoatKhungNhap(150,295+360-150,d,8,2,0,1);
        	//chuyen thanh nd sang trai thai nhap van ban
        	hinhChuNhatRong(140,260-150,990,310-150, BLUE);
        	hinhChuNhatRong(140+1,260+1-150,990-1,310-1-150, BLUE);
        	khungNhap(150,295-150,nd,8,2,0,1,100);
		}
		else if(thanha){
        	//chuyen thanh b sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+180-150,990,310+180-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+180+1-150,990-1,310+180-1-150, WHITE);
        	thoatKhungNhap(150,295+180-150,b,8,2,0,1);
        	//chuyen thanh c sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+270-150,990,310+270-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+270+1-150,990-1,310+270-1-150, WHITE);
        	thoatKhungNhap(150,295+270-150,c,8,2,0,1);
        	//chuyen thanh d sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+360-150,990,310+360-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+360+1-150,990-1,310+360-1-150, WHITE);
        	thoatKhungNhap(150,295+360-150,d,8,2,0,1);
        	//chuyen thanh nd sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260-150,990,310-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+1-150,990-1,310-1-150, WHITE);
        	thoatKhungNhap(150,295-150,nd,8,2,0,1);
        	//chuyen thanh a ve trang thai nhap van ban
        	hinhChuNhatRong(140,260+90-150,990,310+90-150, BLUE);
        	hinhChuNhatRong(140+1,260+90+1-150,990-1,310+90-1-150, BLUE);
        	khungNhap(150,295+90-150,a,8,2,0,1,100);
		}
		else if(thanhb){
        	//chuyen thanh c sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+270-150,990,310+270-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+270+1-150,990-1,310+270-1-150, WHITE);
        	thoatKhungNhap(150,295+270-150,c,8,2,0,1);
        	//chuyen thanh d sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+360-150,990,310+360-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+360+1-150,990-1,310+360-1-150, WHITE);
        	thoatKhungNhap(150,295+360-150,d,8,2,0,1);
        	//chuyen thanh nd sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260-150,990,310-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+1-150,990-1,310-1-150, WHITE);
        	thoatKhungNhap(150,295-150,nd,8,2,0,1);
        	//chuyen thanh a ve trang thai khong nhap van ban
        	hinhChuNhatRong(140,260+90-150,990,310+90-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+90+1-150,990-1,310+90-1-150, WHITE);
        	thoatKhungNhap(150,295+90-150,a,8,2,0,1);
        	//chuyen thanh b sang trai thai nhap van ban
        	hinhChuNhatRong(140,260+180-150,990,310+180-150, BLUE);
        	hinhChuNhatRong(140+1,260+180+1-150,990-1,310+180-1-150, BLUE);
        	khungNhap(150,295+180-150,b,8,2,0,1,100);
		}
		else if(thanhc){
        	//chuyen thanh d sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+360-150,990,310+360-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+360+1-150,990-1,310+360-1-150, WHITE);
        	thoatKhungNhap(150,295+360-150,d,8,2,0,1);
        	//chuyen thanh nd sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260-150,990,310-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+1-150,990-1,310-1-150, WHITE);
        	thoatKhungNhap(150,295-150,nd,8,2,0,1);
        	//chuyen thanh a ve trang thai khong nhap van ban
        	hinhChuNhatRong(140,260+90-150,990,310+90-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+90+1-150,990-1,310+90-1-150, WHITE);
        	thoatKhungNhap(150,295+90-150,a,8,2,0,1);
        	//chuyen thanh b sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+180-150,990,310+180-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+180+1-150,990-1,310+180-1-150, WHITE);
        	thoatKhungNhap(150,295+180-150,b,8,2,0,1);
        	//chuyen thanh c sang trai thai nhap van ban
        	hinhChuNhatRong(140,260+270-150,990,310+270-150, BLUE);
        	hinhChuNhatRong(140+1,260+270+1-150,990-1,310+270-1-150, BLUE);
        	khungNhap(150,295+270-150,c,8,2,0,1,100);
		}
		else if(thanhd){
        	//chuyen thanh nd sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260-150,990,310-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+1-150,990-1,310-1-150, WHITE);
        	thoatKhungNhap(150,295-150,nd,8,2,0,1);
        	//chuyen thanh a ve trang thai khong nhap van ban
        	hinhChuNhatRong(140,260+90-150,990,310+90-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+90+1-150,990-1,310+90-1-150, WHITE);
        	thoatKhungNhap(150,295+90-150,a,8,2,0,1);
        	//chuyen thanh b sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+180-150,990,310+180-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+180+1-150,990-1,310+180-1-150, WHITE);
        	thoatKhungNhap(150,295+180-150,b,8,2,0,1);
        	//chuyen thanh c sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+270-150,990,310+270-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+270+1-150,990-1,310+270-1-150, WHITE);
        	thoatKhungNhap(150,295+270-150,c,8,2,0,1);
        	//chuyen thanh d sang trai thai nhap van ban
        	hinhChuNhatRong(140,260+360-150,990,310+360-150, BLUE);
        	hinhChuNhatRong(140+1,260+360+1-150,990-1,310+360-1-150, BLUE);
        	khungNhap(150,295+360-150,d,8,2,0,1,100);
		}
		else if(kbhit()) getch();
		else{
			//chuyen thanh nd sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260-150,990,310-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+1-150,990-1,310-1-150, WHITE);
        	thoatKhungNhap(150,295-150,nd,8,2,0,1);
        	//chuyen thanh a ve trang thai khong nhap van ban
        	hinhChuNhatRong(140,260+90-150,990,310+90-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+90+1-150,990-1,310+90-1-150, WHITE);
        	thoatKhungNhap(150,295+90-150,a,8,2,0,1);
        	//chuyen thanh b sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+180-150,990,310+180-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+180+1-150,990-1,310+180-1-150, WHITE);
        	thoatKhungNhap(150,295+180-150,b,8,2,0,1);
        	//chuyen thanh c sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+270-150,990,310+270-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+270+1-150,990-1,310+270-1-150, WHITE);
        	thoatKhungNhap(150,295+270-150,c,8,2,0,1);
        	//chuyen thanh d sang trai thai khong nhap van ban
        	hinhChuNhatRong(140,260+360-150,990,310+360-150, DARKGRAY);
        	hinhChuNhatRong(140+1,260+360+1-150,990-1,310+360-1-150, WHITE);
        	thoatKhungNhap(150,295+360-150,d,8,2,0,1);
		}
		
		if(trolai==2) slideTruocSuaCH();
		else if(sua==2){
			sua=0;
			dscauhoi.suaTheoID(id,nd,a,b,c,d,thanhdapan);
			vanBan(485,295+540-150+40,STRDEL, WHITE, WHITE, 8,1,1,1);
			vanBan(485,295+540-150+40,CONGRATULATION, MAGENTA, WHITE, 8,1,1,1);
			delay(1500);
			slideTruocSuaCH();
		}
	}
}
void slideSETUPbaithi(pSinhVien temp){
	hinhChuNhatDac(0,0,1024,768,WHITE);
	hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
	vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
	vanBan(490, 55, "SETUP bai thi", BLUE, WHITE, 8, 5, 1, 1);
	vanBan(490, 90, "Luu y: mon da thi khong duoc thi lai", LIGHTBLUE, WHITE, 8, 1, 1, 1);
	
	vanBan(300,295-150,"Ma Mon Hoc",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260-150,720,310-150,DARKGRAY);
	vanBan(300,385-150,"So Cau",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,260+90-150,720,310+90-150,DARKGRAY);
	vanBan(300,475-150,"Thoi Gian Thi",BLACK,WHITE,8,2,1,1);
	hinhChuNhatRong(390,350+90-150,720,400+90-150,DARKGRAY);
	hinhChuNhatDac(420,405,550,450,LIGHTBLUE);
	vanBan(485,485-50,"Thi", WHITE, LIGHTBLUE, 8,2,1,1);
	
	int x, y;
	int trolai=0, thi=0, thanhmmh=0, thanhsocau=0, thanhthoigian=0;
	string mmh="", socau="", thoigian="";
	while(1){
		delay(35);
		if(ismouseclick(WM_MOUSEMOVE)){//nhan su kien khi di chuyen chuot
			getmouseclick(WM_MOUSEMOVE, x, y);
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 1: 0);
			thi=((x>=420 && x<=550 && y>=405 && y<=450)? 1: 0);
		}
		if(thi==1){
			hinhChuNhatDac(420,405,550,450,BLUE);
			vanBan(485,485-50,"Thi", WHITE, BLUE, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(420,405,550,450,LIGHTBLUE);
			vanBan(485,485-50,"Thi", WHITE, LIGHTBLUE, 8,2,1,1);
		}
		if(trolai==1){
			hinhChuNhatDac(30,30,120,65,MAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, MAGENTA, 8,2,1,1);
		}
		else{
			hinhChuNhatDac(30,30,120,65,LIGHTMAGENTA);
			vanBan(75, 55,"Tro Lai", WHITE, LIGHTMAGENTA, 8,2,1,1);
		}
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
	
			thanhmmh=((x>=390 && x<=720 && y>=260-150 && y<=310-150)? 1: 0);
			thanhsocau=((x>=390 && x<=720 && y>=260+90-150 && y<=310+90-150)? 1: 0);
			thanhthoigian=((x>=390 && x<=720 && y>=350+90-150 && y<=400+90-150)? 1: 0);
			
			trolai=((x>=30 && x<=120 && y>=30 && y<=65)? 2: 0);
			thi=((x>=420 && x<=550 && y>=405 && y<=450)? 2: 0);												
        }
        if(thanhmmh){
        	//chuyen thanh socau ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,385-150,socau,8,2,0,1);
        	//chuyen thanh thoigian ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,350+90-150,720,400+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,350+90+1-150,720-1,400+90-1-150, WHITE);
        	thoatKhungNhap(395,385+90-150,thoigian,8,2,0,1);
        	//chuyen thanh mmh sang trai thai nhap van ban
        	hinhChuNhatRong(390,260-150,720,310-150, BLUE);
        	hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, BLUE);
        	khungNhap(395,295-150,mmh,8,2,0,1,25);
		}
		else if(thanhsocau){
			//chuyen thanh mmh ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
			hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
			thoatKhungNhap(395,295-150,mmh,8,2,0,1);
			//chuyen thanh thoigian ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,350+90-150,720,400+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,350+90+1-150,720-1,400+90-1-150, WHITE);
        	thoatKhungNhap(395,385+90-150,thoigian,8,2,0,1);
        	//chuyen thanh socau sang trang thai nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, BLUE);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, BLUE);
			khungNhap(395,385-150,socau,8,2,0,1,5);
		}
		else if(thanhthoigian){
			//chuyen thanh mmh ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
			hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
			thoatKhungNhap(395,295-150,mmh,8,2,0,1);
			//chuyen thanh socau ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,385-150,socau,8,2,0,1);
        	//chuyen thanh thoigian ve trang thai nhap van ban
        	hinhChuNhatRong(390,350+90-150,720,400+90-150, BLUE);
        	hinhChuNhatRong(390+1,350+90+1-150,720-1,400+90-1-150, BLUE);
        	khungNhap(395,385+90-150,thoigian,8,2,0,1,5);
		}
		else if(kbhit()) getch();
		else{
			//chuyen thanh mmh ve trang thai khong nhap van ban
			hinhChuNhatRong(390,260-150,720,310-150, DARKGRAY);
			hinhChuNhatRong(390+1,260+1-150,720-1,310-1-150, WHITE);
			thoatKhungNhap(395,295-150,mmh,8,2,0,1);
			//chuyen thanh socau ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,260+90-150,720,310+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,260+90+1-150,720-1,310+90-1-150, WHITE);
        	thoatKhungNhap(395,385-150,socau,8,2,0,1);
        	//chuyen thanh thoigian ve trang thai khong nhap van ban
        	hinhChuNhatRong(390,350+90-150,720,400+90-150, DARKGRAY);
        	hinhChuNhatRong(390+1,350+90+1-150,720-1,400+90-1-150, WHITE);
        	thoatKhungNhap(395,385+90-150,thoigian,8,2,0,1);
		}
		if(trolai==2) manHinhDangNhap();
		else if(thi==2){
			thi=0;
			if(mmh.length()==0 || socau.length()==0 || thoigian.length()==0){
				vanBan(485,485-50+40,STRDEL, WHITE, WHITE, 8,1,1,1);
				vanBan(485,485-50+40,"Thong bao: Khong duoc de trong", MAGENTA, WHITE, 8,1,1,1);
			}
			else{
				int socaucungmmh=dscauhoi.soCauCungMMH(mmh);
				int socau_int=toNumber(socau), thoigian_int=toNumber(thoigian);
				bool ok=1;
				pDiemThi temp1=temp->ketqua;
				while(temp1!=NULL){
					if(temp1->mmh==mmh){
						ok=0;
						break;
					}
				}
				if(ok==0){
					vanBan(485,485-50+40,STRDEL, WHITE, WHITE, 8,1,1,1);
					vanBan(485,485-50+40,"Thong bao: Sinh vien da thi mon nay roi", MAGENTA, WHITE, 8,1,1,1);
				}
				else if(socau_int==0){
					vanBan(485,485-50+40,STRDEL, WHITE, WHITE, 8,1,1,1);
					vanBan(485,485-50+40,"So cau khong the la 0", MAGENTA, WHITE, 8,1,1,1);
				}
				else if(thoigian_int<5 ||thoigian_int>500){
					vanBan(485,485-50+40,STRDEL, WHITE, WHITE, 8,1,1,1);
					vanBan(485,485-50+40,"Thoi gian khong the < 5 phut hoac >500", MAGENTA, WHITE, 8,1,1,1);
				}
				else if(socau_int>socaucungmmh){
					vanBan(485,485-50+40,STRDEL, WHITE, WHITE, 8,1,1,1);
					vanBan(485,485-50+40,"So Cau hoi khong du, thieu "+to_string(socau_int-socaucungmmh)+" cau", MAGENTA, WHITE, 8,1,1,1);
				}
				else{
					int arr[socaucungmmh];
					dscauhoi.dscaucungMMH(mmh, arr);
					for(int i=0; i<socaucungmmh; i++){
						int j=rand()%socaucungmmh;
						swap(arr[i], arr[j]);
					}
					pDiemThi x=new DiemThi;
					x->mmh=mmh;
					x->soCau=socau_int;
					x->next=temp->ketqua;
					x->baiLam=NULL;
					temp->ketqua=x;
					for(int i=0; i<socau_int; i++){
						pCauDaLam  y=new CauDaLam;
						y->id=arr[i];
						y->next=x->baiLam;
						x->baiLam=y;
					}
					temp->soMonThi++;
					slideTHITRACNGHIEM(temp, thoigian_int);
				}
			}	
		}
	}
}
void slideTHITRACNGHIEM(pSinhVien temp,int thoigian){
	pDiemThi temp1=temp->ketqua;
	int socau=temp1->soCau;
	pCauDaLam temp2=temp1->baiLam;
	int caunow=1;
	pNodeQuestion cauchitiet=dscauhoi.timCauHoi(temp2->id);
	int socaudung=0;
	hinhChuNhatDac(0,0,1024,768,WHITE);
	vanBan(490, 55, "Xin Chao "+temp->ho+" "+temp->ten, BLUE, WHITE, 8, 3, 1, 1);
	hinhChuNhatDac(30,260-150,990,310-150,DARKGRAY);
	hinhChuNhatDac(30,260+90-150,990,310+90-150,DARKGRAY);
	hinhChuNhatDac(30,260+180-150,990,310+180-150,DARKGRAY);
	hinhChuNhatDac(30,260+270-150,990,310+270-150,DARKGRAY);
	hinhChuNhatDac(30,260+360-150,990,310+360-150,DARKGRAY);
	
	vanBan(40,295-150,"Noi Dung: "+cauchitiet->noiDung,WHITE,DARKGRAY,8,2,0,1);
	vanBan(40,295+90-150,"A. "+cauchitiet->cauA,WHITE,DARKGRAY,8,2,0,1);
	vanBan(40,295+180-150,"B. "+cauchitiet->cauB,WHITE,DARKGRAY,8,2,0,1);
	vanBan(40,295+270-150,"C. "+cauchitiet->cauC,WHITE,DARKGRAY,8,2,0,1);
	vanBan(40,295+360-150,"D. "+cauchitiet->cauD,WHITE,DARKGRAY,8,2,0,1);
	
	hinhChuNhatDac(140,260+450-150,300,310+450-150,DARKGRAY);
	vanBan(80,295+450-150,"Lua chon",BLACK,WHITE,8,2,1,1);
	
	hinhChuNhatDac(920,640,960,680,LIGHTMAGENTA);
	vanBan(937, 662, ">", WHITE, LIGHTMAGENTA, 8, 3, 1, 1);
	
	vanBan(480, 675, "Cau "+to_string(caunow), BLACK, WHITE, 8, 2, 1, 1);
	vanBan(550, 675, "/ "+to_string(socau), BLACK, WHITE, 8, 2, 1, 1);
	
	int x, y;
	int thanhluachon=0, tiep=0;
	int Time=0;
	while(1){
		delay(35);
		Time+=35;
		int sophut=Time/1000/60, sogiay=Time/1000%60;
		vanBan(490, 55+40,STRDEL, WHITE, WHITE, 8, 2, 1, 1);
		vanBan(490, 55+40,"Thoi gian hien tai "+to_string(sophut)+":"+to_string(sogiay), RED, WHITE, 8, 2, 1, 1);
		
		if(sophut==thoigian){
			temp1->diem=to_string(int(1.0*socaudung/socau*10*100)/100.0);
			vanBan(490, 55+40,STRDEL, WHITE, WHITE, 8, 2, 1, 1);
			vanBan(490, 55+40,"So diem cua ban la "+temp1->diem, RED, WHITE, 8, 2, 1, 1);
			delay(3000);
			slideSETUPbaithi(temp);
		}
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			thanhluachon=((x>=140 && x<=300 && y>=260+450-150 && y<=310+450-150)? (thanhluachon+1)%4: thanhluachon);
			tiep=((x>=920 && x<=960 && y>=640 && y<=680)? 2: 0);												
        }
		
		hinhChuNhatDac(140,260+450-150,300,310+450-150,1+thanhluachon);
		string luachon;
		if(thanhluachon==0) luachon="A";
		else if(thanhluachon==1) luachon="B";
		else if(thanhluachon==2) luachon="C";
		else luachon="D";
		vanBan(220,295+450-150,luachon, WHITE, 1+thanhluachon, 8,2,1,1);
		
		if(tiep==2){
			tiep=0;
			if(cauchitiet->dapAn==thanhluachon) socaudung++;
			temp2->luaChon=thanhluachon;
			
			temp2=temp2->next;
			caunow++;
			if(caunow>socau){
				temp1->diem=to_string(int(1.0*socaudung/socau*10*100)/100.0);
				vanBan(490, 55+40,STRDEL, WHITE, WHITE, 8, 2, 1, 1);
				vanBan(490, 55+40,"So diem cua ban la "+temp1->diem, RED, WHITE, 8, 2, 1, 1);
				delay(3000);
				slideSETUPbaithi(temp);
			}
			else{
				cauchitiet=dscauhoi.timCauHoi(temp2->id);
				hinhChuNhatDac(30,260-150,990,310-150,DARKGRAY);
				hinhChuNhatDac(30,260+90-150,990,310+90-150,DARKGRAY);
				hinhChuNhatDac(30,260+180-150,990,310+180-150,DARKGRAY);
				hinhChuNhatDac(30,260+270-150,990,310+270-150,DARKGRAY);
				hinhChuNhatDac(30,260+360-150,990,310+360-150,DARKGRAY);
				
				vanBan(40,295-150,"Noi Dung: "+cauchitiet->noiDung,WHITE,DARKGRAY,8,2,0,1);
				vanBan(40,295+90-150,"A. "+cauchitiet->cauA,WHITE,DARKGRAY,8,2,0,1);
				vanBan(40,295+180-150,"B. "+cauchitiet->cauB,WHITE,DARKGRAY,8,2,0,1);
				vanBan(40,295+270-150,"C. "+cauchitiet->cauC,WHITE,DARKGRAY,8,2,0,1);
				vanBan(40,295+360-150,"D. "+cauchitiet->cauD,WHITE,DARKGRAY,8,2,0,1);
				vanBan(480, 675, "Cau "+to_string(caunow), BLACK, WHITE, 8, 2, 1, 1);
				vanBan(550, 675, "/ "+to_string(socau), BLACK, WHITE, 8, 2, 1, 1);
			}
		}
		
	}
}
void timToaDo(){
	int x, y;
	while(1){
		delay(0.0001);
		if (ismouseclick(WM_LBUTTONDOWN)){//nhan su kien khi click chuot trai
			getmouseclick(WM_LBUTTONDOWN, x, y);
			cout << x << " " << y << " jj";
    	}
	}
	
}
int main(){
	//khoi tao do hoa
	int mh=IBM8514, mode=IBM8514HI;
	initgraph(&mh, &mode, "");
	dscauhoi.readFile();
	dslop.readFile();
	dsmonhoc.readFile();
	read_IDpossible();
	
	manHinhDangNhap();
//	slideDanhSach();
//	slideLopHoc();
//	slideThemLop();
//	slideXoaLop();
//	slideSuaLop();
//	slideInLop();
//	slideSinhVien();
//	slideTruocThemSV();
//	slideThemSV();
//	slideXoaSV();
//	slideTruocThemSV();
//	slideThemSV("D18CQCN02-N");
//	slideSuaSV();
//	slideXemBaiThisv();
//	slideMonHoc();
//	slideThemMH();
//	slideXoaMH();
//	slideSuaMH();
//	slideCauHoi();
//	slideThemCH();
//	slideXoaCH();
//	slideTruocSuaCH();
//	slideSuaCH("123456");
//	slideTHITRACNGHIEM();
	timToaDo();
	system("paste");
//	delay(500000000);
}

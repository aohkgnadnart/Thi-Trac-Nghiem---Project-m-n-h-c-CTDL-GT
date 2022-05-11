#include "DiemThi.h"
struct SinhVien{
	string masv, ho,ten,password;
	bool phai;
	int soMonThi=0;
	pDiemThi ketqua=NULL;
	SinhVien * next;
};
typedef SinhVien * pSinhVien;

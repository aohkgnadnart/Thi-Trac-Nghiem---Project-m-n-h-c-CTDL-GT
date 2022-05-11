#include "listLop.h"
const int MAX_SIZE_MH=1000; 
struct MonHoc{
	string mmh, tenmh;
};
typedef MonHoc * pMonHoc;
class listMH{
	pMonHoc a[MAX_SIZE_MH];
	int n=0; //kich thuoc cua mang hien tai
	bool empty(){
		return n==0? true: false;
	}
	bool full(){
		return n==MAX_SIZE_MH? true: false;
	}
	public:
	//tim kiem xem mmh da ton tai hay chua
	bool find(const string &mmh){
		for(int i=0; i<n; i++){
			if(a[i]->mmh==mmh) return true;
		}
		return false;
	}
 
	//them 1 phan tu moi
	void append(const string &mmh, const string &tenmh){
		if(full()==true){
			thongbao="Danh sach da day, khong the them";
			return ;
		}
		if(find(mmh)==true){
			thongbao="Ma mon hoc da ton tai";
			return ;
		}
		a[n]=new MonHoc;
		a[n]->mmh=mmh;
		a[n]->tenmh=tenmh;
		n++;//tang kich thuoc mang len 1
		thongbao=CONGRATULATION;
	}
 
	//thay doi ma mon hoc, tenmh
	//->keo theo thay doi mmh o ds diem thi(nam trong ds sv(nam trong ds lop)), va o danh sach cau hoi thi
	void changeMH(const string &mmh, const string &newmmh, const string &newtenmh, listLop &x, AVLtree &t){
		if(newmmh.length()>0){
			for(int i=0; i<n; i++){
				if(a[i]->mmh==newmmh){
					thongbao="Ma mon hoc moi da ton tai";
					return ;
				}
			}
		}
		bool ok=0;
		for(int i=0; i<n; i++){
			if(a[i]->mmh==mmh){
				ok=1;
				if(newtenmh.length()>0) a[i]->tenmh=newtenmh;
				if(newmmh.length()>0) a[i]->mmh=newmmh;
				break;
			}
		}
		if(ok==0){
			thongbao="Khong tim thay ma mon hoc nay";
			return ;
		}
		t.suaMMH(mmh, newmmh);
		x.changeMMH(mmh, newmmh);
		thongbao=CONGRATULATION;
	}
 
	//xoa mon hoc
	//->keo theo xoa diem thi mon hoc do->keo theo xoa bai thi cua mon do
	//->keo theo xoa danh sach cau hoi cua mon hoc do
	void deleteMH(const string &mmh, listLop &x, AVLtree &t){
		bool ok=0;
		for(int i=0; i<n; i++){
			if(a[i]->mmh==mmh){
				swap(a[i], a[n-1]);
				delete a[n-1];
				n--;
				ok=1;
				break;
			}
		}
		if(ok==0){
			thongbao="Khong tim thay ma mon hoc nay";
			return ;
		}
		x.xoaMH(mmh);
		t.xoaMH(mmh);
		thongbao=CONGRATULATION;
	}
	void writeFile(){//co ket hop giai phong bo nho
		ofstream myfile ("DSMON.txt");
		if (myfile.is_open()){
			myfile << n << "\n";
			for(int i=0; i<n; i++){
				myfile << a[i]->mmh << "\n";
				myfile << a[i]->tenmh << "\n";
				delete a[i];
			}
			myfile.close();
		}
	}
	void readFile(){
		ifstream myfile ("DSMON.txt");
		if (myfile.is_open()){
			string line;
			getline(myfile,line);
			n=toNumber(line);
			for(int i=0; i<n; i++){
				a[i]=new MonHoc;
				getline(myfile,a[i]->mmh);
				getline(myfile,a[i]->tenmh);
			}
			myfile.close();
		}
	}
};

#include "SinhVien.h"
const int MAX_SIZE_LOP=1000;
struct Lop{
	string malop;
	string tenlop;
	int soSV=0;
	pSinhVien sinhvien=NULL;
};
class listLop{
	Lop a[MAX_SIZE_LOP];
	int n=0;//kich thuoc mang hien tai
	bool empty(){
		return n==0? true: false;
	}
	bool full(){
		return n==MAX_SIZE_LOP? true: false;
	}		
	public:
		int size(){
			return n;
		}
		string malop_at(int i){
			return a[i].malop;
		}
		string tenlop_at(int i){
			return a[i].tenlop;
		}
		//tim kiem de xem da co malop nay chua, tra ve chi so vi tri neu co
		int find(const string &malop){
			for(int i=0; i<n; i++){
				if(a[i].malop==malop) return i;
			}
			return -1;
		}
		pSinhVien xemSV(const string &masv){
			for(int i=0; i<n; i++){
				pSinhVien temp=a[i].sinhvien;
				while(temp!=NULL){
					if(temp->masv==masv){
						return temp;
					}
					temp=temp->next;
				}
			}
			return NULL;
		}
		//them sinh vien vao lop
 		void addSVvaoLop(int pos, pSinhVien x){
 			for(int i=0; i<n; i++){
 				pSinhVien temp=a[i].sinhvien;
	 			while(temp!=NULL){
	 				if(temp->masv==x->masv){
	 					thongbao="Ma Sinh Vien nay da ton tai";
	 					return ;
					 }
					 temp=temp->next;
				}
			}
 			x->next=a[pos].sinhvien;
 			a[pos].sinhvien=x;
 			a[pos].soSV++;
 			thongbao=CONGRATULATION;
		}
		//xoa sinh vien khoi lop
		void xoaSVkhoiLop(const string &masv, AVLtree t){
 			for(int i=0; i<n; i++){
 				pSinhVien temp=a[i].sinhvien;
 				if(temp==NULL) continue;
 				if(temp->masv==masv){
 					a[i].sinhvien=temp->next;
 					pDiemThi temp1=temp->ketqua;
 					while(temp1!=NULL){
 						pCauDaLam temp2=temp1->baiLam;
 						while(temp2!=NULL){
 							t.giamUsers(temp2->id);
 							pCauDaLam x=temp2;
 							temp2=temp2->next;
 							delete x;
						}
						pDiemThi y=temp1;
						temp1=temp1->next;
						delete y;
					}
					delete temp;
 					a[i].soSV--;
 					thongbao=CONGRATULATION;
	 				return ;
				}
	 			while(temp->next!=NULL){
	 				if(temp->next->masv==masv){
	 					pSinhVien g=temp->next;
	 					pDiemThi temp1=g->ketqua;
	 					while(temp1!=NULL){
	 						pCauDaLam temp2=temp1->baiLam;
	 						while(temp2!=NULL){
	 							t.giamUsers(temp2->id);
	 							pCauDaLam x=temp2;
	 							temp2=temp2->next;
	 							delete x;
							}
							pDiemThi y=temp1;
							temp1=temp1->next;
							delete y;
						}
	 					temp->next=g->next;
	 					delete g;
	 					a[i].soSV--;
	 					thongbao=CONGRATULATION;
	 					return ;
					}
					temp=temp->next;
				}
			}
 			thongbao="Khong tim thay ma sinh vien nay";
		}
		//thay doi thong tin sv
		void suaSV(const string &masvcu, const string &masvmoi, const string &ho, const string &ten, const string &password, bool phai){
			if(masvmoi.length()>0){
				for(int i=0; i<n; i++){
	 				pSinhVien temp=a[i].sinhvien;
		 			while(temp!=NULL){
		 				if(temp->masv==masvmoi){
		 					thongbao="Ma Sinh Vien Moi nay da ton tai";
		 					return ;
						}
						temp=temp->next;
					}
				}
			}
			for(int i=0; i<n; i++){
 				pSinhVien temp=a[i].sinhvien;
	 			while(temp!=NULL){
	 				if(temp->masv==masvcu){
	 					if(masvmoi.length()>0) temp->masv=masvmoi;
	 					if(ho.length()>0) temp->ho=ho;
	 					if(ten.length()>0) temp->ten=ten;
	 					temp->phai=phai;
	 					if(password.length()>0) temp->password=password;
	 					thongbao=CONGRATULATION;
	 					return ;
					}
					temp=temp->next;
				}
			}
			thongbao="Ma Sinh Vien Cu khong duoc tim thay";
		}
		//them moi lop vao mang
		void append(const string &malop, const string &tenlop){
			if(find(malop)!=-1){
				thongbao="Ma lop da ton tai";
				return ;
			}
			if(full()==true){
				thongbao="Danh sach lop da day, khong the them";
				return ;
			}
			a[n].malop=malop;
			a[n].tenlop=tenlop;
			n++;
			thongbao=CONGRATULATION;
		}
		//SUA MA LOP, TEN LOP THEO MA LOP
		void change(const string &malop, const string &newmalop, const string& newtenlop){
			if(find(malop)==-1){
				thongbao="Khong tim thay ma lop cu de sua";
				return ;
			}
			if(find(newmalop)!=-1){
				thongbao="Ma lop moi da ton tai";
				return ;
			}
			for(int i=0; i<n; i++){
				if(a[i].malop==malop){
					if(newmalop.length()>0) a[i].malop=newmalop;
					if(newtenlop.length()>0) a[i].tenlop=newtenlop;
					thongbao=CONGRATULATION;
					return ;
				}
			}
		}
		//XOA LOP
//		xoa lop hoc->keo theo xoa sinh vien
//			->keo theo xoa diem thi
//				->keo theo xoa bai thi
//					->bien so nguoi dung cac cau hoi tuong ung trong bai thi giam 1
		void deleteLop(const string &malop, AVLtree &t){
			//Tim lop do, va dua lop do ve cuoi cung cua danh sach
			bool ok=0; //cho biet co lop do trong mang hay khong
			for(int i=0; i<n; i++){
				if(a[i].malop==malop){
					swap(a[i], a[n-1]);
					ok=1;
					break;
				} 
			}
			if(ok==0){
				thongbao="Khong tim thay ma lop de xoa";
				return ;
			}
 
			//xoa het moi thu lien quan den lop nay tu danh sach sv, ds diem cua sv, ds bai thi cua sv
			//bien so nguoi dung cac cau hoi tuong ung trong bai thi giam 1
			pSinhVien temp1=a[n-1].sinhvien;
			while(temp1!=NULL){
				pDiemThi temp2=temp1->ketqua;
				while(temp2!=NULL){
					pCauDaLam temp3=temp2->baiLam;
					for(int i=0; i<temp2->soCau; i++){
						t.giamUsers(temp3[i].id);
					}
					delete[] temp3;
					pDiemThi y=temp2;
					temp2=temp2->next;
					delete y;
				}
				pSinhVien z=temp1;
				temp1=temp1->next;
				delete z;
			}
			n--;//mang bot di 1 phan tu
			thongbao=CONGRATULATION;
		}
		//SUA MA MON HOC cho tat ca diem thi cua tat ca sinh vien trong tat ca cac lop
		void changeMMH(const string &mmh, const string &newmmh){
			for(int i=0; i<n; i++){
				pSinhVien temp1=a[i].sinhvien;
				while(temp1!=NULL){
					pDiemThi temp2=temp1->ketqua;
					while(temp2!=NULL){
						if(temp2->mmh==mmh){
							temp2->mmh=newmmh;
							break;
						} 
						temp2=temp2->next;
					}
					temp1=temp1->next;
				}
			}
		}
		void xoaMH(const string &mmh){
			for(int i=0; i<n; i++){
				pSinhVien temp=a[i].sinhvien;
				while(temp!=NULL){
					pDiemThi temp1=temp->ketqua;
					if(temp1==NULL){
						temp=temp->next;
						continue;
					}
					if(temp1->mmh==mmh){
						pDiemThi x=temp1->next;
						delete temp1;
						temp->soMonThi--;
						temp=temp->next;
						continue;
					}
					while(temp1->next!=NULL){
						if(temp1->next->mmh==mmh){
							pDiemThi x=temp1->next;
							temp1->next=x->next;
							delete x;
							temp->soMonThi--;
							break;
						}
					}
					temp=temp->next;
				}
			}
		}
		void writeFile(){//co ket hop giai phong bo nho
			ofstream myfile ("DSLOP.txt");
			if(myfile.is_open()){
				myfile << n << "\n";
				for(int i=0; i<n; i++){
					myfile << a[i].malop << "\n";
					myfile << a[i].tenlop << "\n";
					myfile << a[i].soSV << "\n";
					pSinhVien temp=a[i].sinhvien;
					for(int j=0; j<a[i].soSV; j++){
						myfile << temp->masv << "\n";
						myfile << temp->ho << "\n";
						myfile << temp->ten << "\n";
						myfile << temp->phai << "\n";
						myfile << temp->password << "\n";
						myfile << temp->soMonThi << "\n";
						pDiemThi temp1=temp->ketqua;
						for(int k=0; k<temp->soMonThi; k++){
							myfile << temp1->mmh << "\n";
							myfile << temp1->diem << "\n";
							myfile << temp1->soCau << "\n";
							pCauDaLam temp2=temp1->baiLam;
							for(int l=0; l<temp1->soCau; l++){
								myfile << temp2->id << "\n";
								myfile << temp2->luaChon << "\n";
								pCauDaLam z=temp2;
								temp2=temp2->next;
								delete z;
							}
							pDiemThi y=temp1;
							temp1=temp1->next;
							delete temp1;
						}
						pSinhVien x=temp;
						temp=temp->next;
						delete x;
					}
				}
				myfile.close();
			}
		}
		void readFile(){
			ifstream myfile ("DSLOP.txt");
			if (myfile.is_open()){
				string line;
				getline(myfile,line);
				n=toNumber(line);
				for(int i=0; i<n; i++){
					getline(myfile, a[i].malop);
					getline(myfile, a[i].tenlop);
					getline(myfile,line);
					a[i].soSV=toNumber(line);
					pSinhVien temp=NULL;
					for(int j=0; j<a[i].soSV; j++){
						pSinhVien x=new SinhVien;
						getline(myfile,x->masv);
						getline(myfile,x->ho);
						getline(myfile,x->ten);
						getline(myfile,line);
						x->phai=toNumber(line);
						getline(myfile,x->password);
						getline(myfile,line);
						x->soMonThi=toNumber(line);
						x->next=temp;
						temp=x;
						pDiemThi temp1=NULL;
						for(int l=0; l<temp->soMonThi; l++){
							pDiemThi y=new DiemThi;
							getline(myfile,y->mmh);
							getline(myfile,y->diem);
							getline(myfile,line);
							y->soCau=toNumber(line);
							y->next=temp1;
							temp1=y;
							pCauDaLam temp2=NULL;
							for(int k=0; k<temp1->soCau; k++){
								pCauDaLam z=new CauDaLam;
								string id, luachon;
								getline(myfile,id);
								getline(myfile, luachon);
								z->id=toNumber(id);
								z->luaChon=toNumber(luachon);
								z->next=temp2;
								temp2=z;
							}
							temp1->baiLam=temp2;
						}
						temp->ketqua=temp1;
					}
					a[i].sinhvien=temp;
				}
				myfile.close();
			}
		}
		pSinhVien svThi(const string &tk, const string &mk){
			for(int i=0; i<n; i++){
 				pSinhVien temp=a[i].sinhvien;
	 			while(temp!=NULL){
	 				if(temp->masv==tk && temp->password==mk) return temp;
					temp=temp->next;
				}
			}
			return NULL;
		}
};

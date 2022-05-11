#include <bits/stdc++.h>
using namespace std;
const string CONGRATULATION="Da thuc hien thanh cong!";
const string STRDEL="12345678901234567890123456789012345689012345678901234657890";
string thongbao;//bien thong bao sau khu thuc hien 1 lenh nao do
struct NodeQuestion{
	int id;
	string mmh, noiDung, cauA, cauB, cauC, cauD;
	int dapAn;
	NodeQuestion *left;
	NodeQuestion *right;
	int cnt=0;// so sinh vien dung cau hoi nay de thi
	int height=1;
};
typedef NodeQuestion * pNodeQuestion;
class AVLtree{//ngan hang cau hoi
	pNodeQuestion root=NULL;
 
	//chieu cao cua cay
	int height(pNodeQuestion a){
		if(a==NULL) return 0;
		return a->height;
	}
 
	//tao 1 node moi
	pNodeQuestion newNodeQuestion(int id, const string &mmh, const string &noiDung, const string &cauA, const string &cauB, const string &cauC, const string &cauD, int dapAn, int cnt=0){
		pNodeQuestion temp=new NodeQuestion;
		temp->id=id;
		temp->mmh=mmh;
		temp->noiDung=noiDung;
		temp->cauA=cauA;
		temp->cauB=cauB;
		temp->cauC=cauC;
		temp->cauD=cauD;
		temp->dapAn=dapAn;
		temp->cnt=cnt;
		temp->left=NULL;
		temp->right=NULL;
		return temp;
	}
 
	//phep xoay phai
	pNodeQuestion rightRotate(pNodeQuestion y){
		pNodeQuestion x=y->left;
		pNodeQuestion T2=x->right;
 
		//thuc hien luan chuyen
		x->right=y;
		y->left=T2;
 
		//update heights
		y->height=max(height(y->left), height(y->right))+1;
		x->height=max(height(x->left), height(x->right))+1;
 
		return x;
	}
 
	//phep xoay trai
	pNodeQuestion leftRotate(pNodeQuestion y){
		pNodeQuestion x=y->right;
		pNodeQuestion T2=x->left;
 
		//thuc hien luan chuyen
		x->left=y;
		y->right=T2;
 
		//update hights
		y->height=max(height(y->left), height(y->right))+1;
		x->height=max(height(x->left), height(x->right))+1;
 
		//dat lai y
		return x;
	}
 
	//tinh he so can bang cua node n
	int getBalance(pNodeQuestion n){
		if(n==NULL) return 0;
		return height(n->left)-height(n->right);
	}
 
	//chen 1 node vao cay va tra ve goc moi cua cay con da sua doi
	pNodeQuestion insert(pNodeQuestion node, int id, const string &mmh, const string &noiDung, const string &cauA, const string &cauB, const string &cauC, const string &cauD, int dapAn, int cnt=0){
		//thuc hien chen binh thuong
		if(node==NULL) return newNodeQuestion(id,mmh,noiDung,cauA,cauB,cauC,cauD,dapAn,cnt);
		if(id<node->id) node->left=insert(node->left, id,mmh,noiDung,cauA,cauB,cauC,cauD,dapAn,cnt);
		else if(id>node->id) node->right=insert(node->right, id,mmh,noiDung,cauA,cauB,cauC,cauD,dapAn,cnt);
		else{
			return node;//cac khoa bang nhau khong duoc chen
		}
		//cap nhat chieu cao cac nut to tien
		node->height = 1+max(height(node->left), height(node->right));
 
		//lay yeu to can bang cua to tien de kiem tra xem node nay co mat can bang khong
		int balance=getBalance(node);
		//neu nut tro nen mat can bang thi co 4 TH
 
		//left left case
		if(balance>1 && id<node->left->id) return rightRotate(node);
 
		//left right case
		if(balance>1 && id>node->left->id){
			node->left=leftRotate(node->left);
			return rightRotate(node);
		}
 
		//right right case
		if(balance<-1 && id>node->right->id) return leftRotate(node);
 
		//right left case
		if(balance<-1 && id<node->right->id){
			node->right=rightRotate(node->right);
			return leftRotate(node);
		}
		return node;
	}
 
	//tra ve node co khoa toi thieu trong cay
	pNodeQuestion minValueNodeQuestion(pNodeQuestion node){
		//lap xuong tim la ngoai cung ben trai
		while(node->left!=NULL) node=node->left;
		return node;
	}
 
	//xoa mot nut cua cay va tra ve goc moi cua cay con da sua doi
	pNodeQuestion deleteNodeQuestion(pNodeQuestion node, int id){
		//BUOC 1: XOA THEO CHUAN NHU BST TREE
		if(node==NULL) return node;
		if(id<node->id) node->left=deleteNodeQuestion(node->left, id);
		else if(id>node->id) node->right=deleteNodeQuestion(node->right, id);
 
		//neu key==node->key thi day chinh la node can xoa
		else{
			if(node->cnt>0) return node;//thong bao: cau hoi da duoc su dung de thi khong the xoa
			//node chi co 1 con hoac khong co con
			if(node->left==NULL or node->right==NULL){
				pNodeQuestion temp=(node->left==NULL? node->right: node->left);
 
				//TH khong co con
				if(temp==NULL){
					temp=node;
					node=NULL;
				} 
				else{//TH co 1 con
					*node=*temp;
				}
				delete temp;
			}
 
			//node co 2 con
			else{
				pNodeQuestion temp=minValueNodeQuestion(node->right);
 
				//dat lai data cho node------------------------------------------------------don't forget
				node->id=temp->id;
				node->mmh=temp->mmh;
				node->noiDung=temp->noiDung;
				node->cauA=temp->cauA;
				node->cauB=temp->cauB;
				node->cauC=temp->cauC;
				node->cauD=temp->cauD;
				node->dapAn=temp->dapAn;
				node->cnt=temp->cnt;
				//xoa node temp
				node->right=deleteNodeQuestion(node->right, temp->id);
			}
		}
		//neu sau khi xoa xong cay khong con node nao
		if(node==NULL) return node;
 
		//BUOC 2: CAP NHAT LAI HEIGHT CUA NODE HIEN TAI
		node->height=1+max(height(node->left), height(node->right));
 
		//BUOC 3: KIEM TRA YEU TO CAN BANG VA LAM CHO CAN BANG
		int balance=getBalance(node);
 
		//neu node khong can bang, co 4TH
 
		//left left case
		if(balance>1 and getBalance(node->left)>=0) return rightRotate(node);
 
		//left right case
		if(balance>1 and getBalance(node->left)<0){
			node->left=leftRotate(node->left);
			return rightRotate(node);
		}
 
		//right right case
		if(balance<-1 and getBalance(node->right)<=0) return leftRotate(node);
 
		//right left case
		if(balance<-1 and getBalance(node->right)>0){
			node->right=rightRotate(node->right);
			return leftRotate(node);
		}
		return node;
	}
	void change(pNodeQuestion node, int id, const string &noiDung, const string &cauA, const string &cauB, const string &cauC, const string &cauD, int dapAn){
		if(node==NULL) return ;
		if(node->id==id){
			if(node->cnt>0) return ;//thong vao: khong duoc sua vi cau nay da duoc su dung de thi
			if(noiDung.length()>0) node->noiDung=noiDung;
			if(cauA.length()>0) node->cauA=cauA;
			if(cauB.length()>0) node->cauB=cauB;
			if(cauC.length()>0) node->cauC=cauC;
			if(cauD.length()>0) node->cauD=cauD;
			node->dapAn=dapAn;
			return ;
		}
		else if(node->id>id) change(node->left, id,noiDung,cauA,cauB,cauC,cauD,dapAn);
		else change(node->right, id,noiDung,cauA,cauB,cauC,cauD,dapAn);
	}
	void changeMMH(pNodeQuestion node, const string &mmh, const string &newmmh){
		if(node==NULL) return ;
		if(node->mmh==mmh) node->mmh=newmmh;
		changeMMH(node->left, mmh, newmmh);
		changeMMH(node->right, mmh, newmmh);
	}
	struct CauXoa{
		int id;
		CauXoa * next;
	};
	typedef CauXoa * pCauXoa;
	pCauXoa cauxoa=NULL;
	//tim ra tat ca cac cau cua 1 ma mon hoc can xoa
	void search(pNodeQuestion node, const string &mmh){
		if(node==NULL) return ;
		if(node->mmh==mmh){
			pCauXoa temp=new CauXoa;
			temp->id=node->id;
			temp->next=cauxoa;
			cauxoa=temp;
		}
		search(node->left, mmh);
		search(node->right, mmh);
	}
	void findID(pNodeQuestion node, int id){
		if(node==NULL){
			thongbao="Khong tim thay ID nay";
			return ;
		} 
		if(node->id==id){
			if(node->cnt>0) thongbao="Cau hoi nay da duoc su dung, khong the xoa hoac thay doi";
			else thongbao=CONGRATULATION;
			return ;
		}
		findID(node->left, id);
		findID(node->right, id);
	}
	void giamNguoiDung(pNodeQuestion node, int id){
		if(node==NULL) return ;
		if(node->id>id) return giamNguoiDung(node->left, id);
		else if(node->id<id) return giamNguoiDung(node->right, id);
		else{
			node->cnt--;
			return ;
		}
	}
	void cnt_socaucungMMH(pNodeQuestion node, const string &mmh, int &res){
		if(node==NULL) return ;
		if(node->mmh==mmh) res++;
		cnt_socaucungMMH(node->left, mmh, res);
		cnt_socaucungMMH(node->right, mmh, res);
	}
	void cacCauCungMMH(pNodeQuestion node, const string &mmh, int arr[],  int &pos){
		if(node==NULL) return ;
		if(node->mmh==mmh) arr[pos++]=node->id;
		cacCauCungMMH(node->left, mmh, arr, pos);
		cacCauCungMMH(node->right, mmh, arr, pos);
	}
	pNodeQuestion findID1(int id, pNodeQuestion node){//ham dung khi chac chan tim thay
			if(node==NULL) return NULL;
			if(node->id>id) findID1(id, node->left);
			else if(node->id<id) findID1(id, node->right);
			else return node;
		}
	public:
		pNodeQuestion timCauHoi(int id){
			return findID1(id, root);
		}
		void dscaucungMMH(const string &mmh, int arr[]){//mang arr nay da duoc cap phat dong vua du o trong slide
			int i=0;
			cacCauCungMMH(root, mmh, arr, i);
		}
		int soCauCungMMH(const string &mmh){
			int res=0;
			cnt_socaucungMMH(root, mmh, res);
			return res;
		}
		void chen(int id, const string &mmh, const string &noiDung, const string &cauA, const string &cauB, const string &cauC, const string &cauD, int dapAn, int cnt=0){
			root=insert(root, id,mmh,noiDung,cauA,cauB,cauC,cauD,dapAn, cnt);
		}
		void xoa(int id){
			root=deleteNodeQuestion(root, id);
		}
		void suaTheoID(int id, const string &noiDung, const string &cauA, const string &cauB, const string &cauC, const string &cauD, int dapAn){
			change(root, id,noiDung,cauA,cauB,cauC,cauD,dapAn);
		}
		void suaMMH(const string &mmh, const string &newmmh){
			changeMMH(root, mmh,newmmh);
		}
		void xoaMH(const string &mmh){
			search(root, mmh);//gom cau cung ma mon hoc lai roi xoa;
			while(cauxoa!=NULL){
				xoa(cauxoa->id);
				pCauXoa temp=cauxoa->next;
				delete cauxoa;
				cauxoa=temp;
			}
		}
		int cnt_SoCauHoi(pNodeQuestion node){
			if(node==NULL) return 0;
			return 1+cnt_SoCauHoi(node->left)+cnt_SoCauHoi(node->right);
		}
		//tim id cho biet id nay co the xoa hay sua duoc khong
		void timID(int id){
			findID(root, id);
		}
		//giam nguoi dung id nay di 1
		void giamUsers(int id){
			giamNguoiDung(root, id);
		}
		struct AllCau{
			pNodeQuestion q;
			AllCau * next;
		};
		typedef AllCau * pAllCau;
		pAllCau allcau=NULL;
		void ChuyenDSLKD(pNodeQuestion node){
			if(node==NULL) return ;
			
			pAllCau temp=new AllCau;
			temp->q=node;
			temp->next=allcau;
			allcau=temp;
			
			ChuyenDSLKD(node->left);
			ChuyenDSLKD(node->right);
		}
		void writeFile(){
			ofstream myfile ("DSCAUHOI.txt");
			if (myfile.is_open()){
				int n=cnt_SoCauHoi(root);
				myfile << n << "\n";
				ChuyenDSLKD(root);
				for(int i=0; i<n; i++){
					myfile << allcau->q->id << "\n";
					myfile << allcau->q->mmh << "\n";
					myfile << allcau->q->noiDung << "\n";
					myfile << allcau->q->cauA << "\n";
					myfile << allcau->q->cauB << "\n";
					myfile << allcau->q->cauC << "\n";
					myfile << allcau->q->cauD << "\n";
					myfile << allcau->q->dapAn << "\n";
					myfile << allcau->q->cnt << "\n";
					pAllCau temp=allcau;
					allcau=allcau->next;
					delete temp;
				}
				myfile.close();
			}
		}
		int toNumber(const string& s){
			int res=0;
			for(int i=0; i<s.length(); i++){
				res=res*10+(s[i]-'0');
			}
			return res;
		}
		void readFile(){
			ifstream myfile ("DSCAUHOI.txt");
			if (myfile.is_open()){
				string line;
				getline(myfile,line);
				int n=toNumber(line);
				for(int i=0; i<n; i++){
					string id, mmh, nd, a,b,c,d,dapan,cnt;
					getline(myfile,id);
					getline(myfile,mmh);
					getline(myfile,nd);
					getline(myfile,a);
					getline(myfile,b);
					getline(myfile,c);
					getline(myfile,d);
					getline(myfile,dapan);
					getline(myfile,cnt);
					chen(toNumber(id),mmh,nd,a,b,c,d,toNumber(dapan),toNumber(cnt));
				}
				myfile.close();
			}
		}
		
};
int toNumber(const string& s){
	int res=0;
	for(int i=0; i<s.length(); i++){
		res=res*10+(s[i]-'0');
	}
	return res;
}

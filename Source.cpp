#include<iostream>
using namespace std;
#include<string>
#include<fstream>
#include<vector>



// khai báo cấu trúc ngày tháng năm sinh
struct date
{
	int ngay;
	int thang;
	int nam;
};
typedef struct date DATE;

// hàm đọc dữ liệu ngày tháng năm từ file
void Doc_Ngay_Thang_Nam(ifstream &filein, DATE &date)
{
	filein >> date.ngay;
	filein.seekg(1, 1); // dịch sang phải 1 byte để bỏ qua kí tự '/'
	filein >> date.thang;
	filein.seekg(1, 1); // dịch sang phải 1 byte để bỏ qua kí tự '/'
	filein >> date.nam;
}

// khai báo cấu trúc sinh viên
struct sinhvien
{
	string hoten;
	string masv;
	DATE ngaysinh;
	string quequan;
	string diachiEmail;
	int CMND;
	string diachihientai;
};
typedef struct sinhvien SINHVIEN;

// khai báo cấu trúc 1 cái node sinh viên

void TronMergeCMND(vector<SINHVIEN>& left, vector<SINHVIEN>& right, vector<SINHVIEN>& dssv);
void Merge_Sort_CMND(vector<SINHVIEN>& dssv);
void Merge_Sort_MSSV(vector<SINHVIEN>& dssv);
void TronMergeMSSV(vector<SINHVIEN>& left, vector<SINHVIEN>& right, vector<SINHVIEN>& dssv);
void TronMergeDATE(vector<SINHVIEN>& left, vector<SINHVIEN>& right, vector<SINHVIEN>& dssv);
void Merge_Sort_DATE(vector<SINHVIEN>& dssv);
int SoSanh2Date(DATE date1, DATE date2);

struct node
{
	SINHVIEN data; // dữ liệu của node
	struct node *pNext; // con trỏ dùng để liên kết giữa các cái node với nhau
};
typedef struct node NODE;

// ========== KHAI BÁO CẤU TRÚC DANH SÁCH LIÊN KẾT ĐƠN CÁC SINH VIÊN =========

struct list
{
	NODE *pHead;
	NODE *pTail;
};
typedef struct list LIST;

// hàm khởi tạo danh sách liên kết đơn các sinh viên
void KhoiTaoDanhSach(LIST &l)
{
	l.pHead = NULL;
	l.pTail = NULL;
}

// hàm khởi tạo 1 cái node để chuẩn bị thêm vào danh sách
NODE *KhoiTaoNode(SINHVIEN x)
{
	NODE *p = new NODE;
	if (p == NULL)
	{
		cout << "\nCap phat that bai !";
		return NULL;
	}
	p->data = x; // đưa dữ liệu của biến sinh vien x vào data của cái Node p
	p->pNext = NULL; // khởi tạo node p nhưng node p chưa có liên kết đến node nào hết
	return p;
}

// hàm thêm 1 cái node sinh viên vào đầu danh sách
void ThemDau(LIST &l, NODE *p)
{
	// nếu danh sách rỗng
	if (l.pHead == NULL)
	{
		l.pHead = l.pTail = p; // node p thêm vào cũng chính là node đầu và node cuối
	}
	else
	{
		p->pNext = l.pHead; // cho con trỏ p trỏ đến pHead
		l.pHead = p; // cập nhật lại pHead là node p
	}
}

// hàm thêm 1 cái node sinh viên vào cuối danh sách
void ThemCuoi(LIST &l, NODE *p)
{
	// nếu danh sách rỗng
	if (l.pHead == NULL)
	{
		l.pHead = l.pTail = p; // node p thêm vào cũng chính là node đầu và node cuối
	}
	else
	{
		l.pTail->pNext = p; // cho con trỏ của pTail trỏ đến node p
		l.pTail = p; // cập nhật lại pTail chính là node p
	}
}

// hàm đọc dữ liệu 1 sinh viên từ file
void Doc_Thong_Tin_1_Sinh_Vien(ifstream &filein, SINHVIEN &sv)
{
	// đọc họ tên sinh viên
	getline(filein, sv.hoten, ','); // đọc đến dấu ',' thì dừng
	// đọc mã sinh viên
	getline(filein, sv.masv, ','); // đọc đến dấu ',' thì dừng
	// đọc thông tin ngày tháng năm sinh
	Doc_Ngay_Thang_Nam(filein, sv.ngaysinh);
	filein.seekg(1, 1); // tại vị trí hiện tại dịch sang phải 1 byte để bỏ dấu phẩy
	// đọc thông tin quê quán
	getline(filein, sv.quequan, ','); // đọc đến dấu ',' thì dừng
	// đọc thông tin email
	getline(filein, sv.diachiEmail, ','); // đọc đến dấu ',' thì dừng
	// đọc thông tin cmnd
	filein >> sv.CMND; // đọc đến dấu ',' thì dừng
	// đọc thông tin địa chỉ hiện tại
	filein.seekg(1, 1);
	getline(filein, sv.diachihientai);
}

// hàm đọc danh sách sinh viên từ file
void Doc_Danh_Sach_Sinh_Vien(ifstream &filein, LIST &l)
{
	// đọc đến cuối file thì dừng
	while (filein.good())
	{
		// BƯỚC 1: ĐỌC THÔNG TIN SINH VIÊN
		SINHVIEN sv;
		Doc_Thong_Tin_1_Sinh_Vien(filein, sv);
		// BƯỚC 2: KHỞI TẠO 1 CÁI NODE SINH VIÊN
		NODE *p = KhoiTaoNode(sv);
		// BƯỚC 3: THÊM SINH VIÊN(thêm node p) VÀO DANH SÁCH LIÊN KẾT ĐƠN CÁC SINH VIÊN
		ThemCuoi(l, p);
	}
}

// hàm xuất để test dữ liệu
void Xuat(SINHVIEN sv)
{
	cout << "\nHo ten:" << sv.hoten;
	cout << "\nMa sinh vien:" << sv.masv;
	cout << "\nNgay sinh:" << sv.ngaysinh.ngay << "/" << sv.ngaysinh.thang << "/" << sv.ngaysinh.nam;
	cout << "\nQue quan:" << sv.quequan;
	cout << "\nDia chi email :" << sv.diachiEmail;
	cout << "\nCMND:" << sv.CMND;
	cout << "\nDia chi hien tai:" << sv.diachihientai;
}

// hàm xuất danh sách sinh viên
void Xuat_Danh_Sach_Sinh_Vien(LIST l)
{
	int dem = 1;
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		cout << "\n\n\t\t SINH VIEN THU " << dem++;
		Xuat(k->data);
	}
}
void CapNhatDuLieuVaoVector(LIST &l, vector <SINHVIEN> &dssv) {

	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		SINHVIEN sv;
		sv.CMND = k->data.CMND;
		sv.diachiEmail = k->data.diachiEmail;
		sv.diachihientai = k->data.diachihientai;
		sv.hoten = k->data.hoten;
		sv.masv = k->data.masv;
		sv.ngaysinh = k->data.ngaysinh;
		sv.quequan = k->data.quequan;
		dssv.push_back(sv);
	}

}
void DanhSachTatCaCacSinhVien(vector<SINHVIEN> dssv)
{
	for (int i = 0; i < dssv.size(); i++)
	{
		cout << "\nHo ten:" << dssv[i].hoten;
		cout << "\nMa sinh vien:" << dssv[i].masv;
		cout << "\nNgay sinh:" << dssv[i].ngaysinh.ngay << "/" << dssv[i].ngaysinh.thang << "/" << dssv[i].ngaysinh.nam;
		cout << "\nQue quan:" << dssv[i].quequan;
		cout << "\nDia chi email :" << dssv[i].diachiEmail;
		cout << "\nCMND:" << dssv[i].CMND;
		cout << "\nDia chi hien tai:" << dssv[i].diachihientai;
		cout << "\n\n";
	}
	cout << "\n-----------------------------------------------------------------------\n\n\n";

}

void Hoan_Vi(SINHVIEN &x, SINHVIEN &y) {
	SINHVIEN tam = x;
	x = y;
	y = tam;
}
// hàm xóa đầu
void XoaDau(LIST &l)
{
	// nếu danh sách rỗng
	if (l.pHead == NULL)
	{
		return;
	}
	NODE *p = l.pHead; // node p là node sẽ xóa
	l.pHead = l.pHead->pNext;// cập nhật lại l.pHead là phần tử kế tiếp
	delete p;
}

// xóa cuối
void XoaCuoi(LIST &l)
{
	// nếu danh sách rỗng
	if (l.pHead == NULL)
	{
		return;
	}
	// trường hợp danh sách có phần tử
	if (l.pHead->pNext == NULL)
	{
		XoaDau(l);
		return;
	}
	// duyệt từ đầu danh sách đến thằng kế cuối
	for (NODE *k = l.pHead; k != NULL; k = k->pNext)
	{
		// phát hiện thằng kế cuối
		if (k->pNext == l.pTail)
		{
			delete l.pTail; // xóa đi phần tử cuối
			k->pNext = NULL; // cho con trỏ của node kế cuối trỏ đến vùng nhớ null
			l.pTail = k; // cập nhật lại l.pTail
			return;
		}
	}
}

void TronMergeCMND(vector<SINHVIEN>& left, vector<SINHVIEN>& right, vector<SINHVIEN>& dssv) {
	int ddleft = left.size();// Lấy độ dài của chuổi bên trái
	int ddright = right.size(); // Lấy độ dài của chuổi bên phải
	int i = 0, j = 0, k = 0;
	while (j < ddleft && k < ddright)
	{
		if (left[j].CMND < right[k].CMND) {
			dssv[i] = left[j];
			j++;
		}
		else {
			dssv[i] = right[k];
			k++;
		}
		i++;
	}
	while (j < ddleft) {
		dssv[i] = left[j];
		j++; i++;
	}
	while (k < ddright) {
		dssv[i] = right[k];
		k++; i++;
	}
}
//xap xep theo CMND
void Merge_Sort_MSSV(vector<SINHVIEN>& dssv) {
	if (dssv.size() == 1) return;

	int mid = (dssv.size()) / 2;

	vector<SINHVIEN> left;
	vector<SINHVIEN> right;
	//cout << mid <<""<< endl;
	for (int j = 0; j < mid; j++)
		left.push_back(dssv[j]);
	for (int i = mid; i < dssv.size(); i++)
		right.push_back(dssv[i]);

	Merge_Sort_MSSV(left);
	Merge_Sort_MSSV(right);
	TronMergeCMND(left, right, dssv);
}
void TronMergeMSSV(vector<SINHVIEN>& left, vector<SINHVIEN>& right, vector<SINHVIEN>& dssv) {
	int ddleft = left.size();// Lấy độ dài của chuổi bên trái
	int ddright = right.size(); // Lấy độ dài của chuổi bên phải
	int i = 0, j = 0, k = 0;
	while (j < ddleft && k < ddright)
	{
		if (stoi(left[j].masv) < stoi(right[k].masv)) {
			dssv[i] = left[j];
			j++;
		}
		else {
			dssv[i] = right[k];
			k++;
		}
		i++;
	}
	while (j < ddleft) {
		dssv[i] = left[j];
		j++; i++;
	}
	while (k < ddright) {
		dssv[i] = right[k];
		k++; i++;
	}
}
//xap xep theo CMND
void Merge_Sort_CMND(vector<SINHVIEN>& dssv) {
	if (dssv.size() == 1) return;

	int mid = (dssv.size()) / 2;

	vector<SINHVIEN> left;
	vector<SINHVIEN> right;
	//cout << mid <<""<< endl;
	for (int j = 0; j < mid; j++)
		left.push_back(dssv[j]);
	for (int i = mid; i < dssv.size(); i++)
		right.push_back(dssv[i]);

	Merge_Sort_CMND(left);
	Merge_Sort_CMND(right);
	TronMergeCMND(left, right, dssv);
}
void TronMergeDATE(vector<SINHVIEN>& left, vector<SINHVIEN>& right, vector<SINHVIEN>& dssv) {
	int ddleft = left.size();// Lấy độ dài của chuổi bên trái
	int ddright = right.size(); // Lấy độ dài của chuổi bên phải
	int i = 0, j = 0, k = 0;
	while (j < ddleft && k < ddright)
	{
		if ((SoSanh2Date(left[j].ngaysinh,right[k].ngaysinh)) == 1) {
			dssv[i] = left[j];
			j++;
		}
		else {
			dssv[i] = right[k];
			k++;
		}
		i++;
	}
	while (j < ddleft) {
		dssv[i] = left[j];
		j++; i++;
	}
	while (k < ddright) {
		dssv[i] = right[k];
		k++; i++;
	}

}
void Merge_Sort_DATE(vector<SINHVIEN>& dssv) {
	if (dssv.size() == 1) return;

	int mid = (dssv.size()) / 2;

	vector<SINHVIEN> left;
	vector<SINHVIEN> right;
	//cout << mid <<""<< endl;
	for (int j = 0; j < mid; j++)
		left.push_back(dssv[j]);
	for (int i = mid; i < dssv.size(); i++)
		right.push_back(dssv[i]);

	Merge_Sort_DATE(left);
	Merge_Sort_DATE(right);
	TronMergeDATE(left, right, dssv);
}
void Them1SV(SINHVIEN &sv) {
	cout << "Nhap Ma So Sinh Vien:";
	cin >> sv.masv;
	cin.ignore();
	cout << "Nhap Ho Ten Sinh Vien:";
	getline(cin, sv.hoten);
	cout << "Nhap SCMND Sinh Vien:";
	cin >> sv.CMND;
	cout << "Nhap vao ngay thang nam sinh\n";
	do
	{
		cout << "*Ngay sinh: ";
		cin >> sv.ngaysinh.ngay;
		fflush(stdin);
	} while (sv.ngaysinh.ngay > 31 || sv.ngaysinh.ngay < 1);
	do
	{
		fflush(stdin);
		cout << "*Thang sinh: ";
		cin >> sv.ngaysinh.thang;
	} while (sv.ngaysinh.thang > 12 || sv.ngaysinh.thang < 1);
	do
	{
		fflush(stdin);
		cout << "*Nam sinh: ";
		cin >> sv.ngaysinh.nam;
	} while (sv.ngaysinh.nam > 2019 || sv.ngaysinh.nam < 1000);
	cin.ignore();
	cout << "Nhap noi sinh Sinh Vien:";
	getline(cin, sv.quequan);
	cout << "Nhap email Sinh Vien:";
	getline(cin, sv.diachiEmail);
	cout << "Nhap noi song hien tai Sinh Vien:";
	getline(cin, sv.diachiEmail);

}
void Chen1SVTheoCMND(vector<SINHVIEN> &dssv) {
	SINHVIEN sv1;
	Them1SV(sv1);
	dssv.push_back(sv1);
	Merge_Sort_CMND(dssv);
}
void Chen1SVTheoMSSV(vector<SINHVIEN> &dssv) {
	SINHVIEN sv1;
	Them1SV(sv1);
	dssv.push_back(sv1);
	Merge_Sort_MSSV(dssv);
}
void Chen1SVTheoDATE(vector<SINHVIEN> &dssv) {
	SINHVIEN sv1;
	Them1SV(sv1);
	dssv.push_back(sv1);
	Merge_Sort_DATE(dssv);
}
int SoSanh2Date(DATE date1, DATE date2) {
	if (date1.nam < date2.nam) return 1;
	if (date1.nam > date2.nam) return 0;
	if (date1.nam == date2.nam) {
		if (date1.thang < date2.thang) return 1;
		if (date1.thang > date2.thang)return 0;
		if (date1.thang == date2.thang) {
			if (date1.ngay <= date2.ngay) return 1;
			else return 0;
		}
	}
}
void xoa1SVtheoten(string ten, vector<SINHVIEN>& dssv) {
	cout << "Nhap ten cua Sinh vien ma ban can xoa: ";
	cin >> ten;
	for (int i = 0; i < ten.length(); i++) {
		if (ten[i] <= 'z' && ten[i] >= 'a')
			ten[i] -= 32;
	}
	for (int i = 0; i < dssv.size(); i++) {
		if (dssv[i].hoten.find(ten) != string::npos) {
			dssv.erase(dssv.begin() + i);
		}
	}
}
void xoa1SVtheongay(vector<SINHVIEN>& dssv) {
	int tam;
	cout << "Nhap vao ngay sinh cua Sinh vien ma ban can xoa: ";
	cin >> tam;
	for (int i = 0; i < dssv.size(); i++) {
		if (dssv[i].ngaysinh.ngay == tam) {
			dssv.erase(dssv.begin() + i);
		}
	}
}
void timkiemSVtheomssv(string mssv, vector<SINHVIEN>& dssv, int& vitri) {
	cout << "Nhap ma so can tim:";
	cin >> mssv;
	int flag = 0;
	for (int i = 0; i < dssv.size(); i++) {
		if (dssv[i].masv == mssv) {
			cout << "\n*****************************DA TIM THAY HOC SINH CAN TIM*****************************\n";
			cout
				<< "Ma So Sinh Vien: " << dssv[i].masv
				<< "\nTen Sinh Vien: " << dssv[i].hoten
				<< "\nCMND: " << dssv[i].CMND
				<< "\nNgay sinh:" << dssv[i].ngaysinh.ngay << "/" << dssv[i].ngaysinh.thang << "/" << dssv[i].ngaysinh.nam
				<< "\nNoi Sinh: " << dssv[i].quequan
				<< "\nEmail: " << dssv[i].diachiEmail
				<< "\nNoi Song Hien Tai:" << dssv[i].diachihientai
				<< "\n---------------\n";
			flag++;
			vitri = i + 1;
		}
	}

	if (flag == 0) {
		cout << "\n*****************************KHONG TIM THAY*****************************\n";
	}
}
void xuatfileexcel(vector<SINHVIEN>& dssv) {
	ofstream myfile;
	myfile.open("DSSV.csv");
	myfile << "MSSV,Ho Va Ten,So CMND,Ngay Thang Nam Sinh,Que Quan,Email,Dia Chi Hien Tai\n";
	for (int i = 0; i < dssv.size(); i++) {
		myfile << dssv[i].masv << "," << dssv[i].hoten << "," << dssv[i].CMND << "," << dssv[i].ngaysinh.ngay <<"/"<< dssv[i].ngaysinh.thang << "/" <<dssv[i].ngaysinh.nam << "," << dssv[i].quequan << "," << dssv[i].diachiEmail << "," << dssv[i].diachihientai << "\n";
	}
	cout << "Xuat File Thanh Cong";
	myfile.close();
}
int main()
{
	vector <SINHVIEN> dssv;
	LIST l;
	KhoiTaoDanhSach(l);
	// mở file lên
	ifstream filein;
	filein.open("SINHVIEN.csv", ios::in);
	Doc_Danh_Sach_Sinh_Vien(filein, l);
	XoaCuoi(l);
	//Xuat_Danh_Sach_Sinh_Vien(l);
	CapNhatDuLieuVaoVector(l, dssv);
	DanhSachTatCaCacSinhVien(dssv);
	int luachon;
	while (true) {
		cout << "\n\n\t\t =========== MENU ===========";
		cout << "\n1. Sap xep MergeSort theo CMND";
		cout << "\n2. Sap xep MergeSort theo MSSV";
		cout << "\n3. Sap xep MergeSort theo DATE";
		cout << "\n4. Chen 1 sinh vien sap xep MergeSort theo CMND";
		cout << "\n5. Chen 1 sinh vien sap xep MergeSort theo MSSV";
		cout << "\n6. Chen 1 sinh vien sap xep MergeSort theo DATE";
		cout << "\n7. Xoa 1 sinh vien theo ten";
		cout << "\n8. Xoa 1 sinh vien theo ngay";
		cout << "\n9. Tim kiem 1 sinh vien theo mssv";
		cout << "\n10. Hien thi danh sach Sinh vien";
		cout << "\n0. Ket thuc";
		cout << "\n\n\t\t =========== END ===========";
		cout << "\nNhap lua chon: ";
		cin >> luachon;
		switch (luachon)
		{
		case 1:
		{
			Merge_Sort_CMND(dssv);
			cout << "\n----------DANH SACH CAC SINH VIEN DUOC SAP XEP MERGSORT THEO CMND----------";
			DanhSachTatCaCacSinhVien(dssv);
			break;
		}
		case 2:
		{
			Merge_Sort_MSSV(dssv);
			cout << "\n----------DANH SACH CAC SINH VIEN DUOC SAP XEP MERGSORT THEO MA SO SINH VIEN----------";
			DanhSachTatCaCacSinhVien(dssv);
			break;
		}
		case 3:
		{
			Merge_Sort_DATE(dssv);
			cout << "\n----------DANH SACH CAC SINH VIEN SAP XEP MERGSORT THEO NGAY SINH----------";
			DanhSachTatCaCacSinhVien(dssv);
			break;
		}
		case 4:
		{
			Chen1SVTheoCMND(dssv);
			cout << "\n----------DANH SACH CAC SINH VIEN SAU KHI THEM 1 SINH VIEN SAP XEP MERGSORT THEO CMND----------";
			DanhSachTatCaCacSinhVien(dssv);
			break;
		}
		case 5:
		{
			Chen1SVTheoMSSV(dssv);
			cout << "\n----------DANH SACH CAC SINH VIEN SAU KHI THEM 1 SINH VIEN SAP XEP MERGSORT THEO MSSV----------";
			DanhSachTatCaCacSinhVien(dssv);
			break;
		}
		case 6:
		{
			Chen1SVTheoDATE(dssv);
			cout << "\n----------DANH SACH CAC SINH VIEN SAU KHI THEM 1 SINH VIEN SAP XEP MERGSORT THEO DATE----------";
			DanhSachTatCaCacSinhVien(dssv);
			break;
		}
		case 7:
		{
			string ten;
			xoa1SVtheoten(ten, dssv);
			cout << "\n----------DANH SACH CAC SINH VIEN DUOC SAU KHI XOA 1 SINH VIEN THEO TEN----------";
			DanhSachTatCaCacSinhVien(dssv);
			break;
		}
		case 8:
		{
			xoa1SVtheongay(dssv);
			cout << "\n----------DANH SACH CAC SINH VIEN DUOC SAU KHI XOA 1 SINH VIEN THEO NGAY ----------";
			DanhSachTatCaCacSinhVien(dssv);
			break;
		}
		case 9:
		{
			string tim; int kiem;
			timkiemSVtheomssv(tim, dssv, kiem);
			break;
		}
		case 10:
		{
			cout << "\n----------DANH SACH TAT CA CAC SINH VIEN----------";
			DanhSachTatCaCacSinhVien(dssv);
			break;
		}
		case 0: {
			goto exit_loop;
		}
		default:
			cout << "LUA CHON KHONG DUNG XIN NHAP LAI";
		}
	}
exit_loop:;
	xuatfileexcel(dssv);
	filein.close();
	system("pause");
	return 0;
}
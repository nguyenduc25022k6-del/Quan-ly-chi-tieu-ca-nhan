#ifndef TIENICH_H
#define TIENICH_H

#define MAX_GHICHU   200
#define MAX_DANHMUC   64
#define MAX_STR       64

/* Loại giao dịch */
typedef enum {
    LOAI_THU = 0,
    LOAI_CHI = 1
} LoaiGiaoDich;

/* Danh mục chi tiêu */
typedef enum {
    DM_LUONG      = 0,
    DM_THUONG     = 1,
    DM_ANUONG     = 2,
    DM_DICHUY     = 3,
    DM_HOCTAP     = 4,
    DM_GIAITRI    = 5,
    DM_SINHHOAT   = 6,
    DM_SUCKHOE    = 7,
    DM_KHAC       = 8,
    DM_COUNT      = 9   /* Tổng số danh mục */
} DanhMuc;

/* Tra cứu chuỗi tên danh mục */
const char* TenDanhMuc(DanhMuc dm);
const char* TenLoai(LoaiGiaoDich loai);
DanhMuc     DocDanhMuc(const char* ten);
LoaiGiaoDich DocLoai(const char* ten);

/* Nhập dữ liệu an toàn */
int    NhapSoNguyen(const char* nhacNho, int min, int max);
double NhapSoThuc(const char* nhacNho, double min);
void   NhapChuoi(const char* nhacNho, char* buf, int maxLen);
int    NhapNgay(int* ngay, int* thang, int* nam);

/* Tiện ích */
void LamSachBoDem(void);
int  NgayHopLe(int ngay, int thang, int nam);
void InDuongKe(char ky, int so);

#endif /* TIENICH_H */

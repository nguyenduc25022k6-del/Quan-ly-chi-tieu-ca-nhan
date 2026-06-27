#ifndef NGANSACH_H
#define NGANSACH_H

#include "tienich.h"

/* Struct nút DSLK đơn */
typedef struct NganSach {
    DanhMuc       danhMuc;
    int           thang, nam;
    double        hanMuc;
    struct NganSach* tiep;
} NganSach;

/* CRUD */
void  ThietLapNganSach(NganSach** dau);
void  SuaNganSach(NganSach* dau);
void  XoaNganSach(NganSach** dau);
void  XemDanhSachNganSach(const NganSach* dau);

/* Truy vấn */
double LayHanMuc(const NganSach* dau, DanhMuc dm, int thang, int nam);

/* File I/O */
void DocFileNganSach(NganSach** dau);
void GhiFileNganSach(const NganSach* dau);

/* Giải phóng bộ nhớ */
void GiaiPhongNganSach(NganSach** dau);

#endif /* NGANSACH_H */

#ifndef BAOCAO_H
#define BAOCAO_H

#include "giaodich.h"
#include "ngansach.h"

/* Báo cáo tháng */
void BaoCaoThang(const GiaoDich* gdDau, const NganSach* nsDau);

/* Báo cáo quý */
void BaoCaoQuy(const GiaoDich* gdDau);

/* Báo cáo năm */
void BaoCaoNam(const GiaoDich* gdDau);

/* Cảnh báo vượt hạn mức */
void CanhBaoNganSach(const GiaoDich* gdDau, const NganSach* nsDau,
                     int thang, int nam);

/* Biểu đồ ASCII */
void BieuDoChiTieu(const GiaoDich* gdDau, int thang, int nam);

#endif /* BAOCAO_H */

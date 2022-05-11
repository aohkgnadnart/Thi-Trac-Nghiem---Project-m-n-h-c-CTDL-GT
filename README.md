# projectCTDLGT

## Yêu cầu Đề tài Thi trắc nghiệm
Viết chương trình có các chức năng, và cấu trúc dữ liệu theo yêu cầu:
- Chức năng:
  - Giáo viên: 
    - Đăng nhập (tài khoản: GV, mật khẩu: GV)
    - Thêm, xóa, sửa, xem danh sách lớp học
    - Thêm, xóa, sửa thông tin sinh viên(bao gồm tài khoản, mật khẩu để sinh viên đăng nhập để thi)
    - Xem bài thi, xem điểm của sinh viên
    - Thêm, xóa, sửa môn học
    - Thêm xóa sửa câu hỏi thi của môn học
  - Sinh viên:
    - Đăng nhập
    - Thi (chọn môn thi, thời gian thi, số câu hỏi)
    - Xem điểm sau khi làm xong.
- Cấu trúc dữ liệu yêu cầu:
  - danh sách lớp: mảng cấp phát tĩnh
  - danh sách sinh viên của một lớp: danh sách liên kết đơn
  - danh sách môn học: mảng cấp phát động
  - danh sách tất cả câu hỏi thi: cây nhị phân tìm kiếm cân bằng
  - danh sách câu đã làm trong 1 bài thi: danh sách liên kết đơn
  - danh sách điểm thi các môn học của 1 sinh viên: danh sách liên kết đơn
- **Lưu ý**: Không được sử dụng thư viện chuẩn C++ (cho phép dùng string).
## Tài liệu liên quan để hoàn thành đề tài
- [Con trỏ](https://cplusplus.com/doc/tutorial/pointers/)
- [Cấp phát tĩnh, cấp phát động](https://www.stdio.vn/modern-cpp/cap-phat-tinh-va-cap-phat-dong-H133BL)
- [Cây nhị phân tìm kiếm cân bằng](https://vi.wikipedia.org/wiki/C%C3%A2y_AVL)
- [Đọc ghi file](https://cplusplus.com/doc/tutorial/files/)
- [Hướng dẫn cài đặt và thêm thư viện đồ họa vào Dev C/C++](https://thaynhuom.edu.vn/huongdancaidatvathemthuviendohoatrongc/)

## Demo chức năng
- Giáo viên: 
![20220511_124508](https://user-images.githubusercontent.com/83690404/167779070-8acc50c4-43cb-4c31-9bbb-437fd08e07d1.gif)

- Sinh viên:
![20220511_125536](https://user-images.githubusercontent.com/83690404/167779091-d0290d88-22f5-438b-ae44-e9f39af86172.gif)

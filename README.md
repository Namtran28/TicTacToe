### TicTacToeGAME :joystick:

I. Giới thiệu
1. AI engine.
  - Cài đặt các bước đi cho AI.
  - Tính điểm sau mỗi bước di chuyển.
    - Nếu bước đi dẫn đến -1 (thua) thì không đi, chỉ đi các nước đi có điểm số 0 (hòa) hoặc +1 (thắng).
    - Từ cách tính điểm từng bước đi để đưa ra nước đi hợp lý nhất.
  - kiểm tra tính kết thúc của trò chơi
    - Nếu có một trong hai người đạt được ba điểm thẳng hàng thì thắng, ngược lại là thua. 
2. Giao diện người dùng.
  - Lựa chọn người chơi (x hoặc o).
  - Người chơi x được bắt đầu trước người chơi o.
  - Yêu cầu người chơi chọn nước đi của mình.
  - Báo cho người chơi các nước đi không hợp lý.
3. Hiển thị màn hình.
  - Hiển thị bàn cờ lần lượt sau mỗi nước đi của máy và người chơi.

II. Bàn cờ
- File game: XO.cpp
- Thể loại game: TicTacToe 3x3

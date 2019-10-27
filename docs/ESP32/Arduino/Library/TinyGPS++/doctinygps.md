Sử dụng
Giả sử bạn có một Arduino được nối với một thiết bị GPS ngoài luồng và bạn muốn hiển thị độ cao của mình. Bạn chỉ cần tạo một cá thể TinyGPS ++ như thế này:

1
2
#include "TinyGPS++.h"
TinyGPSPlus gps;
Cho ăn liên tục các ký tự từ thiết bị GPS của bạn:

1
2
while (ss.available() > 0)
  gps.encode(ss.read());
Sau đó truy vấn nó để biết thông tin mong muốn:

1
2
if (gps.altitude.isUpdated())
  Serial.println(gps.altitude.meters());
Sự khác biệt từ TinyGPS
Mặc dù TinyGPS ++ chia sẻ nhiều công cụ phân tích cú pháp nhỏ gọn tương tự với TinyGPS, giao diện lập trình viên của nó có phần trực quan hơn. Một ví dụ đơn giản, đây là cách dễ dàng để in ra vĩ độ, kinh độ và độ cao hiện tại trong TinyGPS ++:

1
2
3
Serial.print("LAT=");  Serial.println(gps.location.lat(), 6);
Serial.print("LONG="); Serial.println(gps.location.lng(), 6);
Serial.print("ALT=");  Serial.println(gps.altitude.meters());
Cả hai thư viện đều trích xuất vị trí cơ bản, độ cao, khóa học, thời gian và ngày tháng, v.v. từ hai câu NMEA phổ biến là $ GPGGA và $ GPRMC . Nhưng có một số câu thú vị khác, cả NMEA được xác định và thuộc sở hữu của nhà cung cấp, đang chờ để được thu hoạch.

Ví dụ, hãy xem xét $ GPRMB tối nghĩa , cung cấp thông tin điều hướng tối thiểu được đề xuất của Bỉ nếu bạn có một điểm đến đích được xác định.

$ GPRMB, A, 4.08, L, EGLL, EGLM, 5130.02, N, 00046.34, W, 004.6.213.9.122.9, A * 3D
Với TinyGPS ++, giờ đây có thể trích xuất chỉ LÊ trong lĩnh vực thứ ba (nó có nghĩa là steer L eft! Thật dễ dàng với đối tượng theo dõi TinyGPSCustom mới:

1
2
3
TinyGPSCustom steerDirection(gps, "GPRMB", 3);
...
Serial.print(steerDirection.value()); // prints "L" or "R"
Đương nhiên, chức năng bổ sung này đi kèm với một số chi phí. TinyGPS ++ tiêu thụ bộ nhớ nhiều hơn TinyGPS và giao diện của nó không tương thích. Vậy làm thế nào để quyết định có nên cập nhật? Dưới đây là hướng dẫn:

Hãy xem xét TinyGPS ++ trên TinyGPS nếu:

Khả năng tương thích với mã hiện có (sử dụng TinyGPS) là không cần thiết.
Bản phác thảo của bạn không đạt đến giới hạn tài nguyên RAM hoặc flash.
Bạn đang chạy trên Do hoặc bộ xử lý có thể tận dụng độ chính xác cao hơn của dấu phẩy động kép 64 bit.
Bạn thích mô hình đối tượng trực quan hơn.
Bạn cần truy vấn dữ liệu NMEA ngoài vị trí cơ bản, ngày, giờ, độ cao, khóa học, tốc độ, vệ tinh hoặc hdop.
Nuôi dưỡng đối tượng đói
Để làm cho TinyGPS ++ hoạt động, bạn phải liên tục chuyển các ký tự đến nó từ mô-đun GPS bằng phương thức encode () . Ví dụ: nếu mô-đun GPS của bạn được gắn vào chân 4 (RX) và 3 (TX), bạn có thể viết mã như thế này:

1
2
3
4
5
6
SoftwareSerial ss(4, 3);
void loop()
{
  while (ss.available() > 0)
    gps.encode(ss.read);
  ...
Sau khi đối tượng đã được cho ăn, bạn có thể truy vấn nó để xem có trường dữ liệu nào được cập nhật không:

1
2
3
4
5
6
  if (gps.location.isUpdated())
  {
    Serial.print("LAT="); Serial.print(gps.location.lat(), 6);
    Serial.print("LNG="); Serial.println(gps.location.lng(), 6);
  }
} // end loop()
Mô hình đối tượng TinyGPS ++
Đối tượng TinyGPS ++ chính chứa một số đối tượng phụ cốt lõi:

vị trí - sửa chữa vị trí mới nhất
ngày - bản sửa lỗi ngày mới nhất (UT)
thời gian - thời gian sửa lỗi mới nhất (UT)
tốc độ - tốc độ mặt đất hiện tại
khóa học - khóa học mặt đất hiện tại
độ cao - sửa chữa độ cao mới nhất
vệ tinh - số lượng vệ tinh có thể nhìn thấy, tham gia
hdop - giảm độ chính xác theo chiều ngang
Mỗi phương thức cung cấp các phương thức để kiểm tra giá trị hiện tại của nó, đôi khi ở nhiều định dạng và đơn vị. Đây là một danh sách đầy đủ:

1
2
3
4
5
6
7
số 8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
Serial.println(gps.location.lat(), 6); // Latitude in degrees (double)
Serial.println(gps.location.lng(), 6); // Longitude in degrees (double)
Serial.print(gps.location.rawLat().negative ? "-" : "+");
Serial.println(gps.location.rawLat().deg); // Raw latitude in whole degrees
Serial.println(gps.location.rawLat().billionths);// ... and billionths (u16/u32)
Serial.print(gps.location.rawLng().negative ? "-" : "+");
Serial.println(gps.location.rawLng().deg); // Raw longitude in whole degrees
Serial.println(gps.location.rawLng().billionths);// ... and billionths (u16/u32)
Serial.println(gps.date.value()); // Raw date in DDMMYY format (u32)
Serial.println(gps.date.year()); // Year (2000+) (u16)
Serial.println(gps.date.month()); // Month (1-12) (u8)
Serial.println(gps.date.day()); // Day (1-31) (u8)
Serial.println(gps.time.value()); // Raw time in HHMMSSCC format (u32)
Serial.println(gps.time.hour()); // Hour (0-23) (u8)
Serial.println(gps.time.minute()); // Minute (0-59) (u8)
Serial.println(gps.time.second()); // Second (0-59) (u8)
Serial.println(gps.time.centisecond()); // 100ths of a second (0-99) (u8)
Serial.println(gps.speed.value()); // Raw speed in 100ths of a knot (i32)
Serial.println(gps.speed.knots()); // Speed in knots (double)
Serial.println(gps.speed.mph()); // Speed in miles per hour (double)
Serial.println(gps.speed.mps()); // Speed in meters per second (double)
Serial.println(gps.speed.kmph()); // Speed in kilometers per hour (double)
Serial.println(gps.course.value()); // Raw course in 100ths of a degree (i32)
Serial.println(gps.course.deg()); // Course in degrees (double)
Serial.println(gps.altitude.value()); // Raw altitude in centimeters (i32)
Serial.println(gps.altitude.meters()); // Altitude in meters (double)
Serial.println(gps.altitude.miles()); // Altitude in miles (double)
Serial.println(gps.altitude.kilometers()); // Altitude in kilometers (double)
Serial.println(gps.altitude.feet()); // Altitude in feet (double)
Serial.println(gps.satellites.value()); // Number of satellites in use (u32)
Serial.println(gps.hdop.value()); // Horizontal Dim. of Precision (100ths-i32)
Hiệu lực, cập nhật trạng thái và tuổi
Bạn có thể kiểm tra giá trị của một đối tượng bất cứ lúc nào, nhưng trừ khi TinyGPS ++ gần đây đã được cung cấp từ GPS, thì nó không nên được coi là hợp lệ và cập nhật. Phương thức isValid () sẽ cho bạn biết liệu đối tượng có chứa bất kỳ dữ liệu hợp lệ nào không và có an toàn để truy vấn hay không.

Tương tự, isUpdated () cho biết liệu giá trị của đối tượng đã được cập nhật (không nhất thiết phải thay đổi ) kể từ lần cuối bạn truy vấn nó.

Cuối cùng, nếu bạn muốn biết dữ liệu của đối tượng cũ như thế nào, hãy gọi phương thức age () của nó , trả về số mili giây kể từ lần cập nhật cuối cùng. Nếu giá trị này trả về giá trị lớn hơn 1500 hoặc hơn, đó có thể là dấu hiệu của sự cố như bản sửa lỗi bị mất.

Gỡ lỗi
Khi bản phác thảo TinyGPS ++ thất bại, thường là do đối tượng nhận được luồng NMEA không hoàn chỉnh hoặc có lẽ không có gì cả.

May mắn thay, thật dễ dàng để xác định điều gì sai khi sử dụng một số phương pháp chẩn đoán tích hợp:

charsProcessed () - tổng số ký tự mà đối tượng nhận được
câuWithFix () - số câu $ GPRMC hoặc $ GPGGA đã sửa
failChecksum () - số lượng câu của tất cả các loại không thành công trong bài kiểm tra tổng kiểm tra
PassChecksum () - số lượng câu của tất cả các loại đã vượt qua bài kiểm tra tổng kiểm tra
Nếu bản phác thảo của bạn đã chạy được một lúc nhưng charsProcessed () đang trả về 0, bạn có thể gặp vấn đề với kết nối dây hoặc nối tiếp. (Nếu dữ liệu không bao giờ đến từ thiết bị GPS, lý do là nó không đến TinyGPS ++.) Tôi thường chèn một mệnh đề gỡ lỗi nhỏ vào bản phác thảo GPS của mình phát hiện tình trạng này sau đó in ra luồng đến:

1
2
3
4
5
6
7
số 8
9
10
// Debug: if we haven't seen lots of data in 5 seconds, something's wrong.
if (millis() > 5000 && gps.charsProcessed() < 10) // uh oh
{
  Serial.println("ERROR: not getting any GPS data!");
  // dump the stream to Serial
  Serial.println("GPS stream dump:");
  while (true) // infinite loop
    if (ss.available() > 0) // any data coming in?
      Serial.write(ss.read());
}
Một thất bại phổ biến khác là khi các câu được gửi đến TinyGPS ++ không đầy đủ. Điều này thường xảy ra khi bạn truy xuất các ký tự từ GPS quá chậm hoặc không thường xuyên đến nỗi một số bị mất. Triệu chứng rất dễ phát hiện: thất bại kiểm tra .

http://arduiniana.org/libraries/tinygpsplus/


Giải thích: Mỗi câu NMEA kết thúc bằng một trường số đại diện cho tổng kết toán học của tất cả các ký tự trong câu. Nó ở đó để đảm bảo tính toàn vẹn dữ liệu. Nếu con số này không khớp với tổng số thực tế (có lẽ vì một số ký tự bị sai lệch), TinyGPS ++ chỉ cần loại bỏ toàn bộ câu và tăng một bộ đếm tổng kiểm tra nội bộ không thành công. Bạn có thể đọc quầy này với:

1
2
3
4
5
6
Serial.print("Sentences that failed checksum=");
Serial.println(gps.failedChecksum());
 
// Testing overflow in SoftwareSerial is sometimes useful too.
Serial.print("Soft Serial device overflowed? ");
Serial.println(ss.overflow() ? "YES!" : "No");
Nếu bộ đếm tổng kiểm tra liên tục tăng, bạn có vấn đề. (Gợi ý: không sử dụng độ trễ () trong bản phác thảo của bạn.)

Khai thác câu NMEA tùy chỉnh
Một trong những tính năng mới tuyệt vời của TinyGPS ++ là khả năng trích xuất dữ liệu tùy ý từ bất kỳ câu nào giống như NMEA hoặc NMEA. Đọc một số câu thú vị hiện có, sau đó kiểm tra để đảm bảo rằng bộ thu GPS của bạn có thể tạo ra chúng.

Ý tưởng đằng sau trích xuất tùy chỉnh là bạn nói với TinyGPS ++ tên câu và số trường bạn quan tâm, như thế này:

1
TinyGPSCustom magneticVariation(gps, "GPRMC", 10)
Điều này hướng dẫn TinyGPS ++ để mắt đến các câu $ GPRMC và trích xuất trường được phân tách bằng dấu phẩy thứ 10 mỗi khi một dòng chảy qua. Tại thời điểm này, từ tính là một đối tượng mới giống như các đối tượng tích hợp. Bạn có thể truy vấn nó giống như những người khác:

1
2
3
4
5
if (magneticVariation.isUpdated())
{
  Serial.print("Magnetic variation is ");
  Serial.println(magneticVariation.value());
}
Thiết lập một sửa chữa
Các đối tượng TinyGPS ++ phụ thuộc vào bản phác thảo máy chủ của chúng để cung cấp cho chúng dữ liệu GPS NMEA hợp lệ và hiện tại. Để đảm bảo thế giới quan của họ liên tục được cập nhật, ba điều phải xảy ra:

Bạn phải liên tục cung cấp dữ liệu NMEA nối tiếp đối tượng với encode () .
Các câu NMEA phải vượt qua bài kiểm tra tổng kiểm tra.
Đối với các đối tượng tích hợp (không tùy chỉnh), các câu NMEA phải tự báo cáo là hợp lệ. Đó là, nếu câu $ GPRMC báo cáo tính hợp lệ của Triệu Vv (void) thay vì Câu A (hoạt động) hoặc nếu câu $ GPGGA báo cáo loại sửa 0 0 (không sửa), thì thông tin về vị trí và độ cao bị loại bỏ (mặc dù thời gian và ngày được giữ lại).
Có thể mất vài phút để thiết bị khắc phục sự cố, đặc biệt là thiết bị đã đi được một quãng đường hoặc một thời gian dài đã trôi qua kể từ lần sử dụng cuối cùng.

Khoảng cách và khóa học
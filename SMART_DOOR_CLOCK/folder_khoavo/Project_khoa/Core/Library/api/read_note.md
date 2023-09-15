##### - LCD    --> I2C1 --> PB6: SCL ; PB7: SDA
##### - DS1307 --> I2C3 --> PA8: SCL ; PC9: SDA
##### --> CHECK ĐỊA CHỈ I2C-LCD, của Khoa là 0x27.

#brief: 
####api_handle_display library is cover functions about display

#guide:
***to use function in main***

ex: **h_display_time()** --> display time,date,dow on LCD
--> include "api_handle.h"
--> init   lcd_init(&hi2c1);  ds1307_init(&hi2c3);	
--> and call h_display_time(); to display	

.....


###note:
**ds1307_set_date_time(...)**
	--> sau khi chạy xong lần đầu để set thời gian thực cho ds1307 thì comment dòng này và chạy lại để trường hợp mất nguồn thì khi khởi động lại sẽ không set lại thời gian cũ này. 
 	 (ds1307 tự động duy trì thgian chính xác nhờ pin (có thể 2-10 năm))
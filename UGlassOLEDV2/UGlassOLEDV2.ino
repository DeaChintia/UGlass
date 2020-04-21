#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// display height = 32px, width = 128px
// coordinate system start from 0
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

String command_str[] = {"", "", "", "", "", "", ""};
byte index = 0;

static const unsigned char PROGMEM ICON_ENV_OPEN[] =
{ 0x01, 0x80, 0x03, 0xc0, 0x06, 0x60, 0x0c, 0x30,
  0x18, 0x18, 0x30, 0x0c, 0x60, 0x06, 0x70, 0x0e,
  0x58, 0x1a, 0x4c, 0x32, 0x43, 0xc2, 0x41, 0x82,
  0x40, 0x02, 0x40, 0x02, 0x40, 0x02, 0x7f, 0xfe
};

static const unsigned char PROGMEM ICON_ENV_CLOSE[] =
{ 0x00, 0x00, 0x00, 0x00, 0x7f, 0xfe, 0xff, 0xff,
  0xf8, 0x1f, 0xdc, 0x3b, 0xce, 0x73, 0xc7, 0xe3,
  0xc3, 0xc3, 0xc1, 0x83, 0xc0, 0x03, 0xc0, 0x03,
  0xff, 0xff, 0x7f, 0xfe, 0x00, 0x00, 0x00, 0x00
};

// ARROW ICONS
static const unsigned char PROGMEM ICON_TOP_ARROW[] =
{ 0x00, 0x80, 0x01, 0xc0, 0x03, 0xe0, 0x07, 0xf0,
  0x0f, 0xf8, 0x1f, 0xfc, 0x3f, 0xfe, 0x03, 0xe0,
  0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0,
  0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0
};

static const unsigned char PROGMEM ICON_TOP_RIGHT_ARROW[] =
{ 0x00, 0x00, 0x03, 0xfe, 0x03, 0xfe, 0x01, 0xfe,
  0x00, 0xfe, 0x01, 0xfe, 0x03, 0xfe, 0x07, 0xfe,
  0x0f, 0xee, 0x1f, 0xc6, 0x3f, 0x80, 0x1f, 0x00,
  0x0e, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const unsigned char PROGMEM ICON_RIGHT_ARROW[] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x60,
  0x00, 0x70, 0x00, 0x78, 0xff, 0xfc, 0xff, 0xfe,
  0xff, 0xff, 0xff, 0xfe, 0xff, 0xfc, 0x00, 0x78,
  0x00, 0x70, 0x00, 0x60, 0x00, 0x40, 0x00, 0x00
};

static const unsigned char PROGMEM ICON_BOTTOM_RIGHT_ARROW[] =
{ 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x0e, 0x00,
  0x1f, 0x00, 0x3f, 0x80, 0x1f, 0xc6, 0x0f, 0xee,
  0x07, 0xfe, 0x03, 0xfe, 0x01, 0xfe, 0x00, 0xfe,
  0x01, 0xfe, 0x03, 0xfe, 0x03, 0xfe, 0x00, 0x00
};

static const unsigned char PROGMEM ICON_BOTTOM_ARROW[] =
{ 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0,
  0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0, 0x03, 0xe0,
  0x03, 0xe0, 0x3f, 0xfe, 0x1f, 0xfc, 0x0f, 0xf8,
  0x07, 0xf0, 0x03, 0xe0, 0x01, 0xc0, 0x00, 0x80
};

static const unsigned char PROGMEM ICON_BOTTOM_LEFT_ARROW[] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x70,
  0x00, 0xf8, 0x01, 0xfc, 0x63, 0xf8, 0x77, 0xf0,
  0x7f, 0xe0, 0x7f, 0xc0, 0x7f, 0x80, 0x7f, 0x00,
  0x7f, 0x80, 0x7f, 0xc0, 0x7f, 0xc0, 0x00, 0x00
};

static const unsigned char PROGMEM ICON_LEFT_ARROW[] =
{ 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x06, 0x00,
  0x0e, 0x00, 0x1e, 0x00, 0x3f, 0xff, 0x7f, 0xff,
  0xff, 0xff, 0x7f, 0xff, 0x3f, 0xff, 0x1e, 0x00,
  0x0e, 0x00, 0x06, 0x00, 0x02, 0x00, 0x00, 0x00
};

static const unsigned char PROGMEM ICON_TOP_LEFT_ARROW[] =
{ 0x00, 0x00, 0x7f, 0xc0, 0x7f, 0xc0, 0x7f, 0x80,
  0x7f, 0x00, 0x7f, 0x80, 0x7f, 0xc0, 0x7f, 0xe0,
  0x77, 0xf0, 0x63, 0xf8, 0x01, 0xfc, 0x00, 0xf8,
  0x00, 0x70, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00
};

// WEATHER ICONS
static const unsigned char PROGMEM ICON_CLOUD[] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0,
  0x01, 0xf8, 0x1f, 0xf8, 0x3f, 0xf8, 0x3f, 0xfe,
  0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00
};

static const unsigned char PROGMEM ICON_RAIN[] =
{ 0x00, 0x00, 0x00, 0xf0, 0x01, 0xf8, 0x1f, 0xf8,
  0x3f, 0xf8, 0x3f, 0xfe, 0x7f, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xaa, 0xaa,
  0xaa, 0xaa, 0x55, 0x55, 0xd7, 0x5f, 0xaa, 0xaa
};

static const unsigned char PROGMEM ICON_SUN[] =
{ 0x01, 0x80, 0x01, 0x80, 0x31, 0x8c, 0x38, 0x1c,
  0x17, 0xe8, 0x0f, 0xf0, 0x0f, 0xf0, 0xff, 0xf7,
  0xff, 0xf7, 0x0f, 0xf0, 0x0f, 0xf0, 0x17, 0xe8,
  0x38, 0x1c, 0x11, 0x88, 0x01, 0x80, 0x00, 0x00
};

// SIGNAL ICONS
static const unsigned char PROGMEM ICON_NO_SIGNAL[] =
{ 0x00, 0x00, 0x10, 0x00, 0x92, 0x00, 0x54, 0x00,
  0x38, 0x00, 0x12, 0x04, 0x17, 0x0e, 0x13, 0x9c,
  0x11, 0xf8, 0x10, 0xf0, 0x11, 0xf8, 0x13, 0x9c,
  0x17, 0x0e, 0x12, 0x04, 0x10, 0x00, 0x10, 0x00
};

static const unsigned char PROGMEM ICON_ONE_SIGNAL[] =
{ 0x00, 0x00, 0x10, 0x00, 0x92, 0x00, 0x54, 0x00,
  0x38, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00,
  0x10, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00,
  0x13, 0x00, 0x13, 0x00, 0x13, 0x00, 0x13, 0x00
};

static const unsigned char PROGMEM ICON_TWO_SIGNAL[] =
{ 0x00, 0x00, 0x10, 0x00, 0x92, 0x00, 0x54, 0x00,
  0x38, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x00,
  0x10, 0x00, 0x10, 0x30, 0x10, 0x30, 0x10, 0x30,
  0x13, 0x30, 0x13, 0x30, 0x13, 0x30, 0x13, 0x30
};

static const unsigned char PROGMEM ICON_FULL_SIGNAL[] =
{ 0x00, 0x00, 0x10, 0x00, 0x92, 0x00, 0x54, 0x00,
  0x38, 0x00, 0x10, 0x00, 0x10, 0x00, 0x10, 0x03,
  0x10, 0x03, 0x10, 0x33, 0x10, 0x33, 0x10, 0x33,
  0x13, 0x33, 0x13, 0x33, 0x13, 0x33, 0x13, 0x33
};

// WIFI SIGNAL ICONS
static const unsigned char PROGMEM ICON_WIFI_NO_SIGNAL[] =
{ 0x00, 0x00, 0x30, 0x00, 0x3b, 0xf0, 0x1d, 0xfc,
  0x6e, 0x3e, 0xf7, 0x0f, 0xc3, 0x83, 0x0d, 0xd0,
  0x1e, 0xe8, 0x1c, 0x70, 0x00, 0x38, 0x01, 0xdc,
  0x01, 0x9e, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00
};

static const unsigned char PROGMEM ICON_WIFI_LOW_SIGNAL[] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80,
  0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const unsigned char PROGMEM ICON_WIFI_MED_SIGNAL[] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x0f, 0xf0,
  0x1f, 0xf8, 0x1c, 0x38, 0x00, 0x00, 0x01, 0x80,
  0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const unsigned char PROGMEM ICON_WIFI_HIGH_SIGNAL[] =
{ 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x3f, 0xfc,
  0x7c, 0x3e, 0xf0, 0x0f, 0xc3, 0xc3, 0x0f, 0xf0,
  0x1f, 0xf8, 0x1c, 0x38, 0x00, 0x00, 0x01, 0x80,
  0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// EMOTICON AND CUSTOM SHAPE
static const unsigned char PROGMEM ICON_SMILE_EMOTICON[] =
{ 0x07, 0xe0, 0x1f, 0xf8, 0x38, 0x1c, 0x70, 0x0e,
  0x60, 0x06, 0xc6, 0x63, 0xc6, 0x63, 0xc0, 0x03,
  0xc0, 0x03, 0xd8, 0x1b, 0xc8, 0x13, 0x6e, 0x76,
  0x73, 0xce, 0x38, 0x1c, 0x1f, 0xf8, 0x07, 0xe0
};

static const unsigned char PROGMEM ICON_SAD_EMOTICON[] =
{ 0x07, 0xe0, 0x1f, 0xf8, 0x38, 0x1c, 0x70, 0x0e,
  0x60, 0x06, 0xc6, 0x63, 0xc6, 0x63, 0xc0, 0x03,
  0xc0, 0x03, 0xc0, 0x03, 0xc7, 0xe3, 0x6c, 0x36,
  0x78, 0x1e, 0x38, 0x1c, 0x1f, 0xf8, 0x07, 0xe0
};

static const unsigned char PROGMEM ICON_HEART_FILL[] =
{ 0x3e, 0x7c, 0x7f, 0xfe, 0xff, 0xff, 0xff, 0xff,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x7f, 0xfe, 0x7f, 0xfe, 0x3f, 0xfc, 0x1f, 0xf8,
  0x0f, 0xf0, 0x07, 0xe0, 0x03, 0xc0, 0x01, 0x80
};

static const unsigned char PROGMEM ICON_HEART_EMPTY[] =
{ 0x3e, 0x7c, 0x7f, 0xfe, 0xe3, 0xc7, 0xc1, 0x83,
  0xc1, 0x83, 0xc0, 0x03, 0xc0, 0x03, 0xe0, 0x07,
  0x60, 0x06, 0x70, 0x0e, 0x38, 0x1c, 0x1c, 0x38,
  0x0e, 0x70, 0x07, 0xe0, 0x03, 0xc0, 0x01, 0x80
};

static const unsigned char PROGMEM ICON_STAR_FILL[] =
{ 0x01, 0x80, 0x01, 0x80, 0x03, 0xc0, 0x03, 0xc0,
  0x0f, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfe,
  0x3f, 0xfc, 0x1f, 0xf8, 0x1f, 0xf8, 0x1f, 0xf8,
  0x1f, 0xf8, 0x1f, 0xf8, 0x1c, 0x38, 0x00, 0x00
};

void setup() {
  // init
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // show image buffer (kalo ada)
  display.display();
  delay(500);
  // clear buffer
  display.clearDisplay();
}

void loop() {
  while (Serial.available() > 0) {
    char incoming_char = Serial.read();
    if (incoming_char == ',') {
      index += 1;
    }
    else if (incoming_char == ';') {
      execute_command(command_str);
      index = 0;
      break;
    }
    else if (incoming_char != '\n')
      command_str[index].concat(incoming_char);
  }
}

void execute_command(String str_array[]) {
  if (str_array[0].equals("o")) {
    //    Serial.println("Draw Circle");
    if (str_array[4].toInt() == 1) {
      display.fillCircle(
        str_array[1].toInt(),
        str_array[2].toInt(),
        str_array[3].toInt(), 1);
    } else {
      display.drawCircle(
        str_array[1].toInt(),
        str_array[2].toInt(),
        str_array[3].toInt(), 1);
    }
    display.display();

  } else if (str_array[0].equals("r")) {
    //    Serial.println("Draw Rectangle");
    if (str_array[5].toInt() == 1) {
      display.fillRect(
        str_array[1].toInt(),
        str_array[2].toInt(),
        str_array[3].toInt(),
        str_array[4].toInt(), 1);
    } else {
      display.drawRect(
        str_array[1].toInt(),
        str_array[2].toInt(),
        str_array[3].toInt(),
        str_array[4].toInt(), 1);
    }
    display.display();

  } else if (str_array[0].equals("t")) {
    //    Serial.println("Draw Triangle");
    if (str_array[7].toInt() == 1) {
      display.fillTriangle(
        str_array[1].toInt(),
        str_array[2].toInt(),
        str_array[3].toInt(),
        str_array[4].toInt(),
        str_array[5].toInt(),
        str_array[6].toInt(), 1);
    } else {
      display.drawTriangle(
        str_array[1].toInt(),
        str_array[2].toInt(),
        str_array[3].toInt(),
        str_array[4].toInt(),
        str_array[5].toInt(),
        str_array[6].toInt(), 1);
    }
    display.display();

  } else if (str_array[0].equals("l")) {
    //    Serial.println("Draw Line");
    display.drawLine(
      str_array[1].toInt(),
      str_array[2].toInt(),
      str_array[3].toInt(),
      str_array[4].toInt(), 1);
    display.display();

  } else if (str_array[0].equals("p")) {
    //    Serial.println("Draw Point");
    display.drawPixel(str_array[1].toInt(), str_array[2].toInt(), 1);
    display.display();

  } else if (str_array[0].equals("teks")) {
    //    Serial.println("Write Text");
    display.setCursor(str_array[1].toInt(), str_array[2].toInt());
    display.setTextColor(1);
    display.setTextSize(str_array[3].toInt());
    display.setTextWrap(str_array[4].toInt());
    display.print(str_array[5]);
    display.display();

  } else if (str_array[0].equals("env0")) {
    //    Serial.println("Draw Closed Message Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_ENV_CLOSE,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("env1")) {
    //    Serial.println("Draw Opened Message Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_ENV_OPEN,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("tarrow")) {
    //    Serial.println("Draw Top Arrow Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_TOP_ARROW,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("trarrow")) {
    //    Serial.println("Draw Top Right Arrow Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_TOP_RIGHT_ARROW,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("rarrow")) {
    //    Serial.println("Draw Right Arrow Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_RIGHT_ARROW,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("brarrow")) {
    //    Serial.println("Draw Bottom Right Arrow Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_BOTTOM_RIGHT_ARROW,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("barrow")) {
    //    Serial.println("Draw Bottom Arrow Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_BOTTOM_ARROW,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("blarrow")) {
    //    Serial.println("Draw Bottom Left Arrow Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_BOTTOM_LEFT_ARROW,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("larrow")) {
    //    Serial.println("Draw Left Arrow Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_LEFT_ARROW,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("tlarrow")) {
    //    Serial.println("Draw Top Left Arrow Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_TOP_LEFT_ARROW,
      16, 16, 1);
    display.display();
  } else if (str_array[0].equals("cld")) {
    //    Serial.println("Draw Opened Message Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_CLOUD,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("rain")) {
    //    Serial.println("Draw Opened Message Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_RAIN,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("sun")) {
    //    Serial.println("Draw Opened Message Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_SUN,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("sig0")) {
    //    Serial.println("Draw Opened Message Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_NO_SIGNAL,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("sig1")) {
    //    Serial.println("Draw Opened Message Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_ONE_SIGNAL,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("sig2")) {
    //    Serial.println("Draw Opened Message Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_TWO_SIGNAL,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("sig3")) {
    //    Serial.println("Draw Opened Message Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_FULL_SIGNAL,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("wifi0")) {
    //    Serial.println("Draw Opened Message Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_WIFI_NO_SIGNAL,
      16, 16, 1);
    display.display();
  } else if (str_array[0].equals("wifi1")) {
    //    Serial.println("Draw Opened Message Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_WIFI_LOW_SIGNAL,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("wifi2")) {
    Serial.println("Draw Opened Message Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_WIFI_MED_SIGNAL,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("wifi3")) {
    //    Serial.println("Draw Opened Message Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_WIFI_HIGH_SIGNAL,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("smile")) {
    //    Serial.println("Draw Opened Message Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_SMILE_EMOTICON,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("sad")) {
    //    Serial.println("Draw Opened Message Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_SAD_EMOTICON,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("heart0")) {
    //    Serial.println("Draw Opened Message Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_HEART_EMPTY,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("heart1")) {
    //    Serial.println("Draw Opened Message Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_HEART_FILL,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("star")) {
    //    Serial.println("Draw Opened Message Icon");
    display.drawBitmap(
      str_array[1].toInt(),
      str_array[2].toInt(),
      ICON_STAR_FILL,
      16, 16, 1);
    display.display();

  } else if (str_array[0].equals("clr")) {
    //    Serial.println("Clear Display");
    display.clearDisplay();
    display.display();
  }

  // print isi array hasil parsing
  for (byte i = 0; i < 6; i++) {
    //    Serial.print(str_array[i]);
    //    Serial.print(" ");
    str_array[i] = "";
  }
  //  Serial.println();
}

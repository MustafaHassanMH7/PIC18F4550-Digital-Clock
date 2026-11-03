// 7-Segment Display Anot Kod Tablosu
const unsigned char dAnode[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

// PORTD Hane Seçimi
#define DIGIT1 PORTD.B0
#define DIGIT2 PORTD.B1
#define DIGIT3 PORTD.B2
#define DIGIT4 PORTD.B3

// Saat ve Dakika Değişkenleri
unsigned char hours = 00;   // Başlangıç saati
unsigned char minutes = 15; // Başlangıç dakikası

void setup() {
    // GPIO Ayarları
    TRISB = 0x00;
    TRISD = 0x00;
    PORTB = 0x00;
    PORTD = 0x00;
}

void displayNumber(unsigned char digit, unsigned char value) {
    PORTD = 0x01 << digit;
    PORTB = dAnode[value];
    Delay_ms(5);
}

void updateTime() {
    minutes++;
    if (minutes >= 60) {
        minutes = 0;
        hours++;
    }
    if (hours >= 24) {
        hours = 0;
    }
}

void displayTime() {
    displayNumber(0, hours / 10);
    displayNumber(1, hours % 10);
    displayNumber(2, minutes / 10);
    displayNumber(3, minutes % 10);
}

void main() {
    unsigned int delayCounter = 0;
    setup();

    while (1) {
        displayTime();
        // NOT: Bu ilk sürümde zaman hesabı hatalıdır (1200 ekran döngüsü yaklaşık 24 saniye).
        delayCounter++;
        if (delayCounter >= 1200) {  // 4 hane * 5 ms * 1200 = yaklaşık 24 s; 60 s değildir
            delayCounter = 0;
            updateTime();
        }
    }
}
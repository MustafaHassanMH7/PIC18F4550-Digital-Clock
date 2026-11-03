// CONFIG Ayarları (not: mikroC derleyici bu #pragma config satırlarını yok saymıştır)
#pragma config FOSC = HS      // Yüksek hızlı kristal osilatör seçimi
#pragma config PWRT = ON      // Güç Açılış Zamanlayıcısı
#pragma config WDT = OFF      // Watchdog Timer devre dışı
#pragma config LVP = OFF      // Düşük Voltajlı Programlama devre dışı

// 7-Segment Display Anot Kod Tablosu
const unsigned char dAnode[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

// PORTD Hane Seçimi
#define DIGIT1 PORTD.B0
#define DIGIT2 PORTD.B1
#define DIGIT3 PORTD.B2
#define DIGIT4 PORTD.B3

// Saat ve Dakika Değişkenleri
unsigned char hours = 13;    // Başlangıç saati
unsigned char minutes = 10; // Başlangıç dakikası

void setup() {
    // GPIO Ayarları
    TRISB = 0x00;  // PORTB çıkış (Segment veri pini)
    TRISD = 0x00;  // PORTD çıkış (Hane seçimi)
    PORTB = 0x00;  // PORTB sıfırla
    PORTD = 0x00;  // PORTD sıfırla
}

void displayNumber(unsigned char digit, unsigned char value) {
    // Hane seçimi
    PORTD = 0x01 << digit;  // İlgili haneyi aktif et

    // Segment verisi
    PORTB = dAnode[value];  // Gösterilecek değeri segmentlere gönder

    Delay_ms(5);            // Gözle görülür süre için bekle
}

void updateTime() {
    // Dakikayı artır
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
    // 1. Hane: Saatin onlar basamağı
    displayNumber(0, hours / 10);

    // 2. Hane: Saatin birler basamağı
    displayNumber(1, hours % 10);

    // 3. Hane: Dakikanın onlar basamağı
    displayNumber(2, minutes / 10);

    // 4. Hane: Dakikanın birler basamağı
    displayNumber(3, minutes % 10);
}

void main() {
    unsigned int delayCounter = 0;
    setup();

    while (1) {
        displayTime(); // Anlık zamanı ekrana yazdır

        // Yaklaşık 60 saniyelik döngüden sonra dakika bilgisini artır (kalibre edilmemiş)
        delayCounter++;
        if (delayCounter >= 2980) {  // 4 hane * 5 ms * 2980 = yaklaşık 59,6 s; fonksiyon ek süreleri dahil değildir
            delayCounter = 0;
            updateTime();
        }
    }
}
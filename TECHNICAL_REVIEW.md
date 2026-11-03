# Teknik inceleme / Technical review

Kaynak: Projenin orijinal **Digital Watch Project** arşivi ve proje derleme kayıtları.

## Doğrulanmış bulgular

- `MyProject.mcppi` proje ayarları `Name=P18F4550` ve `Clock=8000000` içerir.
- Orijinal `Watch/MyProject.log` dosyasında 13 Ocak 2025 tarihinde başarılı derleme kaydı bulunmaktadır; dört `Unknown pragma line ignored` uyarısı yer almaktadır.
- Orijinal `Digital Watch/MyProject.log` dosyasında 17 Aralık 2024 tarihinde başarılı derleme kaydı bulunmaktadır.
- Sonraki sürümde `delayCounter >= 2980`, ilk sürümde `>= 1200` kullanılmaktadır.
- Her `displayTime()` çağrısı dört adet `displayNumber()` içerir; her birinde `Delay_ms(5)` bulunduğundan dört haneli taramanın yalnızca gecikme süresi yaklaşık **4 × 5 ms = 20 ms** olur.
- `2980 × 20 ms = 59,6 s`; önceki sürümde `1200 × 20 ms = 24 s`. Hesaplarda komut yürütme süresi ve diğer gecikmeler hesaba katılmamıştır.
- `updateTime()` her çağrıda dakika değerini bir artırır. Bu nedenle ilk sürüm gerçek dakika tabanı sağlamaz; sonraki sürüm de ölçülüp kalibre edilmiş bir saat değildir.
- Orijinal sunumdaki “1200 × 5 ms = 1 saniye” açıklaması tutarlı değildir; bir ekran çevriminde dört ayrı 5 ms gecikme bulunur.
- Kaynak C kodunda timer interrupt, RTC ya da saat ayarı düğmesi işlevi yoktur.
- `#pragma config` satırları mikroC derleyicisinde yok sayılmıştır. Yapılandırma bitlerinin IDE'deki değerleri ayrıca kontrol edilmelidir.

## Bu depoda bulunan içerik

- C kaynak kodu ve mikroC proje ayarları.
- Orijinal HEX çıktısı; bu yayın sırasında yeniden derlenmedi.
- İlk ve sonraki C kod sürümleri ayrı tutularak sürüm farkları korunmuştur.
- Projenin teknik tanıtımı ve geliştirme önerileri.

## Doğrulama durumu

**Yeniden derleme:** yapılmadı.  
**Proteus simülasyonu:** bu yayın sırasında çalıştırılmadı.  
**Fiziksel donanım testi:** bu yayın sırasında yapılmadı.  
**Gerçek zaman doğruluğu ölçümü:** yapılmadı.

## İyileştirme önerileri

- Timer1/Timer0 kesmesi veya RTC ile bağımsız zaman tabanı tasarlamak.
- Ekran çoklamasını zaman sayacından ayırmak.
- 8 MHz osilatör ve PIC konfigürasyon bitlerini doğrulamak.
- Simülasyon ve gerçek devrede saniye/dakika sapmasını ölçmek.

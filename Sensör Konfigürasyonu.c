#include <stdio.h>
#include <stdint.h>

// Enum for Acceleration Range
// Datasheet'te verilen değerlere göre ivme ölçerin G aralığını tanımlıyoruz.
typedef enum {
    ACC_RANGE_2G = 0x00, // 2G aralığı
    ACC_RANGE_4G = 0x01, // 4G aralığı
    ACC_RANGE_8G = 0x02, // 8G aralığı
    ACC_RANGE_16G = 0x03 // 16G aralığı
} AccelRange;

// Enum for Bandwidth
// Datasheet'teki bant genişliği ayarları.
typedef enum {
    ACC_BW_7_81HZ = 0x00, // 7.81 Hz
    ACC_BW_15_63HZ = 0x01, // 15.63 Hz
    ACC_BW_31_25HZ = 0x02, // 31.25 Hz
    ACC_BW_62_5HZ = 0x03,  // 62.5 Hz
    ACC_BW_125HZ = 0x04,   // 125 Hz
    ACC_BW_250HZ = 0x05,   // 250 Hz
    ACC_BW_500HZ = 0x06,   // 500 Hz
    ACC_BW_1000HZ = 0x07   // 1000 Hz
} AccelBandwidth;

// Enum for Operation Mode
// İşlem modu parametreleri.
typedef enum {
    ACC_MODE_NORMAL = 0x00,   // Normal mod
    ACC_MODE_SUSPEND = 0x01,  // Suspend mod
    ACC_MODE_LOW_POWER = 0x02 // Düşük güç modu
} AccelOperationMode;

// Struct for Accelerometer Configuration
// Sensörün tüm konfigürasyon parametrelerini bir arada tutar.
typedef struct {
    AccelRange range;
    AccelBandwidth bandwidth;
    AccelOperationMode mode;
    uint8_t accConfigValue; // Register'a gönderilecek değer
} AccelerometerConfig;

// Function to configure the accelerometer
// Bu fonksiyon, bitwise operatörler kullanarak accConfigValue değerini hesaplar.
void configureAccelerometer(AccelerometerConfig *config) {
    config->accConfigValue = (config->range << 6) | (config->bandwidth << 3) | (config->mode);
    // range, bandwidth ve mode değerlerini birleştirerek register için gerekli değeri oluşturuyoruz.
}

// Main function
int main() {
    AccelerometerConfig accelConfig;

    // Struct için örnek değerler atıyoruz.
    accelConfig.range = ACC_RANGE_8G;
    accelConfig.bandwidth = ACC_BW_125HZ;
    accelConfig.mode = ACC_MODE_NORMAL;

    // Konfigürasyonu hesaplıyoruz.
    configureAccelerometer(&accelConfig);

    // Sonuçları decimal, hexadecimal ve binary olarak yazdırıyoruz.
    printf("Decimal Config Value: %d\n", accelConfig.accConfigValue);
    printf("Hexadecimal Config Value: 0x%X\n", accelConfig.accConfigValue);

    // Binary formatta yazdırmak için bir döngü kullanıyoruz.
    printf("Binary Config Value: ");
    for (int i = 7; i >= 0; i--) {
        printf("%d", (accelConfig.accConfigValue >> i) & 1);
    }
    printf("\n");

    return 0;
}
/*
Output örneği :
Decimal Config Value: 100
Hexadecimal Config Value: 0x64
Binary Config Value: 01100100
*/

#include <AESLib.h>

AESLib aesLib;

String plaintext = "forward";  // Gesture command to encrypt
char encrypted[128];           // output buffer for Base64 encrypted data
char decrypted[128];           // output buffer for decrypted data

byte aesKey[16] = { 0x60, 0x3D, 0xEB, 0x10, 0x15, 0xCA, 0x71, 0xBE,
                    0x2B, 0x73, 0xAE, 0xF0, 0x85, 0x7D, 0x77, 0x81 }; // 128-bit key

byte iv[16] = { 0x00, 0x01, 0x02, 0x03,
                0x04, 0x05, 0x06, 0x07,
                0x08, 0x09, 0x0A, 0x0B,
                0x0C, 0x0D, 0x0E, 0x0F }; // Initialization vector

void setup() {
  Serial.begin(115200);
  delay(2000);

  Serial.println("Original text: " + plaintext);

  // --- Encrypt ---
  aesLib.encrypt64(
      (byte*)plaintext.c_str(),          // input
      plaintext.length(),                // input length
      encrypted,                         // output buffer
      aesKey,                             // key
      128,                                // key size in bits
      iv                                   // IV
  );

  Serial.print("Encrypted (Base64): ");
  Serial.println(encrypted);

  // --- Decrypt ---
  aesLib.decrypt64(
      encrypted,                         // input Base64
      strlen(encrypted),                 // length of Base64 input
      (byte*)decrypted,                  // output buffer
      aesKey,                             // key
      128,                                // key size in bits
      iv                                   // IV
  );

  Serial.print("Decrypted text: ");
  Serial.println(decrypted);
}

void loop() {}

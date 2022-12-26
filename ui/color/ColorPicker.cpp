//
// Created by Antonio Jose Pires on 12/25/22.
//

#include "ColorPicker.hpp"

extern "C" {
#include "openssl/evp.h"
}

namespace ui::ColorPicker {

QColor forPath(const std::filesystem::path &path) {
  auto digest_ctx = EVP_MD_CTX_new();
  QColor color;

  {
    char buffer[1024];

    EVP_DigestInit_ex(digest_ctx, EVP_md5(), nullptr);
    QFile file(path);
    file.open(QIODeviceBase::ReadOnly);

    while (!file.atEnd()) {
      auto read = file.read(buffer, 1024);
      // Fine to static cast because we know the size is at most 1024
      EVP_DigestUpdate(digest_ctx, buffer, static_cast<size_t>(read));
    }
    file.close();
  }
  {
    unsigned char md_value[16]; // md5 is 16 bytes
    unsigned char in[4];
    unsigned char out[4];
    int out_size = 0; // Shouldn't be more than 4, but our buddy won't take a nullptr here.
    auto cipher_ctx = EVP_CIPHER_CTX_new();

    EVP_DigestFinal_ex(digest_ctx, md_value, nullptr);
    EVP_MD_CTX_free(digest_ctx);
    EVP_EncryptInit_ex(cipher_ctx, EVP_aes_128_ctr(), nullptr, md_value, nullptr);
    EVP_EncryptUpdate(cipher_ctx, out, &out_size, in, 4);
    EVP_CIPHER_CTX_free(cipher_ctx);

    color.setHsl(((out[1] << 8) + out[2]) % 360, 255, 255 * ((out[0] % 21) + 65) / 100);
  }

  return color;
};

}

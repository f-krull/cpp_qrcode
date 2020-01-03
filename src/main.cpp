#include "../3rdparty/QR-Code-generator/c/qrcodegen.c"
#include "../3rdparty/CImg.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
  printf("%d\n", argc);
  if (argc < 2) {
    fputs("error reading cmd-line argument\n", stderr);
    return EXIT_FAILURE;
  }
  const char *text = argv[1];                  // User-supplied text
	enum qrcodegen_Ecc errCorLvl = qrcodegen_Ecc_MEDIUM; // Error correction level
	
	// Make and print the QR Code symbol
	uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
	uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
	bool ok = qrcodegen_encodeText(text, tempBuffer, qrcode, errCorLvl,
		qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);

  if (!ok) {
    fputs("error encoding string\n", stderr);
    return EXIT_FAILURE;
  }

	int size = qrcodegen_getSize(qrcode);
	int border = 4;

  fputs(text, stdout);
  fputs("\n", stdout);
	for (int y = -border; y < size + border; y++) {
		for (int x = -border; x < size + border; x++) {
			fputs((qrcodegen_getModule(qrcode, x, y) ? "##" : "  "), stdout);
		}
		fputs("\n", stdout);
	}
	fputs("\n", stdout);
  int scale = 5;
  int img_out_w = (size + border * 2) * scale;
  cimg_library::CImg<uint8_t> img_out(
    img_out_w, 
    img_out_w, 
    1, 1, 0xFF
  );
  cimg_forXY(img_out, x, y) {
    img_out(x, y, 0) = qrcodegen_getModule(qrcode, x / scale - border, y / scale - border) ? 0x00 : 0xFF;
  }
  cimg_library::CImgDisplay main_disp(img_out, text);
  while (!main_disp.is_closed()) {
    main_disp.wait();
  }
  return EXIT_SUCCESS;
}

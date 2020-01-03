all: QR-Code-generator CImg.h
	$(MAKE) -C QR-Code-generator/c  # not required!

QR-Code-generator:
	git clone https://github.com/nayuki/QR-Code-generator/


CImg.h:
	wget https://raw.githubusercontent.com/dtschump/CImg/master/CImg.h


.PHONY: clean
clean:
	$(RM) -r QR-Code-generator
	$(RM) CImg.h
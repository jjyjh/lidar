#include "libsynexens3/libsynexens3.h"
#include <fstream>
#include <iostream>
#include <fstream>
#include <iostream>
#include <sys/timeb.h>



#define PROTOBIN_DEPTH_320_240_TEMP "test_320.pb"
#define PROTOBIN_DEPTH_640_480_TEMP "test_640.pb"

#define EEPROM_INTRINSICS_MD5_LEN 16
#define EEPROM_INTRINSICS_BURN_TIME_LEN 4
#define EEPROM_INTRINSICS_BURN_VER_LEN 2
#define EEPROM_INTRINSICS_CALIB_SIZE_LEN 4


void  write_depth_320(const sy3::sensor* s) {
	std::filebuf *pbuf;
	std::ifstream filestr;
	uint8_t *buffer;
	filestr.open(PROTOBIN_DEPTH_320_240_TEMP, std::ios::binary);

	if (!filestr.is_open()) {
		printf("no internal reference file found in current directory £º%s !!!!!!!!!!\n", PROTOBIN_DEPTH_320_240_TEMP);
		system("pause");
	}

	pbuf = filestr.rdbuf();
	uint16_t size = pbuf->pubseekoff(0, std::ios::end, std::ios::in);

	printf("Burning PROTOBIN_DEPTH_320_240 (%d bytes), do not close window !!!   ... \n", size);
	pbuf->pubseekpos(0, std::ios::in);
	buffer = new uint8_t[size];
	pbuf->sgetn((char *)buffer, size);
	filestr.close();
	s->write_calib_depth_320_240(buffer, size);
}

void  write_depth_640(const sy3::sensor* s) {
	std::filebuf *pbuf;
	std::ifstream filestr;
	uint8_t *buffer;
	filestr.open(PROTOBIN_DEPTH_640_480_TEMP, std::ios::binary);
	if (!filestr.is_open()) {
		printf("No internal reference file found in current directory £º%s\n !!!!!!!!", PROTOBIN_DEPTH_640_480_TEMP);
		system("pause");
	}
	pbuf = filestr.rdbuf();
	uint16_t size = pbuf->pubseekoff(0, std::ios::end, std::ios::in);

	printf("burning PROTOBIN_DEPTH_640_480 (%d bytes), do not close window !!! ...\n", size);
	pbuf->pubseekpos(0, std::ios::in);
	buffer = new uint8_t[size];
	pbuf->sgetn((char *)buffer, size);
	filestr.close();
	s->write_calib_depth_640_480(buffer, size);
}

void write_sn(const sy3::sensor* s,uint8_t sn[20]) {
	s->write_device_sn(sn);
}

int main(int argc, char **argv)
{
	sy3::sy3_error e;
	printf("version:%s \n", sy3::sy3_get_version(e));
	printf("For testing purposes only£¡£¡£¡£¡£¡£¡£¡£¡£¡\n");
	sy3::context *ctx = sy3::sy3_create_context(e);
	sy3::device *dev = ctx->query_device(e);
	const sy3::sensor* sensor = dev->get_sensor(e);
	write_depth_320(sensor);
	write_depth_640(sensor);
	
	uint8_t sn[20] = { 'S','V','0','1','2','0','6','1','5','L','0','0','0','3','#','a','b','c' };
	write_sn(sensor,sn);
	printf("Only do the test using burning completed, re-powered to take effect !!!!!!!!\n\n\n");
	system("pause");
	return 0;
}

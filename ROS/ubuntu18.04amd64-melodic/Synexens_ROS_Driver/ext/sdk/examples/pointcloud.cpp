#include "libsynexens3/libsynexens3.h"
#include <opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#define RAW_WIDTH 1280
#define RAW_HEIGHT 960

#if 1
#define DEPTH_WIDTH 640
#define DEPTH_HEIGHT 480
#else
#define DEPTH_WIDTH 320
#define DEPTH_HEIGHT 240
#endif

#define RGB_WIDTH 1920
#define RGB_HEIGHT 1080


void show_point_cloud_frame(sy3::depth_frame *frame, const char* name,sy3::process_engine* engine)
{
	if (frame) {
		sy3::sy3_error e;
		sy3::points* points = engine->comptute_points(frame,e);

		 float*  data =  points->get_points();

		delete points;
	}

}

void print_device_info(sy3::device *dev)
{
	sy3::sy3_error e;
	printf("\nUsing device 0, an %s\n", sy3::sy3_get_device_info(dev, sy3::SY3_CAMERA_INFO_NAME, e));
	printf("    Serial number: %s\n", sy3::sy3_get_device_info(dev, sy3::SY3_CAMERA_INFO_SERIAL_NUMBER, e));
	printf("    Firmware version: %s\n\n", sy3::sy3_get_device_info(dev, sy3::SY3_CAMERA_INFO_FIRMWARE_VERSION, e));
}

void print_support_format(sy3::device *dev, sy3::sy3_error &e)
{

	std::vector<sy3::sy3_stream> support_stream = dev->get_support_stream(e);
	for (int i = 0; i < support_stream.size(); i++)
	{
		printf("support stream:%s \n", sy3_stream_to_string(support_stream[i]));
		std::vector<sy3::sy3_format> support_format = dev->get_support_format(support_stream[i], e);
		for (int j = 0; j < support_format.size(); j++)
		{
			printf("\t\t support format:%d x %d \n", support_format[j].width, support_format[j].height);
		}
	}
}

int main(int argc, char **argv)
{
	sy3::sy3_error e;
	printf("version:%s \n", sy3::sy3_get_version(e));
	sy3::context *ctx = sy3::sy3_create_context(e);
	sy3::device *dev = ctx->query_device(e);

	print_support_format(dev, e);
	print_device_info(dev);

	sy3::pipeline *pline = sy3::sy3_create_pipeline(ctx, e);

	sy3::config *cfg = sy3_create_config(e);
	cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_DEPTH, DEPTH_WIDTH, DEPTH_HEIGHT, e);

	pline->start(cfg, e);

	uint16_t exposure = 0;
	bool quit = false;
	while (!quit)
	{

		sy3::frameset *frameset = pline->wait_for_frames(SY3_DEFAULT_TIMEOUT, e);

		sy3::depth_frame *depth_frame = frameset->get_depth_frame();
		show_point_cloud_frame(depth_frame, "POINT_CLOUD", pline->get_process_engin(e));

		delete frameset;
		switch (cv::waitKey(1))
		{

		case 'q':
		{
			pline->stop(e);
			quit = true;
		}
		break;
		}
	}
	system("pause");

	return 0;
}

#include "libsynexens3/libsynexens3.h"
int main(int argc, char **argv)
{
	sy3::sy3_error e;
	printf("version:%s \n", sy3::sy3_get_version(e));
	sy3::context *ctx = sy3::sy3_create_context(e);
	sy3::device *dev = ctx->query_device(e);

	if (e != sy3::sy3_error::SUCCESS) {
		printf("error:%d  %s \n", e, sy3::sy3_error_to_string(e));
		return 0;
	}

	sy3::pipeline *pline = sy3::sy3_create_pipeline(ctx, e);
	sy3::config *cfg = sy3_create_config(e);
	cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_DEPTH, 640, 480, e);
	cfg->enable_stream(sy3::sy3_stream::SY3_STREAM_RGB, 1920, 1080, e);
	pline->start(cfg, e);

	bool quit = false;
	while (!quit)
	{

		switch (cv::waitKey(1)) {

		case 'q': {

			pline->stop(e);
			quit = true;
		}break;
		default:
			break;
		}

		sy3::frameset *frameset = pline->wait_for_frames(SY3_DEFAULT_TIMEOUT, e);
		sy3::depth_frame *depth_frame = frameset->get_depth_frame();
		sy3::rgb_frame *rgb_frame = frameset->get_rgb_frame();
		 sy3::process_engine *process_engine = pline->get_process_engin(e)
		sy3::frameset *align_set = pline->get_process_engin(e)->align_to_rgb(depth_frame, rgb_frame, e);
		show_depth_frame(align_set->get_depth_frame(), "algin_depth");
		show_rgb_rgb_frame(align_set->get_rgb_frame(), "algin_rgb");
		delete frameset;
		delete align_set;
	}

	system("pause");
	return 0;
}

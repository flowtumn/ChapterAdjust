#include <cassert>
#include <functional>
#include <vector>

#include "converter.h"

void testConverter() {
	const std::string test1{ "01:59:59.951" };

	//50msの補正。
	assert(std::string{ "02:00:00.001" } == flowTumn::converter::correctionChapterTime(test1, 50, 0));
	assert(std::string{ "02:00:00.010" } == flowTumn::converter::correctionChapterTime(test1, 50, 1));
	assert(std::string{ "02:00:00.100" } == flowTumn::converter::correctionChapterTime(test1, 50, 2));
	assert(std::string{ "02:00:01.000" } == flowTumn::converter::correctionChapterTime(test1, 50, 3));
	assert(std::string{ "02:00:10.000" } == flowTumn::converter::correctionChapterTime(test1, 50, 4));
	assert(std::string{ "02:00:00.000" } == flowTumn::converter::correctionChapterTime(test1, 50, 5));
	assert(std::string{ "02:00:00.000" } == flowTumn::converter::correctionChapterTime(test1, 50, 6));
	assert(std::string{ "02:00:00.000" } == flowTumn::converter::correctionChapterTime(test1, 50, 7));
	assert(std::string{ "10:00:00.000" } == flowTumn::converter::correctionChapterTime(test1, 50, 8));
	assert(std::string{ "00:00:00.000" } == flowTumn::converter::correctionChapterTime(test1, 50, 9));

	try {
		assert(std::string{ "00:00:00.000" } == flowTumn::converter::correctionChapterTime(test1, 50, 10));
		assert(false && "do not exception.");
	} catch (const std::invalid_argument&) {
		assert(true);
	}

	//80msの補正。
	assert(std::string{ "02:00:00.031" } == flowTumn::converter::correctionChapterTime(test1, 80, 0));
	assert(std::string{ "02:00:00.040" } == flowTumn::converter::correctionChapterTime(test1, 80, 1));
	assert(std::string{ "02:00:00.100" } == flowTumn::converter::correctionChapterTime(test1, 80, 2));
	assert(std::string{ "02:00:01.000" } == flowTumn::converter::correctionChapterTime(test1, 80, 3));
	assert(std::string{ "02:00:10.000" } == flowTumn::converter::correctionChapterTime(test1, 80, 4));
	assert(std::string{ "02:00:00.000" } == flowTumn::converter::correctionChapterTime(test1, 80, 5));
	assert(std::string{ "02:00:00.000" } == flowTumn::converter::correctionChapterTime(test1, 80, 6));
	assert(std::string{ "02:00:00.000" } == flowTumn::converter::correctionChapterTime(test1, 80, 7));
	assert(std::string{ "10:00:00.000" } == flowTumn::converter::correctionChapterTime(test1, 80, 8));
	assert(std::string{ "00:00:00.000" } == flowTumn::converter::correctionChapterTime(test1, 80, 9));

	//20000msの補正。
	assert(std::string{ "02:00:19.951" } == flowTumn::converter::correctionChapterTime(test1, 20000, 0));
	assert(std::string{ "02:00:19.960" } == flowTumn::converter::correctionChapterTime(test1, 20000, 1));
	assert(std::string{ "02:00:20.000" } == flowTumn::converter::correctionChapterTime(test1, 20000, 2));
	assert(std::string{ "02:00:20.000" } == flowTumn::converter::correctionChapterTime(test1, 20000, 3));
	assert(std::string{ "02:00:20.000" } == flowTumn::converter::correctionChapterTime(test1, 20000, 4));
	assert(std::string{ "02:00:00.000" } == flowTumn::converter::correctionChapterTime(test1, 20000, 5));
	assert(std::string{ "02:00:00.000" } == flowTumn::converter::correctionChapterTime(test1, 20000, 6));
	assert(std::string{ "02:00:00.000" } == flowTumn::converter::correctionChapterTime(test1, 20000, 7));
	assert(std::string{ "10:00:00.000" } == flowTumn::converter::correctionChapterTime(test1, 20000, 8));
	assert(std::string{ "00:00:00.000" } == flowTumn::converter::correctionChapterTime(test1, 20000, 9));

	//チャプターの時間同士を加算。
	assert(
		std::string{ "99:59:59.999" } ==
		flowTumn::converter::convertChapterTimeInteger2Str(
				flowTumn::converter::convertChapterTimeStr2Integer("12:34:56.789")
			+	flowTumn::converter::convertChapterTimeStr2Integer("87:25:03.210")
		)
	);
}

static const std::vector <std::function<void()> > TESTS{
	&testHevcManager,
	&testConverter,
};

int main() {
	for (auto&& each : TESTS) {
		each();
	}
}

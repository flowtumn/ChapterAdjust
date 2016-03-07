#ifndef CONVERTER_H_INCLUDE
#define CONVERTER_H_INCLUDE

#include <cstdint>
#include <string>

namespace flowTumn {
	struct converter {
		/**
		 * hh:mm:ss.mss の形式を補正。
		 * (roundUpでは、その桁数から切り上げ。)
		 */
		static auto correctionChapterTime(std::string t, uint64_t millis, uint32_t roundUp) -> std::string;
		static auto convertChapterTimeStr2Integer(std::string t) -> int64_t;
		static auto convertChapterTimeInteger2Str(int64_t t) -> std::string;
	};
}

#endif

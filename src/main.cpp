#include <array>
#include <iostream>
#include <tuple>
#include <functional>
#include <fstream>
#include <regex>
#include <sstream>

#include "converter.h"
#include "define.h"

#if defined(UNICODE) || defined(_UNICODE)
  #define _tmain	wmain
  #define err		std::wcerr
#else
  #define _tmain	main
  #define err		std::cerr
#endif

static inline auto adjust(const std::string& chapter, uint64_t correctTime, uint32_t roundUp) {
	std::regex pattern(u8"([0-9]{2}:[0-5][0-9]:[0-5][0-9].[0-9]{3})");
	std::smatch match;

	if (std::regex_search(chapter, match, pattern)) {
		const auto newTime = flowTumn::converter::correctionChapterTime(*match.begin(), correctTime, roundUp);
		return std::regex_replace(chapter, pattern, newTime, std::regex_constants::format_first_only);
	}

	return chapter;
}

static auto adjustChapter(const flowTumn::tstr& source, uint64_t correctTime, uint32_t roundUp) {
	std::ifstream iif(source);
	std::ostringstream ss;

	if (iif.good()) {
		while (!iif.eof()) {
			std::string lineBuffer;
			if (std::getline(iif, lineBuffer)) {
				ss << adjust(lineBuffer, correctTime, roundUp) << std::endl;
			}
		}
		return ss.str();
	}

	return std::string{""};
}

void setParam(uint64_t& dest, flowTumn::tstr v) {
	dest = flowTumn::toUint64(v);
}

void setParam(uint32_t& dest, flowTumn::tstr v) {
	dest = flowTumn::toUint32(v);
}

void setParam(flowTumn::tstr& dest, flowTumn::tstr v) {
	dest = std::move(v);
}

template <typename T>
void setParam(T& dest, flowTumn::tstr v) {
	setParam(dest, v);
}

using CommandLineValues = std::tuple <std::string, std::function <void(flowTumn::tstr)> >;

template <typename T>
CONSTEXPR auto createCommandLineValues(const std::string& key, T& dest) {
	return CommandLineValues{
		key,
		std::bind(setParam <T>, std::ref(dest), std::placeholders::_1)
	};
}

int _tmain(int argc, flowTumn::tstr::value_type** argv) {
	uint64_t correctTime = 0;
	uint32_t roundUp = 0;
	flowTumn::tstr source;
	flowTumn::tstr dest;

	std::array <CommandLineValues, 4> commandLine{ {
		createCommandLineValues("--chapter_file", source),
		createCommandLineValues("--correction_time", correctTime),
		createCommandLineValues("--roundup_time", roundUp),
		createCommandLineValues("--output_file", dest),
	} };

	for (decltype(argc) i = 1; i < argc; ++i) {
		auto s = flowTumn::tstr(argv[i]);
		for (auto& each : commandLine) {
			if (flowTumn::tstr(argv[i]) == flowTumn::conv(std::get <0> (each))) {
				if (i + 1 < argc) {
					std::get <1>(each)(argv[i + 1]);
					++i;
					break;
				}
			}
		}
	}

	if (!source.empty()) {
		auto result = adjustChapter(source, correctTime, roundUp);
		if (dest.empty()) {
			std::cout << result << std::endl;
		} else {
			std::ofstream ofs(dest);
			if (ofs.good()) {
				ofs << result;
			}
			else {
				err << _T("output error: ") << dest << std::endl;
			}
		}
	}

	return 0;
}

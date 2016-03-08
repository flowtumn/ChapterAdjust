#include "converter.h"

#include <array>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <stdexcept>

/**
 * 0のパディング埋め、文字列に変換。
 */
static auto padding(int64_t v, int32_t digit) -> std::string {
	--digit;
	return (0 < digit && v < static_cast <int64_t> (std::pow(10, digit)))
		? "0" + padding(v, digit)
		: std::to_string(v);
}

/**
 * 時間表記なので2桁。
 */
static auto convTimeStr(int64_t t) -> std::string {
    return padding(t, 2);
}

template <typename ... Args>
static auto convTimeStr(int64_t elem, Args ... args) -> std::string {
	return convTimeStr(elem) + ":" + convTimeStr(std::forward <Args>(args)...);
}

auto flowTumn::converter::correctionChapterTime(std::string t, uint64_t millis, uint32_t roundUp) -> std::string {
	if (9 < roundUp) {
		throw std::invalid_argument("roundUp invalid.");
	}

	const auto tt = convertChapterTimeStr2Integer(t) + millis;
	return convertChapterTimeInteger2Str(
			tt
		+	[tt, roundUp] {
				auto result = INT64_C(0);
				if (0 < roundUp) {
					auto radix = static_cast <uint32_t> (std::pow(10, roundUp));
					if (auto d = tt % radix) {
						result = static_cast <int64_t> (radix - d);
					}
				}
				return result;
		}()
	);
}

auto flowTumn::converter::convertChapterTimeStr2Integer(std::string t)->int64_t {
	static std::array <char, 2> trim = { {':', '.'} };

	std::for_each(
		std::begin(trim),
		std::end(trim),
		[&t](const auto each) {
			t.erase(std::remove(std::begin(t), std::end(t), each), std::end(t));
	});

	return static_cast <int64_t> (std::atoll(t.data()));
}


auto flowTumn::converter::convertChapterTimeInteger2Str(int64_t t)->std::string {
	const auto ms = t % 1000;
	const auto s = (t % 100000) / 1000;
	const auto m = (t % 10000000) / 100000;
	const auto h = (t % 1000000000) / 10000000;
	const auto cs = s % 60;
	const auto cm = (m + (s / 60)) % 60;
	const auto ch = (h + ((m + (s / 60)) / 60)) % 100;

	//hh;mm:ss:mss:
	return convTimeStr(ch, cm, cs) + "." + padding(ms, 3);
}

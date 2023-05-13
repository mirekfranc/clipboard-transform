#include <string>
#include <string_view>
#include <iostream>
#include <algorithm>
#include <cctype>

namespace {
	using namespace std::string_view_literals;

	constexpr const auto kernel_url = "https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id="sv;
	constexpr const auto bugzilla_url = "https://bugzilla.suse.com/show_bug.cgi?id="sv;
	constexpr const auto bsc_id = "bsc#"sv;
	constexpr const auto bnc_id = "bnc"sv;
	constexpr const auto gcc_url = "https://gcc.gnu.org/bugzilla/show_bug.cgi?id="sv;
	constexpr const auto gcc_id = "PR"sv;
	constexpr const auto git_a = "a/"sv;
	constexpr const auto git_b = "b/"sv;

	bool is_bug_url(std::string_view lv) { return lv.starts_with(bugzilla_url); }
	bool is_upstream_url(std::string_view lv) { return lv.starts_with(kernel_url); }
	bool is_bsc(std::string_view lv) { return lv.starts_with(bsc_id); }
	bool is_bnc(std::string_view lv) { return lv.starts_with(bnc_id); }
	bool is_bugn(std::string_view lv) { return lv.size() < 8 && std::ranges::all_of(lv, ::isdigit); }
	bool is_hash(std::string_view lv) { return lv.size() > 7 && std::ranges::all_of(lv, ::isxdigit); }
	bool is_gcc_id(std::string_view lv) { return lv.starts_with(gcc_id); }
	bool is_gcc_url(std::string_view lv) { return lv.starts_with(gcc_url); }
	bool is_git_path(std::string_view lv) { return lv.starts_with(git_a) || lv.starts_with(git_b); }

	std::string transform_line(const std::string&);
}

int main()
{
	std::string s;
	std::cin >> s;
	std::cout << transform_line(s);
}

namespace {
	std::string transform_line(const std::string& l)
	{
		if (is_bug_url(l))
			return std::string(bsc_id) + l.substr(bugzilla_url.size());
		else if (is_upstream_url(l))
			return l.substr(kernel_url.size());
		else if (is_bsc(l))
			return std::string(bugzilla_url) + l.substr(bsc_id.size());
		else if (is_bnc(l))
			return std::string(bugzilla_url) + l.substr(bnc_id.size());
		else if (is_bugn(l))
			return std::string(bugzilla_url) + l;
		else if (is_hash(l))
			return std::string(kernel_url) + l;
		else if (is_gcc_id(l))
			return std::string(gcc_url) + l.substr(gcc_id.size());
		else if (is_gcc_url(l))
			return std::string(gcc_id) + l.substr(gcc_url.size());
		else if (is_git_path(l))
			return l.substr(git_a.size());
		return l;
	}
}

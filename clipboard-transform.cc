#include <string>
#include <string_view>
#include <iostream>
#include <algorithm>
#include <cctype>

namespace {
	constexpr const std::string_view kernel_url = "https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=";
	constexpr const std::string_view bugzilla_url = "https://bugzilla.suse.com/show_bug.cgi?id=";
	constexpr const std::string_view bsc_id = "bsc#";

	bool is_bug_url(const std::string& l) { return l.starts_with(bugzilla_url); }
	bool is_upstream_url(const std::string& l) { return l.starts_with(kernel_url); }
	bool is_bsc(const std::string& l) { return l.starts_with(bsc_id); }
	bool is_bugn(const std::string& l) { return l.size() < 8 && std::ranges::all_of(l, ::isdigit); }
	bool is_hash(const std::string& l) { return l.size() > 7 && std::ranges::all_of(l, ::isxdigit); }

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
		else if (is_bugn(l))
			return std::string(bugzilla_url) + l;
		else if (is_hash(l))
			return std::string(kernel_url) + l;
		return l;
	}
}

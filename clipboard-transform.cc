#include <string>
#include <string_view>
#include <iostream>
#include <algorithm>
#include <cctype>

namespace {
	constexpr const std::string_view kernel_url = "https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=";
	constexpr const std::string_view bugzilla_url = "https://bugzilla.suse.com/show_bug.cgi?id=";
	constexpr const std::string_view bsc_id = "bsc#";
	constexpr const std::string_view bnc_id = "bnc";
	constexpr const std::string_view gcc_url = "https://gcc.gnu.org/bugzilla/show_bug.cgi?id=";
	constexpr const std::string_view gcc_id = "PR";
	constexpr const std::string_view git_a = "a/";
	constexpr const std::string_view git_b = "b/";

	bool is_bug_url(const std::string& l) { return l.starts_with(bugzilla_url); }
	bool is_upstream_url(const std::string& l) { return l.starts_with(kernel_url); }
	bool is_bsc(const std::string& l) { return l.starts_with(bsc_id); }
	bool is_bnc(const std::string& l) { return l.starts_with(bnc_id); }
	bool is_bugn(const std::string& l) { return l.size() < 8 && std::ranges::all_of(l, ::isdigit); }
	bool is_hash(const std::string& l) { return l.size() > 7 && std::ranges::all_of(l, ::isxdigit); }
	bool is_gcc_id(const std::string& l) { return l.starts_with(gcc_id); }
	bool is_gcc_url(const std::string& l) { return l.starts_with(gcc_url); }
	bool is_git_path(const std::string& l) { return l.starts_with(git_a) || l.starts_with(git_b); }

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

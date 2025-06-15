#include "validate.h"

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define debug(...) //ignore
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double ld;

int main(int argc, char **argv) {
	init_io(argc, argv);

	string a,b,lcs;
	judge_in >> a >> b >> lcs;

	// is a a subsequence of b?
	auto is_subsequence = [](string a, string b)
	{
		int j = 0;
		rep(i,0,sz(a))
		{
			while (j<sz(b)&&a[i]!=b[j]) j++;
			if (j==sz(b)) return false;
			j++;
		}
		return true;
	};

	auto check = [&](istream& sol, feedback_function feedback){
		string ans;
		if(!(sol >> ans)) feedback("Expected more output");
		for (char& c : ans)
		{
			if (c < 'a' || c > 'z')
			{
				feedback("Answer contains character that is not a or z, which is provably suboptimal");
			}
		}
		
		if (!is_subsequence(a, ans)) feedback("a is not subsequence of the given answer");
		if (!is_subsequence(b, ans)) feedback("b is not subsequence of the given answer");

		string trailing;
		if(sol >> trailing) feedback("Trailing output");
		return sz(ans);
	};
	int scs_length = sz(a)+sz(b)-sz(lcs);
	int judge_length = check(judge_ans, judge_error);
  	int author_length = check(author_out, wrong_answer);

	if (min(author_length, judge_length) < scs_length)
	{
		judge_error("Incorrect LCS");
	}

	if (author_length < judge_length) judge_error("NO! contestant found shorter solution than judge");
	if (author_length > judge_length) wrong_answer("Suboptimal answer: got "+to_string(author_length) + ", expected " + to_string(judge_length));

	accept();
}
